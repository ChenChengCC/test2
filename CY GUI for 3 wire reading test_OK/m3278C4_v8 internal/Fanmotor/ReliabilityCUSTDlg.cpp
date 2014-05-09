// ReliabilityCUSTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "ReliabilityCUSTDlg.h"
#include "afxdialogex.h"
#include "FanmotorDlg.h"
#include "TestDlg.h"

//************************Timer Class*********************
int CUSTRegOntime=0,CUSTRegOfftime=0;
int CUSTfan_cycle_cnt_TEST=0;
int CUSTnLoop;
double CUSTtimeperiod,CUSTtotaltime=0;
BOOL CUSTFan_Status_TEST;//fan on == True, fan off == False

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  IDT_TIMER  WM_USER + 200 

//****************************************************

// CReliabilityCUSTDlg dialog

IMPLEMENT_DYNAMIC(CReliabilityCUSTDlg, CDialog)

CReliabilityCUSTDlg::CReliabilityCUSTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReliabilityCUSTDlg::IDD, pParent)
	, m_RADIO_RegLoopMode(0)
	, m_EDIT_RegCnt(_T(""))
{
	m_pParent=pParent;
}

CReliabilityCUSTDlg::~CReliabilityCUSTDlg()
{
}

void CReliabilityCUSTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_RegLoop, m_RADIO_RegLoopMode);
	DDX_Control(pDX, IDC_EDIT_nLoop, m_EDIT_nLoop);
	DDX_Control(pDX, IDC_EDIT_TimePeriod, m_EDIT_TimePeriod);
	DDX_Control(pDX, IDC_EDIT_RegOn, m_EDIT_RegOn);
	DDX_Control(pDX, IDC_EDIT_RegOff, m_EDIT_RegOff);
	DDX_Text(pDX, IDC_EDIT_RegCnt, m_EDIT_RegCnt);
}


BEGIN_MESSAGE_MAP(CReliabilityCUSTDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_REG_RELIABILITY, &CReliabilityCUSTDlg::OnBnClickedButtonRegReliability)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_RegLoop, &CReliabilityCUSTDlg::OnBnClickedRadioRegloop)
	ON_BN_CLICKED(IDC_RADIO_RegTime, &CReliabilityCUSTDlg::OnBnClickedRadioRegtime)
END_MESSAGE_MAP()


// CReliabilityCUSTDlg message handlers


void CReliabilityCUSTDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


BOOL CReliabilityCUSTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//CTestDlg* pParent = (CTestDlg*)m_pParent;
	//CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	//CString errmsg;
	//errmsg.Format(_T("Test is completed.\nNo of Spins: %d.\nTotal Time: %.2fhr."),CUSTfan_cycle_cnt_TEST,0.25);
	//			pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);

	// TODO:  Add extra initialization here
	m_EDIT_RegCnt.Format(_T("-"));
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CReliabilityCUSTDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	((CTestDlg*)m_pParent)->reliabilityCUSTdlg = NULL;
    delete this;
}


void CReliabilityCUSTDlg::OnBnClickedButtonRegReliability()
{
	// TODO: Add your control notification handler code here
	CString errmsg,dats,datbits;
	UINT TimerVal;

	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	int fan_en;
	
	//clear settings
	CUSTfan_cycle_cnt_TEST =0;
	CUSTtotaltime = 0;
	m_EDIT_RegCnt.Format(_T("-"));
	UpdateData(FALSE);

	//get input
	m_EDIT_RegOn.GetWindowText(dats);
	CUSTRegOntime = _wtoi(dats);

	m_EDIT_RegOff.GetWindowText(dats);
	CUSTRegOfftime = _wtoi(dats);

	if ((CUSTRegOntime == 0) |(CUSTRegOfftime == 0))
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Fan on time and off time!");
		return;
	}

	if (m_RADIO_RegLoopMode==0)//loop mode
	{
		m_EDIT_nLoop.GetWindowText(dats);
		CUSTnLoop = _wtoi(dats);
		if (CUSTnLoop == 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter number of loop!");
			return;
		}
	}

	else if(m_RADIO_RegLoopMode==1)//time mode
	{
		m_EDIT_TimePeriod.GetWindowText(dats);
		CUSTtimeperiod = _wtof(dats);
		if (CUSTtimeperiod <= 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Time Period!");
			return;
		}
		//convert hr to ms
		CUSTtimeperiod = CUSTtimeperiod*60*60*1000;
	}


	// set fan_en
	pParentParent->dataupdate_anybits(0x04,0,L"1",1);//set fan_en=1
	fan_en = pParentParent->dataread_anybits(0x04,0,1);

	//init FAN_STATUS
	if (fan_en == 1)
		CUSTFan_Status_TEST = TRUE;
	else
	{
		CUSTFan_Status_TEST = FALSE;
		return;
	}

	TimerVal = StartTimer (CUSTRegOntime);

}


void CReliabilityCUSTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int bFault;
	CString datbits,errmsg;
	BOOL stop;
	int datlength;
	int orig_pos_sns;
	int pos_sns_reg;

	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	if (CUSTFan_Status_TEST == TRUE)
	{
		//off the fan
		datbits = "0";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 0
		if (!success){return;};

		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//update status
		CUSTFan_Status_TEST = FALSE;

		//reset timer with CUSTRegOfftime
		StartTimer (CUSTRegOfftime);	
	}

	else
	{
		CUSTfan_cycle_cnt_TEST++;
		m_EDIT_RegCnt.Format(_T("%d"),CUSTfan_cycle_cnt_TEST);
		UpdateData(FALSE);

		if (m_RADIO_RegLoopMode==0)//loop mode
		{
			if(CUSTfan_cycle_cnt_TEST >= CUSTnLoop)
			{
				//kill timer 
				stop = StopTimer(IDT_TIMER);
				if (stop == FALSE)
				{
					pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
				}

				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d."),CUSTfan_cycle_cnt_TEST);
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
			
				//reset parameter
				CUSTfan_cycle_cnt_TEST=0;
				CUSTtotaltime = 0;

				return;
			}

		}
		else if(m_RADIO_RegLoopMode==1)//time mode
		{
			CUSTtotaltime+=CUSTRegOntime;
			CUSTtotaltime+=CUSTRegOfftime;
			if (CUSTtotaltime > CUSTtimeperiod)
			{
				//kill timer 
				stop = StopTimer(IDT_TIMER);
				if (stop == FALSE)
				{
					pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
				}

				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d.\nTotal Time: %.2fhr."),CUSTfan_cycle_cnt_TEST,(CUSTtotaltime/(60*60*1000)));
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
			
				//reset parameter
				CUSTfan_cycle_cnt_TEST=0;
				CUSTtotaltime = 0;

				return;
			}
		}


		//save pos_sns
		datlength = 1;
		orig_pos_sns = pParentParent->dataread_anybits(0x01,3,datlength);
		// set pos_sns = 0
		datbits = "0";
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
			//kill timer 
			stop = StopTimer(IDT_TIMER);
			if (stop == FALSE)
			{
				pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
			}

			//display msg
			errmsg.Format(_T("No of Spins: %d. Fault = %d"),CUSTfan_cycle_cnt_TEST, bFault);
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
			
			//reset parameter
			CUSTfan_cycle_cnt_TEST=0;
			CUSTtotaltime = 0;

			return;
		}

		//on the fan
		datbits = "1";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 1
		if (!success){return;};

		//update status
		CUSTFan_Status_TEST = TRUE;


		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//reset timer with CUSTRegOntime
		StartTimer (CUSTRegOntime);		
	}
	CDialog::OnTimer(nIDEvent);
}

UINT CReliabilityCUSTDlg::StartTimer (int TimerDuration)
 
{
	CTestDlg* pParent = (CTestDlg*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
    UINT TimerVal;

    TimerVal = SetTimer (IDT_TIMER, TimerDuration, NULL);  // Starting the Timer
    if (TimerVal == 0)
    {
        pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to obtain timer.");
    }
    return TimerVal;
}

BOOL CReliabilityCUSTDlg::StopTimer (UINT TimerVal)
{
    if (!KillTimer (TimerVal))
    {
        return FALSE;
    }

    return TRUE;
} 


void CReliabilityCUSTDlg::OnBnClickedRadioRegloop()
{
	// TODO: Add your control notification handler code here
	m_RADIO_RegLoopMode=0;
}


void CReliabilityCUSTDlg::OnBnClickedRadioRegtime()
{
	// TODO: Add your control notification handler code here
	m_RADIO_RegLoopMode=1;
}
