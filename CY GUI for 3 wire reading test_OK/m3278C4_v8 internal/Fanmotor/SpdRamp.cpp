// SpdRamp.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "SpdRamp.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"

#include <string.h>
#include "conio.h"
#include <stdlib.h>
#include <ctype.h>
#include "math.h"
#include "ni488.h"
#include "Decl-32.h"

// CSpdRamp dialog
int nMaxDacRamp,nMinDacRamp, nLoopRamp, nSettleTimeRamp;
int nLoopTemp=0;
double fMaxDacRamp,fMinDacRamp;
extern int FuncGen;
int FWtorque_temp=-1, FWtorque_temp1=-1, FWtorA_coarse=-1, FWtorA_fine=-1, FWtorB_coarse=-1, FWtorB_fine=-1,FWtorC_coarse=-1, 
	FWtorC_fine=-1,FWtorD_coarse=-1, FWtorD_fine=-1,FWtorE_coarse=-1, FWtorE_fine=-1,FWtorF_coarse=-1, FWtorF_fine=-1,FWtorG_coarse=-1, FWtorG_fine=-1,FWtorH_coarse=-1, FWtorH_fine=-1;
CString sFWtorque_temp, sFWtorque_temp1, sFWtorA_coarse, sFWtorA_fine, sFWtorB_coarse, sFWtorB_fine,sFWtorC_coarse, sFWtorC_fine,sFWtorD_coarse, sFWtorD_fine,sFWtorE_coarse, sFWtorE_fine,sFWtorF_coarse, sFWtorF_fine,sFWtorG_coarse, sFWtorG_fine,sFWtorH_coarse, sFWtorH_fine;
BOOL statFWTorA=FALSE,statFWTorB=FALSE,statFWTorC=FALSE,statFWTorD=FALSE,statFWTorE=FALSE,statFWTorF=FALSE,statFWTorG=FALSE,statFWTorH=FALSE;

IMPLEMENT_DYNAMIC(CSpdRamp, CDialog)

CSpdRamp::CSpdRamp(CWnd* pParent /*=NULL*/)
	: CDialog(CSpdRamp::IDD, pParent)
	, m_RADIO_Mode(0)
	, m_RADIO_PWM_Mode(0)
{
	m_pParent=pParent;
}

CSpdRamp::~CSpdRamp()
{
}

void CSpdRamp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MaxDac, m_EDIT_MaxDac);
	DDX_Control(pDX, IDC_EDIT_MinDac, m_EDIT_MinDac);
	DDX_Control(pDX, IDC_CHECK_Fault, m_CHECK_Fault);
	DDX_Radio(pDX, IDC_RADIO_Inc, m_RADIO_Mode);
	DDX_Control(pDX, IDC_EDIT_LoopN, m_EDIT_LoopN);
	DDX_Control(pDX, IDC_EDIT_Ts, m_EDIT_Ts);
	DDX_Radio(pDX, IDC_RADIO_PWM_REG, m_RADIO_PWM_Mode);
	DDX_Control(pDX, IDC_CHECK_StopFan, m_CHECK_StopFan);
	DDX_Control(pDX, IDC_EDIT_TorCoarseA, m_EDIT_TorCoarseA);
	DDX_Control(pDX, IDC_EDIT_TorCoarseB, m_EDIT_TorCoarseB);
	DDX_Control(pDX, IDC_EDIT_TorCoarseC, m_EDIT_TorCoarseC);
	DDX_Control(pDX, IDC_EDIT_TorCoarseD, m_EDIT_TorCoarseD);
	DDX_Control(pDX, IDC_EDIT_TorCoarseE, m_EDIT_TorCoarseE);
	DDX_Control(pDX, IDC_EDIT_TorCoarseF, m_EDIT_TorCoarseF);
	DDX_Control(pDX, IDC_EDIT_TorCoarseG, m_EDIT_TorCoarseG);
	DDX_Control(pDX, IDC_EDIT_TorCoarseH, m_EDIT_TorCoarseH);
	DDX_Control(pDX, IDC_EDIT_TorFineA, m_EDIT_TorFineA);
	DDX_Control(pDX, IDC_EDIT_TorFineB, m_EDIT_TorFineB);
	DDX_Control(pDX, IDC_EDIT_TorFineC, m_EDIT_TorFineC);
	DDX_Control(pDX, IDC_EDIT_TorFineD, m_EDIT_TorFineD);
	DDX_Control(pDX, IDC_EDIT_TorFineE, m_EDIT_TorFineE);
	DDX_Control(pDX, IDC_EDIT_TorFineF, m_EDIT_TorFineF);
	DDX_Control(pDX, IDC_EDIT_TorFineG, m_EDIT_TorFineG);
	DDX_Control(pDX, IDC_EDIT_TorFineH, m_EDIT_TorFineH);
	DDX_Control(pDX, IDC_CHECK_FWAdTor, m_CHECK_FWAdTor);
	//  DDX_Check(pDX, IDC_CHECK_OTP1DONE, m_CHECK_OTP1Done);
	DDX_Control(pDX, IDC_CHECK_OTP1DONE, m_CHECK_OTP1Done);
}


