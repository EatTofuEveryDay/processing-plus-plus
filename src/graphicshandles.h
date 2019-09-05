#ifndef GHANDLES_H
#define GHANDLES_H

#include<Windows.h>
#include<d2d1.h>
#include<exception>
#include"exceptions.h"
#include"basewin.h"

template<class T>
class D2DGraphicsHandle;

template<class T>
HRESULT CreateResource(D2DGraphicsHandle<T>& renderTarget, ID2D1Factory* pFactory, HWND m_hwnd);

template<class T>
class D2DGraphicsHandle {
  T* pResource;
public:
  template<class T>
  friend HRESULT CreateResource<>(D2DGraphicsHandle<T>&, ID2D1Factory* pFactory, HWND m_hwnd);
  D2DGraphicsHandle();
  ~D2DGraphicsHandle();
  HRESULT Create();
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

template<class T>
D2DGraphicsHandle<T>::D2DGraphicsHandle() : pResource(nullptr) {}

template<class T>
D2DGraphicsHandle<T>::~D2DGraphicsHandle() {
  Release();
}

template<class T>
HRESULT D2DGraphicsHandle<T>::Create() {
  return false;
}

template<>
HRESULT D2DGraphicsHandle<ID2D1Factory>::Create();

template<>
HRESULT D2DGraphicsHandle<IDWriteTextFormat>::Create();

template<class T>
void D2DGraphicsHandle<T>::Release() {
  SafeRelease(&pResource);
  pResource = nullptr;
}

template<class T>
bool D2DGraphicsHandle<T>::IsNull()
{
  return pResource == nullptr;
}

template<class T>
void D2DGraphicsHandle<T>::UnsafeSet(T * ptr)
{
  pResource = ptr;
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
  // Don't let user access nullptr
  if (IsNull()) {
    throw new D2DNullAccessError();
  }
  return pResource;
}

template<class T>
T ** D2DGraphicsHandle<T>::operator&()
{
  return &pResource;
}

#endif