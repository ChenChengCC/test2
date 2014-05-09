#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CReliabilityDlg dialog

class CReliabilityDlg : public CDialog
{
	DECLARE_DYNAMIC(CReliabilityDlg)

public:
	CReliabilityDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReliabilityDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_RELIABILITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	public:
	CWnd* m_pParent;
	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	int m_RADIO_Mode;
	int m_RADIO_RegLoopMode;
	CButton m_CHECK_SelLowVolt;
	CButton m_CHECK_Sel12Volt;
	CButton m_CHECK_SelHighVolt;
	CEdit m_EDIT_LowVolt;
	CEdit m_EDIT_HighVolt;
	CEdit m_EDIT_CurrLimit;
	CEdit m_EDIT_PSOn;
	CEdit m_EDIT_PSOff;
	CString m_EDIT_PSCnt;
	CString m_EDIT_RegCnt;
	CEdit m_EDIT_RegOff;
	CEdit m_EDIT_RegOn;
	CEdit m_EDIT_TimePeriod;
	CEdit m_EDIT_nLoop;
	int m_RADIO_PWMMode;
	CEdit m_EDIT_PWMOn;
	CEdit m_EDIT_PWMOff;
	CString m_EDIT_PWMCnt;
	afx_msg void OnBnClickedButtonRegReliability();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT StartTimer (int);
	BOOL StopTimer (UINT);
	afx_msg void OnBnClickedButtonPsReliability();
	void RegReliability (void);
	void PSReliability (void);
	void PWMReliability (void);
	afx_msg void OnBnClickedRadioRegmode();
	afx_msg void OnBnClickedRadioPsmode();
	afx_msg void OnBnClickedRadioPwminlowmode();
	int m_RADIO_PSLoopMode;
	int m_RADIO_PWMLoopMode;
	CEdit m_EDIT_PSnLoop;
	CEdit m_EDIT_PSTimePeriod;
	CEdit m_EDIT_PWMnLoop;
	CEdit m_EDIT_PWMTimePeriod;
	afx_msg void OnBnClickedButtonPwmReliability();
	
	afx_msg void OnBnClickedRadioRegloop();
	afx_msg void OnBnClickedRadioRegtime();
	afx_msg void OnBnClickedRadioPsloop();
	afx_msg void OnBnClickedRadioPstime();
	afx_msg void OnBnClickedRadioPwmloop();
	afx_msg void OnBnClickedRadioPwmtime();
	afx_msg void OnBnClickedRadioPwmcy();
	afx_msg void OnBnClickedRadioPwmfg();
};
