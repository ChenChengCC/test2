// IntTest.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "IntTest.h"
#include "afxdialogex.h"
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
#include "SpdProfile.h"
#include "ReliabilityDlg.h"

//CFanmotorDlg use_fanmotordlg_intTest;
CdebugDlg use_Debugdlg_intTest;
CdetailDlg use_Detaildlg_intTest;

// CIntTest dialog

IMPLEMENT_DYNAMIC(CIntTest, CDialog)

CIntTest::CIntTest(CWnd* pParent /*=NULL*/)
	: CDialog(CIntTest::IDD, pParent)
	//, m_EDIT_TPOS1(_T(""))
	//, m_EDIT_TPOS2(_T(""))
	//, m_EDIT_TPOS3(_T(""))
	//, m_EDIT_TPOS4(_T(""))
	//, m_EDIT_TPOS5(_T(""))
	//, m_EDIT_TPOS6(_T(""))
	//, m_EDIT_TPOS_DELTA(_T(""))
	//, m_EDIT_TPOS1_star(_T(""))
	//, m_EDIT_TPOS2_star(_T(""))
	//, m_EDIT_TPOS3_star(_T(""))
	//, m_EDIT_TPOS5_star(_T(""))
	//, m_EDIT_TPOS6_star(_T(""))
	//, m_EDIT_TPOS4_star(_T(""))
	//, m_EDIT_TorCoarseA(_T(""))
	//, m_EDIT_TorCoarseB(_T(""))
	//, m_EDIT_TorCoarseC(_T(""))
	//, m_EDIT_TorCoarseD(_T(""))
	//, m_EDIT_TorCoarseE(_T(""))
	//, m_EDIT_TorCoarseF(_T(""))
	//, m_EDIT_TorCoarseG(_T(""))
	//, m_EDIT_TorCoarseH(_T(""))
	//, m_EDIT_TorFineA(_T(""))
	//, m_EDIT_TorFineB(_T(""))
	//, m_EDIT_TorFineC(_T(""))
	//, m_EDIT_TorFineD(_T(""))
	//, m_EDIT_TorFineE(_T(""))
	//, m_EDIT_TorFineF(_T(""))
	//, m_EDIT_TorFineG(_T(""))
	//, m_EDIT_TorFineH(_T(""))
{
      m_pParent=pParent;
}

CIntTest::~CIntTest()
{
}

void CIntTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_TPOS1, m_EDIT_TPOS1);
	//DDX_Text(pDX, IDC_EDIT_TPOS2, m_EDIT_TPOS2);
	//DDX_Text(pDX, IDC_EDIT_TPOS3, m_EDIT_TPOS3);
	//DDX_Text(pDX, IDC_EDIT_TPOS4, m_EDIT_TPOS4);
	//DDX_Text(pDX, IDC_EDIT_TPOS5, m_EDIT_TPOS5);
	//DDX_Text(pDX, IDC_EDIT_TPOS6, m_EDIT_TPOS6);
	//DDX_Text(pDX, IDC_EDIT_TPOS_DELTA, m_EDIT_TPOS_DELTA);
	//DDX_Text(pDX, IDC_EDIT_TPOS1_star, m_EDIT_TPOS1_star);
	//DDX_Text(pDX, IDC_EDIT_TPOS2_star, m_EDIT_TPOS2_star);
	//DDX_Text(pDX, IDC_EDIT_TPOS3_star, m_EDIT_TPOS3_star);
	////  DDX_Text(pDX, IDC_EDIT_TPOS4_star, m__EDIT_TPOS4_star);
	//DDX_Text(pDX, IDC_EDIT_TPOS5_star, m_EDIT_TPOS5_star);
	//DDX_Text(pDX, IDC_EDIT_TPOS6_star, m_EDIT_TPOS6_star);
	//DDX_Text(pDX, IDC_EDIT_TPOS4_star, m_EDIT_TPOS4_star);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseA, m_EDIT_TorCoarseA);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseB, m_EDIT_TorCoarseB);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseC, m_EDIT_TorCoarseC);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseD, m_EDIT_TorCoarseD);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseE, m_EDIT_TorCoarseE);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseF, m_EDIT_TorCoarseF);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseG, m_EDIT_TorCoarseG);
	//DDX_Text(pDX, IDC_EDIT_TorCoarseH, m_EDIT_TorCoarseH);
	//DDX_Text(pDX, IDC_EDIT_TorFineA, m_EDIT_TorFineA);
	//DDX_Text(pDX, IDC_EDIT_TorFineB, m_EDIT_TorFineB);
	//DDX_Text(pDX, IDC_EDIT_TorFineC, m_EDIT_TorFineC);
	//DDX_Text(pDX, IDC_EDIT_TorFineD, m_EDIT_TorFineD);
	//DDX_Text(pDX, IDC_EDIT_TorFineE, m_EDIT_TorFineE);
	//DDX_Text(pDX, IDC_EDIT_TorFineF, m_EDIT_TorFineF);
	//DDX_Text(pDX, IDC_EDIT_TorFineG, m_EDIT_TorFineG);
	//DDX_Text(pDX, IDC_EDIT_TorFineH, m_EDIT_TorFineH);
	//DDX_Control(pDX, IDC_CHECK_OTP1DONE_Test, m_CHECK_OTP1DONE_Test);
	//DDX_Control(pDX, IDC_EDIT_OSCTCTEST, m_EDIT_OSCTCTEST);
	//DDX_Control(pDX, IDC_EDIT_OSCOFFTEST, m_EDIT_OSCOFFTEST);
	//DDX_Control(pDX, IDC_EDIT_PINSELTEST, m_EDIT_PINSELTEST);
	//DDX_Control(pDX, IDC_EDIT_PWM_LOWTEST, m_EDIT_PWM_LOWTEST);
	//DDX_Control(pDX, IDC_EDIT_PWM_FLOATTEST, m_EDIT_PWM_FLOATTEST);
	//DDX_Control(pDX, IDC_EDIT_PWMFREQTEST, m_EDIT_PWMFREQTEST);
	//DDX_Control(pDX, IDC_EDIT_CHROMSELTEST, m_EDIT_CHROMSELTEST);
	//DDX_Control(pDX, IDC_EDIT_RETRY_TIMETEST, m_EDIT_RETRY_TIMETEST);
	//DDX_Control(pDX, IDC_CHECK_SWAPBC, m_CHECK_SWAPBC);
	//DDX_Control(pDX, IDC_CHECK_DLLOTP, m_CHECK_DLLOTP);
	//DDX_Control(pDX, IDC_CHECK_FFOTP, m_CHECK_FFOTP);
	//DDX_Control(pDX, IDC_CHECK_PMCOTP, m_CHECK_PMCOTP);
	//DDX_Control(pDX, IDC_CHECK_SKIP_S2, m_CHECK_SKIP_S2);
	//DDX_Control(pDX, IDC_CHECK_VARDACOTP, m_CHECK_VARDACOTP);
	//DDX_Control(pDX, IDC_CHECK_RETRY_ILIM_BRKOTP, m_CHECK_RETRY_ILIM_BRKOTP);
	//DDX_Control(pDX, IDC_CHECK_PWMFLOATDIS, m_CHECK_PWMFLOATDIS);
	//DDX_Control(pDX, IDC_CHECK_HP_ALARM_DIS, m_CHECK_HP_ALARM_DIS);
	//DDX_Control(pDX, IDC_CHECK_TRIPHASEOTP, m_CHECK_TRIPHASEOTP);
	//DDX_Control(pDX, IDC_CHECK_OTP_CRC_CHK_DIS, m_CHECK_OTP_CRC_CHK_DIS);
	//DDX_Control(pDX, IDC_CHECK_PWMOVROTP, m_CHECK_PWMOVROTP);
	//DDX_Control(pDX, IDC_CHECK_OFFBRKOTP, m_CHECK_OFFBRKOTP);
	//DDX_Control(pDX, IDC_CHECK_RETRY_TRISTATEOTP, m_CHECK_RETRY_TRISTATEOTP);
	//DDX_Control(pDX, IDC_CHECK_OTPCALDONE_Test, m_CHECK_OTPCALDONE_Test);
}


BEGIN_MESSAGE_MAP(CIntTest, CDialog)
	ON_WM_CLOSE()
//	ON_WM_DESTROY()
ON_WM_NCDESTROY()
ON_BN_CLICKED(IDC_BUTTON_ReadTPOS, &CIntTest::OnBnClickedButtonReadtpos)
ON_BN_CLICKED(IDC_BUTTON_AdtorExtract, &CIntTest::OnBnClickedButtonAdtorextract)
ON_BN_CLICKED(IDC_BUTTON_ReadOTPCAL, &CIntTest::OnBnClickedButtonReadotpcal)
ON_BN_CLICKED(IDC_BUTTON_DialogSpeedProfile, &CIntTest::OnBnClickedButtonDialogspeedprofile)
ON_BN_CLICKED(IDC_BUTTON_TPOS, &CIntTest::OnBnClickedButtonTpos)
ON_BN_CLICKED(IDC_BUTTON_AdTorque, &CIntTest::OnBnClickedButtonAdtorque)
ON_BN_CLICKED(IDC_BUTTON_OTPCAL_Read, &CIntTest::OnBnClickedButtonOtpcalRead)
ON_BN_CLICKED(IDC_BUTTON_DAC_Readback, &CIntTest::OnBnClickedButtonDacReadback)
ON_BN_CLICKED(IDC_BUTTON_Reliability, &CIntTest::OnBnClickedButtonReliability)
ON_BN_CLICKED(IDC_BUTTON_SpdRamp, &CIntTest::OnBnClickedButtonSpdramp)
END_MESSAGE_MAP()


