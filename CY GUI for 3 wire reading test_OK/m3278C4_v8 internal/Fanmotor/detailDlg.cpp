// detailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "FanmotorDlg.h"
#include "debugDlg.h"
#include "detailDlg.h"
#include <string.h>
#include "conio.h"
#include <stdlib.h>
#include <ctype.h>
#include "math.h"

//************************Timer Class*********************
int ontime=0,offtime=0, fan_cycle_cnt=0;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  IDT_TIMER  WM_USER + 200 
BOOL Fan_Status=TRUE;//fan on == True, fan off == False
//****************************************************

double ilim0=-1,ilim1=-1,ilim2=-1,ilim3=-1,ilim4=-1,ilim5=-1,ilim6=-1,ilim7=-1,ilim8=-1,ilim9=-1,ilim10=-1,ilim11=-1,ilim12=-1,ilim13=-1,ilim14=-1,ilim15=-1;
int var_dac_en;
int fault_shut_dis;
int ilimit_brake_dis;
int pos_sns;
int pwmin_low_time;
int six_sine;
int sp_tri;
int fan_en;
//int ph_detect;
int ad_tor;
int retry_disable;
int swap_bc;
int pwmin_low_stop;
int max_speed_en;
int syn_clamp_dis;
int pmc_en;
int pwm_reg_sel;
int triphase_det_en;
int pwmin_freq;
int pwm_inv;
int bemf_fil_en;
int sdisrupt;
int scomm;
int winmsk;
int sp_speed;
int sp_win;
int bhys;
int frzhys;
int uv_dis;
int freeze;
int torque_coarse;
int torque_fine;
int rev_torque;
int pwm_msk;
int pole_pair;
int comm_msk;
int offmsk_en;
int ilimit;
int s0s2_rpm;
int comm_msk_acc;
int phase_cnt;
int onmsk_acc;
int ts;
int vardac_count;
int handover_spd;
int pwm_nonoverlap_dis;
int to_s3;
int to_s2;
int to_s1;
int ilimit_auto_is;
int ilimit_brake;
int winmsk_auto;
int driver_non_overlap;
int sp_win_auto;
int spdac_s1;
int pwm_in_select;
int tc_ext;
int spdac_s2;
int spdac_s4;
int pwm_freq_detail;
int osc_offset;
//int osc_cal_man;
//int osc_cal_auto;
int osc_dis;
int test_en2;
int test_en1;
int test_en;
int tmux;
int mode;
int adc;
int offmsk;
int tpos_lsb;
int tpos_msb;
int dac;
int auto_spin_done;
int auto_spin_flt;
int rev;
int tfreeze_in;
int bc;
int twarn;
int tshut;
int no_sysclk;
int ilimit_gain;
int minsp;
int refcount1;
int refcount2;
int refcount;
int sp_cntl_en;
int blind_spin_en;
int spin_rev;
int spin_acc;
int spin_time;
int spin_init;
int spin_step;
int direct_spn;
int low;
int tachpin_sel;
int tor_hys_dis;
int clkmon_en;
int osc_tc;
int use_reg;
int otp1done;
int otpcaldone;
int otp_cal_sel;
int tshutdis;
int reg2p5fb_en;
int slow_response;
int dll_en;
int ff_en;
int pwm_float_dis;
int pwmin_stop_level;
int is_delay;
int fan_en_off_brk;
int pwm_low;
int pwm_float;
int profile_sel;
int ht;
int lt;
int mt;
int mid;
int mindac_clamp;
int hss_cal=1;
int reg_crc_chk_dis;
double fb_res=18.0;
double ref_res=1.1;
double sense_res=3.3;
int fourpp=0;
int hex_percent=0;
int spdac_stage=1;
int mid2;
int mt2;
int mt1;
int pwmin_fs;
int tachpin_inv;
int retry_tristate;
int retry_ilim_brk;
int tachpin;

bool input_rangecheck;

// CdetailDlg dialog
CdebugDlg use_debugdlg_detail;
//CFanmotorDlg use_fanmotordlg_detail;

IMPLEMENT_DYNAMIC(CdetailDlg, CDialog)

CdetailDlg::CdetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdetailDlg::IDD, pParent)
	, m_EDIT_HDAC_CAL(_T(""))
	, m_EDIT_SPIN_DONE(_T(""))
	, m_EDIT_SPIN_FLT(_T(""))
	, m_EDIT_TSHUT(_T(""))
	, m_EDIT_REV(_T(""))
	, m_EDIT_DAC(_T(""))
	, m_EDIT_SPDAC(_T(""))
	, m_EDIT_TPOS(_T(""))
	, m_EDIT_SP_WINCAL(_T(""))
	, m_EDIT_WINMSK_CAL(_T(""))
	, m_EDIT_WINMSK_AUTOCAL(_T(""))
	, m_EDIT_SPDAC2(_T(""))
	, m_EDIT_SPDAC4(_T(""))
	, m_EDIT_TWARN(_T(""))
	, m_EDIT_NO_SYSCLK(_T(""))
	, m_EDIT_BC(_T(""))
	, m_EDIT_TFREEZE_IN(_T(""))
	, m_EDIT_RPHASE_CNT(_T(""))
	, m_EDIT_REFCOUNTR(_T(""))
	, m_EDIT_PWMIN_FINAL(_T(""))
	, m_EDIT_TARGET_SPD(_T(""))
	, m_EDIT_SENGAIN(_T(""))
	, m_EDIT_SUMOUT_FF(_T(""))
	, m_EDIT_SUMOUT_FF_TEST(_T(""))
	, m_EDIT_RELY_CNT(_T(""))
	, m_EDIT_RPMCOUNT(_T(""))
	, m_EDIT_MINSP_PERCENT(_T(""))
	, m_EDIT_LOW_PERCENT(_T(""))
	, m_EDIT_MID_PERCENT(_T(""))
	, m_EDIT_HT_PERCENT(_T(""))
	, m_EDIT_LT_PERCENT(_T(""))
	, m_EDIT_MIT1_PERCENT(_T(""))
	, m_EDIT_MID2_PERCENT(_T(""))
	, m_EDIT_MIT2_PERCENT(_T(""))
	, m_EDIT_EFFECTIVE_SDISRUPT(_T(""))
	, m_EDIT_TO_S3(_T(""))
	, m_EDIT_MINDAC_CLAMP_RD(_T(""))
	//, m_CHECK_GAIN_SEL(FALSE)
{
     m_pParent=pParent;
}

CdetailDlg::~CdetailDlg()
{
}

void CdetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_FAN_EN, m_CHECK_FAN_EN);
	DDX_Control(pDX, IDC_CHECK_SYN_CLAMP, m_CHECK_SYN_CLAMP);
	DDX_Control(pDX, IDC_CHECK_VPWR_CLAMP, m_CHECK_VPWR_CLAMP);
	DDX_Control(pDX, IDC_CHECK_POS_SNS, m_CHECK_POS_SNS);
	DDX_Control(pDX, IDC_CHECK_PMC_EN, m_CHECK_PMC_EN);
	DDX_Control(pDX, IDC_CHECK_FAULT_SHUT, m_CHECK_FAULT_SHUT);
	DDX_Control(pDX, IDC_CHECK_COM_SEL, m_CHECK_COM_SEL);
	DDX_Control(pDX, IDC_CHECK_6S_SIN, m_CHECK_6S_SIN);
	DDX_Control(pDX, IDC_CHECK_TRISTATE, m_CHECK_TRISTATE);
	DDX_Control(pDX, IDC_CHECK_3PH_DET, m_CHECK_3PH_DET);
	DDX_Control(pDX, IDC_CHECK_BEMF_FLT, m_CHECK_BEMF_FLT);
	DDX_Control(pDX, IDC_CHECK_SP_PWR, m_CHECK_SP_PWR);
	DDX_Control(pDX, IDC_CHECK_VAR_DAC, m_CHECK_VAR_DAC);
	DDX_Control(pDX, IDC_CHECK_BLIND_SPNACCEL, m_CHECK_BLIND_SPNACCEL);
	DDX_Control(pDX, IDC_CHECK_FP_EN, m_CHECK_FP_EN);
	DDX_Control(pDX, IDC_CHECK_PWM_FREQDIV, m_CHECK_PWM_FREQDIV);
	DDX_Control(pDX, IDC_CHECK_OFFMSK_EN, m_CHECK_OFFMSK_EN);
	DDX_Control(pDX, IDC_CHECK_TC_EXT, m_CHECK_TC_EXT);
	DDX_Control(pDX, IDC_CHECK_TSHUT_DIS, m_CHECK_TSHUT_DIS);
	DDX_Control(pDX, IDC_COMBO_REG_OVERWR, m_COMBO_REG_OVERWR);
	DDX_Control(pDX, IDC_COMBO_SCOMM, m_COMBO_SCOMM);
	DDX_Control(pDX, IDC_COMBO_TACHO, m_COMBO_TACHO);
	DDX_Control(pDX, IDC_COMBO_S0S3_RPM, m_COMBO_S0S3_RPM);
	DDX_Control(pDX, IDC_COMBO_TFREEZE, m_COMBO_TFREEZE);
	DDX_Control(pDX, IDC_COMBO_COMM_MASK, m_COMBO_COMM_MASK);
	DDX_Control(pDX, IDC_COMBO_TORQUE_COARSE, m_COMBO_TORQUE_COARSE);
	DDX_Control(pDX, IDC_COMBO_TORQUE_FINE, m_COMBO_TORQUE_FINE);
	DDX_Control(pDX, IDC_COMBO_FREEZE_HYS, m_COMBO_FREEZE_HYS);
	DDX_Control(pDX, IDC_COMBO_BEMF_HYS, m_COMBO_BEMF_HYS);
	DDX_Control(pDX, IDC_COMBO_ILIMIT, m_COMBO_ILIMIT);
	DDX_Control(pDX, IDC_COMBO_ILIMIT_AUTO, m_COMBO_ILIMIT_AUTO);
	DDX_Control(pDX, IDC_COMBO_OFF_MASK, m_COMBO_OFF_MASK);
	DDX_Control(pDX, IDC_COMBO_ON_MASK, m_COMBO_ON_MASK);
	DDX_Control(pDX, IDC_COMBO_S1_ISDELAY, m_COMBO_S1_ISDELAY);
	DDX_Control(pDX, IDC_COMBO_BLINDSPN_STEP, m_COMBO_BLINDSPN_STEP);
	DDX_Control(pDX, IDC_COMBO_BLINDSPN_COUNT, m_COMBO_BLINDSPN_COUNT);
	DDX_Control(pDX, IDC_COMBO_TS_IS, m_COMBO_TS_IS);
	DDX_Control(pDX, IDC_COMBO_TO_S3, m_COMBO_TO_S3);
	DDX_Control(pDX, IDC_COMBO_TS_INIT, m_COMBO_TS_INIT);
	DDX_Control(pDX, IDC_COMBO_TS_BLIND, m_COMBO_TS_BLIND);
	DDX_Control(pDX, IDC_COMBO_TS_INITBLIND, m_COMBO_TS_INITBLIND);
	DDX_Control(pDX, IDC_COMBO_OSC_OFFSET, m_COMBO_OSC_OFFSET);
	DDX_Control(pDX, IDC_COMBO_OSC_TC, m_COMBO_OSC_TC);
	DDX_Control(pDX, IDC_COMBO_TESTMUX, m_COMBO_TESTMUX);
	DDX_Control(pDX, IDC_EDIT_WIN_MASK, m_EDIT_WIN_MASK);
	DDX_Control(pDX, IDC_EDIT_WIN, m_EDIT_WIN);
	DDX_Control(pDX, IDC_EDIT_LDAC, m_EDIT_LDAC);
	DDX_Control(pDX, IDC_EDIT_HDAC, m_EDIT_HDAC);
	DDX_Text(pDX, IDC_EDIT_HDAC_CAL, m_EDIT_HDAC_CAL);
	DDX_Control(pDX, IDC_EDIT_SPDAC_S1, m_EDIT_SPDAC_S1);
	DDX_Text(pDX, IDC_EDIT_SPIN_DONE, m_EDIT_SPIN_DONE);
	DDX_Text(pDX, IDC_EDIT_SPIN_FLT, m_EDIT_SPIN_FLT);
	DDX_Text(pDX, IDC_EDIT_TSHUT, m_EDIT_TSHUT);
	DDX_Text(pDX, IDC_EDIT_REV, m_EDIT_REV);
	DDX_Text(pDX, IDC_EDIT_DAC, m_EDIT_DAC);
	DDX_Control(pDX, IDC_COMBO_LOW_DAC, m_COMBO_LOW_DAC);
	DDX_Control(pDX, IDC_COMBO_MIN_DAC, m_COMBO_MIN_DAC);
	DDX_Control(pDX, IDC_EDIT_WDAC, m_EDIT_WDAC);
	DDX_Text(pDX, IDC_EDIT_SPDAC, m_EDIT_SPDAC);
	DDX_Text(pDX, IDC_EDIT_TPOS, m_EDIT_TPOS);
	DDX_Control(pDX, IDC_COMBO_SDISRUPT_SEL, m_COMBO_SDISRUPT_SEL);
	DDX_Control(pDX, IDC_COMBO_POLE_PAIR, m_COMBO_POLE_PAIR);
	DDX_Text(pDX, IDC_EDIT_SP_WINCAL, m_EDIT_SP_WINCAL);
	DDX_Text(pDX, IDC_EDIT_WINMSK_CAL, m_EDIT_WINMSK_CAL);
	DDX_Control(pDX, IDC_EDIT_WINMSK_AUTO, m_EDIT_WINMSK_AUTO);
	DDX_Text(pDX, IDC_EDIT_WINMSK_AUTOCAL, m_EDIT_WINMSK_AUTOCAL);
	DDX_Control(pDX, IDC_EDIT_SPDAC_S2, m_EDIT_SPDAC_S2);
	DDX_Text(pDX, IDC_EDIT_SPDAC2, m_EDIT_SPDAC2);
	DDX_Control(pDX, IDC_EDIT_SPDAC_S4, m_EDIT_SPDAC_S4);
	DDX_Text(pDX, IDC_EDIT_SPDAC4, m_EDIT_SPDAC4);
	DDX_Control(pDX, IDC_CHECK_OSCCAL_MAN, m_CHECK_OSCCAL_MAN);
	DDX_Control(pDX, IDC_CHECK_OSCCAL_AUTO, m_CHECK_OSCCAL_AUTO);
	DDX_Control(pDX, IDC_CHECK_OSC_DIS, m_CHECK_OSC_DIS);
	DDX_Text(pDX, IDC_EDIT_TWARN, m_EDIT_TWARN);
	DDX_Text(pDX, IDC_EDIT_NO_SYSCLK, m_EDIT_NO_SYSCLK);
	DDX_Text(pDX, IDC_EDIT_BC, m_EDIT_BC);
	DDX_Text(pDX, IDC_EDIT_TFREEZE_IN, m_EDIT_TFREEZE_IN);
	DDX_Control(pDX, IDC_EDIT_PHASE_CNT, m_EDIT_PHASE_CNT);
	DDX_Text(pDX, IDC_EDIT_RPHASE_CNT, m_EDIT_RPHASE_CNT);
	DDX_Control(pDX, IDC_CHECK_AD_TOR, m_CHECK_AD_TOR);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_00, m_COMBO_TESTMODE_00);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_01, m_COMBO_TESTMODE_10);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_10, m_COMBO_TESTMODE_101);
	DDX_Control(pDX, IDC_COMBO_TESTMODE_11, m_COMBO_TESTMODE_11);
	DDX_Control(pDX, IDC_COMBO_ILIMIT_BRAKE, m_COMBO_ILIMIT_BRAKE);
	DDX_Control(pDX, IDC_COMBO_BBS_RANGE, m_COMBO_BBS_RANGE);
	DDX_Control(pDX, IDC_EDIT_REFCOUNT, m_EDIT_REFCOUNT);
	DDX_Text(pDX, IDC_EDIT_REFCOUNTR, m_EDIT_REFCOUNTR);
	DDX_Control(pDX, IDC_COMBO_MINSP, m_COMBO_MINSP);
	DDX_Control(pDX, IDC_CHECK_SP_CNTL_EN, m_CHECK_SP_CNTL_EN);
	DDX_Control(pDX, IDC_COMBO_SPIN_REV, m_COMBO_SPIN_REV);
	DDX_Control(pDX, IDC_COMBO_SPIN_TIME, m_COMBO_SPIN_TIME);
	DDX_Control(pDX, IDC_COMBO_SPIN_STEP, m_COMBO_SPIN_STEP);
	DDX_Control(pDX, IDC_CHECK_SPIN_ACC, m_CHECK_SPIN_ACC);
	DDX_Control(pDX, IDC_COMBO_SPIN_INIT, m_COMBO_SPIN_INIT);
	DDX_Control(pDX, IDC_CHECK_DIRECT_SPN, m_CHECK_DIRECT_SPN);
	DDX_Control(pDX, IDC_COMBO_LOW, m_COMBO_LOW);
	DDX_Control(pDX, IDC_COMBO_TACHPIN_SEL, m_COMBO_TACHPIN_SEL);
	DDX_Text(pDX, IDC_EDIT_PWMIN_FINAL, m_EDIT_PWMIN_FINAL);
	DDX_Text(pDX, IDC_EDIT_TARGET_SPD, m_EDIT_TARGET_SPD);
	DDX_Control(pDX, IDC_CHECK_TOR_HYS_DIS, m_CHECK_TOR_HYS_DIS);
	DDX_Control(pDX, IDC_EDIT_FBRES, m_EDIT_FBRES);
	DDX_Control(pDX, IDC_EDIT_REFRES, m_EDIT_REFRES);
	DDX_Control(pDX, IDC_EDIT_SENRES, m_EDIT_SENRES);
	DDX_Text(pDX, IDC_EDIT_SENGAIN, m_EDIT_SENGAIN);
	DDX_Control(pDX, IDC_COMBO_ILIMIT_MAX, m_COMBO_ILIMIT_MAX);
	DDX_Control(pDX, IDC_CHECK_CLKMON_EN, m_CHECK_CLKMON_EN);
	DDX_Control(pDX, IDC_CHECK_REG2P5FB_EN, m_CHECK_REG2P5FB_EN);
	DDX_Control(pDX, IDC_CHECK_TSHUTDIS, m_CHECK_TSHUTDIS);
	DDX_Control(pDX, IDC_CHECK_USEREG, m_CHECK_USEREG);
	DDX_Control(pDX, IDC_COMBO_OSCTC, m_COMBO_OSCTC);
	DDX_Control(pDX, IDC_CHECK_OTP1DONE, m_CHECK_OTP1DONE);
	DDX_Control(pDX, IDC_CHECK_OTPCAL_DONE, m_CHECK_OTPCAL_DONE);
	DDX_Control(pDX, IDC_EDIT_REFSPEED, m_EDIT_REFSPEED);
	DDX_Control(pDX, IDC_CHECK_SLOW_RESPONSE, m_CHECK_SLOW_RESPONSE);
	DDX_Control(pDX, IDC_COMBO_IS_DELAY, m_COMBO_IS_DELAY);
	DDX_Control(pDX, IDC_CHECK_DLL_EN, m_CHECK_DLL_EN);
	DDX_Control(pDX, IDC_CHECK_FF_EN, m_CHECK_FF_EN);
	DDX_Control(pDX, IDC_CHECK_FF_S6_EN, m_CHECK_FF_S6_EN);
	DDX_Control(pDX, IDC_CHECK_LEVEL_OVERFLOW, m_CHECK_LEVEL_OVERFLOW);
	DDX_Text(pDX, IDC_EDIT_SUMOUT_FF, m_EDIT_SUMOUT_FF);
	DDX_Text(pDX, IDC_EDIT_SUMOUT_FF_TEST, m_EDIT_SUMOUT_FF_TEST);
	DDX_Text(pDX, IDC_EDIT_RELY_CNT, m_EDIT_RELY_CNT);
	DDX_Control(pDX, IDC_EDIT_RELY_ON, m_RELY_ON);
	DDX_Control(pDX, IDC_EDIT_RELY_OFF, m_EDIT_RELY_OFF);
	DDX_Text(pDX, IDC_EDIT_RPMCOUNT, m_EDIT_RPMCOUNT);
	DDX_Control(pDX, IDC_EDIT_MINSP, m_EDIT_MINSP);
	DDX_Text(pDX, IDC_EDIT_MINSP_PERCENT, m_EDIT_MINSP_PERCENT);
	DDX_Control(pDX, IDC_EDIT_PERSEC, m_EDIT_PERSEC);
	DDX_Control(pDX, IDC_EDIT_FORSEC, m_EDIT_FORSEC);
	DDX_Control(pDX, IDC_CHECK_FAN_EN_OFF_BRK, m_CHECK_FAN_EN_OFF_BRK);
	DDX_Control(pDX, IDC_CHECK_PWM_FLOAT_DIS, m_CHECK_PWM_FLOAT_DIS);
	DDX_Control(pDX, IDC_COMBO_PWM_FLOAT_DETAIL, m_COMBO_PWM_FLOAT_DETAIL);
	DDX_Control(pDX, IDC_COMBO_PWM_LOW_DETAIL, m_COMBO_PWM_LOW_DETAIL);
	DDX_Control(pDX, IDC_COMBO_HT, m_COMBO_HT);
	DDX_Control(pDX, IDC_COMBO_LT, m_COMBO_LT);
	DDX_Control(pDX, IDC_COMBO_MT, m_COMBO_MT);
	DDX_Control(pDX, IDC_EDIT_LOW, m_EDIT_LOW);
	DDX_Control(pDX, IDC_EDIT_MID, m_EDIT_MID);
	DDX_Text(pDX, IDC_EDIT_LOW_PERCENT, m_EDIT_LOW_PERCENT);
	DDX_Text(pDX, IDC_EDIT_MID_PERCENT, m_EDIT_MID_PERCENT);
	DDX_Control(pDX, IDC_EDIT_HT, m_EDIT_HT);
	DDX_Text(pDX, IDC_EDIT_HT_PERCENT, m_EDIT_HT_PERCENT);
	DDX_Control(pDX, IDC_EDIT_LT, m_EDIT_LT);
	DDX_Text(pDX, IDC_EDIT_LT_PERCENT, m_EDIT_LT_PERCENT);
	DDX_Control(pDX, IDC_EDIT_MT1, m_EDIT_MT1);
	DDX_Text(pDX, IDC_EDIT_MIT1_PERCENT, m_EDIT_MIT1_PERCENT);
	DDX_Control(pDX, IDC_EDIT_MID2, m_EDIT_MID2);
	DDX_Text(pDX, IDC_EDIT_MID2_PERCENT, m_EDIT_MID2_PERCENT);
	DDX_Control(pDX, IDC_EDIT_MT2, m_EDIT_MT2);
	DDX_Text(pDX, IDC_EDIT_MIT2_PERCENT, m_EDIT_MIT2_PERCENT);
	DDX_Control(pDX, IDC_EDIT_INCRE_PERCENT, m_EDIT_INCRE_PERCENT);
	DDX_Text(pDX, IDC_EDIT_EFFECTIVE_SDISRUPT, m_EDIT_EFFECTIVE_SDISRUPT);
	DDX_Control(pDX, IDC_COMBO_PWMIN_FS, m_COMBO_PWMIN_FS);
	DDX_Control(pDX, IDC_CHECK_TACHPIN_INV, m_CHECK_TACHPIN_INV);
	DDX_Control(pDX, IDC_CHECK_RETRY_ILIM_BRK, m_CHECK_RETRY_ILIM_BRK);
	DDX_Control(pDX, IDC_CHECK_RETRY_TRISTATE, m_CHECK_RETRY_TRISTATE);
	DDX_Text(pDX, IDC_EDIT_TO_S3, m_EDIT_TO_S3);
	DDX_Control(pDX, IDC_EDIT_MINDAC_CLAMP, m_EDIT_MINDAC_CLAMP);
	DDX_Text(pDX, IDC_EDIT_MINDAC_CLAMP_RD, m_EDIT_MINDAC_CLAMP_RD);
	//  DDX_Control(pDX, IDC_CHECK_GAIN_SEL, m_CHECK_GAIN_SEL);
	//  DDX_Check(pDX, IDC_CHECK_GAIN_SEL, m_CHECK_GAIN_SEL);
	DDX_Control(pDX, IDC_CHECK_GAIN_SEL, m_CHECK_GAIN_SEL);
}


