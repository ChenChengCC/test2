// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "FanmotorDlg.h"
#include "OTPDlg.h"
#include "debugDlg.h"
#include "detailDlg.h"
#include <string.h>
#include "conio.h"
#include <stdlib.h>
#include <ctype.h>
#include "math.h"
#include "OTPcalDlg.h"
#include "TestDlg.h"

bool input_rangechecktest;

CdebugDlg use_debugdlg_test;
CdetailDlg use_detaildlg_test;
//CFanmotorDlg use_fanmotordlg_test;
// CTestDlg dialog

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_EDIT_SPIN_DONE(_T(""))
	, m_EDIT_TSHUT(_T(""))
	, m_EDIT_TWARN(_T(""))
	, m_EDIT_NO_SYSCLK(_T(""))
	, m_EDIT_BC(_T(""))
	, m_EDIT_SUMOUT_FFT(_T(""))
	, m_EDIT_CRC_MATCH(_T(""))
	, m_EDIT_REGCRC_CODE(_T(""))
	, m_EDIT_OTPCRC_CODE(_T(""))
{
      m_pParent=pParent;
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_00, m_COMBO_TESTMODE_00);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_10, m_COMBO_TESTMODE_10);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_11, m_COMBO_TESTMODE_11);
	DDX_Control(pDX, IDC_COMBO_TESTMUX, m_COMBO_TESTMUX);
	DDX_Control(pDX, IDC_CHECK_TCEXT, m_CHECK_TCEXT);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_01, m_COMBO_TESTMODE_101);
	DDX_Control(pDX, IDC_CHECK_TRISTATE, m_CHECK_TRISTATE);
	DDX_Control(pDX, IDC_CHECK_BEMF_FILTER_EN, m_CHECK_BEMF_FILTER_EN);
	DDX_Control(pDX, IDC_CHECK_RETRY_DIS, m_CHECK_RETRY_DIS);
	DDX_Control(pDX, IDC_CHECK_SWAP_BC, m_CHECK_SWAP_BC);
	DDX_Control(pDX, IDC_CHECK_TRIPHASE_DET, m_CHECK_TRIPHASE_DET);
	DDX_Control(pDX, IDC_CHECK_PMC_EN, m_CHECK_PMC_EN);
	DDX_Control(pDX, IDC_CHECK_SYNC_CLAMP, m_CHECK_SYNC_CLAMP);
	DDX_Control(pDX, IDC_CHECK_OSC_DIS, m_CHECK_OSC_DIS);
	DDX_Control(pDX, IDC_COMBO_COMSEL, m_COMBO_COMSEL);
	DDX_Control(pDX, IDC_COMBO_ILIMIT_BRAKE, m_COMBO_ILIMIT_BRAKE);
	DDX_Text(pDX, IDC_EDIT_SPIN_DONE, m_EDIT_SPIN_DONE);
	DDX_Text(pDX, IDC_EDIT_TSHUT, m_EDIT_TSHUT);
	DDX_Text(pDX, IDC_EDIT_TWARN, m_EDIT_TWARN);
	DDX_Text(pDX, IDC_EDIT_NO_SYSCLK, m_EDIT_NO_SYSCLK);
	DDX_Text(pDX, IDC_EDIT_BC, m_EDIT_BC);
	DDX_Text(pDX, IDC_EDIT_SUMOUT_FFT, m_EDIT_SUMOUT_FFT);
	DDX_Control(pDX, IDC_EDIT_ADC, m_EDIT_ADC);
	DDX_Control(pDX, IDC_COMBO_ILIMIT_BRKMASK, m_COMBO_ILIMIT_BRKMASK);
	DDX_Control(pDX, IDC_CHECK_PWM_NONOVRLAP, m_CHECK_PWM_NONOVRLAP);
	DDX_Text(pDX, IDC_EDIT_CRC_MATCH, m_EDIT_CRC_MATCH);
	DDX_Control(pDX, IDC_CHECK_REG_CRC_CHK_DIS, m_CHECK_REG_CRC_CHK_DIS);
	DDX_Text(pDX, IDC_EDIT_REGCRC_CODE, m_EDIT_REGCRC_CODE);
	DDX_Text(pDX, IDC_EDIT_OTPCRC_CODE, m_EDIT_OTPCRC_CODE);
	DDX_Control(pDX, IDC_CHECK_CLKMON_EN, m_CHECK_CKJMON_EN);
	DDX_Control(pDX, IDC_CHECK_OTP_CRC_CHK_DIS_TEST, m_CHECK_OTP_CRC_CHK_DIS_TEST);
	DDX_Control(pDX, IDC_CHECK_SKIP_S2_TEST, m_CHECK_SKIP_S2_TEST);
	DDX_Control(pDX, IDC_COMBO_SNSAMP_TEST, m_COMBO_SNSAMP_TEST);
	DDX_Control(pDX, IDC_COMBO_PG_THRESH_TEST, m_COMBO_PG_THRESH_TEST);
	DDX_Control(pDX, IDC_COMBO_NG_THRESH_TEST, m_COMBO_NG_THRESH_TEST);
	DDX_Control(pDX, IDC_CHECK_FAN_EN_OFF_BRK_DIS, m_CHECK_FAN_EN_OFF_BRK_DIS);
	DDX_Control(pDX, IDC_CHECK_HP_ALARM_DIS, m_CHECK_HP_ALARM_DIS);
	DDX_Control(pDX, IDC_COMBO_RETRY_TIME, m_COMBO_RETRY_TIME);
	DDX_Control(pDX, IDC_CHECK_PWM_AVG_EN, m_CHECK_PWM_AVG_EN);
	DDX_Control(pDX, IDC_CHECK_NEW_STABLE_SPD_EN, m_CHECK_NEW_STABLE_SPD_EN);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_00, &CTestDlg::OnCbnSelchangeComboTestmode00)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_10, &CTestDlg::OnCbnSelchangeComboTestmode10)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_11, &CTestDlg::OnCbnSelchangeComboTestmode11)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMUX, &CTestDlg::OnCbnSelchangeComboTestmux)
	ON_BN_CLICKED(IDC_CHECK_TCEXT, &CTestDlg::OnBnClickedCheckTcext)
	ON_BN_CLICKED(IDC_RADIO_MODE_00, &CTestDlg::OnBnClickedRadioMode00)
	ON_BN_CLICKED(IDC_RADIO_MODE_01, &CTestDlg::OnBnClickedRadioMode01)
	ON_BN_CLICKED(IDC_RADIO_MODE_10, &CTestDlg::OnBnClickedRadioMode10)
	ON_BN_CLICKED(IDC_RADIO_MODE_11, &CTestDlg::OnBnClickedRadioMode11)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_01, &CTestDlg::OnCbnSelchangeComboTestmode01)
	ON_BN_CLICKED(IDC_CHECK_TRISTATE, &CTestDlg::OnBnClickedCheckTristate)
	ON_BN_CLICKED(IDC_CHECK_BEMF_FILTER_EN, &CTestDlg::OnBnClickedCheckBemfFilterEn)
	ON_BN_CLICKED(IDC_CHECK_RETRY_DIS, &CTestDlg::OnBnClickedCheckRetryDis)
	ON_BN_CLICKED(IDC_CHECK_SWAP_BC, &CTestDlg::OnBnClickedCheckSwapBc)
	ON_BN_CLICKED(IDC_CHECK_TRIPHASE_DET, &CTestDlg::OnBnClickedCheckTriphaseDet)
	ON_BN_CLICKED(IDC_CHECK_PMC_EN, &CTestDlg::OnBnClickedCheckPmcEn)
	ON_BN_CLICKED(IDC_CHECK_SYNC_CLAMP, &CTestDlg::OnBnClickedCheckSyncClamp)
	ON_BN_CLICKED(IDC_CHECK_OSC_DIS, &CTestDlg::OnBnClickedCheckOscDis)
	ON_CBN_SELCHANGE(IDC_COMBO_COMSEL, &CTestDlg::OnCbnSelchangeComboComsel)
	ON_CBN_SELCHANGE(IDC_COMBO_ILIMIT_BRAKE, &CTestDlg::OnCbnSelchangeComboIlimitBrake)
	ON_BN_CLICKED(IDC_BUTTON_START, &CTestDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_READALL, &CTestDlg::OnBnClickedButtonReadall)
	ON_BN_CLICKED(IDC_BUTTON_READ_STATUS, &CTestDlg::OnBnClickedButtonReadStatus)
	ON_BN_CLICKED(IDC_BUTTON_ADC, &CTestDlg::OnBnClickedButtonAdc)
	ON_CBN_SELCHANGE(IDC_COMBO_ILIMIT_BRKMASK, &CTestDlg::OnCbnSelchangeComboIlimitBrkmask)
	ON_BN_CLICKED(IDC_CHECK_PWM_NONOVRLAP, &CTestDlg::OnBnClickedCheckPwmNonovrlap)
	ON_BN_CLICKED(IDC_BUTTON_READADC, &CTestDlg::OnBnClickedButtonReadadc)
	ON_BN_CLICKED(IDC_CHECK_REG_CRC_CHK_DIS, &CTestDlg::OnBnClickedCheckRegCrcChkDis)
	ON_BN_CLICKED(IDC_CHECK_CLKMON_EN, &CTestDlg::OnBnClickedCheckClkmonEn)
	ON_BN_CLICKED(IDC_CHECK_OTP_CRC_CHK_DIS_TEST, &CTestDlg::OnBnClickedCheckOtpCrcChkDisTest)
	ON_BN_CLICKED(IDC_CHECK_SKIP_S2_TEST, &CTestDlg::OnBnClickedCheckSkipS2Test)
	ON_CBN_SELCHANGE(IDC_COMBO_SNSAMP_TEST, &CTestDlg::OnCbnSelchangeComboSnsampTest)
	ON_CBN_SELCHANGE(IDC_COMBO_PG_THRESH_TEST, &CTestDlg::OnCbnSelchangeComboPgThreshTest)
	ON_CBN_SELCHANGE(IDC_COMBO_NG_THRESH_TEST, &CTestDlg::OnCbnSelchangeComboNgThreshTest)
	ON_BN_CLICKED(IDC_CHECK_FAN_EN_OFF_BRK_DIS, &CTestDlg::OnBnClickedCheckFanEnOffBrkDis)
	ON_BN_CLICKED(IDC_CHECK_HP_ALARM_DIS, &CTestDlg::OnBnClickedCheckHpAlarmDis)
	ON_CBN_SELCHANGE(IDC_COMBO_RETRY_TIME, &CTestDlg::OnCbnSelchangeComboRetryTime)
	ON_BN_CLICKED(IDC_CHECK_PWM_AVG_EN, &CTestDlg::OnBnClickedCheckPwmAvgEn)
	ON_BN_CLICKED(IDC_CHECK_NEW_STABLE_SPD_EN, &CTestDlg::OnBnClickedCheckNewStableSpdEn)
	ON_BN_CLICKED(IDC_BUTTON_TPOS_TEST, &CTestDlg::OnBnClickedButtonTposTest)
	ON_BN_CLICKED(IDC_BUTTON_Reliability, &CTestDlg::OnBnClickedButtonReliability)
	ON_BN_CLICKED(IDC_BUTTON_FW_ADTORQUE, &CTestDlg::OnBnClickedButtonFwAdtorque)
