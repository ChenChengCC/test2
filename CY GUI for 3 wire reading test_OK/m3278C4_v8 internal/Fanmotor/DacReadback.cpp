// DacReadback.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "DacReadback.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"

// CDacReadback dialog

IMPLEMENT_DYNAMIC(CDacReadback, CDialog)

CDacReadback::CDacReadback(CWnd* pParent /*=NULL*/)
	: CDialog(CDacReadback::IDD, pParent)
{
	m_pParent=pParent;
}

CDacReadback::~CDacReadback()
{
}

void CDacReadback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Loop_Count, m_EDIT_Loop_Count);
}


BEGIN_MESSAGE_MAP(CDacReadback, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DacReadback, &CDacReadback::OnBnClickedButtonDacreadback)
END_MESSAGE_MAP()


// CDacReadback message handlers


void CDacReadback::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


void CDacReadback::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


BOOL CDacReadback::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDacReadback::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	((CIntTest*)m_pParent)->dacreadbackdlg = NULL;
    delete this;
}


void CDacReadback::OnBnClickedButtonDacreadback()
{
	// TODO: Add your control notification handler code here
	FILE *fpo;
	FILE *fbo;
	errno_t err;
	int i=0;
	int loop_count=0;
	int datr18=0;
	int datr16=0;
	int datr17=0;
	int datpos=0;
	int length_dat=0;
	CTime cTime;
	CString sTime;

	CString loopw,datbit;
	const TCHAR* fpo_name2 = L"backupfile.txt";
	const TCHAR* fpo_name = L"DAC Readback.txt";
	LPTSTR p;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	
	_wfopen_s(&fbo, fpo_name2, _T("w"));
	    
	fclose(fbo);

	CopyFileW(fpo_name, fpo_name2, false); //back up current save file
 
    if (err = _wfopen_s(&fpo, fpo_name, _T("w"))!=0)
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Protected or Not Found.");
		return;
	};

	m_EDIT_Loop_Count.GetWindowText(loopw);
	length_dat =m_EDIT_Loop_Count.LineLength();
	if (length_dat == 0)
	{
		fclose(fpo);
		return;
	};

	datbit="0";
	pParentParent->dataupdate_anybits(0x01,3,datbit,1);
	pParentParent->dataupdate_anybits(0x01,7,datbit,1);

	fprintf( fpo, "   Loop  TPOS  DAC\n ");
	loop_count = _wtoi(loopw);

	do{
	   	datr16 = pParentParent->rreg(0x16);
		datr17 = pParentParent->rreg(0x17);

		datr18 = pParentParent->rreg(0x18);
		datpos = datr16+(datr17<<8);

		cTime = CTime::GetCurrentTime();
		sTime = cTime.Format("%H:%M:%S");
		fwprintf(fpo, sTime);
		
		fprintf( fpo, "   %d   %d  %d\n ", i,datpos,datr18);
		i++;
	}while(i<=loop_count);

	
	pParentParent->DisplayInforMessageBox((LPCWSTR)L"Infor", (LPCWSTR)L"Test Completed.");

	fclose(fpo);
}
