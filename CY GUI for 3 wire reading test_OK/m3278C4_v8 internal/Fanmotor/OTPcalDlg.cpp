// OTPcalDlg.cpp : implementation file
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

int TIMEOUT_otpcal = 100; // 1s
int nLowercal = 0;
int nUppercal = 100;
int nStepcal = 10;
int edit=0;
// COTPDlg dialog
CdebugDlg use_debugdlg_otpcal;
CdetailDlg use_detaildlg_otpcal;
//CFanmotorDlg use_fanmotordlg_otpcal;

// COTPcalDlg dialog

IMPLEMENT_DYNAMIC(COTPcalDlg, CDialog)

COTPcalDlg::COTPcalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COTPcalDlg::IDD, pParent)
{
      m_pParent=pParent;
}

COTPcalDlg::~COTPcalDlg()
{
}

void COTPcalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS2, m_PROGRESS2);
	DDX_Control(pDX, IDC_CHECK_PASSCAL, m_CHECK_PASSCAL);
	DDX_Control(pDX, IDC_CHECK_FAILCAL, m_CHECK_FAILCAL);
	DDX_Control(pDX, IDC_CHECK_OTPCAL_DONE, m_CHECK_OTPCAL_DONE);
	DDX_Control(pDX, IDC_CHECK_DLLOTP, m_CHECK_DLLOTP);
	DDX_Control(pDX, IDC_CHECK_FFOTP, m_CHECK_FFOTP);
	DDX_Control(pDX, IDC_CHECK_PMCOTP, m_CHECK_PMCOTP);
	DDX_Control(pDX, IDC_CHECK_TRIPHASEOTP, m_CHECK_TRIPHASEOTP);
	DDX_Control(pDX, IDC_CHECK_PWMOVROTP, m_CHECK_PWMOVROTP);
	DDX_Control(pDX, IDC_CHECK_VARDACOTP, m_CHECK_VARDACOTP);
	DDX_Control(pDX, IDC_COMBO_OSCTCOTP, m_COMBO_OSCTCOTP);
	DDX_Control(pDX, IDC_COMBO_OSCOFFOTP, m_COMBO_OSCOFFOTP);
	DDX_Control(pDX, IDC_COMBO_PINSEL, m_COMBO_PINSEL);
	DDX_Control(pDX, IDC_COMBO_CHROMSEL, m_COMBO_CHROMSEL);
	DDX_Control(pDX, IDC_CHECK_OFFBRKOTP, m_CHECK_OFFBRKOTP);
	DDX_Control(pDX, IDC_CHECK_SKIP_S2, m_CHECK_SKIP_S2);
	DDX_Control(pDX, IDC_COMBO_PWM_LOW, m_COMBO_PWM_LOW);
	DDX_Control(pDX, IDC_COMBO_PWM_FLOAT, m_COMBO_PWM_FLOAT);
	DDX_Control(pDX, IDC_CHECK_PWMFLOATDIS, m_CHECK_PWMFLOATDIS);
	DDX_Control(pDX, IDC_CHECK_OTP_CRC_CHK_DIS, m_CHECK_OTP_CRC_CHK_DIS);
	DDX_Control(pDX, IDC_CHECK_CLKMONEN, m_CHECK_CLKMONEN);
	DDX_Control(pDX, IDC_COMBO_PWMFREQ_OTP, m_COMBO_PWMFREQ_OTP);
	DDX_Control(pDX, IDC_COMBO_PG_THRESH, m_COMBO_PG_THRESH);
	DDX_Control(pDX, IDC_COMBO_NG_THRESH, m_COMBO_NG_THRESH);
	DDX_Control(pDX, IDC_CHECK_DUAL_PROFILE_EN, m_CHECK_DUAL_PROFILE_EN);
	DDX_Control(pDX, IDC_CHECK_TRIPLE_PROFILE_EN, m_CHECK_TRIPLE_PROFILE_EN);
	DDX_Control(pDX, IDC_CHECK_HP_ALARM_DIS, m_CHECK_HP_ALARM_DIS);

	DDX_Control(pDX, IDC_COMBO_RETRY_TIMEOTP, m_COMBO_RETRY_TIMEOTP);
	DDX_Control(pDX, IDC_CHECK_RETRY_TRISTATEOTP, m_CHECK_RETRY_TRISTATEOTP);
	DDX_Control(pDX, IDC_CHECK_RETRY_ILIM_BRKOTP, m_CHECK_RETRY_ILIM_BRKOTP);
	DDX_Control(pDX, IDC_COMBO_CheckOTPCALFile, m_COMBO_CheckOTPCALFile);
}


