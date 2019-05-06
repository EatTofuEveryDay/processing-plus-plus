// processing v0.0

#ifndef PRIVATE_H
#define PRIVATE_H

#include<string>
// Incase they are trying to call fill() and whatnot from another thread
#include<mutex>
#include<windows.h>
#include<chrono>
#include<thread>
#include<d2d1.h>
#undef min
#undef max
#include"basewin.h"
#include"../include/processing.h"
#include"strings.h"
#include"graphicshandles.h"

#ifndef EXT

namespace prxx {
  namespace __private {
    std::mutex staticvarlock;
    void aquire_lock() {
      while (staticvarlock.try_lock()) std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }
    tstring title;
    prxx::color_t fillcol; // Incase fillbrush is ever invalidated
    prxx::color_t strokecol;
	  bool operator!=(runningFunc a, runningFunc b);
    runningFunc cfn = runningFunc::null;
    double width;
    double height;
    double strokewidth;
    quadMode_t rectmode = quadMode_t::CORNER;
    quadMode_t ellipsemode = quadMode_t::CENTER;
    D2DGraphicsHandle<ID2D1Factory> pFactory;
    D2DGraphicsHandle<ID2D1HwndRenderTarget> pRenderTarget;
    D2DGraphicsHandle<ID2D1SolidColorBrush> fillbrush;
    D2DGraphicsHandle<ID2D1SolidColorBrush> strokebrush;
  }
}

#else

namespace prxx {
	namespace __private {
    void aquire_lock();

		extern std::mutex staticvarlock;
		extern tstring title;
		extern prxx::color_t fillcol; // Incase fillbrush is ever invalidated
		extern prxx::color_t strokecol;
		bool operator!=(runningFunc a, runningFunc b);
		extern runningFunc cfn;
		extern double width;
		extern double height;
		extern double strokewidth;
		extern quadMode_t rectmode;
		extern quadMode_t ellipsemode;
    extern D2DGraphicsHandle<ID2D1Factory> pFactory;
    extern D2DGraphicsHandle<ID2D1HwndRenderTarget> pRenderTarget;
    extern D2DGraphicsHandle<ID2D1SolidColorBrush> fillbrush;
    extern D2DGraphicsHandle<ID2D1SolidColorBrush> strokebrush;
	}
}

#endif

#endif