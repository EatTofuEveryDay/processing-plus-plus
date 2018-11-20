// processing v0.0

#include<string>
// Incase they are trying to call fill() and whatnot from another thread
#include<mutex>
#include<windows.h>
#include<d2d1.h>
#include"../include/processing.h"

#ifndef EXT
#define CEXT 1
#define EXT extern
#endif

namespace prxx {
  namespace __private {
    EXT std::mutex staticvarlock;
    EXT std::wstring title;
    EXT ID2D1SolidColorBrush* fillbrush;
    EXT ID2D1SolidColorBrush* strokebrush;
    EXT color_t fillcol; // Incase fillbrush is ever invalidated
    EXT color_t strokecol;
    enum class runningFunc
    #ifndef CEXT
    {
      null,
      setup,
      draw,
      event
    }
    #endif
    ;
    EXT runningFunc cfn
    #ifndef CEXT
    = runningFunc::null
    #endif
    ;
    EXT unsigned int width;
    EXT unsigned int height;
    EXT double strokewidth;
    EXT quadMode_t rectmode
    #ifndef CEXT
    = quadMode_t::CORNER
    #endif
    ;
    EXT quadMode_t ellipsemode
    #ifndef CEXT
    = quadMode_t::CENTER
    #endif
    ;
    EXT ID2D1Factory            *pFactory;
    EXT ID2D1HwndRenderTarget   *pRenderTarget;
  }
}
