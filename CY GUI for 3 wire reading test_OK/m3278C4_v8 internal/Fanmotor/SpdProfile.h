#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CSpdProfile dialog

class CSpdProfile : public CDialogEx
{
	DECLARE_DYNAMIC(CSpdProfile)

public:
	CSpdProfile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSpdProfile();

// Dialog Data
	enum { IDD = IDD_DIALOG_SPD_PROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	CWnd* m_pParent;
	int m_RADIO_Inc_Dec;
	CEdit m_EDIT_Step;
	CEdit m_EDIT_SettleTime;
	afx_msg void OnBnClickedButtonMeasure();
	afx_msg void OnBnClickedRadioInc();
	afx_msg void OnBnClickedRadioDec();
	CEdit m_EDIT_MaxDac;
	CButton m_CHECK_Tacho;
	CButton m_CHECK_FinalDac;
	CButton m_CHECK_Current;
	afx_msg void OnBnClickedCheckTacho();
	afx_msg void OnBnClickedCheckFinaldac();
	afx_msg void OnBnClickedCheckCurrent();
	int m_PWM_SEL_MODE;
	afx_msg void OnBnClickedRadioPwmReg();
	afx_msg void OnBnClickedRadioPwmIn();
	CEdit m_EDIT_MinDac;
	CButton m_CHECK_Dac;
	CButton m_CHECK_DAC_B2B;
	CButton m_CHECK_FinalDac_B2B;

	UINT StartTimer (int);
	BOOL StopTimer (UINT);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckDacB2b();
	afx_msg void OnBnClickedRadioPwmFuncgen();
	CButton m_CHECK_Volt;
	void PWMFGMeasure();
	void PWMRegMeasure();
	void PWMInMeasure();
	CButton m_CHECK_StopFan;
};
