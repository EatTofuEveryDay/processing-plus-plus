// processing v0.0

#include <windows.h>
#include <d2d1.h>
#include <cstdlib>
#include <string>

#ifdef _MSC_VER
// Do automatic linking if used in Visual Studio (only MSVS has support for this #pragma)
#pragma comment(lib, "d2d1")
#endif

#include "../include/processing.h"

#undef EXT
// Not external
#include "private.h"
#include "exceptions.h"
#include "windecl.h"

// Recalculate drawing layout when the size of the window changes.

void MainWindow::CreateGraphicsResources()
{
  using namespace prxx::__private;
  aquire_lock();
  HRESULT hr = S_OK;
  if (pFactory.IsNull()) {
    hr = pFactory.Create();
    if (FAILED(hr)) {
      throw new D2DCreateResourceError(std::string("CreateFactory failed with HRESULT ") + std::to_string(hr));
    }
  }
  if (pRenderTarget.IsNull())
  {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    hr = pFactory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(m_hwnd, size),
      &pRenderTarget);

    if (FAILED(hr))
    {
      throw new D2DCreateResourceError(std::string("CreateHwndRenderTarget failed with HRESULT ") + std::to_string(hr));
    }
    D2D1_COLOR_F color = D2D1::ColorF(FLOAT(fillcol.r / 255), FLOAT(fillcol.g / 255), FLOAT(fillcol.b / 255), FLOAT(1 - (fillcol.a / 255)));
    hr = pRenderTarget->CreateSolidColorBrush(color, &fillbrush);
    if (FAILED(hr))
    {
      throw new D2DCreateResourceError(std::string("CreateSolidColorBrush failed with HRESULT ") + std::to_string(hr));
    }
    color = D2D1::ColorF(FLOAT(strokecol.r / 255), FLOAT(strokecol.g / 255), FLOAT(strokecol.b / 255), FLOAT(1 - (strokecol.a / 255)));
    hr = pRenderTarget->CreateSolidColorBrush(color, &fillbrush);
    if (FAILED(hr)) {
      throw new D2DCreateResourceError(std::string("CreateSolidColorBrush failed with HRESULT ") + std::to_string(hr));
    }
  }
  staticvarlock.unlock();
}

void MainWindow::DiscardGraphicsResources()
{
  using namespace prxx::__private;
  aquire_lock();
  SafeRelease(&pRenderTarget);
  SafeRelease(&fillbrush);
  SafeRelease(&strokebrush);
  staticvarlock.unlock();
}

void MainWindow::OnPaint()
{
  using namespace prxx::__private;
  aquire_lock();
  CreateGraphicsResources();
  prxx::fill(fillcol);
  prxx::stroke(strokecol);

  PAINTSTRUCT ps;
  BeginPaint(m_hwnd, &ps);
  pRenderTarget->BeginDraw();
  // make sure that processing draw calls are being called in draw()
  cfn = runningFunc::draw;
  draw(); // processing function
  cfn = runningFunc::null;
  HRESULT hr = pRenderTarget->EndDraw();
  if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
    DiscardGraphicsResources();
    CreateGraphicsResources();
    EndPaint(m_hwnd, &ps);
  }
  staticvarlock.unlock();
}

void MainWindow::Resize()
{
  using namespace prxx::__private;
  aquire_lock();
  if (!pRenderTarget.IsNull())
  {
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
    windowResized(size.width, size.height); // processing function
    pRenderTarget->Resize(size);
    InvalidateRect(m_hwnd, NULL, FALSE);
  }
  staticvarlock.unlock();
}

// WinMain?
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, int nCmdShow)
{

  using namespace prxx::__private;
  aquire_lock();
  cfn = runningFunc::setup;
  // Avoid double aquire
  staticvarlock.unlock();
  MainWindow win;

  setup(); // processing function

  // Check if width and height are 0
  aquire_lock();
  if (!(width + height))
    return 1;

  if (!win.Create(title.c_str(), WS_OVERLAPPEDWINDOW, hInstance, WS_EX_LEFT, CW_USEDEFAULT, CW_USEDEFAULT, (int)std::floor(width), (int)std::floor(height)))
    return 1;

  staticvarlock.unlock();
  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg{ };
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
  case WM_CREATE: {
    aquire_lock();
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
      std::abort();
    staticvarlock.unlock();
    return 0;
  }

  case WM_DESTROY:
    DiscardGraphicsResources();
    aquire_lock();
    SafeRelease(&pFactory);
    PostQuitMessage(0);
    staticvarlock.unlock();
    return 0;

  case WM_PAINT:
    OnPaint();
    return 0;

  case WM_SIZE:
    Resize();
    return 0;

  case WM_KEYDOWN:
    keyPressed((char)wParam);
    return 0;

  case WM_KEYUP:
    keyReleased((char)wParam);
    return 0;
  }
  return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}