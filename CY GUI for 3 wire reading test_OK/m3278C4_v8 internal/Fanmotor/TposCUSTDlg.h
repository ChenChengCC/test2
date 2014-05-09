#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CTposCUSTDlg dialog

class CTposCUSTDlg : public CDialog
{
	DECLARE_DYNAMIC(CTposCUSTDlg)

public:
	CTposCUSTDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTposCUSTDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TPOS_CUST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	public:
	CWnd* m_pParent;
	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedButtonReadtpos();
	CString m_EDIT_TPOS1;
	CString m_EDIT_TPOS2;
	CString m_EDIT_TPOS3;
	CString m_EDIT_TPOS4;
	CString m_EDIT_TPOS5;
	CString m_EDIT_TPOS6;
	CString m_EDIT_TPOS_DELTA;
	CString m_EDIT_TPOS1_star;
	CString m_EDIT_TPOS2_star;
	CString m_EDIT_TPOS3_star;
	CString m_EDIT_TPOS4_star;
	CString m_EDIT_TPOS5_star;
	CString m_EDIT_TPOS6_star;
	CString m_EDIT_TPOS_ILIMIT_IS;
	CComboBox m_COMBO_TPOS_ILIMIT_IS;
	void DisplayIlimitIs(int );
};
