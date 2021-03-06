
/*-------------------------------------------------------------------------------------------------

14-mar-2020: Started with Win32 boilerplate code.

-------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "sample_win_proj1.h"

//-------------------------------------------------------------------------------------------------

#define MAX_LOADSTRING 100

//-------------------------------------------------------------------------------------------------

// Globals only for the sake of quick-n-dirty trial code..

HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

//-------------------------------------------------------------------------------------------------

ATOM				MyRegisterClass (HINSTANCE hInstance);
BOOL				InitInstance (HINSTANCE, int);
LRESULT CALLBACK	WndProc (HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About (HWND, UINT, WPARAM, LPARAM);

//-------------------------------------------------------------------------------------------------

int APIENTRY _tWinMain (_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow
    )
{
    UNREFERENCED_PARAMETER (hPrevInstance);
    UNREFERENCED_PARAMETER (lpCmdLine);

    MSG msg;
    HACCEL hAccelTable;

    LoadString (hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString (hInstance, IDC_SAMPLE_WIN_PROJ1, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass (hInstance);

    if (!InitInstance (hInstance, SW_MAXIMIZE))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators (hInstance, MAKEINTRESOURCE (IDC_SAMPLE_WIN_PROJ1));

    while (GetMessage (&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    return (int) msg.wParam;
}

//-------------------------------------------------------------------------------------------------

ATOM MyRegisterClass (HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof (WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon (hInstance, MAKEINTRESOURCE (IDI_SAMPLE_WIN_PROJ1));
    wcex.hCursor = LoadCursor (NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE (IDC_SAMPLE_WIN_PROJ1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon (wcex.hInstance, MAKEINTRESOURCE (IDI_SMALL));

    return RegisterClassEx (&wcex);
}

//-------------------------------------------------------------------------------------------------

BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow (
        szWindowClass,
        szTitle,
        WS_MAXIMIZE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_SYSMENU,
        0, 0,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
        );

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

    return TRUE;
}

//-------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {

    case WM_COMMAND:

        wmId = LOWORD (wParam);
        wmEvent = HIWORD (wParam);

        switch (wmId)
        {
        case IDM_ABOUT:

            DialogBox (hInst, MAKEINTRESOURCE (IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:

            DestroyWindow (hWnd);
            break;

        default:

            return DefWindowProc (hWnd, message, wParam, lParam);
        }
        break;

    case WM_PAINT:

        hdc = BeginPaint (hWnd, &ps);
        EndPaint (hWnd, &ps);
        break;

    case WM_DESTROY:

        PostQuitMessage (0);
        break;

    default:

        return DefWindowProc (hWnd, message, wParam, lParam);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------

INT_PTR CALLBACK About (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER (lParam);

    switch (message)
    {

    case WM_INITDIALOG:

        return (INT_PTR) TRUE;

    case WM_COMMAND:

        if (LOWORD (wParam) == IDOK || LOWORD (wParam) == IDCANCEL)
        {
            EndDialog (hDlg, LOWORD (wParam));
            return (INT_PTR) TRUE;
        }
        break;
    }

    return (INT_PTR) FALSE;
}

//-------------------------------------------------------------------------------------------------
