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
#include<dwrite.h>
#undef min
#undef max
#include"basewin.h"
#include"../include/processing.h"
#include"strings.h"
#include"graphicshandles.h"

#ifndef EXT



#else

namespace prxx {
	namespace __private {
    void aquire_lock();

		extern std::mutex staticvarlock;
		extern tstring title;
		extern prxx::PColor fillcol; // Incase fillbrush is ever invalidated
		extern prxx::PColor strokecol;
		bool operator!=(runningFunc a, runningFunc b);
		extern runningFunc cfn;
		extern double width;
		extern double height;
		extern double strokewidth;
		extern QuadMode rectmode;
		extern QuadMode ellipsemode;
    extern D2DGraphicsHandle<ID2D1Factory> pFactory;
    extern D2DGraphicsHandle<ID2D1HwndRenderTarget> pRenderTarget;
    extern D2DGraphicsHandle<ID2D1SolidColorBrush> fillbrush;
    extern D2DGraphicsHandle<ID2D1SolidColorBrush> strokebrush;
    extern D2DGraphicsHandle<IDWriteFactory> pWriteFactory;
    extern IDWriteTextFormat* textFormat;
    extern std::chrono::time_point<std::chrono::high_resolution_clock> programstart;
    
	}
}

#endif

#endif