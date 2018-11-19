// processing v0.0

#include "basewin.h"

class MainWindow : public BaseWindow<MainWindow>
{

    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();

public:

    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
    {}

    PCWSTR  ClassName() const { return prxx::__private::title.c_str(); }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};