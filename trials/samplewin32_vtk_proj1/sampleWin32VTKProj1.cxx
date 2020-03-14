
/*-------------------------------------------------------------------------------------------------

14-mar-2020: Originally copied from VTK examples, and then modified.

-------------------------------------------------------------------------------------------------*/

#include "windows.h"

//-------------------------------------------------------------------------------------------------

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"

//-------------------------------------------------------------------------------------------------

// Globals only for the sake of quick-n-dirty trial code..

static HANDLE hinst;

//-------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

//-------------------------------------------------------------------------------------------------

class myVTKApp
{
public:

    myVTKApp (HWND parent);
    ~myVTKApp ();

private:

    vtkRenderWindow *renWin;
    vtkRenderer *renderer;
    vtkRenderWindowInteractor *iren;
    vtkConeSource *cone;
    vtkPolyDataMapper *coneMapper;
    vtkActor *coneActor;
};

//-------------------------------------------------------------------------------------------------

int PASCAL WinMain (
    HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR /* lpszCmdParam */,
    int nCmdShow
    )
{
    static char szAppName [] = "Win32Cone";
    HWND        hwnd;
    MSG         msg;
    WNDCLASS    wndclass;

    if (!hPrevInstance)
    {
        wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wndclass.lpfnWndProc = WndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
        wndclass.lpszMenuName = NULL;
        wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
        wndclass.lpszClassName = szAppName;
        RegisterClass (&wndclass);
    }

    hinst = hInstance;
    hwnd = CreateWindow (
        szAppName,
        "Draw Window",
        WS_MAXIMIZE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0, 0,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow (hwnd, SW_MAXIMIZE);
    UpdateWindow (hwnd);

    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    return msg.wParam;
}

//-------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND ewin;
    static myVTKApp *theVTKApp;

    switch (message)
    {
    case WM_CREATE:
    {
        ewin = CreateWindow ("button", "Test Button",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            0, 400, 400, 60,
            hwnd, (HMENU) 2,
            (HINSTANCE) vtkGetWindowLong (hwnd, vtkGWL_HINSTANCE),
            NULL);
        theVTKApp = new myVTKApp (hwnd);
        return 0;
    }

    case WM_COMMAND:
    {
        switch (wParam)
        {
        case 2:
            PostQuitMessage (0);
            delete theVTKApp;
            theVTKApp = NULL;
            break;
        }
        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage (0);
        delete theVTKApp;
        theVTKApp = NULL;
        return 0;
    }
    }

    return DefWindowProc (hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------

myVTKApp::myVTKApp (HWND hwnd)
{
    this->renderer = vtkRenderer::New ();
    this->renWin = vtkRenderWindow::New ();
    this->renWin->AddRenderer (this->renderer);

    this->renWin->SetParentId (hwnd);
    this->iren = vtkRenderWindowInteractor::New ();
    this->iren->SetRenderWindow (this->renWin);

    this->cone = vtkConeSource::New ();
    this->cone->SetHeight (3.0);
    this->cone->SetRadius (1.0);
    this->cone->SetResolution (10);
    this->coneMapper = vtkPolyDataMapper::New ();
    this->coneMapper->SetInputConnection (this->cone->GetOutputPort ());
    this->coneActor = vtkActor::New ();
    this->coneActor->SetMapper (this->coneMapper);

    this->renderer->AddActor (this->coneActor);
    this->renderer->SetBackground (0.2, 0.4, 0.3);
    this->renWin->SetSize (200, 200);
    this->renWin->SetPosition (100, 50);

    this->renWin->Render ();
}

//-------------------------------------------------------------------------------------------------

myVTKApp::~myVTKApp ()
{
    renWin->Delete ();
    renderer->Delete ();
    iren->Delete ();
    cone->Delete ();
    coneMapper->Delete ();
    coneActor->Delete ();
}

//-------------------------------------------------------------------------------------------------
