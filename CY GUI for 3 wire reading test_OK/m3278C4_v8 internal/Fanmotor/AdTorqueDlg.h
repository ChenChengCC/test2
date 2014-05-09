#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CAdTorqueDlg dialog

class CAdTorqueDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdTorqueDlg)

public:
	CAdTorqueDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdTorqueDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_AD_TORQUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CWnd* m_pParent;
	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	CString m_EDIT_TorCoarseA;
	CString m_EDIT_TorCoarseB;
	CString m_EDIT_TorCoarseC;
	CString m_EDIT_TorCoarseD;
	CString m_EDIT_TorCoarseE;
	CString m_EDIT_TorCoarseF;
	CString m_EDIT_TorCoarseG;
	CString m_EDIT_TorCoarseH;
	CString m_EDIT_TorFineA;
	CString m_EDIT_TorFineB;
	CString m_EDIT_TorFineC;
	CString m_EDIT_TorFineD;
	CString m_EDIT_TorFineE;
	CString m_EDIT_TorFineF;
	CString m_EDIT_TorFineG;
	CString m_EDIT_TorFineH;
	CButton m_CHECK_OTP1DONE_Test;
	afx_msg void OnBnClickedButtonAdtorextract();
};
