// FWTOR.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "FanmotorDlg.h"
#include "TestDlg.h"
#include "FWTOR.h"
#include "afxdialogex.h"
#include <string.h>
#include "conio.h"
#include <stdlib.h>
#include <ctype.h>
#include "math.h"

// CFWTOR dialog
int nSettleT=10000,MnMaxDacRamp=0xff,MnMinDacRamp=0;
double MfMaxDacRamp,MfMinDacRamp;
int MFWtorque_temp=-1, MFWtorque_temp1=-1, MFWtorA_coarse=-1, MFWtorA_fine=-1, MFWtorB_coarse=-1, MFWtorB_fine=-1,MFWtorC_coarse=-1, 
	MFWtorC_fine=-1,MFWtorD_coarse=-1, MFWtorD_fine=-1,MFWtorE_coarse=-1, MFWtorE_fine=-1,MFWtorF_coarse=-1, MFWtorF_fine=-1,MFWtorG_coarse=-1, MFWtorG_fine=-1,MFWtorH_coarse=-1, MFWtorH_fine=-1;
CString MsFWtorque_temp, MsFWtorque_temp1, MsFWtorA_coarse, MsFWtorA_fine, MsFWtorB_coarse, MsFWtorB_fine,MsFWtorC_coarse, MsFWtorC_fine,MsFWtorD_coarse, MsFWtorD_fine,MsFWtorE_coarse, MsFWtorE_fine,MsFWtorF_coarse, MsFWtorF_fine,MsFWtorG_coarse, MsFWtorG_fine,MsFWtorH_coarse, MsFWtorH_fine;
BOOL MstatFWTorA=FALSE,MstatFWTorB=FALSE,MstatFWTorC=FALSE,MstatFWTorD=FALSE,MstatFWTorE=FALSE,MstatFWTorF=FALSE,MstatFWTorG=FALSE,MstatFWTorH=FALSE;

IMPLEMENT_DYNAMIC(CFWTOR, CDialog)

CFWTOR::CFWTOR(CWnd* pParent /*=NULL*/)
	: CDialog(CFWTOR::IDD, pParent)
	, m_RADIO_Mode(1)
{
	m_pParent=pParent;
}

CFWTOR::~CFWTOR()
{
}

void CFWTOR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MinDac, m_EDIT_MinDac);
	DDX_Control(pDX, IDC_EDIT_MaxDac, m_EDIT_MaxDac);
	DDX_Radio(pDX, IDC_RADIO_Inc, m_RADIO_Mode);
	DDX_Control(pDX, IDC_CHECK_StopFan, m_CHECK_StopFan);
	DDX_Control(pDX, IDC_EDIT_SettleT, m_EDIT_SettleT);
	DDX_Control(pDX, IDC_CHECK_FWAdTor, m_CHECK_FWAdTor);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseA, m_COMBO_TorCoarseA);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseB, m_COMBO_TorCoarseB);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseC, m_COMBO_TorCoarseC);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseD, m_COMBO_TorCoarseD);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseE, m_COMBO_TorCoarseE);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseF, m_COMBO_TorCoarseF);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseG, m_COMBO_TorCoarseG);
	//DDX_Control(pDX, IDC_EDIT_TorCoarseH, m_COMBO_TorCoarseH);
	//DDX_Control(pDX, IDC_EDIT_TorFineA, m_COMBO_TorFineA);
	//DDX_Control(pDX, IDC_EDIT_TorFineB, m_COMBO_TorFineB);
	//DDX_Control(pDX, IDC_EDIT_TorFineC, m_COMBO_TorFineC);
	//DDX_Control(pDX, IDC_EDIT_TorFineD, m_COMBO_TorFineD);
	//DDX_Control(pDX, IDC_EDIT_TorFineE, m_COMBO_TorFineE);
	//DDX_Control(pDX, IDC_EDIT_TorFineF, m_COMBO_TorFineF);
	//DDX_Control(pDX, IDC_EDIT_TorFineG, m_COMBO_TorFineG);
	//DDX_Control(pDX, IDC_EDIT_TorFineH, m_COMBO_TorFineH);
	DDX_Control(pDX, IDC_COMBO_TorCoarseA, m_COMBO_TorCoarseA);
	DDX_Control(pDX, IDC_COMBO_TorCoarseB, m_COMBO_TorCoarseB);
	DDX_Control(pDX, IDC_COMBO_TorCoarseC, m_COMBO_TorCoarseC);
	DDX_Control(pDX, IDC_COMBO_TorCoarseD, m_COMBO_TorCoarseD);
	DDX_Control(pDX, IDC_COMBO_TorCoarseE, m_COMBO_TorCoarseE);
	DDX_Control(pDX, IDC_COMBO_TorCoarseF, m_COMBO_TorCoarseF);
	DDX_Control(pDX, IDC_COMBO_TorCoarseG, m_COMBO_TorCoarseG);
	DDX_Control(pDX, IDC_COMBO_TorCoarseH, m_COMBO_TorCoarseH);
	DDX_Control(pDX, IDC_COMBO_TorFineA, m_COMBO_TorFineA);
	DDX_Control(pDX, IDC_COMBO_TorFineB, m_COMBO_TorFineB);
	DDX_Control(pDX, IDC_COMBO_TorFineC, m_COMBO_TorFineC);
	DDX_Control(pDX, IDC_COMBO_TorFineD, m_COMBO_TorFineD);
	DDX_Control(pDX, IDC_COMBO_TorFineE, m_COMBO_TorFineE);
	DDX_Control(pDX, IDC_COMBO_TorFineF, m_COMBO_TorFineF);
	DDX_Control(pDX, IDC_COMBO_TorFineG, m_COMBO_TorFineG);
	DDX_Control(pDX, IDC_COMBO_TorFineH, m_COMBO_TorFineH);
}