BEGIN_MESSAGE_MAP(CdetailDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_CHECK_FAN_EN, &CdetailDlg::OnBnClickedCheckFanEn)
	ON_BN_CLICKED(IDC_CHECK_SYN_CLAMP, &CdetailDlg::OnBnClickedCheckSynClamp)
	ON_BN_CLICKED(IDC_CHECK_VPWR_CLAMP, &CdetailDlg::OnBnClickedCheckVpwrClamp)
	ON_BN_CLICKED(IDC_CHECK_POS_SNS, &CdetailDlg::OnBnClickedCheckPosSns)
	ON_BN_CLICKED(IDC_CHECK_PMC_EN, &CdetailDlg::OnBnClickedCheckPmcEn)
	ON_BN_CLICKED(IDC_CHECK_FAULT_SHUT, &CdetailDlg::OnBnClickedCheckFaultShut)
	ON_BN_CLICKED(IDC_CHECK_COM_SEL, &CdetailDlg::OnBnClickedCheckComSel)
	ON_BN_CLICKED(IDC_CHECK_6S_SIN, &CdetailDlg::OnBnClickedCheck6sSin)
	ON_BN_CLICKED(IDC_CHECK_TRISTATE, &CdetailDlg::OnBnClickedCheckTristate)
	ON_BN_CLICKED(IDC_CHECK_3PH_DET, &CdetailDlg::OnBnClickedCheck3phDet)
	ON_BN_CLICKED(IDC_CHECK_BEMF_FLT, &CdetailDlg::OnBnClickedCheckBemfFlt)
	ON_BN_CLICKED(IDC_CHECK_SP_PWR, &CdetailDlg::OnBnClickedCheckSpPwr)
	ON_BN_CLICKED(IDC_CHECK_VAR_DAC, &CdetailDlg::OnBnClickedCheckVarDac)
	ON_BN_CLICKED(IDC_CHECK_BLIND_SPNACCEL, &CdetailDlg::OnBnClickedCheckBlindSpnaccel)
	ON_BN_CLICKED(IDC_CHECK_FP_EN, &CdetailDlg::OnBnClickedCheckFpEn)
	ON_BN_CLICKED(IDC_CHECK_OFFMSK_EN, &CdetailDlg::OnBnClickedCheckOffmskEn)
	ON_BN_CLICKED(IDC_CHECK_TC_EXT, &CdetailDlg::OnBnClickedCheckTcExt)
	ON_BN_CLICKED(IDC_CHECK_TSHUT_DIS, &CdetailDlg::OnBnClickedCheckTshutDis)
	ON_CBN_SELCHANGE(IDC_COMBO_REG_OVERWR, &CdetailDlg::OnCbnSelchangeComboRegOverwr)
	ON_CBN_SELCHANGE(IDC_COMBO_SCOMM, &CdetailDlg::OnCbnSelchangeComboScomm)
	ON_CBN_SELCHANGE(IDC_COMBO_TACHO, &CdetailDlg::OnCbnSelchangeComboTacho)
	ON_CBN_SELCHANGE(IDC_COMBO_S0S3_RPM, &CdetailDlg::OnCbnSelchangeComboS0s3Rpm)
	ON_CBN_SELCHANGE(IDC_COMBO_TFREEZE, &CdetailDlg::OnCbnSelchangeComboTfreeze)
	ON_CBN_SELCHANGE(IDC_COMBO_COMM_MASK, &CdetailDlg::OnCbnSelchangeComboCommMask)
	ON_CBN_SELCHANGE(IDC_COMBO_TORQUE_COARSE, &CdetailDlg::OnCbnSelchangeComboTorqueCoarse)
	ON_CBN_SELCHANGE(IDC_COMBO_TORQUE_FINE, &CdetailDlg::OnCbnSelchangeComboTorqueFine)
	ON_CBN_SELCHANGE(IDC_COMBO_FREEZE_HYS, &CdetailDlg::OnCbnSelchangeComboFreezeHys)
	ON_CBN_SELCHANGE(IDC_COMBO_BEMF_HYS, &CdetailDlg::OnCbnSelchangeComboBemfHys)
	ON_CBN_SELCHANGE(IDC_COMBO_ILIMIT, &CdetailDlg::OnCbnSelchangeComboIlimit)
	ON_CBN_SELCHANGE(IDC_COMBO_ILIMIT_AUTO, &CdetailDlg::OnCbnSelchangeComboIlimitAuto)
	ON_CBN_SELCHANGE(IDC_COMBO_OFF_MASK, &CdetailDlg::OnCbnSelchangeComboOffMask)
	ON_CBN_SELCHANGE(IDC_COMBO_ON_MASK, &CdetailDlg::OnCbnSelchangeComboOnMask)
	ON_CBN_SELCHANGE(IDC_COMBO_S1_ISDELAY, &CdetailDlg::OnCbnSelchangeComboS1Isdelay)
	ON_CBN_SELCHANGE(IDC_COMBO_BLINDSPN_COUNT, &CdetailDlg::OnCbnSelchangeComboBlindspnCount)
	ON_CBN_SELCHANGE(IDC_COMBO_BLINDSPN_STEP, &CdetailDlg::OnCbnSelchangeComboBlindspnStep)
	ON_CBN_SELCHANGE(IDC_COMBO_TS_IS, &CdetailDlg::OnCbnSelchangeComboTsIs)
	ON_CBN_SELCHANGE(IDC_COMBO_TO_S3, &CdetailDlg::OnCbnSelchangeComboToS3)
	ON_CBN_SELCHANGE(IDC_COMBO_TS_INIT, &CdetailDlg::OnCbnSelchangeComboTsInit)
	ON_CBN_SELCHANGE(IDC_COMBO_TS_BLIND, &CdetailDlg::OnCbnSelchangeComboTsBlind)
	ON_CBN_SELCHANGE(IDC_COMBO_TS_INITBLIND, &CdetailDlg::OnCbnSelchangeComboTsInitblind)
	ON_CBN_SELCHANGE(IDC_COMBO_OSC_OFFSET, &CdetailDlg::OnCbnSelchangeComboOscOffset)
	ON_CBN_SELCHANGE(IDC_COMBO_OSC_TC, &CdetailDlg::OnCbnSelchangeComboOscTc)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMUX, &CdetailDlg::OnCbnSelchangeComboTestmux)
	ON_BN_CLICKED(IDC_BUTTON_WIN_MASK, &CdetailDlg::OnBnClickedButtonWinMask)
	ON_BN_CLICKED(IDC_BUTTON_WIN, &CdetailDlg::OnBnClickedButtonWin)
	ON_BN_CLICKED(IDC_BUTTON_LDAC, &CdetailDlg::OnBnClickedButtonLdac)
	ON_BN_CLICKED(IDC_BUTTON_HDAC, &CdetailDlg::OnBnClickedButtonHdac)
	ON_BN_CLICKED(IDC_BUTTON_SPDAC_S1, &CdetailDlg::OnBnClickedButtonSpdacS1)
	ON_BN_CLICKED(IDC_BUTTON_DACUP, &CdetailDlg::OnBnClickedButtonDacup)
	ON_BN_CLICKED(IDC_BUTTON_DACDOWN, &CdetailDlg::OnBnClickedButtonDacdown)
	ON_BN_CLICKED(IDC_BUTTON_DACUP_SMALL, &CdetailDlg::OnBnClickedButtonDacupSmall)
	ON_BN_CLICKED(IDC_BUTTON_DACDOWN_SMALL, &CdetailDlg::OnBnClickedButtonDacdownSmall)
	ON_BN_CLICKED(IDC_BUTTON_RSTATUS, &CdetailDlg::OnBnClickedButtonRstatus)
	ON_CBN_SELCHANGE(IDC_COMBO_LOW_DAC, &CdetailDlg::OnCbnSelchangeComboLowDac)
	ON_CBN_SELCHANGE(IDC_COMBO_MIN_DAC, &CdetailDlg::OnCbnSelchangeComboMinDac)
	ON_BN_CLICKED(IDC_BUTTON_READ_DAC, &CdetailDlg::OnBnClickedButtonReadDac)
	ON_BN_CLICKED(IDC_BUTTON_WDAC, &CdetailDlg::OnBnClickedButtonWdac)
	ON_BN_CLICKED(IDC_BUTTON_WDACUP, &CdetailDlg::OnBnClickedButtonWdacup)
	ON_BN_CLICKED(IDC_BUTTON_WDACDOWN, &CdetailDlg::OnBnClickedButtonWdacdown)
	ON_BN_CLICKED(IDC_BUTTON_WDACUP_SMALL, &CdetailDlg::OnBnClickedButtonWdacupSmall)
	ON_BN_CLICKED(IDC_BUTTON_WDACDOWN_SMALL, &CdetailDlg::OnBnClickedButtonWdacdownSmall)
	ON_BN_CLICKED(IDC_BUTTON_READ_TPOS, &CdetailDlg::OnBnClickedButtonReadTpos)
	ON_BN_CLICKED(IDC_BUTTON_READALL, &CdetailDlg::OnBnClickedButtonReadall)
	ON_BN_CLICKED(IDC_BUTTON_START, &CdetailDlg::OnBnClickedButtonStart)
	ON_CBN_SELCHANGE(IDC_COMBO_SDISRUPT_SEL, &CdetailDlg::OnCbnSelchangeComboSdisruptSel)
	ON_CBN_SELCHANGE(IDC_COMBO_POLE_PAIR, &CdetailDlg::OnCbnSelchangeComboPolePair)
	ON_BN_CLICKED(IDC_BUTTON_WINMSK_AUTO, &CdetailDlg::OnBnClickedButtonWinmskAuto)
	ON_BN_CLICKED(IDC_BUTTON_SPDAC_S2, &CdetailDlg::OnBnClickedButtonSpdacS2)
	ON_BN_CLICKED(IDC_BUTTON_DACUP2, &CdetailDlg::OnBnClickedButtonDacup2)
	ON_BN_CLICKED(IDC_BUTTON_DACUP_SMALL2, &CdetailDlg::OnBnClickedButtonDacupSmall2)
	ON_BN_CLICKED(IDC_BUTTON_DACDOWN2, &CdetailDlg::OnBnClickedButtonDacdown2)
	ON_BN_CLICKED(IDC_BUTTON_DACDOWN_SMALL2, &CdetailDlg::OnBnClickedButtonDacdownSmall2)
	ON_BN_CLICKED(IDC_BUTTON_SPDAC_S4, &CdetailDlg::OnBnClickedButtonSpdacS4)
	ON_BN_CLICKED(IDC_BUTTON_DACUP4, &CdetailDlg::OnBnClickedButtonDacup4)
	ON_BN_CLICKED(IDC_BUTTON_DACDOWN4, &CdetailDlg::OnBnClickedButtonDacdown4)
	ON_BN_CLICKED(IDC_BUTTON_DACUP_SMALL4, &CdetailDlg::OnBnClickedButtonDacupSmall4)
	ON_BN_CLICKED(IDC_BUTTON_DACDOWN_SMALL4, &CdetailDlg::OnBnClickedButtonDacdownSmall4)
	ON_BN_CLICKED(IDC_CHECK_OSCCAL_MAN, &CdetailDlg::OnBnClickedCheckOsccalMan)
	ON_BN_CLICKED(IDC_CHECK_OSCCAL_AUTO, &CdetailDlg::OnBnClickedCheckOsccalAuto)
	ON_BN_CLICKED(IDC_CHECK_OSC_DIS, &CdetailDlg::OnBnClickedCheckOscDis)
	ON_BN_CLICKED(IDC_RADIO_PWMREG_SEL, &CdetailDlg::OnBnClickedRadioPwmregSel)
	ON_BN_CLICKED(IDC_RADIO_PWMIN_SEL, &CdetailDlg::OnBnClickedRadioPwminSel)
	ON_BN_CLICKED(IDC_RADIO_EXTDAC_SEL, &CdetailDlg::OnBnClickedRadioExtdacSel)
	ON_BN_CLICKED(IDC_BUTTON_PHASE_CNT, &CdetailDlg::OnBnClickedButtonPhaseCnt)
	ON_BN_CLICKED(IDC_CHECK_AD_TOR, &CdetailDlg::OnBnClickedCheckAdTor)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_00, &CdetailDlg::OnCbnSelchangeComboTestmode00)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_01, &CdetailDlg::OnCbnSelchangeComboTestmode01)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_10, &CdetailDlg::OnCbnSelchangeComboTestmode10)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTMODE_11, &CdetailDlg::OnCbnSelchangeComboTestmode11)
	ON_BN_CLICKED(IDC_RADIO_MODE_00, &CdetailDlg::OnBnClickedRadioMode00)
	ON_BN_CLICKED(IDC_RADIO_MODE_01, &CdetailDlg::OnBnClickedRadioMode01)
	ON_BN_CLICKED(IDC_RADIO_MODE_10, &CdetailDlg::OnBnClickedRadioMode10)
	ON_BN_CLICKED(IDC_RADIO_MODE_11, &CdetailDlg::OnBnClickedRadioMode11)
	ON_CBN_SELCHANGE(IDC_COMBO_ILIMIT_BRAKE, &CdetailDlg::OnCbnSelchangeComboIlimitBrake)
	ON_BN_CLICKED(IDC_BUTTON_WMSK_UP, &CdetailDlg::OnBnClickedButtonWmskUp)
	ON_BN_CLICKED(IDC_BUTTON_WMSK_DOWN, &CdetailDlg::OnBnClickedButtonWmskDown)
	ON_BN_CLICKED(IDC_BUTTON_WIN_UP, &CdetailDlg::OnBnClickedButtonWinUp)
	ON_BN_CLICKED(IDC_BUTTON_WIN_DOWN, &CdetailDlg::OnBnClickedButtonWinDown)
	ON_BN_CLICKED(IDC_BUTTON_WINAUTO_DOWN, &CdetailDlg::OnBnClickedButtonWinautoDown)
	ON_BN_CLICKED(IDC_BUTTON_MSKAUTO_UP, &CdetailDlg::OnBnClickedButtonMskautoUp)
	ON_BN_CLICKED(IDC_BUTTON_MSKAUTO_DOWN, &CdetailDlg::OnBnClickedButtonMskautoDown)
	ON_BN_CLICKED(IDC_BUTTON_WINAUTO_UP, &CdetailDlg::OnBnClickedButtonWinautoUp)
	ON_CBN_SELCHANGE(IDC_COMBO_BBS_RANGE, &CdetailDlg::OnCbnSelchangeComboBbsRange)
	ON_BN_CLICKED(IDC_BUTTON_REFCOUNT, &CdetailDlg::OnBnClickedButtonRefcount)
	ON_BN_CLICKED(IDC_BUTTON_REFCOUNTUP, &CdetailDlg::OnBnClickedButtonRefcountup)
	ON_BN_CLICKED(IDC_BUTTON_REFCOUNTDOWN, &CdetailDlg::OnBnClickedButtonRefcountdown)
	ON_BN_CLICKED(IDC_BUTTON_REFCOUNTUP_SMALL, &CdetailDlg::OnBnClickedButtonRefcountupSmall)
	ON_BN_CLICKED(IDC_BUTTON_REFCOUNTDOWN_SMALL, &CdetailDlg::OnBnClickedButtonRefcountdownSmall)
	ON_CBN_SELCHANGE(IDC_COMBO_MINSP, &CdetailDlg::OnCbnSelchangeComboMinsp)
	ON_BN_CLICKED(IDC_CHECK_SP_CNTL_EN, &CdetailDlg::OnBnClickedCheckSpCntlEn)
	ON_BN_CLICKED(IDC_RADIO_BLIND_SPIN_DIS, &CdetailDlg::OnBnClickedRadioBlindSpinDis)
	ON_BN_CLICKED(IDC_RADIO_BLIND_SPIN_EN, &CdetailDlg::OnBnClickedRadioBlindSpinEn)
	ON_CBN_SELCHANGE(IDC_COMBO_SPIN_REV, &CdetailDlg::OnCbnSelchangeComboSpinRev)
	ON_CBN_SELCHANGE(IDC_COMBO_SPIN_TIME, &CdetailDlg::OnCbnSelchangeComboSpinTime)
	ON_CBN_SELCHANGE(IDC_COMBO_SPIN_STEP, &CdetailDlg::OnCbnSelchangeComboSpinStep)
	ON_CBN_SELCHANGE(IDC_COMBO_SPIN_INIT, &CdetailDlg::OnCbnSelchangeComboSpinInit)
	ON_BN_CLICKED(IDC_CHECK_SPIN_ACC, &CdetailDlg::OnBnClickedCheckSpinAcc)
	ON_BN_CLICKED(IDC_CHECK_DIRECT_SPN, &CdetailDlg::OnBnClickedCheckDirectSpn)
	ON_CBN_SELCHANGE(IDC_COMBO_LOW, &CdetailDlg::OnCbnSelchangeComboLow)
	ON_CBN_SELCHANGE(IDC_COMBO_TACHPIN_SEL, &CdetailDlg::OnCbnSelchangeComboTachpinSel)
	ON_BN_CLICKED(IDC_CHECK_TOR_HYS_DIS, &CdetailDlg::OnBnClickedCheckTorHysDis)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_IS, &CdetailDlg::OnBnClickedButtonManualIs)
	ON_BN_CLICKED(IDC_RADIO_HSS, &CdetailDlg::OnBnClickedRadioHss)
	ON_BN_CLICKED(IDC_RADIO_LSS, &CdetailDlg::OnBnClickedRadioLss)
	ON_BN_CLICKED(IDC_BUTTON_SET_ILIMIT, &CdetailDlg::OnBnClickedButtonSetIlimit)
	ON_BN_CLICKED(IDC_CHECK_CLKMON_EN, &CdetailDlg::OnBnClickedCheckClkmonEn)
	ON_BN_CLICKED(IDC_CHECK_REG2P5FB_EN, &CdetailDlg::OnBnClickedCheckReg2p5fbEn)
	ON_BN_CLICKED(IDC_CHECK_TSHUTDIS, &CdetailDlg::OnBnClickedCheckTshutdis)
	ON_BN_CLICKED(IDC_CHECK_USEREG, &CdetailDlg::OnBnClickedCheckUsereg)
	ON_CBN_SELCHANGE(IDC_COMBO_OSCTC, &CdetailDlg::OnCbnSelchangeComboOsctc)
	ON_BN_CLICKED(IDC_RADIO_1PP, &CdetailDlg::OnBnClickedRadio1pp)
	ON_BN_CLICKED(IDC_RADIO_4PP, &CdetailDlg::OnBnClickedRadio4pp)
	ON_CBN_DROPDOWN(IDC_COMBO_POLE_PAIR, &CdetailDlg::OnCbnDropdownComboPolePair)
	ON_BN_CLICKED(IDC_BUTTON_REFSPEED, &CdetailDlg::OnBnClickedButtonRefspeed)
	ON_BN_CLICKED(IDC_CHECK_SLOW_RESPONSE, &CdetailDlg::OnBnClickedCheckSlowResponse)
	ON_CBN_SELCHANGE(IDC_COMBO_IS_DELAY, &CdetailDlg::OnCbnSelchangeComboIsDelay)
	ON_BN_CLICKED(IDC_CHECK_DLL_EN, &CdetailDlg::OnBnClickedCheckDllEn)
	ON_BN_CLICKED(IDC_CHECK_FF_EN, &CdetailDlg::OnBnClickedCheckFfEn)
	ON_BN_CLICKED(IDC_CHECK_FF_S6_EN, &CdetailDlg::OnBnClickedCheckFfS6En)
	ON_BN_CLICKED(IDC_CHECK_LEVEL_OVERFLOW, &CdetailDlg::OnBnClickedCheckLevelOverflow)
	ON_BN_CLICKED(IDC_BUTTON_RELIABILITY_TEST, &CdetailDlg::OnBnClickedButtonReliabilityTest)
	ON_BN_CLICKED(IDC_RADIO_HEX, &CdetailDlg::OnBnClickedRadioHex)
	ON_BN_CLICKED(IDC_RADIO_PERCENT, &CdetailDlg::OnBnClickedRadioPercent)
	ON_BN_CLICKED(IDC_RADIO_SPDAC_S1, &CdetailDlg::OnBnClickedRadioSpdacS1)
	ON_BN_CLICKED(IDC_RADIO_SPDAC_S2, &CdetailDlg::OnBnClickedRadioSpdacS2)
	ON_BN_CLICKED(IDC_RADIO_SPDAC_S4, &CdetailDlg::OnBnClickedRadioSpdacS4)
	ON_BN_CLICKED(IDC_BUTTON_RPMCOUNT, &CdetailDlg::OnBnClickedButtonRpmcount)
	ON_BN_CLICKED(IDC_BUTTON_RPMLOG, &CdetailDlg::OnBnClickedButtonRpmlog)
	ON_BN_CLICKED(IDC_BUTTON_SPEED_PROFILE, &CdetailDlg::OnBnClickedButtonSpeedProfile)
	ON_BN_CLICKED(IDC_BUTTON_MINSP, &CdetailDlg::OnBnClickedButtonMinsp)
	ON_BN_CLICKED(IDC_CHECK_FAN_EN_OFF_BRK, &CdetailDlg::OnBnClickedCheckFanEnOffBrk)
	ON_BN_CLICKED(IDC_CHECK_PWM_FLOAT_DIS, &CdetailDlg::OnBnClickedCheckPwmFloatDis)
	ON_CBN_SELCHANGE(IDC_COMBO_PWM_LOW_DETAIL, &CdetailDlg::OnCbnSelchangeComboPwmLowDetail)
	ON_CBN_SELCHANGE(IDC_COMBO_PWM_FLOAT_DETAIL, &CdetailDlg::OnCbnSelchangeComboPwmFloatDetail)
	ON_CBN_SELCHANGE(IDC_COMBO_HT, &CdetailDlg::OnCbnSelchangeComboHt)
	ON_CBN_SELCHANGE(IDC_COMBO_LT, &CdetailDlg::OnCbnSelchangeComboLt)
	ON_CBN_SELCHANGE(IDC_COMBO_MT, &CdetailDlg::OnCbnSelchangeComboMt)
	ON_CBN_SELCHANGE(IDC_COMBO_PWMIN_FS, &CdetailDlg::OnCbnSelchangeComboPwminFs)
	ON_BN_CLICKED(IDC_CHECK_TACHPIN_INV, &CdetailDlg::OnBnClickedCheckTachpinInv)
	ON_BN_CLICKED(IDC_CHECK_RETRY_ILIM_BRK, &CdetailDlg::OnBnClickedCheckRetryIlimBrk)
	ON_BN_CLICKED(IDC_CHECK_RETRY_TRISTATE, &CdetailDlg::OnBnClickedCheckRetryTristate)
	//ON_EN_CHANGE(IDC_EDIT_MINSP, &CdetailDlg::OnEnChangeEditMinsp)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MINDAC_CLAMP, &CdetailDlg::OnBnClickedButtonMindacClamp)
	END_MESSAGE_MAP()


// CdetailDlg message handlers

BOOL CdetailDlg::OnInitDialog()
{
	CString temp_string;
	
	FILE *fpi;
	char command[1000];
	int wordcnt=0;
	int i=0;
	CString str;
	CString errmsg;
    errno_t err;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	const TCHAR* fpi_name = L"ilimit_setting.txt";
    
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		// hss_cal=1;
		 fb_res=18000.0;
         ref_res=1100.0;
         sense_res=0.0033;
		 goto end_error;
	};

      while (i != EOF){
		i = fscanf_s(fpi, "%s", command, 1000);
		if(i == EOF) break;
		//wordcnt++;

		if (_stricmp(command, "hssl") == 0 ){
			fscanf_s(fpi, "%x", &hss_cal);
		}
		else if (_stricmp(command, "rsen") == 0 ){
			fscanf_s(fpi, "%f", &sense_res);
		}
		else if (_stricmp(command, "rref") == 0 ){
			fscanf_s(fpi, "%f", &ref_res);
		}
		else if (_stricmp(command, "rfbk") == 0 ){
			fscanf_s(fpi, "%f", &fb_res);
		}
		else {
			unknown_format:;
			errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end_loading;
		};
	};

	end_loading:;
	fclose(fpi);
	end_error:;

	CDialog::OnInitDialog();
	//OnBnClickedButtonStart();
	m_EDIT_TO_S3.Format(_T("40ms"));
	UpdateData(FALSE);

	temp_string.Format(_T("%.5f"),sense_res);
	m_EDIT_SENRES.SetWindowText(temp_string);
	temp_string.Format(_T("%.2f"),ref_res);
	m_EDIT_REFRES.SetWindowText(temp_string);
	temp_string.Format(_T("%.2f"),fb_res);
	m_EDIT_FBRES.SetWindowText(temp_string);

	//test
	double test=sense_res;

	m_RELY_ON.SetWindowText(L"2500");
	m_EDIT_RELY_OFF.SetWindowText(L"4000");
	m_EDIT_PERSEC.SetWindowText(L"1000");
	m_EDIT_FORSEC.SetWindowText(L"20");
	m_EDIT_INCRE_PERCENT.SetWindowText(L"10");
	OnBnClickedButtonSetIlimit();

	//test
	test=sense_res;

	vardaccount();
	if (!success){goto end;};
	updatedelay();
	if (!success){goto end;};
	updateonmskacc();
	if (!success){goto end;};

	readall();
	if (!success){goto end;};

	

	//updatesdisrupt();
	//if (!success){goto end;};
	m_COMBO_ILIMIT_MAX.SetCurSel(15);

	if(hss_cal == 0){
		CheckRadioButton(IDC_RADIO_HSS,IDC_RADIO_LSS,IDC_RADIO_LSS);
	}else if(hss_cal == 1){
		CheckRadioButton(IDC_RADIO_HSS,IDC_RADIO_LSS,IDC_RADIO_HSS);
	}

	if(hex_percent == 0){
		CheckRadioButton(IDC_RADIO_HEX,IDC_RADIO_PERCENT,IDC_RADIO_HEX);
	}else if(hex_percent == 1){
		CheckRadioButton(IDC_RADIO_HEX,IDC_RADIO_PERCENT,IDC_RADIO_PERCENT);
	}

/*	if(fourpp == 0){
		CheckRadioButton(IDC_RADIO_1PP,IDC_RADIO_4PP,0);
	}else if(fourpp == 1){
		CheckRadioButton(IDC_RADIO_1PP,IDC_RADIO_4PP,IDC_RADIO_4PP);
	}else if(fourpp == 2){
		CheckRadioButton(IDC_RADIO_1PP,IDC_RADIO_4PP,IDC_RADIO_1PP);
	}*/

	if(spdac_stage == 1){
		CheckRadioButton(IDC_RADIO_SPDAC_S1,IDC_RADIO_SPDAC_S4,IDC_RADIO_SPDAC_S1);
		m_EDIT_SPDAC_S1.EnableWindow(1);
	    m_EDIT_SPDAC_S2.EnableWindow(0);
	    m_EDIT_SPDAC_S4.EnableWindow(0);
	}else if(spdac_stage == 2){
		CheckRadioButton(IDC_RADIO_SPDAC_S1,IDC_RADIO_SPDAC_S4,IDC_RADIO_SPDAC_S2);
		m_EDIT_SPDAC_S1.EnableWindow(0);
		m_EDIT_SPDAC_S2.EnableWindow(1);
		m_EDIT_SPDAC_S4.EnableWindow(0);
	}else if(spdac_stage == 4){
		CheckRadioButton(IDC_RADIO_SPDAC_S1,IDC_RADIO_SPDAC_S4,IDC_RADIO_SPDAC_S4);
		m_EDIT_SPDAC_S1.EnableWindow(0);
		m_EDIT_SPDAC_S2.EnableWindow(0);
		m_EDIT_SPDAC_S4.EnableWindow(1);
	}

    end:;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CdetailDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
    ((CFanmotorDlg*)m_pParent)->detaildlg = NULL;
    delete this;
}

void CdetailDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void CdetailDlg::OnClose() 
{
	DestroyWindow();
}

void CdetailDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CdetailDlg::OnOK() 
{
}

void CdetailDlg::OnCancel() 
{
}


bool CdetailDlg::datarangecheck8bits(int data)
{		
	bool pass = FALSE;
	CString feedback;
	if(data<0x0 || data > 0xff){
		feedback.Format(_T("Data %xh is out of allowable range.\nINFO: Allowable data range is from 0h to ffh\nPlease re-enter the data\n"),data);
		AfxMessageBox(feedback);
	}else{
		pass = TRUE;
	}
	return pass;
}

bool CdetailDlg::datarangecheck4bits(int data)
{		
	bool pass = FALSE;
	CString feedback;
	if(data<0x0 || data > 0xf){
		feedback.Format(_T("Data %xh is out of allowable range.\nINFO: Allowable data range is from 0h to fh\nPlease re-enter the data\n"),data);
		AfxMessageBox(feedback);
	}else{
		pass = TRUE;
	}
	return pass;
}

bool CdetailDlg::datarangecheck6bits(int data)
{		
	bool pass = FALSE;
	CString feedback;
	if(data<0x0 || data > 0x3f){
		feedback.Format(_T("Data %xh is out of allowable range.\nINFO: Allowable data range is from 0h to 3fh\nPlease re-enter the data\n"),data);
		AfxMessageBox(feedback);
	}else{
		pass = TRUE;
	}
	return pass;
}

bool CdetailDlg::datarangecheck12bits(int data)
{		
	bool pass = FALSE;
	CString feedback;
	if(data<0x0 || data > 0xfff){
		feedback.Format(_T("Data %xh is out of allowable range.\nINFO: Allowable data range is from 0h to fffh\nPlease re-enter the data\n"),data);
		AfxMessageBox(feedback);
	}else{
		pass = TRUE;
	}
	return pass;
}

bool CdetailDlg::datarangecheck16bits(int data)
{		
	bool pass = FALSE;
	CString feedback;
	if(data<0x0 || data > 0xffff){
		feedback.Format(_T("Data %xh is out of allowable range.\nINFO: Allowable data range is from 0h to ffffh\nPlease re-enter the data\n"),data);
		AfxMessageBox(feedback);
	}else{
		pass = TRUE;
	}
	return pass;
}

bool CdetailDlg::datarangecheck5bits(int data)
{		
	bool pass = FALSE;
	CString feedback;
	if(data<0x0 || data > 0x1f){
		feedback.Format(_T("Data %xh is out of allowable range.\nINFO: Allowable data range is from 0h to 1fh\nPlease re-enter the data\n"),data);
		AfxMessageBox(feedback);
	}else{
		pass = TRUE;
	}
	return pass;
}

