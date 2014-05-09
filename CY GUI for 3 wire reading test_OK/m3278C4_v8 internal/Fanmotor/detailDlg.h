#pragma once
#include "afxwin.h"


// CdetailDlg dialog

class CdetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CdetailDlg)

public:
	CdetailDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CdetailDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DETAIL };

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

	bool datarangecheck8bits(int);
	bool datarangecheck4bits(int);
	bool datarangecheck6bits(int);
	bool datarangecheck12bits(int);
	bool datarangecheck5bits(int);
	bool datarangecheck16bits(int);
public:
	void readall();
	void updatepole();
	void updatedelay();
	void updateonmskacc();
	void torque_update();
	void writespeeddac();
    void updatesdisrupt();
public:
	CButton m_CHECK_FAN_EN;
public:
	afx_msg void OnBnClickedCheckFanEn();
public:
	CButton m_CHECK_SYN_CLAMP;
public:
	afx_msg void OnBnClickedCheckSynClamp();
public:
	CButton m_CHECK_VPWR_CLAMP;
public:
	afx_msg void OnBnClickedCheckVpwrClamp();
public:
	CButton m_CHECK_POS_SNS;
public:
	afx_msg void OnBnClickedCheckPosSns();
public:
	CButton m_CHECK_PMC_EN;
public:
	afx_msg void OnBnClickedCheckPmcEn();
public:
	CButton m_CHECK_FAULT_SHUT;
public:
	afx_msg void OnBnClickedCheckFaultShut();
public:
	CButton m_CHECK_COM_SEL;
public:
	afx_msg void OnBnClickedCheckComSel();
public:
	CButton m_CHECK_6S_SIN;
public:
	afx_msg void OnBnClickedCheck6sSin();
public:
	CButton m_CHECK_TRISTATE;
public:
	afx_msg void OnBnClickedCheckTristate();
public:
	CButton m_CHECK_3PH_DET;
public:
	afx_msg void OnBnClickedCheck3phDet();
public:
	CButton m_CHECK_BEMF_FLT;
public:
	afx_msg void OnBnClickedCheckBemfFlt();
public:
	CButton m_CHECK_SP_PWR;
public:
	afx_msg void OnBnClickedCheckSpPwr();
public:
	CButton m_CHECK_VAR_DAC;
public:
	afx_msg void OnBnClickedCheckVarDac();
public:
	CButton m_CHECK_BLIND_SPNACCEL;
public:
	afx_msg void OnBnClickedCheckBlindSpnaccel();
public:
	CButton m_CHECK_FP_EN;
public:
	afx_msg void OnBnClickedCheckFpEn();
public:
	CButton m_CHECK_PWM_FREQDIV;
public:
	CButton m_CHECK_OFFMSK_EN;
public:
	afx_msg void OnBnClickedCheckOffmskEn();
public:
	CButton m_CHECK_TC_EXT;
public:
	afx_msg void OnBnClickedCheckTcExt();
public:
	CButton m_CHECK_TSHUT_DIS;
public:
	afx_msg void OnBnClickedCheckTshutDis();
public:
	CComboBox m_COMBO_REG_OVERWR;
public:
	afx_msg void OnCbnSelchangeComboRegOverwr();
public:
	CComboBox m_COMBO_SCOMM;
public:
	afx_msg void OnCbnSelchangeComboScomm();
//public:
//	CComboBox m_COMBO_ISBLIND_EN;
//public:
//	afx_msg void OnCbnSelchangeComboIsblindEn();
public:
	CComboBox m_COMBO_TACHO;
public:
	afx_msg void OnCbnSelchangeComboTacho();
public:
	CComboBox m_COMBO_S0S3_RPM;
public:
	afx_msg void OnCbnSelchangeComboS0s3Rpm();
public:
	CComboBox m_COMBO_TFREEZE;
public:
	afx_msg void OnCbnSelchangeComboTfreeze();
public:
	CComboBox m_COMBO_COMM_MASK;
public:
	afx_msg void OnCbnSelchangeComboCommMask();
public:
	CComboBox m_COMBO_TORQUE_COARSE;
public:
	afx_msg void OnCbnSelchangeComboTorqueCoarse();
public:
	CComboBox m_COMBO_TORQUE_FINE;
public:
	afx_msg void OnCbnSelchangeComboTorqueFine();
public:
	CComboBox m_COMBO_FREEZE_HYS;
public:
	afx_msg void OnCbnSelchangeComboFreezeHys();
public:
	CComboBox m_COMBO_BEMF_HYS;
