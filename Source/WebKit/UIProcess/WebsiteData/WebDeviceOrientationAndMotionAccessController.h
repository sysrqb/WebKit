/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(DEVICE_ORIENTATION)

#include <WebCore/DeviceOrientationOrMotionPermissionState.h>
#include <WebCore/SecurityOriginData.h>
#include <wtf/CanMakeWeakPtr.h>
#include <wtf/HashMap.h>

namespace WebKit {

class WebsiteDataStore;
class WebPageProxy;
class WebFrameProxy;
struct FrameInfoData;

class WebDeviceOrientationAndMotionAccessController : public CanMakeWeakPtr<WebDeviceOrientationAndMotionAccessController> {
public:
    WebDeviceOrientationAndMotionAccessController(WebsiteDataStore&);

    void ref() const;
    void deref() const;

    void shouldAllowAccess(WebPageProxy&, WebFrameProxy&, FrameInfoData&&, bool mayPrompt, CompletionHandler<void(WebCore::DeviceOrientationOrMotionPermissionState)>&&);
    void clearPermissions() { m_deviceOrientationPermissionDecisions.clear(); }
#if ENABLE(WEB_ARCHIVE)
    void clearPermissionsForWebArchives(WebPageProxy&);
#endif

    WebCore::DeviceOrientationOrMotionPermissionState cachedDeviceOrientationPermission(const WebCore::SecurityOriginData&, const URL&, WebPageProxy&) const;
    void setCachedDeviceOrientationPermission(const WebCore::SecurityOriginData&, WebCore::DeviceOrientationOrMotionPermissionState);

private:
    HashMap<WebCore::SecurityOriginData, bool> m_deviceOrientationPermissionDecisions;
    HashMap<WebCore::SecurityOriginData, Vector<CompletionHandler<void(WebCore::DeviceOrientationOrMotionPermissionState)>>> m_pendingRequests;

    WeakRef<WebsiteDataStore> m_websiteDataStore;
};

}

#endif
