#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "TposCUSTDlg.h"
#include "ReliabilityCUSTDlg.h"
#include "FWTOR.h"
// CTestDlg dialog

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
	virtual void OnOK();
    virtual void OnCancel();
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pParent;
public:
	CComboBox m_COMBO_TESTMODE_00;
public:
	afx_msg void OnCbnSelchangeComboTestmode00();
public:
	CComboBox m_COMBO_TESTMODE_10;
public:
	afx_msg void OnCbnSelchangeComboTestmode10();
public:
	CComboBox m_COMBO_TESTMODE_11;
public:
	afx_msg void OnCbnSelchangeComboTestmode11();
public:
	CComboBox m_COMBO_TESTMUX;
public:
	afx_msg void OnCbnSelchangeComboTestmux();
public:
	afx_msg void OnBnClickedCheckTcext();
public:
	afx_msg void OnBnClickedRadioMode00();
public:
	afx_msg void OnBnClickedRadioMode01();
public:
	afx_msg void OnBnClickedRadioMode10();
public:
	afx_msg void OnBnClickedRadioMode11();
public:
	void setcontent_testmode00();
public:
	void setcontent_testmode01();
public:
	void setcontent_testmode10();
public:
	void setcontent_testmode11();
public:
	CButton m_CHECK_TCEXT;

public:
	CComboBox m_COMBO_TESTMODE_101;
public:
	afx_msg void OnCbnSelchangeComboTestmode01();
public:
	CButton m_CHECK_TRISTATE;
public:
	afx_msg void OnBnClickedCheckTristate();
public:
	CButton m_CHECK_BEMF_FILTER_EN;
public:
	afx_msg void OnBnClickedCheckBemfFilterEn();
public:
	CButton m_CHECK_RETRY_DIS;
public:
	afx_msg void OnBnClickedCheckRetryDis();
public:
	CButton m_CHECK_SWAP_BC;
public:
	afx_msg void OnBnClickedCheckSwapBc();
public:
	CButton m_CHECK_TRIPHASE_DET;
public:
	afx_msg void OnBnClickedCheckTriphaseDet();
public:
	CButton m_CHECK_PMC_EN;
public:
	afx_msg void OnBnClickedCheckPmcEn();
public:
	CButton m_CHECK_SYNC_CLAMP;
public:
	afx_msg void OnBnClickedCheckSyncClamp();
public:
	CButton m_CHECK_OSC_DIS;
public:
	afx_msg void OnBnClickedCheckOscDis();
public:
	CComboBox m_COMBO_COMSEL;
public:
	afx_msg void OnCbnSelchangeComboComsel();
public:
	CComboBox m_COMBO_ILIMIT_BRAKE;
public:
	afx_msg void OnCbnSelchangeComboIlimitBrake();
public:
	CString m_EDIT_SPIN_DONE;
public:
	CString m_EDIT_TSHUT;
public:
	CString m_EDIT_TWARN;
public:
	CString m_EDIT_NO_SYSCLK;
public:
	CString m_EDIT_BC;
public:
	afx_msg void OnBnClickedButtonStart();
public:
	afx_msg void OnBnClickedButtonReadall();
public:
	afx_msg void OnBnClickedButtonReadStatus();
public:
	void readall();
public:
	CString m_EDIT_SUMOUT_FFT;
public:
	CEdit m_EDIT_ADC;
public:
	afx_msg void OnBnClickedButtonAdc();
public:
	CComboBox m_COMBO_ILIMIT_BRKMASK;
public:
	afx_msg void OnCbnSelchangeComboIlimitBrkmask();
public:
	afx_msg void OnBnClickedCheckPwmNonovrlap();
public:
	afx_msg void OnBnClickedButtonReadadc();
public:
	CButton m_CHECK_PWM_NONOVRLAP;
public:
	CString m_EDIT_CRC_MATCH;
public:
	CButton m_CHECK_REG_CRC_CHK_DIS;
public:
	CString m_EDIT_REGCRC_CODE;
public:
	CString m_EDIT_OTPCRC_CODE;
public:
	afx_msg void OnBnClickedCheckRegCrcChkDis();
public:
	afx_msg void OnBnClickedCheckClkmonEn();
public:
	CButton m_CHECK_CKJMON_EN;
public:
	CButton m_CHECK_OTP_CRC_CHK_DIS_TEST;
public:
	afx_msg void OnBnClickedCheckOtpCrcChkDisTest();
public:
	CButton m_CHECK_SKIP_S2_TEST;
public:
	afx_msg void OnBnClickedCheckSkipS2Test();
public:
	CComboBox m_COMBO_SNSAMP_TEST;
public:
	afx_msg void OnCbnSelchangeComboSnsampTest();
public:
	CComboBox m_COMBO_PG_THRESH_TEST;
public:
	afx_msg void OnCbnSelchangeComboPgThreshTest();
public:
	CComboBox m_COMBO_NG_THRESH_TEST;
public:
	afx_msg void OnCbnSelchangeComboNgThreshTest();
public:
	afx_msg void OnBnClickedCheckFanEnOffBrkDis();
public:
	CButton m_CHECK_FAN_EN_OFF_BRK_DIS;
public:
	CButton m_CHECK_HP_ALARM_DIS;
public:
	afx_msg void OnBnClickedCheckHpAlarmDis();
	CComboBox m_COMBO_RETRY_TIME;
	afx_msg void OnCbnSelchangeComboRetryTime();
	CButton m_CHECK_PWM_AVG_EN;
	afx_msg void OnBnClickedCheckPwmAvgEn();
	CButton m_CHECK_NEW_STABLE_SPD_EN;
	afx_msg void OnBnClickedCheckNewStableSpdEn();
	afx_msg void OnBnClickedButtonTposTest();

public:
	CTposCUSTDlg* tposCUSTdlg;
	CReliabilityCUSTDlg* reliabilityCUSTdlg;
	CFWTOR* fwtordlg;

	afx_msg void OnBnClickedButtonReliability();
	afx_msg void OnBnClickedButtonFwAdtorque();
};
