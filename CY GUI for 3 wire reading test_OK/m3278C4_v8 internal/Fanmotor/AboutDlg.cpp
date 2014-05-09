// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "FanmotorDlg.h"
#include "AboutDlg.h"


//CFanmotorDlg use_fanmotordlg_about;
// CAboutDlg dialog

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
	, m_EDIT_Firmware_Version(_T(""))
{
      m_pParent=pParent;
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Firmware_Version, m_EDIT_Firmware_Version);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_Firmware_Version, &CAboutDlg::OnBnClickedButtonFirmwareVersion)
END_MESSAGE_MAP()


// AboutDlg message handlers

void CAboutDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->aboutdlg = NULL;
    delete this;
}

void CAboutDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void CAboutDlg::OnClose() 
{
	DestroyWindow();
}
void CAboutDlg::OnBnClickedOk()
{
	DestroyWindow();
}

void CAboutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CAboutDlg::OnOK() 
{
}

void CAboutDlg::OnCancel() 
{
}


void CAboutDlg::OnBnClickedButtonFirmwareVersion()
{
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	CString FVersion;
	FVersion=pParent->GetFirmwareVersion();
	m_EDIT_Firmware_Version.Format(_T("%s"),FVersion);
	UpdateData(FALSE);
}
