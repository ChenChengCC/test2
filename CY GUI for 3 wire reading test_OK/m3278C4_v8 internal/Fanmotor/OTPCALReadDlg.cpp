// OTPCALReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "OTPCALReadDlg.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"

// COTPCALReadDlg dialog

IMPLEMENT_DYNAMIC(COTPCALReadDlg, CDialog)

COTPCALReadDlg::COTPCALReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COTPCALReadDlg::IDD, pParent)
	, m_EDIT_OSCTCTEST(_T(""))
	, m_EDIT_OSCOFFTEST(_T(""))
	, m_EDIT_PINSELTEST(_T(""))
	, m_EDIT_PWM_LOWTEST(_T(""))
	, m_EDIT_PWM_FLOATTEST(_T(""))
	, m_EDIT_PWMFREQTEST(_T(""))
	, m_EDIT_CHROMSELTEST(_T(""))
	, m_EDIT_RETRY_TIMETEST(_T(""))
{
	m_pParent=pParent;
}

COTPCALReadDlg::~COTPCALReadDlg()
{
}

void COTPCALReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OSCTCTEST, m_EDIT_OSCTCTEST);
	DDX_Text(pDX, IDC_EDIT_OSCOFFTEST, m_EDIT_OSCOFFTEST);
	DDX_Text(pDX, IDC_EDIT_PINSELTEST, m_EDIT_PINSELTEST);
	DDX_Text(pDX, IDC_EDIT_PWM_LOWTEST, m_EDIT_PWM_LOWTEST);
	DDX_Text(pDX, IDC_EDIT_PWM_FLOATTEST, m_EDIT_PWM_FLOATTEST);
	DDX_Text(pDX, IDC_EDIT_PWMFREQTEST, m_EDIT_PWMFREQTEST);
	DDX_Text(pDX, IDC_EDIT_CHROMSELTEST, m_EDIT_CHROMSELTEST);
	DDX_Text(pDX, IDC_EDIT_RETRY_TIMETEST, m_EDIT_RETRY_TIMETEST);
	DDX_Control(pDX, IDC_CHECK_SWAPBC, m_CHECK_SWAPBC);
	DDX_Control(pDX, IDC_CHECK_DLLOTP, m_CHECK_DLLOTP);
	DDX_Control(pDX, IDC_CHECK_FFOTP, m_CHECK_FFOTP);
	DDX_Control(pDX, IDC_CHECK_PMCOTP, m_CHECK_PMCOTP);
	DDX_Control(pDX, IDC_CHECK_SKIP_S2, m_CHECK_SKIP_S2);
	DDX_Control(pDX, IDC_CHECK_VARDACOTP, m_CHECK_VARDACOTP);
	DDX_Control(pDX, IDC_CHECK_RETRY_ILIM_BRKOTP, m_CHECK_RETRY_ILIM_BRKOTP);
	DDX_Control(pDX, IDC_CHECK_RETRY_TRISTATEOTP, m_CHECK_RETRY_TRISTATEOTP);
	DDX_Control(pDX, IDC_CHECK_PWMFLOATDIS, m_CHECK_PWMFLOATDIS);
	DDX_Control(pDX, IDC_CHECK_HP_ALARM_DIS, m_CHECK_HP_ALARM_DIS);
	DDX_Control(pDX, IDC_CHECK_TRIPHASEOTP, m_CHECK_TRIPHASEOTP);
	DDX_Control(pDX, IDC_CHECK_OTP_CRC_CHK_DIS, m_CHECK_OTP_CRC_CHK_DIS);
	DDX_Control(pDX, IDC_CHECK_PWMOVROTP, m_CHECK_PWMOVROTP);
	DDX_Control(pDX, IDC_CHECK_OFFBRKOTP, m_CHECK_OFFBRKOTP);
	DDX_Control(pDX, IDC_CHECK_OTPCALDONE_Test, m_CHECK_OTPCALDONE_Test);
}


BEGIN_MESSAGE_MAP(COTPCALReadDlg, CDialog)
	ON_WM_CLOSE()
//	ON_WM_DESTROY()
ON_WM_NCDESTROY()
ON_BN_CLICKED(IDC_BUTTON_ReadOTPCAL, &COTPCALReadDlg::OnBnClickedButtonReadotpcal)
END_MESSAGE_MAP()


// COTPCALReadDlg message handlers


void COTPCALReadDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


//void COTPCALReadDlg::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//	// TODO: Add your message handler code here
//}


void COTPCALReadDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


void COTPCALReadDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}


BOOL COTPCALReadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	int regval_temp,mask,OTPCAL_done;
	//check otpcal_done
	regval_temp = pParentParent->rreg(0x1a);
	mask=1;
	OTPCAL_done=(regval_temp>>4)&mask;

	if(OTPCAL_done==0)
	{
		m_CHECK_OTPCALDONE_Test.SetCheck(0);
	}

	else
	{
		m_CHECK_OTPCALDONE_Test.SetCheck(1);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void COTPCALReadDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}


void COTPCALReadDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	((CIntTest*)m_pParent)->otpcalreaddlg = NULL;
    delete this;
}


void COTPCALReadDlg::OnBnClickedButtonReadotpcal()
{
	// TODO: Add your control notification handler code here
	int regval;
	int mask;
	CString datbits;
	int osc_offset,osc_tc,profile_sel,pwm_low,pwm_float, pwm_freq, fast_vardac, retry_time, pwm_float_dis,hp_alarm_dis,triphase_det_en, otp_crc_chk_dis, pwm_nonoverlap_dis,fan_en_off_brk,retry_tristate, swap_BC, dll_en, ff_en, pmc_en,
		skip_s2, vardac_en, retry_ilim_brk;
	int OTPCAL_done;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	regval = pParentParent->rreg(0x1a);
    if (!success) return;
	mask=1;
	OTPCAL_done=(regval>>4)&mask;

	if(OTPCAL_done==0)
	{
		m_CHECK_OTPCALDONE_Test.SetCheck(0);
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTPCAL have not been burnt!");
		return;
	}

	else
	{
		m_CHECK_OTPCALDONE_Test.SetCheck(1);

		regval = pParentParent->rreg(0x1b);
		if (!success){return;};
		mask=31;
		osc_offset=regval&mask;
		mask=7;
		osc_tc=(regval>>5)&mask; 

		int otp_cal_reg=pParentParent->dataread_anybits(0x01,7,1); //save otp_cal_sel
		CString otpcal_temp=pParentParent->int2bin_anybits(otp_cal_reg,1);

		datbits = "1";//set otp_cal_sel=1
		pParentParent->dataupdate_anybits(0x01,7,datbits,1);

		regval = pParentParent->rreg(0x04);
		if (!success){return;};
		mask=1;
		dll_en=(regval>>3)&mask;
		ff_en=(regval>>2)&mask;

		regval = pParentParent->rreg(0x08);
		if (!success){return;};
		mask=1;
		triphase_det_en=(regval>>7)&mask;
		pmc_en=(regval>>6)&mask;

		regval = pParentParent->rreg(0x10);
		if (!success){return;};
		mask=1;
		vardac_en=(regval>>6)&mask;

		regval = pParentParent->rreg(0x0b);
		if (!success){return;};
		mask=1;
		pwm_nonoverlap_dis=(regval>>7)&mask;

		regval = pParentParent->rreg(0x11);
		if (!success){return;};
		mask=1;
		pwm_freq=(regval>>6)&mask;

		regval = pParentParent->rreg(0x18);
		if (!success){return;};
		mask=1;
		pwm_float_dis=(regval>>7)&mask;
		swap_BC=(regval>>6)&mask;
		hp_alarm_dis = (regval>>3)&mask;
		retry_tristate=(regval>>2)&mask;
		retry_ilim_brk=(regval>>1)&mask;
		retry_time=regval&mask;
		mask=3;
		profile_sel=(regval>>4)&mask;

		int pos_sns=pParentParent->dataread_anybits(0x01,3,1); //save pos_sns
		CString pos_sns_temp=pParentParent->int2bin_anybits(pos_sns,1);

		datbits = "1";//set pos_sns=1
		pParentParent->dataupdate_anybits(0x01,3,datbits,1);

		regval = pParentParent->rreg(0x15);
		if (!success){return;};
		mask=1;
		fan_en_off_brk=(regval>>7)&mask;
		fast_vardac=(regval>>6)&mask;
		otp_crc_chk_dis=(regval>>5)&mask;
		skip_s2=(regval>>4)&mask;
		mask=3;
		pwm_low=(regval>>2)&mask;
		pwm_float=regval&mask;

		//******************update display value**********************
		//OSC_TC display
		if (osc_tc == 0)
			m_EDIT_OSCTCTEST.Format(_T("0h: 11.89kHz/deg"));
		else if (osc_tc == 1)
			m_EDIT_OSCTCTEST.Format(_T("1h: 8.74kHz/deg"));
		else if (osc_tc == 2)
			m_EDIT_OSCTCTEST.Format(_T("2h: 6.42kHz/deg"));
		else if (osc_tc == 3)
			m_EDIT_OSCTCTEST.Format(_T("3h: 2.89kHz/deg"));
		else if (osc_tc == 4)
			m_EDIT_OSCTCTEST.Format(_T("4h: 0.64kHz/deg"));
		else if (osc_tc == 5)
			m_EDIT_OSCTCTEST.Format(_T("5h: -3.68kHz/deg"));
		else if (osc_tc == 6)
			m_EDIT_OSCTCTEST.Format(_T("6h: -9.49kHz/deg"));
		else if (osc_tc == 7)
			m_EDIT_OSCTCTEST.Format(_T("7h: -13.63kHz/deg"));
		//OSC_OFFSET display
		if (osc_offset == 0)
			m_EDIT_OSCOFFTEST.Format(_T("0h: 19.8MHz"));
		else if (osc_offset == 1)
			m_EDIT_OSCOFFTEST.Format(_T("1h: 20.1MHz"));
		else if (osc_offset == 2)
			m_EDIT_OSCOFFTEST.Format(_T("2h: 20.2MHz"));
		else if (osc_offset == 3)
			m_EDIT_OSCOFFTEST.Format(_T("3h: 20.6MHz"));
		else if (osc_offset == 4)
			m_EDIT_OSCOFFTEST.Format(_T("4h: 21.0MHz"));
		else if (osc_offset == 5)
			m_EDIT_OSCOFFTEST.Format(_T("5h: 21.3MHz"));
		else if (osc_offset == 6)
			m_EDIT_OSCOFFTEST.Format(_T("6h: 21.8MHz"));
		else if (osc_offset == 7)
			m_EDIT_OSCOFFTEST.Format(_T("7h: 22.2MHz"));
		else if (osc_offset == 8)
			m_EDIT_OSCOFFTEST.Format(_T("8h: 22.4MHz"));
		else if (osc_offset == 9)
			m_EDIT_OSCOFFTEST.Format(_T("9h: 22.7MHz"));
		else if (osc_offset == 10)
			m_EDIT_OSCOFFTEST.Format(_T("Ah: 23.1MHz"));
		else if (osc_offset == 11)
			m_EDIT_OSCOFFTEST.Format(_T("Bh: 23.5MHz"));
		else if (osc_offset == 12)
			m_EDIT_OSCOFFTEST.Format(_T("Ch: 23.9MHz"));
		else if (osc_offset == 13)
			m_EDIT_OSCOFFTEST.Format(_T("Dh: 24.1MHz"));
		else if (osc_offset == 14)
			m_EDIT_OSCOFFTEST.Format(_T("Eh: 24.4MHz"));
		else if (osc_offset == 15)
			m_EDIT_OSCOFFTEST.Format(_T("Fh: 25.0MHz"));
		else if (osc_offset == 16)
			m_EDIT_OSCOFFTEST.Format(_T("10h: 25.1MHz"));
		else if (osc_offset == 17)
			m_EDIT_OSCOFFTEST.Format(_T("11h: 25.7MHz"));
		else if (osc_offset == 18)
			m_EDIT_OSCOFFTEST.Format(_T("12h: 25.8MHz"));
		else if (osc_offset == 19)
			m_EDIT_OSCOFFTEST.Format(_T("13h: 26.2MHz"));
		else if (osc_offset == 20)
			m_EDIT_OSCOFFTEST.Format(_T("14h: 26.5MHz"));
		else if (osc_offset == 21)
			m_EDIT_OSCOFFTEST.Format(_T("15h: 26.8MHz"));
		else if (osc_offset == 22)
			m_EDIT_OSCOFFTEST.Format(_T("16h: 27.2MHz"));
		else if (osc_offset == 23)
			m_EDIT_OSCOFFTEST.Format(_T("17h: 27.8MHz"));
		else if (osc_offset == 24)
			m_EDIT_OSCOFFTEST.Format(_T("18h: 27.8MHz"));
		else if (osc_offset == 25)
			m_EDIT_OSCOFFTEST.Format(_T("19h: 28.2MHz"));
		else if (osc_offset == 26)
			m_EDIT_OSCOFFTEST.Format(_T("1Ah: 28.3MHz"));
		else if (osc_offset == 27)
			m_EDIT_OSCOFFTEST.Format(_T("1Bh: 29.0MHz"));
		else if (osc_offset == 28)
			m_EDIT_OSCOFFTEST.Format(_T("1Ch: 29.5MHz"));
		else if (osc_offset == 29)
			m_EDIT_OSCOFFTEST.Format(_T("1Dh: 29.6MHz"));
		else if (osc_offset == 30)
			m_EDIT_OSCOFFTEST.Format(_T("1Eh: 30.0MHz"));
		else if (osc_offset == 31)
			m_EDIT_OSCOFFTEST.Format(_T("1Fh: 30.1MHz"));
		//profile_sel display
		if (profile_sel == 0)
			m_EDIT_PINSELTEST.Format(_T("0h: SINGLE"));
		else if (profile_sel == 1)
			m_EDIT_PINSELTEST.Format(_T("1h: TRIPLE"));
		else if (profile_sel == 2)
			m_EDIT_PINSELTEST.Format(_T("2h: DUAL"));
		else if (profile_sel == 3)
			m_EDIT_PINSELTEST.Format(_T("3h: TRIPLE"));
		//pwm_low display
		if (pwm_low == 0)
			m_EDIT_PWM_LOWTEST.Format(_T("0h: 0x00"));
		else if (pwm_low == 1)
			m_EDIT_PWM_LOWTEST.Format(_T("1h: stop"));
		else if (pwm_low == 2)
			m_EDIT_PWM_LOWTEST.Format(_T("2h: previous value"));
		else if (pwm_low == 3)
			m_EDIT_PWM_LOWTEST.Format(_T("3h: 0xFF"));
		//pwm_float display
		if (pwm_float == 0)
			m_EDIT_PWM_FLOATTEST.Format(_T("0h: 0x00"));
		else if (pwm_float == 1)
			m_EDIT_PWM_FLOATTEST.Format(_T("1h: stop"));
		else if (pwm_float == 2)
			m_EDIT_PWM_FLOATTEST.Format(_T("2h: previous value"));
		else if (pwm_float == 3)
			m_EDIT_PWM_FLOATTEST.Format(_T("3h: 0xFF"));
		// pwm_freq display
		if (pwm_freq == 0)
			m_EDIT_PWMFREQTEST.Format(_T("0h: 97.7kHz"));
		else if (pwm_freq == 1)
			m_EDIT_PWMFREQTEST.Format(_T("1h: 48.8kHz"));
		// fast_vardac display
		if (fast_vardac == 0)
			m_EDIT_CHROMSELTEST.Format(_T("0h: 2 Steps"));
		else if (fast_vardac == 1)
			m_EDIT_CHROMSELTEST.Format(_T("1h: 1 Step"));
		// retry_time display
		if (retry_time == 0)
			m_EDIT_RETRY_TIMETEST.Format(_T("0h: 5s"));
		else if (retry_time == 1)
			m_EDIT_RETRY_TIMETEST.Format(_T("1h: 10s"));

		m_CHECK_PWMFLOATDIS.SetCheck(pwm_float_dis);
		m_CHECK_HP_ALARM_DIS.SetCheck(hp_alarm_dis);
		m_CHECK_TRIPHASEOTP.SetCheck(triphase_det_en);
		m_CHECK_OTP_CRC_CHK_DIS.SetCheck(otp_crc_chk_dis);
		m_CHECK_PWMOVROTP.SetCheck(pwm_nonoverlap_dis);
		m_CHECK_OFFBRKOTP.SetCheck(fan_en_off_brk);
		m_CHECK_SWAPBC.SetCheck(swap_BC);
		m_CHECK_DLLOTP.SetCheck(dll_en);
		m_CHECK_FFOTP.SetCheck(ff_en);
		m_CHECK_PMCOTP.SetCheck(pmc_en);
		m_CHECK_SKIP_S2.SetCheck(skip_s2);
		m_CHECK_VARDACOTP.SetCheck(vardac_en);
		m_CHECK_RETRY_ILIM_BRKOTP.SetCheck(retry_ilim_brk);
		m_CHECK_RETRY_TRISTATEOTP.SetCheck(retry_tristate);

		UpdateData(FALSE);

		pParentParent->dataupdate_anybits(0x01,3,pos_sns_temp,1);//original pos_sns      
		pParentParent->dataupdate_anybits(0x01,7,otpcal_temp,1); //original otp_cal_sel

	}
}