// CIntTest message handlers


void CIntTest::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


//void CIntTest::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//	// TODO: Add your message handler code here
//}


void CIntTest::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


void CIntTest::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

}


void CIntTest::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

}


void CIntTest::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->inttest = NULL;
    delete this;
}


BOOL CIntTest::OnInitDialog()
{
	CDialog::OnInitDialog();
	//CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//int regval_temp,mask,OTP1_done, OTPCAL_done;

	//////debug
	////int x1=pParent->rreg(1);
	////int x2=pParent->rreg(2);

	////check otp1_done
	//regval_temp = pParent->rreg(0x1a);
	//mask=1;
	//OTP1_done=(regval_temp>>5)&mask;

	//if(OTP1_done==0)
	//{
	//	m_CHECK_OTP1DONE_Test.SetCheck(0);
	//}

	//else
	//{
	//	m_CHECK_OTP1DONE_Test.SetCheck(1);
	//}

	////check otpcal_done
	//regval_temp = pParent->rreg(0x1a);
	//mask=1;
	//OTPCAL_done=(regval_temp>>4)&mask;

	//if(OTPCAL_done==0)
	//{
	//	m_CHECK_OTPCALDONE_Test.SetCheck(0);
	//}

	//else
	//{
	//	m_CHECK_OTPCALDONE_Test.SetCheck(1);
	//}


	//m_EDIT_TorCoarseA.Format(_T("-"));
	//m_EDIT_TorFineA.Format(_T("-"));
	//m_EDIT_TorCoarseB.Format(_T("-"));
	//m_EDIT_TorFineB.Format(_T("-"));
	//m_EDIT_TorCoarseC.Format(_T("-"));
	//m_EDIT_TorFineC.Format(_T("-"));
	//m_EDIT_TorCoarseD.Format(_T("-"));
	//m_EDIT_TorFineD.Format(_T("-"));
	//m_EDIT_TorCoarseE.Format(_T("-"));
	//m_EDIT_TorFineE.Format(_T("-"));
	//m_EDIT_TorCoarseF.Format(_T("-"));
	//m_EDIT_TorFineF.Format(_T("-"));
	//m_EDIT_TorCoarseG.Format(_T("-"));
	//m_EDIT_TorFineG.Format(_T("-"));
	//m_EDIT_TorCoarseH.Format(_T("-"));
	//m_EDIT_TorFineH.Format(_T("-"));
	//UpdateData(FALSE);


	spdprofiledlg = NULL;
	tposdlg = NULL;
	adtorquedlg = NULL;
	otpcalreaddlg = NULL;
	dacreadbackdlg = NULL;
	reliabilitydlg = NULL;
	spdrampdlg =  NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CIntTest::OnBnClickedButtonReadtpos()
{
	// TODO: Add your control notification handler code here
		int pos_sns_temp = 0,pos_sns_update;
	int scomm_temp=0,scomm_update, scomm_readback=-1;
	int tpos_temp1, tpos_temp2, tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta=-1;
	int TPOS[10];
	int min_tpos=0,min_index=-1,min2_tpos=0,min2_index=-1,min3_tpos=0,min3_index=-1,min4_tpos=0,min4_index=-1,min5_tpos=0,min5_index=-1,min6_tpos=0,min6_index=-1;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	pos_sns_temp=pParent->rreg(0x01);//read original pos_sns bit
	scomm_temp=pParent->rreg(0x03);//read original scomm bit

	pos_sns_update= pos_sns_temp | 0x10;//set pos_sns bits to 1
	pParent->wreg(0x01,pos_sns_update);
	Sleep(2);//wait for 2ms

	//*************************TPOS1****************************
	scomm_update=scomm_temp&0x1F;//set scomm to 01h
	scomm_update|=0x20;
	pParent->wreg(0x03,scomm_update);// set scomm to 1h
	Sleep(2);//wait for 2ms

	scomm_readback=pParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos1 = (tpos_temp1<<8)+tpos_temp2;

	}
	else
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}
	

	//*************************TPOS2****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0x40;//set scomm to 02h
	pParent->wreg(0x03,scomm_update);
	Sleep(2);//wait for 2ms

	scomm_readback=pParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos2 = (tpos_temp1<<8)+tpos_temp2;

	}
	else
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

		//*************************TPOS3****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0x60;//set scomm to 03h
	pParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos3 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

	//*************************TPOS4****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0x80;//set scomm to 04h
	pParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos4 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

	//*************************TPOS5****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0xa0;//set scomm to 05h
	pParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos5 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}
	
			//*************************TPOS6****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0xc0;//set scomm to 06h
	pParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos6 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

