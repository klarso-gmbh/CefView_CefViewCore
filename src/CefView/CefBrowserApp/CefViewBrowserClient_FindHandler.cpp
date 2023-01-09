#include <CefViewBrowserClient.h>

#pragma region std_headers
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

CefRefPtr<CefFindHandler>
CefViewBrowserClient::GetFindHandler()
{
  return this;
}

void
CefViewBrowserClient::OnFindResult(CefRefPtr<CefBrowser> browser,
                                    int identifier,
                                    int count,
                                    const CefRect& selectionRect,
                                    int activeMatchOrdinal,
                                    bool finalUpdate)
{
  CEF_REQUIRE_UI_THREAD();

  auto delegate = client_delegate_.lock();
  if (delegate)
    delegate->findResult(browser, identifier, count, selectionRect, activeMatchOrdinal, finalUpdate);
}

