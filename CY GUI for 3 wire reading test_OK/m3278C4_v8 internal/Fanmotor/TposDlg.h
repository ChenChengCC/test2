#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CTposDlg dialog

class CTposDlg : public CDialog
{
	DECLARE_DYNAMIC(CTposDlg)

public:
	CTposDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTposDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TPOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CWnd* m_pParent;
	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
//	CEdit m_EDIT_TPOS1;
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
	afx_msg void OnBnClickedButtonReadtpos();
//	CString m_EDIT_TPOS_ILIMIT_IS;
//	CComboBox m_COMBO_TPOS_ILIMIT_IS;
	void DisplayIlimitIs(int);
//	CString m_COMBO_TPOS_ILIMIT_IS1;
//	CString m_EDIT_TPOS_ILIMIT_IS1;
	CString m_EDIT_TPOS_ILIMIT_IS1;
	afx_msg void OnBnClickedButtonScommTpos();
};
