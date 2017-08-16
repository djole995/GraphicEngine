#include "StdAfx.h"
#include "ApplicationMain.h"

ApplicationMain* appPointer;              //Global pointer to application

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return appPointer->MsgProc(hWnd, message, wParam, lParam);
}

INT_PTR CALLBACK AboutProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return appPointer->About(hWnd, message, wParam, lParam);
}

ApplicationMain::ApplicationMain(HINSTANCE hInstance, const unsigned long _IDSAppTittle, const unsigned long _IDCApp)
{
	appPointer = this;
	hInst = hInstance;
	LoadString(hInst, _IDSAppTittle, szTitle, MAX_LOADSTRING);
	LoadString(hInst, _IDCApp, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass();
}


ApplicationMain::~ApplicationMain(void)
{
}

//  Saves instance handle and creates main window. 
bool ApplicationMain::InitWindow(int nCmdShow)
{
 //  hInst = hInstance; // Store instance handle in our global variable

   hAppMainWindow = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);

   if (!hAppMainWindow)
   {
      return FALSE;
   }

   ShowWindow(hAppMainWindow, nCmdShow);
   UpdateWindow(hAppMainWindow);

   return TRUE;
}

// Registers the window class.
ATOM ApplicationMain::MyRegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_DIRECTX2));
	wcex.hCursor		= LoadCursor(NULL, IDC_CROSS);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DIRECTX2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

// Processes messages for the main window.
LRESULT CALLBACK ApplicationMain::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK ApplicationMain::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

int ApplicationMain::Run() 
{
	MSG msg = {0};

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}
	
	return (int)msg.wParam;
}

void ApplicationMain::Render() 
{

}