//calculate tpos delta
		TPOS[0]=tpos1;
		TPOS[1]=tpos2;
		TPOS[2]=tpos3;
		TPOS[3]=tpos4;
		TPOS[4]=tpos5;
		TPOS[5]=tpos6;

		for (int i =0; i <6; i++)// find the min value and index
		{
			if (min_tpos==0) 
			{
				min_tpos=TPOS[i];
				min_index = i;
			}

			if(TPOS[i]<min_tpos)
			{
				min_tpos=TPOS[i];	
				min_index = i;
			}
		}

		switch (min_index)//add star
		{
		case 0:
			m_EDIT_TPOS1_star.Format(_T("*"));
			break;
		case 1:
			m_EDIT_TPOS2_star.Format(_T("*"));
			break;
		case 2:
			m_EDIT_TPOS3_star.Format(_T("*"));
			break;
		case 3:
			m_EDIT_TPOS4_star.Format(_T("*"));
			break;
		case 4:
			m_EDIT_TPOS5_star.Format(_T("*"));
			break;
		case 5:
			m_EDIT_TPOS6_star.Format(_T("*"));
			break;
		}

		for (int i =0; i <6; i++)// find 2nd min value and index
		{
			if (i==min_index) continue;

			if (min2_tpos==0) 
			{
				min2_tpos=TPOS[i];
				min2_index = i;
			}

			if(TPOS[i]<min2_tpos)
			{
				min2_tpos=TPOS[i];	
				min2_index = i;
			}
		}


		switch (min2_index)//add 2 stars
		{
		case 0:
			m_EDIT_TPOS1_star.Format(_T("**"));
			break;
		case 1:
			m_EDIT_TPOS2_star.Format(_T("**"));
			break;
		case 2:
			m_EDIT_TPOS3_star.Format(_T("**"));
			break;
		case 3:
			m_EDIT_TPOS4_star.Format(_T("**"));
			break;
		case 4:
			m_EDIT_TPOS5_star.Format(_T("**"));
			break;
		case 5:
			m_EDIT_TPOS6_star.Format(_T("**"));
			break;
		}

		
		for (int i =0; i <6; i++)// find 3rd min value and index
		{
			if ((i==min_index)||(i==min2_index)) continue;

			if (min3_tpos==0) 
			{
				min3_tpos=TPOS[i];
				min3_index = i;
			}

			if(TPOS[i]<min3_tpos)
			{
				min3_tpos=TPOS[i];	
				min3_index = i;
			}
		}

		switch (min3_index)//add 3 stars
		{
		case 0:
			m_EDIT_TPOS1_star.Format(_T("***"));
			break;
		case 1:
			m_EDIT_TPOS2_star.Format(_T("***"));
			break;
		case 2:
			m_EDIT_TPOS3_star.Format(_T("***"));
			break;
		case 3:
			m_EDIT_TPOS4_star.Format(_T("***"));
			break;
		case 4:
			m_EDIT_TPOS5_star.Format(_T("***"));
			break;
		case 5:
			m_EDIT_TPOS6_star.Format(_T("***"));
			break;
		}

		
		for (int i =0; i <6; i++)// find 4th min value and index
		{
			if ((i==min_index)||(i==min2_index)||(i==min3_index)) continue;

			if (min4_tpos==0) 
			{
				min4_tpos=TPOS[i];
				min4_index = i;
			}

			if(TPOS[i]<min4_tpos)
			{
				min4_tpos=TPOS[i];	
				min4_index = i;
			}
		}

		switch (min4_index)//add 4 stars
		{
		case 0:
			m_EDIT_TPOS1_star.Format(_T("****"));
			break;
		case 1:
			m_EDIT_TPOS2_star.Format(_T("****"));
			break;
		case 2:
			m_EDIT_TPOS3_star.Format(_T("****"));
			break;
		case 3:
			m_EDIT_TPOS4_star.Format(_T("****"));
			break;
		case 4:
			m_EDIT_TPOS5_star.Format(_T("****"));
			break;
		case 5:
			m_EDIT_TPOS6_star.Format(_T("****"));
			break;
		}

		for (int i =0; i <6; i++)// find 5th min value and index
		{
			if ((i==min_index)||(i==min2_index)||(i==min3_index)||(i==min4_index)) continue;

			if (min5_tpos==0) 
			{
				min5_tpos=TPOS[i];
				min5_index = i;
			}

			if(TPOS[i]<min5_tpos)
			{
				min5_tpos=TPOS[i];	
				min5_index = i;
			}
		}

		switch (min5_index)//add 5 stars
		{
		case 0:
			m_EDIT_TPOS1_star.Format(_T("*****"));
			break;
		case 1:
			m_EDIT_TPOS2_star.Format(_T("*****"));
			break;
		case 2:
			m_EDIT_TPOS3_star.Format(_T("*****"));
			break;
		case 3:
			m_EDIT_TPOS4_star.Format(_T("*****"));
			break;
		case 4:
			m_EDIT_TPOS5_star.Format(_T("*****"));
			break;
		case 5:
			m_EDIT_TPOS6_star.Format(_T("*****"));
			break;
		}

		for (int i =0; i <6; i++)// find 6th min value and index
		{
			if ((i==min_index)||(i==min2_index)||(i==min3_index)||(i==min4_index)||(i==min5_index)) continue;

			if (min6_tpos==0) 
			{
				min6_tpos=TPOS[i];
				min6_index = i;
			}
		}

		switch (min6_index)//add 6 stars
		{
		case 0:
			m_EDIT_TPOS1_star.Format(_T("******"));
			break;
		case 1:
			m_EDIT_TPOS2_star.Format(_T("******"));
			break;
		case 2:
			m_EDIT_TPOS3_star.Format(_T("******"));
			break;
		case 3:
			m_EDIT_TPOS4_star.Format(_T("******"));
			break;
		case 4:
			m_EDIT_TPOS5_star.Format(_T("******"));
			break;
		case 5:
			m_EDIT_TPOS6_star.Format(_T("******"));
			break;
		}


		tpos_delta=min2_tpos-min_tpos;

	//******************update display value**********************
	m_EDIT_TPOS1.Format(_T("%d"),tpos1);
	m_EDIT_TPOS2.Format(_T("%d"),tpos2);
	m_EDIT_TPOS3.Format(_T("%d"),tpos3);
	m_EDIT_TPOS4.Format(_T("%d"),tpos4);
	m_EDIT_TPOS5.Format(_T("%d"),tpos5);
	m_EDIT_TPOS6.Format(_T("%d"),tpos6);
	m_EDIT_TPOS_DELTA.Format(_T("%d"),tpos_delta);
	UpdateData(FALSE);

	pParent->wreg(0x01,pos_sns_temp);//restore original pos_sns bit
	pParent->wreg(0x03,scomm_temp);//restore original scomm bit

}