BEGIN_MESSAGE_MAP(COTPcalDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OTPCAL, &COTPcalDlg::OnBnClickedButtonOtpcal)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_OTPCAL, &COTPcalDlg::OnBnClickedButtonSaveOtpcal)
	ON_CBN_SELCHANGE(IDC_COMBO_OSCTCOTP, &COTPcalDlg::OnCbnSelchangeComboOsctcotp)
	ON_CBN_SELCHANGE(IDC_COMBO_OSCOFFOTP, &COTPcalDlg::OnCbnSelchangeComboOscoffotp)
	ON_CBN_SELCHANGE(IDC_COMBO_CHROMSEL, &COTPcalDlg::OnCbnSelchangeComboChromsel)
	ON_CBN_SELCHANGE(IDC_COMBO_PINSEL, &COTPcalDlg::OnCbnSelchangeComboPinsel)
	ON_BN_CLICKED(IDC_CHECK_FFOTP, &COTPcalDlg::OnBnClickedCheckFfotp)
	ON_BN_CLICKED(IDC_CHECK_TRIPHASEOTP, &COTPcalDlg::OnBnClickedCheckTriphaseotp)
	ON_BN_CLICKED(IDC_CHECK_DLLOTP, &COTPcalDlg::OnBnClickedCheckDllotp)
	ON_BN_CLICKED(IDC_CHECK_PMCOTP, &COTPcalDlg::OnBnClickedCheckPmcotp)
	ON_BN_CLICKED(IDC_CHECK_PWMOVROTP, &COTPcalDlg::OnBnClickedCheckPwmovrotp)
	ON_BN_CLICKED(IDC_CHECK_VARDACOTP, &COTPcalDlg::OnBnClickedCheckVardacotp)
	ON_BN_CLICKED(IDC_CHECK_OFFBRKOTP, &COTPcalDlg::OnBnClickedCheckOffbrkotp)
	ON_BN_CLICKED(IDC_CHECK_SKIP_S2, &COTPcalDlg::OnBnClickedCheckSkipS2)
	ON_CBN_SELCHANGE(IDC_COMBO_PWM_LOW, &COTPcalDlg::OnCbnSelchangeComboPwmLow)
	ON_CBN_SELCHANGE(IDC_COMBO_PWM_FLOAT, &COTPcalDlg::OnCbnSelchangeComboPwmFloat)
	ON_BN_CLICKED(IDC_CHECK_PWMFLOATDIS, &COTPcalDlg::OnBnClickedCheckPwmfloatdis)
	ON_BN_CLICKED(IDC_CHECK_OTP_CRC_CHK_DIS, &COTPcalDlg::OnBnClickedCheckOtpCrcChkDis)
	ON_BN_CLICKED(IDC_CHECK_CLKMONEN, &COTPcalDlg::OnBnClickedCheckClkmonen)
	ON_CBN_SELCHANGE(IDC_COMBO_PWMFREQ_OTP, &COTPcalDlg::OnCbnSelchangeComboPwmfreqOtp)
	ON_CBN_SELCHANGE(IDC_COMBO_PG_THRESH, &COTPcalDlg::OnCbnSelchangeComboPgThresh)
	ON_CBN_SELCHANGE(IDC_COMBO_NG_THRESH, &COTPcalDlg::OnCbnSelchangeComboNgThresh)
	ON_BN_CLICKED(IDC_CHECK_DUAL_PROFILE_EN, &COTPcalDlg::OnBnClickedCheckDualProfileEn)
	ON_BN_CLICKED(IDC_CHECK_TRIPLE_PROFILE_EN, &COTPcalDlg::OnBnClickedCheckTripleProfileEn)
//	ON_CBN_SELCHANGE(IDC_COMBO_CheckOTPCALFile, &COTPcalDlg::OnSelchangeComboCheckotpcalfile)
	ON_CBN_DROPDOWN(IDC_COMBO_CheckOTPCALFile, &COTPcalDlg::OnDropdownComboCheckotpcalfile)
	ON_BN_CLICKED(IDC_BUTTON_CheckOTPCALFile, &COTPcalDlg::OnBnClickedButtonCheckotpcalfile)
END_MESSAGE_MAP()

BOOL COTPcalDlg::OnInitDialog()
{
	
	int temp;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	CDialog::OnInitDialog();
	edit=0;
	use_debugdlg_otpcal.OnBnClickedButtonStart();//no use
	
	temp=pParent->dataread_anybits(0x1a,3,1);
	if (!success){goto end;};

	if(temp==0){
		m_CHECK_OTPCAL_DONE.SetCheck(0);
	}else{
        m_CHECK_OTPCAL_DONE.SetCheck(1);
	}
	
	temp=pParent->dataread_anybits(0x14,2,1);
	if (!success){goto end;};
	m_COMBO_PG_THRESH.SetCurSel(temp);

	    m_CHECK_DLLOTP.EnableWindow(0);
		m_CHECK_FFOTP.EnableWindow(0);
		m_CHECK_TRIPHASEOTP.EnableWindow(0);
		m_CHECK_PMCOTP.EnableWindow(0);
		m_CHECK_PWMOVROTP.EnableWindow(0);
		m_CHECK_VARDACOTP.EnableWindow(0);
		m_CHECK_SKIP_S2.EnableWindow(0);
		m_CHECK_OFFBRKOTP.EnableWindow(0);
		m_CHECK_CLKMONEN.EnableWindow(0);
		m_CHECK_OTP_CRC_CHK_DIS.EnableWindow(0);
		m_CHECK_PWMFLOATDIS.EnableWindow(0);
		m_CHECK_RETRY_TRISTATEOTP.EnableWindow(0);
		m_CHECK_RETRY_ILIM_BRKOTP.EnableWindow(0);
		m_CHECK_DUAL_PROFILE_EN.EnableWindow(0);
		m_CHECK_TRIPLE_PROFILE_EN.EnableWindow(0);
		m_CHECK_HP_ALARM_DIS.EnableWindow(0);
		m_COMBO_OSCTCOTP.EnableWindow(0);
		m_COMBO_OSCOFFOTP.EnableWindow(0);
		m_COMBO_CHROMSEL.EnableWindow(0);
		m_COMBO_PINSEL.EnableWindow(0);
		m_COMBO_PWM_LOW.EnableWindow(0);
		m_COMBO_PWM_FLOAT.EnableWindow(0);
		//m_COMBO_PG_THRESH.EnableWindow(0);
		m_COMBO_NG_THRESH.EnableWindow(0);
		m_COMBO_PWMFREQ_OTP.EnableWindow(0);
		m_COMBO_RETRY_TIMEOTP.EnableWindow(0);

	displayfile();	
	
    m_CHECK_PASSCAL.SetCheck(0);
	m_CHECK_FAILCAL.SetCheck(0);
	m_PROGRESS2.SetPos(nLowercal);
    end:;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COTPcalDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->otpcaldlg = NULL;
    delete this;
}

void COTPcalDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void COTPcalDlg::OnClose() 
{
	DestroyWindow();
}

void COTPcalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void COTPcalDlg::OnOK() 
{
}

void COTPcalDlg::OnCancel() 
{
}

