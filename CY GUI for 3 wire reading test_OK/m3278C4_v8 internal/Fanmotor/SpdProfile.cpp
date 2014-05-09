// SpdProfile.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "SpdProfile.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"
//#include "FanmotorDlg.cpp"

#include <string.h>
#include "conio.h"
#include <stdlib.h>
#include <ctype.h>
#include "math.h"
#include "ni488.h"
#include "Decl-32.h"
// CSpdProfile dialog


int nStep_SP=-1, nSettleTime=-1;
int nMaxDac,nMinDac;
double fStep_SP,fMaxDac,fMinDac;
static BOOL SelTacho = FALSE;
static BOOL SelFinalDac = FALSE;
static BOOL SelCurrent = FALSE;
static BOOL SelDAC = FALSE;
static BOOL SelDACB2B = FALSE;
static BOOL SelFinalDacB2B = FALSE;
static BOOL SelVolt = FALSE;

int DMM;
int FuncGen;
FILE *fpo;
int TachoLen = 2;
int fTacho=0xff;

int FinalDacB2BDone=0;

extern double duty_cycle1;
extern int duty_cycle2;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  IDT_TIMER  WM_USER + 200 



IMPLEMENT_DYNAMIC(CSpdProfile, CDialogEx)

CSpdProfile::CSpdProfile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpdProfile::IDD, pParent)
	, m_RADIO_Inc_Dec(0)
	, m_PWM_SEL_MODE(0)
{
      m_pParent=pParent;
}

CSpdProfile::~CSpdProfile()
{
}

void CSpdProfile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_Inc, m_RADIO_Inc_Dec);
	DDX_Control(pDX, IDC_EDIT_Step, m_EDIT_Step);
	DDX_Control(pDX, IDC_EDIT_SettleTime, m_EDIT_SettleTime);
	DDX_Control(pDX, IDC_EDIT_MaxDac, m_EDIT_MaxDac);
	DDX_Control(pDX, IDC_CHECK_Tacho, m_CHECK_Tacho);
	DDX_Control(pDX, IDC_CHECK_FinalDac, m_CHECK_FinalDac);
	DDX_Control(pDX, IDC_CHECK_Current, m_CHECK_Current);
	DDX_Radio(pDX, IDC_RADIO_PWM_REG, m_PWM_SEL_MODE);
	DDX_Control(pDX, IDC_EDIT_MinDac, m_EDIT_MinDac);
	DDX_Control(pDX, IDC_CHECK_Dac, m_CHECK_Dac);
	DDX_Control(pDX, IDC_CHECK_DAC_B2B, m_CHECK_DAC_B2B);
	DDX_Control(pDX, IDC_CHECK_FinalDac_B2B, m_CHECK_FinalDac_B2B);
	DDX_Control(pDX, IDC_CHECK_Volt, m_CHECK_Volt);
	DDX_Control(pDX, IDC_CHECK_StopFan, m_CHECK_StopFan);
}


BEGIN_MESSAGE_MAP(CSpdProfile, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_Measure, &CSpdProfile::OnBnClickedButtonMeasure)
	ON_BN_CLICKED(IDC_RADIO_Inc, &CSpdProfile::OnBnClickedRadioInc)
	ON_BN_CLICKED(IDC_RADIO_Dec, &CSpdProfile::OnBnClickedRadioDec)
	ON_BN_CLICKED(IDC_CHECK_Tacho, &CSpdProfile::OnBnClickedCheckTacho)
	ON_BN_CLICKED(IDC_CHECK_FinalDac, &CSpdProfile::OnBnClickedCheckFinaldac)
	ON_BN_CLICKED(IDC_CHECK_Current, &CSpdProfile::OnBnClickedCheckCurrent)
	ON_BN_CLICKED(IDC_RADIO_PWM_REG, &CSpdProfile::OnBnClickedRadioPwmReg)
	ON_BN_CLICKED(IDC_RADIO_PWM_IN, &CSpdProfile::OnBnClickedRadioPwmIn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_DAC_B2B, &CSpdProfile::OnBnClickedCheckDacB2b)
	ON_BN_CLICKED(IDC_RADIO_PWM_FuncGen, &CSpdProfile::OnBnClickedRadioPwmFuncgen)
