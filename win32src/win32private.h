// processing v0.0

#include<string>
// Incase they are trying to call fill() and whatnot from another thread
#include<mutex>
#include<windows.h>
#include<d2d1.h>
#include"../include/processing.h"

#ifdef EXT

namespace prxx {
  namespace __private {
    std::mutex staticvarlock;
    std::wstring title;
    ID2D1SolidColorBrush* fillbrush;
    ID2D1SolidColorBrush* strokebrush;
    prxx::color_t fillcol; // Incase fillbrush is ever invalidated
    prxx::color_t strokecol;
    enum class runningFunc 
    {
      null,
      setup,
      draw,
      event
	};
    runningFunc cfn = runningFunc::null;
    unsigned int width;
    unsigned int height;
    double strokewidth;
    quadMode_t rectmode = quadMode_t::CORNER;
    quadMode_t ellipsemode = quadMode_t::CENTER;
    ID2D1Factory            *pFactory;
    ID2D1HwndRenderTarget   *pRenderTarget;
  }
  void reload_brushes() {
	 fill(__private::fillcol);
	 stroke(__private::strokecol);
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
		enum class runningFunc;
		extern runningFunc cfn;
		extern unsigned int width;
		extern unsigned int height;
		extern double strokewidth;
		extern quadMode_t rectmode;
		extern quadMode_t ellipsemode;
		extern ID2D1Factory            *pFactory;
		extern ID2D1HwndRenderTarget   *pRenderTarget;
	}
	void reload_brushes() {
		fill(__private::fillcol);
		stroke(__private::strokecol);
	}
}

#endif