void COTPcalDlg::OnBnClickedButtonOtpcal()
{
	CString otpprog,auto_spin,dats;
    int i,temp=0;
	int timeout_counter=0;
    int otp_cal_done,otp_cal_sel,otp1_done,query;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	if(edit==1) goto end;
	/*pwm_on_mod=0;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+1;
   use_fanmotordlg_otpcal.rreg(0x11);
    pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;*/
	m_CHECK_PASSCAL.SetCheck(0);
	m_CHECK_FAILCAL.SetCheck(0);
	UpdateWindow();       //update text box value

	/*******************************Virtual BD Burn*****************************/
	if (pParent->virtual_board)
	{
		temp=pParent->rreg(0x1a);//set OPTcal_done=1
		temp|=0x10;
		pParent->wreg(0x1a,temp);

		for (int j=0; j<256; j++)
			pParent->virtual_board_otp[j]=pParent->virtual_board_reg[j];


		pParent->fOTP=1;//reg R/W hand over to OTP array

		//burn otpcal file value to otp array
		writeotpcalreg();
	
		m_CHECK_PASSCAL.SetCheck(1);
		pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Burn Process Pass!");
		m_CHECK_OTPCAL_DONE.SetCheck(1);
	
		return;
	}
	/*******************************************************************************/


	dats="1";
    pParent->dataupdate_anybits(0x14,5,dats,1);   //uv_dis  //?????????????????????????????? 
	query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Query", (LPCWSTR)L"Reduce VDD to 8V.\nComfirm Burn Setup and Setting?");
    if(query == IDCANCEL)
	{
		goto end;
	}
	else if(query == IDOK)
	{
	    
		otp_cal_sel=pParent->dataread_anybits(0x01,7,1);// read back otp_cal_sel value
	    if(otp_cal_sel==1){
			otp_cal_done=pParent->dataread_anybits(0x1a,3,1);
			if(otp_cal_done==1){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP_CAL_DONE!\nOTP_CAL cannot be Burned Again!");
				goto end;
			};

			//ClearRegVal();
			writeotpcalreg();
			m_PROGRESS2.SetRange(nLowercal,nUppercal);
			m_PROGRESS2.SetStep((nUppercal-nLowercal)/nStepcal);
			m_PROGRESS2.SetPos(0);
			Sleep(10);
			auto_spin="0";
			pParent->dataupdate_anybits(0x04,0,auto_spin,1); //FAN_EN=0
			otpprog="1";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=1
			
			//m_PROGRESS.GetPos();
			for (i=nLowercal;i<nUppercal;i=i+nStepcal)
			{
				m_PROGRESS2.StepIt();
				Sleep(10);
			}
			otpprog="0";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=0
			do{
				timeout_counter++;
				temp=pParent->dataread_anybits(0x1a,3,1);
			    if (!success){goto end;};
			}while((temp==0)&&(timeout_counter != TIMEOUT_otpcal));
			pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Please change power supply to 12V and do a power cycle.\nPress 'OK' after power cycle to continue!");
			readotpcalreg();
			
		}else if(otp_cal_sel==0){

			dats="1";
            pParent->dataupdate_anybits(0x01,7,dats,1);//set Otp_cal_sel value to 1

			otp_cal_done=pParent->dataread_anybits(0x1a,3,1);
			if(otp_cal_done==1){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP_CAL_DONE!\nOTP_CAL cannot be Burned Again!");
				goto end;
			};

			//ClearRegVal();
			writeotpcalreg();
			m_PROGRESS2.SetRange(nLowercal,nUppercal);
			m_PROGRESS2.SetStep((nUppercal-nLowercal)/nStepcal);
			m_PROGRESS2.SetPos(0);
			Sleep(100);
			auto_spin="0";
			pParent->dataupdate_anybits(0x04,0,auto_spin,1); //FAN_EN=0
			otpprog="1";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=1
			
			//m_PROGRESS.GetPos();
			for (i=nLowercal;i<nUppercal;i=i+nStepcal)
			{
				m_PROGRESS2.StepIt();
				Sleep(10);
			}
			otpprog="0";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=0
			do{
				timeout_counter++;
				temp=pParent->dataread_anybits(0x1a,3,1);
			    if (!success){goto end;};
			}while((temp==0)&&(timeout_counter != TIMEOUT_otpcal));
			pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Please change power supply to 12V and do a power cycle.\nPress 'OK' after power cycle to continue!");
			readotpcalreg();
			dats="0";
            pParent->dataupdate_anybits(0x01,7,dats,1);//set back Otp_cal_sel value to 0

	   };
	};

   //dats="0";
   //pParent->dataupdate_anybits(0x14,5,dats,1);   //uv_en
   end:;
}