void CdetailDlg::readall()
{
	int regval,mask,angle,temp_int1,temp_int2;
	int lowcount_read,mapdac_read;
	double temp_cal,temp_float,target_speed;
	CString datbits,temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    regval = pParent->rreg(0x01);
    if (!success){goto end;};

	mask=1;
	
	sp_tri=(regval>>6)&mask;
	bemf_fil_en=(regval>>5)&mask;
	pos_sns=(regval>>4)&mask;
	ad_tor=(regval>>3)&mask;
	swap_bc=(regval>>2)&mask;
	direct_spn=(regval>>1)&mask;
	otp_cal_sel=regval&mask;
	
	regval = pParent->rreg(0x02);
    if (!success){goto end;};

	mask=1;
	pwm_reg_sel=(regval>>6)&mask;
	fault_shut_dis=(regval>>5)&mask;
	osc_dis=(regval>>4)&mask;
	tshutdis=(regval>>3)&mask;
	reg2p5fb_en=(regval>>2)&mask;
	use_reg=(regval>>1)&mask;

	regval = pParent->rreg(0x03);
    if (!success){goto end;};

	mask=7;
	scomm=(regval>>5)&mask;
    torque_coarse=(regval>>2)&mask;
	mask=3;
	torque_fine=regval&mask;
	
	regval = pParent->rreg(0x04);
    if (!success){goto end;};

	mask=1;
	fan_en=(regval>>7)&mask;
	sp_cntl_en=(regval>>6)&mask;
	blind_spin_en=(regval>>5)&mask;
	six_sine=(regval>>4)&mask;
	dll_en=(regval>>3)&mask;
	ff_en=(regval>>2)&mask;
	retry_disable=(regval>>1)&mask;
	tachpin_inv=regval&mask;

    regval = pParent->rreg(0x05);
    if (!success){goto end;};

	mask=3;
	bhys=(regval>>6)&mask;
	mask=1;
	rev_torque=(regval>>1)&mask;
	syn_clamp_dis=regval&mask;

	regval = pParent->rreg(0x06);
    if (!success){goto end;};

	mask=15;
	comm_msk=(regval>>4)&mask;
	mask=7;
	pwm_msk=(regval>>1)&mask;
	mask=1;
	offmsk_en=regval&mask;

	regval = pParent->rreg(0x07);
    if (!success){goto end;};

	mask=15;
    comm_msk_acc=(regval>>4)&mask;
	mask=3;
	onmsk_acc=(regval>>2)&mask;
	mask=1;
	pole_pair=(regval>>1)&mask;
	s0s2_rpm=regval&mask;

	regval = pParent->rreg(0x08);
    if (!success){goto end;};

	mask=63;
    sp_win_auto=regval&mask;
	mask=1;
	triphase_det_en=(regval>>7)&mask;
	pmc_en=(regval>>6)&mask;

	temp_string.Format(_T("%x"),sp_win_auto);
	m_EDIT_HDAC.SetWindowText(temp_string);
	temp_float = sp_win_auto*1.875;
    m_EDIT_HDAC_CAL.Format(_T("%.1f deg"),temp_float);
	UpdateData(FALSE);

	regval = pParent->rreg(0x09);
    if (!success){goto end;};

	mask=63;
	sp_win=regval&mask;
	mask=1;
	pwm_inv=(regval>>7)&mask;
	
	temp_string.Format(_T("%x"),sp_win);
	m_EDIT_WIN.SetWindowText(temp_string);
	temp_float = sp_win*1.875;
    m_EDIT_SP_WINCAL.Format(_T("%.1f deg"),temp_float);
	UpdateData(FALSE);  

	regval = pParent->rreg(0x0a);
    if (!success){goto end;};

    mask=1;
	pwm_in_select=(regval>>7)&mask;
	mask=7;
	vardac_count=(regval>>4)&mask;
	mask=15;
	winmsk_auto=regval&mask;

	temp_string.Format(_T("%x"),winmsk_auto);
	m_EDIT_WINMSK_AUTO.SetWindowText(temp_string);
	temp_float = winmsk_auto*1.875;
	m_EDIT_WINMSK_AUTOCAL.Format(_T("%.1f deg"),temp_float);
	UpdateData(FALSE); 
	
	regval = pParent->rreg(0x0b);
    if (!success){goto end;};

	mask=1;
	pwm_nonoverlap_dis=(regval>>7)&mask;
	mask=7;
	handover_spd=(regval>>4)&mask;
	mask=15;
	winmsk=regval&mask;

	temp_string.Format(_T("%x"),winmsk);
	m_EDIT_WIN_MASK.SetWindowText(temp_string);
	temp_float = winmsk*1.875;
    m_EDIT_WINMSK_CAL.Format(_T("%.1f deg"),temp_float);
	UpdateData(FALSE);

	regval = pParent->rreg(0x0c);
    if (!success){goto end;};

    mask=15;
	ilimit=(regval>>4)&mask;
	ilimit_brake=regval&mask;
		
	if(blind_spin_en==0){
        regval = pParent->rreg(0x0d);
        if (!success){goto end;};

	    mask=15;
		ilimit_auto_is=(regval>>4)&mask;
		ts=regval&mask;

		regval = pParent->rreg(0x0e);
		if (!success){goto end;};

		mask=3;
		spin_init=(regval>>5)&mask;
		//mask=1;
		//sdisrupt=(regval>>7)&mask;
		mask=31;
		phase_cnt=regval&mask;
		
		temp_string.Format(_T("%x"),phase_cnt);
		m_EDIT_PHASE_CNT.SetWindowText(temp_string);
		angle = (phase_cnt+1)*2;
		m_EDIT_RPHASE_CNT.Format(_T("%d"),angle);
		UpdateData(FALSE);  

		datbits="1";
	    pParent->dataupdate_anybits(0x04,2,datbits,1);

		regval = pParent->rreg(0x0d);
        if (!success){goto end;};

		mask=7;
	    spin_step=(regval>>4)&mask;
		spin_time=regval&mask;
		mask=1;
		spin_acc=(regval>>3)&mask;

		regval = pParent->rreg(0x0e);
        if (!success){goto end;};

        mask=31;
		spin_rev=regval&mask;
		mask=3;
		is_delay=(regval>>5)&mask;
		
		if (spin_acc==0){
			spinrev0();
		}else if(spin_acc==1){
			spinrev1();
		}

        datbits="0";
	    pParent->dataupdate_anybits(0x04,2,datbits,1);

	}else{
		regval = pParent->rreg(0x0d);
        if (!success){goto end;};

		mask=7;
	    spin_step=(regval>>4)&mask;
		spin_time=regval&mask;
		mask=1;
		spin_acc=(regval>>3)&mask;

		regval = pParent->rreg(0x0e);
        if (!success){goto end;};

        mask=31;
		spin_rev=regval&mask;
		mask=3;
		is_delay=(regval>>5)&mask;
				
		if (spin_acc==0){
			spinrev0();
		}else if(spin_acc==1){
			spinrev1();
		}

		datbits="0";
	    pParent->dataupdate_anybits(0x04,2,datbits,1);

		regval = pParent->rreg(0x0d);
        if (!success){goto end;};

	    mask=15;
		ilimit_auto_is=(regval>>4)&mask;
		ts=regval&mask;

		regval = pParent->rreg(0x0e);
		if (!success){goto end;};

		mask=3;
		spin_init=(regval>>5)&mask;
		//mask=1;
		//sdisrupt=(regval>>7)&mask;
		mask=31;
		phase_cnt=regval&mask;
		
		temp_string.Format(_T("%x"),phase_cnt);
		m_EDIT_PHASE_CNT.SetWindowText(temp_string);
		angle = (phase_cnt+1)*2;
		m_EDIT_RPHASE_CNT.Format(_T("%d"),angle);
		UpdateData(FALSE);  

		datbits="1";
	    pParent->dataupdate_anybits(0x04,2,datbits,1);
	}


	regval = pParent->rreg(0x0f);
    if (!success){goto end;};

	mask=3;
	driver_non_overlap=(regval>>6)&mask;
    mask=63;//0x3F
	spdac_s1=regval&mask;

	temp_string.Format(_T("%x"),spdac_s1);
	m_EDIT_SPDAC_S1.SetWindowText(temp_string);
	temp_cal = spdac_s1<<2;
	temp_float = temp_cal*0.3922;
    m_EDIT_SPDAC.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE); 


	regval = pParent->rreg(0x10);
    if (!success){goto end;};

	mask=1;
	var_dac_en=(regval>>6)&mask;
	mask=63;
	spdac_s2=regval&mask;

	temp_string.Format(_T("%x"),spdac_s2);
	m_EDIT_SPDAC_S2.SetWindowText(temp_string);
	temp_cal = spdac_s2<<2;
	temp_float = temp_cal*0.3922;
	m_EDIT_SPDAC2.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE); 
		
	
	regval = pParent->rreg(0x11);
    if (!success){goto end;};

	mask=63;
	spdac_s4=regval&mask;

	temp_string.Format(_T("%x"),spdac_s4);
	m_EDIT_SPDAC_S4.SetWindowText(temp_string);
	temp_cal = spdac_s4<<2;
	temp_float = temp_cal*0.3922;
    m_EDIT_SPDAC4.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE);  

	mask=1;
	pwm_freq_detail=(regval>>6)&mask;
	
	regval = pParent->rreg(0x12);
    if (!success){goto end;};

	mask=3;
	to_s3=(regval>>6)&mask;
	mask=7;
	to_s2=(regval>>3)&mask;
	to_s1=regval&mask;
	
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
	test_en2=regval&mask;
	max_speed_en=(regval>>1)&mask;
	uv_dis=(regval>>2)&mask;
	//reg_crc_chk_dis=(regval>>3)&mask;
		
	test_en = test_en2*2 + test_en1;

	if(pos_sns==0){	
		regval = pParent->rreg(0x15);
		if (!success){goto end;};

		m_EDIT_SUMOUT_FF_TEST.Format(_T("%x"),regval);
		UpdateData(FALSE);

		temp_int1 = pParent->dataread_anybits(0x17,4,4);
		if (!success){goto end;};
		temp_int2 = pParent->dataread_anybits(0x16,0,8);
		if (!success){goto end;};
		temp_cal = (temp_int1<<8)+temp_int2;
		m_EDIT_PWMIN_FINAL.Format(_T("%x"),temp_cal);
		UpdateData(FALSE);

		regval = pParent->rreg(0x19);
        if (!success){goto end;};

		mask=1;
		auto_spin_done=(regval>>7)&mask;
		mask=15;
		auto_spin_flt=(regval>>3)&mask;
		mask=7;
		rev=regval&mask;

		if(fan_en==1){	
			datbits = "1";
			pParent->dataupdate_anybits(0x01,3,datbits,1);
			datbits = "1";
			pParent->dataupdate_anybits(0x01,7,datbits,1);

			regval = pParent->rreg(0x15);
			if (!success){goto end;};

			mask=1;
			fan_en_off_brk=(regval>>7)&mask;
			mask=3;
			pwm_low=(regval>>2)&mask;
			pwm_float=regval&mask;

			datbits = "0";
			pParent->dataupdate_anybits(0x01,7,datbits,1);

			tpos_lsb = pParent->rreg(0x16);
			if (!success){goto end;};
			tpos_msb = pParent->rreg(0x17);
			if (!success){goto end;};
			temp_cal = (tpos_msb<<8)+tpos_lsb;
			m_EDIT_TPOS.Format(_T("%d"),temp_cal);
			UpdateData(FALSE); 

			datbits = "0";
			pParent->dataupdate_anybits(0x01,3,datbits,1);
		}else{
			if(scomm==0){
				datbits = "1";
				pParent->dataupdate_anybits(0x01,3,datbits,1);
				datbits = "1";
				pParent->dataupdate_anybits(0x01,7,datbits,1);

				regval = pParent->rreg(0x15);
				if (!success){goto end;};

				mask=1;
				fan_en_off_brk=(regval>>7)&mask;
				mask=3;
				pwm_low=(regval>>2)&mask;
				pwm_float=regval&mask;

				datbits = "0";
				pParent->dataupdate_anybits(0x01,7,datbits,1);

				tpos_lsb = pParent->rreg(0x16);
				if (!success){goto end;};
				tpos_msb = pParent->rreg(0x17);
				if (!success){goto end;};
				temp_cal = (tpos_msb<<8)+tpos_lsb;
				m_EDIT_TPOS.Format(_T("%d"),temp_cal);
				UpdateData(FALSE); 

				datbits = "0";
				pParent->dataupdate_anybits(0x01,3,datbits,1);
			}
		}

	}else if(pos_sns==1){
        datbits = "1";
		pParent->dataupdate_anybits(0x01,7,datbits,1);

		regval = pParent->rreg(0x15);
        if (!success){goto end;};

	    mask=1;
		fan_en_off_brk=(regval>>7)&mask;
		mask=3;
		pwm_low=(regval>>2)&mask;
		pwm_float=regval&mask;

		datbits = "0";
		pParent->dataupdate_anybits(0x01,7,datbits,1);

		tpos_lsb = pParent->rreg(0x16);
		if (!success){goto end;};
		tpos_msb = pParent->rreg(0x17);
        if (!success){goto end;};
		temp_cal = (tpos_msb<<8)+tpos_lsb;
		m_EDIT_TPOS.Format(_T("%d"),temp_cal);
		UpdateData(FALSE); 

		regval = pParent->rreg(0x19);
        if (!success){goto end;};

		mask=1;
		auto_spin_done=(regval>>7)&mask;
		mask=15;
		auto_spin_flt=(regval>>3)&mask;
		mask=7;
		rev=regval&mask;

		datbits = "0";
		pParent->dataupdate_anybits(0x01,3,datbits,1);

		regval = pParent->rreg(0x15);
		if (!success){goto end;};

		m_EDIT_SUMOUT_FF_TEST.Format(_T("%x"),regval);
		UpdateData(FALSE);

		temp_int1 = pParent->dataread_anybits(0x17,4,4);
		if (!success){goto end;};
		temp_int2 = pParent->dataread_anybits(0x16,0,8);
		if (!success){goto end;};
		temp_cal = (temp_int1<<8)+temp_int2;
		m_EDIT_PWMIN_FINAL.Format(_T("%x"),temp_cal);
		UpdateData(FALSE);

		regval = pParent->rreg(0x19);
        if (!success){goto end;};
        
		m_EDIT_SUMOUT_FF.Format(_T("%x"),regval);
		UpdateData(FALSE);
		rev=regval&mask;

		datbits = "1";
		pParent->dataupdate_anybits(0x01,3,datbits,1);
	}
	
		
		regval = pParent->rreg(0x18);
		if (!success){goto end;};

		mask=255;
		dac=regval&mask;

		temp_string.Format(_T("%x"),dac);
		m_EDIT_WDAC.SetWindowText(temp_string);
		temp_float = dac*0.3922;
		m_EDIT_DAC.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);  

		datbits = "1";
		pParent->dataupdate_anybits(0x01,7,datbits,1);
		regval = pParent->rreg(0x18);
		if (!success){goto end;};

		mask=1;
		pwm_float_dis=(regval>>7)&mask;
		retry_tristate=(regval>>2)&mask;
		retry_ilim_brk=(regval>>1)&mask;
		mask=3;
		profile_sel=(regval>>4)&mask;
        
		datbits = "0";
		pParent->dataupdate_anybits(0x01,7,datbits,1);

		/*if(profile_sel==0){
			m_EDIT_MID.EnableWindow(0);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(0);
			m_EDIT_MT2.EnableWindow(0);
		}else if(profile_sel==2){
            m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(1);
			m_EDIT_MT2.EnableWindow(0);
		}else{
			m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(1);
			m_EDIT_MT1.EnableWindow(1);
			m_EDIT_MT2.EnableWindow(1);
		}*/



	regval = pParent->rreg(0x1a);
    if (!success){goto end;};

	mask=1;
	otp1done=(regval>>5)&mask;
	otpcaldone=(regval>>4)&mask;
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
	     
	             m_EDIT_REV.Format(_T("%d"),rev);
	             UpdateData(FALSE);
				
	             if(auto_spin_flt==0){
					 m_EDIT_SPIN_FLT.Format(_T("0: no fault"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==1){
                     m_EDIT_SPIN_FLT.Format(_T("1: ind_sense"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==2){
					 m_EDIT_SPIN_FLT.Format(_T("2: mancomm timeout"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==3){
					 m_EDIT_SPIN_FLT.Format(_T("3: handover timeout"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==4){
					 m_EDIT_SPIN_FLT.Format(_T("4: S4 min speed"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==5){
					 m_EDIT_SPIN_FLT.Format(_T("5: S5 min speed"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==6){
					 m_EDIT_SPIN_FLT.Format(_T("6: S6 min speed"));
					 UpdateData(FALSE);
				 }else if(auto_spin_flt==7){
					 m_EDIT_SPIN_FLT.Format(_T("7: sdisrupt"));
					 UpdateData(FALSE);
				 }else{
                     m_EDIT_SPIN_FLT.Format(_T("-NA-"));
					 UpdateData(FALSE);
				 }

				if(no_sysclk == 0){
	 	              m_EDIT_NO_SYSCLK.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else {
		              m_EDIT_NO_SYSCLK.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
	             if(tshut == 0){
		              m_EDIT_TSHUT.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TSHUT.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(twarn == 0){
		              m_EDIT_TWARN.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TWARN.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(bc == 0){
		              m_EDIT_BC.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_BC.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(tfreeze_in == 0){
		              m_EDIT_TFREEZE_IN.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else{
		              m_EDIT_TFREEZE_IN.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }  
				 if(otpcaldone == 0){
		              m_CHECK_OTPCAL_DONE.SetCheck(0);
	             }else{
		              m_CHECK_OTPCAL_DONE.SetCheck(1);
	             }  
				 if(otp1done == 0){
		              m_CHECK_OTP1DONE.SetCheck(0);
	             }else{
		              m_CHECK_OTP1DONE.SetCheck(1);
	             }  
   
    if(pwm_reg_sel == 1){
		CheckRadioButton(IDC_RADIO_PWMREG_SEL,IDC_RADIO_EXTDAC_SEL,IDC_RADIO_PWMREG_SEL);
    }
	
	if(pwm_reg_sel == 0 && pwm_in_select == 1){
		CheckRadioButton(IDC_RADIO_PWMREG_SEL,IDC_RADIO_EXTDAC_SEL,IDC_RADIO_PWMIN_SEL);
	}

	if(pwm_reg_sel == 0 && pwm_in_select == 0){
		CheckRadioButton(IDC_RADIO_PWMREG_SEL,IDC_RADIO_EXTDAC_SEL,IDC_RADIO_EXTDAC_SEL);
	}

	
	if(blind_spin_en == 0){
		CheckRadioButton(IDC_RADIO_BLIND_SPIN_DIS,IDC_RADIO_BLIND_SPIN_EN,IDC_RADIO_BLIND_SPIN_DIS);
	}else if(blind_spin_en ==1){
		CheckRadioButton(IDC_RADIO_BLIND_SPIN_DIS,IDC_RADIO_BLIND_SPIN_EN,IDC_RADIO_BLIND_SPIN_EN);
	}

	regval = pParent->rreg(0x1b);
    if (!success){goto end;};

	mask=31;
	osc_offset=regval&mask;
    mask=7;
	osc_tc=(regval>>5)&mask;
	
	regval = pParent->rreg(0x1c);
    if (!success){goto end;};
    
	
	mask=15;
	tachpin=(regval>>4)&mask;
	tachpin_sel=tachpin+(tachpin_inv<<4);
    mask=3;
	pwmin_stop_level=(regval>>2)&mask;
    ilimit_gain=regval&mask;

	regval = pParent->rreg(0x1d);
    if (!success){goto end;};

	mask=255;
	refcount1=regval&mask;

	regval = pParent->rreg(0x1e);
    if (!success){goto end;};

	mask=255;
	refcount2=regval&mask;

	refcount=(refcount2<<8)+refcount1;

	regval = pParent->rreg(0x1f);
    if (!success){goto end;};

	mask=3;
	offmsk=(regval>>6)&mask;
	pwmin_low_time=(regval>>1)&mask;
	mask=7;
	sdisrupt=(regval>>3)&mask;
	mask=1;
	tor_hys_dis=regval&mask;

	regval = pParent->rreg(0x20);
    if (!success){goto end;};

	minsp=regval;

	temp_string.Format(_T("%x"),minsp);
	m_EDIT_MINSP.SetWindowText(temp_string);
	temp_cal=minsp*0.39216;
	m_EDIT_MINSP_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE);

	regval = pParent->rreg(0x22);
    if (!success){goto end;};

	mask=3;
	pwmin_fs=(regval>>6)&mask;

	regval = pParent->rreg(0x23);
    if (!success){goto end;};

	low=regval;
	
	temp_string.Format(_T("%x"),low);
	m_EDIT_LOW.SetWindowText(temp_string);
	temp_cal=low*0.39216;
	m_EDIT_LOW_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE);

	regval = pParent->rreg(0x24);
    if (!success){goto end;};

	ht=regval;

	temp_string.Format(_T("%x"),ht);
	m_EDIT_HT.SetWindowText(temp_string);
	temp_cal=ht*0.39216;
	m_EDIT_HT_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 
	
	regval = pParent->rreg(0x25);
    if (!success){goto end;};

	lt=regval;

	temp_string.Format(_T("%x"),lt);
	m_EDIT_LT.SetWindowText(temp_string);
	temp_cal=lt*0.39216;
	m_EDIT_LT_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 

	regval = pParent->rreg(0x26);
    if (!success){goto end;};

	//mt1=regval&mask;
	mt1=regval;
	temp_string.Format(_T("%x"),mt1);
	m_EDIT_MT1.SetWindowText(temp_string);
	temp_cal=mt1*0.39216;
	m_EDIT_MIT1_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 

    regval = pParent->rreg(0x27);
    if (!success){goto end;};

	mid=regval;

	temp_string.Format(_T("%x"),mid);
	m_EDIT_MID.SetWindowText(temp_string);
	temp_cal=mid*0.39216;
	m_EDIT_MID_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 

	regval = pParent->rreg(0x28);
    if (!success) return;
	mindac_clamp = regval;
	temp_string.Format(_T("%x"),mindac_clamp);
	m_EDIT_MINDAC_CLAMP.SetWindowText(temp_string);
	temp_cal=mindac_clamp*0.39216;
	m_EDIT_MINDAC_CLAMP_RD.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 


	m_EDIT_MT2.SetWindowText(_T("0"));
	m_EDIT_MIT2_PERCENT.Format(_T("0%s"),"%");
	UpdateData(FALSE); 

	regval = pParent->rreg(0x29);
    if (!success){goto end;};

	mid2=regval;

	temp_string.Format(_T("%x"),mid2);
	m_EDIT_MID2.SetWindowText(temp_string);
	temp_cal=mid2*0.39216;
	m_EDIT_MID2_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 

	mapdac_read = int(double(((255-low)*(double(dac)/255)))+double(low));

	if(fourpp==0){
	 if(pole_pair==0){
		temp_string.Format(_T("%x"),refcount);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(refcount!=0){
			temp_float = 249023438/refcount;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(direct_spn==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					target_speed = (temp_float*mapdac_read)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),target_speed);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	}else if(pole_pair==1){
        temp_string.Format(_T("%x"),refcount);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(refcount!=0){
			temp_float = 166015625/refcount;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(direct_spn==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					target_speed = (temp_float*mapdac_read)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),target_speed);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
      }
	}else if(fourpp==1){
		temp_string.Format(_T("%x"),refcount);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(refcount!=0){
			temp_float = 124511719/refcount;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(direct_spn==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					target_speed = (temp_float*mapdac_read)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),target_speed);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	}else if(fourpp==2){
		temp_string.Format(_T("%x"),refcount);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(refcount!=0){
			temp_float = 498046876/refcount;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(direct_spn==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					target_speed = (temp_float*mapdac_read)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),target_speed);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	}

	updatesdisrupt();
	vardaccount();
	updateonmskacc();
	updatedelay();

	m_CHECK_FAN_EN.SetCheck(fan_en);
	m_CHECK_AD_TOR.SetCheck(ad_tor);
	m_CHECK_SYN_CLAMP.SetCheck(retry_disable);
	m_CHECK_VPWR_CLAMP.SetCheck(swap_bc);
	m_CHECK_SP_CNTL_EN.SetCheck(sp_cntl_en);
	m_CHECK_POS_SNS.SetCheck(pos_sns);
	m_CHECK_PMC_EN.SetCheck(pmc_en);
	m_CHECK_FAULT_SHUT.SetCheck(fault_shut_dis);
	m_CHECK_COM_SEL.SetCheck(pwm_inv);
	m_CHECK_6S_SIN.SetCheck(pwm_nonoverlap_dis);
	m_CHECK_TRISTATE.SetCheck(sp_tri);
	m_CHECK_3PH_DET.SetCheck(max_speed_en);
	m_CHECK_BEMF_FLT.SetCheck(bemf_fil_en);
	m_CHECK_SP_PWR.SetCheck(syn_clamp_dis);
	m_CHECK_VAR_DAC.SetCheck(var_dac_en);
	m_CHECK_BLIND_SPNACCEL.SetCheck(pwmin_low_stop);
	m_CHECK_FP_EN.SetCheck(uv_dis);
	//m_CHECK_PWM_FREQDIV.SetCheck(reg_crc_chk_dis);
	m_CHECK_OFFMSK_EN.SetCheck(offmsk_en);
	m_CHECK_TC_EXT.SetCheck(tc_ext);
	m_CHECK_TSHUT_DIS.SetCheck(triphase_det_en);
	//m_CHECK_OSCCAL_MAN.SetCheck(osc_cal_man);
	//m_CHECK_OSCCAL_AUTO.SetCheck(osc_cal_auto);
	m_CHECK_OSC_DIS.SetCheck(osc_dis);
	m_CHECK_SPIN_ACC.SetCheck(spin_acc);
	m_CHECK_CLKMON_EN.SetCheck(rev_torque);
	m_CHECK_USEREG.SetCheck(use_reg);
	m_CHECK_TSHUTDIS.SetCheck(tshutdis);
	m_CHECK_REG2P5FB_EN.SetCheck(reg2p5fb_en);
	m_CHECK_SLOW_RESPONSE.SetCheck(slow_response);
	m_CHECK_DLL_EN.SetCheck(dll_en);
	m_CHECK_FF_EN.SetCheck(ff_en);
	m_CHECK_FAN_EN_OFF_BRK.SetCheck(fan_en_off_brk);
	m_CHECK_PWM_FLOAT_DIS.SetCheck(pwm_float_dis);
	m_CHECK_DIRECT_SPN.SetCheck(direct_spn);
	m_CHECK_TOR_HYS_DIS.SetCheck(tor_hys_dis);
	m_CHECK_TACHPIN_INV.SetCheck(tachpin_inv);
	m_CHECK_RETRY_TRISTATE.SetCheck(retry_tristate);
	m_CHECK_RETRY_ILIM_BRK.SetCheck(retry_ilim_brk);
	m_COMBO_REG_OVERWR.SetCurSel(pwmin_low_time);
	m_COMBO_SCOMM.SetCurSel(scomm);
	m_COMBO_SDISRUPT_SEL.SetCurSel(sdisrupt);
	//m_COMBO_TACHO.SetCurSel(ph_detect);
	m_COMBO_S0S3_RPM.SetCurSel(s0s2_rpm);
	m_COMBO_TFREEZE.SetCurSel(pwmin_stop_level);
	m_COMBO_COMM_MASK.SetCurSel(comm_msk);
	m_COMBO_TORQUE_COARSE.SetCurSel(torque_coarse);
	m_COMBO_TORQUE_FINE.SetCurSel(torque_fine);
    m_COMBO_FREEZE_HYS.SetCurSel(frzhys);
	m_COMBO_BEMF_HYS.SetCurSel(bhys);
	m_COMBO_ILIMIT.SetCurSel(ilimit);
	m_COMBO_ILIMIT_AUTO.SetCurSel(ilimit_auto_is);
	m_COMBO_ILIMIT_BRAKE.SetCurSel(ilimit_brake);
	m_COMBO_OFF_MASK.SetCurSel(offmsk);
	m_COMBO_ON_MASK.SetCurSel(pwm_msk);
	m_COMBO_BLINDSPN_COUNT.SetCurSel(pwm_freq_detail);
	m_COMBO_S1_ISDELAY.SetCurSel(driver_non_overlap);
	m_COMBO_BLINDSPN_STEP.SetCurSel(onmsk_acc);
	m_COMBO_TS_INITBLIND.SetCurSel(handover_spd);
	m_COMBO_TS_INIT.SetCurSel(vardac_count);
	m_COMBO_TO_S3.SetCurSel(to_s3);
	m_COMBO_TS_IS.SetCurSel(ts);
	m_COMBO_TS_BLIND.SetCurSel(comm_msk_acc);
	m_COMBO_LOW_DAC.SetCurSel(to_s1);
	m_COMBO_MIN_DAC.SetCurSel(to_s2);
	m_COMBO_TESTMUX.SetCurSel(test_en);
	m_COMBO_OSC_TC.SetCurSel(six_sine);
	m_COMBO_OSC_OFFSET.SetCurSel(osc_offset);
	m_COMBO_OSCTC.SetCurSel(osc_tc);
	m_COMBO_POLE_PAIR.SetCurSel(pole_pair);
	m_COMBO_TESTMODE_00.SetCurSel(tmux);
	m_COMBO_TESTMODE_10.SetCurSel(tmux);
	m_COMBO_TESTMODE_101.SetCurSel(tmux);
	m_COMBO_TESTMODE_11.SetCurSel(tmux);
	m_COMBO_BBS_RANGE.SetCurSel(ilimit_gain);
	m_COMBO_SPIN_REV.SetCurSel(spin_rev);
	m_COMBO_SPIN_TIME.SetCurSel(spin_time);
	m_COMBO_SPIN_STEP.SetCurSel(spin_step);
	m_COMBO_SPIN_INIT.SetCurSel(spin_init);
	m_COMBO_TACHPIN_SEL.SetCurSel(tachpin_sel);
	m_COMBO_IS_DELAY.SetCurSel(is_delay);
	m_COMBO_OFF_MASK.SetCurSel(offmsk);
	m_COMBO_PWM_LOW_DETAIL.SetCurSel(pwm_low);
	m_COMBO_PWM_FLOAT_DETAIL.SetCurSel(pwm_float);
	m_COMBO_HT.SetCurSel(profile_sel);
	m_COMBO_PWMIN_FS.SetCurSel(pwmin_fs);
    OnBnClickedButtonRstatus();
	if (!success)
		return;

	// enable/disable otp bits
	if(otpcaldone==0){
		m_CHECK_DLL_EN.EnableWindow(1);
		m_CHECK_FF_EN.EnableWindow(1);
		m_CHECK_VAR_DAC.EnableWindow(1);
		m_CHECK_FAN_EN_OFF_BRK.EnableWindow(1);
		m_CHECK_PWM_FLOAT_DIS.EnableWindow(1);
		m_CHECK_RETRY_TRISTATE.EnableWindow(1);
		m_CHECK_RETRY_ILIM_BRK.EnableWindow(1);
		m_COMBO_HT.EnableWindow(1);
		m_COMBO_OSCTC.EnableWindow(1);
		m_COMBO_OSC_OFFSET.EnableWindow(1);
		m_COMBO_BLINDSPN_COUNT.EnableWindow(1);
		m_COMBO_PWM_LOW_DETAIL.EnableWindow(1);
		m_COMBO_PWM_FLOAT_DETAIL.EnableWindow(1);
	}else if(otpcaldone==1){
        m_CHECK_DLL_EN.EnableWindow(0);
		m_CHECK_FF_EN.EnableWindow(0);
		m_CHECK_VAR_DAC.EnableWindow(0);
		m_CHECK_FAN_EN_OFF_BRK.EnableWindow(0);
		m_CHECK_PWM_FLOAT_DIS.EnableWindow(0);
		m_CHECK_RETRY_TRISTATE.EnableWindow(0);
		m_CHECK_RETRY_ILIM_BRK.EnableWindow(0);
		m_COMBO_HT.EnableWindow(0);
		m_COMBO_OSCTC.EnableWindow(0);
		m_COMBO_OSC_OFFSET.EnableWindow(0);
		m_COMBO_BLINDSPN_COUNT.EnableWindow(0);
		m_COMBO_PWM_LOW_DETAIL.EnableWindow(0);
		m_COMBO_PWM_FLOAT_DETAIL.EnableWindow(0);
	};

	if(otp1done==0)
	{
		if(profile_sel==0){
			m_EDIT_MID.EnableWindow(0);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(0);
			m_EDIT_MT2.EnableWindow(0);
		}else if(profile_sel==2){
            m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(1);
			m_EDIT_MT2.EnableWindow(0);
		}else{
			m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(1);
			m_EDIT_MT1.EnableWindow(1);
			m_EDIT_MT2.EnableWindow(1);
		}
		m_EDIT_HT.EnableWindow(1);
		m_EDIT_LT.EnableWindow(1);
		m_EDIT_LOW.EnableWindow(1);
		m_EDIT_MINSP.EnableWindow(1);
		m_EDIT_HDAC.EnableWindow(1);
		m_EDIT_WIN.EnableWindow(1);
		m_EDIT_WINMSK_AUTO.EnableWindow(1);
		m_EDIT_WIN_MASK.EnableWindow(1);
		m_EDIT_PHASE_CNT.EnableWindow(1);
		m_EDIT_SPDAC_S1.EnableWindow(1);
		m_EDIT_SPDAC_S2.EnableWindow(1);
		m_EDIT_SPDAC_S4.EnableWindow(1);
		m_EDIT_REFCOUNT.EnableWindow(1);
		m_EDIT_REFSPEED.EnableWindow(1);
		m_CHECK_COM_SEL.EnableWindow(1);
		m_CHECK_SP_CNTL_EN.EnableWindow(1);
		m_CHECK_CLKMON_EN.EnableWindow(1);
		m_CHECK_OFFMSK_EN.EnableWindow(1);
		m_CHECK_SPIN_ACC.EnableWindow(1);
		m_CHECK_TOR_HYS_DIS.EnableWindow(1);
		m_CHECK_TACHPIN_INV.EnableWindow(1);
		m_COMBO_OSC_TC.EnableWindow(1);
		m_COMBO_BEMF_HYS.EnableWindow(1);
		m_COMBO_COMM_MASK.EnableWindow(1);
		m_COMBO_ON_MASK.EnableWindow(1);
		m_COMBO_TS_BLIND.EnableWindow(1);
		m_COMBO_BLINDSPN_STEP.EnableWindow(1);
		m_COMBO_POLE_PAIR.EnableWindow(1);
		m_COMBO_S0S3_RPM.EnableWindow(1);
		m_COMBO_TS_INIT.EnableWindow(1);
		m_COMBO_TS_INITBLIND.EnableWindow(1);
		m_COMBO_ILIMIT.EnableWindow(1);
		m_COMBO_ILIMIT_AUTO.EnableWindow(1);
		m_COMBO_SPIN_STEP.EnableWindow(1);
		m_COMBO_TS_IS.EnableWindow(1);
		m_COMBO_SPIN_TIME.EnableWindow(1);
		m_COMBO_SPIN_INIT.EnableWindow(1);
		m_COMBO_IS_DELAY.EnableWindow(1);
		m_COMBO_SPIN_REV.EnableWindow(1);
		m_COMBO_S1_ISDELAY.EnableWindow(1);
		m_COMBO_TO_S3.EnableWindow(1);
		m_COMBO_MIN_DAC.EnableWindow(1);
		m_COMBO_LOW_DAC.EnableWindow(1);
		m_COMBO_TACHPIN_SEL.EnableWindow(1);
		m_COMBO_TFREEZE.EnableWindow(1);
		m_COMBO_BBS_RANGE.EnableWindow(1);
		m_COMBO_OFF_MASK.EnableWindow(1);
		m_COMBO_SDISRUPT_SEL.EnableWindow(1);
		m_COMBO_REG_OVERWR.EnableWindow(1);
		m_COMBO_PWMIN_FS.EnableWindow(1);
		m_EDIT_MINDAC_CLAMP.EnableWindow(1);

	}else if(otp1done==1&&use_reg==1){
		if(profile_sel==0){
			m_EDIT_MID.EnableWindow(0);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(0);
			m_EDIT_MT2.EnableWindow(0);
		}else if(profile_sel==2){
            m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(1);
			m_EDIT_MT2.EnableWindow(0);
		}else{
			m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(1);
			m_EDIT_MT1.EnableWindow(1);
			m_EDIT_MT2.EnableWindow(1);
		}
		m_EDIT_HT.EnableWindow(1);
		m_EDIT_LT.EnableWindow(1);
        m_EDIT_LOW.EnableWindow(1);
		m_EDIT_MINSP.EnableWindow(1);
		m_EDIT_HDAC.EnableWindow(1);
		m_EDIT_WIN.EnableWindow(1);
		m_EDIT_WINMSK_AUTO.EnableWindow(1);
		m_EDIT_WIN_MASK.EnableWindow(1);
		m_EDIT_PHASE_CNT.EnableWindow(1);
		m_EDIT_SPDAC_S1.EnableWindow(1);
		m_EDIT_SPDAC_S2.EnableWindow(1);
		m_EDIT_SPDAC_S4.EnableWindow(1);
		m_EDIT_REFCOUNT.EnableWindow(1);
		m_EDIT_REFSPEED.EnableWindow(1);
		m_CHECK_COM_SEL.EnableWindow(1);
		m_CHECK_SP_CNTL_EN.EnableWindow(1);
		m_CHECK_CLKMON_EN.EnableWindow(1);
		m_CHECK_OFFMSK_EN.EnableWindow(1);
		m_CHECK_SPIN_ACC.EnableWindow(1);
		m_CHECK_TOR_HYS_DIS.EnableWindow(1);
		m_CHECK_TACHPIN_INV.EnableWindow(1);
		m_COMBO_OSC_TC.EnableWindow(1);
		//m_COMBO_HT.EnableWindow(1);
		m_COMBO_LT.EnableWindow(1);
		m_COMBO_MT.EnableWindow(1);
		m_COMBO_BEMF_HYS.EnableWindow(1);
		m_COMBO_COMM_MASK.EnableWindow(1);
		m_COMBO_ON_MASK.EnableWindow(1);
		m_COMBO_TS_BLIND.EnableWindow(1);
		m_COMBO_BLINDSPN_STEP.EnableWindow(1);
		m_COMBO_POLE_PAIR.EnableWindow(1);
		m_COMBO_S0S3_RPM.EnableWindow(1);
		m_COMBO_TS_INIT.EnableWindow(1);
		m_COMBO_TS_INITBLIND.EnableWindow(1);
		m_COMBO_ILIMIT.EnableWindow(1);
		m_COMBO_ILIMIT_AUTO.EnableWindow(1);
		m_COMBO_SPIN_STEP.EnableWindow(1);
		m_COMBO_TS_IS.EnableWindow(1);
		m_COMBO_SPIN_TIME.EnableWindow(1);
		m_COMBO_SPIN_INIT.EnableWindow(1);
		m_COMBO_IS_DELAY.EnableWindow(1);
		m_COMBO_SPIN_REV.EnableWindow(1);
		m_COMBO_S1_ISDELAY.EnableWindow(1);
		m_COMBO_TO_S3.EnableWindow(1);
		m_COMBO_MIN_DAC.EnableWindow(1);
		m_COMBO_LOW_DAC.EnableWindow(1);
		m_COMBO_TACHPIN_SEL.EnableWindow(1);
		m_COMBO_TFREEZE.EnableWindow(1);
		m_COMBO_BBS_RANGE.EnableWindow(1);
		m_COMBO_OFF_MASK.EnableWindow(1);
		m_COMBO_SDISRUPT_SEL.EnableWindow(1);
		m_COMBO_REG_OVERWR.EnableWindow(1);
		m_COMBO_PWMIN_FS.EnableWindow(1);
		m_EDIT_MINDAC_CLAMP.EnableWindow(1);
	}else if(otp1done==1&&use_reg==0){
			m_EDIT_MID.EnableWindow(0);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(0);
			m_EDIT_MT2.EnableWindow(0);
		m_EDIT_HT.EnableWindow(0);
		m_EDIT_LT.EnableWindow(0);
		m_EDIT_MINSP.EnableWindow(0);
		m_EDIT_MID.EnableWindow(0);
		m_EDIT_MID2.EnableWindow(0);
		m_EDIT_MT1.EnableWindow(0);
		m_EDIT_MT2.EnableWindow(0);
        m_EDIT_LOW.EnableWindow(0);
		m_EDIT_MID.EnableWindow(0);
		m_EDIT_MINSP.EnableWindow(0);
		m_EDIT_HDAC.EnableWindow(0);
		m_EDIT_WIN.EnableWindow(0);
		m_EDIT_WINMSK_AUTO.EnableWindow(0);
		m_EDIT_WIN_MASK.EnableWindow(0);
		m_EDIT_PHASE_CNT.EnableWindow(0);
		m_EDIT_SPDAC_S1.EnableWindow(0);
		m_EDIT_SPDAC_S2.EnableWindow(0);
		m_EDIT_SPDAC_S4.EnableWindow(0);
		m_EDIT_REFCOUNT.EnableWindow(0);
		m_EDIT_REFSPEED.EnableWindow(0);
		m_CHECK_COM_SEL.EnableWindow(0);
		m_CHECK_SP_CNTL_EN.EnableWindow(0);
		m_CHECK_CLKMON_EN.EnableWindow(0);
		m_CHECK_OFFMSK_EN.EnableWindow(0);
		m_CHECK_SPIN_ACC.EnableWindow(0);
		m_CHECK_TOR_HYS_DIS.EnableWindow(0);
		m_CHECK_TACHPIN_INV.EnableWindow(0);
		m_COMBO_OSC_TC.EnableWindow(0);
		//m_COMBO_HT.EnableWindow(0);
		m_COMBO_LT.EnableWindow(0);
		m_COMBO_MT.EnableWindow(0);
		m_COMBO_BEMF_HYS.EnableWindow(0);
		m_COMBO_COMM_MASK.EnableWindow(0);
		m_COMBO_ON_MASK.EnableWindow(0);
		m_COMBO_TS_BLIND.EnableWindow(0);
		m_COMBO_BLINDSPN_STEP.EnableWindow(0);
		m_COMBO_POLE_PAIR.EnableWindow(0);
		m_COMBO_S0S3_RPM.EnableWindow(0);
		m_COMBO_TS_INIT.EnableWindow(0);
		m_COMBO_TS_INITBLIND.EnableWindow(0);
		m_COMBO_ILIMIT.EnableWindow(0);
		m_COMBO_ILIMIT_AUTO.EnableWindow(0);
		m_COMBO_SPIN_STEP.EnableWindow(0);
		m_COMBO_TS_IS.EnableWindow(0);
		m_COMBO_SPIN_TIME.EnableWindow(0);
		m_COMBO_SPIN_INIT.EnableWindow(0);
		m_COMBO_IS_DELAY.EnableWindow(0);
		m_COMBO_SPIN_REV.EnableWindow(0);
		m_COMBO_S1_ISDELAY.EnableWindow(0);
		m_COMBO_TO_S3.EnableWindow(0);
		m_COMBO_MIN_DAC.EnableWindow(0);
		m_COMBO_LOW_DAC.EnableWindow(0);
		m_COMBO_TACHPIN_SEL.EnableWindow(0);
		m_COMBO_TFREEZE.EnableWindow(0);
		m_COMBO_BBS_RANGE.EnableWindow(0);
		m_COMBO_OFF_MASK.EnableWindow(0);
		m_COMBO_SDISRUPT_SEL.EnableWindow(0);
		m_COMBO_REG_OVERWR.EnableWindow(0);
		m_COMBO_PWMIN_FS.EnableWindow(0);
		m_EDIT_MINDAC_CLAMP.EnableWindow(0);
	};
	end:;  
}

void CdetailDlg::OnBnClickedCheckSpCntlEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SP_CNTL_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,1,datbits,1);
	vardaccount();
}

	
void CdetailDlg::OnBnClickedCheckFanEn()
{
	static BOOL check = FALSE;
	CString datbits;
	int datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_FAN_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,0,datbits,1);
	datbit=pParent->dataread_anybits(0x04,0,1);
	m_CHECK_FAN_EN.SetCheck(datbit);
}

void CdetailDlg::OnBnClickedCheckSynClamp() //retry_disable
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SYN_CLAMP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,6,datbits,1);
}

void CdetailDlg::OnBnClickedCheckVpwrClamp()  //swap_bc - spare bit - hide
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_VPWR_CLAMP.GetCheck();
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,5,datbits,1);
}

void CdetailDlg::OnBnClickedCheckPosSns()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_POS_SNS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,3,datbits,1);
}

void CdetailDlg::OnBnClickedCheckPmcEn()
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

void CdetailDlg::OnBnClickedCheckFaultShut()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_FAULT_SHUT.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x02,2,datbits,1);
}

void CdetailDlg::OnBnClickedCheckComSel()   //pwm_inv
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_COM_SEL.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x09,0,datbits,1);
}

void CdetailDlg::OnBnClickedCheck6sSin()   // PWM_NONOVERLAP_DIS
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_6S_SIN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x0b,0,datbits,1);
}

