// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "atlcrack.h"
#include "AboutDlg.h"
#include "SettingDlg.h"
#include "Config.h"
#include "MainDlg.h"

#define REMIND_GAP  5000
#define SHOWLONG	4000

RECT CMainDlg::m_rectScreen = {0};
BOOL CMainDlg::m_bWindowShow = FALSE;

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return FALSE;
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
 	// register object for message filtering and idle updates
 	CMessageLoop* pLoop = _Module.GetMessageLoop();
 	ATLASSERT(pLoop != NULL);
 	pLoop->AddMessageFilter(this);
 	pLoop->AddIdleHandler(this);

	::GetWindowRect(GetDesktopWindow(), &m_rectScreen);
	m_rectScreen.bottom -=500;
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, this->m_rectScreen.right, this->m_rectScreen.bottom, SWP_SHOWWINDOW);
	
	return FALSE;
}

void CMainDlg::SetupMinitor()
{
	INT gap = CConfig::Instance()->GetIntValue(CK_GapBetweenShow, 30);
	::SetTimer(m_hWnd, TN_Remind, gap*60000, TimerProc );
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CMainDlg::OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMainDlg::OnPosChanged(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WINDOWPOS* wp = (WINDOWPOS*)lParam;

	static BOOL bLastShow = FALSE;
	BOOL bIsShow = IsWindowVisible();
	CStringW strMessage;
	strMessage.Format(L"Carer: OnPosChanged id:%s , bLastShow:%s\n", bIsShow ? L"True" :L"False", bLastShow ? L"True":L"False" );
	OutputDebugString(strMessage);
	static HHOOK hHook = NULL;
	if(bIsShow && !bLastShow){   //show
		INT showLong = CConfig::Instance()->GetIntValue(CK_ShowLong, 30);
		BOOL bRet =::SetTimer(m_hWnd, TN_WindowHide, showLong*1000, TimerProc);
		ATLASSERT(bRet);
		OutputDebugString(L"SetTimer\n");	
		bLastShow = bIsShow;

	}
	else if(!bIsShow && bLastShow){   // hide
		BOOL bRet =::KillTimer(m_hWnd, TN_WindowHide);
		ATLASSERT(bRet);
		OutputDebugString(L"KillTimer\n");		 
		bLastShow = bIsShow;
	}	
	return 0;
}

LRESULT CMainDlg::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//CWindowDC adc(m_hWnd);
	RECT rectWindow={0};
	GetWindowRect(&rectWindow);
	WTL::CMemoryDC adc(GetWindowDC(), rectWindow);	
	RECT rect ={0,0, 100, 100};
	adc.DrawText(L"abc", 4, &rect, 0);	
	bHandled = FALSE;
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch(lParam)
	{
	case WM_RBUTTONDOWN:
		OutputDebugString(L"Rbtn");
		{
			//bHandled = FALSE;
			//return 0;
			SetForegroundWindow(m_hWnd);
			POINT pnt ;
			pnt.x = GET_X_LPARAM(lParam);
			pnt.y = GET_Y_LPARAM(lParam);
			HMENU menuNotify = LoadMenu(_Module.get_m_hInst(), MAKEINTRESOURCE(IDR_MENU1));
			HMENU hMenuPopup = GetSubMenu(menuNotify, 0);
			//::ClientToScreen(uMsg, &pnt);
			GetCursorPos(&pnt);
			INT ret = TrackPopupMenu(hMenuPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON , pnt.x, pnt.y, 0, m_hWnd, NULL);
			OutputDebugString(L"Rbtn\n");
		}		
		break;
	case WM_CONTEXTMENU:
		OutputDebugString(L"OnMenu");
		break;
	}
	return 0;
}

LRESULT CMainDlg::OnMenuAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal(m_hWnd);
	return 0;
}

LRESULT CMainDlg::OnMenuSetting(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSettingDlg dlgSetting;
	dlgSetting.m_Gap = CConfig::Instance()->GetIntValue(CK_GapBetweenShow, 30);	
	dlgSetting.m_ShowLong = CConfig::Instance()->GetIntValue(CK_ShowLong, 30);

	if(IDOK == dlgSetting.DoModal(m_hWnd)){
		CConfig::Instance()->SetIntValue(CK_GapBetweenShow, dlgSetting.m_Gap);
		CConfig::Instance()->SetIntValue(CK_ShowLong, dlgSetting.m_ShowLong);
		SetupMinitor();
	}
	return 0;
}



VOID CALLBACK CMainDlg::TimerProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  UINT_PTR idEvent,
	_In_  DWORD dwTime
	)
{	
	CStringW strMessage;
	strMessage.Format(L"Carer: TimerProc id:%d\n", idEvent);
	OutputDebugString(strMessage);		 
	static UINT_PTR m_TimerID = 0;
 	if (TN_Remind == idEvent)
	{
		::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, m_rectScreen.right, m_rectScreen.bottom, SWP_SHOWWINDOW);
		::SetActiveWindow(hwnd);		
	}
	else if(TN_WindowHide == idEvent)
	{
		::ShowWindow(hwnd, SW_HIDE);
	}
}