//write to OTP_CAL register
void COTPcalDlg::writeotpcalreg()
{
    FILE *fpi;
	int regval,regtemp,mask,clampreg,regtemplsb,regtempmsb,clamp,seln;
	CString errmsg,dat;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0;
	CString str,datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	const TCHAR* fpi_name = L"burn_otpcal_file.txt";
	
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"burn_otpcal_file.txt Not Found. Please use EDIT file button to create file");
		goto end_error;
	}

	    while (i != EOF){
		regval = 0xffff;
		i = fscanf_s(fpi, "%s", command, 1000);
		if(i == EOF) break;
		wordcnt++;

            if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		    else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>2)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x04,5,datbits,1);
				seln=pParent->dataread_anybits(0x04,5,1);
				m_CHECK_FFOTP.SetCheck(seln);

				regtemp=(regval>>3)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x04,4,datbits,1);
				seln=pParent->dataread_anybits(0x04,4,1);
				m_CHECK_DLLOTP.SetCheck(seln);
				
	
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x08,0,datbits,1);
				seln=pParent->dataread_anybits(0x08,0,1);
				m_CHECK_TRIPHASEOTP.SetCheck(seln);
				regtemp=(regval>>6)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x08,1,datbits,1);
				seln=pParent->dataread_anybits(0x08,1,1);
				m_CHECK_PMCOTP.SetCheck(seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x0b,0,datbits,1);
				seln=pParent->dataread_anybits(0x0b,0,1);
				m_CHECK_PWMOVROTP.SetCheck(seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x10,1,datbits,1);
				seln=pParent->dataread_anybits(0x10,1,1);
				m_CHECK_VARDACOTP.SetCheck(seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x11,1,datbits,1);
				seln=pParent->dataread_anybits(0x11,1,1);
				m_COMBO_PWMFREQ_OTP.SetCurSel(seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
				datbits="1";
				pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sns=1
				mask=1;
				regtemp=(regval>>7)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x15,0,datbits,1);
				seln=pParent->dataread_anybits(0x15,0,1);
				m_CHECK_OFFBRKOTP.SetCheck(seln);
				regtemp=(regval>>6)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x15,1,datbits,1);
				seln=pParent->dataread_anybits(0x15,1,1);
				m_COMBO_CHROMSEL.SetCurSel(seln);
				regtemp=(regval>>5)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x15,2,datbits,1);
				seln=pParent->dataread_anybits(0x15,2,1);
				m_CHECK_OTP_CRC_CHK_DIS.SetCheck(seln);
				regtemp=(regval>>4)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x15,3,datbits,1);
				seln=pParent->dataread_anybits(0x15,3,1);
				m_CHECK_SKIP_S2.SetCheck(seln);
				mask=3;
				regtemp=(regval>>2)&mask;
				datbits = pParent->int2bin_anybits(regtemp,2);
				pParent->dataupdate_anybits(0x15,4,datbits,2);
				seln=pParent->dataread_anybits(0x15,4,2);
				m_COMBO_PWM_LOW.SetCurSel(seln);
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,2);
				pParent->dataupdate_anybits(0x15,6,datbits,2);
				seln=pParent->dataread_anybits(0x15,6,2);
				m_COMBO_PWM_FLOAT.SetCurSel(seln);
				datbits="0";
				pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sns=0
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x18,0,datbits,1);
				seln=pParent->dataread_anybits(0x18,0,1);
				m_CHECK_PWMFLOATDIS.SetCheck(seln);
				regtemp=(regval>>6)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x18,1,datbits,1);
				seln=pParent->dataread_anybits(0x18,1,1);
				m_CHECK_CLKMONEN.SetCheck(seln);
				regtemp=(regval>>3)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x18,4,datbits,1);
				seln=pParent->dataread_anybits(0x18,4,1);
				m_CHECK_HP_ALARM_DIS.SetCheck(seln);
				regtemp=(regval>>2)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x18,5,datbits,1);
				seln=pParent->dataread_anybits(0x18,5,1);
				m_CHECK_RETRY_TRISTATEOTP.SetCheck(seln);
				regtemp=(regval>>1)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x18,6,datbits,1);
				seln=pParent->dataread_anybits(0x18,6,1);
				m_CHECK_RETRY_ILIM_BRKOTP.SetCheck(seln);
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x18,7,datbits,1);
				seln=pParent->dataread_anybits(0x18,7,1);
				m_COMBO_RETRY_TIMEOTP.SetCurSel(seln);
				mask=3;
				regtemp=(regval>>4)&mask;
				datbits = pParent->int2bin_anybits(regtemp,2);
				pParent->dataupdate_anybits(0x18,2,datbits,2);
				seln=pParent->dataread_anybits(0x18,2,2);
				m_COMBO_PINSEL.SetCurSel(seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				datbits="0";
				pParent->dataupdate_anybits(0x01,7,datbits,1); //otp_cal_sel=0
				mask=7;
				regtemp=(regval>>5)&mask;
				datbits = pParent->int2bin_anybits(regtemp,3);
				pParent->dataupdate_anybits(0x1b,0,datbits,3);
				seln=pParent->dataread_anybits(0x1b,0,3);
				m_COMBO_OSCTCOTP.SetCurSel(seln);
				mask=31;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,5);
				pParent->dataupdate_anybits(0x1b,3,datbits,5);
				seln=pParent->dataread_anybits(0x1b,3,5);
				m_COMBO_OSCOFFOTP.SetCurSel(seln);
				datbits="1";
				pParent->dataupdate_anybits(0x01,7,datbits,1); //otp_cal_sel=1
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}

				else if (_stricmp(command, "Reg22h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg23h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg24h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
		
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

			
			}
			else
			{
				goto unknown_format;
			}  
		}

		else{
			unknown_format:;
			errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
		};
	};
			
	end:;
	end_error:;
	fclose(fpi);
}