void CdetailDlg::OnBnClickedCheckTristate()
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

void CdetailDlg::OnBnClickedCheck3phDet()  // max_speed_en
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_3PH_DET.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x14,6,datbits,1);
}

void CdetailDlg::OnBnClickedCheckBemfFlt()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_BEMF_FLT.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,2,datbits,1);
}

void CdetailDlg::OnBnClickedCheckSpPwr() //syn_clamp_dis
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SP_PWR.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x05,7,datbits,1);
}

void CdetailDlg::OnBnClickedCheckVarDac()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_VAR_DAC.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x10,1,datbits,1);
}

void CdetailDlg::OnBnClickedCheckBlindSpnaccel()  //pwmin_low_stop
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_BLIND_SPNACCEL.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x09,1,datbits,1);
}

void CdetailDlg::OnBnClickedCheckFpEn()  //UV_DIS
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_FP_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x14,5,datbits,1);
	//tfreeze_dropdownlist();
}

/*void CdetailDlg::OnBnClickedCheckPwmFreqdiv()  // REG_CRC_CHK_DIS
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_PWM_FREQDIV.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x14,4,datbits,1); 
}*/

void CdetailDlg::OnBnClickedCheckDirectSpn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_DIRECT_SPN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,6,datbits,1);

	OnBnClickedButtonRefcount();
}


void CdetailDlg::OnBnClickedCheckOffmskEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_OFFMSK_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x06,7,datbits,1);
}

void CdetailDlg::OnBnClickedCheckClkmonEn()   //Reverse_torque
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_CLKMON_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x05,6,datbits,1);
	torque_update();
}

void CdetailDlg::OnBnClickedCheckTcExt()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TC_EXT.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x13,0,datbits,1);
}

void CdetailDlg::OnBnClickedCheckTshutDis()   // triphase_det_en
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TSHUT_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x08,0,datbits,1);
}

void CdetailDlg::OnBnClickedCheckOsccalMan()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_OSCCAL_MAN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x13,4,datbits,1);
}

void CdetailDlg::OnBnClickedCheckOsccalAuto()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_OSCCAL_AUTO.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x13,5,datbits,1);
}

void CdetailDlg::OnBnClickedCheckOscDis()
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

void CdetailDlg::OnBnClickedCheckAdTor()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_AD_TOR.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,4,datbits,1);
}

void CdetailDlg::OnBnClickedCheckTorHysDis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TOR_HYS_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x1f,7,datbits,1);
}

void CdetailDlg::OnBnClickedCheckTshutdis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TSHUTDIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x02,4,datbits,1);
}

void CdetailDlg::OnBnClickedCheckReg2p5fbEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_REG2P5FB_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x02,5,datbits,1);
}

void CdetailDlg::OnBnClickedCheckSlowResponse()
{
	/*static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_SLOW_RESPONSE.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x1e,2,datbits,1);*/
}

void CdetailDlg::OnBnClickedCheckDllEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_DLL_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,4,datbits,1);
}

void CdetailDlg::OnBnClickedCheckFfEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_FF_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,5,datbits,1);
}

void CdetailDlg::OnBnClickedCheckFfS6En()  
{
/*	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_FF_S6_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,7,datbits,1);*/
}

void CdetailDlg::OnBnClickedCheckTachpinInv()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_TACHPIN_INV.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x04,7,datbits,1);
}

void CdetailDlg::OnBnClickedCheckLevelOverflow()
{
/*	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_LEVEL_OVERFLOW.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x1e,6,datbits,1);*/
}

void CdetailDlg::OnBnClickedCheckUsereg()
{
	static BOOL check = FALSE;
	CString datbits;
	int seln1,seln2,seln3;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	if (pParent->virtual_board)
	{
		//check if otp1 already
		int temp=pParent->rreg(0x1a);
		temp=(temp&0x20)>>5;
		if (temp)//OTP1_done=1
		{
			check = m_CHECK_USEREG.GetCheck();
			if(check == TRUE)
			{
				pParent->fOTP = 0;
			}
			else if(check == FALSE)
			{
				pParent->fOTP = 1;
			}
		}

	}

	check = m_CHECK_USEREG.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
		
	}else if(check == FALSE){
		datbits = "0";
		
	}
	
	pParent->dataupdate_anybits(0x02,6,datbits,1);
	seln1=pParent->dataread_anybits(0x18,2,2);  //profile_sel
	//seln1=pParent->dataread_anybits(0x18,2,1);  //profile_sel
	seln2=pParent->dataread_anybits(0x1a,2,1);  //otp1_done
    seln3=pParent->dataread_anybits(0x02,6,1);  //use_reg

	if(seln2==1&&seln3==1){
		if(seln1==0){
			m_EDIT_MID.EnableWindow(0);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(0);
			//m_EDIT_MT2.EnableWindow(0);
		}else if(seln1==2){
            m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(1);
			//m_EDIT_MT2.EnableWindow(0);
		}else{
			m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(1);
			m_EDIT_MT1.EnableWindow(1);
			//m_EDIT_MT2.EnableWindow(1);
		}
		m_EDIT_HT.EnableWindow(1);
		m_EDIT_LT.EnableWindow(1);
        m_EDIT_LOW.EnableWindow(1);
		m_EDIT_MINSP.EnableWindow(1);
		m_EDIT_HDAC.EnableWindow(1);
		m_EDIT_WIN.EnableWindow(1);
		m_EDIT_WINMSK_AUTO.EnableWindow(1);
		m_EDIT_WIN_MASK.EnableWindow(1);
		m_EDIT_PHASE_CNT.EnableWindow(1);
		m_EDIT_SPDAC_S1.EnableWindow(1);
		m_EDIT_SPDAC_S2.EnableWindow(1);
		m_EDIT_SPDAC_S4.EnableWindow(1);
		m_EDIT_REFCOUNT.EnableWindow(1);
		m_EDIT_REFSPEED.EnableWindow(1);
		m_CHECK_COM_SEL.EnableWindow(1);
		m_CHECK_SP_CNTL_EN.EnableWindow(1);
		m_CHECK_CLKMON_EN.EnableWindow(1);
		m_CHECK_OFFMSK_EN.EnableWindow(1);
		m_CHECK_SPIN_ACC.EnableWindow(1);
		m_CHECK_TOR_HYS_DIS.EnableWindow(1);
		m_CHECK_TACHPIN_INV.EnableWindow(1);
		m_COMBO_OSC_TC.EnableWindow(1);
		//m_COMBO_HT.EnableWindow(1);
		m_COMBO_LT.EnableWindow(1);
		m_COMBO_MT.EnableWindow(1);
		m_COMBO_BEMF_HYS.EnableWindow(1);
		m_COMBO_COMM_MASK.EnableWindow(1);
		m_COMBO_ON_MASK.EnableWindow(1);
		m_COMBO_TS_BLIND.EnableWindow(1);
		m_COMBO_BLINDSPN_STEP.EnableWindow(1);
		m_COMBO_POLE_PAIR.EnableWindow(1);
		m_COMBO_S0S3_RPM.EnableWindow(1);
		m_COMBO_TS_INIT.EnableWindow(1);
		m_COMBO_TS_INITBLIND.EnableWindow(1);
		m_COMBO_ILIMIT.EnableWindow(1);
		m_COMBO_ILIMIT_AUTO.EnableWindow(1);
		m_COMBO_SPIN_STEP.EnableWindow(1);
		m_COMBO_TS_IS.EnableWindow(1);
		m_COMBO_SPIN_TIME.EnableWindow(1);
		m_COMBO_SPIN_INIT.EnableWindow(1);
		m_COMBO_IS_DELAY.EnableWindow(1);
		m_COMBO_SPIN_REV.EnableWindow(1);
		m_COMBO_S1_ISDELAY.EnableWindow(1);
		m_COMBO_TO_S3.EnableWindow(1);
		m_COMBO_MIN_DAC.EnableWindow(1);
		m_COMBO_LOW_DAC.EnableWindow(1);
		m_COMBO_TACHPIN_SEL.EnableWindow(1);
		m_COMBO_TFREEZE.EnableWindow(1);
		m_COMBO_BBS_RANGE.EnableWindow(1);
		m_COMBO_OFF_MASK.EnableWindow(1);
		m_COMBO_SDISRUPT_SEL.EnableWindow(1);
		m_COMBO_REG_OVERWR.EnableWindow(1);
		m_COMBO_PWMIN_FS.EnableWindow(1);
	}else if(seln2==1&&seln3==0){
		m_EDIT_HT.EnableWindow(0);
		m_EDIT_LT.EnableWindow(0);
		m_EDIT_MID2.EnableWindow(0);
		m_EDIT_MT1.EnableWindow(0);
		//m_EDIT_MT2.EnableWindow(0);
        m_EDIT_LOW.EnableWindow(0);
		m_EDIT_MID.EnableWindow(0);
		m_EDIT_MINSP.EnableWindow(0);
		m_EDIT_HDAC.EnableWindow(0);
		m_EDIT_WIN.EnableWindow(0);
		m_EDIT_WINMSK_AUTO.EnableWindow(0);
		m_EDIT_WIN_MASK.EnableWindow(0);
		m_EDIT_PHASE_CNT.EnableWindow(0);
		m_EDIT_SPDAC_S1.EnableWindow(0);
		m_EDIT_SPDAC_S2.EnableWindow(0);
		m_EDIT_SPDAC_S4.EnableWindow(0);
		m_EDIT_REFCOUNT.EnableWindow(0);
		m_EDIT_REFSPEED.EnableWindow(0);
		m_CHECK_COM_SEL.EnableWindow(0);
		m_CHECK_SP_CNTL_EN.EnableWindow(0);
		m_CHECK_CLKMON_EN.EnableWindow(0);
		m_CHECK_OFFMSK_EN.EnableWindow(0);
		m_CHECK_SPIN_ACC.EnableWindow(0);
		m_CHECK_TOR_HYS_DIS.EnableWindow(0);
		m_CHECK_TACHPIN_INV.EnableWindow(0);
		m_COMBO_OSC_TC.EnableWindow(0);
		//m_COMBO_HT.EnableWindow(0);
		m_COMBO_LT.EnableWindow(0);
		m_COMBO_MT.EnableWindow(0);
		m_COMBO_BEMF_HYS.EnableWindow(0);
		m_COMBO_COMM_MASK.EnableWindow(0);
		m_COMBO_ON_MASK.EnableWindow(0);
		m_COMBO_TS_BLIND.EnableWindow(0);
		m_COMBO_BLINDSPN_STEP.EnableWindow(0);
		m_COMBO_POLE_PAIR.EnableWindow(0);
		m_COMBO_S0S3_RPM.EnableWindow(0);
		m_COMBO_TS_INIT.EnableWindow(0);
		m_COMBO_TS_INITBLIND.EnableWindow(0);
		m_COMBO_ILIMIT.EnableWindow(0);
		m_COMBO_ILIMIT_AUTO.EnableWindow(0);
		m_COMBO_SPIN_STEP.EnableWindow(0);
		m_COMBO_TS_IS.EnableWindow(0);
		m_COMBO_SPIN_TIME.EnableWindow(0);
		m_COMBO_SPIN_INIT.EnableWindow(0);
		m_COMBO_IS_DELAY.EnableWindow(0);
		m_COMBO_SPIN_REV.EnableWindow(0);
		m_COMBO_S1_ISDELAY.EnableWindow(0);
		m_COMBO_TO_S3.EnableWindow(0);
		m_COMBO_MIN_DAC.EnableWindow(0);
		m_COMBO_LOW_DAC.EnableWindow(0);
		m_COMBO_TACHPIN_SEL.EnableWindow(0);
		m_COMBO_TFREEZE.EnableWindow(0);
		m_COMBO_BBS_RANGE.EnableWindow(0);
		m_COMBO_OFF_MASK.EnableWindow(0);
		m_COMBO_SDISRUPT_SEL.EnableWindow(0);
		m_COMBO_REG_OVERWR.EnableWindow(0);
		m_COMBO_PWMIN_FS.EnableWindow(0);
	};
}

void CdetailDlg::OnBnClickedCheckFanEnOffBrk()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_FAN_EN_OFF_BRK.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x15,0,datbits,1);
}

void CdetailDlg::OnCbnSelchangeComboRegOverwr()  //pwmin_low_time
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_REG_OVERWR.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x1f,5,datbits,2);
}


void CdetailDlg::OnCbnSelchangeComboScomm()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_SCOMM.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x03,0,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboTacho()  // ph_detect
{
	/*int seln;
	CString datbits;

	seln = m_COMBO_TACHO.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x02,6,datbits,1);*/
}

void CdetailDlg::OnCbnSelchangeComboS0s3Rpm()  //s0s2_rpm
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_S0S3_RPM.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x07,7,datbits,1);
}

void CdetailDlg::OnCbnSelchangeComboTfreeze()  //PWMIN_STOP_LEVEL
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TFREEZE.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x1c,4,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboPwminFs()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PWMIN_FS.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x22,0,datbits,2);
}

void CdetailDlg::tfreeze_dropdownlist()
{
	static BOOL check = FALSE;
	int sel_tfreeze;
	CString datbits;
	CString lt_tfreeze0,lt_tfreeze1,lt_tfreeze2,lt_tfreeze3,lt_tfreeze4,lt_tfreeze5,lt_tfreeze6,lt_tfreeze7;
	
	check = m_CHECK_FP_EN.GetCheck();
	
	if(check == FALSE ){
		lt_tfreeze0 = "0h: 0 us";lt_tfreeze1 = "1h: 6.6 us";lt_tfreeze2 = "2h: 13.2 us";lt_tfreeze3 = "3h: 26.4 us";
		lt_tfreeze4 = "4h: 39.6 us";lt_tfreeze5 = "5h: 52.8 us";lt_tfreeze6 = "6h: 60.7 us";lt_tfreeze7 = "7h: 66 us";
	}else if(check == TRUE){
		lt_tfreeze0 = "0h: 0 us";lt_tfreeze1 = "1h: 4 us";lt_tfreeze2 = "2h: 8 us";lt_tfreeze3 = "3h: 12 us";
		lt_tfreeze4 = "4h: 16 us";lt_tfreeze5 = "5h: 20 us";lt_tfreeze6 = "6h: 24 us";lt_tfreeze7 = "7h: 28 us";
	}

	sel_tfreeze = m_COMBO_TFREEZE.GetCurSel();

	//set dropdown list for tfreeze
	m_COMBO_TFREEZE.ResetContent();
	m_COMBO_TFREEZE.InsertString(0, lt_tfreeze0 );
	m_COMBO_TFREEZE.InsertString(1, lt_tfreeze1 );
	m_COMBO_TFREEZE.InsertString(2, lt_tfreeze2 );
	m_COMBO_TFREEZE.InsertString(3, lt_tfreeze3 );
	m_COMBO_TFREEZE.InsertString(4, lt_tfreeze4 );
	m_COMBO_TFREEZE.InsertString(5, lt_tfreeze5 );
	m_COMBO_TFREEZE.InsertString(6, lt_tfreeze6 );
	m_COMBO_TFREEZE.InsertString(7, lt_tfreeze7 );

	m_COMBO_TFREEZE.SetCurSel(sel_tfreeze);
}

void CdetailDlg::OnCbnSelchangeComboCommMask()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_COMM_MASK.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x06,0,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboTorqueCoarse()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TORQUE_COARSE.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x03,3,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboTorqueFine()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TORQUE_FINE.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x03,6,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboFreezeHys()
{
/*	int seln;
	CString datbits;

	seln = m_COMBO_FREEZE_HYS.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x06,2,datbits,2);*/
}

void CdetailDlg::OnCbnSelchangeComboBemfHys()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_BEMF_HYS.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x05,0,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboIlimit()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_ILIMIT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x0c,0,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboIlimitAuto()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_ILIMIT_AUTO.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x0d,0,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboIlimitBrake()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_ILIMIT_BRAKE.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x0c,4,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboOffMask()   
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_OFF_MASK.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x1f,0,datbits,2); 
}

void CdetailDlg::OnCbnSelchangeComboOnMask()  //PWM_MSK
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_ON_MASK.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x06,4,datbits,3);
	updateonmskacc();
}

void CdetailDlg::OnCbnSelchangeComboS1Isdelay()  // driver_non_overlap
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_S1_ISDELAY.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
    pParent->dataupdate_anybits(0x0f,0,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboBlindspnCount()   // pwm_freq
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_BLINDSPN_COUNT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
    pParent->dataupdate_anybits(0x11,1,datbits,1);
}

void CdetailDlg::OnCbnSelchangeComboBlindspnStep()  // ONMSK_ACC
{
	int seln;
	CString datbits,dat;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_BLINDSPN_STEP.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
    pParent->dataupdate_anybits(0x07,4,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboTsIs()  // Ts
{
	int seln;
	CString datbits,dat;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TS_IS.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
    pParent->dataupdate_anybits(0x0d,4,datbits,4);
	
}

void CdetailDlg::OnCbnSelchangeComboToS3() 
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TO_S3.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x12,0,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboTsInit()  //vardac_count
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TS_INIT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
    pParent->dataupdate_anybits(0x0a,1,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboTsBlind() //comm_msk_acc
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TS_BLIND.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
    pParent->dataupdate_anybits(0x07,0,datbits,4);
	updatedelay();
}

void CdetailDlg::OnCbnSelchangeComboTsInitblind()  //handover_spd
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TS_INITBLIND.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
    pParent->dataupdate_anybits(0x0b,1,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboLowDac()  //to_s1
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_LOW_DAC.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x12,5,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboMinDac()  //to_s2
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_MIN_DAC.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x12,2,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboOscOffset() 
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_OSC_OFFSET.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,5);
	pParent->dataupdate_anybits(0x1b,3,datbits,5);
}

void CdetailDlg::OnCbnSelchangeComboOsctc()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_OSCTC.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x1b,0,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboOscTc()  //six_sine
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_OSC_TC.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x04,3,datbits,1);
}

void CdetailDlg::OnCbnSelchangeComboSdisruptSel()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_SDISRUPT_SEL.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x1f,2,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboTestmux()
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
	pParent->dataupdate_anybits(0x13,7,datbits1,1);
	pParent->dataupdate_anybits(0x14,7,datbits2,1);
}

void CdetailDlg::OnCbnSelchangeComboPolePair()
{
	int seln,regval;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//regval = pParent->dataread_anybits(0x07,6,1);
	//m_COMBO_POLE_PAIR.SetCurSel(regval);
	seln = m_COMBO_POLE_PAIR.GetCurSel();	
	
	if(seln==2){
		fourpp=2;
		updatepole();
	    OnBnClickedButtonRefcount();
	}else if(seln==3){
        fourpp=1;
    	updatepole();
	    OnBnClickedButtonRefcount();
	}else{
		datbits = pParent->int2bin_anybits(seln,1);
		pParent->dataupdate_anybits(0x07,6,datbits,1);
		fourpp=0;
		//CheckRadioButton(IDC_RADIO_1PP,IDC_RADIO_4PP,0);
		updatepole();
		OnBnClickedButtonRefcount();
	}
}

void CdetailDlg::OnCbnSelchangeComboBbsRange()   //ILIMIT_GAIN
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_BBS_RANGE.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x1c,6,datbits,2);
	
}

void CdetailDlg::OnCbnSelchangeComboMinsp()
{
/*	int seln;
	CString datbits;

	seln = m_COMBO_MINSP.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,8);
	pParent->dataupdate_anybits(0x20,0,datbits,8);*/
}

void CdetailDlg::OnCbnSelchangeComboLow()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_LOW.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x1c,4,datbits,2);
	OnBnClickedButtonRefcount();
}

void CdetailDlg::OnCbnSelchangeComboTachpinSel()
{
	int seln;
	int mask;
	int seln_mask;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TACHPIN_SEL.GetCurSel();
	mask=15;
	seln_mask=seln&mask;
	datbits = pParent->int2bin_anybits(seln_mask,4);
	pParent->dataupdate_anybits(0x1c,0,datbits,4);
	mask=1;
	seln_mask=(seln>>4)&mask;
	datbits = pParent->int2bin_anybits(seln_mask,1);
	pParent->dataupdate_anybits(0x04,7,datbits,1);
}

void CdetailDlg::OnCbnSelchangeComboPwmLowDetail()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PWM_LOW_DETAIL.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x15,4,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboPwmFloatDetail()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PWM_FLOAT_DETAIL.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x15,6,datbits,2);
}

void CdetailDlg::OnCbnSelchangeComboTestmode00()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_00.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboTestmode01()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_10.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboTestmode10()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_101.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboTestmode11()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_TESTMODE_11.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x13,3,datbits,4);
}

void CdetailDlg::OnCbnSelchangeComboSpinRev()
{
	int seln;
	CString datbits,dat;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_SPIN_REV.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,5);

	blind_spin_en=pParent->dataread_anybits(0x04,2,1);
	if (!success){goto end;};

    if(blind_spin_en==1){
        pParent->dataupdate_anybits(0x0e,3,datbits,5);
		if (!success){goto end;};
	}else{
		dat="1";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
		pParent->dataupdate_anybits(0x0e,3,datbits,5);
		if (!success){goto end;};
		dat="0";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
	}
end:;
}

void CdetailDlg::OnCbnSelchangeComboIsDelay()
{
	int seln;
		CString datbits,dat;
		CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
		seln = m_COMBO_IS_DELAY.GetCurSel();	
		datbits = pParent->int2bin_anybits(seln,2);

		blind_spin_en=pParent->dataread_anybits(0x04,2,1);
		if (!success){goto end;};

		if(blind_spin_en==0){
			pParent->dataupdate_anybits(0x0e,1,datbits,2);
			if (!success){goto end;};
		}else{
			dat="0";
			pParent->dataupdate_anybits(0x04,2,dat,1);
			if (!success){goto end;};
			pParent->dataupdate_anybits(0x0e,1,datbits,2);
			if (!success){goto end;};
			dat="1";
			pParent->dataupdate_anybits(0x04,2,dat,1);
			if (!success){goto end;};
		}
	end:;
}

void CdetailDlg::OnCbnSelchangeComboSpinTime()
{
	int seln;
	CString datbits,dat;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_SPIN_TIME.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);

	blind_spin_en=pParent->dataread_anybits(0x04,2,1);
	if (!success){goto end;};

    if(blind_spin_en==1){
        pParent->dataupdate_anybits(0x0d,5,datbits,3);
		if (!success){goto end;};
	}else{
		dat="1";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
		pParent->dataupdate_anybits(0x0d,5,datbits,3);
		if (!success){goto end;};
		dat="0";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
	}
end:;
}

void CdetailDlg::OnCbnSelchangeComboSpinStep()
{
	int seln;
	CString datbits,dat;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_SPIN_STEP.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);

	blind_spin_en=pParent->dataread_anybits(0x04,2,1);
	if (!success){goto end;};

    if(blind_spin_en==1){
        pParent->dataupdate_anybits(0x0d,1,datbits,3);
		if (!success){goto end;};
	}else{
		dat="1";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
		pParent->dataupdate_anybits(0x0d,1,datbits,3);
		if (!success){goto end;};
		dat="0";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
	}
end:;
}

void CdetailDlg::OnCbnSelchangeComboSpinInit()
{
	int seln;
		CString datbits,dat;
		CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
		seln = m_COMBO_SPIN_INIT.GetCurSel();	
		datbits = pParent->int2bin_anybits(seln,2);

		blind_spin_en=pParent->dataread_anybits(0x04,2,1);
		if (!success){goto end;};

		if(blind_spin_en==1){
			pParent->dataupdate_anybits(0x0e,1,datbits,2);
			if (!success){goto end;};
		}else{
			dat="1";
			pParent->dataupdate_anybits(0x04,2,dat,1);
			if (!success){goto end;};
			pParent->dataupdate_anybits(0x0e,1,datbits,2);
			if (!success){goto end;};
			dat="0";
			pParent->dataupdate_anybits(0x04,2,dat,1);
			if (!success){goto end;};
		}
	end:;
	
}

void CdetailDlg::OnBnClickedCheckSpinAcc()
{
	static BOOL check = FALSE;
	CString datbits,dat;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_SPIN_ACC.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
		spinrev1();
	}else if(check == FALSE){
		datbits = "0";
		spinrev0();
	}

	blind_spin_en=pParent->dataread_anybits(0x04,2,1);
	if (!success){goto end;};

	if(blind_spin_en==1){
        pParent->dataupdate_anybits(0x0d,4,datbits,1);
		if (!success){goto end;};
	}else{
		dat="1";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
		pParent->dataupdate_anybits(0x0d,4,datbits,1);
		if (!success){goto end;};
		dat="0";
	    pParent->dataupdate_anybits(0x04,2,dat,1);
		if (!success){goto end;};
	}
end:;
}

void CdetailDlg::OnCbnSelchangeComboHt() //PROFILE_SEL
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_HT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	pParent->dataupdate_anybits(0x18,2,datbits,2);

	   if(seln==0){
			m_EDIT_MID.EnableWindow(0);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(0);
			//m_EDIT_MT2.EnableWindow(0);
		}else if(seln==2){
            m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(0);
			m_EDIT_MT1.EnableWindow(1);
			//m_EDIT_MT2.EnableWindow(0);
		}else{
			m_EDIT_MID.EnableWindow(1);
			m_EDIT_MID2.EnableWindow(1);
			m_EDIT_MT1.EnableWindow(1);
			//m_EDIT_MT2.EnableWindow(1);
		}

}

void CdetailDlg::OnCbnSelchangeComboLt()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_LT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	pParent->dataupdate_anybits(0x24,5,datbits,3);
}

void CdetailDlg::OnCbnSelchangeComboMt()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_MT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,4);
	pParent->dataupdate_anybits(0x25,4,datbits,4);
}

void CdetailDlg::OnBnClickedRadioMode00()
{
	
}

void CdetailDlg::OnBnClickedRadioMode01()
{
	
}

void CdetailDlg::OnBnClickedRadioMode10()
{
	
}

void CdetailDlg::OnBnClickedRadioMode11()
{
	
}

void CdetailDlg::OnBnClickedButtonWinMask()
{
	int dat = 0;
	int length_dat,temp_int;
	double temp_cal;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_WIN_MASK.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_WIN_MASK.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck4bits(dat);
	datbits = pParent->int2bin_anybits(dat,4);

	if( input_rangecheck == TRUE ){
	pParent->dataupdate_anybits(0x0b,4,datbits,4);
	if (!success){goto end;};
    temp_int = pParent->dataread_anybits(0x0b,4,4);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_WIN_MASK.SetWindowText(temp_string);
	temp_cal = temp_int*1.875;
    m_EDIT_WINMSK_CAL.Format(_T("%.1f deg"),temp_cal);
	UpdateData(FALSE);
	}
	updatesdisrupt();
  end:;
}

void CdetailDlg::OnBnClickedButtonWmskUp()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_WIN_MASK.GetWindowText(dats);
	   	 length_dat = m_EDIT_WIN_MASK.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck4bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck4bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WIN_MASK.SetWindowTextW(dat_string);
	   OnBnClickedButtonWinMask();
	}
}

void CdetailDlg::OnBnClickedButtonWmskDown()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_WIN_MASK.GetWindowText(dats);
	   	 length_dat = m_EDIT_WIN_MASK.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck4bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck4bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WIN_MASK.SetWindowTextW(dat_string);
	   OnBnClickedButtonWinMask();
	}
}

void CdetailDlg::OnBnClickedButtonWin()
{
	int dat = 0;
	int length_dat,temp_int;
	double temp_cal;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_WIN.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_WIN.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck6bits(dat);
	datbits = pParent->int2bin_anybits(dat,6);

	if( input_rangecheck == TRUE ){
	pParent->dataupdate_anybits(0x09,2,datbits,6);
	if (!success){goto end;};
    temp_int = pParent->dataread_anybits(0x09,2,6);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_WIN.SetWindowText(temp_string);
	temp_cal = temp_int*1.875;
    m_EDIT_SP_WINCAL.Format(_T("%.1f deg"),temp_cal);
	UpdateData(FALSE);
	}
	updatesdisrupt();
  end:;
}

void CdetailDlg::OnBnClickedButtonWinUp()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_WIN.GetWindowText(dats);
	   	 length_dat = m_EDIT_WIN.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WIN.SetWindowTextW(dat_string);
	   OnBnClickedButtonWin();
	}
}

void CdetailDlg::OnBnClickedButtonWinDown()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_WIN.GetWindowText(dats);
	   	 length_dat = m_EDIT_WIN.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WIN.SetWindowTextW(dat_string);
	   OnBnClickedButtonWin();
	}
}

void CdetailDlg::OnBnClickedButtonWinmskAuto()
{
	int dat = 0;
	int length_dat,temp_int;
	double temp_cal;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_WINMSK_AUTO.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_WINMSK_AUTO.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck4bits(dat);
	datbits = pParent->int2bin_anybits(dat,4);

	if( input_rangecheck == TRUE ){
	pParent->dataupdate_anybits(0x0a,4,datbits,4);
	if (!success){goto end;};
    temp_int = pParent->dataread_anybits(0x0a,4,4);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_WINMSK_AUTO.SetWindowText(temp_string);
	temp_cal = temp_int*1.875;
    m_EDIT_WINMSK_AUTOCAL.Format(_T("%.1f deg"),temp_cal);
	UpdateData(FALSE);
	}
  end:;
}

