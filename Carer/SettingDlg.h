#pragma once

#include "resource.h"
#include "atlddx.h"

class CSettingDlg: public CDialogImpl<CSettingDlg>,
	public CWinDataExchange<CSettingDlg>
{
public:
	enum{IDD=IDD_MAINDLG};

	BEGIN_MSG_MAP(CSettingDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOkCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CSettingDlg)
		DDX_INT(IDC_EDIT_GAP, m_Gap )
		DDX_INT(IDC_EDIT_SHOWLONG, m_ShowLong )
	END_DDX_MAP()

	INT m_Gap;
	INT m_ShowLong;

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}

	CUpDownCtrl m_spinGap, m_spinShowLong;		 
	
	CSettingDlg(void);
	~CSettingDlg(void);
};

