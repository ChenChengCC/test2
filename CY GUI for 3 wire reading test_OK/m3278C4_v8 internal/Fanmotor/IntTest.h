#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SpdProfile.h"
#include "TposDlg.h"
#include "AdTorqueDlg.h"
#include "OTPCALReadDlg.h"
#include "DacReadback.h"
#include "ReliabilityDlg.h"
#include "SpdRamp.h"
// CIntTest dialog

class CIntTest : public CDialog
{
	DECLARE_DYNAMIC(CIntTest)

public:
	CIntTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIntTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_INT_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
//	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
public:
	CWnd* m_pParent;
	CString m_EDIT_TPOS1;
	CString m_EDIT_TPOS2;
	CString m_EDIT_TPOS3;
	CString m_EDIT_TPOS4;
	CString m_EDIT_TPOS5;
	CString m_EDIT_TPOS6;
	CString m_EDIT_TPOS_DELTA;
	afx_msg void OnBnClickedButtonReadtpos();
	CString m_EDIT_TPOS1_star;
	CString m_EDIT_TPOS2_star;
	CString m_EDIT_TPOS3_star;
//	CString m__EDIT_TPOS4_star;
	CString m_EDIT_TPOS5_star;
	CString m_EDIT_TPOS6_star;
	CString m_EDIT_TPOS4_star;
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
	afx_msg void OnBnClickedButtonReadotpcal();
	CEdit m_EDIT_OSCTCTEST;
	CEdit m_EDIT_OSCOFFTEST;
	CEdit m_EDIT_PINSELTEST;
	CEdit m_EDIT_PWM_LOWTEST;
	CEdit m_EDIT_PWM_FLOATTEST;
	CEdit m_EDIT_PWMFREQTEST;
	CEdit m_EDIT_CHROMSELTEST;
	CEdit m_EDIT_RETRY_TIMETEST;
	CButton m_CHECK_SWAPBC;
	CButton m_CHECK_DLLOTP;
	CButton m_CHECK_FFOTP;
	CButton m_CHECK_PMCOTP;
	CButton m_CHECK_SKIP_S2;
	CButton m_CHECK_VARDACOTP;
	CButton m_CHECK_RETRY_ILIM_BRKOTP;
	CButton m_CHECK_PWMFLOATDIS;
	CButton m_CHECK_HP_ALARM_DIS;
	CButton m_CHECK_TRIPHASEOTP;
	CButton m_CHECK_OTP_CRC_CHK_DIS;
	CButton m_CHECK_PWMOVROTP;
	CButton m_CHECK_OFFBRKOTP;
	CButton m_CHECK_RETRY_TRISTATEOTP;
	CButton m_CHECK_OTPCALDONE_Test;
	afx_msg void OnBnClickedButtonDialogspeedprofile();

public:
	CSpdProfile* spdprofiledlg;
	CTposDlg* tposdlg;
	CAdTorqueDlg* adtorquedlg;
	COTPCALReadDlg* otpcalreaddlg;
	CDacReadback* dacreadbackdlg;
	CReliabilityDlg* reliabilitydlg;
	CSpdRamp* spdrampdlg;
//
	afx_msg void OnBnClickedButtonTpos();
	afx_msg void OnBnClickedButtonAdtorque();
	afx_msg void OnBnClickedButtonOtpcalRead();
	afx_msg void OnBnClickedButtonDacReadback();
	afx_msg void OnBnClickedButtonReliability();
	afx_msg void OnBnClickedButtonSpdramp();
};
