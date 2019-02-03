// processing v0.0

#include<string>
// Incase they are trying to call fill() and whatnot from another thread
#include<mutex>
#include<windows.h>
#include<d2d1.h>
#undef min
#undef max
#include"../include/processing.h"

#ifndef EXT

namespace prxx {
  namespace __private {
    std::mutex staticvarlock;
    std::wstring title;
    ID2D1SolidColorBrush* fillbrush;
    ID2D1SolidColorBrush* strokebrush;
    prxx::color_t fillcol; // Incase fillbrush is ever invalidated
    prxx::color_t strokecol;
	bool operator!=(runningFunc a, runningFunc b);
    runningFunc cfn = runningFunc::null;
    double width;
    double height;
    double strokewidth;
    quadMode_t rectmode = quadMode_t::CORNER;
    quadMode_t ellipsemode = quadMode_t::CENTER;
    ID2D1Factory            *pFactory;
    ID2D1HwndRenderTarget   *pRenderTarget;
  }
}

#else

namespace prxx {
	namespace __private {
		extern std::mutex staticvarlock;
		extern std::wstring title;
		extern ID2D1SolidColorBrush* fillbrush;
		extern ID2D1SolidColorBrush* strokebrush;
		extern prxx::color_t fillcol; // Incase fillbrush is ever invalidated
		extern prxx::color_t strokecol;
		bool operator!=(runningFunc a, runningFunc b);
		extern runningFunc cfn;
		extern double width;
		extern double height;
		extern double strokewidth;
		extern quadMode_t rectmode;
		extern quadMode_t ellipsemode;
		extern ID2D1Factory            *pFactory;
		extern ID2D1HwndRenderTarget   *pRenderTarget;
	}
}

#endif