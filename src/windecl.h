// processing v0.0

#include "basewin.h"

class MainWindow : public BaseWindow<MainWindow>
{

    void    CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    tstring classname;

public:

  MainWindow() {
		using namespace prxx::__private;
    aquire_lock();
		staticvarlock.unlock();
    // use pointer values to generate a random hex number
    classname = tstring(_T("ProcessingPlusPlus-wnd")) + to_tstring(reinterpret_cast<long long>(&m_hwnd));
	}

    LPCWSTR ClassName() const { return classname.c_str(); }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
