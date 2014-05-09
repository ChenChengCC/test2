// OTPDlg.cpp : implementation file
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

int TIMEOUT_otp = 100; // 1s
int edit_otp=0;
int nLower = 0;
int nUpper = 100;
int nStep = 10;
int COMBOWIDTH_OTP = 140;
wchar_t tora[5][120]= {L" ad_torque_a[0] ",
						L" ad_torque_a[1] ",
						L" ad_torque_a[2] ",
						L" ad_torque_a[3] ",
						L" ad_torque_a[4] "};
wchar_t torb[5][120]= {L" ad_torque_b[0] ",
						L" ad_torque_b[1] ",
						L" ad_torque_b[2] ",
						L" ad_torque_b[3] ",
						L" ad_torque_b[4] "};
wchar_t torc[5][120]= {L" ad_torque_c[0] ",
						L" ad_torque_c[1] ",
						L" ad_torque_c[2] ",
						L" ad_torque_c[3] ",
						L" ad_torque_c[4] "};
wchar_t tord[5][120]= {L" ad_torque_d[0] ",
						L" ad_torque_d[1] ",
						L" ad_torque_d[2] ",
						L" ad_torque_d[3] ",
						L" ad_torque_d[4] "};
wchar_t tore[5][120]= {L" ad_torque_e[0] ",
						L" ad_torque_e[1] ",
						L" ad_torque_e[2] ",
						L" ad_torque_e[3] ",
						L" ad_torque_d[4] "};
wchar_t torf[5][120]= {L" ad_torque_f[0] ",
						L" ad_torque_f[1] ",
						L" ad_torque_f[2] ",
						L" ad_torque_f[3] ",
						L" ad_torque_f[4] "};
wchar_t torg[5][120]= {L" ad_torque_g[0] ",
						L" ad_torque_g[1] ",
						L" ad_torque_g[2] ",
						L" ad_torque_g[3] ",
						L" ad_torque_g[4] "};
wchar_t torh[5][120]= {L" ad_torque_h[0] ",
						L" ad_torque_h[1] ",
						L" ad_torque_h[2] ",
						L" ad_torque_h[3] ",
						L" ad_torque_h[4] "};

// COTPDlg dialog
CdebugDlg use_debugdlg_otp;
CdetailDlg use_detaildlg_otp;
//CFanmotorDlg use_fanmotordlg_otp;

IMPLEMENT_DYNAMIC(COTPDlg, CDialog)

COTPDlg::COTPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COTPDlg::IDD, pParent)
	, m_EDIT_FILETORA(_T(""))
	, m_EDIT_FILETORB(_T(""))
	, m_EDIT_FILETORC(_T(""))
	, m_EDIT_FILETORD(_T(""))
	, m_EDIT_FILETORE(_T(""))
	, m_EDIT_FILETORF(_T(""))
	, m_EDIT_FILETORG(_T(""))
	, m_EDIT_FILETORH(_T(""))
{
    m_pParent=pParent;
}

COTPDlg::~COTPDlg()
{
}

void COTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_PROGRESS1);
	DDX_Control(pDX, IDC_CHECK_PASS1, m_CHECK_PASS1);
	DDX_Control(pDX, IDC_CHECK_FAIL1, m_CHECK_FAIL1);
	DDX_Control(pDX, IDC_CHECK_OTPCALDONE, m_CHECK_OTPCALDONE);
	DDX_Control(pDX, IDC_CHECK_OTP1DONE, m_CHECK_OTP1DONE);
	DDX_Control(pDX, IDC_EDIT_TORA, m_EDIT_TORA);
	DDX_Control(pDX, IDC_COMBO_TORA, m_COMBO_TORA);
	DDX_Control(pDX, IDC_EDIT_TORB, m_EDIT_TORB);
	DDX_Control(pDX, IDC_COMBO_TORB, m_COMBO_TORB);
	DDX_Control(pDX, IDC_EDIT_TORC, m_EDIT_TORC);
	DDX_Control(pDX, IDC_COMBO_TORC, m_COMBO_TORC);
	DDX_Control(pDX, IDC_EDIT_TORD, m_EDIT_TORD);
	DDX_Control(pDX, IDC_COMBO_TORD, m_COMBO_TORD);
	DDX_Control(pDX, IDC_EDIT_TORE, m_EDIT_TORE);
	DDX_Control(pDX, IDC_COMBO_TORE, m_COMBO_TORE);
	DDX_Control(pDX, IDC_EDIT_TORF, m_EDIT_TORF);
	DDX_Control(pDX, IDC_COMBO_TORF, m_COMBO_TORF);
	DDX_Control(pDX, IDC_EDIT_TORG, m_EDIT_TORG);
	DDX_Control(pDX, IDC_COMBO_TORG, m_COMBO_TORG);
	DDX_Control(pDX, IDC_COMBO_TORH, m_COMBO_TORH);
	DDX_Control(pDX, IDC_EDIT_TORH, m_EDIT_TORH);
	DDX_Control(pDX, IDC_COMBO_TORQUE_FILELOAD, m_COMBO_TORQUE_FILELOAD);
	DDX_Control(pDX, IDC_COMBO_TORQUE_FILESAVE, m_COMBO_TORQUE_FILESAVE);
	DDX_Text(pDX, IDC_EDIT_FILETORA, m_EDIT_FILETORA);
	DDX_Text(pDX, IDC_EDIT_FILETORB, m_EDIT_FILETORB);
	DDX_Text(pDX, IDC_EDIT_FILETORC, m_EDIT_FILETORC);
	DDX_Text(pDX, IDC_EDIT_FILETORD, m_EDIT_FILETORD);
	DDX_Text(pDX, IDC_EDIT_FILETORE, m_EDIT_FILETORE);
	DDX_Text(pDX, IDC_EDIT_FILETORF, m_EDIT_FILETORF);
	DDX_Text(pDX, IDC_EDIT_FILETORG, m_EDIT_FILETORG);
	DDX_Text(pDX, IDC_EDIT_FILETORH, m_EDIT_FILETORH);
	DDX_Control(pDX, IDC_COMBO_MARGIN_RD_EN, m_COMBO_MARGIN_RD_EN);
	DDX_Control(pDX, IDC_COMBO_CheckOTP1File, m_COMBO_CheckOTP1File);
	DDX_Control(pDX, IDC_BUTTON_SAVE_FILE_OTPCAL, m_BUTTON_SAVE_FILE_OTPCAL);
}