END_MESSAGE_MAP()


BOOL CTestDlg::OnInitDialog()
{
	
	int temp;

	CDialog::OnInitDialog();
	//OnBnClickedButtonStart();
	tposCUSTdlg = NULL;
	reliabilityCUSTdlg = NULL;
	fwtordlg = NULL;

	readall();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->testdlg = NULL;
    delete this;
}

void CTestDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void CTestDlg::OnClose() 
{
	DestroyWindow();
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == SC_CLOSE)
    {
        //if user clicked the "X"
        OnClose();   //Close the dialog with IDOK (or IDCANCEL)
        //---end of code you have added   
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}


void CTestDlg::OnOK() 
{
}

void CTestDlg::OnCancel() 
{
}

void CTestDlg::OnCbnSelchangeComboTestmode00()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_00.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CTestDlg::OnCbnSelchangeComboTestmode01()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_101.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CTestDlg::OnCbnSelchangeComboTestmode10()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_10.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}



void CTestDlg::OnCbnSelchangeComboTestmode11()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_11.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CTestDlg::setcontent_testmode00()
{
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
    int seln;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	lt0 = "0h:       ILIMIT_CORE                    VSS                                  VSS";
	lt1 = "1h:       Tristate_LU5                     VSS                                  VSS";
	lt2 = "2h:       WIN_MASK_SEL                 BEMF_DET_INT                    VSS";
	lt3 = "3h:       ADC_COMPOUT                  TFREEZE_TOP                     VSS";
	lt4 = "4h:       sysclk_stop                         VSS                                 VSS";
	lt5 = "5h:       High_low_overflow_top         VSS                                VSS            not buffered";
	lt6 = "6h:       CLK_500K                            VSS                                 VSS            not buffered"; 	
	lt7 = "7h:       SPBRAKE_EN                        VSS                                 VSS            not buffered";
	lt8 = "8h:       Reset_384_clk                  Test_reset_comm                 VSS";
	lt9 = "9h:       BC\                                   TC_TOP                              VSS";
	lt10 = "Ah:       INA                                  ENA                                  VSS";	
	lt11 = "Bh:       INB                                PWM_BLANK                          VSS";
	lt12 = "Ch:       GT70_TM                        LT50_TM                             VSS";
	lt13 = "Dh:       NGA_OFF(ilimit brake)          VSS                                 VSS";
	lt14 = "Eh:       NGA12_ON                          VSS                                 VSS"; 	
	lt15 = "Fh:       PGA12_ON                          VSS                                 VSS";
	
    seln=pParent->dataread_anybits(0x13,3,4);

	//reset all dropdown lists 
	m_COMBO_TESTMODE_00.ResetContent();
	m_COMBO_TESTMODE_101.ResetContent();
	m_COMBO_TESTMODE_10.ResetContent();
	m_COMBO_TESTMODE_11.ResetContent();
	
	//set dropdown list for one
	m_COMBO_TESTMODE_00.InsertString(0, lt0 );
	m_COMBO_TESTMODE_00.InsertString(1, lt1 );
	m_COMBO_TESTMODE_00.InsertString(2, lt2 );
	m_COMBO_TESTMODE_00.InsertString(3, lt3 );
	m_COMBO_TESTMODE_00.InsertString(4, lt4 );
	m_COMBO_TESTMODE_00.InsertString(5, lt5 );
	m_COMBO_TESTMODE_00.InsertString(6, lt6 );
	m_COMBO_TESTMODE_00.InsertString(7, lt7 );
	m_COMBO_TESTMODE_00.InsertString(8, lt8 );
	m_COMBO_TESTMODE_00.InsertString(9, lt9 );
	m_COMBO_TESTMODE_00.InsertString(10, lt10 );
	m_COMBO_TESTMODE_00.InsertString(11, lt11 );
	m_COMBO_TESTMODE_00.InsertString(12, lt12 );
	m_COMBO_TESTMODE_00.InsertString(13, lt13 );
	m_COMBO_TESTMODE_00.InsertString(14, lt14 );
	m_COMBO_TESTMODE_00.InsertString(15, lt15 );
	m_COMBO_TESTMODE_00.SetCurSel(seln);
}

