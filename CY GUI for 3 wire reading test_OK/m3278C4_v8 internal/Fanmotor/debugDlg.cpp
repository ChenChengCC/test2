// debugDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "FanmotorDlg.h"
#include "debugDlg.h"
#include <string.h>
#include "conio.h"
#include <stdlib.h>
#include <ctype.h>
#include "math.h"

//CFanmotorDlg use_fanmotordlg_main;
COTPcalDlg use_OTPcaldlg_debug;


FILE *stream;
#define FPGA_CONFIGURATION_FILE "mvc1_mb_i2c_usb.bit"
//int TIMEOUT = 100; // 1s

int COMBOWIDTH = 120;
wchar_t REG01[8][120]= {L" OTP_CAL_sel ",
						L" direct_spn ",
						L" - ",
						L" ad_tor_en ",
						L" pos_sns ",
						L" bemf_fil_en ",
						L" sp_tri ",
						L" com_sel "};
wchar_t REG02[8][120]= {L" burn_OTP ",
						L" use_Reg ",
						L" reg2p5_fb_dis ",
						L" tshut_dis ",
						L" osc_dis ",
						L" fault_shut_dis ",
						L" pwm_reg_sel ",
						L" - "};
wchar_t REG03[8][120]= {L" torque[0] ",
						L" torque[1] ",
						L" torque[2] ",
						L" torque[3]",
						L" torque[4] ",
						L" scomm[0] ",
						L" scomm[1] ",
						L" scomm[2] "};
wchar_t REG04[8][120]= {L" tachpin_inv ",
						L" Retry_disable ",
						L" ff_en ",
						L" dll_en ",
						L" six_sine ",
						L" blind_spin_en ",
						L" sp_cntl_en ",
						L" fan_en "};
wchar_t REG05[8][120]= {L" sync_clamp_dis ",
						L" reverse_torque ",
						L" ilimit_brk_msk[0] ",
						L" ilimit_brk_msk[1] ",
						L" ilimit_brk_msk[2] ",
						L" - ",
						L" bhys[0] ",
						L" bhys[1] "};
wchar_t REG06[8][120]= {L" offmsk_en ",
						L" onmsk[0] ",
						L" onmsk[1] ",
						L" onmsk[2] ",
						L" comm_msk[0] ",
						L" comm_msk[1] ",
						L" comm_msk[2] ",
						L" comm_msk[3] "};
wchar_t REG07[8][120]= {L" s0s2_rpm ",
						L" pole_pair ",
						L" onmsk_acc[0] ",
						L" onmsk_acc[1] ",
						L" comm_msk_acc[0] ",
						L" comm_msk_acc[1] ",
						L" comm_msk_acc[2] ",
						L" comm_msk_acc[3] "};
wchar_t REG08[8][120]= {L" sp_win_auto[0] ",
						L" sp_win_auto[1] ",
						L" sp_win_auto[2] ",
						L" sp_win_auto[3] ",
						L" sp_win_auto[4] ",
						L" sp_win_auto[5] ",
						L" pmc_en ",
						L" triphase_det_en "};
wchar_t REG09[8][120]= {L" sp_win[0] ",
						L" sp_win[1] ",
						L" sp_win[2] ",
						L" sp_win[3] ",
						L" sp_win[4] ",
						L" sp_win[5] ",
						L" - ",
						L" pwm_inv "};
wchar_t REG0a[8][120]= {L" winmsk_auto[0] ",
						L" winmsk_auto[1] ",
						L" winmsk_auto[2] ",
						L" winmsk_auto[3] ",
						L" vardac_count[0] ",
						L" vardac_count[1] ",
						L" vardac_count[2] ",
						L" pwm_in_select "};
wchar_t REG0b[8][120]= {L" winmsk[0] ",
						L" winmsk[1] ",
						L" winmsk[2] ",
						L" winmsk[3] ",
						L" handover_spd[0] ",
						L" handover_spd[1] ",
						L" handover_spd[2] ",
						L" pwm_nonoverlap_dis "};

wchar_t REG0c[8][120]= {L" brake_ilim[0] ",
						L" brake_ilim[1] ",
						L" brake_ilim[2] ",
						L" brake_ilim[3] ",
						L" ilimit[0] ",
						L" ilimit[1] ",
						L" ilimit[2] ",
						L" ilimit[3] "};
wchar_t REG0d[8][120]= {L" Ts[0] ",
						L" Ts[1] ",
						L" Ts[2] ",
						L" Ts[3] ",
						L" ilimit_auto_is[0] ",
						L" ilimit_auto_is[1] ",
						L" ilimit_auto_is[2] ",
						L" ilimit_auto_is[3] "};
wchar_t REG0dx[8][120]= {L" spn_time[0] ",
						L" spn_time[1] ",
						L" spn_time[2] ",
						L" spn_acc ",
						L" spn_step[0] ",
						L" spn_step[1] ",
						L" spn_step[2] ",
						L" ilimit_auto_is[3] "};
wchar_t REG0e[8][120]= {L" phase_cnt[0] ",
						L" phase_cnt[1] ",
						L" phase_cnt[2] ",
						L" phase_cnt[3] ",
						L" phase_cnt[4] ",
						L" spn_init_top[0] ",
						L" spn_init_top[1] ",
						L" - "};
wchar_t REG0ex[8][120]= {L" spn_rev[0] ",
						L" spn_rev[1] ",
						L" spn_rev[2] ",
						L" spn_rev[3] ",
						L" spn_rev[4] ",
						L" is_delay[0] ",
						L" is_delay[1] ",
						L" - "};
wchar_t REG0f[8][120]={L" spdac_s1[0] ",
						L" spdac_s1[1] ",
						L" spdac_s1[2] ",
						L" spdac_s1[3] ",
						L" spdac_s1[4] ",
						L" spdac_s1[5] ",
						L" driver_nonoverlap[0] ",
						L" driver_nonoverlap[1] "};
wchar_t REG10[8][120]= {L" spdac_s2[0] ",
						L" spdac_s2[1] ",
						L" spdac_s2[2] ",
						L" spdac_s2[3] ",
						L" spdac_s2[4] ",
						L" spdac_s2[5] ",
						L" var_dac_en ",
						L" - "};
wchar_t REG11[8][120]={L" spdac_s4[0] ",
						L" spdac_s4[1] ",
						L" spdac_s4[2] ",
						L" spdac_s4[3] ",
						L" spdac_s4[4] ",
						L" spdac_s4[5] ",
						L" pwm_freq ",
						L" - "};
wchar_t REG12[8][120]={L" to_s1[0] ",
						L" to_s1[1] ",
						L" to_s1[2] ",
						L" to_s2[0] ",
						L" to_s2[1] ",
						L" to_s2[2] ",
						L" new_stable_spd_en ",
						L" PWM_AVG_EN "};
wchar_t REG13[8][120]={L" test_en1 ",
						L" tmux[0] ",
						L" tmux[1] ",
						L" tmux[2] ",
						L" tmux[3] ",
						L" mode[0] ",
						L" mode[1] ",
						L" tc_ext "};
wchar_t REG14[8][120]= {L" test_en2 ",
						L" max_speed_en ",
						L" uv_dis ",
						L" REG_CRC_CHK_DIS ",
						L" fan_en_off_brk_dis ",
						L" margin_rd_en ",
						L" - ",
						L" - "};
wchar_t REG15[8][120]= {L" adc[0] ",
						L" adc[1] ",
						L" adc[2] ",
						L" adc[3] ",
						L" adc[4] ",
						L" adc[5] ",
						L" adc[6] ",
						L" adc[7] "};
wchar_t REG15a[8][120]= {L" supply_READ[0] ",
						L" supply_READ[1] ",
						L" supply_READ[2] ",
						L" supply_READ[3] ",
						L" supply_READ[4] ",
						L" supply_READ[5] ",
						L" supply_READ[6] ",
						L" supply_READ[7] "};
wchar_t REG16[8][120]= {L" tpos[0] ",
						L" tpos[1] ",
						L" tpos[2] ",
						L" tpos[3] ",
						L" tpos[4] ",
						L" tpos[5] ",
						L" tpos[6] ",
						L" tpos[7] "};
wchar_t REG16a[8][120]= {L" final_spdac[0] ",
						L" final_spdac[1] ",
						L" final_spdac[2] ",
						L" final_spdac[3] ",
						L" final_spdac[4] ",
						L" final_spdac[5] ",
						L" final_spdac[6] ",
						L" final_spdac[7] "};
wchar_t REG17[8][120]= {L" tpos[8] ",
						L" tpos[9] ",
						L" tpos[10] ",
						L" tpos[11] ",
						L" - ",
						L" - ",
						L" - ",
						L" - "};
wchar_t REG17a[8][120]= {L" final_spdac[8] ",
						L" final_spdac[9] ",
						L" final_spdac[10] ",
						L" final_spdac[11] ",
						L" - ",
						L" - ",
						L" - ",
						L" - "};
wchar_t REG18[8][120]= {L" dac[0] ",
						L" dac[1] ",
						L" dac[2] ",
						L" dac[3] ",
						L" dac[4] ",
						L" dac[5] ",
						L" dac[6] ",
						L" dac[7] "};
wchar_t REG18x[8][120]= {L" spdac_wire[0] ",
						L" spdac_wire[1] ",
						L" spdac_wire[2] ",
						L" spdac_wire[3] ",
						L" spdac_wire[4] ",
						L" spdac_wire[5] ",
						L" spdac_wire[6] ",
						L" spdac_wire[7] "};
wchar_t REG19[8][120]= {L" rev[0] ",
						L" rev[1] ",
						L" rev[2] ",
						L" auto_spin_flt[0] ",
						L" auto_spin_flt[1] ",
						L" auto_spin_flt[2] ",
						L" auto_spin_flt[3] ",
						L" auto_spin_done "};
wchar_t REG19x[8][120]= {L" sumout_ff[0] ",
						L" sumout_ff[1] ",
						L" sumout_ff[2] ",
						L" sumout_ff[3] ",
						L" sumout_ff[4] ",
						L" sumout_ff[5] ",
						L" sumout_ff[6] ",
						L" sumout_ff[7] "};
wchar_t REG1a[8][120]= {L" no_sysclk ",
						L" tshut ",
						L" twarn ",
						L" BC ",
						L" OTP_CAL_Done ",
						L" OTP1_Done ",
						L" CRC_match ",
						L" - "};
wchar_t REG1b[8][120]= {L" osc_offset[0] ",
						L" osc_offset[1] ",
						L" osc_offset[2] ",
						L" osc_offset[3] ",
						L" osc_offset[4] ",
						L" osc_tc[0] ",
						L" osc_tc[1] ",
						L" osc_tc[2] "};
wchar_t REG1c[8][120]= {L" ilimit_gain[0] ",
						L" ilimit_gain[1] ",
						L" pwmin_stop_level[0] ",
						L" pwmin_stop_level[1] ",
						L" tachpin_sel[0] ",
						L" tachpin_sel[1] ",
						L" tachpin_sel[2] ",
						L" tachpin_sel[3] "};
wchar_t REG1d[8][120]= {L" REFCOUNT[0] ",
						L" REFCOUNT[1] ",
						L" REFCOUNT[2] ",
						L" REFCOUNT[3] ",
						L" REFCOUNT[4] ",
						L" REFCOUNT[5] ",
						L" REFCOUNT[6] ",
						L" REFCOUNT[7] "};
wchar_t REG1e[8][120]= {L" REFCOUNT[8] ",
						L" REFCOUNT[9] ",
						L" REFCOUNT[10] ",
						L" REFCOUNT[11] ",
						L" REFCOUNT[12] ",
						L" REFCOUNT[13] ",
						L" REFCOUNT[14] ",
						L" REFCOUNT[15] "};
wchar_t REG1f[8][120]= {L" tor_hys_dis ",
						L" pwmin_low_time[0] ",
						L" pwmin_low_time[1] ",
						L" sdisrupt[0] ",
						L" sdisrupt[1] ",
						L" sdisrupt[2] ",
						L" offmsk[0] ",
						L" offmsk[1] "};
wchar_t REG20[8][120]= {L" MINSP[0] ",
						L" MINSP[1] ",
						L" MINSP[2] ",
						L" MINSP[3] ",
						L" MINSP[4] ",
						L" MINSP[5] ",
						L" MINSP[6] ",
						L" MINSP[7] "};
