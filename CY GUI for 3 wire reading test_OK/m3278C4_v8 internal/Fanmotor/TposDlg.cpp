// TposDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "TposDlg.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"

// CTposDlg dialog
extern double ilim0,ilim1,ilim2,ilim3,ilim4,ilim5,ilim6,ilim7,ilim8,ilim9,ilim10,ilim11,ilim12,ilim13,ilim14,ilim15;
int tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta=-1;

IMPLEMENT_DYNAMIC(CTposDlg, CDialog)

CTposDlg::CTposDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTposDlg::IDD, pParent)
	, m_EDIT_TPOS1(_T(""))
	, m_EDIT_TPOS2(_T(""))
	, m_EDIT_TPOS3(_T(""))
	, m_EDIT_TPOS4(_T(""))
	, m_EDIT_TPOS5(_T(""))
	, m_EDIT_TPOS6(_T(""))
	, m_EDIT_TPOS_DELTA(_T(""))
	, m_EDIT_TPOS1_star(_T(""))
	, m_EDIT_TPOS2_star(_T(""))
	, m_EDIT_TPOS3_star(_T(""))
	, m_EDIT_TPOS4_star(_T(""))
	, m_EDIT_TPOS5_star(_T(""))
	, m_EDIT_TPOS6_star(_T(""))
	, m_EDIT_TPOS_ILIMIT_IS1(_T(""))
{
	m_pParent=pParent;
}

CTposDlg::~CTposDlg()
{
}

void CTposDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_TPOS1, m_EDIT_TPOS1);
	DDX_Text(pDX, IDC_EDIT_TPOS1, m_EDIT_TPOS1);
	DDX_Text(pDX, IDC_EDIT_TPOS2, m_EDIT_TPOS2);
	DDX_Text(pDX, IDC_EDIT_TPOS3, m_EDIT_TPOS3);
	DDX_Text(pDX, IDC_EDIT_TPOS4, m_EDIT_TPOS4);
	DDX_Text(pDX, IDC_EDIT_TPOS5, m_EDIT_TPOS5);
	DDX_Text(pDX, IDC_EDIT_TPOS6, m_EDIT_TPOS6);
	DDX_Text(pDX, IDC_EDIT_TPOS_DELTA, m_EDIT_TPOS_DELTA);
	DDX_Text(pDX, IDC_EDIT_TPOS1_star, m_EDIT_TPOS1_star);
	DDX_Text(pDX, IDC_EDIT_TPOS2_star, m_EDIT_TPOS2_star);
	DDX_Text(pDX, IDC_EDIT_TPOS3_star, m_EDIT_TPOS3_star);
	DDX_Text(pDX, IDC_EDIT_TPOS4_star, m_EDIT_TPOS4_star);
	DDX_Text(pDX, IDC_EDIT_TPOS5_star, m_EDIT_TPOS5_star);
	DDX_Text(pDX, IDC_EDIT_TPOS6_star, m_EDIT_TPOS6_star);
	DDX_Text(pDX, IDC_EDIT_TPOS_ILIMIT_IS1, m_EDIT_TPOS_ILIMIT_IS1);
}


BEGIN_MESSAGE_MAP(CTposDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_ReadTPOS, &CTposDlg::OnBnClickedButtonReadtpos)
	ON_BN_CLICKED(IDC_BUTTON_SCOMM_TPOS, &CTposDlg::OnBnClickedButtonScommTpos)
END_MESSAGE_MAP()


// CTposDlg message handlers


void CTposDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


void CTposDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


void CTposDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	((CIntTest*)m_pParent)->tposdlg = NULL;
    delete this;
}