void CTestDlg::setcontent_testmode01()
{
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
    int seln;
	
	lt0 = "0h:      TSHUT                            VSS                            TWARN";
	lt1 = "1h:      scomm[0]                        scomm[2]                      scomm[1]";
	lt2 = "2h:      CLK0(DLL)                       VSS                            CLKN (DLL)                  not buffered";
	lt3 = "3h:      PWMIN_TOP (o/p)             VSS                         Low_overflow_top          not buffered";
	lt4 = "4h:      SPDAC_TEST_4                 stable_speed               SPDAC_TEST_0";
	lt5 = "5h:      SPDAC_TEST_4                 SPIN_STAGE                 SPDAC_TEST_0";
	lt6 = "6h:      SUMOUT_TOP_A                 SAMP                         BEMFO_RAW"; 	
	lt7 = "7h:      TC_384                            WIN_DLY                      WIN_MASK";
	lt8 = "8h:      TC_384                            TC6                           COMM_BLANK";
	lt9 = "9h:      TC_384                            TC6_XOR                      TC_96                       not buffered";
	lt10 = "Ah:      PWM_FLT (o/p)                   VSS                         Float_overflow_top        not buffered"; 	
	lt11 = "Bh:      SUMOUT_FF_SLEW_MAX       SPIN_STAGE               SUMOUT_TOP_A";
	lt12 = "Ch:      SPIN_STAGE                     SPIN_FAULT                 TC_XOR";
	lt13 = "Dh:      NGA_FAST_PU                  VSS                           NGA_SLEWP_B";
	lt14 = "Eh:      PGA_FAST_PD                  VSS                           PGA_SLEWN_B"; 	
	lt15 = "Fh:      NUV12                             VSS                            POR_COUNT";
	 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    seln=pParent->dataread_anybits(0x13,3,4);

	//reset all dropdown lists 
	m_COMBO_TESTMODE_00.ResetContent();
	m_COMBO_TESTMODE_101.ResetContent();
	m_COMBO_TESTMODE_10.ResetContent();
	m_COMBO_TESTMODE_11.ResetContent();
	
	//set dropdown list for one
	m_COMBO_TESTMODE_101.InsertString(0, lt0 );
	m_COMBO_TESTMODE_101.InsertString(1, lt1 );
	m_COMBO_TESTMODE_101.InsertString(2, lt2 );
	m_COMBO_TESTMODE_101.InsertString(3, lt3 );
	m_COMBO_TESTMODE_101.InsertString(4, lt4 );
	m_COMBO_TESTMODE_101.InsertString(5, lt5 );
	m_COMBO_TESTMODE_101.InsertString(6, lt6 );
	m_COMBO_TESTMODE_101.InsertString(7, lt7 );
	m_COMBO_TESTMODE_101.InsertString(8, lt8 );
	m_COMBO_TESTMODE_101.InsertString(9, lt9 );
	m_COMBO_TESTMODE_101.InsertString(10, lt10 );
	m_COMBO_TESTMODE_101.InsertString(11, lt11 );
	m_COMBO_TESTMODE_101.InsertString(12, lt12 );
	m_COMBO_TESTMODE_101.InsertString(13, lt13 );
	m_COMBO_TESTMODE_101.InsertString(14, lt14 );
	m_COMBO_TESTMODE_101.InsertString(15, lt15 );
	m_COMBO_TESTMODE_101.SetCurSel(seln);
}

