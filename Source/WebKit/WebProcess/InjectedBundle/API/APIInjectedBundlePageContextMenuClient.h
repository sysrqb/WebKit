/*
 * Copyright (C) 2014 Igalia S.L.
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

#ifndef APIInjectedBundlePageContextMenuClient_h
#define APIInjectedBundlePageContextMenuClient_h

#if ENABLE(CONTEXT_MENUS)

#include <wtf/Forward.h>
#include <wtf/TZoneMallocInlines.h>

namespace WebCore {
class ContextMenuContext;
class ContextMenuItem;
class HitTestResult;
}

namespace WebKit {
class WebContextMenuItemData;
class WebFrame;
class WebPage;
class WebSecurityOrigin;
}

namespace API {
class Object;

namespace InjectedBundle {

class PageContextMenuClient {
    WTF_MAKE_TZONE_ALLOCATED_INLINE(PageContextMenuClient);
public:
    virtual ~PageContextMenuClient() { }

    virtual bool getCustomMenuFromDefaultItems(WebKit::WebPage&, const WebCore::HitTestResult&, const Vector<WebCore::ContextMenuItem>& /* defaultMenu */, Vector<WebKit::WebContextMenuItemData>& /* newMenu */, const WebCore::ContextMenuContext&, RefPtr<API::Object>& /* userData */) { return false; }
    virtual void prepareForImmediateAction(WebKit::WebPage&, const WebCore::HitTestResult&, RefPtr<API::Object>& /* userData */) { }
};

} // namespace InjectedBundle

} // namespace API

#endif // ENABLE(CONTEXT_MENUS)
#endif // APIInjectedBundlePageContextMenuClient_h