BOOL CTposDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int blind_spin_en,ilimit_auto_is;
	CString datbits;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//read ilimit_auto_is and display
	blind_spin_en = ((pParentParent->rreg(0x04))>>5) & 1;
	if (blind_spin_en!=0)
	{
		datbits = "0";
		pParentParent->dataupdate_anybits(0x04,2,datbits,1); // set blind_spin_en = 0

		ilimit_auto_is=((pParentParent->rreg(0x0d))>>4) & 0x0f;

		datbits = "1";
		pParentParent->dataupdate_anybits(0x04,2,datbits,1); // set blind_spin_en = 1
	}
	else
		ilimit_auto_is=((pParentParent->rreg(0x0d))>>4) & 0x0f;

	this->DisplayIlimitIs(ilimit_auto_is);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTposDlg::DisplayIlimitIs(int ilimit_is)
{
	CString errmsg;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	if (ilim0==-1)
	{
		errmsg.Format(_T("Please set ilimit value at Detail Window!"));
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
		return;
	}

	switch (ilimit_is)
	{
		case 0:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("0h: %.2f A"),ilim0);
			break;
		case 1:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("1h: %.2f A"),ilim1);
			break;
		case 2:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("2h: %.2f A"),ilim2);
			break;
		case 3:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("3h: %.2f A"),ilim3);
			break;
		case 4:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("4h: %.2f A"),ilim4);
			break;
		case 5:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("5h: %.2f A"),ilim5);
			break;
		case 6:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("6h: %.2f A"),ilim6);
			break;
		case 7:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("7h: %.2f A"),ilim7);
			break;
		case 8:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("8h: %.2f A"),ilim8);
			break;
		case 9:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("9h: %.2f A"),ilim9);
			break;
		case 0x0a:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("Ah: %.2f A"),ilim10);
			break;
		case 0x0b:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("Bh: %.2f A"),ilim11);
			break;
		case 0x0c:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("Ch: %.2f A"),ilim12);
			break;
		case 0x0d:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("Dh: %.2f A"),ilim13);
			break;
		case 0x0e:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("Eh: %.2f A"),ilim14);
			break;
		case 0x0f:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("Fh: %.2f A"),ilim15);
			break;
		default:
			m_EDIT_TPOS_ILIMIT_IS1.Format(_T("-"));
	}

	UpdateData(FALSE);
}

void CTposDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}


void CTposDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}


void CTposDlg::OnBnClickedButtonReadtpos()
{
	// TODO: Add your control notification handler code here
	int pos_sns_temp = 0,pos_sns_update;
	int scomm_temp=0,scomm_update, scomm_readback=-1;
	int fan_en_off_brk_dis_temp,fan_en_off_brk_dis_update;
	int ilimit_temp,ilimit_auto_is;
	int blind_spin_en;
	int tpos_temp1, tpos_temp2;
	int TPOS[10];
	int min_tpos=0,min_index=-1,min2_tpos=0,min2_index=-1,min3_tpos=0,min3_index=-1,min4_tpos=0,min4_index=-1,min5_tpos=0,min5_index=-1,min6_tpos=0,min6_index=-1;
	CString datbits;
	int temp;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	pos_sns_temp=pParentParent->rreg(0x01);//read original pos_sns bit
	scomm_temp=pParentParent->rreg(0x03);//read original scomm bit
	fan_en_off_brk_dis_temp=pParentParent->rreg(0x14);//read original fan_en_off_brk_dis bit
	ilimit_temp=pParentParent->rreg(0x0c);//read original ilimit bit

	//read ilimit_auto_is and display
	blind_spin_en = ((pParentParent->rreg(0x04))>>5) & 1;
	if (blind_spin_en!=0)
	{
		datbits = "0";
		pParentParent->dataupdate_anybits(0x04,2,datbits,1); // set blind_spin_en = 0

		ilimit_auto_is=((pParentParent->rreg(0x0d))>>4) & 0x0f;

		datbits = "1";
		pParentParent->dataupdate_anybits(0x04,2,datbits,1); // set blind_spin_en = 1
	}
	else
		ilimit_auto_is=((pParentParent->rreg(0x0d))>>4) & 0x0f;

	DisplayIlimitIs(ilimit_auto_is);


	//set ilimit_auto_is value to ilimit
	temp = pParentParent->rreg(0x0c);
	temp &= 0x0f;
	temp|=(ilimit_auto_is<<4);
	pParentParent->wreg(0x0c,temp);

	//set fan_en_off_brk_dis=1
	fan_en_off_brk_dis_update = fan_en_off_brk_dis_temp | 0x10;
	pParentParent->wreg(0x14,fan_en_off_brk_dis_update);

	//set pos_sns bits to 1
	pos_sns_update= pos_sns_temp | 0x10;
	pParentParent->wreg(0x01,pos_sns_update);

	//off fan_en
	pParentParent->dataupdate_anybits(0x04,0,L"0",1); 

	Sleep(2);//wait for 2ms

	//*************************TPOS1****************************
	scomm_update=scomm_temp&0x1F;//set scomm to 01h
	scomm_update|=0x20;
	pParentParent->wreg(0x03,scomm_update);// set scomm to 1h
	Sleep(2);//wait for 2ms

	scomm_readback=pParentParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos1 = (tpos_temp1<<8)+tpos_temp2;

	}
	else
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}
	

	//*************************TPOS2****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0x40;//set scomm to 02h
	pParentParent->wreg(0x03,scomm_update);
	Sleep(2);//wait for 2ms

	scomm_readback=pParentParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos2 = (tpos_temp1<<8)+tpos_temp2;

	}
	else
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

		//*************************TPOS3****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0x60;//set scomm to 03h
	pParentParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParentParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos3 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

	//*************************TPOS4****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0x80;//set scomm to 04h
	pParentParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParentParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos4 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}

	//*************************TPOS5****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0xa0;//set scomm to 05h
	pParentParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParentParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos5 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
	}
	
			//*************************TPOS6****************************
	scomm_update=scomm_temp&0x1F;
	scomm_update|=0xc0;//set scomm to 06h
	pParentParent->wreg(0x03,scomm_update);
	Sleep(2);

	scomm_readback=pParentParent->rreg(0x03)>>5;
	if (scomm_readback==0)
	{
		tpos_temp1 = pParentParent->dataread_anybits(0x17,4,4);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}
		tpos_temp2 = pParentParent->dataread_anybits(0x16,0,8);
		if (!success) 
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
			return;
		}

		tpos6 = (tpos_temp1<<8)+tpos_temp2;//

	}
	else
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"ILIMIT is too high!");
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

	pParentParent->wreg(0x01,pos_sns_temp);//restore original pos_sns bit
	pParentParent->wreg(0x03,scomm_temp);//restore original scomm bit
	pParentParent->wreg(0x14,fan_en_off_brk_dis_temp);//restore original fan_en_off_brk_dis bit
	pParentParent->wreg(0x0c,ilimit_temp);//restore original ilimit bit
}