public:
	afx_msg void OnCbnSelchangeComboBemfHys();
public:
	CComboBox m_COMBO_ILIMIT;
public:
	afx_msg void OnCbnSelchangeComboIlimit();
public:
	CComboBox m_COMBO_ILIMIT_AUTO;
public:
	afx_msg void OnCbnSelchangeComboIlimitAuto();
public:
	CComboBox m_COMBO_OFF_MASK;
public:
	afx_msg void OnCbnSelchangeComboOffMask();
public:
	CComboBox m_COMBO_ON_MASK;
public:
	afx_msg void OnCbnSelchangeComboOnMask();
public:
	CComboBox m_COMBO_S1_ISDELAY;
public:
	afx_msg void OnCbnSelchangeComboS1Isdelay();
public:
	afx_msg void OnCbnSelchangeComboBlindspnCount();
public:
	CComboBox m_COMBO_BLINDSPN_STEP;
public:
	afx_msg void OnCbnSelchangeComboBlindspnStep();
public:
	CComboBox m_COMBO_BLINDSPN_COUNT;
public:
	CComboBox m_COMBO_TS_IS;
public:
	afx_msg void OnCbnSelchangeComboTsIs();
public:
	CComboBox m_COMBO_TO_S3;
public:
	afx_msg void OnCbnSelchangeComboToS3();
public:
	CComboBox m_COMBO_TS_INIT;
public:
	afx_msg void OnCbnSelchangeComboTsInit();
public:
	CComboBox m_COMBO_TS_BLIND;
public:
	afx_msg void OnCbnSelchangeComboTsBlind();
public:
	CComboBox m_COMBO_TS_INITBLIND;
public:
	afx_msg void OnCbnSelchangeComboTsInitblind();
public:
	CComboBox m_COMBO_OSC_OFFSET;
public:
	afx_msg void OnCbnSelchangeComboOscOffset();
public:
	CComboBox m_COMBO_OSC_TC;
public:
	afx_msg void OnCbnSelchangeComboOscTc();
public:
	CComboBox m_COMBO_TESTMUX;
public:
	afx_msg void OnCbnSelchangeComboTestmux();
public:
	CEdit m_EDIT_WIN_MASK;
public:
	afx_msg void OnBnClickedButtonWinMask();
public:
	CEdit m_EDIT_WIN;
public:
	afx_msg void OnBnClickedButtonWin();
public:
	CEdit m_EDIT_LDAC;
public:
	afx_msg void OnBnClickedButtonLdac();
public:
	CEdit m_EDIT_HDAC;
public:
	CString m_EDIT_HDAC_CAL;
public:
	afx_msg void OnBnClickedButtonHdac();
public:
	CEdit m_EDIT_SPDAC_S1;
public:
	afx_msg void OnBnClickedButtonSpdacS1();
public:
	afx_msg void OnBnClickedButtonDacup();
public:
	afx_msg void OnBnClickedButtonDacdown();
public:
	afx_msg void OnBnClickedButtonDacupSmall();
public:
	afx_msg void OnBnClickedButtonDacdownSmall();
public:
	CString m_EDIT_SPIN_DONE;
public:
	CString m_EDIT_SPIN_FLT;
public:
	CString m_EDIT_TSHUT;
public:
	CString m_EDIT_REV;
public:
	afx_msg void OnBnClickedButtonRstatus();
public:
	CString m_EDIT_DAC;
public:
	CComboBox m_COMBO_LOW_DAC;
public:
	afx_msg void OnCbnSelchangeComboLowDac();
public:
	CComboBox m_COMBO_MIN_DAC;
public:
	afx_msg void OnCbnSelchangeComboMinDac();
public:
	afx_msg void OnBnClickedButtonReadDac();
public:
	CEdit m_EDIT_WDAC;
public:
	afx_msg void OnBnClickedButtonWdac();
public:
	afx_msg void OnBnClickedButtonWdacup();
public:
	afx_msg void OnBnClickedButtonWdacdown();
public:
	afx_msg void OnBnClickedButtonWdacupSmall();
public:
	afx_msg void OnBnClickedButtonWdacdownSmall();
public:
	CString m_EDIT_SPDAC;
public:
	afx_msg void OnBnClickedButtonReadTpos();
public:
	CString m_EDIT_TPOS;
public:
	afx_msg void OnBnClickedButtonReadall();
public:
	afx_msg void OnBnClickedButtonStart();
public:
	CComboBox m_COMBO_SDISRUPT_SEL;
public:
	afx_msg void OnCbnSelchangeComboSdisruptSel();
