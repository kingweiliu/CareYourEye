#include "StdAfx.h"
#include "SettingDlg.h"


CSettingDlg::CSettingDlg(void)
{
}

CSettingDlg::~CSettingDlg(void)
{
}

LRESULT CSettingDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());

	m_spinGap.Attach(GetDlgItem(IDC_SPIN_GAP));	
	m_spinGap.SetRange(5, 100);
	m_spinShowLong.Attach(GetDlgItem(IDC_SPIN_SHOWLONG));
	m_spinShowLong.SetRange(2, 60);

	DoDataExchange(FALSE);
	return TRUE;
}
LRESULT CSettingDlg::OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(TRUE);
	EndDialog(wID);
	return TRUE;
}