void CIntTest::OnBnClickedButtonAdtorextract()
{
	int regval_temp, mask;
	int OTP1_done,pwm_reg_sel_orig;
	CString datbits;
	int torque_temp, torque_temp1, torA_coarse, torA_fine, torB_coarse, torB_fine,torC_coarse, torC_fine,torD_coarse, torD_fine,torE_coarse, torE_fine,torF_coarse, torF_fine,torG_coarse, torG_fine,torH_coarse, torH_fine;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	regval_temp = pParent->rreg(0x1a);
    if (!success) return;
	mask=1;
	OTP1_done=(regval_temp>>5)&mask;

	if(OTP1_done==0)
	{
		m_CHECK_OTP1DONE_Test.SetCheck(0);
		//display
		m_EDIT_TorCoarseA.Format(_T("-"));
		m_EDIT_TorFineA.Format(_T("-"));
		m_EDIT_TorCoarseB.Format(_T("-"));
		m_EDIT_TorFineB.Format(_T("-"));
		m_EDIT_TorCoarseC.Format(_T("-"));
		m_EDIT_TorFineC.Format(_T("-"));
		m_EDIT_TorCoarseD.Format(_T("-"));
		m_EDIT_TorFineD.Format(_T("-"));
		m_EDIT_TorCoarseE.Format(_T("-"));
		m_EDIT_TorFineE.Format(_T("-"));
		m_EDIT_TorCoarseF.Format(_T("-"));
		m_EDIT_TorFineF.Format(_T("-"));
		m_EDIT_TorCoarseG.Format(_T("-"));
		m_EDIT_TorFineG.Format(_T("-"));
		m_EDIT_TorCoarseH.Format(_T("-"));
		m_EDIT_TorFineH.Format(_T("-"));
		UpdateData(FALSE);
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP1 have not been burnt!");
		return;
	}

	else
	{
		if (pParent->virtual_board)
		{
			m_CHECK_OTP1DONE_Test.SetCheck(1);
			pParent->fOTP=1;//reg R/W hand over to OTP array

			// readback OTP torque values
			torque_temp=pParent->rreg(0x01);
			torque_temp1=pParent->rreg(0x02);
			torA_coarse = (((torque_temp>>1)& 0x03)<<1) | (torque_temp1>>7);
			torA_fine = (torque_temp1>>5) & 0x03;

			
			torque_temp=pParent->rreg(0x03);
			torB_coarse = (torque_temp>>2) & 0x07;
			torB_fine = torque_temp & 0x03;

			
			torque_temp=pParent->rreg(0x13);
			torC_coarse = (torque_temp>>4) & 0x07;
			torC_fine = (torque_temp>>2) & 0x03;

			
			torque_temp=pParent->rreg(0x13);
			torque_temp1=pParent->rreg(0x15);
			torD_coarse = (((torque_temp>>1) & 0x01)<<2) | (torque_temp1>>6);
			torD_fine = (torque_temp1>>4) & 0x03;

			
			torque_temp=pParent->rreg(0x15);
			torque_temp1=pParent->rreg(0x18);
			torE_coarse = (torque_temp>>1) & 0x07;
			torE_fine = ((torque_temp & 0x01)<<1) | (torque_temp1>>7);

			
			torque_temp=pParent->rreg(0x18);
			torF_coarse = (torque_temp>>4) & 0x07;
			torF_fine = (torque_temp>>2) & 0x03;

			
			torque_temp=pParent->rreg(0x18);
			torque_temp1=pParent->rreg(0x1B);
			torG_coarse = ((torque_temp & 0x03)<<1) | (torque_temp1>>7);
			torG_fine = (torque_temp1>>5) & 0x03;

			
			torque_temp=pParent->rreg(0x1B);
			torH_coarse = (torque_temp>>2) & 0x07;
			torH_fine = torque_temp & 0x03;

			//display
			m_EDIT_TorCoarseA.Format(_T("%x"),torA_coarse);
			m_EDIT_TorFineA.Format(_T("%x"),torA_fine);
			m_EDIT_TorCoarseB.Format(_T("%x"),torB_coarse);
			m_EDIT_TorFineB.Format(_T("%x"),torB_fine);
			m_EDIT_TorCoarseC.Format(_T("%x"),torC_coarse);
			m_EDIT_TorFineC.Format(_T("%x"),torC_fine);
			m_EDIT_TorCoarseD.Format(_T("%x"),torD_coarse);
			m_EDIT_TorFineD.Format(_T("%x"),torD_fine);
			m_EDIT_TorCoarseE.Format(_T("%x"),torE_coarse);
			m_EDIT_TorFineE.Format(_T("%x"),torE_fine);
			m_EDIT_TorCoarseF.Format(_T("%x"),torF_coarse);
			m_EDIT_TorFineF.Format(_T("%x"),torF_fine);
			m_EDIT_TorCoarseG.Format(_T("%x"),torG_coarse);
			m_EDIT_TorFineG.Format(_T("%x"),torG_fine);
			m_EDIT_TorCoarseH.Format(_T("%x"),torH_coarse);
			m_EDIT_TorFineH.Format(_T("%x"),torH_fine);
			UpdateData(FALSE);

		}
		else
		{
			m_CHECK_OTP1DONE_Test.SetCheck(1);
			////set i2c_en to 1
			pParent->wreg(0x2a,6);
			pParent->wreg(0x3d,5);

			pwm_reg_sel_orig = pParent->rreg(0x02);
			if (!success) return;

			//set pwm_reg to 1.	pwmin_sel to 0
			datbits = "1";
			pParent->dataupdate_anybits(0x02,1,datbits,1);
			datbits = "0";
			pParent->dataupdate_anybits(0x0a,0,datbits,1);

			// readback OTP torque values
			pParent->wreg(0x18,0x0);
			torque_temp=pParent->rreg(0x03);
			torA_coarse = (torque_temp>>2) & 0x07;
			torA_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0x20);
			torque_temp=pParent->rreg(0x03);
			torB_coarse = (torque_temp>>2) & 0x07;
			torB_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0x40);
			torque_temp=pParent->rreg(0x03);
			torC_coarse = (torque_temp>>2) & 0x07;
			torC_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0x60);
			torque_temp=pParent->rreg(0x03);
			torD_coarse = (torque_temp>>2) & 0x07;
			torD_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0x80);
			torque_temp=pParent->rreg(0x03);
			torE_coarse = (torque_temp>>2) & 0x07;
			torE_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0xa0);
			torque_temp=pParent->rreg(0x03);
			torF_coarse = (torque_temp>>2) & 0x07;
			torF_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0xc0);
			torque_temp=pParent->rreg(0x03);
			torG_coarse = (torque_temp>>2) & 0x07;
			torG_fine = torque_temp & 0x03;

			pParent->wreg(0x18,0xe0);
			torque_temp=pParent->rreg(0x03);
			torH_coarse = (torque_temp>>2) & 0x07;
			torH_fine = torque_temp & 0x03;

			//display
			m_EDIT_TorCoarseA.Format(_T("%x"),torA_coarse);
			m_EDIT_TorFineA.Format(_T("%x"),torA_fine);
			m_EDIT_TorCoarseB.Format(_T("%x"),torB_coarse);
			m_EDIT_TorFineB.Format(_T("%x"),torB_fine);
			m_EDIT_TorCoarseC.Format(_T("%x"),torC_coarse);
			m_EDIT_TorFineC.Format(_T("%x"),torC_fine);
			m_EDIT_TorCoarseD.Format(_T("%x"),torD_coarse);
			m_EDIT_TorFineD.Format(_T("%x"),torD_fine);
			m_EDIT_TorCoarseE.Format(_T("%x"),torE_coarse);
			m_EDIT_TorFineE.Format(_T("%x"),torE_fine);
			m_EDIT_TorCoarseF.Format(_T("%x"),torF_coarse);
			m_EDIT_TorFineF.Format(_T("%x"),torF_fine);
			m_EDIT_TorCoarseG.Format(_T("%x"),torG_coarse);
			m_EDIT_TorFineG.Format(_T("%x"),torG_fine);
			m_EDIT_TorCoarseH.Format(_T("%x"),torH_coarse);
			m_EDIT_TorFineH.Format(_T("%x"),torH_fine);
			UpdateData(FALSE);

			//restore original pwm selection
			pParent->wreg(0x02,pwm_reg_sel_orig);

		}//virtual_board=false
	}//otp1_done=1
}


