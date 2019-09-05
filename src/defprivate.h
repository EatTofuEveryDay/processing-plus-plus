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

namespace prxx {
  namespace __private {
    std::mutex staticvarlock;
    void aquire_lock() {
      while (staticvarlock.try_lock()) std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }
    tstring title;
    prxx::PColor fillcol; // Incase fillbrush is ever invalidated
    prxx::PColor strokecol;
    bool operator!=(runningFunc a, runningFunc b);
    runningFunc cfn = runningFunc::null;
    double width;
    double height;
    double strokewidth;
    QuadMode rectmode = QuadMode::CORNER;
    QuadMode ellipsemode = QuadMode::CENTER;
    D2DGraphicsHandle<ID2D1Factory> pFactory;
    D2DGraphicsHandle<ID2D1HwndRenderTarget> pRenderTarget;
    D2DGraphicsHandle<ID2D1SolidColorBrush> fillbrush;
    D2DGraphicsHandle<ID2D1SolidColorBrush> strokebrush;
    extern D2DGraphicsHandle<IDWriteFactory> pWriteFactory;
    IDWriteTextFormat* textformat = nullptr;
    std::chrono::time_point<std::chrono::high_resolution_clock> programstart;
  }
}