BEGIN_MESSAGE_MAP(CSpdRamp, CDialog)
	ON_WM_CLOSE()
//	ON_WM_DESTROY()
ON_WM_NCDESTROY()
ON_BN_CLICKED(IDC_BUTTON_START, &CSpdRamp::OnBnClickedButtonStart)
ON_BN_CLICKED(IDC_RADIO_Inc, &CSpdRamp::OnBnClickedRadioInc)
ON_BN_CLICKED(IDC_RADIO_Dec, &CSpdRamp::OnBnClickedRadioDec)
ON_BN_CLICKED(IDC_RADIO_Loop, &CSpdRamp::OnBnClickedRadioLoop)
ON_BN_CLICKED(IDC_RADIO_PWM_REG, &CSpdRamp::OnBnClickedRadioPwmReg)
ON_BN_CLICKED(IDC_RADIO_PWM_IN, &CSpdRamp::OnBnClickedRadioPwmIn)
ON_BN_CLICKED(IDC_RADIO_PWM_FuncGen, &CSpdRamp::OnBnClickedRadioPwmFuncgen)
ON_BN_CLICKED(IDC_CHECK_FWAdTor, &CSpdRamp::OnBnClickedCheckFwadtor)
END_MESSAGE_MAP()


// CSpdRamp message handlers


void CSpdRamp::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


//void CSpdRamp::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//	// TODO: Add your message handler code here
//}


void CSpdRamp::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


BOOL CSpdRamp::OnInitDialog()
{
	CDialog::OnInitDialog();

	int temp;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	// TODO:  Add extra initialization here
	m_CHECK_Fault.EnableWindow(0);
	m_EDIT_LoopN.EnableWindow(0);
	m_EDIT_Ts.EnableWindow(0);

	//readback otp1_done
	temp=pParentParent->dataread_anybits(0x1a,2,1);
	if(temp==1)
	{
		m_CHECK_OTP1Done.SetCheck(1);
	}
	else
	{
        m_CHECK_OTP1Done.SetCheck(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSpdRamp::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	((CIntTest*)m_pParent)->spdrampdlg = NULL;
    delete this;
}


void CSpdRamp::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	CString sSettleTime,datbits;
	CString sMaxDac,sMinDac,sLoop;
	int PWM_freq=20000;
	int fTacho=0xff;
	int orig_pos_sns,restore_pos_sns;	
	CString errmsg;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//get input
	if (m_RADIO_PWM_Mode == 0)//hex
	{
		m_EDIT_MaxDac.GetWindowText(sMaxDac);
		if (m_EDIT_MaxDac.LineLength()==0) return;
		nMaxDacRamp = wcstod(sMaxDac,NULL);
		if((nMaxDacRamp < 0)|(nMaxDacRamp > 255))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
			return;
		}

		m_EDIT_MinDac.GetWindowText(sMinDac);
		if (m_EDIT_MinDac.LineLength()==0) return;
		nMinDacRamp = wcstod(sMinDac,NULL);
		if((nMinDacRamp < 0)|(nMinDacRamp > 255)|(nMinDacRamp>nMaxDacRamp))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
			return;
		}
	}
	else//%
	{
		m_EDIT_MaxDac.GetWindowText(sMaxDac);
		if (m_EDIT_MaxDac.LineLength()==0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
			return;
		}
		fMaxDacRamp = _wtof(sMaxDac);
		if((fMaxDacRamp < 0)|(fMaxDacRamp > 100))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
			return;
		}

		m_EDIT_MinDac.GetWindowText(sMinDac);
		if (m_EDIT_MinDac.LineLength()==0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
			return;
		}
		fMinDacRamp = _wtof(sMinDac);
		if((fMinDacRamp < 0)|(fMinDacRamp > 100)|(fMinDacRamp > fMaxDacRamp))
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
			return;
		}
	}

	//get input for loop mode
	if (m_RADIO_Mode == 2)
	{
		m_EDIT_LoopN.GetWindowText(sLoop);
		if (m_EDIT_LoopN.LineLength()==0) 
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Loop Number input");
			return;
		}
		nLoopRamp = _wtoi(sLoop);
		if(nLoopRamp <= 0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Loop Number input");
			return;
		}

		m_EDIT_Ts.GetWindowText(sSettleTime);
		if (m_EDIT_Ts.LineLength()==0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Settling Time input");
			return;
		}
		nSettleTimeRamp = _wtoi(sSettleTime);
		if(nSettleTimeRamp < 0)
		{
			pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Settling Time input");
			return;
		}
	}

	//get fw ad_tor input
	if (m_CHECK_FWAdTor.GetCheck()==TRUE)
	{
		if (GetAdTorInput()==FALSE)
			return;
	}

	// start measurement
	if (m_RADIO_PWM_Mode == 0)
		PWMRegMeasure();
	else if (m_RADIO_PWM_Mode == 1)
		PWMInMeasure();
	else if (m_RADIO_PWM_Mode == 2)
	{
		fMaxDacRamp = (fMaxDacRamp/100)/PWM_freq;//convert % to sec
		fMinDacRamp = (fMinDacRamp/100)/PWM_freq;

		//init FuncGen
		FuncGen = ibdev(0, 15, 0, 10, 1, 0);
		if (ibsta & ERR)
		{
		  errmsg.Format(_T("No Function Generator GPIB connection"));
		  pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
		  ibonl(FuncGen, 0);
		  return;
		}

		//generate PWM signal
		ibwrt(FuncGen, "APPL:PULS 20000, 3.3, 1.65", 26);//20kHz, ampl=3.3v, offset =1.65

		PWMFGMeasure();
	}

	//check stop fan
	if(m_CHECK_StopFan.GetCheck()==TRUE)
	{
		//set fan_en=0
		datbits = "0";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1);
	}

	ibonl(FuncGen, 0);
}