BEGIN_MESSAGE_MAP(COTPDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_RADIO_OTP1, &COTPDlg::OnBnClickedRadioOtp1)
	ON_BN_CLICKED(IDC_RADIO_OTPCAL, &COTPDlg::OnBnClickedRadioOtpcal)
	ON_BN_CLICKED(IDC_BUTTON_BURN_OTP1, &COTPDlg::OnBnClickedButtonBurnOtp1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FILE_OTPCAL, &COTPDlg::OnBnClickedButtonSaveFileOtpcal)
	ON_CBN_DROPDOWN(IDC_COMBO_TORA, &COTPDlg::OnCbnDropdownComboTora)
	ON_CBN_DROPDOWN(IDC_COMBO_TORB, &COTPDlg::OnCbnDropdownComboTorb)
	ON_CBN_DROPDOWN(IDC_COMBO_TORC, &COTPDlg::OnCbnDropdownComboTorc)
	ON_CBN_DROPDOWN(IDC_COMBO_TORD, &COTPDlg::OnCbnDropdownComboTord)
	ON_CBN_DROPDOWN(IDC_COMBO_TORE, &COTPDlg::OnCbnDropdownComboTore)
	ON_CBN_DROPDOWN(IDC_COMBO_TORF, &COTPDlg::OnCbnDropdownComboTorf)
	ON_CBN_DROPDOWN(IDC_COMBO_TORG, &COTPDlg::OnCbnDropdownComboTorg)
	ON_CBN_DROPDOWN(IDC_COMBO_TORH, &COTPDlg::OnCbnDropdownComboTorh)
	ON_BN_CLICKED(IDC_BUTTON_FILELOAD, &COTPDlg::OnBnClickedButtonFileload)
	ON_BN_CLICKED(IDC_BUTTON_FILESAVE, &COTPDlg::OnBnClickedButtonFilesave)
	ON_CBN_DROPDOWN(IDC_COMBO_TORQUE_FILELOAD, &COTPDlg::OnCbnDropdownComboTorqueFileload)
	ON_CBN_DROPDOWN(IDC_COMBO_TORQUE_FILESAVE, &COTPDlg::OnCbnDropdownComboTorqueFilesave)
	ON_CBN_SELCHANGE(IDC_COMBO_MARGIN_RD_EN, &COTPDlg::OnCbnSelchangeComboMarginRdEn)
	ON_CBN_DROPDOWN(IDC_COMBO_CheckOTP1File, &COTPDlg::OnDropdownComboCheckotp1file)
	ON_BN_CLICKED(IDC_BUTTON_CheckOTP1File, &COTPDlg::OnBnClickedButtonCheckotp1file)
END_MESSAGE_MAP()


BOOL COTPDlg::OnInitDialog()
{
	int temp;

	CDialog::OnInitDialog();
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	edit_otp=0;
	m_BUTTON_SAVE_FILE_OTPCAL.SetWindowText(_T("EDIT burn_otp1_file.txt"));

	temp=pParent->dataread_anybits(0x01,7,1);
	if (!success){goto end;};

	if(temp == 0){
	    CheckRadioButton(IDC_RADIO_OTP1,IDC_RADIO_OTPCAL,IDC_RADIO_OTP1);
	}else{
		CheckRadioButton(IDC_RADIO_OTP1,IDC_RADIO_OTPCAL,IDC_RADIO_OTPCAL);
	}

	temp=pParent->dataread_anybits(0x1a,3,1);
	if (!success){goto end;};

	if(temp==0){
		m_CHECK_OTPCALDONE.SetCheck(0);
	}else{
        m_CHECK_OTPCALDONE.SetCheck(1);
	}

	temp=pParent->dataread_anybits(0x1a,2,1);
	if (!success){goto end;};

	if(temp==0){
		m_CHECK_OTP1DONE.SetCheck(0);
	}else{
        m_CHECK_OTP1DONE.SetCheck(1);
	}

	temp=pParent->dataread_anybits(0x14,2,1);
	if (!success){goto end;};

	m_COMBO_MARGIN_RD_EN.SetCurSel(temp);

	m_EDIT_TORA.EnableWindow(0);
	m_EDIT_TORB.EnableWindow(0);
	m_EDIT_TORC.EnableWindow(0);
	m_EDIT_TORD.EnableWindow(0);
	m_EDIT_TORE.EnableWindow(0);
	m_EDIT_TORF.EnableWindow(0);
	m_EDIT_TORG.EnableWindow(0);
	m_EDIT_TORH.EnableWindow(0);

    displaytorque();

	m_CHECK_PASS1.SetCheck(0);
	m_CHECK_FAIL1.SetCheck(0);
	m_PROGRESS1.SetPos(nLower);	

    end:;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COTPDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->otpdlg = NULL;
    delete this;
}

void COTPDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void COTPDlg::OnClose() 
{
	DestroyWindow();
}

void COTPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void COTPDlg::OnOK() 
{
}

void COTPDlg::OnCancel() 
{
}

void COTPDlg::OnBnClickedRadioOtp1()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "0";
	pParent->dataupdate_anybits(0x14,0,datbits,1);
}

void COTPDlg::OnBnClickedRadioOtpcal()
{
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	datbits = "1";
	pParent->dataupdate_anybits(0x14,0,datbits,1);
}