void CIntTest::OnBnClickedButtonReadotpcal()
{
	// TODO: Add your control notification handler code here
	int regval;
	int mask;
	CString datbits;
	int osc_offset,osc_tc,profile_sel,pwm_low,pwm_float, pwm_freq, fast_vardac, retry_time, pwm_float_dis,hp_alarm_dis,triphase_det_en, otp_crc_chk_dis, pwm_nonoverlap_dis,fan_en_off_brk,retry_tristate, swap_BC, dll_en, ff_en, PWC_en, pmc_en,
		skip_s2, vardac_en, retry_ilim_brk;
	int OTPCAL_done;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	regval = pParent->rreg(0x1a);
    if (!success) return;
	mask=1;
	OTPCAL_done=(regval>>4)&mask;

	if(OTPCAL_done==0)
	{
		m_CHECK_OTPCALDONE_Test.SetCheck(0);
		pParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTPCAL have not been burnt!");
		return;
	}

	else
	{
		m_CHECK_OTPCALDONE_Test.SetCheck(1);

		regval = pParent->rreg(0x1b);
		if (!success){return;};
		mask=31;
		osc_offset=regval&mask;
		mask=7;
		osc_tc=(regval>>5)&mask; 

		int otp_cal_reg=pParent->dataread_anybits(0x01,7,1); //save otp_cal_sel
		CString otpcal_temp=pParent->int2bin_anybits(otp_cal_reg,1);

		datbits = "1";//set otp_cal_sel=1
		pParent->dataupdate_anybits(0x01,7,datbits,1);

		regval = pParent->rreg(0x04);
		if (!success){return;};
		mask=1;
		dll_en=(regval>>3)&mask;
		ff_en=(regval>>2)&mask;

		regval = pParent->rreg(0x08);
		if (!success){return;};
		mask=1;
		triphase_det_en=(regval>>7)&mask;
		pmc_en=(regval>>6)&mask;

		regval = pParent->rreg(0x10);
		if (!success){return;};
		mask=1;
		vardac_en=(regval>>6)&mask;

		regval = pParent->rreg(0x0b);
		if (!success){return;};
		mask=1;
		pwm_nonoverlap_dis=(regval>>7)&mask;

		regval = pParent->rreg(0x11);
		if (!success){return;};
		mask=1;
		pwm_freq=(regval>>6)&mask;

		regval = pParent->rreg(0x18);
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

		int pos_sns=pParent->dataread_anybits(0x01,3,1); //save pos_sns
		CString pos_sns_temp=pParent->int2bin_anybits(pos_sns,1);

		datbits = "1";//set pos_sns=1
		pParent->dataupdate_anybits(0x01,3,datbits,1);

		regval = pParent->rreg(0x15);
		if (!success){return;};
		mask=1;
		fan_en_off_brk=(regval>>7)&mask;
		fast_vardac=(regval>>6)&mask;
		otp_crc_chk_dis=(regval>>5)&mask;
		skip_s2=(regval>>4)&mask;
		mask=3;
		pwm_low=(regval>>2)&mask;
		pwm_float=regval&mask;

		pParent->dataupdate_anybits(0x01,3,pos_sns_temp,1);//original pos_sns      
		pParent->dataupdate_anybits(0x01,7,otpcal_temp,1); //original otp_cal_sel

	}

}