void CSpdRamp::OnBnClickedRadioInc()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Mode=0;
	m_CHECK_Fault.EnableWindow(0);
	m_EDIT_LoopN.EnableWindow(0);
	m_EDIT_Ts.EnableWindow(0);
}


void CSpdRamp::OnBnClickedRadioDec()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Mode=1;
	m_CHECK_Fault.EnableWindow(0);
	m_EDIT_LoopN.EnableWindow(0);
	m_EDIT_Ts.EnableWindow(0);
}


void CSpdRamp::OnBnClickedRadioLoop()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Mode=2;
	m_CHECK_Fault.EnableWindow(1);
	m_EDIT_LoopN.EnableWindow(1);
	m_EDIT_Ts.EnableWindow(1);
}


void CSpdRamp::PWMRegMeasure()
{
	// TODO: Add your control notification handler code here
	BOOL fault;
	int nSettleTimeRampTemp;
	int FDAC,FDac1,FDac2;
	DWORD startTime,endTime;
	int timeElasp = 0;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//Increasing Dac
	if (m_RADIO_Mode == 0)
	{
		pParentParent->wreg(0x18,nMinDacRamp);
		pParentParent->wreg(0x18,nMaxDacRamp);

		if (m_CHECK_FWAdTor.GetCheck()==TRUE)
		{
			//read FDAC
			FDac1 = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};
			FDac2 = pParentParent->dataread_anybits(0x16,0,8);
			if (!success){return;};
			FDAC = (FDac1<<8)+FDac2;

			while (FDAC<nMaxDacRamp)//will fdac readback value accurate enough for this judgement?
			{
				UseFWAdTorque(FDAC);

				//read FDAC
				FDac1 = pParentParent->dataread_anybits(0x17,4,4);
				if (!success){return;};
				FDac2 = pParentParent->dataread_anybits(0x16,0,8);
				if (!success){return;};
				FDAC = (FDac1<<8)+FDac2;
			}
		}
	}

	//Decreasing Dac
	else if (m_RADIO_Mode == 1)
	{
		pParentParent->wreg(0x18,nMaxDacRamp);
		pParentParent->wreg(0x18,nMinDacRamp);

		if (m_CHECK_FWAdTor.GetCheck()==TRUE)
		{
			//read FDAC
			FDac1 = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};
			FDac2 = pParentParent->dataread_anybits(0x16,0,8);
			if (!success){return;};
			FDAC = (FDac1<<8)+FDac2;

			while (FDAC>nMinDacRamp)//will fdac readback value accurate enough for this judgement?
			{
				UseFWAdTorque(FDAC);

				//read FDAC
				FDac1 = pParentParent->dataread_anybits(0x17,4,4);
				if (!success){return;};
				FDac2 = pParentParent->dataread_anybits(0x16,0,8);
				if (!success){return;};
				FDAC = (FDac1<<8)+FDac2;
			}
		}
	}

	//loop mode
	else if (m_RADIO_Mode == 2)
	{
		pParentParent->wreg(0x18,nMinDacRamp);

		nLoopTemp =0;
		while (nLoopTemp != nLoopRamp)
		{
			//set max dac
			pParentParent->wreg(0x18,nMaxDacRamp);

			//check beginning fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//check fault every 4s
			if ((nSettleTimeRamp >= 5000) && (m_CHECK_Fault.GetCheck() == TRUE))
			{
				nSettleTimeRampTemp=nSettleTimeRamp;
				while (nSettleTimeRampTemp >=5000)
				{
					//Sleep(4000);
					if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(4000);

					else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
					{
						//get start time
						timeElasp = 0;
						startTime = GetTickCount();

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						while (timeElasp<4000)
						{
							//use fw tor
							UseFWAdTorque(FDAC);

							//read FDAC
							FDac1 = pParentParent->dataread_anybits(0x17,4,4);
							if (!success){return;};
							FDac2 = pParentParent->dataread_anybits(0x16,0,8);
							if (!success){return;};
							FDAC = (FDac1<<8)+FDac2;

							endTime = GetTickCount();
							timeElasp = endTime - startTime;
						}
					}//end fw tor


					nSettleTimeRampTemp-=4000;

					fault = CheckFault();
					if (fault == TRUE)
						return;	
				}//end while

				//wait for the rest settle time
				//Sleep(nSettleTimeRampTemp);
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(nSettleTimeRampTemp);
				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRampTemp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor

			}

			else//no fault check, just wait for settle time
			{
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRamp);

				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRamp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}

			//check end fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//set min dac
			pParentParent->wreg(0x18,nMinDacRamp);

			//check init fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//check fault every 4s
			if ((nSettleTimeRamp >= 5000) && (m_CHECK_Fault.GetCheck() == TRUE))
			{
				nSettleTimeRampTemp=nSettleTimeRamp;
				while (nSettleTimeRampTemp >=5000)
				{
					//Sleep(4000);
					if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(4000);

					else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
					{
						//get start time
						timeElasp = 0;
						startTime = GetTickCount();

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						while (timeElasp<4000)
						{
							//use fw tor
							UseFWAdTorque(FDAC);

							//read FDAC
							FDac1 = pParentParent->dataread_anybits(0x17,4,4);
							if (!success){return;};
							FDac2 = pParentParent->dataread_anybits(0x16,0,8);
							if (!success){return;};
							FDAC = (FDac1<<8)+FDac2;

							endTime = GetTickCount();
							timeElasp = endTime - startTime;
						}
					}//end fw tor

					nSettleTimeRampTemp-=4000;

					fault = CheckFault();
					if (fault == TRUE)
						return;	
				}

				//wait for the rest settle time
				//Sleep(nSettleTimeRampTemp);
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRampTemp);
				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRampTemp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}

			else//no fault check, just wait for settle time
			{
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRamp);

				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRamp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}

			//check end fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			nLoopTemp++;
		}//end while
	}//end loop mode
}