void CdetailDlg::OnBnClickedButtonMskautoUp()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_WINMSK_AUTO.GetWindowText(dats);
	   	 length_dat = m_EDIT_WINMSK_AUTO.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck4bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck4bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WINMSK_AUTO.SetWindowTextW(dat_string);
	   OnBnClickedButtonWinmskAuto();
	}
}

void CdetailDlg::OnBnClickedButtonMskautoDown()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_WINMSK_AUTO.GetWindowText(dats);
	   	 length_dat = m_EDIT_WINMSK_AUTO.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck4bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck4bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WINMSK_AUTO.SetWindowTextW(dat_string);
	   OnBnClickedButtonWinmskAuto();
	}
}

void CdetailDlg::OnBnClickedButtonLdac()  //ADC
{
	int dat = 0;
	int length_dat,temp_int,temp_bit;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_LDAC.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_LDAC.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck8bits(dat);
	datbits = pParent->int2bin_anybits(dat,8);

	if( input_rangecheck == TRUE ){
	pParent->dataupdate_anybits(0x15,0,datbits,8);
	if (!success){goto end;};
	temp_bit = pParent->dataread_anybits(0x01,3,1);
	if (!success){goto end;};
		if(temp_bit==0){
			temp_int = pParent->dataread_anybits(0x15,0,8);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_LDAC.SetWindowText(temp_string);
		}else{
            datbit="0";
			pParent->dataupdate_anybits(0x01,3,datbits,1);
	        if (!success){goto end;};
			temp_int = pParent->dataread_anybits(0x15,0,8);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_LDAC.SetWindowText(temp_string);
			datbit="1";
			pParent->dataupdate_anybits(0x01,3,datbits,1);
	        if (!success){goto end;};
		}

	//temp_cal = (((temp_int<<4)+15)/255)*100;
    //m_EDIT_LDAC_CAL.Format(_T("%d%s"),temp_cal,"%");
	//UpdateData(FALSE);
	}
  end:;
}

void CdetailDlg::OnBnClickedButtonHdac()  // SP_WIN_AUTO
{
	int dat = 0;
	int length_dat,temp_int;
	double temp_cal;
	CString dats,datbits,temp_string,datbit;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_HDAC.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_HDAC.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck6bits(dat);
	datbits = pParent->int2bin_anybits(dat,6);

	if( input_rangecheck == TRUE ){
	pParent->dataupdate_anybits(0x08,2,datbits,6);
	if (!success){goto end;};
    temp_int = pParent->dataread_anybits(0x08,2,6);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_HDAC.SetWindowText(temp_string);
	temp_cal = temp_int*1.875;
    m_EDIT_HDAC_CAL.Format(_T("%.1f deg"),temp_cal);
	UpdateData(FALSE);
	}
  end:;
}

void CdetailDlg::OnBnClickedButtonWinautoUp()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_HDAC.GetWindowText(dats);
	   	 length_dat = m_EDIT_HDAC.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_HDAC.SetWindowTextW(dat_string);
	   OnBnClickedButtonHdac();
	}
}

void CdetailDlg::OnBnClickedButtonWinautoDown()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_HDAC.GetWindowText(dats);
	   	 length_dat = m_EDIT_HDAC.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_HDAC.SetWindowTextW(dat_string);
	   OnBnClickedButtonHdac();
	}
}

void CdetailDlg::OnBnClickedButtonSpdacS1()
{
int dat = 0;
	int temp_int,temp_cal;
	double temp_float;
	double datpercent;
	int length_dat;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

		if(spdac_stage==1){
			//read user inputs
			m_EDIT_SPDAC_S1.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_SPDAC_S1.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck6bits(dat);
			datbits = pParent->int2bin_anybits(dat,6);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x0f,2,datbits,6);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x0f,2,6);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_SPDAC_S1.SetWindowText(temp_string);
			temp_cal = temp_int<<2;
			temp_float = temp_cal*0.3922;
			m_EDIT_SPDAC.Format(_T("%.1f%s"),temp_float,"%");
			UpdateData(FALSE);
		}else if(spdac_stage==2){
			//read user inputs
			m_EDIT_SPDAC_S2.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_SPDAC_S2.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck6bits(dat);
			datbits = pParent->int2bin_anybits(dat,6);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x10,2,datbits,6);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x10,2,6);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_SPDAC_S2.SetWindowText(temp_string);
			temp_cal = temp_int<<2;
			temp_float = temp_cal*0.3922;
			m_EDIT_SPDAC2.Format(_T("%.1f%s"),temp_float,"%");
			UpdateData(FALSE);
		}else if(spdac_stage==4){
			//read user inputs
			m_EDIT_SPDAC_S4.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_SPDAC_S4.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck6bits(dat);
			datbits = pParent->int2bin_anybits(dat,6);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x11,2,datbits,6);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x11,2,6);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_SPDAC_S4.SetWindowText(temp_string);
			temp_cal = temp_int<<2;
			temp_float = temp_cal*0.3922;
			m_EDIT_SPDAC4.Format(_T("%.1f%s"),temp_float,"%");
			UpdateData(FALSE);
		}
	

end:;
}

void CdetailDlg::OnBnClickedButtonDacup()
{
	int gain_counter=0;
	int gain_step=16;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

		if(spdac_stage==1){
				 m_EDIT_SPDAC_S1.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S1.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat++;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat--;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S1.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==2){
			   m_EDIT_SPDAC_S2.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S2.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat++;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat--;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==4){
			   m_EDIT_SPDAC_S4.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S4.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat++;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat--;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}
	
}

void CdetailDlg::OnBnClickedButtonDacdown()
{
		int gain_counter=0;
	int gain_step=16;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

		if(spdac_stage==1){
				 m_EDIT_SPDAC_S1.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S1.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat--;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat++;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S1.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==2){
			   m_EDIT_SPDAC_S2.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S2.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat--;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat++;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==4){
			   m_EDIT_SPDAC_S4.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S4.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat--;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat++;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}
	
}

void CdetailDlg::OnBnClickedButtonDacupSmall()
{
	int gain_counter=0;
	int gain_step=1;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

		if(spdac_stage==1){
				 m_EDIT_SPDAC_S1.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S1.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat++;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat--;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S1.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==2){
			   m_EDIT_SPDAC_S2.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S2.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat++;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat--;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==4){
			   m_EDIT_SPDAC_S4.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S4.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat++;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat--;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}
	
}

void CdetailDlg::OnBnClickedButtonDacdownSmall()
{
	int gain_counter=0;
	int gain_step=1;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

		if(spdac_stage==1){
				 m_EDIT_SPDAC_S1.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S1.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat--;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat++;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S1.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==2){
			   m_EDIT_SPDAC_S2.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S2.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat--;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat++;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}else if(spdac_stage==4){
			   m_EDIT_SPDAC_S4.GetWindowText(dats);
	   			 length_dat = m_EDIT_SPDAC_S4.LineLength();
    			 dat = use_debugdlg_detail.string2int(dats, length_dat);
				 input_rangecheck = datarangecheck6bits(dat);
			

			if(input_rangecheck == TRUE){
			   do {
	    			gain_counter++;
					dat--;
					input_rangecheck = datarangecheck6bits(dat);
					if(input_rangecheck != TRUE){
					  dat++;
					  break;
					}
			   }while (gain_counter != gain_step);
			   dat_string.Format(_T("%x"),dat);
			   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
			   OnBnClickedButtonSpdacS1();
			 }
		}
	
}

void CdetailDlg::OnBnClickedButtonSpdacS2()
{
	int dat = 0;
	int temp_int;
	int temp_cal;
	int length_dat;
	double temp_float;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_SPDAC_S2.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_SPDAC_S2.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck6bits(dat);
    datbits = pParent->int2bin_anybits(dat,6);

	if( input_rangecheck == TRUE){
	pParent->dataupdate_anybits(0x10,2,datbits,6);
	if (!success){goto end;};
	}

	temp_int = pParent->dataread_anybits(0x10,2,6);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_SPDAC_S2.SetWindowText(temp_string);
	temp_cal = temp_int<<2;
	temp_float = temp_cal*0.3922;
    m_EDIT_SPDAC2.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE);

end:;
}

void CdetailDlg::OnBnClickedButtonDacup2()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S2.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S2.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS2();
	}
}

void CdetailDlg::OnBnClickedButtonDacdown2()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S2.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S2.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS2();
	}
}

void CdetailDlg::OnBnClickedButtonDacupSmall2()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S2.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S2.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS2();
	}
}

void CdetailDlg::OnBnClickedButtonDacdownSmall2()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S2.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S2.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S2.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS2();
	}
}

void CdetailDlg::OnBnClickedButtonSpdacS4()
{
	int dat = 0;
	int temp_int;
	int temp_cal;
	int length_dat;
	double temp_float;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_SPDAC_S4.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_SPDAC_S4.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck6bits(dat);
    datbits = pParent->int2bin_anybits(dat,6);

	if( input_rangecheck == TRUE){
	pParent->dataupdate_anybits(0x11,2,datbits,6);
	if (!success){goto end;};
	}

	temp_int = pParent->dataread_anybits(0x11,2,6);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_SPDAC_S4.SetWindowText(temp_string);
	temp_cal = temp_int<<2;
	temp_float = temp_cal*0.3922;
    m_EDIT_SPDAC4.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE);

end:;
}

void CdetailDlg::OnBnClickedButtonDacup4()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S4.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S4.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS4();
	}
}

void CdetailDlg::OnBnClickedButtonDacdown4()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S4.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S4.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS4();
	}
}

void CdetailDlg::OnBnClickedButtonDacupSmall4()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S4.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S4.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS4();
	}
}

void CdetailDlg::OnBnClickedButtonDacdownSmall4()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_SPDAC_S4.GetWindowText(dats);
	   	 length_dat = m_EDIT_SPDAC_S4.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck6bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck6bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_SPDAC_S4.SetWindowTextW(dat_string);
	   OnBnClickedButtonSpdacS4();
	}
}

void CdetailDlg::OnBnClickedButtonRstatus()
{
	int temp_sel,mask,temp_int1,temp_int2,temp_cal,temp_bit,temp_bit2,temp_bit3,temp_int;
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
						temp_int1 = pParent->dataread_anybits(0x17,4,4);
						if (!success){goto end;};
						temp_int2 = pParent->dataread_anybits(0x16,0,8);
						if (!success){goto end;};
						temp_cal = (temp_int1<<8)+temp_int2;
						m_EDIT_PWMIN_FINAL.Format(_T("%x"),temp_cal);
						UpdateData(FALSE);
						temp_int = pParent->dataread_anybits(0x15,0,8);
						if (!success){goto end;};
						m_EDIT_SUMOUT_FF_TEST.Format(_T("%x"),temp_int);
						UpdateData(FALSE);
						datr = pParent->rreg(0x19);
						if (!success){goto end;};
						datbin = pParent->int2bin_anybits(datr,8);
						if(temp_bit2==1){
								datbit="1";
								pParent->dataupdate_anybits(0x01,3,datbits,1);
								if (!success){goto end;};
                                temp_int = pParent->dataread_anybits(0x19,0,8);
						        if (!success){goto end;};
						        m_EDIT_SUMOUT_FF.Format(_T("%x"),temp_int);
						        UpdateData(FALSE);
								datbit="0";
								pParent->dataupdate_anybits(0x01,3,datbits,1);
								if (!success){goto end;};
						}else{
							if(temp_bit3==0){
                                datbit="1";
								pParent->dataupdate_anybits(0x01,3,datbits,1);
								if (!success){goto end;};
								temp_int = pParent->dataread_anybits(0x19,0,8);
								if (!success){goto end;};
								m_EDIT_SUMOUT_FF.Format(_T("%x"),temp_int);
								UpdateData(FALSE);
								datbit="0";
								pParent->dataupdate_anybits(0x01,3,datbits,1);
								if (!success){goto end;};
							}
						}
				 }else if(temp_bit==1){
						temp_int = pParent->dataread_anybits(0x19,0,8);
						if (!success){goto end;};
						m_EDIT_SUMOUT_FF.Format(_T("%x"),temp_int);
						UpdateData(FALSE);

						datbits="0";
	                    pParent->dataupdate_anybits(0x01,3,datbits,1);//pos_sns=0
						temp_int = pParent->dataread_anybits(0x15,0,8);
						if (!success){goto end;};
						m_EDIT_SUMOUT_FF_TEST.Format(_T("%x"),temp_int);
						UpdateData(FALSE);
					    
                        temp_int1 = pParent->dataread_anybits(0x17,4,4);
						if (!success){goto end;};
						temp_int2 = pParent->dataread_anybits(0x16,0,8);
						if (!success){goto end;};
						temp_cal = (temp_int1<<8)+temp_int2;
						m_EDIT_PWMIN_FINAL.Format(_T("%x"),temp_cal);
						UpdateData(FALSE);
						datr = pParent->rreg(0x19);
						if (!success){goto end;};
						datbin = pParent->int2bin_anybits(datr,8);
                        datbits="1";
	                    pParent->dataupdate_anybits(0x01,3,datbits,1);
				 }
	
	             

	             if(datbin[0] == '0'){
	 	              m_EDIT_SPIN_DONE.Format(_T("NO"));
	                  UpdateData(FALSE);
	             }else {
		              m_EDIT_SPIN_DONE.Format(_T("YES"));
	                  UpdateData(FALSE);
	             }
	     
                 mask=7;
	             temp_sel=datr&mask;
	             m_EDIT_REV.Format(_T("%x"),temp_sel);
	             UpdateData(FALSE);
				 mask=15;
				 temp_sel=(datr>>3)&mask;
				 if(temp_sel==0){
					 m_EDIT_SPIN_FLT.Format(_T("0: no fault"));
					 UpdateData(FALSE);
				 }else if(temp_sel==1){
                     m_EDIT_SPIN_FLT.Format(_T("1: ind_sense fault"));
					 UpdateData(FALSE);
				 }else if(temp_sel==2){
					 m_EDIT_SPIN_FLT.Format(_T("2: mancomm timeout"));
					 UpdateData(FALSE);
				 }else if(temp_sel==3){
					 m_EDIT_SPIN_FLT.Format(_T("3: handover timeout"));
					 UpdateData(FALSE);
				 }else if(temp_sel==4){
					 m_EDIT_SPIN_FLT.Format(_T("4: S4 min speed"));
					 UpdateData(FALSE);
				 }else if(temp_sel==5){
					 m_EDIT_SPIN_FLT.Format(_T("5: S5 min speed"));
					 UpdateData(FALSE);
				 }else if(temp_sel==6){
					 m_EDIT_SPIN_FLT.Format(_T("6: S6 min speed"));
					 UpdateData(FALSE);
				 }else if(temp_sel==7){
					 m_EDIT_SPIN_FLT.Format(_T("7: sdisrupt"));
					 UpdateData(FALSE);
				 }else if(temp_sel==8){
					 m_EDIT_SPIN_FLT.Format(_T("8: max speed"));
					 UpdateData(FALSE);
				 }else{
					 m_EDIT_SPIN_FLT.Format(_T("-NA-"));
					 UpdateData(FALSE);
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
				 if(datbin[3] == '0'){
		              m_CHECK_OTPCAL_DONE.SetCheck(0);
	             }else{
		             m_CHECK_OTPCAL_DONE.SetCheck(1);
	             }  
				 if(datbin[2] == '0'){
		             m_CHECK_OTP1DONE.SetCheck(0);
	             }else{
		             m_CHECK_OTP1DONE.SetCheck(1);
	             }  

            
end:;
}

void CdetailDlg::OnBnClickedButtonReadDac()
{
	int dat = 0;
	int temp_int;
	int temp_cal;
	double temp_float;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	if(hex_percent==0){
		temp_int = pParent->rreg(0x18);
	    if (!success){goto end;};
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_WDAC.SetWindowText(temp_string);
		temp_float = temp_int*0.3922;
		m_EDIT_DAC.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);

		temp_int = pParent->dataread_anybits(0x0F,2,6);
	    if (!success){goto end;};
        temp_string.Format(_T("%x"),temp_int);
		m_EDIT_SPDAC_S1.SetWindowText(temp_string);
		temp_cal = temp_int<<2;
		temp_float = temp_cal*0.3922;
		m_EDIT_SPDAC.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);

		temp_int = pParent->dataread_anybits(0x10,2,6);
	    if (!success){goto end;};
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_SPDAC_S2.SetWindowText(temp_string);
		temp_cal = temp_int<<2;
		temp_float = temp_cal*0.3922;
		m_EDIT_SPDAC2.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);

		temp_int = pParent->dataread_anybits(0x11,2,6);
		if (!success){goto end;};
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_SPDAC_S4.SetWindowText(temp_string);
		temp_cal = temp_int<<2;
		temp_float = temp_cal*0.3922;
		m_EDIT_SPDAC4.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);
	}else if(hex_percent==1){
	/*	temp_int = pParent->rreg(0x18);
	    if (!success){goto end;};
		temp_float = temp_int*0.3922;
		temp_string.Format(_T("%.1f"),temp_float);
		m_EDIT_WDAC.SetWindowText(temp_string);
		m_EDIT_DAC.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);
		temp_int = pParent->dataread_anybits(0x0f,2,6);
	    if (!success){goto end;};
		temp_cal = temp_int<<2;
	    temp_float = temp_cal*0.3922;
		temp_string.Format(_T("%.1f"),temp_float);
		m_EDIT_SPDAC_S1.SetWindowText(temp_string);
		m_EDIT_SPDAC.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);
		temp_int = pParent->dataread_anybits(0x10,2,6);
		if (!success){goto end;};
		temp_cal = temp_int<<2;
	    temp_float = temp_cal*0.3922;
		temp_string.Format(_T("%.1f"),temp_float);
		m_EDIT_SPDAC_S2.SetWindowText(temp_string);
		m_EDIT_SPDAC2.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);
		temp_int = pParent->dataread_anybits(0x11,2,6);
		if (!success){goto end;};
		temp_cal = temp_int<<2;
	    temp_float = temp_cal*0.3922;
		temp_string.Format(_T("%.1f"),temp_float);
		m_EDIT_SPDAC_S4.SetWindowText(temp_string);
		m_EDIT_SPDAC4.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);*/
	};

end:;
}

void CdetailDlg::OnBnClickedButtonRefcount()
{
	int dat = 0;
	int dat1,dat2,dac_value,lowcount,mapdac;
	int temp_int1,temp_int2,temp_int;
	int mask,pp,dir_spd,low_sel;
	double temp_float,tar_spd;
	int length_dat;
	CString dats,datbits,datbits1,datbits2;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_REFCOUNT.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_REFCOUNT.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck16bits(dat);
	mask = 255;
	dat1 = dat&mask;
	dat2 = (dat>>8)&mask;
    datbits1 = pParent->int2bin_anybits(dat1,8);
	datbits2 = pParent->int2bin_anybits(dat2,8);

	if( input_rangecheck == TRUE){
		pParent->dataupdate_anybits(0x1d,0,datbits1,8);
		if (!success){goto end;};
		pParent->dataupdate_anybits(0x1e,0,datbits2,8);
		if (!success){goto end;};
	}
    
	pp = pParent->dataread_anybits(0x07,6,1);
	if (!success){goto end;};
	dir_spd = pParent->dataread_anybits(0x01,6,1);
	if (!success){goto end;};
	low_sel= pParent->dataread_anybits(0x23,0,8);
	if (!success){goto end;};

/*	if(low_sel==0){
		lowcount=0;
	}else if(low_sel==1){
		lowcount=26;
	}else if(low_sel==2){
		lowcount=51;
	}else if(low_sel==3){
		lowcount=77;
	}*/

	if(fourpp==0){
	  if(pp==0){
		dac_value = pParent->rreg(0x18);
		if (!success){goto end;};
		temp_int1 = pParent->rreg(0x1d);
		if (!success){goto end;};
		temp_int2 = pParent->rreg(0x1e);
		temp_int = (temp_int2<<8)+temp_int1;
		if (!success){goto end;};
		mapdac = int(double(((255-low_sel)*(double(dac_value)/255)))+double(low_sel));
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(temp_int!=0){
			temp_float = 249023438/temp_int;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
				if(dir_spd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					tar_spd = (temp_float*mapdac)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tar_spd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	  }else if(pp==1){
		dac_value = pParent->rreg(0x18);
		if (!success){goto end;};
        temp_int1 = pParent->rreg(0x1d);
		if (!success){goto end;};
		temp_int2 = pParent->rreg(0x1e);
		temp_int = (temp_int2<<8)+temp_int1;
		if (!success){goto end;};
		mapdac = int(double(((255-low_sel)*(double(dac_value)/255)))+double(low_sel));
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(temp_int!=0){
			temp_float = 166015625/temp_int;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(dir_spd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					tar_spd = (temp_float*mapdac)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tar_spd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	  }
	}else if(fourpp==1){
		dac_value = pParent->rreg(0x18);
		if (!success){goto end;};
        temp_int1 = pParent->rreg(0x1d);
		if (!success){goto end;};
		temp_int2 = pParent->rreg(0x1e);
		temp_int = (temp_int2<<8)+temp_int1;
		if (!success){goto end;};
		mapdac = int(double(((255-low_sel)*(double(dac_value)/255)))+double(low_sel));
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(temp_int!=0){
			temp_float = 124511719/temp_int;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(dir_spd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					tar_spd = (temp_float*mapdac)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tar_spd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	}else if(fourpp==2){
		dac_value = pParent->rreg(0x18);
		if (!success){goto end;};
        temp_int1 = pParent->rreg(0x1d);
		if (!success){goto end;};
		temp_int2 = pParent->rreg(0x1e);
		temp_int = (temp_int2<<8)+temp_int1;
		if (!success){goto end;};
		mapdac = int(double(((255-low_sel)*(double(dac_value)/255)))+double(low_sel));
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_REFCOUNT.SetWindowText(temp_string);
		if(temp_int!=0){
			temp_float = 498046876/temp_int;
			temp_string.Format(_T("%.0f"),temp_float);
			m_EDIT_REFSPEED.SetWindowText(temp_string);
			
				if(dir_spd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),temp_float);
					UpdateData(FALSE);
			    }else{
					tar_spd = (temp_float*mapdac)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tar_spd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFSPEED.SetWindowText(L"NA");
		}
	}

end:;
}

void CdetailDlg::OnBnClickedButtonRefcountup()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_REFCOUNT.GetWindowText(dats);
	   	 length_dat = m_EDIT_REFCOUNT.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck16bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck16bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_REFCOUNT.SetWindowTextW(dat_string);
	   OnBnClickedButtonRefcount();
	}
}

void CdetailDlg::OnBnClickedButtonRefcountdown()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_REFCOUNT.GetWindowText(dats);
	   	 length_dat = m_EDIT_REFCOUNT.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck16bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck16bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_REFCOUNT.SetWindowTextW(dat_string);
	   OnBnClickedButtonRefcount();
	}
}

void CdetailDlg::OnBnClickedButtonRefcountupSmall()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_REFCOUNT.GetWindowText(dats);
	   	 length_dat = m_EDIT_REFCOUNT.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck16bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck16bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_REFCOUNT.SetWindowTextW(dat_string);
	   OnBnClickedButtonRefcount();
	}
}

void CdetailDlg::OnBnClickedButtonRefcountdownSmall()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_REFCOUNT.GetWindowText(dats);
	   	 length_dat = m_EDIT_REFCOUNT.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck16bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck16bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_REFCOUNT.SetWindowTextW(dat_string);
	   OnBnClickedButtonRefcount();
	}
}

void CdetailDlg::OnBnClickedButtonWdac()
{
	int dat = 0;
	int temp_int;
	double temp_float;
	double datpercent;
	int length_dat;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	if(hex_percent==0){
		//read user inputs
		m_EDIT_WDAC.GetWindowText(dats);
		
		//get the string length of the inputs
		length_dat = m_EDIT_WDAC.LineLength();

		//convert input string into integer
		dat = use_debugdlg_detail.string2int(dats, length_dat);
		input_rangecheck = datarangecheck8bits(dat);
		datbits = pParent->int2bin_anybits(dat,8);

		//write new DAC value
		if( input_rangecheck == TRUE){
		pParent->dataupdate_anybits(0x18,0,datbits,8);
		if (!success){goto end;};
		}

		//duty_cycle1=dat*0.3922;
		//duty_cycle1=dat*0.392157;
		//pwm_dc=(pwm_period*dat)*0.00392157;
	    //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	    //okUsbFrontPanel_SetWireInValue(use_debugdlg_detail.xem, 0x03, pwm_in, 0xffff);// choose SCLK
        //okUsbFrontPanel_UpdateWireIns(use_debugdlg_detail.xem);
	    //Sleep(1);

		temp_int = pParent->rreg(0x18);
		if (!success){goto end;};
		temp_string.Format(_T("%x"),temp_int);
		m_EDIT_WDAC.SetWindowText(temp_string);
		//temp_float = temp_int*0.3922;
		m_EDIT_DAC.Format(_T("%x hex"),temp_int);
		UpdateData(FALSE);

		OnBnClickedButtonRefcount();
	}else if(hex_percent==1){
		//read user inputs
		m_EDIT_WDAC.GetWindowText(dats);
		datpercent = wcstod(dats, NULL);
		
		dat = datpercent*2.5500;
		input_rangecheck = datarangecheck8bits(dat);
		datbits = pParent->int2bin_anybits(dat,8);

		if( input_rangecheck == TRUE){
		pParent->dataupdate_anybits(0x18,0,datbits,8);
		if (!success){goto end;};
		}

		//duty_cycle1=datpercent;
		//pwm_dc=(pwm_period*datpercent)*0.0100;
	    //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	    //okUsbFrontPanel_SetWireInValue(use_debugdlg_detail.xem, 0x03, pwm_in, 0xffff);// choose SCLK
        //okUsbFrontPanel_UpdateWireIns(use_debugdlg_detail.xem);
	    //Sleep(1);

		temp_int = pParent->rreg(0x18);
		if (!success){goto end;};
		temp_float = temp_int*0.3922;
		temp_string.Format(_T("%.1f"),temp_float);
		m_EDIT_WDAC.SetWindowText(temp_string);
		//temp_float = temp_int*0.3922;
		m_EDIT_DAC.Format(_T("%.1f%s"),temp_float,"%");
		UpdateData(FALSE);

		OnBnClickedButtonRefcount();
	}

end:;
}

void CdetailDlg::OnBnClickedButtonWdacup()
{
	int gain_counter=0;
	int gain_step=16;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

	if(hex_percent==0){
	     m_EDIT_WDAC.GetWindowText(dats);
	   	 length_dat = m_EDIT_WDAC.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck8bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck8bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WDAC.SetWindowTextW(dat_string);
	   OnBnClickedButtonWdac();
	 }
	}else if(hex_percent==1){
               m_EDIT_WDAC.GetWindowText(dats);
		       datpercent = wcstod(dats, NULL);
	   	      	   
			   datpercent = datpercent+10.0;
			   datdac=datpercent*2.55;
			   input_rangecheck = datarangecheck8bits(datdac);
			   if(input_rangecheck != TRUE){
					  datpercent=100.0;
					}
			   dat_string.Format(_T("%.1f"),datpercent);
			   m_EDIT_WDAC.SetWindowTextW(dat_string);
			   OnBnClickedButtonWdac();
	}
   
}

void CdetailDlg::OnBnClickedButtonWdacdown()
{
int gain_counter=0;
	int gain_step=16;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

	if(hex_percent==0){
	     m_EDIT_WDAC.GetWindowText(dats);
	   	 length_dat = m_EDIT_WDAC.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck8bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck8bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WDAC.SetWindowTextW(dat_string);
	   OnBnClickedButtonWdac();
	 }
	}else if(hex_percent==1){
               m_EDIT_WDAC.GetWindowText(dats);
		       datpercent = wcstod(dats, NULL);
	   	      	   
			   datpercent = datpercent-10.0;
			   datdac=datpercent*2.55;
			   input_rangecheck = datarangecheck8bits(datdac);
			   if(input_rangecheck != TRUE){
					  datpercent=0.0;
					}
			   dat_string.Format(_T("%.1f"),datpercent);
			   m_EDIT_WDAC.SetWindowTextW(dat_string);
			   OnBnClickedButtonWdac();
	}
   
}

void CdetailDlg::OnBnClickedButtonWdacupSmall()
{
	int gain_counter=0;
	int gain_step=1;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

	if(hex_percent==0){
	     m_EDIT_WDAC.GetWindowText(dats);
	   	 length_dat = m_EDIT_WDAC.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck8bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat++;
			input_rangecheck = datarangecheck8bits(dat);
			if(input_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WDAC.SetWindowTextW(dat_string);
	  OnBnClickedButtonWdac();
	 }
	}else if(hex_percent==1){
               m_EDIT_WDAC.GetWindowText(dats);
		       datpercent = wcstod(dats, NULL);
	   	      	   
			   datpercent = datpercent+1;
			   datdac=datpercent*2.55;
			   input_rangecheck = datarangecheck8bits(datdac);
			   if(input_rangecheck != TRUE){
					  datpercent=100.0;
					}
			   dat_string.Format(_T("%.1f"),datpercent);
			   m_EDIT_WDAC.SetWindowTextW(dat_string);
			   OnBnClickedButtonWdac();
	}   
}

void CdetailDlg::OnBnClickedButtonWdacdownSmall()
{
	int gain_counter=0;
	int gain_step=1;
	double datpercent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	CString gains;
	CString dats,dat_string;

	if(hex_percent==0){
	     m_EDIT_WDAC.GetWindowText(dats);
	   	 length_dat = m_EDIT_WDAC.LineLength();
    	 dat = use_debugdlg_detail.string2int(dats, length_dat);
	     input_rangecheck = datarangecheck8bits(dat);
	

	if(input_rangecheck == TRUE){
	   do {
	    	gain_counter++;
			dat--;
			input_rangecheck = datarangecheck8bits(dat);
			if(input_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_WDAC.SetWindowTextW(dat_string);
	   OnBnClickedButtonWdac();
	 }
	}else if(hex_percent==1){
               m_EDIT_WDAC.GetWindowText(dats);
		       datpercent = wcstod(dats, NULL);
	   	      	   
			   datpercent = datpercent-1;
			   datdac=datpercent*2.55;
			   input_rangecheck = datarangecheck8bits(datdac);
			   if(input_rangecheck != TRUE){
					  datpercent=0.0;
					}
			   dat_string.Format(_T("%.1f"),datpercent);
			   m_EDIT_WDAC.SetWindowTextW(dat_string);
			   OnBnClickedButtonWdac();
	}
   
}

void CdetailDlg::OnBnClickedButtonReadTpos()
{
	int dat = 0;
	int temp_int1,temp_int2;            
	int temp_cal;
	CString dats,datbits;
	CString temp_string;
		CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	temp_int1 = pParent->dataread_anybits(0x17,4,4);
	if (!success){goto end;};
	temp_int2 = pParent->dataread_anybits(0x16,0,8);
	if (!success){goto end;};
	temp_cal = (temp_int1<<8)+temp_int2;
    m_EDIT_TPOS.Format(_T("%d"),temp_cal);
	UpdateData(FALSE);

end:;
}

void CdetailDlg::OnBnClickedButtonReadall()
{

	OnBnClickedButtonSetIlimit();
	vardaccount();
	if (!success)
		return;
	updatedelay();
	if (!success)
		return;
	updateonmskacc();
	if (!success)
		return;
	readall();
	if (!success)
		return;

	m_COMBO_ILIMIT_MAX.SetCurSel(15);

	if(hss_cal == 0){
		CheckRadioButton(IDC_RADIO_HSS,IDC_RADIO_LSS,IDC_RADIO_LSS);
	}else if(hss_cal == 1){
		CheckRadioButton(IDC_RADIO_HSS,IDC_RADIO_LSS,IDC_RADIO_HSS);
	}

	if(hex_percent == 0){
		CheckRadioButton(IDC_RADIO_HEX,IDC_RADIO_PERCENT,IDC_RADIO_HEX);
	}else if(hex_percent == 1){
		CheckRadioButton(IDC_RADIO_HEX,IDC_RADIO_PERCENT,IDC_RADIO_PERCENT);
	}

	if(spdac_stage == 1){
		CheckRadioButton(IDC_RADIO_SPDAC_S1,IDC_RADIO_SPDAC_S4,IDC_RADIO_SPDAC_S1);
		m_EDIT_SPDAC_S1.EnableWindow(1);
	    m_EDIT_SPDAC_S2.EnableWindow(0);
	    m_EDIT_SPDAC_S4.EnableWindow(0);
	}else if(spdac_stage == 2){
		CheckRadioButton(IDC_RADIO_SPDAC_S1,IDC_RADIO_SPDAC_S4,IDC_RADIO_SPDAC_S2);
		m_EDIT_SPDAC_S1.EnableWindow(0);
		m_EDIT_SPDAC_S2.EnableWindow(1);
		m_EDIT_SPDAC_S4.EnableWindow(0);
	}else if(spdac_stage == 4){
		CheckRadioButton(IDC_RADIO_SPDAC_S1,IDC_RADIO_SPDAC_S4,IDC_RADIO_SPDAC_S4);
		m_EDIT_SPDAC_S1.EnableWindow(0);
		m_EDIT_SPDAC_S2.EnableWindow(0);
		m_EDIT_SPDAC_S4.EnableWindow(1);
	}
}


void CdetailDlg::OnBnClickedButtonStart()
{
	use_debugdlg_detail.OnBnClickedButtonStart();
}

void CdetailDlg::OnBnClickedRadioPwmregSel()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
        datbits = "1";
		pParent->dataupdate_anybits(0x02,1,datbits,1);
		datbits = "0";
		pParent->dataupdate_anybits(0x0a,0,datbits,1);
}

void CdetailDlg::OnBnClickedRadioPwminSel()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "1";
	pParent->dataupdate_anybits(0x0a,0,datbits,1);
	datbits = "0";
	pParent->dataupdate_anybits(0x02,1,datbits,1);
}

