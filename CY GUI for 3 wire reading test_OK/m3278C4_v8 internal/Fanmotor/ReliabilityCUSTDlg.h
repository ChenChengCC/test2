#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CReliabilityCUSTDlg dialog

class CReliabilityCUSTDlg : public CDialog
{
	DECLARE_DYNAMIC(CReliabilityCUSTDlg)

public:
	CReliabilityCUSTDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReliabilityCUSTDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_RELIABILITY_CUST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	public:
	CWnd* m_pParent;
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	int m_RADIO_RegLoopMode;
	CEdit m_EDIT_nLoop;
	CEdit m_EDIT_TimePeriod;
	CEdit m_EDIT_RegOn;
	CEdit m_EDIT_RegOff;
	CString m_EDIT_RegCnt;
	afx_msg void OnBnClickedButtonRegReliability();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT StartTimer (int);
	BOOL StopTimer (UINT);
	afx_msg void OnBnClickedRadioRegloop();
	afx_msg void OnBnClickedRadioRegtime();
};