void CSpdRamp::PWMInMeasure()
{
	int pulse_width1,nSettleTimeRampTemp;
	BOOL fault;
	int FDAC,FDac1,FDac2;
	DWORD startTime,endTime;
	int timeElasp = 0;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//Increasing Dac
	if (m_RADIO_Mode == 0)
	{
		duty_cycle1 = fMinDacRamp;//in percentage
		pulse_width1=(255*duty_cycle1)/100;
	    pParentParent->setpowerPWM(pulse_width1);
		pParentParent->UpdatePWM1();

		duty_cycle1 = fMaxDacRamp;
		pulse_width1=(255*duty_cycle1)/100;
	    pParentParent->setpowerPWM(pulse_width1);
		pParentParent->UpdatePWM1();	

		if (m_CHECK_FWAdTor.GetCheck()==TRUE)
		{
			//read FDAC
			FDac1 = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};
			FDac2 = pParentParent->dataread_anybits(0x16,0,8);
			if (!success){return;};
			FDAC = (FDac1<<8)+FDac2;

			while (FDAC<((255*fMaxDacRamp)/100))//will fdac readback value accurate enough for this judgement?
			{
				UseFWAdTorque(FDAC);

				//read FDAC
				FDac1 = pParentParent->dataread_anybits(0x17,4,4);
				if (!success){return;};
				FDac2 = pParentParent->dataread_anybits(0x16,0,8);
				if (!success){return;};
				FDAC = (FDac1<<8)+FDac2;
			}
		}
	}

	//Decreasing Dac
	else if (m_RADIO_Mode == 1)
	{
		duty_cycle1 = fMaxDacRamp;
		pulse_width1=(255*duty_cycle1)/100;
	    pParentParent->setpowerPWM(pulse_width1);
		pParentParent->UpdatePWM1();

		duty_cycle1 = fMinDacRamp;
		pulse_width1=(255*duty_cycle1)/100;
	    pParentParent->setpowerPWM(pulse_width1);
		pParentParent->UpdatePWM1();

		if (m_CHECK_FWAdTor.GetCheck()==TRUE)
		{
			//read FDAC
			FDac1 = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};
			FDac2 = pParentParent->dataread_anybits(0x16,0,8);
			if (!success){return;};
			FDAC = (FDac1<<8)+FDac2;

			while (FDAC>((255*fMinDacRamp)/100))//will fdac readback value accurate enough for this judgement?
			{
				UseFWAdTorque(FDAC);

				//read FDAC
				FDac1 = pParentParent->dataread_anybits(0x17,4,4);
				if (!success){return;};
				FDac2 = pParentParent->dataread_anybits(0x16,0,8);
				if (!success){return;};
				FDAC = (FDac1<<8)+FDac2;
			}
		}
	}

	//loop mode
	else if(m_RADIO_Mode == 2)
	{
		duty_cycle1 = fMinDacRamp;
		pulse_width1=(255*duty_cycle1)/100;
	    pParentParent->setpowerPWM(pulse_width1);
		pParentParent->UpdatePWM1();

		nLoopTemp =0;
		while (nLoopTemp != nLoopRamp)
		{
			//set max dac
			duty_cycle1 = fMaxDacRamp;
			pulse_width1=(255*duty_cycle1)/100;
			pParentParent->setpowerPWM(pulse_width1);
			pParentParent->UpdatePWM1();

			//check beginning fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//check fault every 4s
			if ((nSettleTimeRamp >= 5000) && (m_CHECK_Fault.GetCheck() == TRUE))
			{
				nSettleTimeRampTemp=nSettleTimeRamp;
				while (nSettleTimeRampTemp >=5000)
				{
					//Sleep(4000);
					if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(4000);

					else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
					{
						//get start time
						timeElasp = 0;
						startTime = GetTickCount();

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						while (timeElasp<4000)
						{
							//use fw tor
							UseFWAdTorque(FDAC);

							//read FDAC
							FDac1 = pParentParent->dataread_anybits(0x17,4,4);
							if (!success){return;};
							FDac2 = pParentParent->dataread_anybits(0x16,0,8);
							if (!success){return;};
							FDAC = (FDac1<<8)+FDac2;

							endTime = GetTickCount();
							timeElasp = endTime - startTime;
						}
					}//end fw tor

					nSettleTimeRampTemp-=4000;

					fault = CheckFault();
					if (fault == TRUE)
						return;	
				}

				//wait for the rest settle time
				//Sleep(nSettleTimeRampTemp);
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(nSettleTimeRampTemp);
				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRampTemp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor		
			}

			else//no fault check, just wait for settle time
			{
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRamp);

				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRamp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}

			//check end fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//set min dac
			duty_cycle1 = fMinDacRamp;
			pulse_width1=(255*duty_cycle1)/100;
			pParentParent->setpowerPWM(pulse_width1);
			pParentParent->UpdatePWM1();

			//check init fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//check fault every 4s
			if ((nSettleTimeRamp >= 5000) && (m_CHECK_Fault.GetCheck() == TRUE))
			{
				nSettleTimeRampTemp=nSettleTimeRamp;
				while (nSettleTimeRampTemp >=5000)
				{
					//Sleep(4000);
					if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(4000);

					else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
					{
						//get start time
						timeElasp = 0;
						startTime = GetTickCount();

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						while (timeElasp<4000)
						{
							//use fw tor
							UseFWAdTorque(FDAC);

							//read FDAC
							FDac1 = pParentParent->dataread_anybits(0x17,4,4);
							if (!success){return;};
							FDac2 = pParentParent->dataread_anybits(0x16,0,8);
							if (!success){return;};
							FDAC = (FDac1<<8)+FDac2;

							endTime = GetTickCount();
							timeElasp = endTime - startTime;
						}
					}//end fw tor

					nSettleTimeRampTemp-=4000;

					fault = CheckFault();
					if (fault == TRUE)
						return;	
				}//end while

				//wait for the rest settle time
				//Sleep(nSettleTimeRampTemp);
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(nSettleTimeRampTemp);
				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRampTemp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}

			else//no fault check, just wait for settle time
			{
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRamp);

				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRamp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}//end no fault check

			//check end fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			nLoopTemp++;
		}//end while
	}//end loop
}

