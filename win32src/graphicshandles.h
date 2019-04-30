#include<Windows.h>
#include<d2d1.h>
#include<exception>
#include"basewin.h"

template<class T>
class D2DGraphicsHandle;

bool CreateResource(D2DGraphicsHandle<ID2D1HwndRenderTarget>& renderTarget, ID2D1Factory* pFactory, HWND m_hwnd, D2D1_SIZE_U size);

template<class T>
class D2DGraphicsHandle {
  T* pResource;
public:
  friend bool CreateResource(D2DGraphicsHandle<ID2D1HwndRenderTarget>&, ID2D1Factory* pFactory, HWND m_hwnd, D2D1_SIZE_U size);
  D2DGraphicsHandle();
  ~D2DGraphicsHandle();
  bool Create();
  void Release();
  bool IsNull();
  void UnsafeSet(T*);
  // Resources cannot be copied
  D2DGraphicsHandle<T> operator=(const D2DGraphicsHandle<T>&) = delete;
  D2DGraphicsHandle(const D2DGraphicsHandle<T>&) = delete;
  T* operator->();
  operator T*();
  T** operator &();
};

class D2DNullAccessError : public std::exception {
  const char* what() {
    return "D2DNullAccessError: attempt to access null resource";
  }
};

template<class T>
D2DGraphicsHandle<T>::D2DGraphicsHandle() {}

template<class T>
D2DGraphicsHandle<T>::~D2DGraphicsHandle() {
  Release();
}

template<class T>
bool D2DGraphicsHandle<T>::Create() {
  return true;
}

template<>
bool D2DGraphicsHandle<ID2D1Factory>::Create() {
  return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pResource);
}

template<class T>
void D2DGraphicsHandle<T>::Release() {
  SafeRelease(&pResource);
}

template<class T>
bool D2DGraphicsHandle<T>::IsNull()
{
  return pResource == nullptr;
}

template<class T>
void D2DGraphicsHandle<T>::UnsafeSet(T *)
{
  throw new std::exception("heh heh you thought you could bypass managed resources");
}

template<class T>
T* D2DGraphicsHandle<T>::operator->()
{
  if (IsNull()) {
    throw new D2DNullAccessError();
  }
  return pResource;
}

template<class T>
D2DGraphicsHandle<T>::operator T*()
{
  return pResource;
}

template<class T>
T ** D2DGraphicsHandle<T>::operator&()
{
  return &pResource;
}

bool CreateResource(D2DGraphicsHandle<ID2D1HwndRenderTarget>& renderTarget, ID2D1Factory* pFactory, HWND m_hwnd, D2D1_SIZE_U size) {
  return pFactory->CreateHwndRenderTarget(
    D2D1::RenderTargetProperties(),
    D2D1::HwndRenderTargetProperties(m_hwnd, size),
    &renderTarget.pResource);
}