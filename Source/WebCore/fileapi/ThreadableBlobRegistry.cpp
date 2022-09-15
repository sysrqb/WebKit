/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 * Copyright (C) 2013, 2014, 2016 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ThreadableBlobRegistry.h"

#include "BlobDataFileReference.h"
#include "BlobPart.h"
#include "BlobRegistry.h"
#include "BlobURL.h"
#include "CrossOriginOpenerPolicy.h"
#include "PolicyContainer.h"
#include "SecurityOrigin.h"
#include <mutex>
#include <wtf/CrossThreadQueue.h>
#include <wtf/CrossThreadTask.h>
#include <wtf/HashMap.h>
#include <wtf/MainThread.h>
#include <wtf/RefPtr.h>
#include <wtf/ThreadSpecific.h>
#include <wtf/text/StringHash.h>
#include <wtf/threads/BinarySemaphore.h>

namespace WebCore {

typedef HashMap<String, RefPtr<SecurityOrigin>> BlobUrlOriginMap;
typedef HashMap<const SecurityOrigin, BlobUrlOriginMap> PartitionedBlobUrlOriginMap;

static ThreadSpecific<PartitionedBlobUrlOriginMap>& originMap()
{
    static std::once_flag onceFlag;
    static ThreadSpecific<PartitionedBlobUrlOriginMap>* map;
    std::call_once(onceFlag, []{
        map = new ThreadSpecific<PartitionedBlobUrlOriginMap>;
    });

    return *map;
}

void ThreadableBlobRegistry::registerFileBlobURL(const URL& url, const SecurityOrigin& topOrigin, const String& path, const String& replacementPath, const String& contentType)
{
    String effectivePath = !replacementPath.isNull() ? replacementPath : path;

    if (isMainThread()) {
        blobRegistry(topOrigin)->registerFileBlobURL(url, BlobDataFileReference::create(effectivePath), path, contentType);
        return;
    }

    callOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy(), effectivePath = effectivePath.isolatedCopy(), path = path.isolatedCopy(), contentType = contentType.isolatedCopy()] {
        blobRegistry(topOrigin)->registerFileBlobURL(url, BlobDataFileReference::create(effectivePath), path, contentType);
    });
}

void ThreadableBlobRegistry::registerBlobURL(const URL& url, const SecurityOrigin& topOrigin, Vector<BlobPart>&& blobParts, const String& contentType)
{
    if (isMainThread()) {
        blobRegistry(topOrigin)->registerBlobURL(url, WTFMove(blobParts), contentType);
        return;
    }
    for (auto& part : blobParts)
        part.detachFromCurrentThread();
    callOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy(), blobParts = WTFMove(blobParts), contentType = contentType.isolatedCopy()]() mutable {
        blobRegistry(topOrigin)->registerBlobURL(url, WTFMove(blobParts), contentType);
    });
}

static inline bool isBlobURLContainsNullOrigin(const URL& url)
{
    ASSERT(url.protocolIsBlob());
    unsigned startIndex = url.pathStart();
    unsigned endIndex = url.pathAfterLastSlash();
    return StringView(url.string()).substring(startIndex, endIndex - startIndex - 1) == "null"_s;
}

void ThreadableBlobRegistry::registerBlobURL(const SecurityOrigin& topOrigin, SecurityOrigin* origin, PolicyContainer&& policyContainer, const URL& url, const URL& srcURL)
{
    // If the blob URL contains null origin, as in the context with unique security origin or file URL, save the mapping between url and origin so that the origin can be retrived when doing security origin check.
    if (origin && isBlobURLContainsNullOrigin(url))
        originMap()->add(topOrigin, BlobUrlOriginMap { }).add<StringViewHashTranslator>(url.viewWithoutFragmentIdentifier(), origin);

    if (isMainThread()) {
        blobRegistry(topOrigin)->registerBlobURL(url, srcURL, policyContainer);
        return;
    }

    callOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy(), srcURL = srcURL.isolatedCopy(), policyContainer = crossThreadCopy(WTFMove(policyContainer))] {
        blobRegistry(topOrigin)->registerBlobURL(url, srcURL, policyContainer);
    });
}

void ThreadableBlobRegistry::registerBlobURLOptionallyFileBacked(const URL& url, const SecurityOrigin& topOrigin, const URL& srcURL, const String& fileBackedPath, const String& contentType)
{
    if (isMainThread()) {
        blobRegistry(topOrigin)->registerBlobURLOptionallyFileBacked(url, srcURL, BlobDataFileReference::create(fileBackedPath), contentType);
        return;
    }
    callOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy(), srcURL = srcURL.isolatedCopy(), fileBackedPath = fileBackedPath.isolatedCopy(), contentType = contentType.isolatedCopy()] {
        blobRegistry(topOrigin)->registerBlobURLOptionallyFileBacked(url, srcURL, BlobDataFileReference::create(fileBackedPath), contentType);
    });
}

void ThreadableBlobRegistry::registerBlobURLForSlice(const URL& newURL, const SecurityOrigin& topOrigin, const URL& srcURL, long long start, long long end, const String& contentType)
{
    if (isMainThread()) {
        blobRegistry(topOrigin)->registerBlobURLForSlice(newURL, srcURL, start, end, contentType);
        return;
    }

    callOnMainThread([topOrigin = topOrigin.isolatedCopy(), newURL = newURL.isolatedCopy(), srcURL = srcURL.isolatedCopy(), start, end, contentType = contentType.isolatedCopy()] {
        blobRegistry(topOrigin)->registerBlobURLForSlice(newURL, srcURL, start, end, contentType);
    });
}

unsigned long long ThreadableBlobRegistry::blobSize(const URL& url, const SecurityOrigin& topOrigin)
{
    if (isMainThread())
        return blobRegistry(topOrigin)->blobSize(url);

    unsigned long long resultSize;
    callOnMainThreadAndWait([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy(), &resultSize] {
        resultSize = blobRegistry(topOrigin)->blobSize(url);
    });
    return resultSize;
}

void ThreadableBlobRegistry::unregisterBlobURL(const URL& url, const SecurityOrigin& topOrigin)
{
    if (isBlobURLContainsNullOrigin(url) && (auto& partitionedMap = originMap()->get(topOrigin)))
        partitionedMap.remove<StringViewHashTranslator>(url.viewWithoutFragmentIdentifier());

    ensureOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy()] {
        blobRegistry(topOrigin)->unregisterBlobURL(url);
    });
}

void ThreadableBlobRegistry::registerBlobURLHandle(const URL& url, const SecurityOrigin& topOrigin)
{
    ensureOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy()] {
        blobRegistry(topOrigin)->registerBlobURLHandle(url);
    });
}

void ThreadableBlobRegistry::unregisterBlobURLHandle(const URL& url, const SecurityOrigin& topOrigin)
{
    ensureOnMainThread([topOrigin = topOrigin.isolatedCopy(), url = url.isolatedCopy()] {
        blobRegistry(topOrigin)->unregisterBlobURLHandle(url);
    });
}

RefPtr<SecurityOrigin> ThreadableBlobRegistry::getCachedOrigin(const URL& url, const SecurityOrigin& topOrigin)
{
    if (auto& partitionedMap = originMap()->get(topOrigin)) {
        if (auto cachedOrigin = partitionedMap.get<StringViewHashTranslator>(url.viewWithoutFragmentIdentifier()))
            return cachedOrigin;
    }

    if (!url.protocolIsBlob() || !isBlobURLContainsNullOrigin(url))
        return nullptr;

    // If we do not have a cached origin for null blob URLs, we use a unique origin.
    return SecurityOrigin::createUnique();
}

} // namespace WebCore