void CTposDlg::OnBnClickedButtonScommTpos()
{

	int i=0,j=0;
	errno_t err;
	FILE *fpo;
	const TCHAR* fpo_name = L"SCOMM TPOS TEST.xls";

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//create xls file	
	if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
		fclose(fpo);
		return;
	};

	fprintf( fpo, "SCOMM\tTPOS1\tTPOS2\tTPOS3\tTPOS4\tTPOS5\tTPOS6\tDELTA\n");

	i=0;
	
	while(i<2)
	{
		//set SCOMM=001b, AB
		pParentParent->dataupdate_anybits(0x03,0,L"001",3);
		Sleep(5000);
		//set SCOMM=000, tri
		pParentParent->dataupdate_anybits(0x03,0,L"000",3);
		Sleep(2000);
		//read tpos
		j=0;
		while(j<10)
		{
			OnBnClickedButtonReadtpos();
			Sleep(2000);
			j++;
		}
		//write in xls file
		fprintf( fpo, "AB\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta);

	
		//set SCOMM=001b, AC
		pParentParent->dataupdate_anybits(0x03,0,L"010",3);
		Sleep(5000);
		//set SCOMM=000, tri
		pParentParent->dataupdate_anybits(0x03,0,L"000",3);
		Sleep(2000);
		//read tpos
		j=0;
		while(j<10)
		{
			OnBnClickedButtonReadtpos();
			Sleep(2000);
			j++;
		}
		//write in xls file
		fprintf( fpo, "AC\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta);

		//set SCOMM=001b, BC
		pParentParent->dataupdate_anybits(0x03,0,L"011",3);
		Sleep(5000);
		//set SCOMM=000, tri
		pParentParent->dataupdate_anybits(0x03,0,L"000",3);
		Sleep(2000);
		//read tpos
		j=0;
		while(j<10)
		{
			OnBnClickedButtonReadtpos();
			Sleep(2000);
			j++;
		}
		//write in xls file
		fprintf( fpo, "BC\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta);

		//set SCOMM=001b, BA
		pParentParent->dataupdate_anybits(0x03,0,L"100",3);
		Sleep(5000);
		//set SCOMM=000, tri
		pParentParent->dataupdate_anybits(0x03,0,L"000",3);
		Sleep(2000);
		//read tpos
		j=0;
		while(j<10)
		{
			OnBnClickedButtonReadtpos();
			Sleep(2000);
			j++;
		}
		//write in xls file
		fprintf( fpo, "BA\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta);

		//set SCOMM=001b, CA
		pParentParent->dataupdate_anybits(0x03,0,L"101",3);
		Sleep(5000);
		//set SCOMM=000, tri
		pParentParent->dataupdate_anybits(0x03,0,L"000",3);
		Sleep(2000);
		//read tpos
		j=0;
		while(j<10)
		{
			OnBnClickedButtonReadtpos();
			Sleep(2000);
			j++;
		}
		//write in xls file
		fprintf( fpo, "CA\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta);

		//set SCOMM=001b, CB
		pParentParent->dataupdate_anybits(0x03,0,L"110",3);
		Sleep(5000);
		//set SCOMM=000, tri
		pParentParent->dataupdate_anybits(0x03,0,L"000",3);
		Sleep(2000);
		//read tpos
		j=0;
		while(j<10)
		{
			OnBnClickedButtonReadtpos();
			Sleep(2000);
			j++;
		}
		//write in xls file
		fprintf( fpo, "CB\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tpos1,tpos2,tpos3,tpos4,tpos5,tpos6,tpos_delta);


		i++;
	}//end while

	fclose(fpo);
}