void COTPDlg::OnBnClickedButtonBurnOtp1()
{
	CString otpprog,auto_spin,dats;
    int i,temp=0;
	int timeout_counter=0;
    int otp_cal_done,otp_cal_sel,otp1_done,query;
	BOOL file_check;

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	if(edit_otp==1) goto end;
	/*pwm_on_mod=0;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+1;
    pParent->rreg(0x11);
    pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;*/
	m_CHECK_PASS1.SetCheck(0);
	m_CHECK_FAIL1.SetCheck(0);
	UpdateWindow();       //update text box value

	/*******************************Virtual BD Burn*****************************/
	if (pParent->virtual_board)
	{
		//check if otpcal already
		temp=pParent->rreg(0x1a);//read OPTcal_done
		temp=(temp&0x10)>>4;
		if (!temp)
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP1 cannot be Burned Yet!/nPlease burn OTPcal first!");
			return;
		}

		pParent->fOTP=0;//reg R/W hand over to Reg array
		temp=pParent->rreg(0x1a);//set OPT1_done=1
		temp|=0x20;
		pParent->wreg(0x1a,temp);


		pParent->fOTP=1;//reg R/W hand over to OTP array
		temp=pParent->rreg(0x1a);//set OPT1_done=1
		temp|=0x20;
		pParent->wreg(0x1a,temp);

		//burn otpcal file value to otp array
		writeotp1reg();

		m_CHECK_PASS1.SetCheck(1);
		pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Burn Process Pass!");
		m_CHECK_OTP1DONE.SetCheck(1);
	
		return;
	}
	/*******************************************************************************/
	//check *
	file_check = checkotp1file();
	if (!file_check)
	{
		pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Please re-confirm the adaptive torque settings.");
		OnBnClickedButtonSaveFileOtpcal();
		return;
	}

	//start burning
	dats="1";
    pParent->dataupdate_anybits(0x14,5,dats,1);   //uv_dis
	query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Query", (LPCWSTR)L"Reduce VDD to 8V.\nComfirm Burn Setup and Setting?");
    if(query == IDCANCEL)
	{
		goto end;
	}
	else if(query == IDOK)
	{
	    
		otp_cal_sel=pParent->dataread_anybits(0x01,7,1);
	    if(otp_cal_sel==1){
			/*otp_cal_done=pParent->dataread_anybits(0x1a,1,1);
			if(otp_cal_done==1){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP_CAL_DONE!\nOTP_CAL cannot be Burned Again!");
				goto end;
			};

			writeotpcalreg();
			m_PROGRESS1.SetRange(nLower,nUpper);
			m_PROGRESS1.SetStep((nUpper-nLower)/nStep);
			m_PROGRESS1.SetPos(0);
			Sleep(500);
			auto_spin="0";
			pParent->dataupdate_anybits(0x02,5,auto_spin,1); //FAN_EN=0
			otpprog="1";
			pParent->dataupdate_anybits(0x12,1,otpprog,1); //OTP_prog=1
			
			//m_PROGRESS.GetPos();
			for (i=nLower;i<nUpper;i=i+nStep)
			{
				m_PROGRESS1.StepIt();
				Sleep(15);
			}
			otpprog="0";
			pParent->dataupdate_anybits(0x12,1,otpprog,1); //OTP_prog=0
			pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Burn Process Completed!");
			readotpcalreg();*/
			dats="0";
            pParent->dataupdate_anybits(0x01,7,dats,1);
			otp_cal_done=pParent->dataread_anybits(0x1a,3,1);
			if(otp_cal_done==0){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Internal System Error!\nOTP1 cannot be Burned Yet!");
				goto end;
			};
			otp1_done=pParent->dataread_anybits(0x1a,2,1);
			if(otp1_done==1){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP1_DONE!\nOTP1 cannot be Burned Again!");
				goto end;
			};

			


			writeotp1reg();
			m_PROGRESS1.SetRange(nLower,nUpper);
			m_PROGRESS1.SetStep((nUpper-nLower)/nStep);
			m_PROGRESS1.SetPos(0);
			Sleep(10);
			auto_spin="0";
			pParent->dataupdate_anybits(0x04,0,auto_spin,1); //FAN_EN=0
			otpprog="1";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=1
			
			//m_PROGRESS.GetPos();
			for (i=nLower;i<nUpper;i=i+nStep)
			{
				m_PROGRESS1.StepIt();
				Sleep(10);
			}
			otpprog="0";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=0
			do{
				timeout_counter++;
				temp=pParent->dataread_anybits(0x1a,3,1);
			    if (!success){goto end;};
			}while((temp==0)&&(timeout_counter != TIMEOUT_otp));
	        pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Please change power supply to 12V and do a power cycle.\nPress 'OK' after power cycle to continue!");
			pParent->wreg(0x2a,6);
		    pParent->wreg(0x3d,5);

			//set fan_en=0
			auto_spin="0";
			pParent->dataupdate_anybits(0x04,0,auto_spin,1); //FAN_EN=0


			readotp1reg();
			dats="1";
			pParent->dataupdate_anybits(0x01,7,dats,1);//otp_cal_sel=1
		}
		
		else if(otp_cal_sel==0){
			otp_cal_done=pParent->dataread_anybits(0x1a,3,1);
			if(otp_cal_done==0){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Internal System Error!\nOTP1 cannot be Burned Yet!");
				goto end;
			};
			otp1_done=pParent->dataread_anybits(0x1a,2,1);
			if(otp1_done==1){
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP1_DONE!\nOTP1 cannot be Burned Again!");
				goto end;
			};

			writeotp1reg();
			m_PROGRESS1.SetRange(nLower,nUpper);
			m_PROGRESS1.SetStep((nUpper-nLower)/nStep);
			m_PROGRESS1.SetPos(0);
			Sleep(10);
			auto_spin="0";
			pParent->dataupdate_anybits(0x04,0,auto_spin,1); //FAN_EN=0
			otpprog="1";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=1
			
			//m_PROGRESS.GetPos();
			for (i=nLower;i<nUpper;i=i+nStep)
			{
				m_PROGRESS1.StepIt();
				Sleep(10);
			}
			otpprog="0";
			pParent->dataupdate_anybits(0x02,7,otpprog,1); //OTP_prog=0
			do{
				timeout_counter++;
				temp=pParent->dataread_anybits(0x1a,3,1);
			    if (!success){goto end;};
			}while((temp==0)&&(timeout_counter != TIMEOUT_otp));
			pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Please change power supply to 12V and do a power cycle.\nPress 'OK' after power cycle to continue!");
			pParent->wreg(0x2a,6);
		    pParent->wreg(0x3d,5);

			//set fan_en=0
			auto_spin="0";
			pParent->dataupdate_anybits(0x04,0,auto_spin,1); //FAN_EN=0

			readotp1reg();
	   };
	};

   //dats="0";
   //pParent->dataupdate_anybits(0x14,5,dats,1);   //uv_en
   end:;
}

