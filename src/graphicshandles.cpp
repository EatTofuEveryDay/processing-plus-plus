#include<exception>
#include"graphicshandles.h"

template<>
HRESULT D2DGraphicsHandle<ID2D1Factory>::Create() {
  return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pResource);
}

HRESULT CreateResource(D2DGraphicsHandle<ID2D1HwndRenderTarget>& renderTarget, ID2D1Factory* pFactory, HWND m_hwnd) {
  RECT rc;
  GetClientRect(m_hwnd, &rc);
  D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
  return pFactory->CreateHwndRenderTarget(
    D2D1::RenderTargetProperties(),
    D2D1::HwndRenderTargetProperties(m_hwnd, size),
    &renderTarget.pResource);
}