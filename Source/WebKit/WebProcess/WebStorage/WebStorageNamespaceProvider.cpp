/*
 * Copyright (C) 2014-2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "WebStorageNamespaceProvider.h"

#include "WebPage.h"
#include "WebPageGroupProxy.h"
#include "WebProcess.h"
#include <wtf/HashMap.h>
#include <wtf/NeverDestroyed.h>

namespace WebKit {
using namespace WebCore;

static HashMap<StorageNamespaceIdentifier, WebStorageNamespaceProvider*>& storageNamespaceProviders()
{
    static NeverDestroyed<HashMap<StorageNamespaceIdentifier, WebStorageNamespaceProvider*>> storageNamespaceProviders;

    return storageNamespaceProviders;
}

Ref<WebStorageNamespaceProvider> WebStorageNamespaceProvider::getOrCreate(WebPageGroupProxy& pageGroup)
{
    RefPtr<WebStorageNamespaceProvider> storageNamespaceProvider;
    auto* result = storageNamespaceProviders().ensure(pageGroup.localStorageNamespaceIdentifier(), [&]() {
        storageNamespaceProvider = adoptRef(*new WebStorageNamespaceProvider(pageGroup.localStorageNamespaceIdentifier()));
        return storageNamespaceProvider.get();
    }).iterator->value;
    return *result;
}

void WebStorageNamespaceProvider::incrementUseCount(const WebPageGroupProxy& pageGroup, const StorageNamespaceImpl::Identifier identifier)
{
    auto storageNamespace = storageNamespaceProviders().find(pageGroup.localStorageNamespaceIdentifier());
    ASSERT(storageNamespace != storageNamespaceProviders().end());
    ASSERT(storageNamespace->value);
    auto& slot = storageNamespace->value->m_sessionStorageNamespaces.add(identifier, SessionStorageNamespaces { }).iterator->value;
    ++slot.useCount;
}

void WebStorageNamespaceProvider::decrementUseCount(const WebPageGroupProxy& pageGroup, const StorageNamespaceImpl::Identifier identifier)
{
    auto storageNamespace = storageNamespaceProviders().find(pageGroup.localStorageNamespaceIdentifier());

    if (storageNamespace == storageNamespaceProviders().end() || !storageNamespace->value)
        return;

    auto& namespaces = storageNamespace->value->m_sessionStorageNamespaces;

    auto slot = namespaces.find(identifier);
    ASSERT(slot != namespaces.end());
    ASSERT(slot->value.useCount);
    --slot->value.useCount;
    if (!slot->value.useCount)
        namespaces.remove(identifier);
}

WebStorageNamespaceProvider::WebStorageNamespaceProvider(StorageNamespaceIdentifier localStorageNamespaceIdentifier)
    : m_localStorageNamespaceIdentifier(localStorageNamespaceIdentifier)
{
}

WebStorageNamespaceProvider::~WebStorageNamespaceProvider()
{
    ASSERT(storageNamespaceProviders().contains(m_localStorageNamespaceIdentifier));

    storageNamespaceProviders().remove(m_localStorageNamespaceIdentifier);
}

Ref<WebCore::StorageNamespace> WebStorageNamespaceProvider::createLocalStorageNamespace(unsigned quota, PAL::SessionID sessionID)
{
    ASSERT_UNUSED(sessionID, sessionID == WebProcess::singleton().sessionID());
    return StorageNamespaceImpl::createLocalStorageNamespace(m_localStorageNamespaceIdentifier, quota);
}

Ref<WebCore::StorageNamespace> WebStorageNamespaceProvider::createTransientLocalStorageNamespace(WebCore::SecurityOrigin& topLevelOrigin, unsigned quota, PAL::SessionID sessionID)
{
    ASSERT_UNUSED(sessionID, sessionID == WebProcess::singleton().sessionID());
    return StorageNamespaceImpl::createTransientLocalStorageNamespace(m_localStorageNamespaceIdentifier, topLevelOrigin, quota);
}

RefPtr<WebCore::StorageNamespace> WebStorageNamespaceProvider::sessionStorageNamespace(const WebCore::SecurityOrigin& topLevelOrigin, WebCore::Page& page, ShouldCreateNamespace shouldCreate)
{
    ASSERT(sessionStorageQuota() != WebCore::StorageMap::noQuota);

    auto& webPage = WebPage::fromCorePage(page);

    // The identifier of a session storage namespace is the WebPageProxyIdentifier. It is possible we have several WebPage objects in a single process for the same
    // WebPageProxyIdentifier and these need to share the same namespace instance so we know where to route the IPC to.
    auto& namespacesSlot = m_sessionStorageNamespaces.add(webPage.sessionStorageNamespaceIdentifier(), SessionStorageNamespaces { }).iterator->value;
    auto& slot = namespacesSlot.map.add(topLevelOrigin.data(), nullptr).iterator->value;
    if (!slot && shouldCreate == ShouldCreateNamespace::Yes)
        slot = StorageNamespaceImpl::createSessionStorageNamespace(webPage.sessionStorageNamespaceIdentifier(), webPage.identifier(), topLevelOrigin, sessionStorageQuota());
    return slot;
}

void WebStorageNamespaceProvider::setSessionStorageNamespace(const WebCore::SecurityOrigin& topLevelOrigin, WebCore::Page& page, RefPtr<WebCore::StorageNamespace>&& newNamespace)
{
    auto& webPage = WebPage::fromCorePage(page);

    auto& slot = m_sessionStorageNamespaces.add(webPage.sessionStorageNamespaceIdentifier(), SessionStorageNamespaces { }).iterator->value;
    slot.map.add(topLevelOrigin.data(), WTFMove(newNamespace));
}

}