//write to OTP1 register
void COTPDlg::writeotp1reg()
{
    FILE *fpi;
	int regval,regtemp,mask,clampreg,regtemplsb,regtempmsb,clamp;
	CString errmsg,dat;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0,temp;
	CString str,datbits;
	int RegEnd=0;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	const TCHAR* fpi_name = L"burn_otp1_file.txt";
	
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	}

	    while (i != EOF){
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

            if (_stricmp(command, "Reg01h") == 0 ){//read file R01[2:1], write to IC R01[2:1]
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=3;
				regtemp=(regval>>1)&mask;
				datbits = pParent->int2bin_anybits(regtemp,2);
				pParent->dataupdate_anybits(0x01,5,datbits,2);
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
				mask=7;
				regtemp=(regval>>5)&mask;
				datbits = pParent->int2bin_anybits(regtemp,3);
				pParent->dataupdate_anybits(0x02,0,datbits,3);
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
				mask=31;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,5);
				pParent->dataupdate_anybits(0x03,3,datbits,5);

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
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,2);
				pParent->dataupdate_anybits(0x04,6,datbits,2);
				mask=7;
				regtemp=(regval>>4)&mask;
				datbits = pParent->int2bin_anybits(regtemp,3);
				pParent->dataupdate_anybits(0x04,1,datbits,3);

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
				mask=3;
				regtemp=(regval>>6)&mask;
				datbits = pParent->int2bin_anybits(regtemp,2);
				pParent->dataupdate_anybits(0x05,0,datbits,2);
				mask=31;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,5);
				pParent->dataupdate_anybits(0x05,3,datbits,5);
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
				pParent->wreg(0x06,regval);
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
				pParent->wreg(0x07,regval);
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
				mask=63;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,6);
				pParent->dataupdate_anybits(0x08,2,datbits,6);
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
				mask=1;
				regtemp=(regval>>7)&mask;
				datbits = pParent->int2bin_anybits(regtemp,1);
				pParent->dataupdate_anybits(0x09,0,datbits,1);
				mask=63;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,6);
				pParent->dataupdate_anybits(0x09,2,datbits,6);
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
				pParent->wreg(0x0a,regval);
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
			    mask=127;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,7);
				pParent->dataupdate_anybits(0x0b,1,datbits,7);						
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
				pParent->wreg(0x0c,regval);
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
					pParent->wreg(0x0d,regval);
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
				mask=127;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,7);
				pParent->dataupdate_anybits(0x0e,1,datbits,7);		
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
				pParent->wreg(0x0f,regval);
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
				mask=63;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,6);
				pParent->dataupdate_anybits(0x10,2,datbits,6);	
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
				mask=63;
				regtemp=regval&mask;
				datbits = pParent->int2bin_anybits(regtemp,6);
				pParent->dataupdate_anybits(0x11,2,datbits,6);	
							
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
				pParent->wreg(0x12,regval);
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
				mask=63;
				regtemp=(regval>>1)&mask;
				datbits = pParent->int2bin_anybits(regtemp,6);
				pParent->dataupdate_anybits(0x13,1,datbits,6);	
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
				pParent->wreg(0x15,regval);
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
				pParent->wreg(0x18,regval);
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
				pParent->wreg(0x1b,regval);
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
				pParent->wreg(0x1c,regval);
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
				pParent->wreg(0x1d,regval);
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
				pParent->wreg(0x1e,regval);
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
				pParent->wreg(0x1f,regval);
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
				pParent->wreg(0x20,regval);
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
				pParent->wreg(0x22,regval);
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
				pParent->wreg(0x23,regval);
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
				pParent->wreg(0x24,regval);
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
				pParent->wreg(0x25,regval);
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
				pParent->wreg(0x26,regval);
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
				pParent->wreg(0x27,regval);
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
				pParent->wreg(0x28,regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg29h") == 0 )
		{
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				RegEnd=1;
				pParent->wreg(0x29,regval);
			}
			else
			{
				RegEnd=1;
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "*") == 0 )
		{
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


//read and check OTP1 register
void COTPDlg::readotp1reg()
{
	FILE *fpi;
	int regval,regtemp,mask,otpreg,otpregmask,use_reg_en,otp_cal_reg,regvalmask;
	int pwm_reg_sel,pwmin_sel,ad_tor_en;
	CString errmsg;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0,temp;
	int RegEnd=0;
	CString str,use_reg,usereg_temp,otpcal_temp,pwm_reg_sel_temp,pwmin_sel_temp,ad_tor_en_temp, otp_cal,datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

    use_reg_en=pParent->dataread_anybits(0x02,6,1); //use_reg
	usereg_temp=pParent->int2bin_anybits(use_reg_en,1);
	use_reg="0";
	pParent->dataupdate_anybits(0x02,6,use_reg,1); //use_reg=0

    otp_cal_reg=pParent->dataread_anybits(0x01,7,1); //otp_cal_sel
	otpcal_temp=pParent->int2bin_anybits(otp_cal_reg,1);
	otp_cal="0";
	pParent->dataupdate_anybits(0x01,7,otp_cal,1); //otp_cal_sel=0

	pwm_reg_sel=pParent->dataread_anybits(0x02,1,1); //pwm_reg_sel
	pwm_reg_sel_temp=pParent->int2bin_anybits(pwm_reg_sel,1);
	pwmin_sel=pParent->dataread_anybits(0x0a,0,1); //pwmin_sel
	pwmin_sel_temp=pParent->int2bin_anybits(pwmin_sel,1);
	datbits="1";
	pParent->dataupdate_anybits(0x02,1,datbits,1); //pwm_reg_sel=1

	ad_tor_en=pParent->dataread_anybits(0x01,4,1); //ad_tor_en
	ad_tor_en_temp=pParent->int2bin_anybits(ad_tor_en,1);
	pParent->dataupdate_anybits(0x01,4,datbits,1); //ad_tor_en=1

	const TCHAR* fpi_name = L"burn_otp1_file.txt";
	
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	}

	    while (i != EOF){
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
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				pParent->wreg(0x18,0x0);
				otpreg=pParent->rreg(0x03);
				mask=3;
				otpregmask=(otpreg>>3)&mask;
				regvalmask=(regval>>1)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				pParent->wreg(0x18,0x0);
				otpreg=pParent->rreg(0x03);
				mask=7;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>5)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				pParent->wreg(0x18,0x20);
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=regval&31;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}

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
				mask=115;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x04);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				mask=223;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x05);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x06);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x07);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=63;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x08);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				mask=191;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x09);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x0a);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=127;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x0b);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				otpreg=pParent->rreg(0x0c);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x0d);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=127;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x0e);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
                       goto burn_failure;
				}
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
			   otpreg=pParent->rreg(0x0f);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=63;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x10);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				mask=63;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x11);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				otpreg=pParent->rreg(0x12);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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

	            pParent->wreg(0x18,0x60);//D
				otpreg=pParent->rreg(0x03);
				mask=1;
				otpregmask=(otpreg>>4)&mask;
				regvalmask=(regval>>1)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x40);//C
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>2)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				
				pParent->wreg(0x18,0x80);//E
				otpreg=pParent->rreg(0x03);
				mask=15;
				otpregmask=(otpreg>>1)&mask;
				regvalmask=regval&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x60);//D
				otpreg=pParent->rreg(0x03);
				mask=15;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>4)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				pParent->wreg(0x18,0xc0);//G
				otpreg=pParent->rreg(0x03);
				mask=3;
				otpregmask=(otpreg>>3)&mask;
				regvalmask=regval&3;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0xa0);//F
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>2)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x80);//E
				otpreg=pParent->rreg(0x03);
				mask=1;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>7)&mask;
				if(otpregmask!=regvalmask){
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
				pParent->wreg(0x18,0xe0);//H
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=regval&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0xc0);//G
				otpreg=pParent->rreg(0x03);
				mask=7;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>5)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1c);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1d);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1e);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1f);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x20);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x22);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x23);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x24);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x25);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x26);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x27);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x28);
				if(otpreg!=regval){
                       goto burn_failure;
				}
			}
			else
			{
				goto unknown_format;
			}  
		}
			else if (_stricmp(command, "Reg29h") == 0 )
			{
				fscanf_s(fpi, "%x", &regval);
				if ((regval >= 0x00) && (regval <= 0xff))
				{
									RegEnd=1;
					otpreg=pParent->rreg(0x29);
					if(otpreg!=regval){
						   goto burn_failure;
					}
				}
				else
				{
					goto unknown_format;
				}  
			}

			else if (_stricmp(command, "*") == 0 )
			{
			}


		};
				m_CHECK_PASS1.SetCheck(1);
				pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Burn Process Pass!");
				temp=pParent->dataread_anybits(0x1a,2,1);
				if (!success){goto end;};

				if(temp==0){
					m_CHECK_OTP1DONE.SetCheck(0);
				}else{
					m_CHECK_OTP1DONE.SetCheck(1);
				}
				goto end;
				
			
				burn_failure:;
				m_CHECK_FAIL1.SetCheck(1);
				temp=pParent->dataread_anybits(0x1a,2,1);
				if (!success){goto end;};

				if(temp==0){
					m_CHECK_OTP1DONE.SetCheck(0);
				}else{
					m_CHECK_OTP1DONE.SetCheck(1);
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
	pParent->dataupdate_anybits(0x0a,0,pwmin_sel_temp,1);//pwmin_sel
	pParent->dataupdate_anybits(0x02,1,pwm_reg_sel_temp,1);//pwm_reg_sel
	pParent->dataupdate_anybits(0x01,4,ad_tor_en_temp,1);//ad_tor_en
	fclose(fpi);

	end_error:;
}



