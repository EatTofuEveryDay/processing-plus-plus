#ifndef BASEWIN_H
#define BASEWIN_H

#include<windows.h>
#include<d2d1.h>
#include<tchar.h>

#include"strings.h"

template <class T>
void SafeRelease(T **ppT)
{
  if (*ppT)
  {
    (*ppT)->Release();
    *ppT = NULL;
  }
}

template <class DERIVED_TYPE>
class BaseWindow
{
public:
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    DERIVED_TYPE *pThis = NULL;

    if (uMsg == WM_NCCREATE)
    {
      CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
      pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

      pThis->m_hwnd = hwnd;
    }
    else
    {
      pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pThis)
    {
      return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
  }

  BaseWindow() : m_hwnd(NULL) { }

  BOOL Create(
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    HINSTANCE hIns,
    DWORD dwExStyle = WS_EX_LEFT,
    int x = CW_USEDEFAULT,
    int y = CW_USEDEFAULT,
    int nWidth = CW_USEDEFAULT,
    int nHeight = CW_USEDEFAULT,
    HWND hWndParent = NULL,
    HMENU hMenu = NULL
  )
  {

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hIns;
    wc.lpszClassName = ClassName();

    if (!RegisterClass(&wc)) {
      tstring terr(to_tstring((int)GetLastError()));
      OutputDebugString(terr.c_str());
      while (true);
    }


    m_hwnd = CreateWindowEx(
      dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
      nWidth, nHeight, hWndParent, hMenu, hIns, this
    );
    return (m_hwnd ? TRUE : FALSE);
  }

  HWND Window() const { return m_hwnd; }

protected:

  virtual LPCWSTR ClassName() const = 0;
  virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  HWND m_hwnd;
};

#endif