wchar_t REG21[8][120]= {L" REG_CRC_CODE[0] ",
						L" REG_CRC_CODE[1] ",
						L" REG_CRC_CODE[2] ",
						L" REG_CRC_CODE[3] ",
						L" OTP_CRC_CODE[0] ",
						L" OTP_CRC_CODE[1] ",
						L" OTP_CRC_CODE[2] ",
						L" OTP_CRC_CODE[3] "};
wchar_t REG22[8][120]=  {L" NG_TFAST[0] ",
						L" NG_TFAST[1] ",
						L" NG_TFAST[2] ",
						L" PG_TFAST[0] ",
						L" PG_TFAST[1] ",
						L" PG_TFAST[2] ",
						L" pwmin_fs_level[0] ",
						L" pwmin_fs_level[1] "};
wchar_t REG23[8][120]= {L" LOW[0] ",
						L" LOW[1] ",
						L" LOW[2] ",
						L" LOW[3] ",
						L" LOW[4] ",
						L" LOW[5] ",
						L" LOW[6] ",
						L" LOW[7] "};
wchar_t REG24[8][120]= {L" HT[0] ",
						L" HT[1] ",
						L" HT[2] ",
						L" HT[3] ",
						L" HT[4] ",
						L" HT[5] ",
						L" HT[6] ",
						L" HT[7] "};
wchar_t REG25[8][120]= {L" LT[0] ",
						L" LT[1] ",
						L" LT[2] ",
						L" LT[3] ",
						L" LT[4] ",
						L" LT[5] ",
						L" LT[6] ",
						L" LT[7] "};
wchar_t REG26[8][120]= {L" MT1[0] ",
						L" MT1[1] ",
						L" MT1[2] ",
						L" MT1[3] ",
						L" MT1[4] ",
						L" MT1[5] ",
						L" MT1[6] ",
						L" MT1[7] "};
wchar_t REG27[8][120]= {L" MID1[0] ",
						L" MID1[1] ",
						L" MID1[2] ",
						L" MID1[3] ",
						L" MID1[4] ",
						L" MID1[5] ",
						L" MID1[6] ",
						L" MID1[7] "};
wchar_t REG28[8][120]= {L" Mindac_clamp[0] ",
						L" Mindac_clamp[1] ",
						L" Mindac_clamp[2] ",
						L" Mindac_clamp[3] ",
						L" Mindac_clamp[4] ",
						L" Mindac_clamp[5] ",
						L" Mindac_clamp[6] ",
						L" Mindac_clamp[7] "};
wchar_t REG29[8][120]= {L" MID2[0] ",
						L" MID2[1] ",
						L" MID2[2] ",
						L" MID2[3] ",
						L" MID2[4] ",
						L" MID2[5] ",
						L" MID2[6] ",
						L" MID2[7] "};

//CFanmotorDlg use_fanmotordlg_debug;
// CdebugDlg dialog

IMPLEMENT_DYNAMIC(CdebugDlg, CDialog)

CdebugDlg::CdebugDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdebugDlg::IDD, pParent)
	, m_EDIT_RREG_01(_T(""))
	, m_EDIT_RREG_02(_T(""))
	, m_EDIT_RREG_03(_T(""))
	, m_EDIT_RREG_04(_T(""))
	, m_EDIT_RREG_05(_T(""))
	, m_EDIT_RREG_06(_T(""))
	, m_EDIT_RREG_07(_T(""))
	, m_EDIT_RREG_08(_T(""))
	, m_EDIT_RREG_09(_T(""))
	, m_EDIT_RREG_0a(_T(""))
	, m_EDIT_RREG_0b(_T(""))
	, m_EDIT_RREG_0c(_T(""))
	, m_EDIT_RREG_0d(_T(""))
	, m_EDIT_RREG_0e(_T(""))
	, m_EDIT_RREG_0f(_T(""))
	, m_EDIT_RREG_10(_T(""))
	, m_EDIT_RREG_11(_T(""))
	, m_EDIT_RREG_12(_T(""))
	, m_EDIT_RREG_13(_T(""))
	, m_EDIT_RREG_14(_T(""))
	, m_EDIT_RREG_15(_T(""))
	, m_EDIT_RREG_16(_T(""))
	, m_EDIT_RREG_17(_T(""))
	, m_EDIT_RREG_18(_T(""))
	, m_EDIT_RREG_19(_T(""))
	, m_EDIT_RREG_1a(_T(""))
	, m_EDIT_RREG_1b(_T(""))
	, m_EDIT_RREG_1c(_T(""))
	, m_EDIT_RREG_1d(_T(""))
	, m_EDIT_RREG_1e(_T(""))
	, m_EDIT_RREG_1f(_T(""))
	, m_EDIT_RREG_20(_T(""))
	, m_EDIT_RREG_21(_T(""))
	, m_EDIT_RREG_22(_T(""))
	, m_EDIT_RREG_23(_T(""))
	, m_EDIT_RREG_24(_T(""))
	, m_EDIT_RREG_25(_T(""))
	, m_EDIT_RREG_26(_T(""))
	, m_EDIT_RREG_27(_T(""))
	, m_EDIT_RREG_28(_T(""))
	, m_EDIT_RREG_29(_T(""))
{
   m_pParent=pParent;
}

CdebugDlg::~CdebugDlg()
{
}

void CdebugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WREG_01, m_EDIT_WREG_01);
	DDX_Text(pDX, IDC_EDIT_RREG_01, m_EDIT_RREG_01);
	DDX_Control(pDX, IDC_COMBO_RREG_01, m_COMBO_RREG_01);
	DDX_Control(pDX, IDC_EDIT_WREG_02, m_EDIT_WREG_02);
	DDX_Text(pDX, IDC_EDIT_RREG_02, m_EDIT_RREG_02);
	DDX_Control(pDX, IDC_COMBO_RREG_02, m_COMBO_RREG_02);
	DDX_Control(pDX, IDC_EDIT_WREG_03, m_EDIT_WREG_03);
	DDX_Text(pDX, IDC_EDIT_RREG_03, m_EDIT_RREG_03);
	DDX_Control(pDX, IDC_COMBO_RREG_03, m_COMBO_RREG_03);
	DDX_Control(pDX, IDC_EDIT_WREG_04, m_EDIT_WREG_04);
	DDX_Text(pDX, IDC_EDIT_RREG_04, m_EDIT_RREG_04);
	DDX_Control(pDX, IDC_COMBO_RREG_04, m_COMBO_RREG_04);
	DDX_Control(pDX, IDC_EDIT_WREG_05, m_EDIT_WREG_05);
	DDX_Text(pDX, IDC_EDIT_RREG_05, m_EDIT_RREG_05);
	DDX_Control(pDX, IDC_COMBO_RREG_05, m_COMBO_RREG_05);
	DDX_Control(pDX, IDC_EDIT_WREG_06, m_EDIT_WREG_06);
	DDX_Text(pDX, IDC_EDIT_RREG_06, m_EDIT_RREG_06);
	DDX_Control(pDX, IDC_COMBO_RREG_06, m_COMBO_RREG_06);
	DDX_Control(pDX, IDC_EDIT_WREG_07, m_EDIT_WREG_07);
	DDX_Text(pDX, IDC_EDIT_RREG_07, m_EDIT_RREG_07);
	DDX_Control(pDX, IDC_COMBO_RREG_07, m_COMBO_RREG_07);
	DDX_Control(pDX, IDC_EDIT_WREG_08, m_EDIT_WREG_08);
	DDX_Text(pDX, IDC_EDIT_RREG_08, m_EDIT_RREG_08);
	DDX_Control(pDX, IDC_COMBO_RREG_08, m_COMBO_RREG_08);
	DDX_Control(pDX, IDC_EDIT_WREG_09, m_EDIT_WREG_09);
	DDX_Text(pDX, IDC_EDIT_RREG_09, m_EDIT_RREG_09);
	DDX_Control(pDX, IDC_COMBO_RREG_09, m_COMBO_RREG_09);
	DDX_Control(pDX, IDC_EDIT_WREG_0a, m_EDIT_WREG_0a);
	DDX_Text(pDX, IDC_EDIT_RREG_0a, m_EDIT_RREG_0a);
	DDX_Control(pDX, IDC_COMBO_RREG_0a, m_COMBO_RREG_0a);
	DDX_Control(pDX, IDC_EDIT_WREG_0b, m_EDIT_WREG_0b);
	DDX_Text(pDX, IDC_EDIT_RREG_0b, m_EDIT_RREG_0b);
	DDX_Control(pDX, IDC_COMBO_RREG_0b, m_COMBO_RREG_0b);
	DDX_Text(pDX, IDC_EDIT_RREG_0c, m_EDIT_RREG_0c);
	DDX_Control(pDX, IDC_COMBO_RREG_0c, m_COMBO_RREG_0c);
	DDX_Control(pDX, IDC_EDIT_WREG_0d, m_EDIT_WREG_0d);
	DDX_Text(pDX, IDC_EDIT_RREG_0d, m_EDIT_RREG_0d);
	DDX_Control(pDX, IDC_COMBO_RREG_0d, m_COMBO_RREG_0d);
	DDX_Text(pDX, IDC_EDIT_RREG_0e, m_EDIT_RREG_0e);
	DDX_Control(pDX, IDC_COMBO_RREG_0e, m_COMBO_RREG_0e);
	DDX_Text(pDX, IDC_EDIT_RREG_0f, m_EDIT_RREG_0f);
	DDX_Control(pDX, IDC_COMBO_RREG_0f, m_COMBO_RREG_0f);
	DDX_Control(pDX, IDC_EDIT_WREG_10, m_EDIT_WREG_10);
	DDX_Text(pDX, IDC_EDIT_RREG_10, m_EDIT_RREG_10);
	DDX_Control(pDX, IDC_COMBO_RREG_10, m_COMBO_RREG_10);
	DDX_Control(pDX, IDC_EDIT_WREG_11, m_EDIT_WREG_11);
	DDX_Text(pDX, IDC_EDIT_RREG_11, m_EDIT_RREG_11);
	DDX_Control(pDX, IDC_COMBO_RREG_11, m_COMBO_RREG_11);
	DDX_Control(pDX, IDC_EDIT_WREG_12, m_EDIT_WREG_12);
	DDX_Text(pDX, IDC_EDIT_RREG_12, m_EDIT_RREG_12);
	DDX_Control(pDX, IDC_COMBO_RREG_12, m_COMBO_RREG_12);
	DDX_Text(pDX, IDC_EDIT_RREG_13, m_EDIT_RREG_13);
	DDX_Control(pDX, IDC_COMBO_RREG_13, m_COMBO_RREG_13);
	DDX_Text(pDX, IDC_EDIT_RREG_14, m_EDIT_RREG_14);
	DDX_Control(pDX, IDC_COMBO_RREG_14, m_COMBO_RREG_14);
	DDX_Control(pDX, IDC_COMBO_LOAD, m_COMBO_LOAD);
	DDX_Control(pDX, IDC_COMBO_SAVE, m_COMBO_SAVE);
	DDX_Control(pDX, IDC_EDIT_WREG_0c, m_EDIT_WREG_0c);
	DDX_Control(pDX, IDC_EDIT_WREG_0e, m_EDIT_WREG_0e);
	DDX_Control(pDX, IDC_EDIT_WREG_0f, m_EDIT_WREG_0f);
	DDX_Control(pDX, IDC_EDIT_WREG_13, m_EDIT_WREG_13);
	DDX_Control(pDX, IDC_EDIT_WREG_14, m_EDIT_WREG_14);
	DDX_Control(pDX, IDC_EDIT_WREG_15, m_EDIT_WREG_15);
	DDX_Text(pDX, IDC_EDIT_RREG_15, m_EDIT_RREG_15);
	DDX_Control(pDX, IDC_COMBO_RREG_15, m_COMBO_RREG_15);

	DDX_Text(pDX, IDC_EDIT_RREG_16, m_EDIT_RREG_16);
	DDX_Control(pDX, IDC_COMBO_RREG_16, m_COMBO_RREG_16);
	DDX_Text(pDX, IDC_EDIT_RREG_17, m_EDIT_RREG_17);
	DDX_Control(pDX, IDC_COMBO_RREG_17, m_COMBO_RREG_17);
	DDX_Control(pDX, IDC_EDIT_WREG_18, m_EDIT_WREG_18);
	DDX_Text(pDX, IDC_EDIT_RREG_18, m_EDIT_RREG_18);
	DDX_Control(pDX, IDC_COMBO_RREG_18, m_COMBO_RREG_18);
	DDX_Text(pDX, IDC_EDIT_RREG_19, m_EDIT_RREG_19);
	DDX_Control(pDX, IDC_COMBO_RREG_19, m_COMBO_RREG_19);
	DDX_Text(pDX, IDC_EDIT_RREG_1a, m_EDIT_RREG_1a);
	DDX_Control(pDX, IDC_COMBO_RREG_1a, m_COMBO_RREG_1a);
	DDX_Control(pDX, IDC_EDIT_WREG_1B, m_WREG_1B);
	DDX_Text(pDX, IDC_EDIT_RREG_1b, m_EDIT_RREG_1b);
	DDX_Control(pDX, IDC_COMBO_RREG_1b, m_COMBO_RREG_1b);
	DDX_Control(pDX, IDC_EDIT_WREG_1C, m_EDIT_WREG_1C);
	DDX_Text(pDX, IDC_EDIT_RREG_1c, m_EDIT_RREG_1c);
	DDX_Control(pDX, IDC_EDIT_WREG_1D, m_EDIT_WREG_1D);
	DDX_Text(pDX, IDC_EDIT_RREG_1d, m_EDIT_RREG_1d);
	DDX_Control(pDX, IDC_COMBO_RREG_1d, m_COMBO_RREG_1d);
	DDX_Control(pDX, IDC_COMBO_RREG_1c, m_COMBO_RREG_1c);
	DDX_Control(pDX, IDC_EDIT_WREG_1E, m_EDIT_WREG_1E);
	DDX_Text(pDX, IDC_EDIT_RREG_1e, m_EDIT_RREG_1e);
	DDX_Control(pDX, IDC_COMBO_RREG_1e, m_COMBO_RREG_1e);
	DDX_Control(pDX, IDC_EDIT_WREG_1F, m_EDIT_WREG_1F);
	DDX_Text(pDX, IDC_EDIT_RREG_1f, m_EDIT_RREG_1f);
	DDX_Control(pDX, IDC_COMBO_RREG_1f, m_COMBO_RREG_1f);
	DDX_Control(pDX, IDC_EDIT_WREG_20, m_EDIT_WREG_20);
	DDX_Text(pDX, IDC_EDIT_RREG_20, m_EDIT_RREG_20);
	DDX_Control(pDX, IDC_COMBO_RREG_20, m_COMBO_RREG_20);
	DDX_Control(pDX, IDC_EDIT_WREG_2A, m_EDIT_WREG_2A);
	DDX_Control(pDX, IDC_EDIT_WREG_3D, m_EDIT_WREG_3D);
	DDX_Text(pDX, IDC_EDIT_RREG_21, m_EDIT_RREG_21);
	DDX_Control(pDX, IDC_COMBO_RREG_21, m_COMBO_RREG_21);
	DDX_Control(pDX, IDC_EDIT_WREG_22, m_EDIT_WREG_22);
	DDX_Text(pDX, IDC_EDIT_RREG_22, m_EDIT_RREG_22);
	DDX_Control(pDX, IDC_COMBO_RREG_22, m_COMBO_RREG_22);
	DDX_Control(pDX, IDC_EDIT_WREG_23, m_EDIT_WREG_23);
	DDX_Text(pDX, IDC_EDIT_RREG_23, m_EDIT_RREG_23);
	DDX_Control(pDX, IDC_COMBO_RREG_23, m_COMBO_RREG_23);
	DDX_Control(pDX, IDC_EDIT_WREG_24, m_EDIT_WREG_24);
	DDX_Text(pDX, IDC_EDIT_RREG_24, m_EDIT_RREG_24);
	DDX_Control(pDX, IDC_COMBO_RREG_24, m_COMBO_RREG_24);
	DDX_Control(pDX, IDC_EDIT_WREG_25, m_EDIT_WREG_25);
	DDX_Control(pDX, IDC_BUTTON_WREG_25, m_BUTTON_WREG_25);
	DDX_Control(pDX, IDC_COMBO_RREG_25, m_COMBO_RREG_25);
	DDX_Text(pDX, IDC_EDIT_RREG_25, m_EDIT_RREG_25);
	DDX_Control(pDX, IDC_EDIT_WREG_26, m_EDIT_WREG_26);
	DDX_Text(pDX, IDC_EDIT_RREG_26, m_EDIT_RREG_26);
	DDX_Control(pDX, IDC_COMBO_RREG_26, m_COMBO_RREG_26);
	DDX_Control(pDX, IDC_EDIT_WREG_27, m_EDIT_WREG_27);
	DDX_Text(pDX, IDC_EDIT_RREG_27, m_EDIT_RREG_27);
	DDX_Control(pDX, IDC_COMBO_RREG_27, m_COMBO_RREG_27);
	DDX_Control(pDX, IDC_EDIT_WREG_28, m_EDIT_WREG_28);
	DDX_Text(pDX, IDC_EDIT_RREG_28, m_EDIT_RREG_28);
	DDX_Control(pDX, IDC_COMBO_RREG_28, m_COMBO_RREG_28);
	DDX_Control(pDX, IDC_EDIT_WREG_29, m_EDIT_WREG_29);
	DDX_Text(pDX, IDC_EDIT_RREG_29, m_EDIT_RREG_29);
	DDX_Control(pDX, IDC_COMBO_RREG_29, m_COMBO_RREG_29);
	DDX_Control(pDX, IDC_EDIT_WREG_16, m_EDIT_WREG_16);
	DDX_Control(pDX, IDC_EDIT_WREG_17, m_EDIT_WREG_17);
	DDX_Control(pDX, IDC_EDIT_WREG_19, m_EDIT_WREG_19);
	DDX_Control(pDX, IDC_EDIT_WREG_1A, m_EDIT_WREG_1A);
	DDX_Control(pDX, IDC_EDIT_WREG_21, m_EDIT_WREG_21);
}