BEGIN_MESSAGE_MAP(CFWTOR, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_START, &CFWTOR::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_RADIO_Inc, &CFWTOR::OnBnClickedRadioInc)
	ON_BN_CLICKED(IDC_RADIO_Dec, &CFWTOR::OnBnClickedRadioDec)
END_MESSAGE_MAP()


// CFWTOR message handlers


void CFWTOR::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();
	//CDialog::OnClose();
}


void CFWTOR::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


void CFWTOR::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	((CTestDlg*)m_pParent)->fwtordlg = NULL;
    delete this;
}


BOOL CFWTOR::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString temp_string;
	// TODO:  Add extra initialization here
	m_RADIO_Mode = 1;//always same mode, stop->increase->decrease

	temp_string.Format(_T("%d"),(MnMinDacRamp*100)/255);
	m_EDIT_MinDac.SetWindowText(temp_string);

	temp_string.Format(_T("%d"),(MnMaxDacRamp*100)/255);
	m_EDIT_MaxDac.SetWindowText(temp_string);

	temp_string.Format(_T("%d"),nSettleT);
	m_EDIT_SettleT.SetWindowText(temp_string);


	m_COMBO_TorCoarseA.SetCurSel(0);
	m_COMBO_TorCoarseB.SetCurSel(0);
	m_COMBO_TorCoarseC.SetCurSel(0);
	m_COMBO_TorCoarseD.SetCurSel(0);
	m_COMBO_TorCoarseE.SetCurSel(0);
	m_COMBO_TorCoarseF.SetCurSel(0);
	m_COMBO_TorCoarseG.SetCurSel(0);
	m_COMBO_TorCoarseH.SetCurSel(0);
	m_COMBO_TorFineA.SetCurSel(0);
	m_COMBO_TorFineB.SetCurSel(0);
	m_COMBO_TorFineC.SetCurSel(0);
	m_COMBO_TorFineD.SetCurSel(0);
	m_COMBO_TorFineE.SetCurSel(0);
	m_COMBO_TorFineF.SetCurSel(0);
	m_COMBO_TorFineG.SetCurSel(0);
	m_COMBO_TorFineH.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFWTOR::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	CString sSettleT,datbits;
	CString sMaxDac,sMinDac;
	int orig_pos_sns,restore_pos_sns;	
	CString errmsg;

	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//get input
	m_EDIT_MaxDac.GetWindowText(sMaxDac);
	if (m_EDIT_MaxDac.LineLength()==0)
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
		return;
	}
	MfMaxDacRamp = _wtof(sMaxDac);
	if((MfMaxDacRamp < 0)|(MfMaxDacRamp > 100))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Max Dac input");
		return;
	}
	MnMaxDacRamp=MfMaxDacRamp*255/100;


	m_EDIT_MinDac.GetWindowText(sMinDac);
	if (m_EDIT_MinDac.LineLength()==0)
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
		return;
	}
	MfMinDacRamp = _wtof(sMinDac);
	if((MfMinDacRamp < 0)|(MfMinDacRamp > 100)|(MfMinDacRamp > MfMaxDacRamp))
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Min Dac input");
		return;
	}
	MnMinDacRamp=MfMinDacRamp*255/100;


	m_EDIT_SettleT.GetWindowText(sSettleT);
	if (m_EDIT_SettleT.LineLength()==0)
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Settling time");
		return;
	}
	nSettleT = _wtof(sSettleT);
	if(nSettleT < 0)
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check Settling time");
		return;
	}


	//get fw ad_tor input
	if (GetAdTorInput()==FALSE)
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please check firmware adaptive torque input!");
		return;
	}

	//disable tor input control
	m_COMBO_TorCoarseA.EnableWindow(0);
	m_COMBO_TorCoarseB.EnableWindow(0);
	m_COMBO_TorCoarseC.EnableWindow(0);
	m_COMBO_TorCoarseD.EnableWindow(0);
	m_COMBO_TorCoarseE.EnableWindow(0);
	m_COMBO_TorCoarseF.EnableWindow(0);
	m_COMBO_TorCoarseG.EnableWindow(0);
	m_COMBO_TorCoarseH.EnableWindow(0);
	m_COMBO_TorFineA.EnableWindow(0);
	m_COMBO_TorFineB.EnableWindow(0);
	m_COMBO_TorFineC.EnableWindow(0);
	m_COMBO_TorFineD.EnableWindow(0);
	m_COMBO_TorFineE.EnableWindow(0);
	m_COMBO_TorFineF.EnableWindow(0);
	m_COMBO_TorFineG.EnableWindow(0);
	m_COMBO_TorFineH.EnableWindow(0);


	//set ad_tor_en=0
	datbits = "0";
	pParentParent->dataupdate_anybits(0x01,4,datbits,1);

	//set pwm_reg_sel=1
	datbits = "1";
	pParentParent->dataupdate_anybits(0x02,1,datbits,1);
	datbits = "0";
	pParentParent->dataupdate_anybits(0x0a,0,datbits,1);

	
	// start measurement
	PWMRegMeasure();

	//check stop fan
	if(m_CHECK_StopFan.GetCheck()==TRUE)
	{
		//set fan_en=0
		datbits = "0";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1);
	}

	//enable tor input control
	m_COMBO_TorCoarseA.EnableWindow(1);
	m_COMBO_TorCoarseB.EnableWindow(1);
	m_COMBO_TorCoarseC.EnableWindow(1);
	m_COMBO_TorCoarseD.EnableWindow(1);
	m_COMBO_TorCoarseE.EnableWindow(1);
	m_COMBO_TorCoarseF.EnableWindow(1);
	m_COMBO_TorCoarseG.EnableWindow(1);
	m_COMBO_TorCoarseH.EnableWindow(1);
	m_COMBO_TorFineA.EnableWindow(1);
	m_COMBO_TorFineB.EnableWindow(1);
	m_COMBO_TorFineC.EnableWindow(1);
	m_COMBO_TorFineD.EnableWindow(1);
	m_COMBO_TorFineE.EnableWindow(1);
	m_COMBO_TorFineF.EnableWindow(1);
	m_COMBO_TorFineG.EnableWindow(1);
	m_COMBO_TorFineH.EnableWindow(1);
}