void CTestDlg::setcontent_testmode10()
{
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
    int seln;
	
	lt0 = "0h:          VSS                       VSS                         VSS";
	lt1 = "1h:          VSS                       VSS                         VSS";
	lt2 = "2h:          VSS                       VSS                         VSS";
	lt3 = "3h:          VSS                       VSS                         VSS";
	lt4 = "4h:          VSS                       VSS                         VSS";
	lt5 = "5h:          VSS                       VSS                         VSS";
	lt6 = "6h:          VSS                       VSS                         VSS";	
	lt7 = "7h:          VSS                       VSS                         VSS";
	lt8 = "8h:          VSS                       VSS                         VSS";
	lt9 = "9h:          VSS                       VSS                         VSS";
	lt10 = "Ah:          VSS                       VSS                         VSS"; 	
	lt11 = "Bh:          VSS                       VSS                         VSS";
	lt12 = "Ch:          VSS                       VSS                         VSS";
	lt13 = "Dh:          VSS                       VSS                         VSS";
	lt14 = "Eh:          VSS                       VSS                         VSS";	
	lt15 = "Fh:          VSS                       VSS                         VSS";
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    seln=pParent->dataread_anybits(0x13,3,4);

	//reset all dropdown lists 
	m_COMBO_TESTMODE_00.ResetContent();
	m_COMBO_TESTMODE_101.ResetContent();
	m_COMBO_TESTMODE_10.ResetContent();
	m_COMBO_TESTMODE_11.ResetContent();
	
	//set dropdown list for one
	m_COMBO_TESTMODE_10.InsertString(0, lt0 );
	m_COMBO_TESTMODE_10.InsertString(1, lt1 );
	m_COMBO_TESTMODE_10.InsertString(2, lt2 );
	m_COMBO_TESTMODE_10.InsertString(3, lt3 );
	m_COMBO_TESTMODE_10.InsertString(4, lt4 );
	m_COMBO_TESTMODE_10.InsertString(5, lt5 );
	m_COMBO_TESTMODE_10.InsertString(6, lt6 );
	m_COMBO_TESTMODE_10.InsertString(7, lt7 );
	m_COMBO_TESTMODE_10.InsertString(8, lt8 );
	m_COMBO_TESTMODE_10.InsertString(9, lt9 );
	m_COMBO_TESTMODE_10.InsertString(10, lt10 );
	m_COMBO_TESTMODE_10.InsertString(11, lt11 );
	m_COMBO_TESTMODE_10.InsertString(12, lt12 );
	m_COMBO_TESTMODE_10.InsertString(13, lt13 );
	m_COMBO_TESTMODE_10.InsertString(14, lt14 );
	m_COMBO_TESTMODE_10.InsertString(15, lt15 );
	m_COMBO_TESTMODE_10.SetCurSel(seln);

}

void CTestDlg::setcontent_testmode11()
{
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
    int seln;
	
	lt0 = "0h:          VSS                       VSS                         VSS";
	lt1 = "1h:          VSS                       VSS                         VSS";
	lt2 = "2h:          VSS                       DAC_OUT                  VSS";
	lt3 = "3h:          VSS                       DAC_REF                  VSS";
	lt4 = "4h:          VSS                       VSS                         VSS";
	lt5 = "5h:          VSS                       VSS                         VSS";
	lt6 = "6h:          VSS                       DAC_OUT                  VSS";	
	lt7 = "7h:          VSS                       DAC_REF                  VSS";
	lt8 = "8h:          VSS                       VSS                         VSS";
	lt9 = "9h:          VSS                       VSS                         VSS";
	lt10 = "Ah:          VSS                       VSS                         VSS";	
	lt11 = "Bh:          VSS                       VSS                         VSS";
	lt12 = "Ch:          VSS                       VSS                         VSS";
	lt13 = "Dh:          VSS                       VSS                         VSS";
	lt14 = "Eh:          VSS                       VSS                         VSS";	
	lt15 = "Fh:          VSS                       VSS                         VSS";
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    seln=pParent->dataread_anybits(0x13,3,4);

	//reset all dropdown lists 
	m_COMBO_TESTMODE_00.ResetContent();
	m_COMBO_TESTMODE_101.ResetContent();
	m_COMBO_TESTMODE_10.ResetContent();
	m_COMBO_TESTMODE_11.ResetContent();
	
	//set dropdown list for one
	m_COMBO_TESTMODE_11.InsertString(0, lt0 );
	m_COMBO_TESTMODE_11.InsertString(1, lt1 );
	m_COMBO_TESTMODE_11.InsertString(2, lt2 );
	m_COMBO_TESTMODE_11.InsertString(3, lt3 );
	m_COMBO_TESTMODE_11.InsertString(4, lt4 );
	m_COMBO_TESTMODE_11.InsertString(5, lt5 );
	m_COMBO_TESTMODE_11.InsertString(6, lt6 );
	m_COMBO_TESTMODE_11.InsertString(7, lt7 );
	m_COMBO_TESTMODE_11.InsertString(8, lt8 );
	m_COMBO_TESTMODE_11.InsertString(9, lt9 );
	m_COMBO_TESTMODE_11.InsertString(10, lt10 );
	m_COMBO_TESTMODE_11.InsertString(11, lt11 );
	m_COMBO_TESTMODE_11.InsertString(12, lt12 );
	m_COMBO_TESTMODE_11.InsertString(13, lt13 );
	m_COMBO_TESTMODE_11.InsertString(14, lt14 );
	m_COMBO_TESTMODE_11.InsertString(15, lt15 );
	m_COMBO_TESTMODE_11.SetCurSel(seln);

}

void CTestDlg::OnCbnSelchangeComboTestmux()
{
	int seln;
	CString datbits1,datbits2;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMUX.GetCurSel();	

	if(seln == 0){
		datbits1 = "0";
		datbits2 = "0";
	}else if(seln == 1){
		datbits1 = "1";
		datbits2 = "0";
	}else if(seln == 2){
		datbits1 = "0";
		datbits2 = "1";
	}else if(seln == 3){
		datbits1 = "1";
		datbits2 = "1";
	}
	pParent->dataupdate_anybits(0x13,7,datbits1,1);//test_en1
	pParent->dataupdate_anybits(0x14,7,datbits2,1);//test_en2
}

void CTestDlg::OnBnClickedCheckTcext()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TCEXT.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x13,0,datbits,1);
}

void CTestDlg::OnBnClickedRadioMode00()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "00";
	pParent->dataupdate_anybits(0x13,1,datbits,2);
	setcontent_testmode00();
}

void CTestDlg::OnBnClickedRadioMode01()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "01";
	pParent->dataupdate_anybits(0x13,1,datbits,2);
	setcontent_testmode01();
}

void CTestDlg::OnBnClickedRadioMode10()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "10";
	pParent->dataupdate_anybits(0x13,1,datbits,2);
	setcontent_testmode10();
}

void CTestDlg::OnBnClickedRadioMode11()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "11";
	pParent->dataupdate_anybits(0x13,1,datbits,2);
	setcontent_testmode11();
}



void CTestDlg::OnBnClickedCheckTristate()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TRISTATE.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,1,datbits,1);
}

void CTestDlg::OnBnClickedCheckBemfFilterEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_BEMF_FILTER_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,2,datbits,1);
}

void CTestDlg::OnBnClickedCheckRetryDis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_RETRY_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,6,datbits,1);
}

void CTestDlg::OnBnClickedCheckSwapBc()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SWAP_BC.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,5,datbits,1);
}

void CTestDlg::OnBnClickedCheckTriphaseDet()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TRIPHASE_DET.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x08,0,datbits,1);
}

void CTestDlg::OnBnClickedCheckPmcEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_PMC_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x08,1,datbits,1);
}