END_MESSAGE_MAP()


// CSpdProfile message handlers


void CSpdProfile::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


void CSpdProfile::OnNcDestroy()
{
	CDialogEx::OnNcDestroy();

	// TODO: Add your message handler code here
}


BOOL CSpdProfile::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString datbits;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	// TODO:  Add extra initialization here
	m_CHECK_Tacho.SetCheck(FALSE);
	m_CHECK_Tacho.SetCheck(FALSE);
	m_CHECK_Tacho.SetCheck(FALSE);

	//set PWM_reg=1, pwmin_sel=0
	datbits = "1";
	pParentParent->dataupdate_anybits(0x02,1,datbits,1);
	datbits = "0";
	pParentParent->dataupdate_anybits(0x0a,0,datbits,1);

	//disable DAC 18h check box
	//m_CHECK_Dac.EnableWindow(0);
	//m_CHECK_DAC_B2B.EnableWindow(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSpdProfile::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialogEx::PostNcDestroy();
	((CIntTest*)m_pParent)->spdprofiledlg = NULL;
    delete this;
	
}


void CSpdProfile::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}


void CSpdProfile::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CSpdProfile::OnBnClickedButtonMeasure()
{
	// TODO: Add your control notification handler code here
	CString sStep,sSettleTime,datbits;
	int PWM_freq=20000;
	int ntemp;
	int TachoFreq = 0;
	int TachoLen = 2;
	int fTacho=0xff;
	int orig_pos_sns,restore_pos_sns;
	
	CString sMaxDac,sMinDac;

	errno_t err;
	const TCHAR* fpo_name = L"Speed Profile.xls";
	
	CString errmsg;
	char GPIBstr[256];
	

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//get input
	if (m_PWM_SEL_MODE == 0)
	{
		m_EDIT_Step.GetWindowText(sStep);
		if (m_EDIT_Step.LineLength()==0)
			return;
		nStep_SP = wcstod(sStep,NULL);
		if(nStep_SP <= 0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check DAC step input");
			return;
		}

		m_EDIT_MaxDac.GetWindowText(sMaxDac);
		if (m_EDIT_MaxDac.LineLength()==0)
			return;
		nMaxDac = wcstod(sMaxDac,NULL);
		if((nMaxDac < 0)|(nMaxDac > 255))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
			return;
		}

		m_EDIT_MinDac.GetWindowText(sMinDac);
		if (m_EDIT_MinDac.LineLength()==0)
			return;
		nMinDac = wcstod(sMinDac,NULL);
		if((nMinDac < 0)|(nMinDac > 255)|(nMinDac>nMaxDac))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
			return;
		}
	}

	else
	{
		m_EDIT_Step.GetWindowText(sStep);
		if (m_EDIT_Step.LineLength()==0) return;
		fStep_SP = _wtof(sStep);
		if(fStep_SP <= 0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check DAC step input");
			return;
		}
	
		m_EDIT_MaxDac.GetWindowText(sMaxDac);
		if (m_EDIT_MaxDac.LineLength()==0) return;
		fMaxDac = _wtof(sMaxDac);
		if((fMaxDac < 0)|(fMaxDac > 100))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
			return;
		}

		m_EDIT_MinDac.GetWindowText(sMinDac);
		if (m_EDIT_MinDac.LineLength()==0) return;
		fMinDac = _wtof(sMinDac);
		if((fMinDac < 0)|(fMinDac > 100)|(fMinDac>fMaxDac))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
			return;
		}
	}

	m_EDIT_SettleTime.GetWindowText(sSettleTime);
	if (m_EDIT_SettleTime.LineLength()==0)
		return;
	nSettleTime = wcstod(sSettleTime,NULL);
	if(nSettleTime < 0)
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Settle Time input");
		return;
	}

	SelTacho = m_CHECK_Tacho.GetCheck();
	SelFinalDac = m_CHECK_FinalDac.GetCheck();
	SelCurrent = m_CHECK_Current.GetCheck();
	SelDAC= m_CHECK_Dac.GetCheck();
	SelDACB2B = m_CHECK_DAC_B2B.GetCheck();
	SelVolt = m_CHECK_Volt.GetCheck();

	//GPIB DMM control
	if ((SelCurrent == TRUE)|(SelVolt == TRUE))
	{
		//open DMM GPIB control
		//ibclr(DMM);
		DMM = ibdev(0, 6, 0, 0, 1, 0);
		if (ibsta & ERR)
		{
		  errmsg.Format(_T("No DMM GPIB connection"));
		  pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
		  ibonl(DMM, 0);
		  return;
		}
	}

	//create xls file	
	if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
		fclose(fpo);
		return;
	};
	fprintf( fpo, "InputDAC\tDAC R18h\tFinalDac\tCurrent(mA)\tVoltage(V)\tTacho(Hz)\n");

	if (m_PWM_SEL_MODE != 2)
	{
		//save pos_sns
		orig_pos_sns = pParentParent->dataread_anybits(0x01,3,1);
	             if (!success){return;};
		//set pos_sns=0
		datbits = "0";
		pParentParent->dataupdate_anybits(0x01,3,datbits,1);

		//set fan_en=1
		datbits = "1";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1);
	}

	// start measurement
	if (m_PWM_SEL_MODE == 0)
		PWMRegMeasure();
	else if (m_PWM_SEL_MODE == 1)
		PWMInMeasure();
	else if (m_PWM_SEL_MODE == 2)
	{
		fStep_SP= (fStep_SP/100)/PWM_freq;//PWM_freq=20k.fStep_SP= (fStep_SP/100)/PWM_freq
		fMaxDac= (fMaxDac/100)/PWM_freq;
		fMinDac= (fMinDac/100)/PWM_freq;

		//init FuncGen
		FuncGen = ibdev(0, 15, 0, 10, 1, 0);
		if (ibsta & ERR)
		{
		  errmsg.Format(_T("No Function Generator GPIB connection"));
		  pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
		  ibonl(FuncGen, 0);
		  fclose(fpo);
		  return;
		}

		//generate PWM signal
		ibwrt(FuncGen, "APPL:PULS 20000, 3.3, 1.65", 26);//20kHz, ampl=3.3v, offset =1.65

		//start swift DAC
		PWMFGMeasure();
	}

	if (m_PWM_SEL_MODE != 2)
	{
		//restore pos_sns
		restore_pos_sns = pParentParent->rreg(0x01);
		restore_pos_sns |= (orig_pos_sns<<4);
		pParentParent->wreg(0x01,restore_pos_sns);

		////set fan_en=0
		//datbits = "0";
		//pParentParent->dataupdate_anybits(0x04,0,datbits,1);
		////set minimum speed
		//pParentParent->wreg(0x18,0);
	}

	//check stop fan
	if(m_CHECK_StopFan.GetCheck()==TRUE)
	{
		//set fan_en=0
		datbits = "0";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1);
	}

	ibonl(DMM, 0);
	ibonl(FuncGen, 0);
	fclose(fpo);
}