BOOL CFWTOR::GetAdTorInput()
{
	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//MsFWtorA_coarse
	MFWtorA_coarse = m_COMBO_TorCoarseA.GetCurSel();
	if (MFWtorA_coarse < 0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torA_coarse");
		return FALSE;
	}


	//MsFWtorA_fine
	MFWtorA_fine = m_COMBO_TorFineA.GetCurSel();
	if (MFWtorA_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorA_fine");
		return FALSE;
	}


	//MsFWtorB_coarse
	MFWtorB_coarse = m_COMBO_TorCoarseB.GetCurSel();
	if (MFWtorB_coarse < 0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torB_coarse");
		return FALSE;
	}

	//MsFWtorB_fine
	MFWtorB_fine = m_COMBO_TorFineB.GetCurSel();
	if (MFWtorB_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorB_fine");
		return FALSE;
	}

	//MsFWtorC_coarse
	MFWtorC_coarse = m_COMBO_TorCoarseC.GetCurSel();
	if (MFWtorC_coarse<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torC_coarse");
		return FALSE;
	}

	//MsFWtorC_fine
	MFWtorC_fine = m_COMBO_TorFineC.GetCurSel();
	if (MFWtorC_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorC_fine");
		return FALSE;
	}

	//MsFWtorD_coarse
	MFWtorD_coarse = m_COMBO_TorCoarseD.GetCurSel();
	if (MFWtorD_coarse<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torD_coarse");
		return FALSE;
	}

	//MsFWtorD_fine
	MFWtorD_fine = m_COMBO_TorFineD.GetCurSel();
	if (MFWtorD_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorD_fine");
		return FALSE;
	}


	//MsFWtorE_coarse
	MFWtorE_coarse = m_COMBO_TorCoarseE.GetCurSel();
	if (MFWtorE_coarse<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torE_coarse");
		return FALSE;
	}


	//MsFWtorE_fine
	MFWtorE_fine = m_COMBO_TorFineE.GetCurSel();
	if (MFWtorE_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorE_fine");
		return FALSE;
	}

	//MsFWtorF_coarse
	MFWtorF_coarse = m_COMBO_TorCoarseF.GetCurSel();
	if (MFWtorF_coarse<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torF_coarse");
		return FALSE;
	}


	//MsFWtorF_fine
	MFWtorF_fine = m_COMBO_TorFineF.GetCurSel();
	if (MFWtorF_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorF_fine");
		return FALSE;
	}


	//MsFWtorG_coarse
	MFWtorG_coarse = m_COMBO_TorCoarseG.GetCurSel();
	if (MFWtorG_coarse<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torG_coarse");
		return FALSE;
	}

	//MsFWtorG_fine
	MFWtorG_fine = m_COMBO_TorFineG.GetCurSel();
	if (MFWtorG_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorG_fine");
		return FALSE;
	}

	//MsFWtorH_coarse
	MFWtorH_coarse = m_COMBO_TorCoarseH.GetCurSel();
	if (MFWtorH_coarse<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input torH_coarse");
		return FALSE;
	}

	//MsFWtorH_fine
	MFWtorH_fine = m_COMBO_TorFineH.GetCurSel();
	if (MFWtorH_fine<0) 
	{
		pParentParent->DisplayErrorMessageBox(L"Error", L"Please input MFWtorH_fine");
		return FALSE;
	}

	return TRUE;
}