void COTPDlg::OnBnClickedButtonSaveFileOtpcal()
{
    int dat = 0,dat2=0,dat3=0;
	int datr = 0;
	int length_dat;
	int mask,mask2,mask3, seln;
	CString datw;
	CString datbits;

	char command[1000];
	int regval,query;
	int wordcnt=0;
	int i=0;
	CString str;
	CString errmsg;
	FILE *fpi;
    FILE *fbo;
	errno_t err;
		int RegEnd=0;
	CString FileStr;
	const TCHAR* fbo_name = L"backup_burn_otp1_file.txt";
	const TCHAR* fpi_name = L"burn_otp1_file.txt";

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	if(edit_otp==0){
		edit_otp=1;
		m_EDIT_TORA.EnableWindow(1);
		m_EDIT_TORB.EnableWindow(1);
		m_EDIT_TORC.EnableWindow(1);
		m_EDIT_TORD.EnableWindow(1);
		m_EDIT_TORE.EnableWindow(1);
		m_EDIT_TORF.EnableWindow(1);
		m_EDIT_TORG.EnableWindow(1);
		m_EDIT_TORH.EnableWindow(1);
		displaytorque();
		m_BUTTON_SAVE_FILE_OTPCAL.SetWindowText(_T("SAVE burn_otp1_file.txt"));

	}
	else
	{
		edit_otp=0;
		
        m_EDIT_TORA.EnableWindow(0);
		m_EDIT_TORB.EnableWindow(0);
		m_EDIT_TORC.EnableWindow(0);
		m_EDIT_TORD.EnableWindow(0);
		m_EDIT_TORE.EnableWindow(0);
		m_EDIT_TORF.EnableWindow(0);
		m_EDIT_TORG.EnableWindow(0);
		m_EDIT_TORH.EnableWindow(0);

		m_BUTTON_SAVE_FILE_OTPCAL.SetWindowText(_T("EDIT burn_otp1_file.txt"));

		query=pParent->DisplayQueryMessageBox((LPCWSTR)L"Query", (LPCWSTR)L"Comfirm TORQUE setting and save file?");
			if(query == IDCANCEL)
			{
				//release MessageBox if otp dialog is closed.
				if (pParent->otpdlg==NULL)
					return;

				displaytorque();
				goto end_error;
			}
			else if(query == IDOK)
			{
				//release MessageBox if otp dialog is closed.
				if (pParent->otpdlg==NULL)
					return;


                _wfopen_s(&fbo, fbo_name, _T("w"));
	    
			    fclose(fbo);

			    CopyFileW(fpi_name, fbo_name, false); //back up current save file
					
				if (err = _wfopen_s(&fpi, fpi_name, _T("w"))!=0)
				{
					pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
					goto end_error;
				};

				if (err = _wfopen_s(&fbo, fbo_name, _T("r"))!=0)
				{
					pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
					goto end_error;
				};


	    while (i != EOF)
		{
			regval = 0xffff;
			i = fscanf_s(fbo, "%s", command, 1000);
			if(i == EOF) 
			{
				if(RegEnd==1)
				{
					//write ad_tor successfully, write * at the end of file everytime
					fprintf( fpi, "%s\n", "*");

					break;
				}
				else
				{
					goto unknown_format; 
				}
			}
			wordcnt++;

		if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				m_EDIT_TORA.GetWindowText(datw);
				length_dat = m_EDIT_TORA.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=3;
				seln=(regval&0xf9)+(((dat>>3)&mask)<<1);
				fprintf( fpi, "Reg01h %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                m_EDIT_TORA.GetWindowText(datw);
				length_dat = m_EDIT_TORA.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=7;
				seln=(regval&0x1f)+((dat&mask)<<5);
				fprintf( fpi, "Reg02h %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                m_EDIT_TORB.GetWindowText(datw);
				length_dat = m_EDIT_TORB.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=31;
				seln=(regval&0xe0)+(dat&mask);
				fprintf( fpi, "Reg03h %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg04h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg05h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg06h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg07h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg08h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg09h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg0Ah %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{		
                fprintf( fpi, "Reg0Bh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg0Ch %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg0Dh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg0Eh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
               fprintf( fpi, "Reg0Fh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg10h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg11h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg12h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                m_EDIT_TORC.GetWindowText(datw);
				length_dat = m_EDIT_TORC.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=31;
				m_EDIT_TORD.GetWindowText(datw);
				length_dat = m_EDIT_TORD.LineLength();
				if (length_dat == 0){goto end;};
				dat2 = use_debugdlg_otp.string2int(datw, length_dat);
				mask2=1;
				seln=(regval&0x81)+((dat&mask)<<2)+(((dat2>>4)&mask2)<<1);
				fprintf( fpi, "Reg13h %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg14h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                m_EDIT_TORD.GetWindowText(datw);
				length_dat = m_EDIT_TORD.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=15;
				m_EDIT_TORE.GetWindowText(datw);
				length_dat = m_EDIT_TORE.LineLength();
				if (length_dat == 0){goto end;};
				dat2 = use_debugdlg_otp.string2int(datw, length_dat);
				mask2=15;
				seln=((dat&mask)<<4)+((dat2>>1)&mask2);
				fprintf( fpi, "Reg15h %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{ 
                m_EDIT_TORE.GetWindowText(datw);
				length_dat = m_EDIT_TORE.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=1;
				m_EDIT_TORF.GetWindowText(datw);
				length_dat = m_EDIT_TORF.LineLength();
				if (length_dat == 0){goto end;};
				dat2 = use_debugdlg_otp.string2int(datw, length_dat);
				mask2=31;
				m_EDIT_TORG.GetWindowText(datw);
				length_dat = m_EDIT_TORG.LineLength();
				if (length_dat == 0){goto end;};
				dat3 = use_debugdlg_otp.string2int(datw, length_dat);
				mask3=3;
				seln=((dat&mask)<<7)+((dat2&mask2)<<2)+((dat3>>3)&mask3);
				fprintf( fpi, "Reg18h %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                m_EDIT_TORG.GetWindowText(datw);
				length_dat = m_EDIT_TORG.LineLength();
				if (length_dat == 0){goto end;};
				dat = use_debugdlg_otp.string2int(datw, length_dat);
				mask=7;
				m_EDIT_TORH.GetWindowText(datw);
				length_dat = m_EDIT_TORH.LineLength();
				if (length_dat == 0){goto end;};
				dat2 = use_debugdlg_otp.string2int(datw, length_dat);
				mask2=31;
				seln=((dat&mask)<<5)+(dat2&mask2);
				fprintf( fpi, "Reg1Bh %x\n", seln);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg1Ch %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg1Dh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg1Eh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg1Fh %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg20h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg22h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg22h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg23h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg23h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg24h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
               fprintf( fpi, "Reg24h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg25h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg25h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg26h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg26h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg27h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg27h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg28h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
                fprintf( fpi, "Reg28h %x\n", regval);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg29h") == 0 ){
			fscanf_s(fbo, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				RegEnd=1;

                fprintf( fpi, "Reg29h %x\n", regval);

			}
			else
			{

				goto unknown_format;
			}
		}
		else if (_stricmp(command, "*") == 0 )
		{
		}

		else
		{
			unknown_format:;
			errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
			};
	 };//end while
	 };//confirm tor idok


	end:;
	fclose(fpi);
	fclose(fbo);
end_error:;

	};//end edit
				
	
}


void COTPDlg::OnCbnDropdownComboTora()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORA.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORA.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORA.ResetContent();
	m_COMBO_TORA.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, tora[4-i]);
			m_COMBO_TORA.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTorb()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORB.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORB.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORB.ResetContent();
	m_COMBO_TORB.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, torb[4-i]);
			m_COMBO_TORB.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTorc()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORC.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORC.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORC.ResetContent();
	m_COMBO_TORC.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, torc[4-i]);
			m_COMBO_TORC.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTord()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORD.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORD.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORD.ResetContent();
	m_COMBO_TORD.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, tord[4-i]);
			m_COMBO_TORD.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTore()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORE.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORE.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORE.ResetContent();
	m_COMBO_TORE.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, tore[4-i]);
			m_COMBO_TORE.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTorf()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORF.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORF.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORF.ResetContent();
	m_COMBO_TORF.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, torf[4-i]);
			m_COMBO_TORF.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTorg()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORG.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORG.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORG.ResetContent();
	m_COMBO_TORG.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, torg[4-i]);
			m_COMBO_TORG.AddString(str);
	}
