// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//typedef CWinTraits<WS_OVERLAPPED , WS_EX_APPWINDOW | WS_EX_WINDOWEDGE>		CTopWindowTraits;
typedef CWinTraits<WS_POPUP , WS_EX_TOPMOST>		CTopWindowTraits;


enum TIMERNO{
	TN_Remind,    // timer used to remind 
	TN_WindowHide // timer used to hide reminded window
};

class CMainDlg : public CWindowImpl<CMainDlg, CWindow, CTopWindowTraits>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnPosChanged)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		//MESSAGE_HANDLER(WM_CONTEXTMENU, OnMenu)
		MESSAGE_HANDLER(4035, OnMenu)
		//MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		COMMAND_ID_HANDLER(ID_NOFIY_About, OnMenuAbout)
		COMMAND_ID_HANDLER(ID_NOFIY_Setting, OnMenuSetting)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void CloseDialog(int nVal);

	LRESULT OnMenuAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnMenuSetting(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void SetupMinitor();

private:
	static BOOL m_bWindowShow;
	static RECT m_rectScreen;
	VOID static CALLBACK TimerProc(
		_In_  HWND hwnd,
		_In_  UINT uMsg,
		_In_  UINT_PTR idEvent,
		_In_  DWORD dwTime
		);
	UINT_PTR m_TimerID;
};