void CSpdProfile::OnBnClickedRadioInc()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Inc_Dec = 0;
}


void CSpdProfile::OnBnClickedRadioDec()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Inc_Dec = 1;
}


void CSpdProfile::OnBnClickedCheckTacho()
{
	// TODO: Add your control notification handler code here
	static BOOL check = FALSE;
	check = m_CHECK_Tacho.GetCheck();
}


void CSpdProfile::OnBnClickedCheckFinaldac()
{
}


void CSpdProfile::OnBnClickedCheckCurrent()
{

}


void CSpdProfile::OnBnClickedRadioPwmReg()
{
	// TODO: Add your control notification handler code here
	CString datbits;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	//set PWM_reg=1, pwmin_sel=0
	datbits = "1";
	pParentParent->dataupdate_anybits(0x02,1,datbits,1);
	datbits = "0";
	pParentParent->dataupdate_anybits(0x0a,0,datbits,1);


	m_CHECK_Dac.EnableWindow(1);
	m_CHECK_DAC_B2B.EnableWindow(1);

	m_CHECK_FinalDac.EnableWindow(1);
	m_CHECK_Current.EnableWindow(1);
	m_CHECK_Volt.EnableWindow(1);
	m_CHECK_Tacho.EnableWindow(1);

	m_PWM_SEL_MODE=0;
}