public:
	CComboBox m_COMBO_POLE_PAIR;
public:
	afx_msg void OnCbnSelchangeComboPolePair();
public:
	CString m_EDIT_SP_WINCAL;
public:
	CString m_EDIT_WINMSK_CAL;
public:
	CEdit m_EDIT_WINMSK_AUTO;
public:
	CString m_EDIT_WINMSK_AUTOCAL;
public:
	afx_msg void OnBnClickedButtonWinmskAuto();
public:
	CEdit m_EDIT_SPDAC_S2;
public:
	CString m_EDIT_SPDAC2;
public:
	afx_msg void OnBnClickedButtonSpdacS2();
public:
	afx_msg void OnBnClickedButtonDacup2();
public:
	afx_msg void OnBnClickedButtonDacupSmall2();
public:
	afx_msg void OnBnClickedButtonDacdown2();
public:
	afx_msg void OnBnClickedButtonDacdownSmall2();
public:
	afx_msg void tfreeze_dropdownlist();
public:
	CEdit m_EDIT_SPDAC_S4;
public:
	CString m_EDIT_SPDAC4;
public:
	afx_msg void OnBnClickedButtonSpdacS4();
public:
	afx_msg void OnBnClickedButtonDacup4();
public:
	afx_msg void OnBnClickedButtonDacdown4();
public:
	afx_msg void OnBnClickedButtonDacupSmall4();
public:
	afx_msg void OnBnClickedButtonDacdownSmall4();
public:
	afx_msg void OnBnClickedCheckOsccalMan();
public:
	afx_msg void OnBnClickedCheckOsccalAuto();
public:
	afx_msg void OnBnClickedCheckOscDis();
public:
	CButton m_CHECK_OSCCAL_MAN;
public:
	CButton m_CHECK_OSCCAL_AUTO;
public:
	CButton m_CHECK_OSC_DIS;
public:
	CString m_EDIT_TWARN;
public:
	CString m_EDIT_NO_SYSCLK;
public:
	CString m_EDIT_BC;
public:
	CString m_EDIT_TFREEZE_IN;
public:
	afx_msg void OnBnClickedRadioPwmregSel();
public:
	afx_msg void OnBnClickedRadioPwminSel();
public:
	afx_msg void OnBnClickedRadioExtdacSel();
public:
	CEdit m_EDIT_PHASE_CNT;
public:
	CString m_EDIT_RPHASE_CNT;
public:
	afx_msg void OnBnClickedButtonPhaseCnt();
public:
	CButton m_CHECK_AD_TOR;
public:
	afx_msg void OnBnClickedCheckAdTor();
public:
	CComboBox m_COMBO_TESTMODE_00;
public:
	afx_msg void OnCbnSelchangeComboTestmode00();
public:
	CComboBox m_COMBO_TESTMODE_10;
public:
	afx_msg void OnCbnSelchangeComboTestmode01();
public:
	CComboBox m_COMBO_TESTMODE_101;
public:
	CComboBox m_COMBO_TESTMODE_11;
public:
	afx_msg void OnCbnSelchangeComboTestmode10();
public:
	afx_msg void OnCbnSelchangeComboTestmode11();
public:
	afx_msg void OnBnClickedRadioMode00();
public:
	afx_msg void OnBnClickedRadioMode01();
public:
	afx_msg void OnBnClickedRadioMode10();
public:
	afx_msg void OnBnClickedRadioMode11();
public:
	CComboBox m_COMBO_ILIMIT_BRAKE;
public:
	afx_msg void OnCbnSelchangeComboIlimitBrake();
public:
	afx_msg void OnBnClickedButtonWmskUp();
public:
	afx_msg void OnBnClickedButtonWmskDown();
public:
	afx_msg void OnBnClickedButtonWinUp();
public:
	afx_msg void OnBnClickedButtonWinDown();
public:
	afx_msg void OnBnClickedButtonWinautoDown();
public:
	afx_msg void OnBnClickedButtonMskautoUp();
public:
	afx_msg void OnBnClickedButtonMskautoDown();
public:
	afx_msg void OnBnClickedButtonWinautoUp();
public:
	CComboBox m_COMBO_BBS_RANGE;
public:
	afx_msg void OnCbnSelchangeComboBbsRange();
public:
	void ilimitbrake0();
public:
	void ilimitbrake1();
public:
	void ilimitbrake3();
public:
	CEdit m_EDIT_REFCOUNT;
public:
	CString m_EDIT_REFCOUNTR;
public:
	afx_msg void OnBnClickedButtonRefcount();
