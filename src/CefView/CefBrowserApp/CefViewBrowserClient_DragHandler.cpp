﻿#include <CefViewBrowserClient.h>

#pragma region std_headers
#include <sstream>
#include <string>
#include <algorithm>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#include <Common/CefViewCoreLog.h>

CefRefPtr<CefDragHandler>
CefViewBrowserClient::GetDragHandler()
{
  return this;
}

bool
CefViewBrowserClient::OnDragEnter(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefDragData> dragData,
                                  CefDragHandler::DragOperationsMask mask)
{
  CEF_REQUIRE_UI_THREAD();

  // Forbid dragging of URLs and files.
  if ((mask & DRAG_OPERATION_LINK) && !dragData->IsFragment()) {
    return true;
  }

  return false;
}

void
CefViewBrowserClient::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
                                                CefRefPtr<CefFrame> frame,
                                                const std::vector<CefDraggableRegion>& regions)
{
  CEF_REQUIRE_UI_THREAD();

  auto delegate = client_delegate_.lock();
  if (delegate)
    delegate->draggableRegionChanged(browser, regions);
}
