// AdTorqueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "AdTorqueDlg.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"

// CAdTorqueDlg dialog

IMPLEMENT_DYNAMIC(CAdTorqueDlg, CDialog)

CAdTorqueDlg::CAdTorqueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdTorqueDlg::IDD, pParent)
	, m_EDIT_TorCoarseA(_T(""))
	, m_EDIT_TorCoarseB(_T(""))
	, m_EDIT_TorCoarseC(_T(""))
	, m_EDIT_TorCoarseD(_T(""))
	, m_EDIT_TorCoarseE(_T(""))
	, m_EDIT_TorCoarseF(_T(""))
	, m_EDIT_TorCoarseG(_T(""))
	, m_EDIT_TorCoarseH(_T(""))
	, m_EDIT_TorFineA(_T(""))
	, m_EDIT_TorFineB(_T(""))
	, m_EDIT_TorFineC(_T(""))
	, m_EDIT_TorFineD(_T(""))
	, m_EDIT_TorFineE(_T(""))
	, m_EDIT_TorFineF(_T(""))
	, m_EDIT_TorFineG(_T(""))
	, m_EDIT_TorFineH(_T(""))
{
	m_pParent=pParent;
}

CAdTorqueDlg::~CAdTorqueDlg()
{
}

void CAdTorqueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TorCoarseA, m_EDIT_TorCoarseA);
	DDX_Text(pDX, IDC_EDIT_TorCoarseB, m_EDIT_TorCoarseB);
	DDX_Text(pDX, IDC_EDIT_TorCoarseC, m_EDIT_TorCoarseC);
	DDX_Text(pDX, IDC_EDIT_TorCoarseD, m_EDIT_TorCoarseD);
	DDX_Text(pDX, IDC_EDIT_TorCoarseE, m_EDIT_TorCoarseE);
	DDX_Text(pDX, IDC_EDIT_TorCoarseF, m_EDIT_TorCoarseF);
	DDX_Text(pDX, IDC_EDIT_TorCoarseG, m_EDIT_TorCoarseG);
	DDX_Text(pDX, IDC_EDIT_TorCoarseH, m_EDIT_TorCoarseH);
	DDX_Text(pDX, IDC_EDIT_TorFineA, m_EDIT_TorFineA);
	DDX_Text(pDX, IDC_EDIT_TorFineB, m_EDIT_TorFineB);
	DDX_Text(pDX, IDC_EDIT_TorFineC, m_EDIT_TorFineC);
	DDX_Text(pDX, IDC_EDIT_TorFineD, m_EDIT_TorFineD);
	DDX_Text(pDX, IDC_EDIT_TorFineE, m_EDIT_TorFineE);
	DDX_Text(pDX, IDC_EDIT_TorFineF, m_EDIT_TorFineF);
	DDX_Text(pDX, IDC_EDIT_TorFineG, m_EDIT_TorFineG);
	DDX_Text(pDX, IDC_EDIT_TorFineH, m_EDIT_TorFineH);
	DDX_Control(pDX, IDC_CHECK_OTP1DONE_Test, m_CHECK_OTP1DONE_Test);
}


BEGIN_MESSAGE_MAP(CAdTorqueDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_AdtorExtract, &CAdTorqueDlg::OnBnClickedButtonAdtorextract)
END_MESSAGE_MAP()


// CAdTorqueDlg message handlers


void CAdTorqueDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


void CAdTorqueDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


void CAdTorqueDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}


void CAdTorqueDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}


BOOL CAdTorqueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	int regval_temp,mask,OTP1_done;
	//check otp1_done
	regval_temp = pParentParent->rreg(0x1a);
	mask=1;
	OTP1_done=(regval_temp>>5)&mask;

	if(OTP1_done==0)
	{
		m_CHECK_OTP1DONE_Test.SetCheck(0);
	}

	else
	{
		m_CHECK_OTP1DONE_Test.SetCheck(1);
	}

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

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAdTorqueDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	((CIntTest*)m_pParent)->adtorquedlg = NULL;
    delete this;
}


