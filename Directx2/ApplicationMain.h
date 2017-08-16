#pragma once

#include "stdafx.h"
#include "Directx2.h"

/* Base WIN Application class. TODO: make application window icon and other resources modular parameterizing them. 
(Add fields to save them and set them in MyRegisterClass). */
class ApplicationMain
{
public:
	/* Initiallize instance, loads global strings and register window class. */
	ApplicationMain(HINSTANCE hInstance, const unsigned long _IDSAppTittle, const unsigned long _IDCApp);
	~ApplicationMain(void);
	
	bool InitWindow(int nCmdShow);
	INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	/* Base window procedure, only handle base messages WM_COMMAND and WM_DESTROY. */ 
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual int Run();
protected:
	/* Register window class, internally called in application constructor. */
	ATOM MyRegisterClass();
	/* Empty method, should be overrided. */
	virtual void Render();

	HWND hAppMainWindow;							// Application window
	HINSTANCE hInst;
	TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
	TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
	HACCEL hAccelTable;
};