void CdetailDlg::OnBnClickedRadioExtdacSel()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "0";
	pParent->dataupdate_anybits(0x02,1,datbits,1);
    pParent->dataupdate_anybits(0x0a,0,datbits,1);
}

void CdetailDlg::OnBnClickedRadioBlindSpinDis()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "0";
	pParent->dataupdate_anybits(0x04,2,datbits,1);
}

void CdetailDlg::OnBnClickedRadioBlindSpinEn()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "1";
	pParent->dataupdate_anybits(0x04,2,datbits,1);
}

void CdetailDlg::OnBnClickedButtonPhaseCnt()
{
	int dat = 0;
	int length_dat;
	int  angle,angle_read;
	CString dats,datbits,temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_PHASE_CNT.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_PHASE_CNT.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck5bits(dat);

	datbits = pParent->int2bin_anybits(dat,5);

	blind_spin_en=pParent->dataread_anybits(0x04,2,1);
	if (!success){goto end;};

	if( input_rangecheck == TRUE){
	//page_sel_0();
		if(blind_spin_en==0){
			pParent->dataupdate_anybits(0x0e,3,datbits,5);
			if (!success){goto end;};
			angle_read = pParent->dataread_anybits(0x0e,3,5);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),angle_read);
			m_EDIT_PHASE_CNT.SetWindowText(temp_string);
			angle = (angle_read+1)*2;
			m_EDIT_RPHASE_CNT.Format(_T("%d"),angle);
			UpdateData(FALSE);
		}else if(blind_spin_en==1){
			dats="0";
	        pParent->dataupdate_anybits(0x04,2,dats,1);
			pParent->dataupdate_anybits(0x0e,3,datbits,5);
			if (!success){goto end;};
			angle_read = pParent->dataread_anybits(0x0e,3,5);
			if (!success){goto end;};
			temp_string.Format(_T("%x"),angle_read);
			m_EDIT_PHASE_CNT.SetWindowText(temp_string);
			angle = (angle_read+1)*2;
			m_EDIT_RPHASE_CNT.Format(_T("%d"),angle);
			UpdateData(FALSE);
            dats="1";
	        pParent->dataupdate_anybits(0x04,2,dats,1);
	}
	}
 end:;
}

void CdetailDlg::ilimitbrake0()
{
	int sel_brake;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7;
	
	lt0 ="0h: 2.6A";
	lt1 ="1h: 3.8A";
	lt2 ="2h: 5.1A";
	lt3 ="3h: 6.4A";
	lt4 ="4h: 7.7A";
	lt5 ="5h: 9.0A";
	lt6 ="6h: 10.2A";
	lt7 ="7h: 11.5A";
		
	sel_brake = m_COMBO_ILIMIT_BRAKE.GetCurSel();
		
	//reset all dropdown lists 
	m_COMBO_ILIMIT_BRAKE.ResetContent();
		
	//set dropdown list for one
	m_COMBO_ILIMIT_BRAKE.InsertString(0, lt0 );
	m_COMBO_ILIMIT_BRAKE.InsertString(1, lt1 );
	m_COMBO_ILIMIT_BRAKE.InsertString(2, lt2 );
	m_COMBO_ILIMIT_BRAKE.InsertString(3, lt3 );
	m_COMBO_ILIMIT_BRAKE.InsertString(4, lt4 );
	m_COMBO_ILIMIT_BRAKE.InsertString(5, lt5 );
	m_COMBO_ILIMIT_BRAKE.InsertString(6, lt6 );
	m_COMBO_ILIMIT_BRAKE.InsertString(7, lt7 );

	m_COMBO_ILIMIT_BRAKE.SetCurSel(sel_brake);
	
}

void CdetailDlg::ilimitbrake1()
{
	int sel_brake;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7;
	
	lt0 ="0h: 5.1A";
	lt1 ="1h: 7.7A";
	lt2 ="2h: 10.2A";
	lt3 ="3h: 12.8A";
	lt4 ="4h: 15.4A";
	lt5 ="5h: 17.9A";
	lt6 ="6h: 20.5A";
	lt7 ="7h: 23A";
		
	sel_brake = m_COMBO_ILIMIT_BRAKE.GetCurSel();
		
	//reset all dropdown lists 
	m_COMBO_ILIMIT_BRAKE.ResetContent();
		
	//set dropdown list for one
	m_COMBO_ILIMIT_BRAKE.InsertString(0, lt0 );
	m_COMBO_ILIMIT_BRAKE.InsertString(1, lt1 );
	m_COMBO_ILIMIT_BRAKE.InsertString(2, lt2 );
	m_COMBO_ILIMIT_BRAKE.InsertString(3, lt3 );
	m_COMBO_ILIMIT_BRAKE.InsertString(4, lt4 );
	m_COMBO_ILIMIT_BRAKE.InsertString(5, lt5 );
	m_COMBO_ILIMIT_BRAKE.InsertString(6, lt6 );
	m_COMBO_ILIMIT_BRAKE.InsertString(7, lt7 );

	m_COMBO_ILIMIT_BRAKE.SetCurSel(sel_brake);
	
}

void CdetailDlg::ilimitbrake3()
{
	int sel_brake;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7;
	
	lt0 ="0h: 7.7A";
	lt1 ="1h: 11.5A";
	lt2 ="2h: 15.4A";
	lt3 ="3h: 19.2A";
	lt4 ="4h: 23.0A";
	lt5 ="5h: 26.9A";
	lt6 ="6h: 30.7A";
	lt7 ="7h: 34.6A";

	sel_brake = m_COMBO_ILIMIT_BRAKE.GetCurSel();
		
	//reset all dropdown lists 
	m_COMBO_ILIMIT_BRAKE.ResetContent();
		
	//set dropdown list for one
	m_COMBO_ILIMIT_BRAKE.InsertString(0, lt0 );
	m_COMBO_ILIMIT_BRAKE.InsertString(1, lt1 );
	m_COMBO_ILIMIT_BRAKE.InsertString(2, lt2 );
	m_COMBO_ILIMIT_BRAKE.InsertString(3, lt3 );
	m_COMBO_ILIMIT_BRAKE.InsertString(4, lt4 );
	m_COMBO_ILIMIT_BRAKE.InsertString(5, lt5 );
	m_COMBO_ILIMIT_BRAKE.InsertString(6, lt6 );
	m_COMBO_ILIMIT_BRAKE.InsertString(7, lt7 );

	m_COMBO_ILIMIT_BRAKE.SetCurSel(sel_brake);
	
}

void CdetailDlg::spinrev0()
{
	int sel_spinrev;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
	CString lt16,lt17,lt18,lt19,lt20,lt21,lt22,lt23,lt24,lt25,lt26,lt27,lt28,lt29,lt30,lt31;
	
	lt0 ="0h: 1 COUNTS";
	lt1 ="1h: 2 COUNTS";
	lt2 ="2h: 3 COUNTS";
	lt3 ="3h: 4 COUNTS";
	lt4 ="4h: 5 COUNTS";
	lt5 ="5h: 6 COUNTS";
	lt6 ="6h: 7 COUNTS";
	lt7 ="7h: 8 COUNTS";
	lt8 ="8h: 9 COUNTS";
	lt9 ="9h: 10 COUNTS";
	lt10 ="Ah: 11 COUNTS";
	lt11 ="Bh: 12 COUNTS";
	lt12 ="Ch: 13 COUNTS";
	lt13 ="Dh: 14 COUNTS";
	lt14 ="Eh: 15 COUNTS";
	lt15 ="Fh: 16 COUNTS";
	lt16 ="10h: 17 COUNTS";
	lt17 ="11h: 18 COUNTS";
	lt18 ="12h: 19 COUNTS";
	lt19 ="13h: 20 COUNTS";
	lt20 ="14h: 21 COUNTS";
	lt21 ="15h: 22 COUNTS";
	lt22 ="16h: 23 COUNTS";
	lt23 ="17h: 24 COUNTS";
	lt24 ="18h: 25 COUNTS";
	lt25 ="19h: 26 COUNTS";
	lt26 ="1Ah: 27 COUNTS";
	lt27 ="1Bh: 28 COUNTS";
	lt28 ="1Ch: 29 COUNTS";
	lt29 ="1Dh: 30 COUNTS";
	lt30 ="1Eh: 31 COUNTS";
	lt31 ="1Fh: 32 COUNTS";
		
	sel_spinrev = m_COMBO_SPIN_REV.GetCurSel();
		
	//reset all dropdown lists 
	m_COMBO_SPIN_REV.ResetContent();
		
	//set dropdown list for one
	m_COMBO_SPIN_REV.InsertString(0, lt0 );
	m_COMBO_SPIN_REV.InsertString(1, lt1 );
	m_COMBO_SPIN_REV.InsertString(2, lt2 );
	m_COMBO_SPIN_REV.InsertString(3, lt3 );
	m_COMBO_SPIN_REV.InsertString(4, lt4 );
	m_COMBO_SPIN_REV.InsertString(5, lt5 );
	m_COMBO_SPIN_REV.InsertString(6, lt6 );
	m_COMBO_SPIN_REV.InsertString(7, lt7 );
	m_COMBO_SPIN_REV.InsertString(8, lt8 );
	m_COMBO_SPIN_REV.InsertString(9, lt9 );
	m_COMBO_SPIN_REV.InsertString(10, lt10 );
	m_COMBO_SPIN_REV.InsertString(11, lt11 );
	m_COMBO_SPIN_REV.InsertString(12, lt12 );
	m_COMBO_SPIN_REV.InsertString(13, lt13 );
	m_COMBO_SPIN_REV.InsertString(14, lt14 );
	m_COMBO_SPIN_REV.InsertString(15, lt15 );
	m_COMBO_SPIN_REV.InsertString(16, lt16 );
	m_COMBO_SPIN_REV.InsertString(17, lt17 );
	m_COMBO_SPIN_REV.InsertString(18, lt18 );
	m_COMBO_SPIN_REV.InsertString(19, lt19 );
	m_COMBO_SPIN_REV.InsertString(20, lt20 );
	m_COMBO_SPIN_REV.InsertString(21, lt21 );
	m_COMBO_SPIN_REV.InsertString(22, lt22 );
	m_COMBO_SPIN_REV.InsertString(23, lt23 );
	m_COMBO_SPIN_REV.InsertString(24, lt24 );
	m_COMBO_SPIN_REV.InsertString(25, lt25 );
	m_COMBO_SPIN_REV.InsertString(26, lt26 );
	m_COMBO_SPIN_REV.InsertString(27, lt27 );
	m_COMBO_SPIN_REV.InsertString(28, lt28 );
	m_COMBO_SPIN_REV.InsertString(29, lt29 );
	m_COMBO_SPIN_REV.InsertString(30, lt30 );
	m_COMBO_SPIN_REV.InsertString(31, lt31 );

	m_COMBO_SPIN_REV.SetCurSel(sel_spinrev);
	
}

void CdetailDlg::spinrev1()
{
	int sel_spinrev;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
	CString lt16,lt17,lt18,lt19,lt20,lt21,lt22,lt23,lt24,lt25,lt26,lt27,lt28,lt29,lt30,lt31;
	
	lt0 ="0h: 33 COUNTS";
	lt1 ="1h: 34 COUNTS";
	lt2 ="2h: 35 COUNTS";
	lt3 ="3h: 36 COUNTS";
	lt4 ="4h: 37 COUNTS";
	lt5 ="5h: 38 COUNTS";
	lt6 ="6h: 39 COUNTS";
	lt7 ="7h: 40 COUNTS";
	lt8 ="8h: 41 COUNTS";
	lt9 ="9h: 42 COUNTS";
	lt10 ="Ah: 43 COUNTS";
	lt11 ="Bh: 44 COUNTS";
	lt12 ="Ch: 45 COUNTS";
	lt13 ="Dh: 46 COUNTS";
	lt14 ="Eh: 47 COUNTS";
	lt15 ="Fh: 48 COUNTS";
	lt16 ="10h: 49 COUNTS";
	lt17 ="11h: 50 COUNTS";
	lt18 ="12h: 51 COUNTS";
	lt19 ="13h: 52 COUNTS";
	lt20 ="14h: 53 COUNTS";
	lt21 ="15h: 54 COUNTS";
	lt22 ="16h: 55 COUNTS";
	lt23 ="17h: 56 COUNTS";
	lt24 ="18h: 57 COUNTS";
	lt25 ="19h: 58 COUNTS";
	lt26 ="1Ah: 59 COUNTS";
	lt27 ="1Bh: 60 COUNTS";
	lt28 ="1Ch: 61 COUNTS";
	lt29 ="1Dh: 62 COUNTS";
	lt30 ="1Eh: 63 COUNTS";
	lt31 ="1Fh: 64 COUNTS";
		
	sel_spinrev = m_COMBO_SPIN_REV.GetCurSel();
		
	//reset all dropdown lists 
	m_COMBO_SPIN_REV.ResetContent();
		
	//set dropdown list for one
	m_COMBO_SPIN_REV.InsertString(0, lt0 );
	m_COMBO_SPIN_REV.InsertString(1, lt1 );
	m_COMBO_SPIN_REV.InsertString(2, lt2 );
	m_COMBO_SPIN_REV.InsertString(3, lt3 );
	m_COMBO_SPIN_REV.InsertString(4, lt4 );
	m_COMBO_SPIN_REV.InsertString(5, lt5 );
	m_COMBO_SPIN_REV.InsertString(6, lt6 );
	m_COMBO_SPIN_REV.InsertString(7, lt7 );
	m_COMBO_SPIN_REV.InsertString(8, lt8 );
	m_COMBO_SPIN_REV.InsertString(9, lt9 );
	m_COMBO_SPIN_REV.InsertString(10, lt10 );
	m_COMBO_SPIN_REV.InsertString(11, lt11 );
	m_COMBO_SPIN_REV.InsertString(12, lt12 );
	m_COMBO_SPIN_REV.InsertString(13, lt13 );
	m_COMBO_SPIN_REV.InsertString(14, lt14 );
	m_COMBO_SPIN_REV.InsertString(15, lt15 );
	m_COMBO_SPIN_REV.InsertString(16, lt16 );
	m_COMBO_SPIN_REV.InsertString(17, lt17 );
	m_COMBO_SPIN_REV.InsertString(18, lt18 );
	m_COMBO_SPIN_REV.InsertString(19, lt19 );
	m_COMBO_SPIN_REV.InsertString(20, lt20 );
	m_COMBO_SPIN_REV.InsertString(21, lt21 );
	m_COMBO_SPIN_REV.InsertString(22, lt22 );
	m_COMBO_SPIN_REV.InsertString(23, lt23 );
	m_COMBO_SPIN_REV.InsertString(24, lt24 );
	m_COMBO_SPIN_REV.InsertString(25, lt25 );
	m_COMBO_SPIN_REV.InsertString(26, lt26 );
	m_COMBO_SPIN_REV.InsertString(27, lt27 );
	m_COMBO_SPIN_REV.InsertString(28, lt28 );
	m_COMBO_SPIN_REV.InsertString(29, lt29 );
	m_COMBO_SPIN_REV.InsertString(30, lt30 );
	m_COMBO_SPIN_REV.InsertString(31, lt31 );

	m_COMBO_SPIN_REV.SetCurSel(sel_spinrev);
	
}