BEGIN_MESSAGE_MAP(CdebugDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_WREG_01, &CdebugDlg::OnBnClickedButtonWreg01)
	ON_BN_CLICKED(IDC_BUTTON_RREG_01, &CdebugDlg::OnBnClickedButtonRreg01)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_01, &CdebugDlg::OnCbnDropdownComboRreg01)
	ON_BN_CLICKED(IDC_BUTTON_WREG_02, &CdebugDlg::OnBnClickedButtonWreg02)
	ON_BN_CLICKED(IDC_BUTTON_RREG_02, &CdebugDlg::OnBnClickedButtonRreg02)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_02, &CdebugDlg::OnCbnDropdownComboRreg02)
	ON_BN_CLICKED(IDC_BUTTON_WREG_03, &CdebugDlg::OnBnClickedButtonWreg03)
	ON_BN_CLICKED(IDC_BUTTON_RREG_03, &CdebugDlg::OnBnClickedButtonRreg03)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_03, &CdebugDlg::OnCbnDropdownComboRreg03)
	ON_BN_CLICKED(IDC_BUTTON_WREG_04, &CdebugDlg::OnBnClickedButtonWreg04)
	ON_BN_CLICKED(IDC_BUTTON_RREG_04, &CdebugDlg::OnBnClickedButtonRreg04)
	ON_BN_CLICKED(IDC_BUTTON_WREG_05, &CdebugDlg::OnBnClickedButtonWreg05)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_04, &CdebugDlg::OnCbnDropdownComboRreg04)
	ON_BN_CLICKED(IDC_BUTTON_RREG_05, &CdebugDlg::OnBnClickedButtonRreg05)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_05, &CdebugDlg::OnCbnDropdownComboRreg05)
	ON_BN_CLICKED(IDC_BUTTON_WREG_06, &CdebugDlg::OnBnClickedButtonWreg06)
	ON_BN_CLICKED(IDC_BUTTON_RREG_06, &CdebugDlg::OnBnClickedButtonRreg06)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_06, &CdebugDlg::OnCbnDropdownComboRreg06)
	ON_BN_CLICKED(IDC_BUTTON_WREG_07, &CdebugDlg::OnBnClickedButtonWreg07)
	ON_BN_CLICKED(IDC_BUTTON_RREG_07, &CdebugDlg::OnBnClickedButtonRreg07)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_07, &CdebugDlg::OnCbnDropdownComboRreg07)
	ON_BN_CLICKED(IDC_BUTTON_WREG_08, &CdebugDlg::OnBnClickedButtonWreg08)
	ON_BN_CLICKED(IDC_BUTTON_RREG_08, &CdebugDlg::OnBnClickedButtonRreg08)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_08, &CdebugDlg::OnCbnDropdownComboRreg08)
	ON_BN_CLICKED(IDC_BUTTON_WREG_09, &CdebugDlg::OnBnClickedButtonWreg09)
	ON_BN_CLICKED(IDC_BUTTON_RREG_09, &CdebugDlg::OnBnClickedButtonRreg09)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_09, &CdebugDlg::OnCbnDropdownComboRreg09)
	ON_BN_CLICKED(IDC_BUTTON_WREG_0a, &CdebugDlg::OnBnClickedButtonWreg0a)
	ON_BN_CLICKED(IDC_BUTTON_RREG_0a, &CdebugDlg::OnBnClickedButtonRreg0a)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_0a, &CdebugDlg::OnCbnDropdownComboRreg0a)
	ON_BN_CLICKED(IDC_BUTTON_WREG_0b, &CdebugDlg::OnBnClickedButtonWreg0b)
	ON_BN_CLICKED(IDC_BUTTON_RREG_0b, &CdebugDlg::OnBnClickedButtonRreg0b)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_0b, &CdebugDlg::OnCbnDropdownComboRreg0b)
	ON_BN_CLICKED(IDC_BUTTON_RREG_0c, &CdebugDlg::OnBnClickedButtonRreg0c)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_0c, &CdebugDlg::OnCbnDropdownComboRreg0c)
	ON_BN_CLICKED(IDC_BUTTON_WREG_0d, &CdebugDlg::OnBnClickedButtonWreg0d)
	ON_BN_CLICKED(IDC_BUTTON_RREG_0e, &CdebugDlg::OnBnClickedButtonRreg0e)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_0e, &CdebugDlg::OnCbnDropdownComboRreg0e)
	ON_BN_CLICKED(IDC_BUTTON_RREG_0d, &CdebugDlg::OnBnClickedButtonRreg0d)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_0d, &CdebugDlg::OnCbnDropdownComboRreg0d)
	ON_BN_CLICKED(IDC_BUTTON_RREG_0f, &CdebugDlg::OnBnClickedButtonRreg0f)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_0f, &CdebugDlg::OnCbnDropdownComboRreg0f)
	ON_BN_CLICKED(IDC_BUTTON_WREG_10, &CdebugDlg::OnBnClickedButtonWreg10)
	ON_BN_CLICKED(IDC_BUTTON_RREG_10, &CdebugDlg::OnBnClickedButtonRreg10)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_10, &CdebugDlg::OnCbnDropdownComboRreg10)
	ON_BN_CLICKED(IDC_BUTTON_WREG_11, &CdebugDlg::OnBnClickedButtonWreg11)
	ON_BN_CLICKED(IDC_BUTTON_RREG_11, &CdebugDlg::OnBnClickedButtonRreg11)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_11, &CdebugDlg::OnCbnDropdownComboRreg11)
	ON_BN_CLICKED(IDC_BUTTON_WREG_12, &CdebugDlg::OnBnClickedButtonWreg12)
	ON_BN_CLICKED(IDC_BUTTON_RREG_12, &CdebugDlg::OnBnClickedButtonRreg12)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_12, &CdebugDlg::OnCbnDropdownComboRreg12)
	ON_BN_CLICKED(IDC_BUTTON_RREG_13, &CdebugDlg::OnBnClickedButtonRreg13)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_13, &CdebugDlg::OnCbnDropdownComboRreg13)
	ON_BN_CLICKED(IDC_BUTTON_RREG_14, &CdebugDlg::OnBnClickedButtonRreg14)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_14, &CdebugDlg::OnCbnDropdownComboRreg14)
	ON_BN_CLICKED(IDC_BUTTON_START, &CdebugDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_WRITEALL, &CdebugDlg::OnBnClickedButtonWriteall)
	ON_BN_CLICKED(IDC_BUTTON_READALL, &CdebugDlg::OnBnClickedButtonReadall)
	ON_CBN_DROPDOWN(IDC_COMBO_LOAD, &CdebugDlg::OnCbnDropdownComboLoad)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CdebugDlg::OnBnClickedButtonLoad)
	ON_CBN_DROPDOWN(IDC_COMBO_SAVE, &CdebugDlg::OnCbnDropdownComboSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CdebugDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_WREG_0c, &CdebugDlg::OnBnClickedButtonWreg0c)
	ON_BN_CLICKED(IDC_BUTTON_WREG_0e, &CdebugDlg::OnBnClickedButtonWreg0e)
	ON_BN_CLICKED(IDC_BUTTON_WREG_0f, &CdebugDlg::OnBnClickedButtonWreg0f)
	ON_BN_CLICKED(IDC_BUTTON_WREG_13, &CdebugDlg::OnBnClickedButtonWreg13)
	ON_BN_CLICKED(IDC_BUTTON_WREG_14, &CdebugDlg::OnBnClickedButtonWreg14)
	ON_BN_CLICKED(IDC_BUTTON_WREG_15, &CdebugDlg::OnBnClickedButtonWreg15)
	ON_BN_CLICKED(IDC_BUTTON_RREG_15, &CdebugDlg::OnBnClickedButtonRreg15)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_15, &CdebugDlg::OnCbnDropdownComboRreg15)
	ON_BN_CLICKED(IDC_BUTTON_RREG_16, &CdebugDlg::OnBnClickedButtonRreg16)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_16, &CdebugDlg::OnCbnDropdownComboRreg16)
	ON_BN_CLICKED(IDC_BUTTON_RREG_17, &CdebugDlg::OnBnClickedButtonRreg17)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_17, &CdebugDlg::OnCbnDropdownComboRreg17)
	ON_BN_CLICKED(IDC_BUTTON_WREG_18, &CdebugDlg::OnBnClickedButtonWreg18)
	ON_BN_CLICKED(IDC_BUTTON_RREG_18, &CdebugDlg::OnBnClickedButtonRreg18)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_18, &CdebugDlg::OnCbnDropdownComboRreg18)
	ON_BN_CLICKED(IDC_BUTTON_RREG_19, &CdebugDlg::OnBnClickedButtonRreg19)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_19, &CdebugDlg::OnCbnDropdownComboRreg19)
	ON_BN_CLICKED(IDC_BUTTON_RREG_1a, &CdebugDlg::OnBnClickedButtonRreg1a)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_1a, &CdebugDlg::OnCbnDropdownComboRreg1a)
	ON_BN_CLICKED(IDC_BUTTON_WREG_1B, &CdebugDlg::OnBnClickedButtonWreg1b)
	ON_BN_CLICKED(IDC_BUTTON_RREG_1b, &CdebugDlg::OnBnClickedButtonRreg1b)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_1b, &CdebugDlg::OnCbnDropdownComboRreg1b)
	ON_BN_CLICKED(IDC_BUTTON_WREG_1C, &CdebugDlg::OnBnClickedButtonWreg1c)
	ON_BN_CLICKED(IDC_BUTTON_RREG_1c, &CdebugDlg::OnBnClickedButtonRreg1c)
	ON_BN_CLICKED(IDC_BUTTON_WREG_1D, &CdebugDlg::OnBnClickedButtonWreg1d)
	ON_BN_CLICKED(IDC_BUTTON_RREG_1d, &CdebugDlg::OnBnClickedButtonRreg1d)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_1d, &CdebugDlg::OnCbnDropdownComboRreg1d)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_1c, &CdebugDlg::OnCbnDropdownComboRreg1c)
	ON_BN_CLICKED(IDC_BUTTON_WREG_1E, &CdebugDlg::OnBnClickedButtonWreg1e)
	ON_BN_CLICKED(IDC_BUTTON_RREG_1e, &CdebugDlg::OnBnClickedButtonRreg1e)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_1e, &CdebugDlg::OnCbnDropdownComboRreg1e)
	ON_BN_CLICKED(IDC_BUTTON_WREG_1F, &CdebugDlg::OnBnClickedButtonWreg1f)
	ON_BN_CLICKED(IDC_BUTTON_RREG_1f, &CdebugDlg::OnBnClickedButtonRreg1f)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_1f, &CdebugDlg::OnCbnDropdownComboRreg1f)
	ON_BN_CLICKED(IDC_BUTTON_WREG_20, &CdebugDlg::OnBnClickedButtonWreg20)
	ON_BN_CLICKED(IDC_BUTTON_RREG_20, &CdebugDlg::OnBnClickedButtonRreg20)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_20, &CdebugDlg::OnCbnDropdownComboRreg20)
	ON_BN_CLICKED(IDC_BUTTON_WREG_2A, &CdebugDlg::OnBnClickedButtonWreg2a)
	ON_BN_CLICKED(IDC_BUTTON_WREG_3D, &CdebugDlg::OnBnClickedButtonWreg3d)
	ON_BN_CLICKED(IDC_BUTTON_RREG_21, &CdebugDlg::OnBnClickedButtonRreg21)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_21, &CdebugDlg::OnCbnDropdownComboRreg21)
	ON_BN_CLICKED(IDC_BUTTON_WREG_22, &CdebugDlg::OnBnClickedButtonWreg22)
	ON_BN_CLICKED(IDC_BUTTON_RREG_22, &CdebugDlg::OnBnClickedButtonRreg22)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_22, &CdebugDlg::OnCbnDropdownComboRreg22)
	ON_BN_CLICKED(IDC_BUTTON_WREG_23, &CdebugDlg::OnBnClickedButtonWreg23)
	ON_BN_CLICKED(IDC_BUTTON_RREG_23, &CdebugDlg::OnBnClickedButtonRreg23)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_23, &CdebugDlg::OnCbnDropdownComboRreg23)
	ON_BN_CLICKED(IDC_BUTTON_WREG_24, &CdebugDlg::OnBnClickedButtonWreg24)
	ON_BN_CLICKED(IDC_BUTTON_RREG_24, &CdebugDlg::OnBnClickedButtonRreg24)
	ON_BN_CLICKED(IDC_BUTTON_WREG_25, &CdebugDlg::OnBnClickedButtonWreg25)
	ON_BN_CLICKED(IDC_BUTTON_RREG_25, &CdebugDlg::OnBnClickedButtonRreg25)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_25, &CdebugDlg::OnCbnDropdownComboRreg25)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_24, &CdebugDlg::OnCbnDropdownComboRreg24)
	ON_BN_CLICKED(IDC_BUTTON_WREG_26, &CdebugDlg::OnBnClickedButtonWreg26)
	ON_BN_CLICKED(IDC_BUTTON_RREG_26, &CdebugDlg::OnBnClickedButtonRreg26)
	ON_BN_CLICKED(IDC_BUTTON_WREG_27, &CdebugDlg::OnBnClickedButtonWreg27)
	ON_BN_CLICKED(IDC_BUTTON_RREG_27, &CdebugDlg::OnBnClickedButtonRreg27)
	ON_BN_CLICKED(IDC_BUTTON_WREG_28, &CdebugDlg::OnBnClickedButtonWreg28)
	ON_BN_CLICKED(IDC_BUTTON_RREG_28, &CdebugDlg::OnBnClickedButtonRreg28)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_26, &CdebugDlg::OnCbnDropdownComboRreg26)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_27, &CdebugDlg::OnCbnDropdownComboRreg27)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_28, &CdebugDlg::OnCbnDropdownComboRreg28)
	ON_BN_CLICKED(IDC_BUTTON_WREG_29, &CdebugDlg::OnBnClickedButtonWreg29)
	ON_BN_CLICKED(IDC_BUTTON_RREG_29, &CdebugDlg::OnBnClickedButtonRreg29)
	ON_CBN_DROPDOWN(IDC_COMBO_RREG_29, &CdebugDlg::OnCbnDropdownComboRreg29)