void CAdTorqueDlg::OnBnClickedButtonAdtorextract()
{
	// TODO: Add your control notification handler code here
	int regval_temp, mask;
	int OTP1_done,pwm_reg_sel_orig;
	CString datbits;
	int torque_temp, torque_temp1, torA_coarse, torA_fine, torB_coarse, torB_fine,torC_coarse, torC_fine,torD_coarse, torD_fine,torE_coarse, torE_fine,torF_coarse, torF_fine,torG_coarse, torG_fine,torH_coarse, torH_fine;
	
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	regval_temp = pParentParent->rreg(0x1a);
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
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"OTP1 have not been burnt!");
		return;
	}

	else
	{
		if (pParentParent->virtual_board)
		{
			m_CHECK_OTP1DONE_Test.SetCheck(1);
			pParentParent->fOTP=1;//reg R/W hand over to OTP array

			// readback OTP torque values
			torque_temp=pParentParent->rreg(0x01);
			torque_temp1=pParentParent->rreg(0x02);
			torA_coarse = (((torque_temp>>1)& 0x03)<<1) | (torque_temp1>>7);
			torA_fine = (torque_temp1>>5) & 0x03;

			
			torque_temp=pParentParent->rreg(0x03);
			torB_coarse = (torque_temp>>2) & 0x07;
			torB_fine = torque_temp & 0x03;

			
			torque_temp=pParentParent->rreg(0x13);
			torC_coarse = (torque_temp>>4) & 0x07;
			torC_fine = (torque_temp>>2) & 0x03;

			
			torque_temp=pParentParent->rreg(0x13);
			torque_temp1=pParentParent->rreg(0x15);
			torD_coarse = (((torque_temp>>1) & 0x01)<<2) | (torque_temp1>>6);
			torD_fine = (torque_temp1>>4) & 0x03;

			
			torque_temp=pParentParent->rreg(0x15);
			torque_temp1=pParentParent->rreg(0x18);
			torE_coarse = (torque_temp>>1) & 0x07;
			torE_fine = ((torque_temp & 0x01)<<1) | (torque_temp1>>7);

			
			torque_temp=pParentParent->rreg(0x18);
			torF_coarse = (torque_temp>>4) & 0x07;
			torF_fine = (torque_temp>>2) & 0x03;

			
			torque_temp=pParentParent->rreg(0x18);
			torque_temp1=pParentParent->rreg(0x1B);
			torG_coarse = ((torque_temp & 0x03)<<1) | (torque_temp1>>7);
			torG_fine = (torque_temp1>>5) & 0x03;

			
			torque_temp=pParentParent->rreg(0x1B);
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
			pParentParent->wreg(0x2a,6);
			pParentParent->wreg(0x3d,5);

			pwm_reg_sel_orig = pParentParent->rreg(0x02);
			if (!success) return;

			//set pwm_reg to 1.	pwmin_sel to 0
			datbits = "1";
			pParentParent->dataupdate_anybits(0x02,1,datbits,1);
			datbits = "0";
			pParentParent->dataupdate_anybits(0x0a,0,datbits,1);

			// readback OTP torque values
			pParentParent->wreg(0x18,0x0);
			torque_temp=pParentParent->rreg(0x03);
			torA_coarse = (torque_temp>>2) & 0x07;
			torA_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0x20);
			torque_temp=pParentParent->rreg(0x03);
			torB_coarse = (torque_temp>>2) & 0x07;
			torB_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0x40);
			torque_temp=pParentParent->rreg(0x03);
			torC_coarse = (torque_temp>>2) & 0x07;
			torC_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0x60);
			torque_temp=pParentParent->rreg(0x03);
			torD_coarse = (torque_temp>>2) & 0x07;
			torD_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0x80);
			torque_temp=pParentParent->rreg(0x03);
			torE_coarse = (torque_temp>>2) & 0x07;
			torE_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0xa0);
			torque_temp=pParentParent->rreg(0x03);
			torF_coarse = (torque_temp>>2) & 0x07;
			torF_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0xc0);
			torque_temp=pParentParent->rreg(0x03);
			torG_coarse = (torque_temp>>2) & 0x07;
			torG_fine = torque_temp & 0x03;

			pParentParent->wreg(0x18,0xe0);
			torque_temp=pParentParent->rreg(0x03);
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
			pParentParent->wreg(0x02,pwm_reg_sel_orig);

		}//virtual_board=false
	}//otp1_done=1
}
