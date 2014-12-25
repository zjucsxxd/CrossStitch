#include "stdafx.h"
#include "MainWindow.h"
#include "Resources.h"

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

    hWnd_ = CreateWindowEx(WS_EX_LAYERED, szClassName, wndName, WS_OVERLAPPEDWINDOW, 0, 0,
                         WND_WIDTH, WND_HEIGHT, NULL, NULL, hInstance, NULL);

    if (hWnd_ == NULL)
        return;

    HBITMAP hBmp = LoadBitmap(hInstance, MAKEINTRESOURCE(ID_MAIN_WINDOW_BMP));
    BITMAP bm;
    GetObject(hBmp, sizeof(bm), &bm);
    int bmpWidth = bm.bmWidth;
    int bmpHeight = bm.bmHeight;

    HDC hDcScreen = GetDC(0);
    HDC hDc = CreateCompatibleDC(hDcScreen);
    ReleaseDC(0, hDcScreen);
    HBITMAP hBmpOld = (HBITMAP)SelectObject(hDc, hBmp);

    POINT dcOffset = { 0, 0 };
    SIZE size = { bmpWidth, bmpHeight };
    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;
    bf.AlphaFormat = AC_SRC_ALPHA;
    UpdateLayeredWindow(hWnd_, 0, 0, &size, hDc, &dcOffset, RGB(0, 0, 0), &bf, ULW_COLORKEY);
    SelectObject(hDc, hBmpOld);
    DeleteDC(hDc);
    DeleteObject(hBmp);

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