void CSpdRamp::PWMFGMeasure()
{
	char sFuncGen[100];
	BOOL fault;
	int nSettleTimeRampTemp;
	int FDAC,FDac1,FDac2;
	DWORD startTime,endTime;
	int timeElasp = 0;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//Increasing Dac
	if (m_RADIO_Mode == 0)
	{	
		sprintf(sFuncGen, "PULS:WIDT %.7f", fMinDacRamp);//issue: from10% to20%, DC cannot go immediately, but have a tranaction time.while manually control FG,no transaction time.
		ibwrt(FuncGen, sFuncGen, 19);

		sprintf(sFuncGen, "PULS:WIDT %.7f", fMaxDacRamp);
		ibwrt(FuncGen, sFuncGen, 19);

		if (m_CHECK_FWAdTor.GetCheck()==TRUE)
		{
			//read FDAC
			FDac1 = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};
			FDac2 = pParentParent->dataread_anybits(0x16,0,8);
			if (!success){return;};
			FDAC = (FDac1<<8)+FDac2;

			while (FDAC<((255*fMaxDacRamp)/100))//will fdac readback value accurate enough for this judgement?
			{
				UseFWAdTorque(FDAC);

				//read FDAC
				FDac1 = pParentParent->dataread_anybits(0x17,4,4);
				if (!success){return;};
				FDac2 = pParentParent->dataread_anybits(0x16,0,8);
				if (!success){return;};
				FDAC = (FDac1<<8)+FDac2;
			}
		}//end fw tor

	}

	//Decreasing Dac
	else if (m_RADIO_Mode == 1)
	{
		sprintf(sFuncGen, "PULS:WIDT %.7f", fMaxDacRamp);
		ibwrt(FuncGen, sFuncGen, 19);
		
		sprintf(sFuncGen, "PULS:WIDT %.7f", fMinDacRamp);
		ibwrt(FuncGen, sFuncGen, 19);

		if (m_CHECK_FWAdTor.GetCheck()==TRUE)
		{
			//read FDAC
			FDac1 = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};
			FDac2 = pParentParent->dataread_anybits(0x16,0,8);
			if (!success){return;};
			FDAC = (FDac1<<8)+FDac2;

			while (FDAC>((255*fMinDacRamp)/100))//will fdac readback value accurate enough for this judgement?
			{
				UseFWAdTorque(FDAC);

				//read FDAC
				FDac1 = pParentParent->dataread_anybits(0x17,4,4);
				if (!success){return;};
				FDac2 = pParentParent->dataread_anybits(0x16,0,8);
				if (!success){return;};
				FDAC = (FDac1<<8)+FDac2;
			}
		}//end fw tor

	}

	//loop mode
	else if(m_RADIO_Mode == 2)
	{
		sprintf(sFuncGen, "PULS:WIDT %.7f", fMinDacRamp);
		ibwrt(FuncGen, sFuncGen, 19);

		nLoopTemp = 0;
		while (nLoopTemp != nLoopRamp)
		{
			//set max dac
			sprintf(sFuncGen, "PULS:WIDT %.7f", fMaxDacRamp);
			ibwrt(FuncGen, sFuncGen, 19);

			//check beginning fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//check fault every 4s
			if ((nSettleTimeRamp >= 5000) && (m_CHECK_Fault.GetCheck() == TRUE))
			{
				nSettleTimeRampTemp=nSettleTimeRamp;
				while (nSettleTimeRampTemp >=5000)
				{
					//Sleep(4000);
					if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(4000);

					else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
					{
						//get start time
						timeElasp = 0;
						startTime = GetTickCount();

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						while (timeElasp<4000)
						{
							//use fw tor
							UseFWAdTorque(FDAC);

							//read FDAC
							FDac1 = pParentParent->dataread_anybits(0x17,4,4);
							if (!success){return;};
							FDac2 = pParentParent->dataread_anybits(0x16,0,8);
							if (!success){return;};
							FDAC = (FDac1<<8)+FDac2;

							endTime = GetTickCount();
							timeElasp = endTime - startTime;
						}
					}//end fw tor

					nSettleTimeRampTemp-=4000;

					fault = CheckFault();
					if (fault == TRUE)
						return;	
				}

				//wait for the rest settle time
				//Sleep(nSettleTimeRampTemp);
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(nSettleTimeRampTemp);
				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRampTemp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}


			else//no fault check, just wait for settle time
			{
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRamp);

				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRamp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}

			//check end fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//set min dac
			sprintf(sFuncGen, "PULS:WIDT %.7f", fMinDacRamp);
			ibwrt(FuncGen, sFuncGen, 19);

			//check init fault
			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			//check fault every 4s
			if ((nSettleTimeRamp >= 5000) && (m_CHECK_Fault.GetCheck() == TRUE))
			{
				nSettleTimeRampTemp=nSettleTimeRamp;
				while (nSettleTimeRampTemp >=5000)
				{
					//Sleep(4000);
					if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(4000);

					else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
					{
						//get start time
						timeElasp = 0;
						startTime = GetTickCount();

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						while (timeElasp<4000)
						{
							//use fw tor
							UseFWAdTorque(FDAC);

							//read FDAC
							FDac1 = pParentParent->dataread_anybits(0x17,4,4);
							if (!success){return;};
							FDac2 = pParentParent->dataread_anybits(0x16,0,8);
							if (!success){return;};
							FDAC = (FDac1<<8)+FDac2;

							endTime = GetTickCount();
							timeElasp = endTime - startTime;
						}
					}//end fw tor

					nSettleTimeRampTemp-=4000;

					fault = CheckFault();
					if (fault == TRUE)
						return;	
				}//end while


				//wait for the rest settle time
				//Sleep(nSettleTimeRampTemp);
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
						Sleep(nSettleTimeRampTemp);
				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRampTemp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}//end check fault every 4s


			else//no fault check, just wait for settle time
			{
				if (m_CHECK_FWAdTor.GetCheck()==FALSE)
					Sleep(nSettleTimeRamp);

				else if (m_CHECK_FWAdTor.GetCheck()==TRUE)
				{
					//get start time
					timeElasp = 0;
					startTime = GetTickCount();

					//read FDAC
					FDac1 = pParentParent->dataread_anybits(0x17,4,4);
					if (!success){return;};
					FDac2 = pParentParent->dataread_anybits(0x16,0,8);
					if (!success){return;};
					FDAC = (FDac1<<8)+FDac2;

					while (timeElasp<nSettleTimeRamp)
					{
						//use fw tor
						UseFWAdTorque(FDAC);

						//read FDAC
						FDac1 = pParentParent->dataread_anybits(0x17,4,4);
						if (!success){return;};
						FDac2 = pParentParent->dataread_anybits(0x16,0,8);
						if (!success){return;};
						FDAC = (FDac1<<8)+FDac2;

						endTime = GetTickCount();
						timeElasp = endTime - startTime;
					}
				}//end fw tor
			}//end no fault check


			if (m_CHECK_Fault.GetCheck()==TRUE)
			{
				fault = CheckFault();
				if (fault == TRUE)
					return;
			}

			nLoopTemp++;
		}//end while
	}//end loop
}