void CdetailDlg::OnBnClickedButtonManualIs()
{
	FILE *fpo;
	FILE *fbo;
	errno_t err;
	CString datbits,dac_bits;
	int query, read_scomm, query_save, query_dac;
	int stageloop, commloop, ilimitloop, ilimitloop_max;
	int temp_int1,temp_int2;            
	int temp_cal,ilimit_over=0;
	int tpos1,tpos2,tpos3,tpos4,tpos5,tpos6;
	int diff1,diff2,diff3,diff4,diff5,diff6;
	int tpos_max,tpos_min,diff_min;
	int dat = 0;
	int length_dat;
	CString dats;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    const TCHAR* fpo_name2 = L"backup_result.xls";
	const TCHAR* fpo_name = L"manual_inductive_sense.xls";

		query_save=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"Do you want to back up previous test result?");
	
		if(query_save == IDCANCEL)
		{
			
		}
		else if(query_save == IDOK)
		{
	  		_wfopen_s(&fbo, fpo_name2, _T("w"));
	    
			fclose(fbo);

			CopyFileW(fpo_name, fpo_name2, false); //back up current save file
		};
	

	if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
		goto end_error;
	};
	
    //read user inputs
	m_EDIT_WDAC.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_WDAC.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck8bits(dat);
    dac_bits = pParent->int2bin_anybits(dat,8);
	if(dat>=103){
		query_dac=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"DAC is more than 50%!\n Continue Inductive sense?");
	
		if(query_dac == IDCANCEL)
		{
			goto end;
		}
		else if(query_dac == IDOK)
		{
	  		
		};
	};

    datbits = "1";
	pParent->dataupdate_anybits(0x02,1,datbits,1); //pwmreg_sel1
	if (!success){goto end;};
	
	if( input_rangecheck == TRUE){
		pParent->dataupdate_anybits(0x18,0,dac_bits,8);  //write to dac
		if (!success){goto end;};
	}

	datbits = "0";
	pParent->dataupdate_anybits(0x04,0,datbits,1); //fan_en=0
	if (!success){goto end;};
	Sleep(5000);
	pParent->dataupdate_anybits(0x01,0,datbits,1); //manual_com_sel
	if (!success){goto end;};
	datbits = "001";
	pParent->dataupdate_anybits(0x03,0,datbits,3); // AB/
	if (!success){goto end;};
	Sleep(1000);
	datbits = "010";
	pParent->dataupdate_anybits(0x03,0,datbits,3); // AC/
	if (!success){goto end;};
	Sleep(1000);
	datbits = "011";
	pParent->dataupdate_anybits(0x03,0,datbits,3); // BC/
	if (!success){goto end;};
	Sleep(1000);
	datbits = "100";
	pParent->dataupdate_anybits(0x03,0,datbits,3); // BA/
	if (!success){goto end;};
	Sleep(1000);
	datbits = "101";
	pParent->dataupdate_anybits(0x03,0,datbits,3); // CA/
	if (!success){goto end;};
	Sleep(1000);
	datbits = "110";
	pParent->dataupdate_anybits(0x03,0,datbits,3); // CB/
	if (!success){goto end;};
	Sleep(1000);
    
	query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"Start Manual Inductive Sense?");
	
	if(query == IDCANCEL)
	{
		goto end;
	}
	else if(query == IDOK)
	{
	  	pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Manual Inductive Sense to start!");
	};
    
	fprintf( fpo, "Ilimit\tTPOS_max\tTPOS_min\tDIFF_min\tPass/Fail\tAB\tAC\tBC\tBA\tCA\tCB\n");

	ilimitloop_max = m_COMBO_ILIMIT_MAX.GetCurSel();

	for(stageloop=1;stageloop<=6;stageloop++){
		datbits = pParent->int2bin_anybits(stageloop,3);
		pParent->dataupdate_anybits(0x03,0,datbits,3); // scomm
		if (!success){goto end;};
		Sleep(1000);
		datbits = "000";
		pParent->dataupdate_anybits(0x03,0,datbits,3); // scomm0
		if (!success){goto end;};
		for(ilimitloop=0;ilimitloop<=ilimitloop_max;ilimitloop++){
			datbits = "1";
			pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sense1
			if (!success){goto end;};
			datbits = pParent->int2bin_anybits(ilimitloop,4);
            pParent->dataupdate_anybits(0x0c,0,datbits,4);  //ilimit
			if (!success){goto end;};
			for(commloop=1;commloop<=6;commloop++){
				datbits = pParent->int2bin_anybits(commloop,3);
				pParent->dataupdate_anybits(0x03,0,datbits,3); // scomm
				if (!success){goto end;};
				Sleep(0.3);
				do{
					read_scomm = pParent->dataread_anybits(0x03,0,3);
					if (!success){goto end;};
				}while(read_scomm!=0);
				    
					temp_int1 = pParent->dataread_anybits(0x17,4,4);
					if (!success){goto end;};
					temp_int2 = pParent->dataread_anybits(0x16,0,8);
					if (!success){goto end;};
					temp_cal = (temp_int1<<8)+temp_int2;
					if(commloop==1){
						tpos1=temp_cal;
						if(tpos1==4095){
                             pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Ilimit Overflow.");
							 ilimit_over=1;
							 goto print_end;
						};
					}else if(commloop==2){
						tpos2=temp_cal;
						if(tpos2==4095){
                             pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Ilimit Overflow.");
							 ilimit_over=1;
							 goto print_end;
						};
					}else if(commloop==3){
						tpos3=temp_cal;
						if(tpos3==4095){
                             pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Ilimit Overflow.");
							 ilimit_over=1;
							 goto print_end;
						};
					}else if(commloop==4){
						tpos4=temp_cal;
						if(tpos4==4095){
                             pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Ilimit Overflow.");
							 ilimit_over=1;
							 goto print_end;
						};
					}else if(commloop==5){
						tpos5=temp_cal;
						if(tpos5==4095){
                             pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Ilimit Overflow.");
							 ilimit_over=1;
							 goto print_end;
						};
					}else if(commloop==6){
						tpos6=temp_cal;
						if(tpos6==4095){
                             pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Ilimit Overflow.");
							 ilimit_over=1;
							 goto print_end;
						};
					};
                    
			    };
                    print_end:;
					if(stageloop==1){
						if(tpos1>tpos2 || tpos1>tpos3 || tpos1>tpos4 || tpos1>tpos5 || tpos1>tpos6 || ilimit_over==1){
							diff1=tpos1-tpos1;
							diff2=tpos2-tpos1;
							diff3=tpos3-tpos1;
							diff4=tpos4-tpos1;
							diff5=tpos5-tpos1;
							diff6=tpos6-tpos1;
							fprintf( fpo, "\%x\tNA\tNA\tNA\tFAIL\t%d\n", ilimitloop,tpos1);
							fprintf( fpo, "\t\t\t\t\t%d\n", diff1);
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Position Sensing Stop.");
							goto end;
						}else{
							diff1=tpos1-tpos1;
							diff2=tpos2-tpos1;
							diff3=tpos3-tpos1;
							diff4=tpos4-tpos1;
							diff5=tpos5-tpos1;
							diff6=tpos6-tpos1;
                            tpos_min=tpos1;
							if(tpos2>=tpos3 && tpos2>=tpos4 && tpos2>=tpos5 && tpos2>=tpos6){
								tpos_max=tpos2;
							}
							if(tpos3>=tpos2 && tpos3>=tpos4 && tpos3>=tpos5 && tpos3>=tpos6){
								tpos_max=tpos3;
							}
							if(tpos4>=tpos3 && tpos4>=tpos2 && tpos4>=tpos5 && tpos4>=tpos6){
								tpos_max=tpos4;
							}
							if(tpos5>=tpos3 && tpos5>=tpos4 && tpos5>=tpos2 && tpos5>=tpos6){
								tpos_max=tpos5;
							}
							if(tpos6>=tpos3 && tpos6>=tpos4 && tpos6>=tpos5 && tpos6>=tpos2){
								tpos_max=tpos6;
							}
							if(diff2<=diff3 && diff2<=diff4 && diff2<=diff5 && diff2<=diff6){
								diff_min=diff2;
							}
							if(diff3<=diff2 && diff3<=diff4 && diff3<=diff5 && diff3<=diff6){
								diff_min=diff3;
							}
							if(diff4<=diff3 && diff4<=diff2 && diff4<=diff5 && diff4<=diff6){
								diff_min=diff4;
							}
							if(diff5<=diff3 && diff5<=diff4 && diff5<=diff2 && diff5<=diff6){
								diff_min=diff5;
							}
							if(diff6<=diff3 && diff6<=diff4 && diff6<=diff5 && diff6<=diff2){
								diff_min=diff6;
							}
							fprintf( fpo, "\%x\t%d\t%d\t%d\tPASS\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos_max,tpos_min,diff_min,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
						};
					}else if(stageloop==2){
						if(tpos2>tpos1 || tpos2>tpos3 || tpos2>tpos4 || tpos2>tpos5 || tpos2>tpos6 || ilimit_over==1){
							diff1=tpos1-tpos2;
							diff2=tpos2-tpos2;
							diff3=tpos3-tpos2;
							diff4=tpos4-tpos2;
							diff5=tpos5-tpos2;
							diff6=tpos6-tpos2;
							fprintf( fpo, "\%x\tNA\tNA\tNA\tFAIL\t%d\t%d\n", ilimitloop,tpos1,tpos2);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\n", diff1,diff2);
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Position Sensing Stop.");
							goto end;
						}else{
							diff1=tpos1-tpos2;
							diff2=tpos2-tpos2;
							diff3=tpos3-tpos2;
							diff4=tpos4-tpos2;
							diff5=tpos5-tpos2;
							diff6=tpos6-tpos2;
							tpos_min=tpos2;
							if(tpos1>=tpos3 && tpos1>=tpos4 && tpos1>=tpos5 && tpos1>=tpos6){
								tpos_max=tpos1;
							}
							if(tpos3>=tpos1 && tpos3>=tpos4 && tpos3>=tpos5 && tpos3>=tpos6){
								tpos_max=tpos3;
							}
							if(tpos4>=tpos3 && tpos4>=tpos1 && tpos4>=tpos5 && tpos4>=tpos6){
								tpos_max=tpos4;
							}
							if(tpos5>=tpos3 && tpos5>=tpos4 && tpos5>=tpos1 && tpos5>=tpos6){
								tpos_max=tpos5;
							}
							if(tpos6>=tpos3 && tpos6>=tpos4 && tpos6>=tpos5 && tpos6>=tpos1){
								tpos_max=tpos6;
							}
							if(diff1<=diff3 && diff1<=diff4 && diff1<=diff5 && diff1<=diff6){
								diff_min=diff1;
							}
							if(diff3<=diff1 && diff3<=diff4 && diff3<=diff5 && diff3<=diff6){
								diff_min=diff3;
							}
							if(diff4<=diff3 && diff4<=diff1 && diff4<=diff5 && diff4<=diff6){
								diff_min=diff4;
							}
							if(diff5<=diff3 && diff5<=diff4 && diff5<=diff1 && diff5<=diff6){
								diff_min=diff5;
							}
							if(diff6<=diff3 && diff6<=diff4 && diff6<=diff5 && diff6<=diff1){
								diff_min=diff6;
							}
							fprintf( fpo, "\%x\t%d\t%d\t%d\tPASS\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos_max,tpos_min,diff_min,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
						};
					}else if(stageloop==3){
						if(tpos3>tpos2 || tpos3>tpos1 || tpos3>tpos4 || tpos3>tpos5 || tpos3>tpos6 || ilimit_over==1){
							diff2=tpos2-tpos3;
							diff1=tpos1-tpos3;
							diff3=tpos3-tpos3;
							diff4=tpos4-tpos3;
							diff5=tpos5-tpos3;
							diff6=tpos6-tpos3;
							fprintf( fpo, "\%x\tNA\tNA\tNA\tFAIL\t%d\t%d\t%d\n", ilimitloop,tpos1,tpos2,tpos3);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\n", diff1,diff2,diff3);
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Position Sensing Stop.");
							goto end;
						}else{
							diff2=tpos2-tpos3;
							diff1=tpos1-tpos3;
							diff3=tpos3-tpos3;
							diff4=tpos4-tpos3;
							diff5=tpos5-tpos3;
							diff6=tpos6-tpos3;
							tpos_min=tpos3;
							if(tpos1>=tpos2 && tpos1>=tpos4 && tpos1>=tpos5 && tpos1>=tpos6){
								tpos_max=tpos1;
							}
							if(tpos2>=tpos1 && tpos2>=tpos4 && tpos2>=tpos5 && tpos2>=tpos6){
								tpos_max=tpos2;
							}
							if(tpos4>=tpos2 && tpos4>=tpos1 && tpos4>=tpos5 && tpos4>=tpos6){
								tpos_max=tpos4;
							}
							if(tpos5>=tpos2 && tpos5>=tpos4 && tpos5>=tpos1 && tpos5>=tpos6){
								tpos_max=tpos5;
							}
							if(tpos6>=tpos2 && tpos6>=tpos4 && tpos6>=tpos5 && tpos6>=tpos1){
								tpos_max=tpos6;
							}
							if(diff1<=diff2 && diff1<=diff4 && diff1<=diff5 && diff1<=diff6){
								diff_min=diff1;
							}
							if(diff2<=diff1 && diff2<=diff4 && diff2<=diff5 && diff2<=diff6){
								diff_min=diff2;
							}
							if(diff4<=diff2 && diff4<=diff1 && diff4<=diff5 && diff4<=diff6){
								diff_min=diff4;
							}
							if(diff5<=diff2 && diff5<=diff4 && diff5<=diff1 && diff5<=diff6){
								diff_min=diff5;
							}
							if(diff6<=diff2 && diff6<=diff4 && diff6<=diff5 && diff6<=diff1){
								diff_min=diff6;
							}
							fprintf( fpo, "\%x\t%d\t%d\t%d\tPASS\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos_max,tpos_min,diff_min,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
						};
					}else if(stageloop==4){
						if(tpos4>tpos2 || tpos4>tpos3 || tpos4>tpos1 || tpos4>tpos5 || tpos4>tpos6 || ilimit_over==1){
							diff2=tpos2-tpos4;
							diff3=tpos3-tpos4;
							diff1=tpos1-tpos4;
							diff4=tpos4-tpos4;
							diff5=tpos5-tpos4;
							diff6=tpos6-tpos4;
							fprintf( fpo, "\%x\tNA\tNA\tNA\tFAIL\t%d\t%d\t%d\t%d\n", ilimitloop,tpos1,tpos2,tpos3,tpos4);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4);
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Position Sensing Stop.");
							goto end;
						}else{
							diff2=tpos2-tpos4;
							diff3=tpos3-tpos4;
							diff1=tpos1-tpos4;
							diff4=tpos4-tpos4;
							diff5=tpos5-tpos4;
							diff6=tpos6-tpos4;
							tpos_min=tpos4;
							if(tpos1>=tpos2 && tpos1>=tpos3 && tpos1>=tpos5 && tpos1>=tpos6){
								tpos_max=tpos1;
							}
							if(tpos2>=tpos1 && tpos2>=tpos3 && tpos2>=tpos5 && tpos2>=tpos6){
								tpos_max=tpos2;
							}
							if(tpos3>=tpos2 && tpos3>=tpos1 && tpos3>=tpos5 && tpos3>=tpos6){
								tpos_max=tpos3;
							}
							if(tpos5>=tpos2 && tpos5>=tpos3 && tpos5>=tpos1 && tpos5>=tpos6){
								tpos_max=tpos5;
							}
							if(tpos6>=tpos2 && tpos6>=tpos3 && tpos6>=tpos5 && tpos6>=tpos1){
								tpos_max=tpos6;
							}
							if(diff1<=diff2 && diff1<=diff3 && diff1<=diff5 && diff1<=diff6){
								diff_min=diff1;
							}
							if(diff2<=diff1 && diff2<=diff3 && diff2<=diff5 && diff2<=diff6){
								diff_min=diff2;
							}
							if(diff3<=diff2 && diff3<=diff1 && diff3<=diff5 && diff3<=diff6){
								diff_min=diff3;
							}
							if(diff5<=diff2 && diff5<=diff3 && diff5<=diff1 && diff5<=diff6){
								diff_min=diff5;
							}
							if(diff6<=diff2 && diff6<=diff3 && diff6<=diff5 && diff6<=diff1){
								diff_min=diff6;
							}
							fprintf( fpo, "\%x\t%d\t%d\t%d\tPASS\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos_max,tpos_min,diff_min,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
						};
					}else if(stageloop==5){
						if(tpos5>tpos2 || tpos5>tpos3 || tpos5>tpos4 || tpos5>tpos1 || tpos5>tpos6 || ilimit_over==1){
							diff2=tpos2-tpos5;
							diff3=tpos3-tpos5;
							diff4=tpos4-tpos5;
							diff1=tpos1-tpos5;
							diff5=tpos5-tpos5;
							diff6=tpos6-tpos5;
							fprintf( fpo, "\%x\tNA\tNA\tNA\tFAIL\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos1,tpos2,tpos3,tpos4,tpos5);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5);
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Position Sensing Stop.");
							goto end;
						}else{
							diff2=tpos2-tpos5;
							diff3=tpos3-tpos5;
							diff4=tpos4-tpos5;
							diff1=tpos1-tpos5;
							diff5=tpos5-tpos5;
							diff6=tpos6-tpos5;
							tpos_min=tpos5;
							if(tpos1>=tpos2 && tpos1>=tpos3 && tpos1>=tpos4 && tpos1>=tpos6){
								tpos_max=tpos1;
							}
							if(tpos2>=tpos1 && tpos2>=tpos3 && tpos2>=tpos4 && tpos2>=tpos6){
								tpos_max=tpos2;
							}
							if(tpos3>=tpos2 && tpos3>=tpos1 && tpos3>=tpos4 && tpos3>=tpos6){
								tpos_max=tpos3;
							}
							if(tpos4>=tpos2 && tpos4>=tpos3 && tpos4>=tpos1 && tpos4>=tpos6){
								tpos_max=tpos4;
							}
							if(tpos6>=tpos2 && tpos6>=tpos3 && tpos6>=tpos4 && tpos6>=tpos1){
								tpos_max=tpos6;
							}
							if(diff1<=diff2 && diff1<=diff3 && diff1<=diff4 && diff1<=diff6){
								diff_min=diff1;
							}
							if(diff2<=diff1 && diff2<=diff3 && diff2<=diff4 && diff2<=diff6){
								diff_min=diff2;
							}
							if(diff3<=diff2 && diff3<=diff1 && diff3<=diff4 && diff3<=diff6){
								diff_min=diff3;
							}
							if(diff4<=diff2 && diff4<=diff3 && diff4<=diff1 && diff4<=diff6){
								diff_min=diff4;
							}
							if(diff6<=diff2 && diff6<=diff3 && diff6<=diff4 && diff6<=diff1){
								diff_min=diff6;
							}
							fprintf( fpo, "\%x\t%d\t%d\t%d\tPASS\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos_max,tpos_min,diff_min,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
						};
					}else if(stageloop==6){
						if(tpos6>tpos2 || tpos6>tpos3 || tpos6>tpos4 || tpos6>tpos5 || tpos6>tpos1 || ilimit_over==1){
							diff1=tpos1-tpos6;
							diff2=tpos2-tpos6;
							diff3=tpos3-tpos6;
							diff4=tpos4-tpos6;
							diff5=tpos5-tpos6;
							diff6=tpos6-tpos6;
							fprintf( fpo, "\%x\tNA\tNA\tNA\tFAIL\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Position Sensing Stop.");
							goto end;
						}else{
							diff1=tpos1-tpos6;
							diff2=tpos2-tpos6;
							diff3=tpos3-tpos6;
							diff4=tpos4-tpos6;
							diff5=tpos5-tpos6;
							diff6=tpos6-tpos6;
							tpos_min=tpos6;
							if(tpos1>=tpos2 && tpos1>=tpos3 && tpos1>=tpos4 && tpos1>=tpos5){
								tpos_max=tpos1;
							}
							if(tpos2>=tpos1 && tpos2>=tpos3 && tpos2>=tpos4 && tpos2>=tpos5){
								tpos_max=tpos2;
							}
							if(tpos3>=tpos2 && tpos3>=tpos1 && tpos3>=tpos4 && tpos3>=tpos5){
								tpos_max=tpos3;
							}
							if(tpos4>=tpos2 && tpos4>=tpos3 && tpos4>=tpos1 && tpos4>=tpos5){
								tpos_max=tpos4;
							}
							if(tpos5>=tpos2 && tpos5>=tpos3 && tpos5>=tpos4 && tpos5>=tpos1){
								tpos_max=tpos5;
							}
							if(diff1<=diff2 && diff1<=diff3 && diff1<=diff4 && diff1<=diff5){
								diff_min=diff1;
							}
							if(diff2<=diff1 && diff2<=diff3 && diff2<=diff4 && diff2<=diff5){
								diff_min=diff2;
							}
							if(diff3<=diff2 && diff3<=diff1 && diff3<=diff4 && diff3<=diff5){
								diff_min=diff3;
							}
							if(diff4<=diff2 && diff4<=diff3 && diff4<=diff1 && diff4<=diff5){
								diff_min=diff4;
							}
							if(diff5<=diff2 && diff5<=diff3 && diff5<=diff4 && diff5<=diff1){
								diff_min=diff5;
							}
							fprintf( fpo, "\%x\t%d\t%d\t%d\tPASS\t%d\t%d\t%d\t%d\t%d\t%d\n", ilimitloop,tpos_max,tpos_min,diff_min,tpos1,tpos2,tpos3,tpos4,tpos5,tpos6);
							fprintf( fpo, "\t\t\t\t\t%d\t%d\t%d\t%d\t%d\t%d\n", diff1,diff2,diff3,diff4,diff5,diff6);
						};
					};
		};
			datbits = "0";
			pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sense0
			if (!success){goto end;};
	};

	end:;
	fclose(fpo);
	end_error:;
}

void CdetailDlg::OnBnClickedRadioHss()
{
	hss_cal=1;
}

void CdetailDlg::OnBnClickedRadioLss()
{
	hss_cal=0;
}

void CdetailDlg::OnBnClickedButtonSetIlimit()
{
int sel_ilimit,length_dat,sel_ilimit_max,sel_ilimit_auto;
	
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7,lt8,lt9,lt10,lt11,lt12,lt13,lt14,lt15;
	CString dats,temp_string;
	double sense_gain;
	char datstring;
	const char* dat;
	BOOL gain_sel;
	
	if(m_CHECK_GAIN_SEL.GetCheck()==TRUE)
	{
			//read user inputs
			m_EDIT_FBRES.GetWindowText(dats);
			fb_res = wcstod(dats, NULL);
			
			//read user inputs
			m_EDIT_REFRES.GetWindowText(dats);
			ref_res = wcstod(dats, NULL);
			
			//read user inputs
			m_EDIT_SENRES.GetWindowText(dats);
			sense_res = wcstod(dats, NULL);
			
			if (ref_res==0)
			{
				sense_gain=1;
			}
			else
			{
				sense_gain = 1+(fb_res/ref_res);
			}

			m_EDIT_SENGAIN.Format(_T("%.1f"),sense_gain);
			UpdateData(FALSE);

			temp_string.Format(_T("%.2f"),fb_res);
			m_EDIT_FBRES.SetWindowText(temp_string);
			temp_string.Format(_T("%.2f"),ref_res);
			m_EDIT_REFRES.SetWindowText(temp_string);
			temp_string.Format(_T("%.5f"),sense_res);
			m_EDIT_SENRES.SetWindowText(temp_string);

			ilim0=0.2/(sense_res*sense_gain);
			ilim1=0.25/(sense_res*sense_gain);
			ilim2=0.3/(sense_res*sense_gain);
			ilim3=0.35/(sense_res*sense_gain);
			ilim4=0.4/(sense_res*sense_gain);
			ilim5=0.45/(sense_res*sense_gain);
			ilim6=0.5/(sense_res*sense_gain);
			ilim7=0.55/(sense_res*sense_gain);
			ilim8=1.05/(sense_res*sense_gain);
			ilim9=1.138/(sense_res*sense_gain);
			ilim10=1.225/(sense_res*sense_gain);
			ilim11=1.313/(sense_res*sense_gain);
			ilim12=1.4/(sense_res*sense_gain);
			ilim13=1.488/(sense_res*sense_gain);
			ilim14=1.575/(sense_res*sense_gain);
			ilim15=1.663/(sense_res*sense_gain);


			lt0.Format(_T("0h: %.2f A"),ilim0);
			lt1.Format(_T("1h: %.2f A"),ilim1);
			lt2.Format(_T("2h: %.2f A"),ilim2);
			lt3.Format(_T("3h: %.2f A"),ilim3);
			lt4.Format(_T("4h: %.2f A"),ilim4);
			lt5.Format(_T("5h: %.2f A"),ilim5);
			lt6.Format(_T("6h: %.2f A"),ilim6);
			lt7.Format(_T("7h: %.2f A"),ilim7);
			lt8.Format(_T("8h: %.2f A"),ilim8);
			lt9.Format(_T("9h: %.2f A"),ilim9);
			lt10.Format(_T("Ah: %.2f A"),ilim10);
			lt11.Format(_T("Bh: %.2f A"),ilim11);
			lt12.Format(_T("Ch: %.2f A"),ilim12);
			lt13.Format(_T("Dh: %.2f A"),ilim13);
			lt14.Format(_T("Eh: %.2f A"),ilim14);
			lt15.Format(_T("Fh: %.2f A"),ilim15);
			
			sel_ilimit = m_COMBO_ILIMIT.GetCurSel();
			sel_ilimit_auto = m_COMBO_ILIMIT_AUTO.GetCurSel();
			sel_ilimit_max = m_COMBO_ILIMIT_MAX.GetCurSel();

			//reset all dropdown lists 
			m_COMBO_ILIMIT.ResetContent();
			m_COMBO_ILIMIT_AUTO.ResetContent();
			m_COMBO_ILIMIT_MAX.ResetContent();
				
			//set dropdown list for one
			m_COMBO_ILIMIT.InsertString(0, lt0 );
			m_COMBO_ILIMIT.InsertString(1, lt1 );
			m_COMBO_ILIMIT.InsertString(2, lt2 );
			m_COMBO_ILIMIT.InsertString(3, lt3 );
			m_COMBO_ILIMIT.InsertString(4, lt4 );
			m_COMBO_ILIMIT.InsertString(5, lt5 );
			m_COMBO_ILIMIT.InsertString(6, lt6 );
			m_COMBO_ILIMIT.InsertString(7, lt7 );
			m_COMBO_ILIMIT.InsertString(8, lt8 );
			m_COMBO_ILIMIT.InsertString(9, lt9 );
			m_COMBO_ILIMIT.InsertString(10, lt10 );
			m_COMBO_ILIMIT.InsertString(11, lt11 );
			m_COMBO_ILIMIT.InsertString(12, lt12 );
			m_COMBO_ILIMIT.InsertString(13, lt13 );
			m_COMBO_ILIMIT.InsertString(14, lt14 );
			m_COMBO_ILIMIT.InsertString(15, lt15 );
			m_COMBO_ILIMIT_AUTO.InsertString(0, lt0 );
			m_COMBO_ILIMIT_AUTO.InsertString(1, lt1 );
			m_COMBO_ILIMIT_AUTO.InsertString(2, lt2 );
			m_COMBO_ILIMIT_AUTO.InsertString(3, lt3 );
			m_COMBO_ILIMIT_AUTO.InsertString(4, lt4 );
			m_COMBO_ILIMIT_AUTO.InsertString(5, lt5 );
			m_COMBO_ILIMIT_AUTO.InsertString(6, lt6 );
			m_COMBO_ILIMIT_AUTO.InsertString(7, lt7 );
			m_COMBO_ILIMIT_AUTO.InsertString(8, lt8 );
			m_COMBO_ILIMIT_AUTO.InsertString(9, lt9 );
			m_COMBO_ILIMIT_AUTO.InsertString(10, lt10 );
			m_COMBO_ILIMIT_AUTO.InsertString(11, lt11 );
			m_COMBO_ILIMIT_AUTO.InsertString(12, lt12 );
			m_COMBO_ILIMIT_AUTO.InsertString(13, lt13 );
			m_COMBO_ILIMIT_AUTO.InsertString(14, lt14 );
			m_COMBO_ILIMIT_AUTO.InsertString(15, lt15 );
			m_COMBO_ILIMIT_MAX.InsertString(0, lt0 );
			m_COMBO_ILIMIT_MAX.InsertString(1, lt1 );
			m_COMBO_ILIMIT_MAX.InsertString(2, lt2 );
			m_COMBO_ILIMIT_MAX.InsertString(3, lt3 );
			m_COMBO_ILIMIT_MAX.InsertString(4, lt4 );
			m_COMBO_ILIMIT_MAX.InsertString(5, lt5 );
			m_COMBO_ILIMIT_MAX.InsertString(6, lt6 );
			m_COMBO_ILIMIT_MAX.InsertString(7, lt7 );
			m_COMBO_ILIMIT_MAX.InsertString(8, lt8 );
			m_COMBO_ILIMIT_MAX.InsertString(9, lt9 );
			m_COMBO_ILIMIT_MAX.InsertString(10, lt10 );
			m_COMBO_ILIMIT_MAX.InsertString(11, lt11 );
			m_COMBO_ILIMIT_MAX.InsertString(12, lt12 );
			m_COMBO_ILIMIT_MAX.InsertString(13, lt13 );
			m_COMBO_ILIMIT_MAX.InsertString(14, lt14 );
			m_COMBO_ILIMIT_MAX.InsertString(15, lt15 );
			
			m_COMBO_ILIMIT.SetCurSel(sel_ilimit);
			m_COMBO_ILIMIT_AUTO.SetCurSel(sel_ilimit_auto);
			m_COMBO_ILIMIT_MAX.SetCurSel(sel_ilimit_max);

	}else if(m_CHECK_GAIN_SEL.GetCheck()==FALSE){

		    //read user inputs
			m_EDIT_SENRES.GetWindowText(dats);
			sense_res = wcstod(dats, NULL);
		
			sense_gain = 1;
			m_EDIT_SENGAIN.Format(_T("%.1f"),sense_gain);
			UpdateData(FALSE);

			temp_string.Format(_T("%.5f"),sense_res);
			m_EDIT_SENRES.SetWindowText(temp_string);

			ilim0=0.2/sense_res;
			ilim1=0.25/sense_res;
			ilim2=0.3/sense_res;
			ilim3=0.35/sense_res;
			ilim4=0.4/sense_res;
			ilim5=0.45/sense_res;
			ilim6=0.5/sense_res;
			ilim7=0.55/sense_res;
			ilim8=1.05/sense_res;
			ilim9=1.138/sense_res;
			ilim10=1.225/sense_res;
			ilim11=1.313/sense_res;
			ilim12=1.4/sense_res;
			ilim13=1.488/sense_res;
			ilim14=1.575/sense_res;
			ilim15=1.663/sense_res;


			lt0.Format(_T("0h: %.2f A"),ilim0);
			lt1.Format(_T("1h: %.2f A"),ilim1);
			lt2.Format(_T("2h: %.2f A"),ilim2);
			lt3.Format(_T("3h: %.2f A"),ilim3);
			lt4.Format(_T("4h: %.2f A"),ilim4);
			lt5.Format(_T("5h: %.2f A"),ilim5);
			lt6.Format(_T("6h: %.2f A"),ilim6);
			lt7.Format(_T("7h: %.2f A"),ilim7);
			lt8.Format(_T("8h: %.2f A"),ilim8);
			lt9.Format(_T("9h: %.2f A"),ilim9);
			lt10.Format(_T("Ah: %.2f A"),ilim10);
			lt11.Format(_T("Bh: %.2f A"),ilim11);
			lt12.Format(_T("Ch: %.2f A"),ilim12);
			lt13.Format(_T("Dh: %.2f A"),ilim13);
			lt14.Format(_T("Eh: %.2f A"),ilim14);
			lt15.Format(_T("Fh: %.2f A"),ilim15);
			
			sel_ilimit = m_COMBO_ILIMIT.GetCurSel();
			sel_ilimit_auto = m_COMBO_ILIMIT_AUTO.GetCurSel();
			sel_ilimit_max = m_COMBO_ILIMIT_MAX.GetCurSel();

			//reset all dropdown lists 
			m_COMBO_ILIMIT.ResetContent();
			m_COMBO_ILIMIT_AUTO.ResetContent();
			m_COMBO_ILIMIT_MAX.ResetContent();
				
			//set dropdown list for one
			m_COMBO_ILIMIT.InsertString(0, lt0 );
			m_COMBO_ILIMIT.InsertString(1, lt1 );
			m_COMBO_ILIMIT.InsertString(2, lt2 );
			m_COMBO_ILIMIT.InsertString(3, lt3 );
			m_COMBO_ILIMIT.InsertString(4, lt4 );
			m_COMBO_ILIMIT.InsertString(5, lt5 );
			m_COMBO_ILIMIT.InsertString(6, lt6 );
			m_COMBO_ILIMIT.InsertString(7, lt7 );
			m_COMBO_ILIMIT.InsertString(8, lt8 );
			m_COMBO_ILIMIT.InsertString(9, lt9 );
			m_COMBO_ILIMIT.InsertString(10, lt10 );
			m_COMBO_ILIMIT.InsertString(11, lt11 );
			m_COMBO_ILIMIT.InsertString(12, lt12 );
			m_COMBO_ILIMIT.InsertString(13, lt13 );
			m_COMBO_ILIMIT.InsertString(14, lt14 );
			m_COMBO_ILIMIT.InsertString(15, lt15 );
			m_COMBO_ILIMIT_AUTO.InsertString(0, lt0 );
			m_COMBO_ILIMIT_AUTO.InsertString(1, lt1 );
			m_COMBO_ILIMIT_AUTO.InsertString(2, lt2 );
			m_COMBO_ILIMIT_AUTO.InsertString(3, lt3 );
			m_COMBO_ILIMIT_AUTO.InsertString(4, lt4 );
			m_COMBO_ILIMIT_AUTO.InsertString(5, lt5 );
			m_COMBO_ILIMIT_AUTO.InsertString(6, lt6 );
			m_COMBO_ILIMIT_AUTO.InsertString(7, lt7 );
			m_COMBO_ILIMIT_AUTO.InsertString(8, lt8 );
			m_COMBO_ILIMIT_AUTO.InsertString(9, lt9 );
			m_COMBO_ILIMIT_AUTO.InsertString(10, lt10 );
			m_COMBO_ILIMIT_AUTO.InsertString(11, lt11 );
			m_COMBO_ILIMIT_AUTO.InsertString(12, lt12 );
			m_COMBO_ILIMIT_AUTO.InsertString(13, lt13 );
			m_COMBO_ILIMIT_AUTO.InsertString(14, lt14 );
			m_COMBO_ILIMIT_AUTO.InsertString(15, lt15 );
			m_COMBO_ILIMIT_MAX.InsertString(0, lt0 );
			m_COMBO_ILIMIT_MAX.InsertString(1, lt1 );
			m_COMBO_ILIMIT_MAX.InsertString(2, lt2 );
			m_COMBO_ILIMIT_MAX.InsertString(3, lt3 );
			m_COMBO_ILIMIT_MAX.InsertString(4, lt4 );
			m_COMBO_ILIMIT_MAX.InsertString(5, lt5 );
			m_COMBO_ILIMIT_MAX.InsertString(6, lt6 );
			m_COMBO_ILIMIT_MAX.InsertString(7, lt7 );
			m_COMBO_ILIMIT_MAX.InsertString(8, lt8 );
			m_COMBO_ILIMIT_MAX.InsertString(9, lt9 );
			m_COMBO_ILIMIT_MAX.InsertString(10, lt10 );
			m_COMBO_ILIMIT_MAX.InsertString(11, lt11 );
			m_COMBO_ILIMIT_MAX.InsertString(12, lt12 );
			m_COMBO_ILIMIT_MAX.InsertString(13, lt13 );
			m_COMBO_ILIMIT_MAX.InsertString(14, lt14 );
			m_COMBO_ILIMIT_MAX.InsertString(15, lt15 );
			
			m_COMBO_ILIMIT.SetCurSel(sel_ilimit);
			m_COMBO_ILIMIT_AUTO.SetCurSel(sel_ilimit_auto);
			m_COMBO_ILIMIT_MAX.SetCurSel(sel_ilimit_max);
		}
}

void CdetailDlg::vardaccount()
{
	int sel_vardac, sel_spcntl;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	sel_spcntl=pParent->dataread_anybits(0x04,1,1);
	
	if(sel_spcntl==0){ //open loop
	
		lt0 ="0h: 4 BEMF";
		lt1 ="1h: 8 BEMF";
		lt2 ="2h: 16 BEMF";
		lt3 ="3h: 32 BEMF";
		lt4 ="4h: 4 BEMF";
		lt5 ="5h: 8 BEMF";
		lt6 ="6h: 16 BEMF";
		lt7 ="7h: 32 BEMF";
			
		sel_vardac = m_COMBO_TS_INIT.GetCurSel();
			
		//reset all dropdown lists 
		m_COMBO_TS_INIT.ResetContent();
			
		//set dropdown list for one
		m_COMBO_TS_INIT.InsertString(0, lt0 );
		m_COMBO_TS_INIT.InsertString(1, lt1 );
		m_COMBO_TS_INIT.InsertString(2, lt2 );
		m_COMBO_TS_INIT.InsertString(3, lt3 );
		m_COMBO_TS_INIT.InsertString(4, lt4 );
		m_COMBO_TS_INIT.InsertString(5, lt5 );
		m_COMBO_TS_INIT.InsertString(6, lt6 );
		m_COMBO_TS_INIT.InsertString(7, lt7 );
	}else{
        
			lt0 ="0h: 4 BEMF";
			lt1 ="1h: 8 BEMF";
			lt2 ="2h: 16 BEMF";
			lt3 ="3h: 32 BEMF";
			lt4 ="4h: 64 BEMF";
			lt5 ="5h: 128 BEMF";
			lt6 ="6h: 1 BEMF";
			lt7 ="7h: 2 BEMF";
				
			sel_vardac = m_COMBO_TS_INIT.GetCurSel();
				
			//reset all dropdown lists 
			m_COMBO_TS_INIT.ResetContent();
				
			//set dropdown list for one
			m_COMBO_TS_INIT.InsertString(0, lt0 );
			m_COMBO_TS_INIT.InsertString(1, lt1 );
			m_COMBO_TS_INIT.InsertString(2, lt2 );
			m_COMBO_TS_INIT.InsertString(3, lt3 );
			m_COMBO_TS_INIT.InsertString(4, lt4 );
			m_COMBO_TS_INIT.InsertString(5, lt5 );
			m_COMBO_TS_INIT.InsertString(6, lt6 );
			m_COMBO_TS_INIT.InsertString(7, lt7 );
		}

	m_COMBO_TS_INIT.SetCurSel(sel_vardac);
	
}



void CdetailDlg::OnBnClickedRadio1pp()
{
	fourpp=2;
	m_COMBO_POLE_PAIR.ResetContent();
	m_COMBO_POLE_PAIR.InsertString(0, L"NA" );
	m_COMBO_POLE_PAIR.SetCurSel(0);
	updatepole();
	OnBnClickedButtonRefcount();
}

void CdetailDlg::OnBnClickedRadio4pp()
{
	fourpp=1;
	m_COMBO_POLE_PAIR.ResetContent();
	m_COMBO_POLE_PAIR.InsertString(0, L"NA" );
	m_COMBO_POLE_PAIR.SetCurSel(0);
	updatepole();
	OnBnClickedButtonRefcount();
}

void CdetailDlg::OnCbnDropdownComboPolePair()
{
/*	int seln;
	
	m_COMBO_POLE_PAIR.ResetContent();
	m_COMBO_POLE_PAIR.InsertString(0, L"0h: 2" );
	m_COMBO_POLE_PAIR.InsertString(1, L"1h: 3" );
	seln = pParent->dataread_anybits(0x07,6,1);	
	m_COMBO_POLE_PAIR.SetCurSel(seln); */
}

void CdetailDlg::updatepole()
{
    int seln;

	seln = m_COMBO_S0S3_RPM.GetCurSel();
    m_COMBO_S0S3_RPM.ResetContent();
	if(fourpp==0){
        m_COMBO_S0S3_RPM.InsertString(0, L"0h: 300 RPM" );
	    m_COMBO_S0S3_RPM.InsertString(1, L"1h: 500 RPM" );
	}else if(fourpp==1){
        m_COMBO_S0S3_RPM.InsertString(0, L"0h: 150 RPM" );
	    m_COMBO_S0S3_RPM.InsertString(1, L"1h: 250 RPM" );
	}else if(fourpp==2){
         m_COMBO_S0S3_RPM.InsertString(0, L"0h: 600 RPM" );
	     m_COMBO_S0S3_RPM.InsertString(1, L"1h: 1000 RPM" );
	};
     m_COMBO_S0S3_RPM.SetCurSel(seln);

   /* seln = m_COMBO_TS_INITBLIND.GetCurSel();
    m_COMBO_TS_INITBLIND.ResetContent();
	if(fourpp==0){
        m_COMBO_TS_INITBLIND.InsertString(0, L"0h: 5k RPM" );
	    m_COMBO_TS_INITBLIND.InsertString(1, L"1h: 10k RPM" );
		m_COMBO_TS_INITBLIND.InsertString(2, L"2h: 15k RPM" );
	    m_COMBO_TS_INITBLIND.InsertString(3, L"3h: 18k RPM" );
	}else if(fourpp==1){
        m_COMBO_TS_INITBLIND.InsertString(0, L"0h: 2.5k RPM" );
	    m_COMBO_TS_INITBLIND.InsertString(1, L"1h: 5k RPM" );
		m_COMBO_TS_INITBLIND.InsertString(2, L"2h: 7.5k RPM" );
	    m_COMBO_TS_INITBLIND.InsertString(3, L"3h: 9k RPM" );
	}else if(fourpp==2){
        m_COMBO_TS_INITBLIND.InsertString(0, L"0h: 10k RPM" );
	    m_COMBO_TS_INITBLIND.InsertString(1, L"1h: 20k RPM" );
		m_COMBO_TS_INITBLIND.InsertString(2, L"2h: 30k RPM" );
	    m_COMBO_TS_INITBLIND.InsertString(3, L"3h: 36k RPM" );
	};
     m_COMBO_TS_INITBLIND.SetCurSel(seln);*/
}


void CdetailDlg::OnBnClickedButtonRefspeed()
{
	int dat = 0;
	int dat1,dat2,dac_value_spd,lowcount_spd,mapdac_spd;
	int temp_int1,temp_int2,temp_int;
	int mask,pp_spd,dirspd,low_sel_spd;
	double temp_float,tarspd,refspd;
	int length_dat;
	CString dats,datbits,datbits1,datbits2;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_REFSPEED.GetWindowText(dats);
	refspd = wcstod(dats, NULL);
		    
	pp_spd = pParent->dataread_anybits(0x07,6,1);
	if (!success){goto end;};
	dirspd = pParent->dataread_anybits(0x01,6,1);
	if (!success){goto end;};
	lowcount_spd = pParent->dataread_anybits(0x22,0,8);
	if (!success){goto end;};

	/*if(low_sel_spd==0){
		lowcount_spd=0;
	}else if(low_sel_spd==1){
		lowcount_spd=26;
	}else if(low_sel_spd==2){
		lowcount_spd=51;
	}else if(low_sel_spd==3){
		lowcount_spd=77;
	}*/

	if(fourpp==0){
	  if(pp_spd==0){
		dac_value_spd = pParent->rreg(0x18);
		if (!success){goto end;};
		mapdac_spd = int(double(((255-lowcount_spd)*(double(dac_value_spd)/255)))+double(lowcount_spd));
		if(refspd!=0){
			temp_int = 249023438/refspd;
			temp_string.Format(_T("%x"),temp_int);
		    m_EDIT_REFCOUNT.SetWindowText(temp_string);
			mask=255;
			temp_int1 = temp_int&mask;
			temp_int2 = (temp_int>>8)&mask;
			input_rangecheck = datarangecheck16bits(temp_int);
			datbits1 = pParent->int2bin_anybits(temp_int1,8);
			datbits2 = pParent->int2bin_anybits(temp_int2,8);

	        if( input_rangecheck == TRUE){
				pParent->dataupdate_anybits(0x1d,0,datbits1,8);
				if (!success){goto end;};
				pParent->dataupdate_anybits(0x1e,0,datbits2,8);
				if (!success){goto end;};
			}
				if(dirspd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),refspd);
					UpdateData(FALSE);
			    }else{
					tarspd = (refspd*mapdac_spd)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tarspd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFCOUNT.SetWindowText(L"NA");
		}
	  }else if(pp_spd==1){
		dac_value_spd = pParent->rreg(0x18);
		if (!success){goto end;};
		mapdac_spd = int(double(((255-lowcount_spd)*(double(dac_value_spd)/255)))+double(lowcount_spd));
		if(refspd!=0){
			temp_int = 166015625/refspd;
			temp_string.Format(_T("%x"),temp_int);
		    m_EDIT_REFCOUNT.SetWindowText(temp_string);
			mask=255;
			temp_int1 = temp_int&mask;
			temp_int2 = (temp_int>>8)&mask;
			input_rangecheck = datarangecheck16bits(temp_int);
			datbits1 = pParent->int2bin_anybits(temp_int1,8);
			datbits2 = pParent->int2bin_anybits(temp_int2,8);

	        if( input_rangecheck == TRUE){
				pParent->dataupdate_anybits(0x1d,0,datbits1,8);
				if (!success){goto end;};
				pParent->dataupdate_anybits(0x1e,0,datbits2,8);
				if (!success){goto end;};
			}
				if(dirspd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),refspd);
					UpdateData(FALSE);
			    }else{
					tarspd = (refspd*mapdac_spd)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tarspd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFCOUNT.SetWindowText(L"NA");
		}
	  }
	}else if(fourpp==1){
		dac_value_spd = pParent->rreg(0x18);
		if (!success){goto end;};
		mapdac_spd = int(double(((255-lowcount_spd)*(double(dac_value_spd)/255)))+double(lowcount_spd));
		if(refspd!=0){
			temp_int = 124511719/refspd;
			temp_string.Format(_T("%x"),temp_int);
		    m_EDIT_REFCOUNT.SetWindowText(temp_string);
			mask=255;
			temp_int1 = temp_int&mask;
			temp_int2 = (temp_int>>8)&mask;
			input_rangecheck = datarangecheck16bits(temp_int);
			datbits1 = pParent->int2bin_anybits(temp_int1,8);
			datbits2 = pParent->int2bin_anybits(temp_int2,8);

	        if( input_rangecheck == TRUE){
				pParent->dataupdate_anybits(0x1d,0,datbits1,8);
				if (!success){goto end;};
				pParent->dataupdate_anybits(0x1e,0,datbits2,8);
				if (!success){goto end;};
			}
				if(dirspd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),refspd);
					UpdateData(FALSE);
			    }else{
					tarspd = (refspd*mapdac_spd)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tarspd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFCOUNT.SetWindowText(L"NA");
		}
	}else if(fourpp==2){
		dac_value_spd = pParent->rreg(0x18);
		if (!success){goto end;};
		mapdac_spd = int(double(((255-lowcount_spd)*(double(dac_value_spd)/255)))+double(lowcount_spd));
		if(refspd!=0){
			temp_int = 498046876/refspd;
			temp_string.Format(_T("%x"),temp_int);
		    m_EDIT_REFCOUNT.SetWindowText(temp_string);
			mask=255;
			temp_int1 = temp_int&mask;
			temp_int2 = (temp_int>>8)&mask;
			input_rangecheck = datarangecheck16bits(temp_int);
			datbits1 = pParent->int2bin_anybits(temp_int1,8);
			datbits2 = pParent->int2bin_anybits(temp_int2,8);

	        if( input_rangecheck == TRUE){
				pParent->dataupdate_anybits(0x1d,0,datbits1,8);
				if (!success){goto end;};
				pParent->dataupdate_anybits(0x1e,0,datbits2,8);
				if (!success){goto end;};
			}
				if(dirspd==1){
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),refspd);
					UpdateData(FALSE);
			    }else{
					tarspd = (refspd*mapdac_spd)/255;
					m_EDIT_TARGET_SPD.Format(_T("%.0f RPM"),tarspd);
					UpdateData(FALSE);
				}
			
		}else{
			m_EDIT_REFCOUNT.SetWindowText(L"NA");
		}
	}