void CFWTOR::PWMRegMeasure()
{
	// TODO: Add your control notification handler code here
	int nSettleTimeRampTemp;
	int FDAC;
	DWORD startTime,endTime;
	int timeElasp = 0;

	int bFault;
	CString datbits,errmsg;
	int datlength;
	int orig_pos_sns;
	int pos_sns_reg;
	int fan_en;
	int orig_DAC;

	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//save pos_sns
	datlength = 1;
	orig_pos_sns = pParentParent->dataread_anybits(0x01,3,datlength);

	//get orig DAC
	orig_DAC = pParentParent->rreg(0x18);
	if (!success){return;};	

	////Increasing Dac
	//if (m_RADIO_Mode == 0)
	//{
	//	//get start time
	//	timeElasp = 0;
	//	startTime = GetTickCount();

	//	//set fan_en=1
	//	datbits = "1";
	//	pParentParent->dataupdate_anybits(0x04,0,datbits,1);

	//	pParentParent->wreg(0x18,MnMinDacRamp);
	//	pParentParent->wreg(0x18,MnMaxDacRamp);

	//	//read FDAC MSB
	//	FDAC = pParentParent->dataread_anybits(0x17,4,4);
	//	if (!success){return;};

	//	

	//	while (timeElasp<nSettleT)//will fdac readback value accurate enough for this judgement?
	//	{
	//		//check fault
	//		datbits = "0";// set pos_sns = 0
	//		pParentParent->dataupdate_anybits(0x01,3,datbits,1); 
	//		//read fault
	//		bFault = pParentParent->rreg( 0x19); // read fault
	//		if (!success){return;};
	//		bFault = ((bFault & 0x78) >> 3);
	//		// restore pos_sns
	//		pos_sns_reg=pParentParent->rreg(0x01); 
	//		pos_sns_reg |=(orig_pos_sns<<4);
	//		pParentParent->wreg(0x01,pos_sns_reg);
	//		if (bFault != 0)
	//		{
	//			//display msg
	//			errmsg.Format(_T("Error! Fault = %d"), bFault);
	//			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
	//			return;
	//		}

	//		//apply ad_tor
	//		UseFWAdTorque(FDAC);

	//		//read FDAC
	//		FDAC = pParentParent->dataread_anybits(0x17,4,4);
	//		if (!success){return;};

	//		endTime = GetTickCount();
	//		timeElasp = endTime - startTime;
	//	}//end while
	//}

	////Decreasing Dac
	//else if (m_RADIO_Mode == 1)
	//{

	//check fan_en
	fan_en=pParentParent->dataread_anybits(0x04,0,1);
	if(fan_en==1)
	{
		//fan_en=0
		pParentParent->dataupdate_anybits(0x04,0,L"0",1);
		Sleep(nSettleT);
		
	}

		//fan_en=1
		pParentParent->dataupdate_anybits(0x04,0,L"1",1);

		//get start time
		timeElasp = 0;
		startTime = GetTickCount();

		pParentParent->wreg(0x18,MnMaxDacRamp);
		//read FDAC
		FDAC = pParentParent->dataread_anybits(0x17,4,4);
		if (!success){return;};		

		while (timeElasp<nSettleT)
		{
			//check fault
			datbits = "0";// set pos_sns = 0
			pParentParent->dataupdate_anybits(0x01,3,datbits,1); 
			//read fault
			bFault = pParentParent->rreg( 0x19); // read fault
			if (!success){return;};
			bFault = ((bFault & 0x78) >> 3);
			// restore pos_sns
			pos_sns_reg=pParentParent->rreg(0x01); 
			pos_sns_reg |=(orig_pos_sns<<4);
			pParentParent->wreg(0x01,pos_sns_reg);
			if (bFault != 0)
			{
				//display msg
				errmsg.Format(_T("Error! Fault = %d"), bFault);
				pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
				pParentParent->wreg(0x18,orig_DAC);//set back orig speed
				return;
			}


			UseFWAdTorque(FDAC);

			//read FDAC
			FDAC = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};				

			endTime = GetTickCount();
			timeElasp = endTime - startTime;
		}

		//get start time
		timeElasp=0;
		startTime = GetTickCount();

		pParentParent->wreg(0x18,MnMinDacRamp);
		//read FDAC
		FDAC = pParentParent->dataread_anybits(0x17,4,4);
		if (!success){return;};		

		while (timeElasp < nSettleT)
		{
			//check fault
			datbits = "0";// set pos_sns = 0
			pParentParent->dataupdate_anybits(0x01,3,datbits,1); 
			//read fault
			bFault = pParentParent->rreg( 0x19); // read fault
			if (!success){return;};
			bFault = ((bFault & 0x78) >> 3);
			// restore pos_sns
			pos_sns_reg=pParentParent->rreg(0x01); 
			pos_sns_reg |=(orig_pos_sns<<4);
			pParentParent->wreg(0x01,pos_sns_reg);
			if (bFault != 0)
			{
				//display msg
				errmsg.Format(_T("Error! Fault = %d"), bFault);
				pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
				pParentParent->wreg(0x18,orig_DAC);//set back orig speed
				return;
			}

			UseFWAdTorque(FDAC);

			//read FDAC
			FDAC = pParentParent->dataread_anybits(0x17,4,4);
			if (!success){return;};				

			endTime = GetTickCount();
			timeElasp = endTime - startTime;
		}
	//}
		pParentParent->wreg(0x18,orig_DAC);//set back orig speed
}