//	ON_CBN_SELCHANGE(IDC_COMBO_LOAD, &CdebugDlg::OnCbnSelchangeComboLoad)
ON_CBN_SETFOCUS(IDC_COMBO_LOAD, &CdebugDlg::OnCbnSetfocusComboLoad)
ON_CBN_SETFOCUS(IDC_COMBO_SAVE, &CdebugDlg::OnCbnSetfocusComboSave)
ON_CBN_EDITCHANGE(IDC_COMBO_LOAD, &CdebugDlg::OnCbnEditchangeComboLoad)
ON_CBN_SELCHANGE(IDC_COMBO_LOAD, &CdebugDlg::OnCbnSelchangeComboLoad)
ON_CBN_EDITUPDATE(IDC_COMBO_LOAD, &CdebugDlg::OnCbnEditupdateComboLoad)
ON_CBN_EDITCHANGE(IDC_COMBO_SAVE, &CdebugDlg::OnCbnEditchangeComboSave)
ON_BN_CLICKED(IDC_BUTTON_WREG_16, &CdebugDlg::OnBnClickedButtonWreg16)
ON_BN_CLICKED(IDC_BUTTON_WREG_17, &CdebugDlg::OnBnClickedButtonWreg17)
ON_BN_CLICKED(IDC_BUTTON_WREG_19, &CdebugDlg::OnBnClickedButtonWreg19)
ON_BN_CLICKED(IDC_BUTTON_WREG_1A, &CdebugDlg::OnBnClickedButtonWreg1a)
ON_BN_CLICKED(IDC_BUTTON_WREG_21, &CdebugDlg::OnBnClickedButtonWreg21)
END_MESSAGE_MAP()


// CdebugDlg message handlers

BOOL CdebugDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//OnBnClickedButtonStart();


	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_LOAD, 0, DDL_READWRITE);

	//TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	//::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_SAVE, 0, DDL_READWRITE);

	OnBnClickedButtonReadall();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CdebugDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->debugdlg = NULL;
    delete this;
}

void CdebugDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void CdebugDlg::OnClose() 
{
	DestroyWindow();
	//detaildlg->EndDialog(TRUE);

}

void CdebugDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CdebugDlg::OnOK() 
{
}

void CdebugDlg::OnCancel() 
{
}

//string to integer conversion
int CdebugDlg::string2int(CString temp, int length)
{	
	int value = 0;
	int i,j;
	UINT64	multiplier = 1;
	char	*hexTable = "0123456789abcdef", *p;

	for (i = length - 1; i >= 0; i--){
			p = hexTable;
			j = 0;
			while (*p++ != temp[i]) j++;
			value += (j * multiplier);
			multiplier *= 16;
	}
	return value;
}

void CdebugDlg::InitUSB ( void )
{
	/*success = 1;
	// Initialize the DLL and load all entrypoints.
	if (FALSE == okFrontPanelDLL_LoadLib(NULL)) {
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Communication is not available.\nPlease check if okFrontPanel.dll exists!");
		success = 0;
	}
	xem = okUsbFrontPanel_Construct();
	okUsbFrontPanel_OpenBySerial(xem,NULL);*/
}

void CdebugDlg::InitFPGA ( void )
{
	/*success = 1;
	//check whether FPGA is already initialised
	if(TRUE == okUsbFrontPanel_IsFrontPanelEnabled(xem)){
			goto end;
		}
	// Initialize the FPGA with our configuration bitfile.
	if (okUsbFrontPanel_ConfigureFPGA(xem, FPGA_CONFIGURATION_FILE) == 0) {
		//fprintf( stream, "\nFPGA configuration complete!\n"); 
	}
	else {
		//pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Communication is not available.\nPlease check:\n1. USB Cable connection\n2. Opal Kelly Board connection\n3. if mvc1_mb_i2c_usb.bit file exists!");
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Communication is not available.\nPlease check:\n1. USB Cable connection\n2. Opal Kelly Board connection\n");
		success = 0;
	}
	Sleep(10);
	okUsbFrontPanel_ActivateTriggerIn(xem, 0x40, 0); // to RESET all FFs
end:;*/
}