end:;
}

void CdetailDlg::updatedelay()
{
    int seln,msk_seln;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_IS_DELAY.GetCurSel();
    m_COMBO_IS_DELAY.ResetContent();

    msk_seln=pParent->dataread_anybits(0x07,0,4);//com_msk_acc
	if (!success){goto end;};

    if(msk_seln==0){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 79us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==1){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 92us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==2){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 106us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==3){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 132us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==4){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 158us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==5){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 185us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==6){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 211us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==7){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 238us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==8){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 264us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==9){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 291us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==10){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 317us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==11){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 343us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==12){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 370us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==13){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 396us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==14){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 423us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	}else if(msk_seln==15){
        m_COMBO_IS_DELAY.InsertString(0, L"0h: 480us" );
		m_COMBO_IS_DELAY.InsertString(1, L"1h: 600us" );
		m_COMBO_IS_DELAY.InsertString(2, L"2h: 800us" );
		m_COMBO_IS_DELAY.InsertString(3, L"3h: 983us" ); 
	};

    
	m_COMBO_IS_DELAY.SetCurSel(seln);

end:;
}

void CdetailDlg::updateonmskacc()
{
    int seln,msk_seln;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_BLINDSPN_STEP.GetCurSel();//onmsk_acc
    m_COMBO_BLINDSPN_STEP.ResetContent();

    msk_seln=pParent->dataread_anybits(0x06,4,3);
	if (!success){goto end;};
	if(msk_seln==0){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 1.2us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 1.5us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 2.4us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 3.0us" );
	}else if(msk_seln==1){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 1.5us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 2.4us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 3.0us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 3.6us" );
	}else if(msk_seln==2){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 2.4us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 3.0us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 3.6us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 4.2us" );
	}else if(msk_seln==3){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 3.0us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 3.6us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 4.2us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 4.8us" );
	}else if(msk_seln==4){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 3.6us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 4.2us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 4.8us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 3.0us" );
	}else if(msk_seln==5){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 4.2us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 4.8us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 3.6us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 3.6us" );
	}else if(msk_seln==6){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 4.8us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 4.2us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 4.2us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 4.2us" );
	}else if(msk_seln==7){
        m_COMBO_BLINDSPN_STEP.InsertString(0, L"0h: 4.8us" );
		m_COMBO_BLINDSPN_STEP.InsertString(1, L"1h: 4.8us" );
		m_COMBO_BLINDSPN_STEP.InsertString(2, L"2h: 4.8us" );
		m_COMBO_BLINDSPN_STEP.InsertString(3, L"3h: 4.8us" );
	};

   
	m_COMBO_BLINDSPN_STEP.SetCurSel(seln);

end:;
}

void CdetailDlg::OnBnClickedButtonReliabilityTest()
{
	//int dat = 0;
	//int i=0,ontime,offtime;
	//int orig_pos_sns;
	//int pos_sns_reg;
	//CString errmsg,dats,datbits;
	//CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//m_RELY_ON.GetWindowText(dats);
	//ontime = wcstod(dats, NULL);

	//m_EDIT_RELY_OFF.GetWindowText(dats);
	//offtime = wcstod(dats, NULL);

	////save pos_sns
	//int datlength = 1;
	//orig_pos_sns = pParent->dataread_anybits(0x01,3,datlength);

	//do{
	//i++;
	//datbits = "1";
	//pParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 1
	//if (!success){goto end;};
	//Sleep(ontime);
	//datbits = "0";
	//pParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 0
	//if (!success){goto end;};
	//m_EDIT_RELY_CNT.Format(_T("%d"),i);
	//UpdateData(FALSE);
	//UpdateWindow();
	//Sleep(offtime);

	//datbits = "0";
	//pParent->dataupdate_anybits(0x01,3,datbits,1); // set pos_sns = 0
	//if (!success){goto end;};

	//dat = pParent->rreg( 0x19); // read fault
	//if (!success){goto end;};

	//dat = ((dat & 0x78) >> 3);
	//}while(!dat);

	//pos_sns_reg=pParent->rreg(0x01); // restore pos_sns
	//pos_sns_reg |=(orig_pos_sns<<4);
	//pParent->wreg(0x01,pos_sns_reg);
	//if (!success){goto end;};

	//errmsg.Format(_T("No of Spins: %d. Fault = %d"),i, dat);
	//pParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);


	//end:;

	CString errmsg,dats,datbits;
	UINT TimerVal;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	m_RELY_ON.GetWindowText(dats);
	ontime = wcstod(dats, NULL);

	m_EDIT_RELY_OFF.GetWindowText(dats);
	offtime = wcstod(dats, NULL);

	if ((ontime == 0) |(offtime == 0))
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Fan on time and off time!");
		return;
	}

	TimerVal = StartTimer (ontime);

	return;
}

void CdetailDlg::OnBnClickedRadioHex()
{
	hex_percent = 0;
	OnBnClickedButtonReadDac();
}

void CdetailDlg::OnBnClickedRadioPercent()
{
	hex_percent = 1;
	OnBnClickedButtonReadDac();
}

void CdetailDlg::OnBnClickedRadioSpdacS1()
{
	spdac_stage = 1;
	m_EDIT_SPDAC_S1.EnableWindow(1);
	m_EDIT_SPDAC_S2.EnableWindow(0);
	m_EDIT_SPDAC_S4.EnableWindow(0);
}

void CdetailDlg::OnBnClickedRadioSpdacS2()
{
	spdac_stage = 2;
	m_EDIT_SPDAC_S1.EnableWindow(0);
	m_EDIT_SPDAC_S2.EnableWindow(1);
	m_EDIT_SPDAC_S4.EnableWindow(0);
}

void CdetailDlg::OnBnClickedRadioSpdacS4()
{
	spdac_stage = 4;
	m_EDIT_SPDAC_S1.EnableWindow(0);
	m_EDIT_SPDAC_S2.EnableWindow(0);
	m_EDIT_SPDAC_S4.EnableWindow(1);
}

void CdetailDlg::OnBnClickedButtonRpmcount()
{
	/*int bemf_period,bemf_period_cal,pole;
	int rpm_count,auto_spin,comsel;
    
	pole = pParent->dataread_anybits(0x07,6,1);
	if (!success){goto end;};

  if(fourpp==0){
	if(pole==0){ 
	    auto_spin = pParent->dataread_anybits(0x04,0,1);
		if (!success){goto end;};
		if(auto_spin==1){
	       okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
           bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		   if(bemf_period==0){
			   m_EDIT_RPMCOUNT.Format(_T("0"));
	           UpdateData(FALSE);
			   goto end;
		   }
	       bemf_period_cal=4*bemf_period;
           rpm_count = 125000000/bemf_period_cal;
	       m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	       UpdateData(FALSE);
		}else{
			comsel = pParent->dataread_anybits(0x01,0,1);
			if (!success){goto end;};
			if(comsel==1){
				okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
                bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		            if(bemf_period==0){
			               m_EDIT_RPMCOUNT.Format(_T("0"));
	                       UpdateData(FALSE);
			               goto end;
		            }
	            bemf_period_cal=4*bemf_period;
                rpm_count = 125000000/bemf_period_cal;
	            m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	            UpdateData(FALSE);
			}else{
                    m_EDIT_RPMCOUNT.Format(_T("0"));
	                UpdateData(FALSE);
			}
		}
	}else{
        auto_spin = pParent->dataread_anybits(0x04,0,1);
		if (!success){goto end;};
		if(auto_spin==1){
	       okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
           bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		   if(bemf_period==0){
			   m_EDIT_RPMCOUNT.Format(_T("0"));
	           UpdateData(FALSE);
			   goto end;
		   }
	       bemf_period_cal=6*bemf_period;
           rpm_count = 125000000/bemf_period_cal;
	       m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	       UpdateData(FALSE);
		}else{
			comsel = pParent->dataread_anybits(0x01,0,1);
			if (!success){goto end;};
			if(comsel==1){
				okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
                bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		            if(bemf_period==0){
			               m_EDIT_RPMCOUNT.Format(_T("0"));
	                       UpdateData(FALSE);
			               goto end;
		            }
	            bemf_period_cal=6*bemf_period;
                rpm_count = 125000000/bemf_period_cal;
	            m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	            UpdateData(FALSE);
			}else{
                    m_EDIT_RPMCOUNT.Format(_T("0"));
	                UpdateData(FALSE);
			}
		}
	}
  }else if(fourpp==1){
	    auto_spin = pParent->dataread_anybits(0x04,0,1);
		if (!success){goto end;};
		if(auto_spin==1){
	       okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
           bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		   if(bemf_period==0){
			   m_EDIT_RPMCOUNT.Format(_T("0"));
	           UpdateData(FALSE);
			   goto end;
		   }
	       bemf_period_cal=8*bemf_period;
           rpm_count = 125000000/bemf_period_cal;
	       m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	       UpdateData(FALSE);
		}else{
			comsel = pParent->dataread_anybits(0x01,0,1);
			if (!success){goto end;};
			if(comsel==1){
				okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
                bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		            if(bemf_period==0){
			               m_EDIT_RPMCOUNT.Format(_T("0"));
	                       UpdateData(FALSE);
			               goto end;
		            }
	            bemf_period_cal=8*bemf_period;
                rpm_count = 125000000/bemf_period_cal;
	            m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	            UpdateData(FALSE);
			}else{
                    m_EDIT_RPMCOUNT.Format(_T("0"));
	                UpdateData(FALSE);
			}
		}
	}else if(fourpp==2){
		auto_spin = pParent->dataread_anybits(0x04,0,1);
		if (!success){goto end;};
		if(auto_spin==1){
	       okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
           bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		   if(bemf_period==0){
			   m_EDIT_RPMCOUNT.Format(_T("0"));
	           UpdateData(FALSE);
			   goto end;
		   }
	       bemf_period_cal=2*bemf_period;
           rpm_count = 125000000/bemf_period_cal;
	       m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	       UpdateData(FALSE);
		}else{
			comsel = pParent->dataread_anybits(0x01,0,1);
			if (!success){goto end;};
			if(comsel==1){
				okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
                bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
		            if(bemf_period==0){
			               m_EDIT_RPMCOUNT.Format(_T("0"));
	                       UpdateData(FALSE);
			               goto end;
		            }
	            bemf_period_cal=2*bemf_period;
                rpm_count = 125000000/bemf_period_cal;
	            m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
	            UpdateData(FALSE);
			}else{
                    m_EDIT_RPMCOUNT.Format(_T("0"));
	                UpdateData(FALSE);
			}
		}
  }
  end:;*/
}

void CdetailDlg::OnBnClickedButtonRpmlog()
{
	/*FILE *fpo;
	FILE *fbo;
	errno_t err;
	CString datbits,dac_bits;
	int query, read_scomm, query_save, query_dac;
	int stageloop, commloop, ilimitloop, ilimitloop_max;
	int bemf_period,bemf_period_cal;
	int rpm_count=0,auto_spin,comsel;
	int temp_int1,temp_int2;            
	int temp_cal,ilimit_over=0;
	int dat = 0, i=1,totalread,interval,persec=1,forsec;
	int length_dat,interval_count;
	CString dats;
	
    const TCHAR* fpo_name2 = L"log_speed_backup.xls";
	const TCHAR* fpo_name = L"log_speed.xls";

		query_save=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"Do you want to back up previous test result?");
	
		if(query_save == IDCANCEL)
		{
			
		}
		else if(query_save == IDOK)
		{
	  		_wfopen_s(&fbo, fpo_name2, _T("w"));
	    
			fclose(fbo);

			CopyFileW(fpo_name, fpo_name2, false); //back up current save file
		};
	

	if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
						{
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
							goto end_error;
						};
	

    
	query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"Start rpm count read?");
	
	if(query == IDCANCEL)
	{
		goto end;
	}
	else if(query == IDOK)
	{
	  	//pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"rpm count reading to start!");
	};
    
    m_EDIT_PERSEC.GetWindowText(dats);
	interval = wcstod(dats, NULL);

	m_EDIT_FORSEC.GetWindowText(dats);
	forsec = wcstod(dats, NULL);

	totalread=forsec*1000/interval;
	fprintf( fpo, "\%s\t%s\n", "ms","rpm");

	do{
					pole_pair = pParent->dataread_anybits(0x07,6,1);
					if (!success){goto end;};

			if(fourpp==0){	
					if(pole_pair==0){ 
						auto_spin = pParent->dataread_anybits(0x04,0,1);
						if (!success){goto end;};
						if(auto_spin==1){
						   okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							   m_EDIT_RPMCOUNT.Format(_T("0"));
							   UpdateData(FALSE);
							   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
							   goto end;
						   }
						   bemf_period_cal=4*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
						}else{
							comsel = pParent->dataread_anybits(0x01,0,1);
							if (!success){goto end;};
							if(comsel==1){
								okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
								bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
									if(bemf_period==0){
										   m_EDIT_RPMCOUNT.Format(_T("0"));
										   UpdateData(FALSE);
										   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
										   goto end;
									}
								bemf_period_cal=4*bemf_period;
								rpm_count = 125000000/bemf_period_cal;
								m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
								UpdateData(FALSE);
							}else{
									m_EDIT_RPMCOUNT.Format(_T("0"));
									UpdateData(FALSE);
									pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
									goto end;
							}
						}
					}else{
						auto_spin = pParent->dataread_anybits(0x04,0,1);
						if (!success){goto end;};
						if(auto_spin==1){
						   okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							   m_EDIT_RPMCOUNT.Format(_T("0"));
							   UpdateData(FALSE);
							   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
							   goto end;
						   }
						   bemf_period_cal=6*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
						}else{
							comsel = pParent->dataread_anybits(0x01,0,1);
							if (!success){goto end;};
							if(comsel==1){
								okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
								bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
									if(bemf_period==0){
										   m_EDIT_RPMCOUNT.Format(_T("0"));
										   UpdateData(FALSE);
										   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
										   goto end;
									}
								bemf_period_cal=6*bemf_period;
								rpm_count = 125000000/bemf_period_cal;
								m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
								UpdateData(FALSE);
							}else{
									m_EDIT_RPMCOUNT.Format(_T("0"));
									UpdateData(FALSE);
									pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
									goto end;
							}
						}
					}
			}else if(fourpp==1){
				       auto_spin = pParent->dataread_anybits(0x04,0,1);
						if (!success){goto end;};
						if(auto_spin==1){
						   okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							   m_EDIT_RPMCOUNT.Format(_T("0"));
							   UpdateData(FALSE);
							   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
							   goto end;
						   }
						   bemf_period_cal=8*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
						}else{
							comsel = pParent->dataread_anybits(0x01,0,1);
							if (!success){goto end;};
							if(comsel==1){
								okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
								bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
									if(bemf_period==0){
										   m_EDIT_RPMCOUNT.Format(_T("0"));
										   UpdateData(FALSE);
										   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
										   goto end;
									}
								bemf_period_cal=8*bemf_period;
								rpm_count = 125000000/bemf_period_cal;
								m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
								UpdateData(FALSE);
							}else{
									m_EDIT_RPMCOUNT.Format(_T("0"));
									UpdateData(FALSE);
									pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
									goto end;
							}
						}
				}else if(fourpp==2){
					auto_spin = pParent->dataread_anybits(0x04,0,1);
						if (!success){goto end;};
						if(auto_spin==1){
						   okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							   m_EDIT_RPMCOUNT.Format(_T("0"));
							   UpdateData(FALSE);
							   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
							   goto end;
						   }
						   bemf_period_cal=2*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
						}else{
							comsel = pParent->dataread_anybits(0x01,0,1);
							if (!success){goto end;};
							if(comsel==1){
								okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
								bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
									if(bemf_period==0){
										   m_EDIT_RPMCOUNT.Format(_T("0"));
										   UpdateData(FALSE);
										   pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
										   goto end;
									}
								bemf_period_cal=2*bemf_period;
								rpm_count = 125000000/bemf_period_cal;
								m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
								UpdateData(FALSE);
							}else{
									m_EDIT_RPMCOUNT.Format(_T("0"));
									UpdateData(FALSE);
									pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Speed is 0 RPM. Please check the setup!");
									goto end;
							}
						}
			}
				            interval_count=i*interval;
							fprintf( fpo, "\%d\t%d\n", interval_count,rpm_count);
							Sleep(interval);
							dat = pParent->rreg( 0x19); // read fault
							if (!success){goto end;};
							dat = ((dat & 0x78) >> 3);
		i++;
	}while(!dat&&i<=totalread);

	                   pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Log Speed Done!");

	end:;
	fclose(fpo);
	end_error:;*/
}

void CdetailDlg::OnBnClickedButtonSpeedProfile()
{
	/*FILE *fpo;
	FILE *fbo;
	errno_t err;
	CString datbits,dac_bits;
	int query, read_scomm, query_save, query_dac;
	int stageloop, commloop, ilimitloop, ilimitloop_max;
	int bemf_period,bemf_period_cal;
	int rpm_count=0,auto_spin,comsel,interval;
	int temp_int1,temp_int2;            
	int temp_cal,ilimit_over=0;
	int dat = 0, i=0, percent_int;
	double percent;
	double incre_percent;
	int length_dat;
	CString dats;
	
    const TCHAR* fpo_name2 = L"speed_profile_backup.xls";
	const TCHAR* fpo_name = L"speed_profile.xls";

		query_save=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"Do you want to back up previous test result?");
	
		if(query_save == IDCANCEL)
		{
			
		}
		else if(query_save == IDOK)
		{
	  		_wfopen_s(&fbo, fpo_name2, _T("w"));
	    
			fclose(fbo);

			CopyFileW(fpo_name, fpo_name2, false); //back up current save file
		};
	

	if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
						{
							pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
							goto end_error;
						};
	

    
	query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Action", (LPCWSTR)L"Start speed profiling?");
	
	if(query == IDCANCEL)
	{
		goto end;
	}
	else if(query == IDOK)
	{
	  	//pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"rpm count reading to start!");
	};
    
	fprintf( fpo, "\%s\t%s\n", "percent","rpm");
    OnBnClickedRadioPercent();
	OnBnClickedRadioPwmregSel();
	m_EDIT_WDAC.SetWindowText(L"0");

	m_EDIT_PERSEC.GetWindowText(dats);
	interval = wcstod(dats, NULL);

	OnBnClickedButtonWdac();
    m_EDIT_WDAC.GetWindowText(dats);
	percent = wcstod(dats, NULL);
	percent_int = int(percent);
	m_EDIT_INCRE_PERCENT.GetWindowText(dats);
	incre_percent = wcstod(dats, NULL);
	//max_loop = int(100)/int(incre_percent);
	datbits="1";
	pParent->dataupdate_anybits(0x04,0,datbits,1);

	do{
					
			        Sleep(interval);
					pole_pair = pParent->dataread_anybits(0x07,6,1);
					if (!success){goto end;};

			if(fourpp==0){		
					if(pole_pair==0){ 
						   okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							  rpm_count=0;
							  goto end_loop;
						   }
						   bemf_period_cal=4*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
					
					}else{
						   okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							  rpm_count=0;
							  goto end_loop;
						   }
						   bemf_period_cal=6*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
					}
			}else if(fourpp==1){
				            okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							  rpm_count=0;
							  goto end_loop;
						   }
						   bemf_period_cal=8*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
			}else if(fourpp==2){
				            okUsbFrontPanel_UpdateWireOuts(use_debugdlg_detail.xem);
						   bemf_period =  okUsbFrontPanel_GetWireOutValue(use_debugdlg_detail.xem, 0x22);
						   if(bemf_period==0){
							  rpm_count=0;
							  goto end_loop;
						   }
						   bemf_period_cal=2*bemf_period;
						   rpm_count = 125000000/bemf_period_cal;
						   m_EDIT_RPMCOUNT.Format(_T("%d"),rpm_count);
						   UpdateData(FALSE);
			}
							end_loop:;	
					        m_EDIT_WDAC.GetWindowText(dats);
	                        percent = wcstod(dats, NULL);
							percent_int = int(percent);
							fprintf( fpo, "\%.1f\t%d\n", percent,rpm_count);
							Sleep(1000);
							dat = pParent->rreg( 0x19); // read fault
							if (!success){goto end;};
							dat = ((dat & 0x78) >> 3);
        //OnBnClickedButtonWdacup();
          writespeeddac();
		  //i++;
	}while(!dat&&percent_int<100);

	datbits="0";
	pParent->dataupdate_anybits(0x04,0,datbits,1);
    pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Speed profiling done!");
	end:;
	fclose(fpo);
	end_error:;*/
}

void CdetailDlg::writespeeddac()
{
	int gain_counter=0;
	int gain_step=16;
	double datpercent;
	double incre_percent;
	int dat = 0;
	int datr = 0;
	int length_dat;
	int datdac;
	int temp_int;
	int skip=0;
	double temp_float;
	CString gains,temp_string;
	CString dats,dat_string,datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	           m_EDIT_INCRE_PERCENT.GetWindowText(dats);
	           incre_percent = wcstod(dats, NULL);
	
	           m_EDIT_WDAC.GetWindowText(dats);
		       datpercent = wcstod(dats, NULL);
	   	      	   
			   datpercent = datpercent+incre_percent;
			   datdac=datpercent*2.55;
			   //input_rangecheck = datarangecheck8bits(datdac);
			   if(datdac>=255){
				      datdac=255;
					  datpercent=100.0;
					  skip=1;
					}
			   
			   dat_string.Format(_T("%.1f"),datpercent);
			   m_EDIT_WDAC.SetWindowTextW(dat_string);
		
			   //datdac=datpercent*2.55;	
			   datbits = pParent->int2bin_anybits(datdac,8);

				//if( input_rangecheck == TRUE){
				pParent->dataupdate_anybits(0x18,0,datbits,8);
				if (!success){goto end;};
				//}

				if(skip==1){
					m_EDIT_WDAC.SetWindowText(L"100");
					goto end;
				}

				temp_int = pParent->rreg(0x18);
				if (!success){goto end;};
				temp_float = temp_int*0.392157;
				temp_string.Format(_T("%.1f"),temp_float);
				m_EDIT_WDAC.SetWindowText(temp_string);

end:;
}

void CdetailDlg::OnBnClickedButtonMinsp()
{
    int dat = 0;
	int temp_int;
	double temp_cal;
	double temp_float;
	double datpercent;
	int length_dat;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	        m_EDIT_MINSP.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_MINSP.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x20,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x20,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_MINSP.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_MINSP_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			m_EDIT_LOW.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_LOW.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x23,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x23,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_LOW.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_LOW_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			m_EDIT_MID.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_MID.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x27,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x27,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_MID.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_MID_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			m_EDIT_MID2.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_MID2.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x29,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x29,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_MID2.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_MID2_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			m_EDIT_HT.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_HT.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x24,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x24,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_HT.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_HT_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			m_EDIT_LT.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_LT.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x25,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x25,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_LT.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_LT_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			m_EDIT_MT1.GetWindowText(dats);
			
			//get the string length of the inputs
			length_dat = m_EDIT_MT1.LineLength();

			//convert input string into integer
			dat = use_debugdlg_detail.string2int(dats, length_dat);
			input_rangecheck = datarangecheck8bits(dat);
			datbits = pParent->int2bin_anybits(dat,8);

			if( input_rangecheck == TRUE){
			pParent->dataupdate_anybits(0x26,0,datbits,8);
			if (!success){goto end;};
			}

			temp_int = pParent->dataread_anybits(0x26,0,8);
	        if (!success){goto end;};
			temp_string.Format(_T("%x"),temp_int);
			m_EDIT_MT1.SetWindowText(temp_string);
			temp_cal=temp_int*0.39216;
			m_EDIT_MIT1_PERCENT.Format(_T("%.1f%s"),temp_cal,"%");
			UpdateData(FALSE);

			//m_EDIT_MT2.GetWindowText(dats);
			//
			////get the string length of the inputs
			//length_dat = m_EDIT_MT2.LineLength();

			////convert input string into integer
			//dat = use_debugdlg_detail.string2int(dats, length_dat);
			//input_rangecheck = datarangecheck8bits(dat);
			//datbits = pParent->int2bin_anybits(dat,8);

			//if( input_rangecheck == TRUE){
			//pParent->dataupdate_anybits(0x28,0,datbits,8);
			//if (!success){goto end;};
			//}

			//temp_int = pParent->dataread_anybits(0x28,0,8);
	  //      if (!success){goto end;};
	//		temp_string.Format(_T("%x"),temp_int);
			m_EDIT_MT2.SetWindowText(_T("0"));
			//temp_cal=temp_int*0.39216;
			m_EDIT_MIT2_PERCENT.Format(_T("0%s"),"%");
			UpdateData(FALSE);

end:;
}

void CdetailDlg::torque_update()
{
	int sel_torque;
	int i;
	CString lt0,lt1,lt2,lt3,lt4,lt5,lt6,lt7;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	i=pParent->dataread_anybits(0x05,6,1);
	
	if(i==0){
			lt0 ="0h: 0 deg";
			lt1 ="1h: 3.75 deg";
			lt2 ="2h: 7.5 deg";
			lt3 ="3h: 11.25 deg";
			lt4 ="4h: 15 deg";
			lt5 ="5h: 18.75 deg";
			lt6 ="6h: 22.5 deg";
			lt7 ="7h: 26.25 deg";
	}else if(i==1){
            lt0 ="0h: -15 deg";
			lt1 ="1h: -11.25 deg";
			lt2 ="2h: -7.5 deg";
			lt3 ="3h: -3.75 deg";
			lt4 ="4h: 0 deg";
			lt5 ="5h: 3.75 deg";
			lt6 ="6h: 7.5 deg";
			lt7 ="7h: 11.25 deg";
	};
		
	sel_torque = m_COMBO_TORQUE_COARSE.GetCurSel();
		
	//reset all dropdown lists 
	m_COMBO_TORQUE_COARSE.ResetContent();
		
	//set dropdown list for one
	m_COMBO_TORQUE_COARSE.InsertString(0, lt0 );
	m_COMBO_TORQUE_COARSE.InsertString(1, lt1 );
	m_COMBO_TORQUE_COARSE.InsertString(2, lt2 );
	m_COMBO_TORQUE_COARSE.InsertString(3, lt3 );
	m_COMBO_TORQUE_COARSE.InsertString(4, lt4 );
	m_COMBO_TORQUE_COARSE.InsertString(5, lt5 );
	m_COMBO_TORQUE_COARSE.InsertString(6, lt6 );
	m_COMBO_TORQUE_COARSE.InsertString(7, lt7 );

	m_COMBO_TORQUE_COARSE.SetCurSel(sel_torque);
	
}

void CdetailDlg::OnBnClickedCheckPwmFloatDis()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_PWM_FLOAT_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x18,0,datbits,1);
}


void CdetailDlg::OnBnClickedCheckRetryIlimBrk()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_RETRY_ILIM_BRK.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x18,6,datbits,1);
}


void CdetailDlg::OnBnClickedCheckRetryTristate()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_RETRY_TRISTATE.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x18,5,datbits,1);
}

void CdetailDlg::updatesdisrupt()
{
    int dat = 0, datmsk = 0;
	int length_datmsk,temp_int,length_dat;
	double eff_sdisrupt;
	CString dats,datbits,temp_string,datbit,dats_msk;
	
	//read user inputs
	m_EDIT_WIN.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_WIN.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);

	//read user inputs
	m_EDIT_WIN_MASK.GetWindowText(dats_msk);
	
	//get the string length of the inputs
	length_datmsk = m_EDIT_WIN_MASK.LineLength();

	//convert input string into integer
	datmsk = use_debugdlg_detail.string2int(dats_msk, length_datmsk);

	eff_sdisrupt=(dat-datmsk)*0.52083;
	m_EDIT_EFFECTIVE_SDISRUPT.Format(_T("%.2f%s"),eff_sdisrupt,"%");
	UpdateData(FALSE);
}

BOOL CdetailDlg::StopTimer (UINT TimerVal)
{
    if (!KillTimer (TimerVal))
    {
        return FALSE;
    }

    return TRUE;
} 

UINT CdetailDlg::StartTimer (int TimerDuration)
 
{
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    UINT TimerVal;
    TimerVal = SetTimer (IDT_TIMER, TimerDuration, NULL);  // Starting the Timer
    if (TimerVal == 0)
    {
        pParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to obtain timer.");
    }
    return TimerVal;
}



void CdetailDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int bFault;
	CString datbits,errmsg;
	BOOL stop;
	int datlength;
	int orig_pos_sns;
	int pos_sns_reg;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	// TODO: Add your message handler code here and/or call default
	if (Fan_Status == TRUE)
	{
		//off the fan
		datbits = "0";
		pParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 0
		if (!success){return;};

		Fan_Status = FALSE;

		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//reset timer with offtime
		StartTimer (offtime);
		
	}

	else
	{
		fan_cycle_cnt++;

		//save pos_sns
		datlength = 1;
		orig_pos_sns = pParent->dataread_anybits(0x01,3,datlength);
		// set pos_sns = 0
		datbits = "0";
		pParent->dataupdate_anybits(0x01,3,datbits,1); 
		//read fault
		bFault = pParent->rreg( 0x19); // read fault
		if (!success){return;};
		bFault = ((bFault & 0x78) >> 3);

		// restore pos_sns
		pos_sns_reg=pParent->rreg(0x01); 
		pos_sns_reg |=(orig_pos_sns<<4);
		pParent->wreg(0x01,pos_sns_reg);

		if (bFault != 0)
		{
			//kill timer 
			stop = StopTimer(IDT_TIMER);
			if (stop == FALSE)
			{
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
			}

			//display msg
			errmsg.Format(_T("No of Spins: %d. Fault = %d"),fan_cycle_cnt, bFault);
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
			
			return;
		}

		//on the fan
		datbits = "1";
		pParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 1
		if (!success){return;};

		Fan_Status = TRUE;


		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//reset timer with ontime
		StartTimer (ontime);
		

	}

	CDialog::OnTimer(nIDEvent);
}


void CdetailDlg::OnBnClickedButtonMindacClamp()
{
	// TODO: Add your control notification handler code here
	int dat = 0;
	int temp_int;
	int length_dat;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	
	m_EDIT_MINDAC_CLAMP.GetWindowText(dats);
			
	//get the string length of the inputs
	length_dat = m_EDIT_MINDAC_CLAMP.LineLength();

	//convert input string into integer
	dat = use_debugdlg_detail.string2int(dats, length_dat);
	input_rangecheck = datarangecheck8bits(dat);
	datbits = pParent->int2bin_anybits(dat,8);

	if( input_rangecheck == TRUE){
	pParent->dataupdate_anybits(0x28,0,datbits,8);
	if (!success){return;};
	}

	
	temp_int = pParent->dataread_anybits(0x28,0,8);
	if (!success){return;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_MINDAC_CLAMP.SetWindowText(temp_string);

	double temp_cal=temp_int*0.39216;
	m_EDIT_MINDAC_CLAMP_RD.Format(_T("%.1f%s"),temp_cal,"%");
	UpdateData(FALSE); 

}
