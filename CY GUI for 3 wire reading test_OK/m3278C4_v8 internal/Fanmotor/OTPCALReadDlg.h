#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// COTPCALReadDlg dialog

class COTPCALReadDlg : public CDialog
{
	DECLARE_DYNAMIC(COTPCALReadDlg)

public:
	COTPCALReadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COTPCALReadDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OTPCAL_RD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
//	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	public:
	CWnd* m_pParent;
	CString m_EDIT_OSCTCTEST;
	CString m_EDIT_OSCOFFTEST;
	CString m_EDIT_PINSELTEST;
	CString m_EDIT_PWM_LOWTEST;
	CString m_EDIT_PWM_FLOATTEST;
	CString m_EDIT_PWMFREQTEST;
	CString m_EDIT_CHROMSELTEST;
	CString m_EDIT_RETRY_TIMETEST;
	CButton m_CHECK_SWAPBC;
	CButton m_CHECK_DLLOTP;
	CButton m_CHECK_FFOTP;
	CButton m_CHECK_PMCOTP;
	CButton m_CHECK_SKIP_S2;
	CButton m_CHECK_VARDACOTP;
	CButton m_CHECK_RETRY_ILIM_BRKOTP;
	CButton m_CHECK_RETRY_TRISTATEOTP;
	CButton m_CHECK_PWMFLOATDIS;
	CButton m_CHECK_HP_ALARM_DIS;
	CButton m_CHECK_TRIPHASEOTP;
	CButton m_CHECK_OTP_CRC_CHK_DIS;
	CButton m_CHECK_PWMOVROTP;
	CButton m_CHECK_OFFBRKOTP;
	CButton m_CHECK_OTPCALDONE_Test;
	afx_msg void OnBnClickedButtonReadotpcal();
};
