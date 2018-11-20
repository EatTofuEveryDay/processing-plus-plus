// processing v0.0

//https://docs.microsoft.com/en-gb/windows/desktop/learnwin32/your-first-direct2d-program

// I copied most of this code from there...

#include <windows.h>
#include <d2d1.h>
#include <cstdlib>
#include <string>

#ifdef _MSC_VER
// Do automatic linking if used in Visual Studio (only MSVS has support for this #pragma)
#pragma comment(lib, "d2d1")
#endif

#include "../include/processing.h"

#define EXT /* */
// Not external
#include "win32private.h"

#include "win32decl.h"

// Recalculate drawing layout when the size of the window changes.

HRESULT MainWindow::CreateGraphicsResources()
{
    using namespace prxx::__private;
    staticvarlock.aquire();
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0);
            hr = pRenderTarget->CreateSolidColorBrush(color, &prxx::__private::fillbrush);
        }
    }
    staticvarlock.release();
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    using namespace prxx::__private;
    staticvarlock.aquire();
    SafeRelease(&pRenderTarget);
    SafeRelease(&fillbrush);
    SafeRelease(&strokebrush);
    staticvarlock.release();
}

void MainWindow::OnPaint()
{
  using namespace prxx::__private;
  staticvarlock.aquire();
  HRESULT hr = CreateGraphicsResources();
  if (SUCCEEDED(hr))
  {
    PAINTSTRUCT ps;
    BeginPaint(m_hwnd, &ps);
    pRenderTarget->BeginDraw();
    // make sure that processing draw calls are being called in draw()
    prxx::__private::cfn = prxx::__private::draw;
    draw(); // processing function
    prxx::__private::cfn = prxx::__private::null;
    hr = pRenderTarget->EndDraw();
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
      DiscardGraphicsResources();
    EndPaint(m_hwnd, &ps);
  }
  staticvarlock.release();
}

void MainWindow::Resize()
{
  using namespace prxx::__private;
  staticvarlock.aquire();
  if (pRenderTarget != NULL)
  {
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
    windowResized(size.width, size.height); // processing function
    pRenderTarget->Resize(size);
    InvalidateRect(m_hwnd, NULL, FALSE);
  }
  staticvarlock.release();
}

// WinMain?
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
  using namespace prxx::__private;
  staticvarlock.aquire();
  cfn = runningFunc::setup;
  // Avoid double aquire
  staticvarlock.release();
  MainWindow win;
  
  setup(); // processing function
  
  // Check if width and height are 0
  staticvarlock.aquire();
  if(!(width + height))
    return 0;

  if (!win.Create(title.c_str(), WS_OVERLAPPEDWINDOW, 0, width, height))
    return 0;
  staticvarlock.release();
  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg { };
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

// Like WindowProc but for this window
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  using namespace prxx::__private;
    switch (uMsg)
    {
    case WM_CREATE:
        staticvarlock.aquire();
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
          std::abort();
        staticvarlock.release();
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        staticvarlock.aquire();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        staticvarlock.release();
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