void CIntTest::OnBnClickedButtonDialogspeedprofile()
{
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// TODO: Add your control notification handler code here
	if(spdprofiledlg)
	{
		spdprofiledlg->SetForegroundWindow();
	}
	else
	{		
		//spdprofiledlg = new CSpdProfile(this);
		//spdprofiledlg->Create(IDD_DIALOG_SPD_PROFILE,GetDesktopWindow());
		//spdprofiledlg->ShowWindow(SW_SHOW);
		spdprofiledlg = new CSpdProfile(this);
		spdprofiledlg->Create(IDD_DIALOG_SPD_PROFILE,GetDesktopWindow());
		spdprofiledlg->ShowWindow(SW_SHOW);
		//pParent->inttest->ShowWindow(SW_HIDE);
		//spdprofiledlg->SetForegroundWindow();
	}
}


void CIntTest::OnBnClickedButtonTpos()
{
	// TODO: Add your control notification handler code here
	if(tposdlg)
	{
		tposdlg->SetForegroundWindow();
	}
	else
	{		
		tposdlg = new CTposDlg(this);
		tposdlg->Create(IDD_DIALOG_TPOS,GetDesktopWindow());
		tposdlg->ShowWindow(SW_SHOW);
	}
}


void CIntTest::OnBnClickedButtonAdtorque()
{
	// TODO: Add your control notification handler code here
	if(adtorquedlg)
	{
		adtorquedlg->SetForegroundWindow();
	}
	else
	{		
		adtorquedlg = new CAdTorqueDlg(this);
		adtorquedlg->Create(IDD_DIALOG_AD_TORQUE,GetDesktopWindow());
		adtorquedlg->ShowWindow(SW_SHOW);
	}
}