void CTestDlg::OnBnClickedCheckSyncClamp()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SYNC_CLAMP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x05,7,datbits,1);
}

void CTestDlg::OnBnClickedCheckOscDis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_OSC_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x02,3,datbits,1);
}

void CTestDlg::OnCbnSelchangeComboComsel()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_COMSEL.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x01,0,datbits,1);
}

void CTestDlg::OnCbnSelchangeComboIlimitBrake()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_ILIMIT_BRAKE.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x0c,4,datbits,4);
}

void CTestDlg::OnBnClickedButtonStart()
{
	use_debugdlg_test.OnBnClickedButtonStart();
}

void CTestDlg::OnBnClickedButtonReadall()
{
	readall();
}

void CTestDlg::OnBnClickedButtonReadStatus()
{
	int temp_sel,mask,temp_int1,temp_int2,temp_cal,temp_bit,temp_int,temp_bit2,temp_bit3;
	int datr = 0;
	CString datbin,datbit;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	             temp_bit = pParent->dataread_anybits(0x01,3,1);
	             if (!success){goto end;};   

				 temp_bit2 = pParent->dataread_anybits(0x04,0,1);
	             if (!success){goto end;};

				 temp_bit3 = pParent->dataread_anybits(0x03,0,3);
	             if (!success){goto end;};
				 
				 if(temp_bit==0){
						datr = pParent->rreg(0x19);
						if (!success){goto end;};
						datbin = pParent->int2bin_anybits(datr,8);
						 if(datbin[0] == '0'){
	 						  m_EDIT_SPIN_DONE.Format(_T("NO"));
							  UpdateData(FALSE);
						 }else {
							  m_EDIT_SPIN_DONE.Format(_T("YES"));
							  UpdateData(FALSE);
						 }
                        
					    temp_bit2 = pParent->dataread_anybits(0x04,0,1);
	                    if (!success){goto end;};

						if(temp_bit2==1){
								datbits="1";
								pParent->dataupdate_anybits(0x01,3,datbits,1);

								temp_int = pParent->dataread_anybits(0x19,0,8);
								if (!success){goto end;};
								m_EDIT_SUMOUT_FFT.Format(_T("%x"),temp_int);
								UpdateData(FALSE);

								datbits="0";
								pParent->dataupdate_anybits(0x01,3,datbits,1);
						}else{
							if(temp_bit3==0){
                                 datbits="1";
								pParent->dataupdate_anybits(0x01,3,datbits,1);

								temp_int = pParent->dataread_anybits(0x19,0,8);
								if (!success){goto end;};
								m_EDIT_SUMOUT_FFT.Format(_T("%x"),temp_int);
								UpdateData(FALSE);

								datbits="0";
								pParent->dataupdate_anybits(0x01,3,datbits,1);
							}
						}
	     
				 }else if(temp_bit==1){
						
					    temp_int = pParent->dataread_anybits(0x19,0,8);
						if (!success){goto end;};
						m_EDIT_SUMOUT_FFT.Format(_T("%x"),temp_int);
						UpdateData(FALSE);

					    datbits="0";
	                    pParent->dataupdate_anybits(0x01,3,datbits,1);
                        datr = pParent->rreg(0x19);
						if (!success){goto end;};
						datbin = pParent->int2bin_anybits(datr,8);
						if(datbin[0] == '0'){
	 						  m_EDIT_SPIN_DONE.Format(_T("NO"));
							  UpdateData(FALSE);
						 }else {
							  m_EDIT_SPIN_DONE.Format(_T("YES"));
							  UpdateData(FALSE);
						 }
                        datbits="1";
	                    pParent->dataupdate_anybits(0x01,3,datbits,1);
				 }

	            

				 datr = pParent->rreg(0x1a);
	             if (!success){goto end;};
	             datbin = pParent->int2bin_anybits(datr,8);

	             if(datbin[7] == '0'){
	 	              m_EDIT_NO_SYSCLK.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else {
		              m_EDIT_NO_SYSCLK.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
	             if(datbin[6] == '0'){
		              m_EDIT_TSHUT.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TSHUT.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(datbin[5] == '0'){
		              m_EDIT_TWARN.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TWARN.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(datbin[4] == '0'){
		              m_EDIT_BC.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_BC.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				/*  if(datbin[1] == '0'){
		              m_EDIT_CRC_MATCH.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_CRC_MATCH.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  */
            
end:;
}

void CTestDlg::readall()
{
	int regval,mask,angle,temp_int1,temp_int2;
	int	com_sel;
	int	sp_tri;
	int	bemf_fil_en;
	int	swap_bc;
	int	osc_dis;
	int	retry_disable;
	int	syn_clamp_dis;
	int	triphase_det_en;
	int	pmc_en;
	int	ilimit_brake;
	int	test_en1;
	int	tc_ext;
	int	tmux;
	int	mode;
	int test_en;
	int	test_en2;
	int	pos_sns;	
	int	auto_spin_done;
	int	bc;
	int	twarn;
	int	tshut;
	int	no_sysclk;
	int temp_int;
	int ilimit_brk_msk;
	int pwm_nonovrlap;
	int use_reg;
	int otp_cal_done;
	int crc_match;
	int reg_crc_chk_dis;
	int reg_crc_code;
	int otp_crc_code;
	int clkmon;
	int otp_crc_chk_dis=-1;
	int skip_s2=-1;
	int pg_thresh;
	int ng_thresh;
	int snsamp=-1;
	int otp1_done;
	int spin_en;
	int scomm_test;
	int fan_en_off_brk_dis;
	int hp_alarm_dis;
	int retry_time;
	int pwm_avg_en;
	int new_stable_spd_en;

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	CString datbits,temp_string;

    regval = pParent->rreg(0x01);
    if (!success){goto end;};

	mask=1;
	com_sel=(regval>>7)&mask;
	sp_tri=(regval>>6)&mask;
	bemf_fil_en=(regval>>5)&mask;
	pos_sns=(regval>>4)&mask;
	swap_bc=(regval>>2)&mask;
	
	regval = pParent->rreg(0x02);
    if (!success){goto end;};

	mask=1;
	use_reg=(regval>>1)&mask;
	osc_dis=(regval>>4)&mask;

	regval = pParent->rreg(0x03);
    if (!success){goto end;};

	mask=7;
	scomm_test=(regval>>5)&mask;

	regval = pParent->rreg(0x04);
    if (!success){goto end;};

	mask=1;
	spin_en=(regval>>7)&mask;
	retry_disable=(regval>>1)&mask;
	
    regval = pParent->rreg(0x05);
    if (!success){goto end;};

	mask=1;
	syn_clamp_dis=regval&mask;
	mask=7;
	ilimit_brk_msk=(regval>>2)&mask;

	regval = pParent->rreg(0x08);
    if (!success){goto end;};

	mask=1;
	triphase_det_en=(regval>>7)&mask;
	pmc_en=(regval>>6)&mask;

	regval = pParent->rreg(0x0b);
    if (!success){goto end;};

    mask=1;
	pwm_nonovrlap=(regval>>7)&mask;

	regval = pParent->rreg(0x0c);
    if (!success){goto end;};
    mask=15;
	ilimit_brake=regval&mask;
		
	regval = pParent->rreg(0x12);
    if (!success) return;
    mask=1;
	pwm_avg_en = regval>>7;
	new_stable_spd_en = (regval>>6)&mask;

	regval = pParent->rreg(0x13);
    if (!success){goto end;};
	mask=1;
	test_en1=regval&mask;
	tc_ext=(regval>>7)&mask;
	mask=15;
	tmux=(regval>>1)&mask;
	mask=3;
	mode=(regval>>5)&mask;
	
	regval = pParent->rreg(0x14);
    if (!success){goto end;};

	mask=1;
    reg_crc_chk_dis=(regval>>3)&mask;
	fan_en_off_brk_dis=(regval>>4)&mask;

	mask=1;
	test_en2=regval&mask;
		
	test_en = test_en2*2 + test_en1;

	datbits = "1";
	pParent->dataupdate_anybits(0x01,7,datbits,1);
    regval = pParent->rreg(0x18);
    if (!success){goto end;};

	mask=1;
	clkmon=(regval>>6)&mask;
	hp_alarm_dis=(regval>>3)&mask;
	retry_time=regval&mask;


    datbits = "0";
	pParent->dataupdate_anybits(0x01,7,datbits,1);

	if(pos_sns==0){	
		regval = pParent->rreg(0x19);
        if (!success){goto end;};

		mask=1;
		auto_spin_done=(regval>>7)&mask;

		if(spin_en==1){ 
				datbits = "1";
				pParent->dataupdate_anybits(0x01,3,datbits,1);
		        
				temp_int = pParent->dataread_anybits(0x19,0,8);
				if (!success){goto end;};
				m_EDIT_SUMOUT_FFT.Format(_T("%x"),temp_int);
				UpdateData(FALSE);
		        
				pParent->dataupdate_anybits(0x01,7,datbits,1);
		        
				regval = pParent->rreg(0x15);
				if (!success){goto end;};

				mask=1;
				snsamp=(regval>>6)&mask;
				otp_crc_chk_dis=(regval>>5)&mask;
				skip_s2=(regval>>4)&mask;

				datbits = "0";
				pParent->dataupdate_anybits(0x01,7,datbits,1);

				temp_int = pParent->dataread_anybits(0x15,0,8);
				if (!success){goto end;};
				temp_string.Format(_T("%x"),temp_int);
				m_EDIT_ADC.SetWindowText(temp_string);

				pParent->dataupdate_anybits(0x01,3,datbits,1);
		}else{
			if(scomm_test==0){
				datbits = "1";
				pParent->dataupdate_anybits(0x01,3,datbits,1);
		        
				temp_int = pParent->dataread_anybits(0x19,0,8);
				if (!success){goto end;};
				m_EDIT_SUMOUT_FFT.Format(_T("%x"),temp_int);
				UpdateData(FALSE);
		        
				pParent->dataupdate_anybits(0x01,7,datbits,1);
		        
				regval = pParent->rreg(0x15);
				if (!success){goto end;};

				mask=1;
				snsamp=(regval>>6)&mask;
				otp_crc_chk_dis=(regval>>5)&mask;
				skip_s2=(regval>>4)&mask;

				datbits = "0";
				pParent->dataupdate_anybits(0x01,7,datbits,1);

				temp_int = pParent->dataread_anybits(0x15,0,8);
				if (!success){goto end;};
				temp_string.Format(_T("%x"),temp_int);
				m_EDIT_ADC.SetWindowText(temp_string);

				pParent->dataupdate_anybits(0x01,3,datbits,1);
			}
		}

	}else if(pos_sns==1){

		temp_int = pParent->dataread_anybits(0x19,0,8);
		if (!success){goto end;};
		m_EDIT_SUMOUT_FFT.Format(_T("%x"),temp_int);
		UpdateData(FALSE);
        
		datbits = "1";
		pParent->dataupdate_anybits(0x01,7,datbits,1);
        
		regval = pParent->rreg(0x15);
        if (!success){goto end;};

	    mask=1;
		snsamp=(regval>>6)&mask;
        otp_crc_chk_dis=(regval>>5)&mask;
        skip_s2=(regval>>4)&mask;

		datbits = "0";
		pParent->dataupdate_anybits(0x01,7,datbits,1);

		temp_int = pParent->dataread_anybits(0x15,0,8);
		if (!success){goto end;};
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_ADC.SetWindowText(temp_string);
		
		datbits = "0";
		pParent->dataupdate_anybits(0x01,3,datbits,1);

		regval = pParent->rreg(0x19);
        if (!success){goto end;};

		mask=1;
		auto_spin_done=(regval>>7)&mask;

		datbits = "1";
		pParent->dataupdate_anybits(0x01,3,datbits,1);
	}
		
			regval = pParent->rreg(0x1a);
			if (!success){goto end;};

			mask=1;
			crc_match=(regval>>6)&mask;
			otp1_done=(regval>>5)&mask;
			otp_cal_done=(regval>>4)&mask;
			bc=(regval>>3)&mask;
			twarn=(regval>>2)&mask;
			tshut=(regval>>1)&mask;
			no_sysclk=regval&mask;

                if(auto_spin_done == 0){
 						  m_EDIT_SPIN_DONE.Format(_T("NO"));
						  UpdateData(FALSE);
					 }else {
						  m_EDIT_SPIN_DONE.Format(_T("YES"));
						  UpdateData(FALSE);
					 }
         	            

				 if(no_sysclk==0){
	 	              m_EDIT_NO_SYSCLK.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else {
		              m_EDIT_NO_SYSCLK.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
	             if(tshut==0){
		              m_EDIT_TSHUT.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TSHUT.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(twarn==0){
		              m_EDIT_TWARN.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TWARN.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(bc==0){
		              m_EDIT_BC.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_BC.Format(_T("YES"));
	                  UpdateData(FALSE);
	             } 
				 if(crc_match==0){
		              m_EDIT_CRC_MATCH.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_CRC_MATCH.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }

				 regval = pParent->rreg(0x21);
			     if (!success){goto end;};
				 mask=15;
                 otp_crc_code=(regval>>4)&mask;
				 m_EDIT_OTPCRC_CODE.Format(_T("%d"),otp_crc_code);
	             UpdateData(FALSE);
				 reg_crc_code=regval&mask;
				 m_EDIT_REGCRC_CODE.Format(_T("%d"),reg_crc_code);
	             UpdateData(FALSE);

				 regval = pParent->rreg(0x22);
			     if (!success){goto end;};
				 	mask=7;
					pg_thresh=(regval>>3)&mask;
					ng_thresh=regval&mask;

				 if(mode==0){
					 CheckRadioButton(IDC_RADIO_MODE_00,IDC_RADIO_MODE_01,IDC_RADIO_MODE_00);
					 setcontent_testmode00();
				 }else if(mode==1){
					 CheckRadioButton(IDC_RADIO_MODE_00,IDC_RADIO_MODE_01,IDC_RADIO_MODE_01);
		             setcontent_testmode01();		 
				 }else if(mode==2){
					 CheckRadioButton(IDC_RADIO_MODE_00,IDC_RADIO_MODE_01,IDC_RADIO_MODE_10);
				     setcontent_testmode10();
				 }else if(mode==3){
					 CheckRadioButton(IDC_RADIO_MODE_00,IDC_RADIO_MODE_01,IDC_RADIO_MODE_11);
				     setcontent_testmode11();
				 }



    m_CHECK_TRISTATE.SetCheck(sp_tri);
	m_CHECK_BEMF_FILTER_EN.SetCheck(bemf_fil_en);
	m_CHECK_RETRY_DIS.SetCheck(retry_disable);
	m_CHECK_SWAP_BC.SetCheck(swap_bc);
	m_CHECK_TRIPHASE_DET.SetCheck(triphase_det_en);
	m_CHECK_PMC_EN.SetCheck(pmc_en);
	m_CHECK_SYNC_CLAMP.SetCheck(syn_clamp_dis);
	m_CHECK_OSC_DIS.SetCheck(osc_dis);
	m_CHECK_TCEXT.SetCheck(tc_ext);
	m_CHECK_REG_CRC_CHK_DIS.SetCheck(reg_crc_chk_dis);
	m_CHECK_PWM_NONOVRLAP.SetCheck(pwm_nonovrlap);
	m_CHECK_CKJMON_EN.SetCheck(clkmon);
	m_CHECK_OTP_CRC_CHK_DIS_TEST.SetCheck(otp_crc_chk_dis);
	m_CHECK_SKIP_S2_TEST.SetCheck(skip_s2);
	m_CHECK_FAN_EN_OFF_BRK_DIS.SetCheck(fan_en_off_brk_dis);
	m_CHECK_HP_ALARM_DIS.SetCheck(hp_alarm_dis);
	m_CHECK_PWM_AVG_EN.SetCheck(pwm_avg_en);
	m_CHECK_NEW_STABLE_SPD_EN.SetCheck(new_stable_spd_en);

	m_COMBO_COMSEL.SetCurSel(com_sel);
	m_COMBO_ILIMIT_BRAKE.SetCurSel(ilimit_brake);
	m_COMBO_TESTMUX.SetCurSel(test_en);
	m_COMBO_ILIMIT_BRKMASK.SetCurSel(ilimit_brk_msk);
	m_COMBO_SNSAMP_TEST.SetCurSel(snsamp);
	m_COMBO_PG_THRESH_TEST.SetCurSel(pg_thresh);
	m_COMBO_NG_THRESH_TEST.SetCurSel(ng_thresh);
	m_COMBO_RETRY_TIME.SetCurSel(retry_time);

	if(otp_cal_done==1){
				m_CHECK_TRIPHASE_DET.EnableWindow(0);
				m_CHECK_PMC_EN.EnableWindow(0);
				m_CHECK_PWM_NONOVRLAP.EnableWindow(0);
				m_CHECK_CKJMON_EN.EnableWindow(0);
				m_CHECK_OTP_CRC_CHK_DIS_TEST.EnableWindow(0);
				m_CHECK_SKIP_S2_TEST.EnableWindow(0);
				m_COMBO_SNSAMP_TEST.EnableWindow(0);
				m_COMBO_RETRY_TIME.EnableWindow(0);
				
			}else if(otp_cal_done==0){
				m_CHECK_TRIPHASE_DET.EnableWindow(1);
				m_CHECK_PMC_EN.EnableWindow(1);
				m_CHECK_PWM_NONOVRLAP.EnableWindow(1);
				m_CHECK_CKJMON_EN.EnableWindow(1);
				m_CHECK_OTP_CRC_CHK_DIS_TEST.EnableWindow(1);
				m_CHECK_SKIP_S2_TEST.EnableWindow(1);
				m_COMBO_SNSAMP_TEST.EnableWindow(1);
				m_COMBO_RETRY_TIME.EnableWindow(1);
			};

			if(otp1_done==0)
			{
				m_CHECK_RETRY_DIS.EnableWindow(1);
				m_CHECK_SYNC_CLAMP.EnableWindow(1);
				m_COMBO_ILIMIT_BRKMASK.EnableWindow(1);
				m_COMBO_ILIMIT_BRAKE.EnableWindow(1);
				m_COMBO_PG_THRESH_TEST.EnableWindow(1);
				m_COMBO_NG_THRESH_TEST.EnableWindow(1);
				m_CHECK_PWM_AVG_EN.EnableWindow(1);
				m_CHECK_NEW_STABLE_SPD_EN.EnableWindow(1);
				
			}
			else if(otp1_done==1&&use_reg==1)
			{
				m_CHECK_RETRY_DIS.EnableWindow(1);
				m_CHECK_SYNC_CLAMP.EnableWindow(1);
				m_COMBO_ILIMIT_BRKMASK.EnableWindow(1);
				m_COMBO_ILIMIT_BRAKE.EnableWindow(1);
				m_COMBO_PG_THRESH_TEST.EnableWindow(1);
				m_COMBO_NG_THRESH_TEST.EnableWindow(1);
				m_CHECK_PWM_AVG_EN.EnableWindow(1);
				m_CHECK_NEW_STABLE_SPD_EN.EnableWindow(1);

			}
			else if(otp1_done==1&&use_reg==0)
			{
				m_CHECK_RETRY_DIS.EnableWindow(0);
				m_CHECK_SYNC_CLAMP.EnableWindow(0);
				m_COMBO_ILIMIT_BRKMASK.EnableWindow(0);
				m_COMBO_ILIMIT_BRAKE.EnableWindow(0);
				m_COMBO_PG_THRESH_TEST.EnableWindow(0);
				m_COMBO_NG_THRESH_TEST.EnableWindow(0);
				m_CHECK_PWM_AVG_EN.EnableWindow(0);
				m_CHECK_NEW_STABLE_SPD_EN.EnableWindow(0);
			};
end:;
}

void CTestDlg::OnBnClickedButtonAdc()
{
	int dat = 0;
	int length_dat,temp_int,temp_bit,temp_bit2;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_ADC.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_ADC.LineLength();

	//convert input string into integer
	dat = use_debugdlg_test.string2int(dats, length_dat);
	input_rangechecktest = use_detaildlg_test.datarangecheck8bits(dat);
	datbits = pParent->int2bin_anybits(dat,8);

	if( input_rangechecktest = TRUE ){
	pParent->dataupdate_anybits(0x15,0,datbits,8);
	if (!success){goto end;};
	temp_bit = pParent->dataread_anybits(0x01,3,1);
	if (!success){goto end;};
		if(temp_bit==1){
			datbit="0";
            pParent->dataupdate_anybits(0x01,7,datbit,1);
			if (!success){goto end;};
			temp_int = pParent->dataread_anybits(0x15,0,8);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_ADC.SetWindowText(temp_string);
		}else{
              temp_bit2 = pParent->dataread_anybits(0x04,0,1);
	          if (!success){goto end;};

			  if(temp_bit2==0){
					datbit="1";
					pParent->dataupdate_anybits(0x01,3,datbit,1);
					if (!success){goto end;};
					datbit="0";
					pParent->dataupdate_anybits(0x01,7,datbit,1);
					if (!success){goto end;};
					temp_int = pParent->dataread_anybits(0x15,0,8);
					if (!success){goto end;};
					temp_string.Format(_T("%x"),temp_int);
					m_EDIT_ADC.SetWindowText(temp_string);
					datbit="0";
					pParent->dataupdate_anybits(0x01,3,datbit,1);
					if (!success){goto end;};
			  }
		}

	}
  end:;
}

void CTestDlg::OnCbnSelchangeComboIlimitBrkmask()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_ILIMIT_BRKMASK.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x05,3,datbits,3);
}

void CTestDlg::OnBnClickedCheckPwmNonovrlap()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_PWM_NONOVRLAP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x0b,0,datbits,1);
}

void CTestDlg::OnBnClickedButtonReadadc()
{
	int dat = 0;
	int length_dat,temp_int,temp_bit,temp_bit2;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	temp_bit = pParent->dataread_anybits(0x01,3,1);
	if (!success){goto end;};
		if(temp_bit==1){
			datbit="0";
            pParent->dataupdate_anybits(0x01,7,datbit,1);
			if (!success){goto end;};
			temp_int = pParent->dataread_anybits(0x15,0,8);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_ADC.SetWindowText(temp_string);
		}else{
			temp_bit2 = pParent->dataread_anybits(0x04,0,1);
	        if (!success){goto end;};

			if(temp_bit2==0){

					datbit="1";
					pParent->dataupdate_anybits(0x01,3,datbit,1);
					if (!success){goto end;};
					datbit="0";
					pParent->dataupdate_anybits(0x01,7,datbit,1);
					if (!success){goto end;};
					temp_int = pParent->dataread_anybits(0x15,0,8);
					if (!success){goto end;};
					temp_string.Format(_T("%x"),temp_int);
					m_EDIT_ADC.SetWindowText(temp_string);
					datbit="0";
					pParent->dataupdate_anybits(0x01,3,datbit,1);
					if (!success){goto end;};
			}
		}

	

  end:;
}

void CTestDlg::OnBnClickedCheckRegCrcChkDis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_REG_CRC_CHK_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x14,4,datbits,1);
}

void CTestDlg::OnBnClickedCheckClkmonEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_CKJMON_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x18,1,datbits,1);
}

void CTestDlg::OnBnClickedCheckOtpCrcChkDisTest()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_OTP_CRC_CHK_DIS_TEST.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x15,2,datbits,1);
}

