#pragma once

#define     WND_WIDTH       500
#define     WND_HEIGHT      400

class MainWindow
{
public:
                MainWindow( LPCTSTR wndName, 
                            HINSTANCE hInstance, 
                            int nCmdShow,
                            WNDPROC WndProc,
                            LPCTSTR menuName = NULL);

    HWND        GetHWND     (void);

private:
    HWND        hWnd_;
    WNDCLASSEX  wc_;
};