BOOL CSpdRamp::CheckFault()
{
	CString errmsg,datbits;
	int datlength;
	int orig_pos_sns,pos_sns_reg;
	int bFault;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	////save pos_sns
	//datlength = 1;
	//orig_pos_sns = pParentParent->dataread_anybits(0x01,3,datlength);
	//// set pos_sns = 0
	//datbits = "0";
	//pParentParent->dataupdate_anybits(0x01,3,datbits,1); 

	//read fault
	bFault = pParentParent->rreg( 0x19); // read fault
	if (!success){return TRUE;};
	bFault = ((bFault & 0x78) >> 3);

	//// restore pos_sns
	//pos_sns_reg=pParentParent->rreg(0x01); 
	//pos_sns_reg |=(orig_pos_sns<<4);
	//pParentParent->wreg(0x01,pos_sns_reg);

	if (bFault != 0)
	{
		//display msg
		errmsg.Format(_T("No of Spins: %d. Fault = %d"),nLoopTemp, bFault);
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);

		return TRUE;
	}

	return FALSE;
}

void CSpdRamp::OnBnClickedRadioPwmReg()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWM_Mode = 0;
}


void CSpdRamp::OnBnClickedRadioPwmIn()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWM_Mode = 1;
}


void CSpdRamp::OnBnClickedRadioPwmFuncgen()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWM_Mode = 2;
}