void CTestDlg::OnBnClickedCheckSkipS2Test()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SKIP_S2_TEST.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x15,3,datbits,1);
}

void CTestDlg::OnCbnSelchangeComboSnsampTest()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_SNSAMP_TEST.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x15,1,datbits,1);
}

void CTestDlg::OnCbnSelchangeComboPgThreshTest()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PG_THRESH_TEST.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x22,2,datbits,3);
}

void CTestDlg::OnCbnSelchangeComboNgThreshTest()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_NG_THRESH_TEST.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x22,5,datbits,3);
}

void CTestDlg::OnBnClickedCheckFanEnOffBrkDis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_FAN_EN_OFF_BRK_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x14,3,datbits,1);
}

void CTestDlg::OnBnClickedCheckHpAlarmDis()
{
	
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_HP_ALARM_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x18,4,datbits,1);
}


void CTestDlg::OnCbnSelchangeComboRetryTime()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_RETRY_TIME.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x18,7,datbits,1);
}


void CTestDlg::OnBnClickedCheckPwmAvgEn()
{
	// TODO: Add your control notification handler code here
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_PWM_AVG_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x12,0,datbits,1);
}


void CTestDlg::OnBnClickedCheckNewStableSpdEn()
{
	// TODO: Add your control notification handler code here
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_NEW_STABLE_SPD_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x12,1,datbits,1);
}