end:;
}

void COTPDlg::OnCbnDropdownComboTorh()
{
	int i;
	int datr = 0;
	int datr_bit = 0;
	int length_dat;
	CString datw;
	CString str;

	// read user inputs
	m_EDIT_TORH.GetWindowText(datw);
	// get the string length of the inputs
	length_dat = m_EDIT_TORH.LineLength();
	if (length_dat == 0){goto end;};
	// convert input string into integer
	datr = use_debugdlg_otp.string2int(datw, length_dat);

	// display data per bit
	m_COMBO_TORH.ResetContent();
	m_COMBO_TORH.SetDroppedWidth(COMBOWIDTH_OTP);
	for (i=0;i<5;i++)
	{
			datr_bit = (datr>>(4-i)) & 0x01;
			str.Format(_T("%x: %s"), datr_bit, torh[4-i]);
			m_COMBO_TORH.AddString(str);
	}
end:;
}



void COTPDlg::OnBnClickedButtonFileload()
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

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	int length=0;

	length = m_COMBO_TORQUE_FILELOAD.GetWindowTextLengthW();
	if (length == 0) 
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Specified.");
		goto end_error;
	}
	else 
		m_COMBO_TORQUE_FILELOAD.GetWindowText(FileStr);

	const TCHAR* fpi_name = (LPCTSTR)FileStr;

	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	};

	while (i != EOF){
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

		if (_stricmp(command, "AD_TORQUE_A") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORA.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_B") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORB.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_C") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORC.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_D") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORD.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_E") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORE.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_F") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORF.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_G") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORG.SetWindowText(str);
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "AD_TORQUE_H") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0x1f))
			{
				str.Format(_T("%x"), regval);
				m_EDIT_TORH.SetWindowText(str);
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

void COTPDlg::OnBnClickedButtonFilesave()
{
	FILE *fpo;
	FILE *fbo;
	errno_t err;
	CString str;

	CString FileStr;
	const TCHAR* fpo_name2 = L"ad_torque_backupfile.txt";
	LPTSTR p;

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	int length=0;

	length = m_COMBO_TORQUE_FILESAVE.GetWindowTextLengthW();
	if (length == 0) 
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Specified.");
		goto end_error;
	}
	else 
		m_COMBO_TORQUE_FILESAVE.GetWindowText(FileStr);
    
	if (FileStr == "ad_torque_backupfile.txt")
    {
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Filename is Default Backup File Name.\n Please choose another name.");
		goto end_error;
	};

	const TCHAR* fpo_name = (LPCTSTR)FileStr;
	
	_wfopen_s(&fbo, fpo_name2, _T("w"));
	    
	fclose(fbo);

	CopyFileW(fpo_name, fpo_name2, false); //back up current save file
 
    if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
		goto end_error;
	};

	m_EDIT_TORA.GetWindowText(str);
	m_EDIT_FILETORA.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORA.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_A %s%s\n", p, p+1); 
	m_EDIT_FILETORA.ReleaseBuffer();

	m_EDIT_TORB.GetWindowText(str);
	m_EDIT_FILETORB.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORB.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_B %s%s\n", p, p+1); 
	m_EDIT_FILETORB.ReleaseBuffer();

	m_EDIT_TORC.GetWindowText(str);
	m_EDIT_FILETORC.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORC.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_C %s%s\n", p, p+1); 
	m_EDIT_FILETORC.ReleaseBuffer();

	m_EDIT_TORD.GetWindowText(str);
	m_EDIT_FILETORD.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORD.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_D %s%s\n", p, p+1); 
	m_EDIT_FILETORD.ReleaseBuffer();

	m_EDIT_TORE.GetWindowText(str);
	m_EDIT_FILETORE.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORE.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_E %s%s\n", p, p+1); 
	m_EDIT_FILETORE.ReleaseBuffer();

	m_EDIT_TORF.GetWindowText(str);
	m_EDIT_FILETORF.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORF.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_F %s%s\n", p, p+1); 
	m_EDIT_FILETORF.ReleaseBuffer();

	m_EDIT_TORG.GetWindowText(str);
	m_EDIT_FILETORG.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORG.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_G %s%s\n", p, p+1); 
	m_EDIT_FILETORG.ReleaseBuffer();

	m_EDIT_TORH.GetWindowText(str);
	m_EDIT_FILETORH.Format(str);
	UpdateData(FALSE);
	p = m_EDIT_FILETORH.GetBuffer(1024);
	fprintf( fpo, "AD_TORQUE_H %s%s\n", p, p+1); 
	m_EDIT_FILETORH.ReleaseBuffer();

	fclose(fpo);
	end_error:;
}

