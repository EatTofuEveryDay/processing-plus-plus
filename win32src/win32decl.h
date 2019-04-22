// processing v0.0

#include "basewin.h"

class MainWindow : public BaseWindow<MainWindow>
{

    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    tstring classname;

public:

  MainWindow() {
		using namespace prxx::__private;
    aquire_lock();
		pFactory = NULL;
		pRenderTarget = NULL;
		fillbrush = NULL;
		strokebrush = NULL;
		staticvarlock.unlock();
    // use pointer values to generate a random hex number
    classname = tstring(_T("ProcessingPlusPlus-wnd")) + to_tstring(reinterpret_cast<long long>("hex"));
    OutputDebugString(classname.c_str());
	}

    LPCWSTR ClassName() const { return classname.c_str(); }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