void CSpdProfile::OnBnClickedRadioPwmIn()
{
	// TODO: Add your control notification handler code here
	CString datbits;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	//set PWM_reg=0, pwmin_sel=1
	datbits = "0";
	pParentParent->dataupdate_anybits(0x02,1,datbits,1);
	datbits = "1";
	pParentParent->dataupdate_anybits(0x0a,0,datbits,1);

	//enable DAC 18h check box
	m_CHECK_Dac.EnableWindow(1);
	m_CHECK_DAC_B2B.EnableWindow(1);
	m_CHECK_FinalDac.EnableWindow(1);
	m_CHECK_Current.EnableWindow(1);
	m_CHECK_Volt.EnableWindow(1);
	m_CHECK_Tacho.EnableWindow(1);

	m_PWM_SEL_MODE=1;
}

void CSpdProfile::PWMRegMeasure()
{
	// TODO: Add your control notification handler code here
	int nDAC;
	int DAC;
	int TachoFreq = 0;
	int FDac1,FDac2,FDac;
	//CString errmsg;
	char GPIBstr[256];
	UINT TimerVal;
	DWORD startTime,endTime;
	int timeElasp = 0;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//Increasing Dac
	if (m_RADIO_Inc_Dec == 0)
	{
		//set dac = 0
		nDAC=nMinDac;
		
		while (nDAC<=nMaxDac)
		{
			pParentParent->wreg(0x18,nDAC);
			fprintf( fpo, "%d\t", nDAC);
			
			if (SelDACB2B == TRUE)
			{
				if((SelDAC == TRUE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\t", DAC);

						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == TRUE)&&(SelFinalDac == FALSE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\n\t", DAC);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == FALSE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				fprintf( fpo, "\t\t");
			}

			//no B2B readback
			else if (SelDACB2B == FALSE)
			{
				StartTimer(nSettleTime);

				//Sleep(nSettleTime);

				//read DAC r18h
				if(SelDAC == TRUE)
				{
					DAC= pParentParent->rreg(0x18);
					fprintf( fpo, "%d\t", DAC);
				}
				else
					fprintf( fpo, "\t");

				//read final dac
				if(SelFinalDac == TRUE)
				{
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDac = (FDac1<<8)+FDac2;
					fprintf( fpo, "%d\t", FDac);
				}
				else
					fprintf( fpo, "\t");
			}
					

			//GPIB meaure current
			if(SelCurrent == TRUE)
			{
				ibwrt(DMM,"MEAS:CURR:DC? 2, 0.001",22);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//GPIB meaure Volt
			if(SelVolt == TRUE)
			{
				ibwrt(DMM,"MEAS:VOLT:DC? 20, 0.001",23);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//tacho readback
			if (SelTacho == TRUE)
			{

				pParentParent->GetTachoFreq();
				TachoFreq = pParentParent->rFWData(fTacho,TachoLen);
				fprintf( fpo, "%d\t", TachoFreq);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			fprintf( fpo, "\n");

			nDAC+=nStep_SP;
		}
	}

	//Decreasing Dac
	else if (m_RADIO_Inc_Dec == 1)
	{
		//set dac = 255
		nDAC=nMaxDac;

		while (nDAC>=nMinDac)
		{
			pParentParent->wreg(0x18,nDAC);
			fprintf( fpo, "%d\t", nDAC);
			
			if (SelDACB2B == TRUE)
			{
				if((SelDAC == TRUE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\t", DAC);

						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == TRUE)&&(SelFinalDac == FALSE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\n\t", DAC);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == FALSE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				fprintf( fpo, "\t\t");
			}

			//no B2B readback
			else if (SelDACB2B == FALSE)
			{
				Sleep(nSettleTime);

				//read DAC r18h
				if(SelDAC == TRUE)
				{
					DAC= pParentParent->rreg(0x18);
					fprintf( fpo, "%d\t", DAC);
				}
				else
					fprintf( fpo, "\t");

				//read final dac
				if(SelFinalDac == TRUE)
				{
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDac = (FDac1<<8)+FDac2;
					fprintf( fpo, "%d\t", FDac);
				}
				else
					fprintf( fpo, "\t");
			}

			//GPIB meaure current
			if(SelCurrent == TRUE)
			{			
				ibwrt(DMM,"MEAS:CURR:DC? 2, 0.001",22);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//GPIB meaure Volt
			if(SelVolt == TRUE)
			{
				ibwrt(DMM,"MEAS:VOLT:DC? 20, 0.001",23);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//tacho readback
			if (SelTacho == TRUE)
			{
				
				pParentParent->GetTachoFreq();
				TachoFreq = pParentParent->rFWData(fTacho,TachoLen);
				fprintf( fpo, "%d\t", TachoFreq);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			fprintf( fpo, "\n");

			nDAC-=nStep_SP;
		}
	}
}

void CSpdProfile::PWMInMeasure()
{
	double fDAC;
	int TachoFreq = 0;
	int FDac1,FDac2,FDac;
	//CString errmsg;
	char GPIBstr[256];
	UINT TimerVal;
	int pulse_width1;
	int DAC;
	//CFileTime startTime,endTime;
	////CString sTime;
	//CFileTimeSpan myFTS;
	DWORD startTime,endTime;
	int timeElasp = 0;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	//Increasing Dac
	if (m_RADIO_Inc_Dec == 0)
	{
		//set dac = 0
		fDAC=fMinDac;
		
		while (fDAC<=fMaxDac)
		{
			duty_cycle1 = fDAC;
			pulse_width1=(255*duty_cycle1)/100;
	    	pParentParent->setpowerPWM(pulse_width1);
			pParentParent->UpdatePWM1();

			fprintf( fpo, "%.2f\t", fDAC);
			
			//check B2B---------------------B2B not work. cannot goin ontimer() during while loop
			//solve 1: user key in loop #-X
			//solve 2: find each loop use how long, then based input time,calculate how may loop need.-X PC speed is different
			//solve 3: other method can avoid while loop.-use OS time to determine when to stop, still use while
			if (SelDACB2B == TRUE)
			{
				if((SelDAC == TRUE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\t", DAC);

						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == TRUE)&&(SelFinalDac == FALSE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\n\t", DAC);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == FALSE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				fprintf( fpo, "\t\t");
			}

			//no B2B readback
			else if (SelDACB2B == FALSE)
			{
				Sleep(nSettleTime);

				//read DAC r18h
				if(SelDAC == TRUE)
				{
					DAC= pParentParent->rreg(0x18);
					fprintf( fpo, "%d\t", DAC);
				}
				else
					fprintf( fpo, "\t");

				//read final dac
				if(SelFinalDac == TRUE)
				{
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDac = (FDac1<<8)+FDac2;
					fprintf( fpo, "%d\t", FDac);
				}
				else
					fprintf( fpo, "\t");
			}
					
			//GPIB meaure current
			if(SelCurrent == TRUE)
			{
				ibwrt(DMM,"MEAS:CURR:DC? 2, 0.001",22);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//GPIB meaure Volt
			if(SelVolt == TRUE)
			{
				ibwrt(DMM,"MEAS:VOLT:DC? 20, 0.001",23);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//tacho readback
			if (SelTacho == TRUE)
			{

				pParentParent->GetTachoFreq();
				TachoFreq = pParentParent->rFWData(fTacho,TachoLen);
				fprintf( fpo, "%d\t", TachoFreq);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			fprintf( fpo, "\n");

			fDAC+=fStep_SP;
		}
	}

	//Decreasing Dac
	else if (m_RADIO_Inc_Dec == 1)
	{
		//set dac = 255
		fDAC=fMaxDac;

		while (fDAC>=fMinDac)
		{
			duty_cycle1 = fDAC;
			pulse_width1=(255*duty_cycle1)/100;
	    	pParentParent->setpowerPWM(pulse_width1);
			pParentParent->UpdatePWM1();

			fprintf( fpo, "%.2f\t", fDAC);
			
			//check B2B
			if (SelDACB2B == TRUE)
			{
				if((SelDAC == TRUE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\t", DAC);

						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == TRUE)&&(SelFinalDac == FALSE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						DAC= pParentParent->rreg(0x18);
						fprintf( fpo, "%d\n\t", DAC);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				if((SelDAC == FALSE)&&(SelFinalDac == TRUE))
				{
					timeElasp = 0;
					startTime = GetTickCount();

					while (timeElasp<=nSettleTime)
					{
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDac = (FDac1<<8)+FDac2;
						fprintf( fpo, "%d\n\t", FDac);

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}

				fprintf( fpo, "\t\t");
			}

			else if (SelDACB2B == FALSE)
			{
				Sleep(nSettleTime);

				//read DAC r18h
				if(SelDAC == TRUE)
				{
					DAC= pParentParent->rreg(0x18);
					fprintf( fpo, "%d\t", DAC);
				}
				else
					fprintf( fpo, "\t");

				//read final dac
				if(SelFinalDac == TRUE)
				{
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDac = (FDac1<<8)+FDac2;
					fprintf( fpo, "%d\t", FDac);
				}
				else
					fprintf( fpo, "\t");
			}

			//GPIB meaure current
			if(SelCurrent == TRUE)
			{			
				ibwrt(DMM,"MEAS:CURR:DC? 2, 0.001",22);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//GPIB meaure Volt
			if(SelVolt == TRUE)
			{
				ibwrt(DMM,"MEAS:VOLT:DC? 20, 0.001",23);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//tacho readback
			if (SelTacho == TRUE)
			{
				
				pParentParent->GetTachoFreq();
				TachoFreq = pParentParent->rFWData(fTacho,TachoLen);
				fprintf( fpo, "%d\t", TachoFreq);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			fprintf( fpo, "\n");

			fDAC-=fStep_SP;
		}
	}
}

UINT CSpdProfile::StartTimer (int TimerDuration)
 
{
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
    UINT TimerVal;

    TimerVal = SetTimer (IDT_TIMER, TimerDuration, NULL);  // Starting the Timer
    if (TimerVal == 0)
    {
        pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to obtain timer.");
    }
    return TimerVal;
}

BOOL CSpdProfile::StopTimer (UINT TimerVal)
{
    if (!KillTimer (TimerVal))
    {
        return FALSE;
    }

    return TRUE;
} 

void CSpdProfile::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	BOOL stop;
	int DAC;
	int FDac1,FDac2,FDac;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//read DAC r18h
	if(SelDAC == TRUE)
	{
		DAC= pParentParent->rreg(0x18);
		fprintf( fpo, "%d\t", DAC);
	}
	else
		fprintf( fpo, "\t");

	//read final dac
	if(SelFinalDac == TRUE)
	{
		FDac1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success){return;};
		FDac2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success){return;};
		FDac = (FDac1<<8)+FDac2;
		fprintf( fpo, "%d\t", FDac);
	}
	else
		fprintf( fpo, "\t");


	//kill timer
	stop = StopTimer(IDT_TIMER);
	if (stop == FALSE)
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
	}			

	CDialogEx::OnTimer(nIDEvent);
}


void CSpdProfile::OnBnClickedCheckDacB2b()
{
	// TODO: Add your control notification handler code here
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	if(m_CHECK_DAC_B2B.GetCheck()==TRUE)
	{
		if((m_CHECK_Dac.GetCheck()==FALSE)&(m_CHECK_FinalDac.GetCheck()==FALSE))
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please select DAC R18h or Final Dac for B2B readback.");
		}
	}
}


void CSpdProfile::OnBnClickedRadioPwmFuncgen()
{
	// TODO: Add your control notification handler code here
	CString datbits;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//set PWM_reg=0, pwmin_sel=1
	datbits = "0";
	pParentParent->dataupdate_anybits(0x02,1,datbits,1);
	datbits = "1";
	pParentParent->dataupdate_anybits(0x0a,0,datbits,1);

	m_CHECK_Dac.EnableWindow(0);
	m_CHECK_DAC_B2B.EnableWindow(0);
	m_CHECK_FinalDac.EnableWindow(0);
	m_CHECK_Tacho.EnableWindow(0);
	
	m_CHECK_Current.EnableWindow(1);
	m_CHECK_Volt.EnableWindow(1);
	
	m_PWM_SEL_MODE=2;
}

void CSpdProfile::PWMFGMeasure()
{
	double fDAC;
	int TachoFreq = 0;
	int FDac1,FDac2,FDac;
	//CString errmsg;
	char GPIBstr[256];
	UINT TimerVal;
	char sFuncGen[100];
	int PWM_freq=20000;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//Increasing Dac
	if (m_RADIO_Inc_Dec == 0)
	{
		//set dac = 0
		fDAC=fMinDac;
		//InputDAC\tDAC R18h\tFinalDac\tCurrent(mA)\tVoltage(V)\tTacho(Hz)\n
		while (fDAC<=fMaxDac)
		{
			//pParentParent->wreg(0x18,fDAC);			
			sprintf(sFuncGen, "PULS:WIDT %.7f", fDAC);
			ibwrt(FuncGen, sFuncGen, 19);

			fprintf( fpo, "%f\t\t\t", fDAC*PWM_freq*100);//convert sec to %
			Sleep(nSettleTime);

			
			//GPIB meaure current
			if(SelCurrent == TRUE)
			{
				ibwrt(DMM,"MEAS:CURR:DC? 2, 0.001",22);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//GPIB meaure Volt
			if(SelVolt == TRUE)
			{
				ibwrt(DMM,"MEAS:VOLT:DC? 20, 0.001",23);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}
			

			fprintf( fpo, "\n");

			fDAC+=fStep_SP;
		}

		//force the last DAC
		sprintf(sFuncGen, "PULS:WIDT %.7f", fMaxDac);
		ibwrt(FuncGen, sFuncGen, 19);
		fprintf( fpo, "%f\t\t\t", fMaxDac*PWM_freq*100);//convert sec to %
	}
	

	//Decreasing Dac
	else if (m_RADIO_Inc_Dec == 1)
	{
		//set dac = 255
		fDAC=fMaxDac;

		while (fDAC>=fMinDac)
		{
			//pParentParent->wreg(0x18,fDAC);
			sprintf(sFuncGen, "PULS:WIDT %.7f", fDAC);
			ibwrt(FuncGen, sFuncGen, 19);

			fprintf( fpo, "%f\t\t\t", fDAC*PWM_freq*100);//convert sec to %
			Sleep(nSettleTime);

			
			//GPIB meaure current
			if(SelCurrent == TRUE)
			{
				ibwrt(DMM,"MEAS:CURR:DC? 2, 0.001",22);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}

			//GPIB meaure Volt
			if(SelVolt == TRUE)
			{
				ibwrt(DMM,"MEAS:VOLT:DC? 20, 0.001",23);
				ibrd(DMM,GPIBstr,ibcnt);
				fprintf( fpo, "%f\t", atof(GPIBstr));
				ibclr(DMM);
			}
			else
			{
				fprintf( fpo, "\t");
			}
			fprintf( fpo, "\n");

			fDAC-=fStep_SP;
		}

		sprintf(sFuncGen, "PULS:WIDT %.7f", fMinDac);
		ibwrt(FuncGen, sFuncGen, 19);
		fprintf( fpo, "%f\t\t\t", fMinDac*PWM_freq*100);//convert sec to %
	}
}