void CIntTest::OnBnClickedButtonOtpcalRead()
{
	// TODO: Add your control notification handler code here
	if(otpcalreaddlg)
	{
		otpcalreaddlg->SetForegroundWindow();
	}
	else
	{		
		otpcalreaddlg = new COTPCALReadDlg(this);
		otpcalreaddlg->Create(IDD_DIALOG_OTPCAL_RD,GetDesktopWindow());
		otpcalreaddlg->ShowWindow(SW_SHOW);
	}
}


void CIntTest::OnBnClickedButtonDacReadback()
{
	// TODO: Add your control notification handler code here
	if(dacreadbackdlg)
	{
		dacreadbackdlg->SetForegroundWindow();
	}
	else
	{		
		dacreadbackdlg = new CDacReadback(this);
		dacreadbackdlg->Create(IDD_DIALOG_DacReadback,GetDesktopWindow());
		dacreadbackdlg->ShowWindow(SW_SHOW);
	}
}


void CIntTest::OnBnClickedButtonReliability()
{
	// TODO: Add your control notification handler code here
	if(reliabilitydlg)
	{
		reliabilitydlg->SetForegroundWindow();
	}
	else
	{		
		reliabilitydlg = new CReliabilityDlg(this);
		reliabilitydlg->Create(IDD_DIALOG_RELIABILITY,GetDesktopWindow());
		reliabilitydlg->ShowWindow(SW_SHOW);
	}
}


void CIntTest::OnBnClickedButtonSpdramp()
{
	// TODO: Add your control notification handler code here
	if(spdrampdlg)
	{
		spdrampdlg->SetForegroundWindow();
	}
	else
	{		
		spdrampdlg = new CSpdRamp(this);
		spdrampdlg->Create(IDD_DIALOG_SP_RAMP,GetDesktopWindow());
		spdrampdlg->ShowWindow(SW_SHOW);
	}
}
