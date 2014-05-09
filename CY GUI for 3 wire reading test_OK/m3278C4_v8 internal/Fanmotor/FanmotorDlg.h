// FanmotorDlg.h : header file
//

#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "AboutDlg.h"
#include "debugDlg.h"
#include "detailDlg.h"
#include "EvaluationDlg.h"
#include "OTPDlg.h"
#include "OTPcalDlg.h"
#include "TestDlg.h"
#include "IntTest.h"

//#include "SpdProfile.h"

extern int comm_port;
extern int sclk_freq;
extern int pwm_freq;
extern int pwm_period;
extern int pwm_dc;
extern int pwm_in;
extern double duty_cycle1;
extern int duty_cycle2;
extern int slave_addr;
extern int success;
extern int pwm_on_mod;
extern int spin_fan;

// CFanmotorDlg dialog
class CFanmotorDlg : public CDialog
{
// Construction
public:
	CFanmotorDlg(CWnd* pParent = NULL);	// standard constructor
//    virtual ~CFanmotorDlg();
// Dialog Data
	enum { IDD = IDD_FANMOTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	CAboutDlg* aboutdlg;
	CdebugDlg* debugdlg;
	CdetailDlg* detaildlg;
	CEvaluationDlg* evaluationdlg;
	COTPDlg* otpdlg;
	COTPcalDlg* otpcaldlg;
	CTestDlg* testdlg;
	CIntTest* inttest;

	//CSpdProfile* spdprofiledlg;

public:
	bool virtual_board;
	int fOTP;
	int virtual_board_reg[256];
	int virtual_board_otp[256];
	void InitVirtualBoard(void);
	int ReadVirtualBoardReg(int, int);
	void WriteVirtualBoardReg(int, int, int);

	int dataread_anybits(int,int,int);
	void dataupdate_anybits(int, int, CString,int);
	CString int2bin(int);
	CString int2bin_anybits(int,int);
		int bin2int(CString);
	int bin2intwl(CString,int);
// Implementation
protected:
	HICON m_hIcon;
    virtual void OnOK();
    virtual void OnCancel();
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	bool GetActiveBridge(CString& BridgeID);
	bool GetActiveDevice(BYTE& DeviceAddress);
	void ErrorMsg(int r); 

public:
	void AddBridgeEvent(BSTR BridgeID);
	void RemoveBridgeEvent(BSTR BridgeID);
public:
	void wreg (int,int);
	void SetPwm(int);
	int rreg (int);

public:
	afx_msg void OnBnClickedButtonStart();
    int ParseString(CStringArray& strArray, CString& str);
public:
	afx_msg void OnBnClickedButtonAbout();
public:
	CEdit m_EDIT_ADDR;
public:
	afx_msg void OnEnChangeEditAddr();
public:
	CString m_EDIT_SCL_FREQ;
public:
	afx_msg void OnBnClickedButton400khz();
public:
	afx_msg void OnBnClickedButton200khz();
public:
	afx_msg void OnBnClickedButton50khz();
public:
	CString m_EDIT_PWM_FREQ;
public:
	afx_msg void OnBnClickedButton10khz();
public:
	afx_msg void OnBnClickedButton25khz();
public:
	afx_msg void OnBnClickedButton70khz();
public:
	afx_msg void OnBnClickedButton8khz();
public:
	afx_msg void OnBnClickedButton80khz();
public:
	CString m_EDIT_PWM_DC;
public:
	afx_msg void OnBnClickedButtonPwmDcUp();
public:
	afx_msg void OnBnClickedButtonPwmDcDown();
public:
	afx_msg void OnBnClickedButtonDebug();

public:
	afx_msg void OnBnClickedButtonDetail();
public:
	CButton m_CHECK_MODE;
public:
	afx_msg void OnBnClickedCheckMode();
public:
	CString m_EDIT_MODE;
public:
	afx_msg void OnBnClickedButtonEvaluation();
public:
	afx_msg void OnBnClickedButtonOtp();
public:
	afx_msg void OnBnClickedButtonOtpcal();
public:
	afx_msg void OnBnClickedButtonTest();
public:
	CButton m_CHECK_I2C;
public:
	afx_msg void OnBnClickedCheckI2c();
public:
	CComboBox m_COMBO_PWMFREQ;
public:
	afx_msg void OnCbnSelchangeComboPwmfreq();
	afx_msg void OnBnClickedButtonPwmDcUpsmall();
	afx_msg void OnBnClickedButtonPwmDcDownsmall();
public:
	afx_msg void linkupbridge();
public:
	afx_msg void linkupdevice();//no use?
public:
	afx_msg void setpowerext();//no use?
public:
	afx_msg void setpower5v();
public:
	afx_msg void setpower3v();
public:
	afx_msg void setpowerPWM(int);
public:
	afx_msg void setspeed400k();
public:
	afx_msg void UpdatePWM1();
public:
	afx_msg void UpdatePWM2();
public:
	afx_msg void setMode();	
public:
	afx_msg void setspeed100k();
public:
	afx_msg void setspeed50k();
public:
	afx_msg void setspeedreserve();

//	CEdit m_EDIT_PWM_DC2;
	afx_msg void OnBnClickedButtonPwmDcUp2();
	afx_msg void OnBnClickedButtonPwmDcDown3();
	afx_msg void OnBnClickedButtonPwmDcUpsmall2();
	afx_msg void OnBnClickedButtonPwmDcDownsmall2();
	CString m_EDIT_PWM_DC2;
	CEdit m_EDIT_UpdatePWM1;
	afx_msg void OnBnClickedButtonUpdatepwm1();

public:
	CString GetFirmwareVersion();

	afx_msg void OnBnClickedButtonIntTest();

public:
	int rFWData (int, int);
	void GetTachoFreq();
	CString m_EDIT_Tacho;
	afx_msg void OnBnClickedButtonTacho();

		int DisplayErrorMessageBox (LPCTSTR, LPCTSTR);
	int DisplayInforMessageBox (LPCTSTR, LPCTSTR);
	int DisplayQueryMessageBox (LPCTSTR, LPCTSTR);
	afx_msg void OnBnClickedButtonFwAdtorque();
	CEdit m_EDIT_test;
	afx_msg void OnBnClickedButtonWtest();
	afx_msg void OnBnClickedButtonRtest();
	CString m_edit_read_test;
	CString m_EDIT_Rtest;
};