void CdebugDlg::InitPLL ( void )
{
	/*// Initialize PLL
   	pll = okPLL22150_Construct();
    // Read the EEPROM PLL configuration and program the PLL using it.
	okUsbFrontPanel_GetEepromPLL22150Configuration(xem, pll);
	okPLL22150_SetDiv1(pll, ok_DivSrc_VCO, 8); // for M3278, sysclk 50MHz (8), 40MHz (10)
	okPLL22150_SetOutputSource(pll, 0, ok_ClkSrc22150_Div1ByN);
	okPLL22150_SetOutputEnable(pll, 0, true);	  
	okUsbFrontPanel_SetPLL22150Configuration(xem, pll);
	okPLL22150_Destruct(pll);*/
}








void CdebugDlg::OnBnClickedButtonWreg01()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_01.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_01.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x01,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg01();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg01()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x81);
    
	// display data
	m_EDIT_RREG_01.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg01()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	OnBnClickedButtonRreg01();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x01);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_01.ResetContent();
	m_COMBO_RREG_01.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG01[7-i]);
			m_COMBO_RREG_01.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg02()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_02.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_02.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x02,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg02();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg02()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x82);
    
	// display data
	m_EDIT_RREG_02.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg02()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg02();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x02);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_02.ResetContent();
	m_COMBO_RREG_02.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG02[7-i]);
			m_COMBO_RREG_02.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg03()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_03.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_03.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x03,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg03();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg03()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x83);
    
	// display data
	m_EDIT_RREG_03.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg03()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg03();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x03);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_03.ResetContent();
	m_COMBO_RREG_03.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG03[7-i]);
			m_COMBO_RREG_03.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg04()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_04.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_04.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x04,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg04();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg04()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x84);
    
	// display data
	m_EDIT_RREG_04.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg04()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg04();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x04);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_04.ResetContent();
	m_COMBO_RREG_04.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG04[7-i]);
			m_COMBO_RREG_04.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg05()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_05.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_05.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x05,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg05();
	};
end:;
}


void CdebugDlg::OnBnClickedButtonRreg05()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x85);
    
	// display data
	m_EDIT_RREG_05.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg05()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg05();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x05);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_05.ResetContent();
	m_COMBO_RREG_05.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG05[7-i]);
			m_COMBO_RREG_05.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg06()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_06.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_06.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x06,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg06();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg06()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x86);
    
	// display data
	m_EDIT_RREG_06.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg06()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg06();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x06);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_06.ResetContent();
	m_COMBO_RREG_06.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG06[7-i]);
			m_COMBO_RREG_06.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg07()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_07.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_07.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x07,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg07();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg07()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x87);
    
	// display data
	m_EDIT_RREG_07.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg07()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg07();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x07);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_07.ResetContent();
	m_COMBO_RREG_07.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG07[7-i]);
			m_COMBO_RREG_07.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg08()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_08.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_08.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x08,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg08();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg08()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x88);
    
	// display data
	m_EDIT_RREG_08.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg08()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg08();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x08);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_08.ResetContent();
	m_COMBO_RREG_08.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG08[7-i]);
			m_COMBO_RREG_08.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg09()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_09.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_09.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x09,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg09();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg09()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x89);
    
	// display data
	m_EDIT_RREG_09.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg09()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg09();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x09);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_09.ResetContent();
	m_COMBO_RREG_09.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG09[7-i]);
			m_COMBO_RREG_09.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg0a()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_0a.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_0a.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x0a,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg0a();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg0a()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x8a);
    
	// display data
	m_EDIT_RREG_0a.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg0a()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg0a();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x0a);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_0a.ResetContent();
	m_COMBO_RREG_0a.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0a[7-i]);
			m_COMBO_RREG_0a.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg0b()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_0b.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_0b.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x0b,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg0b();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg0b()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x8b);
    
	// display data
	m_EDIT_RREG_0b.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg0b()
{
	int i,regval,mask;
	int is_blind=0;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg0b();
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_0b.ResetContent();
	m_COMBO_RREG_0b.SetDroppedWidth(COMBOWIDTH);
	
		   // read reg
	       datr = pParent->rreg(0x0b);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0b[7-i]);
			m_COMBO_RREG_0b.AddString(str);
	}
	
end:;
}

void CdebugDlg::OnBnClickedButtonWreg0c()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_0c.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_0c.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x0c,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg0c();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg0c()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x8c);
    
	// display data
	m_EDIT_RREG_0c.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg0c()
{
	int i,regval;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg0c();
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_0c.ResetContent();
	m_COMBO_RREG_0c.SetDroppedWidth(COMBOWIDTH);
	
		   // read reg
	       datr = pParent->rreg(0x0c);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0c[7-i]);
			m_COMBO_RREG_0c.AddString(str);
	}
	
end:;
}

void CdebugDlg::OnBnClickedButtonWreg0d()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_0d.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_0d.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x0d,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg0d();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg0d()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x8d);
    
	// display data
	m_EDIT_RREG_0d.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg0d()
{
	int i,regval,mask;
	int is_blind=0;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg0d();
	if (!success){goto end;};

	regval = pParent->rreg(0x04);
	if (!success){goto end;};
	mask=1;
	is_blind=(regval>>5)&mask;

	// display data per bit
	m_COMBO_RREG_0d.ResetContent();
	m_COMBO_RREG_0d.SetDroppedWidth(COMBOWIDTH);
	if(is_blind==0){
		   // read reg
	       datr = pParent->rreg(0x0d);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0d[7-i]);
			m_COMBO_RREG_0d.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x0d);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0dx[7-i]);
			m_COMBO_RREG_0d.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg0e()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_0e.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_0e.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x0e,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg0e();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg0e()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x8e);
    
	// display data
	m_EDIT_RREG_0e.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg0e()
{
	int i,regval,mask;
	int is_blind=0;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg0e();
	if (!success){goto end;};

	regval = pParent->rreg(0x04);
	if (!success){goto end;};
	mask=1;
	is_blind=(regval>>5)&mask;

	// display data per bit
	m_COMBO_RREG_0e.ResetContent();
	m_COMBO_RREG_0e.SetDroppedWidth(COMBOWIDTH);
	if(is_blind==0){
		   // read reg
	       datr = pParent->rreg(0x0e);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0e[7-i]);
			m_COMBO_RREG_0e.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x0e);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0ex[7-i]);
			m_COMBO_RREG_0e.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg0f()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_0f.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_0f.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x0f,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg0f();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg0f()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x8f);
    
	// display data
	m_EDIT_RREG_0f.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg0f()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg0f();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x0f);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_0f.ResetContent();
	m_COMBO_RREG_0f.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG0f[7-i]);
			m_COMBO_RREG_0f.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg10()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_10.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_10.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x10,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg10();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg10()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x90);
    
	// display data
	m_EDIT_RREG_10.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg10()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg10();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x10);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_10.ResetContent();
	m_COMBO_RREG_10.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG10[7-i]);
			m_COMBO_RREG_10.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg11()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_11.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_11.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x11,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg11();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg11()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x91);
    
	// display data
	m_EDIT_RREG_11.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg11()
{
	int i,regval;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg11();
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_11.ResetContent();
	m_COMBO_RREG_11.SetDroppedWidth(COMBOWIDTH);
	
		   // read reg
	       datr = pParent->rreg(0x11);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG11[7-i]);
			m_COMBO_RREG_11.AddString(str);
	}
	
end:;
}

void CdebugDlg::OnBnClickedButtonWreg12()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_12.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_12.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x12,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg12();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg12()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x92);
    
	// display data
	m_EDIT_RREG_12.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg12()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg12();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x12);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_12.ResetContent();
	m_COMBO_RREG_12.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG12[7-i]);
			m_COMBO_RREG_12.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg13()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_13.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_13.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x13,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg13();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg13()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x93);
    
	// display data
	m_EDIT_RREG_13.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg13()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg13();
	if (!success){goto end;};

	// read reg
	datr = pParent->rreg(0x13);
	if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_13.ResetContent();
	m_COMBO_RREG_13.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG13[7-i]);
			m_COMBO_RREG_13.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg14()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_14.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_14.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x14,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg14();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg14()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x94);
    
	// display data
	m_EDIT_RREG_14.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg14()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg14();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x14);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_14.ResetContent();
	m_COMBO_RREG_14.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG14[7-i]);
			m_COMBO_RREG_14.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg15()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_15.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_15.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x15,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg15();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg15()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x95);
    
	// display data
	m_EDIT_RREG_15.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg15()
{
	int i;
	int datr = 0, regval,temp_bit,mask;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg15();
	if (!success){goto end;};

	regval = pParent->rreg(0x01);
	if (!success){goto end;};
	mask=1;
	temp_bit=(regval>>4)&mask;

	// display data per bit
	m_COMBO_RREG_15.ResetContent();
	m_COMBO_RREG_15.SetDroppedWidth(COMBOWIDTH);
	
	if(temp_bit==0){
		   // read reg
	       datr = pParent->rreg(0x15);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG15a[7-i]);
			m_COMBO_RREG_15.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x15);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG15[7-i]);
			m_COMBO_RREG_15.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonRreg16()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x96);
    
	// display data
	m_EDIT_RREG_16.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg16()
{
	int i,regval,temp_bit,mask;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg16();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x16);
	 if (!success){goto end;};
    
	regval = pParent->rreg(0x01);
	if (!success){goto end;};
	mask=1;
	temp_bit=(regval>>4)&mask;

	// display data per bit
	m_COMBO_RREG_16.ResetContent();
	m_COMBO_RREG_16.SetDroppedWidth(COMBOWIDTH);
	
	if(temp_bit==1){
		   // read reg
	       datr = pParent->rreg(0x16);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG16[7-i]);
			m_COMBO_RREG_16.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x16);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG16a[7-i]);
			m_COMBO_RREG_16.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonRreg17()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x97);
    
	// display data
	m_EDIT_RREG_17.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg17()
{
	int i,regval,temp_bit,mask;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg17();
	if (!success){goto end;};

	    
	regval = pParent->rreg(0x01);
	if (!success){goto end;};
	mask=1;
	temp_bit=(regval>>4)&mask;

	// display data per bit
	m_COMBO_RREG_17.ResetContent();
	m_COMBO_RREG_17.SetDroppedWidth(COMBOWIDTH);
	
	if(temp_bit==1){
		   // read reg
	       datr = pParent->rreg(0x17);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG17[7-i]);
			m_COMBO_RREG_17.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x17);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG17a[7-i]);
			m_COMBO_RREG_17.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg18()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_18.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_18.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x18,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg18();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg18()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x98);
    
	// display data
	m_EDIT_RREG_18.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg18()
{
	int i,regval,temp_bit,mask;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg18();
	if (!success){goto end;};

	   
	regval = pParent->rreg(0x02);
	if (!success){goto end;};
	mask=1;
	temp_bit=(regval>>6)&mask;

	// display data per bit
	m_COMBO_RREG_18.ResetContent();
	m_COMBO_RREG_18.SetDroppedWidth(COMBOWIDTH);
	
	if(temp_bit==1){
		   // read reg
	       datr = pParent->rreg(0x18);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG18[7-i]);
			m_COMBO_RREG_18.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x18);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG18x[7-i]);
			m_COMBO_RREG_18.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonRreg19()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x99);
    
	// display data
	m_EDIT_RREG_19.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg19()
{
	int i,regval,temp_bit,mask;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg19();
	if (!success){goto end;};

	    
	regval = pParent->rreg(0x01);
	if (!success){goto end;};
	mask=1;
	temp_bit=(regval>>4)&mask;

	// display data per bit
	m_COMBO_RREG_19.ResetContent();
	m_COMBO_RREG_19.SetDroppedWidth(COMBOWIDTH);
	
	if(temp_bit==0){
		   // read reg
	       datr = pParent->rreg(0x19);
	       if (!success){goto end;};
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG19[7-i]);
			m_COMBO_RREG_19.AddString(str);
	}
	}else{
		   // read reg
	       datr = pParent->rreg(0x19);
	       if (!success){goto end;};
    for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG19x[7-i]);
			m_COMBO_RREG_19.AddString(str);
	}
	}
end:;
}