//read and check OTP_CAL register
void COTPcalDlg::readotpcalreg()
{
	FILE *fpi;
	int regval,regtemp,mask,otpreg,otpregmask,use_reg_en,otp_cal_reg;
	CString errmsg;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0,temp;
	CString str,use_reg,usereg_temp,otpcal_temp,otp_cal,datbits,otpshow;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    use_reg_en=pParent->dataread_anybits(0x02,6,1); //use_reg
	usereg_temp=pParent->int2bin_anybits(use_reg_en,1);
	use_reg="0";
	pParent->dataupdate_anybits(0x02,6,use_reg,1); //use_reg=0

    otp_cal_reg=pParent->dataread_anybits(0x01,7,1); //otp_cal_sel
	otpcal_temp=pParent->int2bin_anybits(otp_cal_reg,1);
	otp_cal="1";
	pParent->dataupdate_anybits(0x01,7,otp_cal,1); //otp_cal_sel=1

	const TCHAR* fpi_name = L"burn_otpcal_file.txt";
	
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	}

            while (i != EOF){
			regval = 0xffff;
			i = fscanf_s(fpi, "%s", command, 1000);
			if(i == EOF) break;
			wordcnt++;	    
	
	   if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		    else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=3;
				regtemp=(regval>>2)&mask;
				otpreg=pParent->dataread_anybits(0x04,4,2);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}				
	       
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=3;
				regtemp=(regval>>6)&mask;
				otpreg=pParent->dataread_anybits(0x08,0,2);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				otpreg=pParent->dataread_anybits(0x0b,0,1);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				otpreg=pParent->dataread_anybits(0x10,1,1);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				otpreg=pParent->dataread_anybits(0x11,1,1);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
				datbits="1";
				pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sns=1
				pParent->dataupdate_anybits(0x01,7,otp_cal,1); //otp_cal_sel=1				
				regtemp=regval;
				otpreg=pParent->dataread_anybits(0x15,0,8);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				datbits="0";
				pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sns=0
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
				datbits="1";
				pParent->dataupdate_anybits(0x01,7,datbits,1); //otp_cal_sel=1
				regtemp=regval;
				otpreg=pParent->dataread_anybits(0x18,0,8);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				//use_debugdlg_otpcal.wreg(slave_addr,0x1b,0xff);
				datbits="0";
				pParent->dataupdate_anybits(0x01,7,datbits,1); //otp_cal_sel=0
				regtemp=regval;
				otpreg=pParent->dataread_anybits(0x1b,0,8);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				datbits="1";
				pParent->dataupdate_anybits(0x01,7,datbits,1); //otp_cal_sel=1
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}

				else if (_stricmp(command, "Reg22h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg23h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg24h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
		
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

			
			}
			else
			{
				goto unknown_format;
			}  
		}

		};
				m_CHECK_PASSCAL.SetCheck(1);
				pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Burn Process Pass!");
				temp=pParent->dataread_anybits(0x1a,3,1);
				if (!success){goto end;};

				if(temp==0){
					m_CHECK_OTPCAL_DONE.SetCheck(0);
				}else{
					m_CHECK_OTPCAL_DONE.SetCheck(1);
				}
				goto end;
			
			
				burn_failure:;
				m_CHECK_FAILCAL.SetCheck(1);
				temp=pParent->dataread_anybits(0x1a,3,1);
				if (!success){goto end;};

				if(temp==0){
					m_CHECK_OTPCAL_DONE.SetCheck(0);
				}else{
					m_CHECK_OTPCAL_DONE.SetCheck(1);
				}

				errmsg.Format(_T("Burn Failure.\nPlease check and burn again!"));
			    pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			    goto end;
				unknown_format:;
			    errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			    pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			    goto end;
	
		
	end:;
    pParent->dataupdate_anybits(0x02,6,usereg_temp,1); //original use_reg
	pParent->dataupdate_anybits(0x01,7,otpcal_temp,1); //original otp_cal_sel
	fclose(fpi);
	end_error:;

}