BOOL CSpdRamp::GetAdTorInput()
{
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//sFWtorA_coarse
	m_EDIT_TorCoarseA.GetWindowText(sFWtorA_coarse);
	if (m_EDIT_TorCoarseA.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torA_coarse");
		return FALSE;
	}
	FWtorA_coarse = _wtoi(sFWtorA_coarse);
	if((FWtorA_coarse < 0)|(FWtorA_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torA_coarse input range!");
		return FALSE;
	}

	//sFWtorA_fine
	m_EDIT_TorFineA.GetWindowText(sFWtorA_fine);
	if (m_EDIT_TorFineA.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorA_fine");
		return FALSE;
	}
	FWtorA_fine = _wtoi(sFWtorA_fine);
	if((FWtorA_fine < 0)|(FWtorA_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorA_fine input range!");
		return FALSE;
	}


	//sFWtorB_coarse
	m_EDIT_TorCoarseB.GetWindowText(sFWtorB_coarse);
	if (m_EDIT_TorCoarseB.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torB_coarse");
		return FALSE;
	}
	FWtorB_coarse = _wtoi(sFWtorB_coarse);
	if((FWtorB_coarse < 0)|(FWtorB_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torB_coarse input range!");
		return FALSE;
	}

	//sFWtorB_fine
	m_EDIT_TorFineB.GetWindowText(sFWtorB_fine);
	if (m_EDIT_TorFineB.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorB_fine");
		return FALSE;
	}
	FWtorB_fine = _wtoi(sFWtorB_fine);
	if((FWtorB_fine < 0)|(FWtorB_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorB_fine input range!");
		return FALSE;
	}

	//sFWtorC_coarse
	m_EDIT_TorCoarseC.GetWindowText(sFWtorC_coarse);
	if (m_EDIT_TorCoarseC.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torC_coarse");
		return FALSE;
	}
	FWtorC_coarse = _wtoi(sFWtorC_coarse);
	if((FWtorC_coarse < 0)|(FWtorC_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torC_coarse input range!");
		return FALSE;
	}

	//sFWtorC_fine
	m_EDIT_TorFineC.GetWindowText(sFWtorC_fine);
	if (m_EDIT_TorFineC.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorC_fine");
		return FALSE;
	}
	FWtorC_fine = _wtoi(sFWtorC_fine);
	if((FWtorC_fine < 0)|(FWtorC_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorC_fine input range!");
		return FALSE;
	}

	//sFWtorD_coarse
	m_EDIT_TorCoarseD.GetWindowText(sFWtorD_coarse);
	if (m_EDIT_TorCoarseD.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torD_coarse");
		return FALSE;
	}
	FWtorD_coarse = _wtoi(sFWtorD_coarse);
	if((FWtorD_coarse < 0)|(FWtorD_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torD_coarse input range!");
		return FALSE;
	}

	//sFWtorD_fine
	m_EDIT_TorFineD.GetWindowText(sFWtorD_fine);
	if (m_EDIT_TorFineD.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorD_fine");
		return FALSE;
	}
	FWtorD_fine = _wtoi(sFWtorD_fine);
	if((FWtorD_fine < 0)|(FWtorD_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorD_fine input range!");
		return FALSE;
	}

	//sFWtorE_coarse
	m_EDIT_TorCoarseE.GetWindowText(sFWtorE_coarse);
	if (m_EDIT_TorCoarseE.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torE_coarse");
		return FALSE;
	}
	FWtorE_coarse = _wtoi(sFWtorE_coarse);
	if((FWtorE_coarse < 0)|(FWtorE_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torE_coarse input range!");
		return FALSE;
	}

	//sFWtorE_fine
	m_EDIT_TorFineE.GetWindowText(sFWtorE_fine);
	if (m_EDIT_TorFineE.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorE_fine");
		return FALSE;
	}
	FWtorE_fine = _wtoi(sFWtorE_fine);
	if((FWtorE_fine < 0)|(FWtorE_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorE_fine input range!");
		return FALSE;
	}

	//sFWtorF_coarse
	m_EDIT_TorCoarseF.GetWindowText(sFWtorF_coarse);
	if (m_EDIT_TorCoarseF.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torF_coarse");
		return FALSE;
	}
	FWtorF_coarse = _wtoi(sFWtorF_coarse);
	if((FWtorF_coarse < 0)|(FWtorF_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torF_coarse input range!");
		return FALSE;
	}

	//sFWtorF_fine
	m_EDIT_TorFineF.GetWindowText(sFWtorF_fine);
	if (m_EDIT_TorFineF.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorF_fine");
		return FALSE;
	}
	FWtorF_fine = _wtoi(sFWtorF_fine);
	if((FWtorF_fine < 0)|(FWtorF_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorF_fine input range!");
		return FALSE;
	}

	//sFWtorG_coarse
	m_EDIT_TorCoarseG.GetWindowText(sFWtorG_coarse);
	if (m_EDIT_TorCoarseG.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torG_coarse");
		return FALSE;
	}
	FWtorG_coarse = _wtoi(sFWtorG_coarse);
	if((FWtorG_coarse < 0)|(FWtorG_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torG_coarse input range!");
		return FALSE;
	}

	//sFWtorG_fine
	m_EDIT_TorFineG.GetWindowText(sFWtorG_fine);
	if (m_EDIT_TorFineG.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorG_fine");
		return FALSE;
	}
	FWtorG_fine = _wtoi(sFWtorG_fine);
	if((FWtorG_fine < 0)|(FWtorG_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorG_fine input range!");
		return FALSE;
	}

	//sFWtorH_coarse
	m_EDIT_TorCoarseH.GetWindowText(sFWtorH_coarse);
	if (m_EDIT_TorCoarseH.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torH_coarse");
		return FALSE;
	}
	FWtorH_coarse = _wtoi(sFWtorH_coarse);
	if((FWtorH_coarse < 0)|(FWtorH_coarse > 0x07))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check torH_coarse input range!");
		return FALSE;
	}

	//sFWtorH_fine
	m_EDIT_TorFineH.GetWindowText(sFWtorH_fine);
	if (m_EDIT_TorFineH.LineLength()==0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input FWtorH_fine");
		return FALSE;
	}
	FWtorH_fine = _wtoi(sFWtorH_fine);
	if((FWtorH_fine < 0)|(FWtorH_fine > 0x03))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check FWtorH_fine input range!");
		return FALSE;
	}

	return TRUE;
}

void CSpdRamp::OnBnClickedCheckFwadtor()
{
	// TODO: Add your control notification handler code here
	int temp;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	//readback otp1_done
	temp=pParentParent->dataread_anybits(0x1a,2,1);
	if (!success){return;};
	if(temp==0){
		m_CHECK_OTP1Done.SetCheck(0);
	}else{
        m_CHECK_OTP1Done.SetCheck(1);
	}
}

void CSpdRamp::UseFWAdTorque(int FinalDac)
{
	//int FDac1, FDac2;
	//int FinalDac;
	int currTor;
	int FWTor;
	int temp;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//get correct FW Adtor
	if ((FinalDac>=0)&&(FinalDac<=0x1f))
	{
		FWTor=(FWtorA_coarse<<2)|FWtorA_fine;
	}
	else if ((FinalDac>=0x20)&&(FinalDac<=0x3f))
	{
		FWTor=(FWtorB_coarse<<2)|FWtorB_fine;
	}
	else if ((FinalDac>=0x40)&&(FinalDac<=0x5f))
	{
		FWTor=(FWtorC_coarse<<2)|FWtorC_fine;
	}
	else if ((FinalDac>=0x60)&&(FinalDac<=0x7f))
	{
		FWTor=(FWtorD_coarse<<2)|FWtorD_fine;
	}
	else if ((FinalDac>=0x80)&&(FinalDac<=0x9f))
	{
		FWTor=(FWtorE_coarse<<2)|FWtorE_fine;
	}
	else if ((FinalDac>=0xa0)&&(FinalDac<=0xbf))
	{
		FWTor=(FWtorF_coarse<<2)|FWtorF_fine;
	}
	else if ((FinalDac>=0xc0)&&(FinalDac<=0xdf))
	{
		FWTor=(FWtorG_coarse<<2)|FWtorG_fine;
	}
	else if ((FinalDac>=0xe0)&&(FinalDac<=0xff))
	{
		FWTor=(FWtorH_coarse<<2)|FWtorH_fine;
	}

	//compare current tor and correct fw tor. set correct fw tor
	currTor = (pParentParent->rreg(0x03))&0x1f;
	if (currTor!=FWTor)
	{
		temp = (pParentParent->rreg(0x03))&0xe0;
		temp |= FWTor;
		pParentParent->wreg(0x03,temp);
	}
}