void CdebugDlg::OnBnClickedButtonRreg1a()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x9a);
    
	// display data
	m_EDIT_RREG_1a.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg1a()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg1a();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x1a);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_1a.ResetContent();
	m_COMBO_RREG_1a.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG1a[7-i]);
			m_COMBO_RREG_1a.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg1b()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_WREG_1B.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_WREG_1B.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x1b,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg1b();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg1b()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x9b);
    
	// display data
	m_EDIT_RREG_1b.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg1b()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg1b();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x1b);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_1b.ResetContent();
	m_COMBO_RREG_1b.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG1b[7-i]);
			m_COMBO_RREG_1b.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg1c()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_1C.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_1C.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x1c,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg1c();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg1c()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x9c);
    
	// display data
	m_EDIT_RREG_1c.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg1c()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg1c();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x1c);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_1c.ResetContent();
	m_COMBO_RREG_1c.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG1c[7-i]);
			m_COMBO_RREG_1c.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg1d()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_1D.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_1D.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x1d,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg1d();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg1d()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x1d);
    
	// display data
	m_EDIT_RREG_1d.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg1d()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg1d();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x1d);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_1d.ResetContent();
	m_COMBO_RREG_1d.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG1d[7-i]);
			m_COMBO_RREG_1d.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg1e()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_1E.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_1E.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x1e,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg1e();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg1e()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x1e);
    
	// display data
	m_EDIT_RREG_1e.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg1e()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg1e();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x1e);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_1e.ResetContent();
	m_COMBO_RREG_1e.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG1e[7-i]);
			m_COMBO_RREG_1e.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg1f()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_1F.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_1F.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x1f,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg1f();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg1f()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x1f);
    
	// display data
	m_EDIT_RREG_1f.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg1f()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg1f();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x1f);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_1f.ResetContent();
	m_COMBO_RREG_1f.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG1f[7-i]);
			m_COMBO_RREG_1f.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg20()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_20.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_20.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x20,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg20();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg20()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x20);
    
	// display data
	m_EDIT_RREG_20.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg20()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg20();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x20);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_20.ResetContent();
	m_COMBO_RREG_20.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG20[7-i]);
			m_COMBO_RREG_20.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonRreg21()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0xa1);
    
	// display data
	m_EDIT_RREG_21.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg21()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg21();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x21);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_21.ResetContent();
	m_COMBO_RREG_21.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG21[7-i]);
			m_COMBO_RREG_21.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg22()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_22.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_22.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x22,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg22();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg22()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0xa2);
    
	// display data
	m_EDIT_RREG_22.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg22()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg22();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x22);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_22.ResetContent();
	m_COMBO_RREG_22.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG22[7-i]);
			m_COMBO_RREG_22.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg23()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_23.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_23.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x23,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg23();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg23()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0xa3);
    
	// display data
	m_EDIT_RREG_23.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg23()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg23();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x23);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_23.ResetContent();
	m_COMBO_RREG_23.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG23[7-i]);
			m_COMBO_RREG_23.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg24()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_24.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_24.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x24,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg24();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg24()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x24);
    
	// display data
	m_EDIT_RREG_24.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg24()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg24();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x24);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_24.ResetContent();
	m_COMBO_RREG_24.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG24[7-i]);
			m_COMBO_RREG_24.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg25()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_25.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_25.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x25,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg25();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg25()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x25);
    
	// display data
	m_EDIT_RREG_25.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg25()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg25();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x25);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_25.ResetContent();
	m_COMBO_RREG_25.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG25[7-i]);
			m_COMBO_RREG_25.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg26()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_26.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_26.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x26,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg26();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg26()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x26);
    
	// display data
	m_EDIT_RREG_26.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg26()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg26();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x26);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_26.ResetContent();
	m_COMBO_RREG_26.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG26[7-i]);
			m_COMBO_RREG_26.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg27()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_27.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_27.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x27,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg27();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg27()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x27);
    
	// display data
	m_EDIT_RREG_27.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg27()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg27();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x27);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_27.ResetContent();
	m_COMBO_RREG_27.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG27[7-i]);
			m_COMBO_RREG_27.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg28()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_28.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_28.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x28,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg28();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg28()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x28);
    
	// display data
	m_EDIT_RREG_28.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg28()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg28();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x28);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_28.ResetContent();
	m_COMBO_RREG_28.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG28[7-i]);
			m_COMBO_RREG_28.AddString(str);
	}
end:;
}

void CdebugDlg::OnBnClickedButtonWreg29()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_29.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_29.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x29,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg29();
	};
end:;
}

void CdebugDlg::OnBnClickedButtonRreg29()
{
	int datr = 0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = pParent->rreg(0x29);
    
	// display data
	m_EDIT_RREG_29.Format(_T("%x"), datr);
	UpdateData(FALSE);
}

void CdebugDlg::OnCbnDropdownComboRreg29()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	CString str;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonRreg29();
	if (!success){goto end;};

	 // read reg
	 datr = pParent->rreg(0x29);
	 if (!success){goto end;};

	// display data per bit
	m_COMBO_RREG_29.ResetContent();
	m_COMBO_RREG_29.SetDroppedWidth(COMBOWIDTH);
	for (i=0;i<8;i++)
	{
			datr_bit = (datr>>(7-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, REG29[7-i]);
			m_COMBO_RREG_29.AddString(str);
	}
end:;
}


void CdebugDlg::OnBnClickedButtonStart()
{
//	use_OTPcaldlg_debug.ClearRegVal();

}

void CdebugDlg::OnBnClickedButtonWriteall()
{
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	pParent->fOTP=0;

	    OnBnClickedButtonWreg01();
	if (!success){goto end;};
		/*OnBnClickedButtonWreg02();
	if (!success){goto end;};
		OnBnClickedButtonWreg03();
	if (!success){goto end;};
		OnBnClickedButtonWreg04();
	if (!success){goto end;};
		OnBnClickedButtonWreg05();
	if (!success){goto end;};
		OnBnClickedButtonWreg06();
	if (!success){goto end;};*/
		OnBnClickedButtonWreg07();
	if (!success){goto end;};
		OnBnClickedButtonWreg08();
	if (!success){goto end;};
		OnBnClickedButtonWreg09();
	if (!success){goto end;};
		OnBnClickedButtonWreg0a();
	if (!success){goto end;};
		OnBnClickedButtonWreg0b();
	if (!success){goto end;};
		OnBnClickedButtonWreg0c();
	if (!success){goto end;};
		OnBnClickedButtonWreg0d();
	if (!success){goto end;};
		OnBnClickedButtonWreg0e();
	if (!success){goto end;};
		OnBnClickedButtonWreg0f();
	if (!success){goto end;};
		OnBnClickedButtonWreg10();
	if (!success){goto end;};
		OnBnClickedButtonWreg11();
	if (!success){goto end;};
	    OnBnClickedButtonWreg12();
	if (!success){goto end;};
		OnBnClickedButtonWreg13();
	if (!success){goto end;};
		OnBnClickedButtonWreg14();
	if (!success){goto end;};
		OnBnClickedButtonWreg15();
	if (!success){goto end;};
	OnBnClickedButtonWreg16();
	if (!success){goto end;};
	OnBnClickedButtonWreg17();
	if (!success){goto end;};
	    OnBnClickedButtonWreg18();
	if (!success){goto end;};
	OnBnClickedButtonWreg19();
	if (!success){goto end;};
	OnBnClickedButtonWreg1a();
	if (!success){goto end;};
		OnBnClickedButtonWreg1b();
	if (!success){goto end;};
		/*OnBnClickedButtonWreg1c();
	if (!success){goto end;};
	    OnBnClickedButtonWreg1d();
	if (!success){goto end;};
	    OnBnClickedButtonWreg1e();
	if (!success){goto end;};
	    OnBnClickedButtonWreg1f();
	if (!success){goto end;};
	    OnBnClickedButtonWreg20();
	if (!success){goto end;};*/
		OnBnClickedButtonWreg21();
	if (!success){goto end;};
	    /*OnBnClickedButtonWreg22();
	if (!success){goto end;};*/
	    OnBnClickedButtonWreg23();
	if (!success){goto end;};
	   /* OnBnClickedButtonWreg24();
	if (!success){goto end;};
	    OnBnClickedButtonWreg25();
	if (!success){goto end;};
	    OnBnClickedButtonWreg26();
	if (!success){goto end;};
	    OnBnClickedButtonWreg27();
	if (!success){goto end;};
	    OnBnClickedButtonWreg28();
	if (!success){goto end;};
	    OnBnClickedButtonWreg29();*/

end:;
}

void CdebugDlg::OnBnClickedButtonReadall()
{
		OnBnClickedButtonRreg01();
	if (!success){goto end;};
		/*OnBnClickedButtonRreg02();
	if (!success){goto end;};
		OnBnClickedButtonRreg03();
	if (!success){goto end;};
		OnBnClickedButtonRreg04();
	if (!success){goto end;};*/
		OnBnClickedButtonRreg05();
	if (!success){goto end;};
		OnBnClickedButtonRreg06();
	if (!success){goto end;};
		OnBnClickedButtonRreg07();
	if (!success){goto end;};
		OnBnClickedButtonRreg08();
	if (!success){goto end;};
		OnBnClickedButtonRreg09();
	if (!success){goto end;};
		OnBnClickedButtonRreg0a();
	if (!success){goto end;};
		OnBnClickedButtonRreg0b();
	if (!success){goto end;};
		OnBnClickedButtonRreg0c();
	if (!success){goto end;};
		OnBnClickedButtonRreg0d();
	if (!success){goto end;};
		OnBnClickedButtonRreg0e();
	if (!success){goto end;};
	 	OnBnClickedButtonRreg0f();
	if (!success){goto end;};
		OnBnClickedButtonRreg10();
	if (!success){goto end;};
	    OnBnClickedButtonRreg11();
	if (!success){goto end;};
		OnBnClickedButtonRreg12();
	if (!success){goto end;};
		OnBnClickedButtonRreg13();
	if (!success){goto end;};
		OnBnClickedButtonRreg14();
	if (!success){goto end;};
	 	OnBnClickedButtonRreg15();
	if (!success){goto end;};
		OnBnClickedButtonRreg16();
	if (!success){goto end;};
	    OnBnClickedButtonRreg17();
	if (!success){goto end;};
		OnBnClickedButtonRreg18();
	if (!success){goto end;};
		OnBnClickedButtonRreg19();
	if (!success){goto end;};
		OnBnClickedButtonRreg1a();
	if (!success){goto end;};
		OnBnClickedButtonRreg1b();
	if (!success){goto end;};
		/*OnBnClickedButtonRreg1c();
	if (!success){goto end;};
		OnBnClickedButtonRreg1d();
	if (!success){goto end;};
		OnBnClickedButtonRreg1e();
	if (!success){goto end;};
		OnBnClickedButtonRreg1f();
	if (!success){goto end;};
		OnBnClickedButtonRreg20();
	if (!success){goto end;};*/
	    OnBnClickedButtonRreg21();
	if (!success){goto end;};
		//readsparereg();
	//if (!success){goto end;};
	    OnBnClickedButtonRreg22();
	if (!success){goto end;};
	    OnBnClickedButtonRreg23();
    if (!success){goto end;};
	    /*OnBnClickedButtonRreg24();
	if (!success){goto end;};
	    OnBnClickedButtonRreg25();
	if (!success){goto end;};
	    OnBnClickedButtonRreg26();
	if (!success){goto end;};
	    OnBnClickedButtonRreg27();
    if (!success){goto end;};
	    OnBnClickedButtonRreg28();
	if (!success){goto end;};
	    OnBnClickedButtonRreg29();*/

end:;
}

void CdebugDlg::OnCbnDropdownComboLoad()
{
	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_LOAD, 0, DDL_READWRITE);
}



