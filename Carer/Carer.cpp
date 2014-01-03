// Carer.cpp : main source file for Carer.exe
//

#include "stdafx.h"

#include "resource.h"

#include "MainDlg.h"
#include "strSafe.h"
#include "shellapi.h"
#include "Config.h"

CAppModule _Module;


void SetupNotify(HWND hwnd){
	NOTIFYICONDATA nid = {};
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Test application");
	nid.uCallbackMessage = 4035;
	nid.hIcon = LoadIcon(_Module.get_m_hInst(), MAKEINTRESOURCE(IDR_MAINFRAME));
	// Show the notification.
	Shell_NotifyIcon(NIM_ADD, &nid);
}

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain;

	RECT rect = {0, 0, 100, 200};

	

	if(dlgMain.Create(NULL, rect, NULL, WS_POPUP) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}

	SetupNotify(dlgMain);

	
	//dlgMain.ShowWindow(nCmdShow);
	dlgMain.ShowWindow(SW_HIDE);
	//CConfig::Instance()->SetIntValue(CK_GapBetweenShow, 50);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