void CTestDlg::OnBnClickedButtonTposTest()
{
	// TODO: Add your control notification handler code here
	if(tposCUSTdlg)
	{
		tposCUSTdlg->SetForegroundWindow();
	}
	else
	{		
		tposCUSTdlg = new CTposCUSTDlg(this);
		tposCUSTdlg->Create(IDD_DIALOG_TPOS_CUST,GetDesktopWindow());
		tposCUSTdlg->ShowWindow(SW_SHOW);
	}
}


void CTestDlg::OnBnClickedButtonReliability()
{
	// TODO: Add your control notification handler code here
	if(reliabilityCUSTdlg)
	{
		reliabilityCUSTdlg->SetForegroundWindow();
	}
	else
	{		
		reliabilityCUSTdlg = new CReliabilityCUSTDlg(this);
		reliabilityCUSTdlg->Create(IDD_DIALOG_RELIABILITY_CUST,GetDesktopWindow());
		reliabilityCUSTdlg->ShowWindow(SW_SHOW);
	}
}


void CTestDlg::OnBnClickedButtonFwAdtorque()
{
	// TODO: Add your control notification handler code here
	if(fwtordlg)
	{
		fwtordlg->SetForegroundWindow();
	}
	else
	{		
		fwtordlg = new CFWTOR(this);
		fwtordlg->Create(IDD_DIALOG_FW_ADTORQUE,GetDesktopWindow());
		fwtordlg->ShowWindow(SW_SHOW);
	}
}