void CdebugDlg::OnBnClickedButtonLoad()
{
	FILE *fpi;
	char command[1000];
	int regval;
	int wordcnt=0;
	int i=0;
	CString str;
	CString errmsg;
	errno_t err;
	int RegEnd=0;
	CString FileStr;
	int length=0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	length = m_COMBO_LOAD.GetWindowTextLengthW();
	if (length == 0) 
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Specified.");
		goto end_error;
	}
	else 
		m_COMBO_LOAD.GetWindowText(FileStr);

	const TCHAR* fpi_name = (LPCTSTR)FileStr;

	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	};


	while (i != EOF)
	{
		regval = 0xffff;
		i = fscanf_s(fpi, "%s", command, 1000);
		if(i == EOF) 
			{
				if(RegEnd==1)
				{
					break;
				}
				else
				{
					goto unknown_format; 
				}
			}
		wordcnt++;

		if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_01.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				//str.Format(_T("%x"), regval);
				//m_EDIT_WREG_02.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				//str.Format(_T("%x"), regval);
				//m_EDIT_WREG_03.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
		/*		str.Format(_T("%x"), regval);
				m_EDIT_WREG_04.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
			/*	str.Format(_T("%x"), regval);
				m_EDIT_WREG_05.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				/*str.Format(_T("%x"), regval);
				m_EDIT_WREG_06.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_07.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_08.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_09.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_0a.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{		
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_0b.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_0c.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_0d.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_0e.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_0f.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_10.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_11.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_12.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_13.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_14.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_15.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg16h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_16.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg17h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_17.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_18.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg19h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_19.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_1A.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_WREG_1B.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				//str.Format(_T("%x"), regval);
				//m_EDIT_WREG_1C.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				//str.Format(_T("%x"), regval);
				//m_EDIT_WREG_1D.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				/*str.Format(_T("%x"), regval);
				m_EDIT_WREG_1E.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				/*str.Format(_T("%x"), regval);
				m_EDIT_WREG_1F.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				/*str.Format(_T("%x"), regval);
				m_EDIT_WREG_20.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg21h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_21.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg22h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
			/*	str.Format(_T("%x"), regval);
				m_EDIT_WREG_22.SetWindowText(str);*/
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg23h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xffff))
			{
				RegEnd=1;

				str.Format(_T("%x"), regval);
				m_EDIT_WREG_23.SetWindowText(str);

			}
			else
			{
				goto unknown_format;
			}
		}
		/*else if (_stricmp(command, "Reg24h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_24.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg25h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_25.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg26h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_26.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg27h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_27.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg28h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_28.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg29h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				RegEnd=1;
				str.Format(_T("%x"), regval);
				m_EDIT_WREG_29.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}*/
		//}
		/*else if (_stricmp(command, "*") == 0 )
		{
			RemoveAdTor();
			errmsg.Format(_T("Warning: The displayed setting excludes adaptive torque values.\nIf this setting is modified and saved, please set adaptive torque values again before OTP programming"));
			pParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
		}*/

		else
		{
			unknown_format:;
			errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			fclose(fpi);
			return;
		};
	};

	end:;
	fclose(fpi);
	end_error:;
}

void CdebugDlg::RemoveAdTor()
{
	CString sTemp,str;
	int nTemp;

	m_EDIT_WREG_01.GetWindowTextW(sTemp);
	nTemp = string2int(sTemp,m_EDIT_WREG_01.GetWindowTextLengthW());
	nTemp &= 0xf9;
	str.Format(_T("%x"), nTemp);
	m_EDIT_WREG_01.SetWindowText(str);

	m_EDIT_WREG_02.GetWindowText(sTemp);
	nTemp = string2int(sTemp,m_EDIT_WREG_02.GetWindowTextLengthW());
	nTemp &= 0x1f;
	nTemp |= 0x80;
	str.Format(_T("%x"), nTemp);
	m_EDIT_WREG_02.SetWindowText(str);

	m_EDIT_WREG_03.GetWindowText(sTemp);
	nTemp = string2int(sTemp,m_EDIT_WREG_03.GetWindowTextLengthW());
	nTemp &= 0xe0;
	str.Format(_T("%x"), nTemp);
	m_EDIT_WREG_03.SetWindowText(str);

	m_EDIT_WREG_13.GetWindowText(sTemp);
	nTemp = string2int(sTemp,m_EDIT_WREG_13.GetWindowTextLengthW());
	nTemp &= 0x81;
	str.Format(_T("%x"), nTemp);
	m_EDIT_WREG_13.SetWindowText(str);

	m_EDIT_WREG_15.GetWindowText(sTemp);
	nTemp = string2int(sTemp,m_EDIT_WREG_15.GetWindowTextLengthW());
	nTemp &= 0;
	str.Format(_T("%x"), nTemp);
	m_EDIT_WREG_15.SetWindowText(str);

	m_EDIT_WREG_18.GetWindowText(sTemp);//r18 default value is B0
	nTemp = string2int(sTemp,m_EDIT_WREG_18.GetWindowTextLengthW());
	nTemp &= 0;
	nTemp |= 0xb0;
	str.Format(_T("%x"), nTemp);
	m_EDIT_WREG_18.SetWindowText(str);
	
	m_WREG_1B.GetWindowText(sTemp);
	nTemp = string2int(sTemp,m_WREG_1B.GetWindowTextLengthW());
	nTemp &= 0;
	nTemp |= 0x90;
	str.Format(_T("%x"), nTemp);
	m_WREG_1B.SetWindowText(str);


}

void CdebugDlg::OnCbnDropdownComboSave()
{
	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_SAVE, 0, DDL_READWRITE);
}



void CdebugDlg::OnBnClickedButtonSave()
{
	FILE *fpo;
	FILE *fbo;
	errno_t err;

	char command[1000];
	int i=0;
	CString errmsg;
	int FileFound;
	CString stemp;
	CString DataStrTemp;

	int length=0;
	CString FileStr;
	const TCHAR* fpo_name2 = L"backupfile.txt";
	LPTSTR p;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	

	//get input
	length = m_COMBO_SAVE.GetWindowTextLengthW();
	if (length == 0) 
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Specified.");
		goto end_error;
	}
	else 
		m_COMBO_SAVE.GetWindowText(FileStr);
    
	if (FileStr == "backupfile.txt")
    {
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Filename is Default Backup File Name.\n Please choose another name.");
		goto end_error;
	};

	//backup file
	const TCHAR* fpo_name = (LPCTSTR)FileStr;
	
	_wfopen_s(&fbo, fpo_name2, _T("w"));
	    
	fclose(fbo);

	CopyFileW(fpo_name, fpo_name2, false); //back up current save file


	////check if the saved file will replace a *file(with ad_tor), if yes, pop up warning.
	////get text
	//m_COMBO_SAVE.GetWindowText(stemp);

	////m_COMBO_LOAD.SetWindowText(stemp);
	//TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	//::GetCurrentDirectory(MAX_PATH, szDrive);
	//DlgDirListComboBox(szDrive, IDC_COMBO_SAVE, 0, DDL_READWRITE);

	////set text
	//m_COMBO_SAVE.SetWindowText(stemp);


	//FileFound = m_COMBO_SAVE.FindStringExact(-1,fpo_name);

	//if (FileFound != CB_ERR )
	//{
	//	if (err = _wfopen_s(&fpo, fpo_name, _T("r"))!=0)
	//	{
	//		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
	//		return;
	//	};

	//	while (i != EOF)
	//	{
	//		i = fscanf_s(fpo, "%s", command, 1000);
	//		if(i == EOF) 
	//					break;

	//		else if (_stricmp(command, "*") == 0 )
	//		{
	//			errmsg.Format(_T("Warning: Adaptive torque values is not included in this saved file.\nPlease set adaptive torque again before OTP programming."));
	//			pParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
	//		}
	//	}

	//	fclose(fpo);
	//}



	//start writing file
    if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
		goto end_error;
	};

	p = m_EDIT_RREG_01.GetBuffer(20);
	fprintf( fpo, "Reg01h %S\n", p); 
	m_EDIT_RREG_01.ReleaseBuffer();

	/*p = m_EDIT_RREG_02.GetBuffer(1024);
	fprintf( fpo, "Reg02h %s%s\n", p, p+1); 
	m_EDIT_RREG_02.ReleaseBuffer();

	p = m_EDIT_RREG_03.GetBuffer(1024);
	fprintf( fpo, "Reg03h %s%s\n", p, p+1); 
	m_EDIT_RREG_03.ReleaseBuffer();

	p = m_EDIT_RREG_04.GetBuffer(1024);
	fprintf( fpo, "Reg04h %s%s\n", p, p+1); 
	m_EDIT_RREG_04.ReleaseBuffer();*/

	/*p = m_EDIT_RREG_05.GetBuffer(20);
	fprintf( fpo, "Reg05h %S\n", p); 
	m_EDIT_RREG_05.ReleaseBuffer();

	p = m_EDIT_RREG_06.GetBuffer(20);
	fprintf( fpo, "Reg06h %S\n", p); 
	m_EDIT_RREG_06.ReleaseBuffer();
*/
	p = m_EDIT_RREG_07.GetBuffer(1024);
	fprintf( fpo, "Reg07h %S\n", p); 
	m_EDIT_RREG_07.ReleaseBuffer();

	p = m_EDIT_RREG_08.GetBuffer(1024);
	fprintf( fpo, "Reg08h %S\n", p); 
	m_EDIT_RREG_08.ReleaseBuffer();

	p = m_EDIT_RREG_09.GetBuffer(1024);
	fprintf( fpo, "Reg09h %S\n", p); 
	m_EDIT_RREG_09.ReleaseBuffer();

	p = m_EDIT_RREG_0a.GetBuffer(1024);
	fprintf( fpo, "Reg0Ah %S\n", p); 
	m_EDIT_RREG_0a.ReleaseBuffer();

	p = m_EDIT_RREG_0b.GetBuffer(1024);
	fprintf( fpo, "Reg0Bh %S\n", p); 
	m_EDIT_RREG_0b.ReleaseBuffer();

	p = m_EDIT_RREG_0c.GetBuffer(1024);
	fprintf( fpo, "Reg0Ch %S\n", p); 
	m_EDIT_RREG_0c.ReleaseBuffer(); 

	p = m_EDIT_RREG_0d.GetBuffer(1024);
	fprintf( fpo, "Reg0Dh %S\n", p); 
	m_EDIT_RREG_0d.ReleaseBuffer();

	p = m_EDIT_RREG_0e.GetBuffer(1024);
	fprintf( fpo, "Reg0Eh %S\n", p); 
	m_EDIT_RREG_0e.ReleaseBuffer();

	p = m_EDIT_RREG_0f.GetBuffer(1024);
	fprintf( fpo, "Reg0Fh %S\n", p); 
	m_EDIT_RREG_0f.ReleaseBuffer();

	p = m_EDIT_RREG_10.GetBuffer(1024);
	fprintf( fpo, "Reg10h %S\n", p); 
	m_EDIT_RREG_10.ReleaseBuffer();

	p = m_EDIT_RREG_11.GetBuffer(1024);
	fprintf( fpo, "Reg11h %S\n", p); 
	m_EDIT_RREG_11.ReleaseBuffer();

	p = m_EDIT_RREG_12.GetBuffer(1024);
	fprintf( fpo, "Reg12h %S\n", p); 
	m_EDIT_RREG_12.ReleaseBuffer();

	p = m_EDIT_RREG_13.GetBuffer(1024);
	fprintf( fpo, "Reg13h %S\n", p); 
	m_EDIT_RREG_13.ReleaseBuffer();

	p = m_EDIT_RREG_14.GetBuffer(1024);
	fprintf( fpo, "Reg14h %S\n", p); 
	m_EDIT_RREG_14.ReleaseBuffer();

	p = m_EDIT_RREG_15.GetBuffer(1024);
	fprintf( fpo, "Reg15h %S\n", p); 
	m_EDIT_RREG_15.ReleaseBuffer();

	p = m_EDIT_RREG_16.GetBuffer(1024);
	fprintf( fpo, "Reg16h %s%s\n", p, p+1); 
	m_EDIT_RREG_16.ReleaseBuffer();

	p = m_EDIT_RREG_17.GetBuffer(1024);
	fprintf( fpo, "Reg17h %S\n", p); 
	m_EDIT_RREG_17.ReleaseBuffer();

	p = m_EDIT_RREG_18.GetBuffer(1024);
	fprintf( fpo, "Reg18h %S\n", p); 
	m_EDIT_RREG_18.ReleaseBuffer();

	p = m_EDIT_RREG_19.GetBuffer(1024);
	fprintf( fpo, "Reg19h %S\n", p); 
	m_EDIT_RREG_19.ReleaseBuffer();

	p = m_EDIT_RREG_1a.GetBuffer(1024);
	fprintf( fpo, "Reg1Ah %S\n", p); 
	m_EDIT_RREG_1a.ReleaseBuffer();

	p = m_EDIT_RREG_1b.GetBuffer(1024);
	fprintf( fpo, "Reg1Bh %S\n", p); 
	m_EDIT_RREG_1b.ReleaseBuffer();

	/*p = m_EDIT_RREG_1c.GetBuffer(1024);
	fprintf( fpo, "Reg1Ch %s%s\n", p, p+1); 
	m_EDIT_RREG_1c.ReleaseBuffer();

	p = m_EDIT_RREG_1d.GetBuffer(1024);
	fprintf( fpo, "Reg1Dh %s%s\n", p, p+1); 
	m_EDIT_RREG_1d.ReleaseBuffer();

	p = m_EDIT_RREG_1e.GetBuffer(1024);
	fprintf( fpo, "Reg1Eh %s%s\n", p, p+1); 
	m_EDIT_RREG_1e.ReleaseBuffer();

	p = m_EDIT_RREG_1f.GetBuffer(1024);
	fprintf( fpo, "Reg1Fh %s%s\n", p, p+1); 
	m_EDIT_RREG_1f.ReleaseBuffer();

	p = m_EDIT_RREG_20.GetBuffer(1024);
	fprintf( fpo, "Reg20h %s%s\n", p, p+1); 
	m_EDIT_RREG_20.ReleaseBuffer();*/

	p = m_EDIT_RREG_21.GetBuffer(1024);
	fprintf( fpo, "Reg21h %S\n", p); 
	m_EDIT_RREG_21.ReleaseBuffer();

	/*p = m_EDIT_RREG_22.GetBuffer(1024);
	fprintf( fpo, "Reg22h %S\n", p); 
	m_EDIT_RREG_22.ReleaseBuffer();*/

	p = m_EDIT_RREG_23.GetBuffer(1024);
	fprintf( fpo, "Reg23h %S\n", p); 
	m_EDIT_RREG_23.ReleaseBuffer();

	/*p = m_EDIT_RREG_24.GetBuffer(1024);
	fprintf( fpo, "Reg24h %s%s\n", p, p+1); 
	m_EDIT_RREG_24.ReleaseBuffer();

	p = m_EDIT_RREG_25.GetBuffer(1024);
	fprintf( fpo, "Reg25h %s%s\n", p, p+1); 
	m_EDIT_RREG_25.ReleaseBuffer();

	p = m_EDIT_RREG_26.GetBuffer(1024);
	fprintf( fpo, "Reg26h %s%s\n", p, p+1); 
	m_EDIT_RREG_26.ReleaseBuffer();

	p = m_EDIT_RREG_27.GetBuffer(1024);
	fprintf( fpo, "Reg27h %s%s\n", p, p+1); 
	m_EDIT_RREG_27.ReleaseBuffer();

	p = m_EDIT_RREG_28.GetBuffer(1024);
	fprintf( fpo, "Reg28h %s%s\n", p, p+1); 
	m_EDIT_RREG_28.ReleaseBuffer();

	p = m_EDIT_RREG_29.GetBuffer(1024);
	fprintf( fpo, "Reg29h %s%s\n", p, p+1); 
	m_EDIT_RREG_29.ReleaseBuffer();*/

	fclose(fpo);
	end_error:;
}