void COTPDlg::displaytorque()
{
	int dat = 0,dat2=0,dat3=0;
	int datr = 0;
	int length_dat;
	int mask,mask2,mask3,seln;
	CString datw;
	CString datbits;

	char command[1000];
	int regval;
	int wordcnt=0;
	int i=0;
	CString str;
	CString errmsg;
	FILE *fpi;
	errno_t err;
	int RegEnd=0;
	int fAdTor=0;

	CString FileStr;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

		//clear torque content
	m_EDIT_TORA.SetWindowTextW(L" ");
	m_EDIT_TORB.SetWindowTextW(L" ");
	m_EDIT_TORC.SetWindowTextW(L" ");
	m_EDIT_TORD.SetWindowTextW(L" ");
	m_EDIT_TORE.SetWindowTextW(L" ");
	m_EDIT_TORF.SetWindowTextW(L" ");
	m_EDIT_TORG.SetWindowTextW(L" ");
	m_EDIT_TORH.SetWindowTextW(L" ");


	const TCHAR* fpi_name = L"burn_otp1_file.txt";
 
					
				if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
			{
				pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
				goto end_error;
			};


	    while (i != EOF){
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
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				mask=3;
				dat=(regval>>1)&mask;
							
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
                mask2=7;
				dat2=(regval>>5)&mask2;
				seln=(dat<<3)+dat2;
				str.Format(_T("%x"), seln);
				m_EDIT_TORA.SetWindowText(str);

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
                mask=31;
				seln=regval&mask;
				str.Format(_T("%x"), seln);
				m_EDIT_TORB.SetWindowText(str);
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
                mask=31;
				seln=(regval>>2)&mask;
				str.Format(_T("%x"), seln);
				m_EDIT_TORC.SetWindowText(str);

				mask=1;
				dat=(regval>>1)&mask;
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
                mask2=15;
				dat2=(regval>>4)&mask2;
				seln=(dat<<4)+dat2;
				str.Format(_T("%x"), seln);
				m_EDIT_TORD.SetWindowText(str);

				mask=15;
				dat=regval&mask;
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
                mask2=1;
				dat2=(regval>>7)&mask2;
                seln=(dat<<1)+dat2;
				str.Format(_T("%x"), seln);
				m_EDIT_TORE.SetWindowText(str);

				mask=31;
				seln=(regval>>2)&mask;
				str.Format(_T("%x"), seln);
				m_EDIT_TORF.SetWindowText(str);

				mask=3;
				dat=regval&mask;
				
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
                mask2=7;
				dat2=(regval>>5)&mask2;
                seln=(dat<<3)+dat2;
				str.Format(_T("%x"), seln);
				m_EDIT_TORG.SetWindowText(str);

				mask=31;
				seln=regval&mask;
				str.Format(_T("%x"), seln);
				m_EDIT_TORH.SetWindowText(str);
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
               RegEnd=1;
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "*") == 0 )
		{
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

void COTPDlg::OnCbnDropdownComboTorqueFileload()
{
	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_TORQUE_FILELOAD, 0, DDL_READWRITE);
}

