#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CSpdRamp dialog

class CSpdRamp : public CDialog
{
	DECLARE_DYNAMIC(CSpdRamp)

public:
	CSpdRamp(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSpdRamp();

// Dialog Data
	enum { IDD = IDD_DIALOG_SP_RAMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	public:
	CWnd* m_pParent;

	afx_msg void OnClose();
//	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	CEdit m_EDIT_MaxDac;
	CEdit m_EDIT_MinDac;
	CButton m_CHECK_Fault;
	int m_RADIO_Mode;
	CEdit m_EDIT_LoopN;
	CEdit m_EDIT_Ts;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedRadioInc();
	afx_msg void OnBnClickedRadioDec();
	afx_msg void OnBnClickedRadioLoop();
	int m_RADIO_PWM_Mode;

	void PWMFGMeasure();
	void PWMRegMeasure();
	void PWMInMeasure();

	BOOL CheckFault();

	afx_msg void OnBnClickedRadioPwmReg();
	afx_msg void OnBnClickedRadioPwmIn();
	afx_msg void OnBnClickedRadioPwmFuncgen();
	CButton m_CHECK_StopFan;
	CEdit m_EDIT_TorCoarseA;
	CEdit m_EDIT_TorCoarseB;
	CEdit m_EDIT_TorCoarseC;
	CEdit m_EDIT_TorCoarseD;
	CEdit m_EDIT_TorCoarseE;
	CEdit m_EDIT_TorCoarseF;
	CEdit m_EDIT_TorCoarseG;
	CEdit m_EDIT_TorCoarseH;
	CEdit m_EDIT_TorFineA;
	CEdit m_EDIT_TorFineB;
	CEdit m_EDIT_TorFineC;
	CEdit m_EDIT_TorFineD;
	CEdit m_EDIT_TorFineE;
	CEdit m_EDIT_TorFineF;
	CEdit m_EDIT_TorFineG;
	CEdit m_EDIT_TorFineH;
	CButton m_CHECK_FWAdTor;
	BOOL GetAdTorInput();
//	BOOL m_CHECK_OTP1Done;
	CButton m_CHECK_OTP1Done;
	afx_msg void OnBnClickedCheckFwadtor();
	void UseFWAdTorque(int);
};
