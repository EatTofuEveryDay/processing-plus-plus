#include<exception>
#include"graphicshandles.h"

template<>
HRESULT D2DGraphicsHandle<ID2D1Factory>::Create() {
  return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pResource);
}

HRESULT CreateResource(D2DGraphicsHandle<ID2D1HwndRenderTarget>& renderTarget, ID2D1Factory* pFactory, HWND m_hwnd, D2D1_SIZE_U size) {
  return pFactory->CreateHwndRenderTarget(
    D2D1::RenderTargetProperties(),
    D2D1::HwndRenderTargetProperties(m_hwnd, size),
    &renderTarget.pResource);
}