public:
	afx_msg void OnBnClickedButtonRefcountup();
public:
	afx_msg void OnBnClickedButtonRefcountdown();
public:
	afx_msg void OnBnClickedButtonRefcountupSmall();
public:
	afx_msg void OnBnClickedButtonRefcountdownSmall();
public:
	CComboBox m_COMBO_MINSP;
public:
	afx_msg void OnCbnSelchangeComboMinsp();
public:
	CButton m_CHECK_SP_CNTL_EN;
public:
	afx_msg void OnBnClickedCheckSpCntlEn();
public:
	afx_msg void OnBnClickedRadioBlindSpinDis();
public:
	afx_msg void OnBnClickedRadioBlindSpinEn();
public:
	CComboBox m_COMBO_SPIN_REV;
public:
	afx_msg void OnCbnSelchangeComboSpinRev();
public:
	CComboBox m_COMBO_SPIN_TIME;
public:
	afx_msg void OnCbnSelchangeComboSpinTime();
public:
	CComboBox m_COMBO_SPIN_STEP;
public:
	afx_msg void OnCbnSelchangeComboSpinStep();
public:
	afx_msg void OnCbnSelchangeComboSpinInit();
public:
	CButton m_CHECK_SPIN_ACC;
public:
	afx_msg void OnBnClickedCheckSpinAcc();
public:
	CComboBox m_COMBO_SPIN_INIT;
public:
	CButton m_CHECK_DIRECT_SPN;
public:
	afx_msg void OnBnClickedCheckDirectSpn();
public:
	CComboBox m_COMBO_LOW;
public:
	afx_msg void OnCbnSelchangeComboLow();
public:
	CComboBox m_COMBO_TACHPIN_SEL;
public:
	afx_msg void OnCbnSelchangeComboTachpinSel();
public:
	void spinrev0();
public:
	void spinrev1();
public:
	void vardaccount();
public:
	CString m_EDIT_PWMIN_FINAL;
public:
	CString m_EDIT_TARGET_SPD;
public:
	CButton m_CHECK_TOR_HYS_DIS;
public:
	afx_msg void OnBnClickedCheckTorHysDis();
public:
	afx_msg void OnBnClickedButtonManualIs();

public:
	afx_msg void OnBnClickedRadioHss();
public:
	afx_msg void OnBnClickedRadioLss();
public:
	CEdit m_EDIT_FBRES;
public:
	CEdit m_EDIT_REFRES;
public:
	CEdit m_EDIT_SENRES;
public:
	CString m_EDIT_SENGAIN;
public:
	afx_msg void OnBnClickedButtonSetIlimit();

public:
	CComboBox m_COMBO_ILIMIT_MAX;
public:
	afx_msg void OnBnClickedCheckClkmonEn();
public:
	afx_msg void OnBnClickedCheckReg2p5fbEn();
public:
	afx_msg void OnBnClickedCheckTshutdis();
public:
	CButton m_CHECK_CLKMON_EN;
public:
	CButton m_CHECK_REG2P5FB_EN;
public:
	CButton m_CHECK_TSHUTDIS;
public:
	CButton m_CHECK_USEREG;
public:
	afx_msg void OnBnClickedCheckUsereg();
public:
	CComboBox m_COMBO_OSCTC;
public:
	afx_msg void OnCbnSelchangeComboOsctc();
public:
	CButton m_CHECK_OTP1DONE;
public:
	CButton m_CHECK_OTPCAL_DONE;
public:
	CEdit m_EDIT_REFSPEED;
public:
	afx_msg void OnBnClickedRadio1pp();
public:
	afx_msg void OnBnClickedRadio4pp();
public:
	afx_msg void OnCbnDropdownComboPolePair();
public:
	afx_msg void OnBnClickedButtonRefspeed();
public:
	CButton m_CHECK_SLOW_RESPONSE;
public:
	afx_msg void OnBnClickedCheckSlowResponse();
public:
	CComboBox m_COMBO_IS_DELAY;
public:
	afx_msg void OnCbnSelchangeComboIsDelay();
public:
	CButton m_CHECK_DLL_EN;
public:
	afx_msg void OnBnClickedCheckDllEn();
public:
	CButton m_CHECK_FF_EN;
public:
	afx_msg void OnBnClickedCheckFfEn();
public:
	CButton m_CHECK_FF_S6_EN;
public:
	afx_msg void OnBnClickedCheckFfS6En();
public:
	CButton m_CHECK_LEVEL_OVERFLOW;