void COTPDlg::OnCbnDropdownComboTorqueFilesave()
{
	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_TORQUE_FILESAVE, 0, DDL_READWRITE);
}


void COTPDlg::OnCbnSelchangeComboMarginRdEn()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_MARGIN_RD_EN.GetCurSel();
	datbits = pParent->int2bin_anybits(seln,1);
	pParent->dataupdate_anybits(0x14,2,datbits,1);
}


void COTPDlg::OnDropdownComboCheckotp1file()
{
	TCHAR szDrive[MAX_PATH] = _T("C:\\*.*");
	::GetCurrentDirectory(MAX_PATH, szDrive);
	DlgDirListComboBox(szDrive, IDC_COMBO_CheckOTP1File, 0, DDL_READWRITE);
}


void COTPDlg::OnBnClickedButtonCheckotp1file()
{
	FILE *fpi;
	int regval,regtemp,mask,otpreg,otpregmask,use_reg_en,otp_cal_reg,regvalmask;
	CString errmsg;
	errno_t err;
	char command[1000];
	int wordcnt=0;
	int i=0,temp;
	CString str,use_reg,usereg_temp,otpcal_temp,otp_cal,datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
    use_reg_en=pParent->dataread_anybits(0x02,6,1); //use_reg
	usereg_temp=pParent->int2bin_anybits(use_reg_en,1);
	use_reg="0";
	pParent->dataupdate_anybits(0x02,6,use_reg,1); //use_reg=0

    otp_cal_reg=pParent->dataread_anybits(0x01,7,1); //otp_cal_sel
	otpcal_temp=pParent->int2bin_anybits(otp_cal_reg,1);
	otp_cal="0";
	pParent->dataupdate_anybits(0x01,7,otp_cal,1); //otp_cal_sel=0

	datbits="1";
	pParent->dataupdate_anybits(0x02,1,datbits,1); //pwm_reg_sel=1
	pParent->dataupdate_anybits(0x01,4,datbits,1); //ad_tor_en=1

	//get original OTP1 file name to compare with the burned OTP1 bits
	CString FileStr;
	int length=0;

	length = m_COMBO_CheckOTP1File.GetWindowTextLengthW();
	if (length == 0) 
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Specified.");
		goto end_error;
	}
	else 
		m_COMBO_CheckOTP1File.GetWindowText(FileStr);

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
				pParent->wreg(0x18,0x03);
				otpreg=pParent->rreg(0x03);
				mask=3;
				otpregmask=(otpreg>>3)&mask;
				regvalmask=(regval>>1)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				pParent->wreg(0x18,0x03);
				otpreg=pParent->rreg(0x03);
				mask=7;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>5)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				pParent->wreg(0x18,0x07);
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=regval&31;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}

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
				mask=115;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x04);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				mask=223;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x05);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x06);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x07);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=63;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x08);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				mask=191;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x09);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x0a);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=127;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x0b);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				otpreg=pParent->rreg(0x0c);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x0d);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=127;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x0e);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
                       goto burn_failure;
				}
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
			   otpreg=pParent->rreg(0x0f);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				mask=63;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x10);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				mask=63;
				regtemp=regval&mask;
				otpreg=pParent->rreg(0x11);
				otpregmask=otpreg&mask;
				if(otpregmask!=regtemp){
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
				otpreg=pParent->rreg(0x12);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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

	            pParent->wreg(0x18,0x0f);
				otpreg=pParent->rreg(0x03);
				mask=1;
				otpregmask=(otpreg>>4)&mask;
				regvalmask=(regval>>1)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x0b);
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>2)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				
				pParent->wreg(0x18,0x13);
				otpreg=pParent->rreg(0x03);
				mask=15;
				otpregmask=(otpreg>>1)&mask;
				regvalmask=regval&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x0f);
				otpreg=pParent->rreg(0x03);
				mask=15;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>4)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				pParent->wreg(0x18,0x1b);
				otpreg=pParent->rreg(0x03);
				mask=3;
				otpregmask=(otpreg>>3)&mask;
				regvalmask=regval&3;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x17);
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>2)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x13);
				otpreg=pParent->rreg(0x03);
				mask=1;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>7)&mask;
				if(otpregmask!=regvalmask){
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
				pParent->wreg(0x18,0x1f);
				otpreg=pParent->rreg(0x03);
				mask=31;
				otpregmask=otpreg&mask;
				regvalmask=regval&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
				pParent->wreg(0x18,0x1b);
				otpreg=pParent->rreg(0x03);
				mask=7;
				otpregmask=otpreg&mask;
				regvalmask=(regval>>5)&mask;
				if(otpregmask!=regvalmask){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1c);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1d);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1e);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x1f);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x20);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x22);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x23);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x24);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x25);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x26);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x27);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x28);
				if(otpreg!=regval){
                       goto burn_failure;
				}
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
				otpreg=pParent->rreg(0x29);
				if(otpreg!=regval){
                       goto burn_failure;
				}
			}
			else
			{
				goto unknown_format;
			}  
		}
		};
				
				pParent->DisplayInforMessageBox((LPCWSTR)L"Information", (LPCWSTR)L"Checking OTP1 Burning File Pass!");
				goto end;

				burn_failure:;
				errmsg.Format(_T("Checking OTP1 Burning File Failure.\nPlease check the file and burn again!"));
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

BOOL COTPDlg::checkotp1file()
{
    FILE *fpi;
	BOOL check=FALSE;
	//CString errmsg,dat;
	errno_t err;
	char command[1000];
	int i=0;

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	const TCHAR* fpi_name = L"burn_otp1_file.txt";
	
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		return FALSE;
	}

	while (i != EOF)
	{
		i = fscanf_s(fpi, "%s", command, 1000);
		if(i == EOF) 
			break;
  
		else if (_stricmp(command, "*") == 0 )
		{
			check = TRUE;
		}
	};
			

	fclose(fpi);

	return check;
	
}