void CdebugDlg::OnBnClickedButtonWreg2a()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw,temp_string;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_2A.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_2A.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x2a,dat);
	// read reg
	if (success){
		// read reg
		datr = pParent->rreg(0x2a);
    
		// display data
		temp_string.Format(_T("%x"),datr);
	    m_EDIT_WREG_2A.SetWindowText(temp_string);
	};
end:;
}

void CdebugDlg::OnBnClickedButtonWreg3d()
{
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw,temp_string;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_3D.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_3D.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x3d,dat);
	// read reg
	if (success){
		// read reg
		datr = pParent->rreg(0x3d);
    
		// display data
		temp_string.Format(_T("%x"),datr);
	    m_EDIT_WREG_3D.SetWindowText(temp_string);
	};
end:;
}

void CdebugDlg::readsparereg()
{
    int datr = 0;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	    datr = pParent->rreg(0x2a);
    
		// display data
		temp_string.Format(_T("%x"),datr);
	    m_EDIT_WREG_2A.SetWindowText(temp_string);

		datr = pParent->rreg(0x3d);
    
		// display data
		temp_string.Format(_T("%x"),datr);
	    m_EDIT_WREG_3D.SetWindowText(temp_string);

}



void CdebugDlg::OnCbnSetfocusComboLoad()
{
	//CString stemp;
	//int length;
	////get text
	//m_COMBO_LOAD.GetWindowText(stemp);
	//
	////show drop down list
	//if (!m_COMBO_LOAD.GetDroppedState())
	//	m_COMBO_LOAD.ShowDropDown(TRUE);
	//

	////set text
	//m_COMBO_LOAD.SetWindowText(stemp);

	////set cur position
	//length = stemp.GetLength();
	//m_COMBO_LOAD.SetEditSel(length,length);

}


void CdebugDlg::OnCbnSetfocusComboSave()
{
	//CString stemp;
	//int length;

	////get text
	//m_COMBO_SAVE.GetWindowText(stemp);
	//
	////show drop down list
	//if (!m_COMBO_SAVE.GetDroppedState())
	//	m_COMBO_SAVE.ShowDropDown(TRUE);

	////set text
	//m_COMBO_SAVE.SetWindowText(stemp);

	////set cur position
	//length = stemp.GetLength();
	//m_COMBO_SAVE.SetEditSel(length,length);
}


void CdebugDlg::OnCbnEditchangeComboLoad()
{
	// TODO: Add your control notification handler code here
	CString stemp, found_item[500];
	int length;
	int start_i;
	int found_i,found_i_next;
	int item_count;
	int i,j;

	//get text
	m_COMBO_LOAD.GetWindowText(stemp);
	start_i=-1;
	found_i = m_COMBO_LOAD.FindString(start_i,stemp);

	//no item found
	if (found_i == CB_ERR)
	{
		TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
		::GetCurrentDirectory(MAX_PATH, szDrive);
		DlgDirListComboBox(szDrive, IDC_COMBO_LOAD, 0, DDL_READWRITE);

		//set back text
		m_COMBO_LOAD.SetWindowText(stemp);

		//set cur position
		length = stemp.GetLength();
		m_COMBO_LOAD.SetEditSel(length,length);

		return;
	}

	//found item
	else
	{
		TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
		::GetCurrentDirectory(MAX_PATH, szDrive);
		DlgDirListComboBox(szDrive, IDC_COMBO_LOAD, 0, DDL_READWRITE);

		//research 1st item,since drop down list is updated.
		start_i=-1;
		found_i = m_COMBO_LOAD.FindString(start_i,stemp);

		item_count = m_COMBO_LOAD.GetCount();
		i=0;
		while (found_i != CB_ERR )
		{

			m_COMBO_LOAD.GetLBText(found_i,found_item[i++]);
		
			start_i=found_i;
			if (start_i <= item_count)
			{
				found_i_next = m_COMBO_LOAD.FindString(start_i,stemp);
				if (found_i_next>found_i)//ensure do not search from beginning again
					found_i = found_i_next;
				else
					break;
			}
			else
				break;

		}

		m_COMBO_LOAD.ResetContent();
		for (j=0 ; j< i ; j++)
		{
			m_COMBO_LOAD.AddString(found_item[j]);
		}

		//set back text
		m_COMBO_LOAD.SetWindowText(stemp);

		//set cur position
		length = stemp.GetLength();
		m_COMBO_LOAD.SetEditSel(length,length);
	}
}

void CdebugDlg::OnCbnEditchangeComboSave()
{
	CString stemp, found_item[500];
	int length;
	int start_i;
	int found_i,found_i_next;
	int item_count;
	int i,j;

	//get text
	m_COMBO_SAVE.GetWindowText(stemp);
	start_i=-1;
	found_i = m_COMBO_SAVE.FindString(start_i,stemp);

	//no item found
	if (found_i == CB_ERR)
	{
		TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
		::GetCurrentDirectory(MAX_PATH, szDrive);
		DlgDirListComboBox(szDrive, IDC_COMBO_SAVE, 0, DDL_READWRITE);

		//set back text
		m_COMBO_SAVE.SetWindowText(stemp);

		//set cur position
		length = stemp.GetLength();
		m_COMBO_SAVE.SetEditSel(length,length);

		return;
	}

	//found item
	else
	{
		TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
		::GetCurrentDirectory(MAX_PATH, szDrive);
		DlgDirListComboBox(szDrive, IDC_COMBO_SAVE, 0, DDL_READWRITE);

		//research 1st item,since drop down list is updated.
		start_i=-1;
		found_i = m_COMBO_SAVE.FindString(start_i,stemp);

		item_count = m_COMBO_SAVE.GetCount();
		i=0;
		while (found_i != CB_ERR )
		{

			m_COMBO_SAVE.GetLBText(found_i,found_item[i++]);
		
			start_i=found_i;
			if (start_i <= item_count)
			{
				found_i_next = m_COMBO_SAVE.FindString(start_i,stemp);
				if (found_i_next>found_i)//ensure do not search from beginning again
					found_i = found_i_next;
				else
					break;
			}
			else
				break;

		}

		m_COMBO_SAVE.ResetContent();
		for (j=0 ; j< i ; j++)
		{
			m_COMBO_SAVE.AddString(found_item[j]);
		}

		//set back text
		m_COMBO_SAVE.SetWindowText(stemp);

		//set cur position
		length = stemp.GetLength();
		m_COMBO_SAVE.SetEditSel(length,length);
	}
}

void CdebugDlg::OnCbnSelchangeComboLoad()
{
	// TODO: Add your control notification handler code here
}


void CdebugDlg::OnCbnEditupdateComboLoad()
{
	// TODO: Add your control notification handler code here
}

void CdebugDlg::SetDropDownHeight(CComboBox* m_combo, int m_line)
{
 // //Get rectangles
 // CRect rctComboBox, rctDropDown;
 // //Combo rect
 // pMyComboBox->GetClientRect(&rctComboBox); 
 // //DropDownList rect
 // pMyComboBox->GetDroppedControlRect(&rctDropDown); 

 // //Get Item height
 // int itemHeight = pMyComboBox->GetItemHeight(-1); 
 // //Converts coordinates
 // pMyComboBox->GetParent()->ScreenToClient(&rctDropDown); 
 // //Set height
 //// rctDropDown.bottom = rctDropDown.top + rctComboBox.Height() + itemHeight*itemsToShow; 
 // rctDropDown.bottom = rctDropDown.top + itemHeight*itemsToShow; 
 // //apply changes
 // pMyComboBox->MoveWindow(&rctDropDown); 

       CRect cbsize; // current size of the combo box
           
            int Height; // new height
           
            m_combo->GetClientRect(&cbsize);
 
            // Compute the new height.
            Height = m_combo->GetItemHeight(-1);
 
            Height += m_combo->GetItemHeight(0)*m_line;
           
            Height += GetSystemMetrics(SM_CYEDGE)*4; // top and botton edges for editbox and dropdown box
 
            m_combo->SetWindowPos(NULL,0,0,cbsize.right,Height,SWP_NOMOVE | SWP_NOZORDER);
}

void CdebugDlg::OnBnClickedButtonWreg16()
{
	// TODO: Add your control notification handler code here
		int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_16.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_16.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x16,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg16();
	};
end:;
}


void CdebugDlg::OnBnClickedButtonWreg17()
{
	// TODO: Add your control notification handler code here
		int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_17.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_17.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x17,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg17();
	};
end:;
}


void CdebugDlg::OnBnClickedButtonWreg19()
{
	// TODO: Add your control notification handler code here
		int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_19.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_19.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x19,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg19();
	};
end:;
}


void CdebugDlg::OnBnClickedButtonWreg1a()
{
	// TODO: Add your control notification handler code here
		int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_1A.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_1A.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x1a,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg1a();
	};
end:;
}


void CdebugDlg::OnBnClickedButtonWreg21()
{
	// TODO: Add your control notification handler code here
		int dat = 0;
	int datr = 0;
	int length_dat;
	CString datw;
 CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read user inputs
	m_EDIT_WREG_21.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_WREG_21.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	dat = string2int(datw, length_dat);
	// write reg
	pParent->wreg(0x21,dat);
	// read reg
	if (success){
		OnBnClickedButtonRreg21();
	};
end:;
}