void COTPcalDlg::OnBnClickedButtonSaveOtpcal()
{
	FILE *fpo;
    FILE *fbo;
	errno_t err;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;



	CString FileStr;
	const TCHAR* fpo_name2 = L"backup_burn_otpcal_file.txt";
	const TCHAR* fpo_name = L"burn_otpcal_file.txt";
	CString datw;
	int length_dat,datr,query,regval,regval_temp,temp1,temp2,temp3,temp4,temp5,temp6,temp7;


	if(edit==0){
		edit=1;
		m_CHECK_DLLOTP.EnableWindow(1);
		m_CHECK_FFOTP.EnableWindow(1);
		m_CHECK_TRIPHASEOTP.EnableWindow(1);
		m_CHECK_PMCOTP.EnableWindow(1);
		m_CHECK_PWMOVROTP.EnableWindow(1);
		m_CHECK_VARDACOTP.EnableWindow(1);
		m_CHECK_OFFBRKOTP.EnableWindow(1);
		m_CHECK_SKIP_S2.EnableWindow(1);
		m_CHECK_CLKMONEN.EnableWindow(1);
		m_CHECK_OTP_CRC_CHK_DIS.EnableWindow(1);
		m_CHECK_PWMFLOATDIS.EnableWindow(1);
		m_CHECK_DUAL_PROFILE_EN.EnableWindow(1);
		m_CHECK_TRIPLE_PROFILE_EN.EnableWindow(1);
		m_CHECK_HP_ALARM_DIS.EnableWindow(1);
		m_CHECK_RETRY_TRISTATEOTP.EnableWindow(1);
		m_CHECK_RETRY_ILIM_BRKOTP.EnableWindow(1);
		m_COMBO_OSCTCOTP.EnableWindow(1);
		m_COMBO_OSCOFFOTP.EnableWindow(1);
		m_COMBO_CHROMSEL.EnableWindow(1);
		m_COMBO_PINSEL.EnableWindow(1);
		m_COMBO_PWM_LOW.EnableWindow(1);
		m_COMBO_PWM_FLOAT.EnableWindow(1);
		//m_COMBO_PG_THRESH.EnableWindow(1);
		m_COMBO_NG_THRESH.EnableWindow(1);
		m_COMBO_PWMFREQ_OTP.EnableWindow(1);
		m_COMBO_RETRY_TIMEOTP.EnableWindow(1);

        displayfile();	
	}else{
        edit=0;
		m_CHECK_DLLOTP.EnableWindow(0);
		m_CHECK_FFOTP.EnableWindow(0);
		m_CHECK_TRIPHASEOTP.EnableWindow(0);
		m_CHECK_PMCOTP.EnableWindow(0);
		m_CHECK_PWMOVROTP.EnableWindow(0);
		m_CHECK_VARDACOTP.EnableWindow(0);
		m_CHECK_SKIP_S2.EnableWindow(0);
		m_CHECK_OFFBRKOTP.EnableWindow(0);
		m_CHECK_CLKMONEN.EnableWindow(0);
		m_CHECK_OTP_CRC_CHK_DIS.EnableWindow(0);
		m_CHECK_PWMFLOATDIS.EnableWindow(0);
		m_CHECK_DUAL_PROFILE_EN.EnableWindow(0);
		m_CHECK_TRIPLE_PROFILE_EN.EnableWindow(0);
		m_CHECK_HP_ALARM_DIS.EnableWindow(0);
		m_CHECK_RETRY_TRISTATEOTP.EnableWindow(0);
		m_CHECK_RETRY_ILIM_BRKOTP.EnableWindow(0);
		m_COMBO_OSCTCOTP.EnableWindow(0);
		m_COMBO_OSCOFFOTP.EnableWindow(0);
		m_COMBO_CHROMSEL.EnableWindow(0);
		m_COMBO_PINSEL.EnableWindow(0);
		m_COMBO_PWM_LOW.EnableWindow(0);
		m_COMBO_PWM_FLOAT.EnableWindow(0);
		//m_COMBO_PG_THRESH.EnableWindow(0);
		m_COMBO_NG_THRESH.EnableWindow(0);
		m_COMBO_PWMFREQ_OTP.EnableWindow(0);
		m_COMBO_RETRY_TIMEOTP.EnableWindow(0);

		query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Query", (LPCWSTR)L"Comfirm OTPCAL setting and save file?");
			if(query == IDCANCEL)
			{
				//release MessageBox if otpcal dialog is closed.
				if (pParent->otpcaldlg==NULL)
					return;

				displayfile();
				goto end;
			}
			else if(query == IDOK)
			{
				//release MessageBox if otpcal dialog is closed.
				if (pParent->otpcaldlg==NULL)
					return;

                _wfopen_s(&fbo, fpo_name2, _T("w"));
	    
			    fclose(fbo);

			    CopyFileW(fpo_name, fpo_name2, false); //back up current save file
					
				if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
			{
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
				goto end_error;
			};

				//regval=use_fanmotordlg_otpcal.rreg(0x01);
				fprintf( fpo, "Reg01h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x02);
				fprintf( fpo, "Reg02h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x03);
				fprintf( fpo, "Reg03h %x\n", 0);

				//regval_temp=use_fanmotordlg_otpcal.rreg(0x04);
				temp1=m_CHECK_DLLOTP.GetCheck();
				temp2=m_CHECK_FFOTP.GetCheck();
                regval=(0 & 0xf3)+(temp1<<3)+(temp2<<2);
				fprintf( fpo, "Reg04h %x\n", regval); 

				//regval=use_fanmotordlg_otpcal.rreg(0x05);
				fprintf( fpo, "Reg05h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x06);
				fprintf( fpo, "Reg06h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x07);
				fprintf( fpo, "Reg07h %x\n", 0); 

				//regval_temp=use_fanmotordlg_otpcal.rreg(0x08);
				temp1=m_CHECK_TRIPHASEOTP.GetCheck();
				temp2=m_CHECK_PMCOTP.GetCheck();
                regval=(0 & 0x3f)+(temp1<<7)+(temp2<<6);
				fprintf( fpo, "Reg08h %x\n", regval); 

				//regval=use_fanmotordlg_otpcal.rreg(0x09);
				fprintf( fpo, "Reg09h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x0a);
				fprintf( fpo, "Reg0Ah %x\n", 0); 

				//regval_temp=use_fanmotordlg_otpcal.rreg(0x0b);
				temp1=m_CHECK_PWMOVROTP.GetCheck();
                regval=(0 & 0x7f)+(temp1<<7);
				fprintf( fpo, "Reg0Bh %x\n", regval); 

				//regval=use_fanmotordlg_otpcal.rreg(0x0c);
				fprintf( fpo, "Reg0Ch %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x0d);
				fprintf( fpo, "Reg0Dh %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x0e);
				fprintf( fpo, "Reg0Eh %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x0f);
				fprintf( fpo, "Reg0Fh %x\n", 0); 

				//regval_temp=use_fanmotordlg_otpcal.rreg(0x10);
				temp1=m_CHECK_VARDACOTP.GetCheck();
                regval=(0 & 0xbf)+(temp1<<6);
				fprintf( fpo, "Reg10h %x\n", regval); 

				//regval_temp=use_fanmotordlg_otpcal.rreg(0x11);
				temp1=m_COMBO_PWMFREQ_OTP.GetCurSel();
                regval=(0 & 0xbf)+(temp1<<6);;
				fprintf( fpo, "Reg11h %x\n", regval); 

				//regval=use_fanmotordlg_otpcal.rreg(0x12);
				fprintf( fpo, "Reg12h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x13);
				fprintf( fpo, "Reg13h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x14);
				fprintf( fpo, "Reg14h %x\n", 0); 

				temp1=m_CHECK_OFFBRKOTP.GetCheck();
				temp2=m_COMBO_CHROMSEL.GetCurSel();
				temp3=m_CHECK_OTP_CRC_CHK_DIS.GetCheck();
				temp4=m_CHECK_SKIP_S2.GetCheck();
				temp5=m_COMBO_PWM_LOW.GetCurSel();
				temp6=m_COMBO_PWM_FLOAT.GetCurSel();
                regval=(temp1<<7)+(temp2<<6)+(temp3<<5)+(temp4<<4)+(temp5<<2)+temp6;
				fprintf( fpo, "Reg15h %x\n", regval); 

				//regval_temp=use_fanmotordlg_otpcal.rreg(0x18);
				temp1=m_CHECK_PWMFLOATDIS.GetCheck();
				temp2=m_CHECK_CLKMONEN.GetCheck();
				temp3=m_COMBO_PINSEL.GetCurSel();
				temp4=m_CHECK_HP_ALARM_DIS.GetCheck();
				temp5=m_CHECK_RETRY_TRISTATEOTP.GetCheck();
				temp6=m_CHECK_RETRY_ILIM_BRKOTP.GetCheck();
				temp7=m_COMBO_RETRY_TIMEOTP.GetCurSel();
                regval=(temp1<<7)+(temp2<<6)+(temp3<<4)+(temp4<<3)+(temp5<<2)+(temp6<<1)+temp7;
				fprintf( fpo, "Reg18h %x\n", regval); 

				temp1=m_COMBO_OSCTCOTP.GetCurSel();
				temp2=m_COMBO_OSCOFFOTP.GetCurSel();
                regval=(temp1<<5)+temp2;
				fprintf( fpo, "Reg1Bh %x\n", regval); 

     			//regval=use_fanmotordlg_otpcal.rreg(0x1c);
				fprintf( fpo, "Reg1Ch %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x1d);
				fprintf( fpo, "Reg1Dh %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x1e);
				fprintf( fpo, "Reg1Eh %x\n", 0); 

     			//regval=use_fanmotordlg_otpcal.rreg(0x1f);
				fprintf( fpo, "Reg1Fh %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x20);
				fprintf( fpo, "Reg20h %x\n", 0);

				//regval=use_fanmotordlg_otpcal.rreg(0x22);
				fprintf( fpo, "Reg22h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x23);
				fprintf( fpo, "Reg23h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x24);
				fprintf( fpo, "Reg24h %x\n", 0); 

     			//regval=use_fanmotordlg_otpcal.rreg(0x25);
				fprintf( fpo, "Reg25h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x26);
				fprintf( fpo, "Reg26h %x\n", 0);

				//regval=use_fanmotordlg_otpcal.rreg(0x27);
				fprintf( fpo, "Reg27h %x\n", 0); 

     			//regval=use_fanmotordlg_otpcal.rreg(0x28);
				fprintf( fpo, "Reg28h %x\n", 0); 

				//regval=use_fanmotordlg_otpcal.rreg(0x29);
				fprintf( fpo, "Reg29h %x\n", 0);

				fclose(fpo);
				end_error:;
	     }
	  };

end:;
}

void COTPcalDlg::OnCbnSelchangeComboOsctcotp()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_OSCTCOTP.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
	//pParent->dataupdate_anybits(0x1b,0,datbits,3);
}

void COTPcalDlg::OnCbnSelchangeComboOscoffotp()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_OSCOFFOTP.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,5);
	//pParent->dataupdate_anybits(0x1b,3,datbits,5);
}

void COTPcalDlg::OnCbnSelchangeComboChromsel()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_CHROMSEL.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,1);
	//pParent->dataupdate_anybits(0x15,1,datbits,1);
}

void COTPcalDlg::OnCbnSelchangeComboPinsel()   //PROFILE_SEL
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PINSEL.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	//pParent->dataupdate_anybits(0x15,0,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckFfotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_FFOTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x04,5,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckTriphaseotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_TRIPHASEOTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x08,0,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckDllotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_DLLOTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x04,4,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckPmcotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_PMCOTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x08,1,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckPwmovrotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_PWMOVROTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x0b,0,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckVardacotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_VARDACOTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x10,1,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckOffbrkotp()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_OFFBRKOTP.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x15,0,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckSkipS2()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_SKIP_S2.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x15,3,datbits,1);
}

void COTPcalDlg::OnCbnSelchangeComboPwmLow()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PWM_LOW.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	//pParent->dataupdate_anybits(0x15,4,datbits,2);
}

void COTPcalDlg::OnCbnSelchangeComboPwmFloat()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PWM_FLOAT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,2);
	//pParent->dataupdate_anybits(0x15,6,datbits,2);
}

void COTPcalDlg::OnBnClickedCheckPwmfloatdis()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_PWMFLOATDIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x18,0,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckOtpCrcChkDis()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_OTP_CRC_CHK_DIS.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x15,2,datbits,1);
}

void COTPcalDlg::OnBnClickedCheckClkmonen()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_CLKMONEN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	//pParent->dataupdate_anybits(0x18,1,datbits,1);
}

void COTPcalDlg::displayfile()
{
    FILE *fpi;
	int regval,regtemp,mask,clampreg,regtemplsb,regtempmsb,clamp,seln;
	CString errmsg,dat;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0;
	CString str,datbits;

	const TCHAR* fpi_name = L"burn_otpcal_file.txt";

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"burn_otpcal_file.txt Not Found. Please use EDIT file button to create file");
		goto end_error;
	}

	    while (i != EOF){
		regval = 0xffff;
		i = fscanf_s(fpi, "%s", command, 1000);
		if(i == EOF) break;
		wordcnt++;

            if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		    else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>2)&mask;
				m_CHECK_FFOTP.SetCheck(regtemp);
				regtemp=(regval>>3)&mask;
				m_CHECK_DLLOTP.SetCheck(regtemp);
				
	
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				m_CHECK_TRIPHASEOTP.SetCheck(regtemp);
				regtemp=(regval>>6)&mask;
				m_CHECK_PMCOTP.SetCheck(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				m_CHECK_PWMOVROTP.SetCheck(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				m_CHECK_VARDACOTP.SetCheck(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				m_COMBO_PWMFREQ_OTP.SetCurSel(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				m_CHECK_OFFBRKOTP.SetCheck(regtemp);
				regtemp=(regval>>6)&mask;
				m_COMBO_CHROMSEL.SetCurSel(regtemp);
				regtemp=(regval>>5)&mask;
				m_CHECK_OTP_CRC_CHK_DIS.SetCheck(regtemp);
				regtemp=(regval>>4)&mask;
				m_CHECK_SKIP_S2.SetCheck(regtemp);
				mask=3;
				regtemp=(regval>>2)&mask;
				m_COMBO_PWM_LOW.SetCurSel(regtemp);
				regtemp=regval&mask;
				m_COMBO_PWM_FLOAT.SetCurSel(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				m_CHECK_PWMFLOATDIS.SetCheck(regtemp);
				regtemp=(regval>>6)&mask;
				m_CHECK_CLKMONEN.SetCheck(regtemp);
				regtemp=(regval>>3)&mask;
				m_CHECK_HP_ALARM_DIS.SetCheck(regtemp);
				regtemp=(regval>>2)&mask;
				m_CHECK_RETRY_TRISTATEOTP.SetCheck(regtemp);
				regtemp=(regval>>1)&mask;
				m_CHECK_RETRY_ILIM_BRKOTP.SetCheck(regtemp);
				regtemp=regval&mask;
				m_COMBO_RETRY_TIMEOTP.SetCurSel(regtemp);
				mask=3;
				regtemp=(regval>>4)&mask;
				m_COMBO_PINSEL.SetCurSel(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=7;
				regtemp=(regval>>5)&mask;
				m_COMBO_OSCTCOTP.SetCurSel(regtemp);
				mask=31;
				regtemp=regval&mask;
				m_COMBO_OSCOFFOTP.SetCurSel(regtemp);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}

		else if (_stricmp(command, "Reg22h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg23h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg24h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
		
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

			
			}
			else
			{
				goto unknown_format;
			}  
		}

		else{
			unknown_format:;
			errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
		};
	};
			
	end:;
	fclose(fpi);
	end_error:;
	
}
void COTPcalDlg::OnCbnSelchangeComboPwmfreqOtp()
{
	int seln;
	CString datbits;

	seln = m_COMBO_PWMFREQ_OTP.GetCurSel();	
}

void COTPcalDlg::OnCbnSelchangeComboPgThresh()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_PG_THRESH.GetCurSel();
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x14,2,datbits,1);
}

void COTPcalDlg::OnCbnSelchangeComboNgThresh()
{
	int seln;
	CString datbits;

	seln = m_COMBO_NG_THRESH.GetCurSel();	
}

void COTPcalDlg::OnBnClickedCheckDualProfileEn()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_DUAL_PROFILE_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
}

void COTPcalDlg::OnBnClickedCheckTripleProfileEn()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_TRIPLE_PROFILE_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
}



void COTPcalDlg::ClearRegVal()
{
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	for (int RegAddr=0x00;RegAddr<=0x29;RegAddr++)
	{
		if ((RegAddr==0x16)||(RegAddr==0x17)||(RegAddr==0x19)||(RegAddr==0x1a)||(RegAddr==0x21))
			continue;
		else
			pParent->wreg(RegAddr,0);
	}	
}


void COTPcalDlg::OnDropdownComboCheckotpcalfile()
{
	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_CheckOTPCALFile, 0, DDL_READWRITE);
}


void COTPcalDlg::OnBnClickedButtonCheckotpcalfile()
{
	FILE *fpi;
	int regval,regtemp,mask,otpreg,otpregmask,use_reg_en,otp_cal_reg;
	CString errmsg;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0,temp;
	CString str,use_reg,usereg_temp,otpcal_temp,otp_cal,datbits,otpshow;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    use_reg_en=pParent->dataread_anybits(0x02,6,1); //use_reg
	usereg_temp=pParent->int2bin_anybits(use_reg_en,1);
	use_reg="0";//select parameters from OTP settings, not reg settings
	pParent->dataupdate_anybits(0x02,6,use_reg,1); //use_reg=0

    otp_cal_reg=pParent->dataread_anybits(0x01,7,1); //otp_cal_sel
	otpcal_temp=pParent->int2bin_anybits(otp_cal_reg,1);
	otp_cal="1";//1: program Marvell OTP block,0: program Customer OTP block
	pParent->dataupdate_anybits(0x01,7,otp_cal,1); //otp_cal_sel=1

	//get original OTPCAL file name to compare with the burned OTP bits
	CString FileStr;
	int length=0;

	length = m_COMBO_CheckOTPCALFile.GetWindowTextLengthW();
	if (length == 0) 
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Specified.");
		goto end_error;
	}
	else 
		m_COMBO_CheckOTPCALFile.GetWindowText(FileStr);

	const TCHAR* fpi_name = (LPCTSTR)FileStr;

	
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	}

            while (i != EOF){
			regval = 0xffff;
			i = fscanf_s(fpi, "%s", command, 1000);
			if(i == EOF) break;
			wordcnt++;	    
	
	   if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		    else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=3;
				regtemp=(regval>>2)&mask;
				otpreg=pParent->dataread_anybits(0x04,4,2);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}				
	       
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
			else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=3;
				regtemp=(regval>>6)&mask;
				otpreg=pParent->dataread_anybits(0x08,0,2);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>7)&mask;
				otpreg=pParent->dataread_anybits(0x0b,0,1);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				otpreg=pParent->dataread_anybits(0x10,1,1);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=1;
				regtemp=(regval>>6)&mask;
				otpreg=pParent->dataread_anybits(0x11,1,1);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
				datbits="1";
				pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sns=1
				pParent->dataupdate_anybits(0x01,7,otp_cal,1); //otp_cal_sel=1				
				regtemp=regval;
				otpreg=pParent->dataread_anybits(0x15,0,8);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				datbits="0";
				pParent->dataupdate_anybits(0x01,3,datbits,1); //pos_sns=0
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
				datbits="1";
				pParent->dataupdate_anybits(0x01,7,datbits,1); //otp_cal_sel=1
				regtemp=regval;
				otpreg=pParent->dataread_anybits(0x18,0,8);
				if(otpreg!=regtemp){
                   goto burn_failure;
				}
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
							//ignore osc bits comparison
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}
		}

				else if (_stricmp(command, "Reg22h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg23h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg24h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
		
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

			
			}
			else
			{
				goto unknown_format;
			}  
		}

		};
	
				pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Checking OTPCAL Burning File Pass!");
				goto end;

				burn_failure:;
				errmsg.Format(_T("Checking OTPCAL Burning File Failure.\nPlease check the file and burn again!"));
			    pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			    goto end;

				unknown_format:;
			    errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			    pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			    goto end;
		
	end:;
    pParent->dataupdate_anybits(0x02,6,usereg_temp,1); //original use_reg
	pParent->dataupdate_anybits(0x01,7,otpcal_temp,1); //original otp_cal_sel
	fclose(fpi);
	end_error:;

}
