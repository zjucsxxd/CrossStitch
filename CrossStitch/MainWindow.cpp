#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow( LPCTSTR wndName, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc,
                        LPCTSTR menuName)
{
    wchar_t szClassName[] = L"CrossStitchWndClass";
    wc_.cbSize          = sizeof(wc_);
    wc_.style           = CS_HREDRAW | CS_VREDRAW;
    wc_.lpfnWndProc     = WndProc;
    wc_.cbClsExtra      = 0;
    wc_.cbWndExtra      = 0;
    wc_.hInstance       = hInstance;
    wc_.hIcon           = LoadIcon(NULL, IDI_APPLICATION);
    wc_.hCursor         = LoadCursor(NULL, IDC_ARROW);
    wc_.hbrBackground   = (HBRUSH)(1);
    wc_.lpszMenuName    = menuName;
    wc_.lpszClassName   = szClassName;
    wc_.hIconSm         = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc_))
        return;

    hWnd_ = CreateWindow(szClassName, wndName, WS_OVERLAPPEDWINDOW, 0, 0, 
                         WND_WIDTH, WND_HEIGHT, NULL, NULL, hInstance, NULL);

    if (hWnd_ == NULL)
        return;

    RECT rc;

    GetWindowRect(hWnd_, &rc);

    int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

    SetWindowPos(hWnd_, NULL, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

    ShowWindow(hWnd_, nCmdShow);
}

HWND MainWindow::GetHWND()
{
    return hWnd_;
}