void CFWTOR::UseFWAdTorque(int FinalDac)
{
	int currTor;
	int FWTor;
	int temp;

	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//get correct FW Adtor
	if ((FinalDac>=0)&&(FinalDac<0x2))//0-12.15%
	{
		FWTor=(MFWtorA_coarse<<2)|MFWtorA_fine;
	}
	else if ((FinalDac>=0x2)&&(FinalDac<0x4))//12.55%-
	{
		FWTor=(MFWtorB_coarse<<2)|MFWtorB_fine;
	}
	else if ((FinalDac>=0x4)&&(FinalDac<0x6))//25.1
	{
		FWTor=(MFWtorC_coarse<<2)|MFWtorC_fine;
	}
	else if ((FinalDac>=0x6)&&(FinalDac<0x8))//37.7
	{
		FWTor=(MFWtorD_coarse<<2)|MFWtorD_fine;
	}
	else if ((FinalDac>=0x8)&&(FinalDac<0xa))//50.2
	{
		FWTor=(MFWtorE_coarse<<2)|MFWtorE_fine;
	}
	else if ((FinalDac>=0xa)&&(FinalDac<0xc))//62.8
	{
		FWTor=(MFWtorF_coarse<<2)|MFWtorF_fine;
	}
	else if ((FinalDac>=0xc)&&(FinalDac<0xe))//75.3
	{
		FWTor=(MFWtorG_coarse<<2)|MFWtorG_fine;
	}
	else if ((FinalDac>=0xe)&&(FinalDac<=0xf))//87.9
	{
		FWTor=(MFWtorH_coarse<<2)|MFWtorH_fine;
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


void CFWTOR::OnBnClickedRadioInc()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Mode = 0;
}


void CFWTOR::OnBnClickedRadioDec()
{
	// TODO: Add your control notification handler code here
	m_RADIO_Mode = 1;
}
