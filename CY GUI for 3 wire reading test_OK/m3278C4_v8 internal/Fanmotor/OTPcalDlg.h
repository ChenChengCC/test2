// COTPcalDlg dialog

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class COTPcalDlg : public CDialog
{
	DECLARE_DYNAMIC(COTPcalDlg)

public:
	COTPcalDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COTPcalDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OTPCAL };

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
	CProgressCtrl m_PROGRESS2;
public:
	CButton m_CHECK_PASSCAL;
public:
	CButton m_CHECK_FAILCAL;
public:
	CButton m_CHECK_OTPCAL_DONE;
public:
	afx_msg void OnBnClickedButtonOtpcal();
public:
	afx_msg void writeotpcalreg();
	afx_msg void readotpcalreg();
	afx_msg void displayfile();
	afx_msg void ClearRegVal();

public:
	afx_msg void OnBnClickedButtonSaveOtpcal();

public:
	CButton m_CHECK_DLLOTP;

public:
	CButton m_CHECK_FFOTP;
public:
	CButton m_CHECK_PMCOTP;
public:
	CButton m_CHECK_TRIPHASEOTP;
public:
	CButton m_CHECK_PWMOVROTP;
public:
	CButton m_CHECK_VARDACOTP;
public:
	CComboBox m_COMBO_OSCTCOTP;
public:
	CComboBox m_COMBO_OSCOFFOTP;
public:
	CComboBox m_COMBO_PINSEL;
public:
	CComboBox m_COMBO_CHROMSEL;
public:
	CButton m_CHECK_OFFBRKOTP;
public:
	afx_msg void OnCbnSelchangeComboOsctcotp();
public:
	afx_msg void OnCbnSelchangeComboOscoffotp();
public:
	afx_msg void OnCbnSelchangeComboChromsel();
public:
	afx_msg void OnCbnSelchangeComboPinsel();
public:
	afx_msg void OnBnClickedCheckFfotp();
public:
	afx_msg void OnBnClickedCheckTriphaseotp();
public:
	afx_msg void OnBnClickedCheckDllotp();
public:
	afx_msg void OnBnClickedCheckPmcotp();
public:
	afx_msg void OnBnClickedCheckPwmovrotp();
public:
	afx_msg void OnBnClickedCheckVardacotp();
public:
	afx_msg void OnBnClickedCheckOffbrkotp();
public:
	CButton m_CHECK_SKIP_S2;
public:
	afx_msg void OnBnClickedCheckSkipS2();
public:
	CComboBox m_COMBO_PWM_LOW;
public:
	afx_msg void OnCbnSelchangeComboPwmLow();
public:
	CComboBox m_COMBO_PWM_FLOAT;
public:
	afx_msg void OnCbnSelchangeComboPwmFloat();
public:
	CButton m_CHECK_PWMFLOATDIS;
public:
	afx_msg void OnBnClickedCheckPwmfloatdis();
public:
	CButton m_CHECK_OTP_CRC_CHK_DIS;
public:
	afx_msg void OnBnClickedCheckOtpCrcChkDis();
public:
	CButton m_CHECK_CLKMONEN;
public:
	afx_msg void OnBnClickedCheckClkmonen();
public:
	afx_msg void OnCbnSelchangeComboPwmfreqOtp();
public:
	CComboBox m_COMBO_PWMFREQ_OTP;
public:
	CComboBox m_COMBO_PG_THRESH;
public:
	afx_msg void OnCbnSelchangeComboPgThresh();
public:
	CComboBox m_COMBO_NG_THRESH;
public:
	afx_msg void OnCbnSelchangeComboNgThresh();
public:
	CButton m_CHECK_DUAL_PROFILE_EN;
public:
	afx_msg void OnBnClickedCheckDualProfileEn();
public:
	CButton m_CHECK_TRIPLE_PROFILE_EN;
public:
	afx_msg void OnBnClickedCheckTripleProfileEn();
public:
	CButton m_CHECK_HP_ALARM_DIS;
	CComboBox m_COMBO_RETRY_TIMEOTP;
	CButton m_CHECK_RETRY_TRISTATEOTP;
	CButton m_CHECK_RETRY_ILIM_BRKOTP;
//	afx_msg void OnSelchangeComboCheckotpcalfile();
	afx_msg void OnDropdownComboCheckotpcalfile();
	CComboBox m_COMBO_CheckOTPCALFile;
	afx_msg void OnBnClickedButtonCheckotpcalfile();
};