public:
	afx_msg void OnBnClickedCheckLevelOverflow();
public:
	CString m_EDIT_SUMOUT_FF;
public:
	afx_msg void OnBnClickedRadioUseReg();
public:
	afx_msg void OnBnClickedRadioUseOtp1();
public:
	afx_msg void OnBnClickedRadioUseOtp2();
public:
	afx_msg void OnBnClickedRadioUseOtpcal();
public:
	CString m_EDIT_SUMOUT_FF_TEST;

public:
	afx_msg void OnBnClickedButtonReliabilityTest();
public:
	CString m_EDIT_RELY_CNT;
public:
	CEdit m_RELY_ON;
public:
	CEdit m_EDIT_RELY_OFF;
public:
	afx_msg void OnBnClickedRadioHex();
public:
	afx_msg void OnBnClickedRadioPercent();
public:
	afx_msg void OnBnClickedRadioSpdacS1();
public:
	afx_msg void OnBnClickedRadioSpdacS2();
public:
	afx_msg void OnBnClickedRadioSpdacS4();
public:
	afx_msg void OnBnClickedButtonRpmcount();
public:
	CString m_EDIT_RPMCOUNT;
public:
	afx_msg void OnBnClickedButtonRpmlog();
public:
	afx_msg void OnBnClickedButtonSpeedProfile();
public:
	CEdit m_EDIT_MINSP;
public:
	CString m_EDIT_MINSP_PERCENT;
public:
	afx_msg void OnBnClickedButtonMinsp();
public:
	CEdit m_EDIT_PERSEC;
public:
	CEdit m_EDIT_FORSEC;
public:
	CButton m_CHECK_FAN_EN_OFF_BRK;
public:
	afx_msg void OnBnClickedCheckFanEnOffBrk();
public:
	CButton m_CHECK_PWM_FLOAT_DIS;
public:
	afx_msg void OnBnClickedCheckPwmFloatDis();
public:
	CComboBox m_COMBO_PWM_FLOAT_DETAIL;
public:
	CComboBox m_COMBO_PWM_LOW_DETAIL;
public:
	afx_msg void OnCbnSelchangeComboPwmLowDetail();
public:
	afx_msg void OnCbnSelchangeComboPwmFloatDetail();
public:
	CComboBox m_COMBO_HT;
public:
	afx_msg void OnCbnSelchangeComboHt();
public:
	CComboBox m_COMBO_LT;
public:
	CComboBox m_COMBO_MT;
public:
	CEdit m_EDIT_LOW;
public:
	CEdit m_EDIT_MID;
public:
	CString m_EDIT_LOW_PERCENT;
public:
	CString m_EDIT_MID_PERCENT;
public:
	afx_msg void OnCbnSelchangeComboLt();
public:
	afx_msg void OnCbnSelchangeComboMt();
public:
	CEdit m_EDIT_HT;
public:
	CString m_EDIT_HT_PERCENT;
public:
	CEdit m_EDIT_LT;
public:
	CString m_EDIT_LT_PERCENT;
public:
	CEdit m_EDIT_MT1;
public:
	CString m_EDIT_MIT1_PERCENT;
public:
	CEdit m_EDIT_MID2;
public:
	CString m_EDIT_MID2_PERCENT;
public:
	CEdit m_EDIT_MT2;
public:
	CString m_EDIT_MIT2_PERCENT;
public:
	CEdit m_EDIT_INCRE_PERCENT;
public:
	CString m_EDIT_EFFECTIVE_SDISRUPT;
public:
	CComboBox m_COMBO_PWMIN_FS;
public:
	afx_msg void OnCbnSelchangeComboPwminFs();
public:
	CButton m_CHECK_TACHPIN_INV;
public:
	afx_msg void OnBnClickedCheckTachpinInv();
	CButton m_CHECK_RETRY_ILIM_BRK;
	afx_msg void OnBnClickedCheckRetryIlimBrk();
	CButton m_CHECK_RETRY_TRISTATE;
	afx_msg void OnBnClickedCheckRetryTristate();
	//afx_msg void OnEnChangeEditMinsp();
	BOOL StopTimer (UINT);
	UINT StartTimer (int);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_EDIT_TO_S3;
	CEdit m_EDIT_MINDAC_CLAMP;
	afx_msg void OnBnClickedButtonMindacClamp();
	CString m_EDIT_MINDAC_CLAMP_RD;
//	CButton m_CHECK_GAIN_SEL;
//	BOOL m_CHECK_GAIN_SEL;
	CButton m_CHECK_GAIN_SEL;
};
