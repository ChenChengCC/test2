// ReliabilityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "ReliabilityDlg.h"
#include "afxdialogex.h"
#include "IntTest.h"
#include "FanmotorDlg.h"
#include "ni488.h"
#include "Decl-32.h"
//************************Timer Class*********************
int RegOntime=0,RegOfftime=0;
int PSOntime=0,PSOfftime=0;
int PWMOntime=0,PWMOfftime=0;
int fan_cycle_cnt_TEST=0;
int PS_cycle_cnt=0;
int PWM_cycle_cnt=0;
int nLoop;
int PSnLoop;
int PWMnLoop;
double timeperiod,totaltime=0;
double PStimeperiod,PStotaltime=0;
double PWMtimeperiod,PWMtotaltime=0;
BOOL Fan_Status_TEST;//fan on == True, fan off == False
BOOL PS_Status;//PS on == True, PS off == False
BOOL PWM_Status;//PWM on == 100% duty cycle, PS off == 0% duty cycle
int PS;
int FG;
int PS_LowOngoing=0,PS_12VOngoing=0,PS_HighOngoing=0;
char sPS12V_Setting[50],sPSLowV_Setting[50],sPSHighV_Setting[50];

extern double duty_cycle1;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  IDT_TIMER  WM_USER + 200 

//****************************************************

// CReliabilityDlg dialog

IMPLEMENT_DYNAMIC(CReliabilityDlg, CDialog)

CReliabilityDlg::CReliabilityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReliabilityDlg::IDD, pParent)
	, m_RADIO_Mode(0)
	, m_RADIO_RegLoopMode(0)
	, m_EDIT_PSCnt(_T(""))
	, m_EDIT_RegCnt(_T(""))
	, m_RADIO_PWMMode(0)
	, m_EDIT_PWMCnt(_T(""))
	, m_RADIO_PSLoopMode(0)
	, m_RADIO_PWMLoopMode(0)
{
	m_pParent=pParent;
}

CReliabilityDlg::~CReliabilityDlg()
{
}

void CReliabilityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_RegMode, m_RADIO_Mode);
	DDX_Radio(pDX, IDC_RADIO_RegLoop, m_RADIO_RegLoopMode);
	DDX_Control(pDX, IDC_CHECK_SelLowVolt, m_CHECK_SelLowVolt);
	DDX_Control(pDX, IDC_CHECK_Sel12Volt, m_CHECK_Sel12Volt);
	DDX_Control(pDX, IDC_CHECK_SelHighVolt, m_CHECK_SelHighVolt);
	DDX_Control(pDX, IDC_EDIT_LowVolt, m_EDIT_LowVolt);
	DDX_Control(pDX, IDC_EDIT_HighVolt, m_EDIT_HighVolt);
	DDX_Control(pDX, IDC_EDIT_CurrLimit, m_EDIT_CurrLimit);
	DDX_Control(pDX, IDC_EDIT_PSOn, m_EDIT_PSOn);
	DDX_Control(pDX, IDC_EDIT_PSOff, m_EDIT_PSOff);
	DDX_Text(pDX, IDC_EDIT_PSCnt, m_EDIT_PSCnt);
	DDX_Text(pDX, IDC_EDIT_RegCnt, m_EDIT_RegCnt);
	DDX_Control(pDX, IDC_EDIT_RegOff, m_EDIT_RegOff);
	DDX_Control(pDX, IDC_EDIT_RegOn, m_EDIT_RegOn);
	DDX_Control(pDX, IDC_EDIT_TimePeriod, m_EDIT_TimePeriod);
	DDX_Control(pDX, IDC_EDIT_nLoop, m_EDIT_nLoop);
	DDX_Radio(pDX, IDC_RADIO_PWMCY, m_RADIO_PWMMode);
	DDX_Control(pDX, IDC_EDIT_PWMOn, m_EDIT_PWMOn);
	DDX_Control(pDX, IDC_EDIT_PWMOff, m_EDIT_PWMOff);
	DDX_Text(pDX, IDC_EDIT_PWMCnt, m_EDIT_PWMCnt);
	DDX_Radio(pDX, IDC_RADIO_PSLoop, m_RADIO_PSLoopMode);
	DDX_Radio(pDX, IDC_RADIO_PWMLoop, m_RADIO_PWMLoopMode);
	DDX_Control(pDX, IDC_EDIT_PSnLoop, m_EDIT_PSnLoop);
	DDX_Control(pDX, IDC_EDIT_PSTimePeriod, m_EDIT_PSTimePeriod);
	DDX_Control(pDX, IDC_EDIT_PWMnLoop, m_EDIT_PWMnLoop);
	DDX_Control(pDX, IDC_EDIT_PWMTimePeriod, m_EDIT_PWMTimePeriod);
}


BEGIN_MESSAGE_MAP(CReliabilityDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	//ON_BN_CLICKED(IDC_BUTTON_RELIABILITY_TEST, &CReliabilityDlg::OnBnClickedButtonReliabilityTest)
	ON_BN_CLICKED(IDC_BUTTON_REG_RELIABILITY, &CReliabilityDlg::OnBnClickedButtonRegReliability)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PS_RELIABILITY, &CReliabilityDlg::OnBnClickedButtonPsReliability)
	ON_BN_CLICKED(IDC_RADIO_RegMode, &CReliabilityDlg::OnBnClickedRadioRegmode)
	ON_BN_CLICKED(IDC_RADIO_PSMode, &CReliabilityDlg::OnBnClickedRadioPsmode)
	ON_BN_CLICKED(IDC_RADIO_PwminLowMode, &CReliabilityDlg::OnBnClickedRadioPwminlowmode)
	ON_BN_CLICKED(IDC_BUTTON_PWM_RELIABILITY, &CReliabilityDlg::OnBnClickedButtonPwmReliability)
	ON_BN_CLICKED(IDC_RADIO_RegLoop, &CReliabilityDlg::OnBnClickedRadioRegloop)
	ON_BN_CLICKED(IDC_RADIO_RegTime, &CReliabilityDlg::OnBnClickedRadioRegtime)
	ON_BN_CLICKED(IDC_RADIO_PSLoop, &CReliabilityDlg::OnBnClickedRadioPsloop)
	ON_BN_CLICKED(IDC_RADIO_PSTime, &CReliabilityDlg::OnBnClickedRadioPstime)
	ON_BN_CLICKED(IDC_RADIO_PWMLoop, &CReliabilityDlg::OnBnClickedRadioPwmloop)
	ON_BN_CLICKED(IDC_RADIO_PWMTime, &CReliabilityDlg::OnBnClickedRadioPwmtime)
	ON_BN_CLICKED(IDC_RADIO_PWMCY, &CReliabilityDlg::OnBnClickedRadioPwmcy)
	ON_BN_CLICKED(IDC_RADIO_PWMFG, &CReliabilityDlg::OnBnClickedRadioPwmfg)
END_MESSAGE_MAP()


// CReliabilityDlg message handlers


void CReliabilityDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	DestroyWindow();
}


void CReliabilityDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: Add your message handler code here
}


BOOL CReliabilityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if (m_RADIO_Mode == 0)
	{
		GetDlgItem(IDC_BUTTON_REG_RELIABILITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PS_RELIABILITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PWM_RELIABILITY)->EnableWindow(FALSE);
	}
	else if (m_RADIO_Mode == 1)
	{
		GetDlgItem(IDC_BUTTON_REG_RELIABILITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PS_RELIABILITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PWM_RELIABILITY)->EnableWindow(FALSE);
	}
	else if (m_RADIO_Mode == 2)
	{
		GetDlgItem(IDC_BUTTON_REG_RELIABILITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PS_RELIABILITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PWM_RELIABILITY)->EnableWindow(TRUE);
	}

	m_EDIT_RegCnt.Format(_T("-"));
	m_EDIT_PSCnt.Format(_T("-"));
	m_EDIT_PWMCnt.Format(_T("-"));
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CReliabilityDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	((CIntTest*)m_pParent)->reliabilitydlg = NULL;
    delete this;
}


void CReliabilityDlg::OnBnClickedButtonRegReliability()
{
	// TODO: Add your control notification handler code here
	CString errmsg,dats,datbits;
	UINT TimerVal;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	int fan_en;
	
	//clear settings
	fan_cycle_cnt_TEST =0;
	totaltime = 0;
	m_EDIT_RegCnt.Format(_T("-"));
	UpdateData(FALSE);

	//get input
	m_EDIT_RegOn.GetWindowText(dats);
	RegOntime = _wtoi(dats);

	m_EDIT_RegOff.GetWindowText(dats);
	RegOfftime = _wtoi(dats);

	if ((RegOntime == 0) |(RegOfftime == 0))
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Fan on time and off time!");
		return;
	}

	if (m_RADIO_RegLoopMode==0)//loop mode
	{
		m_EDIT_nLoop.GetWindowText(dats);
		nLoop = _wtoi(dats);
		if (nLoop == 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter number of loop!");
			return;
		}
	}

	else if(m_RADIO_RegLoopMode==1)//time mode
	{
		m_EDIT_TimePeriod.GetWindowText(dats);
		timeperiod = _wtof(dats);
		if (timeperiod <= 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Time Period!");
			return;
		}
		//convert hr to ms
		timeperiod = timeperiod*60*60*1000;
	}


	// set fan_en
	pParentParent->dataupdate_anybits(0x04,0,L"1",1);//set fan_en=1
	fan_en = pParentParent->dataread_anybits(0x04,0,1);

	//init FAN_STATUS
	if (fan_en == 1)
		Fan_Status_TEST = TRUE;
	else
	{
		Fan_Status_TEST = FALSE;
		return;
	}

	TimerVal = StartTimer (RegOntime);

}

UINT CReliabilityDlg::StartTimer (int TimerDuration)
 
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

BOOL CReliabilityDlg::StopTimer (UINT TimerVal)
{
    if (!KillTimer (TimerVal))
    {
        return FALSE;
    }

    return TRUE;
} 

void CReliabilityDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(m_RADIO_Mode == 0)//register mode
	{
		RegReliability();
	}

	else if(m_RADIO_Mode == 1)//PS mode
	{
		PSReliability();
		
	}

	else if(m_RADIO_Mode == 2)//PWM mode
	{
		PWMReliability();	
	}

	CDialog::OnTimer(nIDEvent);
}

void CReliabilityDlg::RegReliability (void)
{
	int bFault;
	CString datbits,errmsg;
	BOOL stop;
	int datlength;
	int orig_pos_sns;
	int pos_sns_reg;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	if (Fan_Status_TEST == TRUE)
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
		Fan_Status_TEST = FALSE;

		//reset timer with RegOfftime
		StartTimer (RegOfftime);	
	}

	else
	{
		fan_cycle_cnt_TEST++;
		m_EDIT_RegCnt.Format(_T("%d"),fan_cycle_cnt_TEST);
		UpdateData(FALSE);

		if (m_RADIO_RegLoopMode==0)//loop mode
		{
			if(fan_cycle_cnt_TEST >= nLoop)
			{
				//kill timer 
				stop = StopTimer(IDT_TIMER);
				if (stop == FALSE)
				{
					pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
				}

				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d."),fan_cycle_cnt_TEST);
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
			
				//reset parameter
				fan_cycle_cnt_TEST=0;
				totaltime = 0;

				return;
			}

		}
		else if(m_RADIO_RegLoopMode==1)//time mode
		{
			totaltime+=RegOntime;
			totaltime+=RegOfftime;
			if (totaltime > timeperiod)
			{
				//kill timer 
				stop = StopTimer(IDT_TIMER);
				if (stop == FALSE)
				{
					pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
				}

				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d.\nTotal Time: %.2fhr."),fan_cycle_cnt_TEST,(totaltime/(60*60*1000)));
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
			
				//reset parameter
				fan_cycle_cnt_TEST=0;
				totaltime = 0;

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
			errmsg.Format(_T("No of Spins: %d. Fault = %d"),fan_cycle_cnt_TEST, bFault);
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
			
			//reset parameter
			fan_cycle_cnt_TEST=0;
			totaltime = 0;

			return;
		}

		//on the fan
		datbits = "1";
		pParentParent->dataupdate_anybits(0x04,0,datbits,1); // set fan_en = 1
		if (!success){return;};

		//update status
		Fan_Status_TEST = TRUE;


		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//reset timer with RegOntime
		StartTimer (RegOntime);		
	}
}

void CReliabilityDlg::PSReliability (void)
{
	int bFault;
	CString datbits,errmsg;
	BOOL stop;
	int datlength;
	int orig_pos_sns;
	int pos_sns_reg;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	if (PS_Status == TRUE)
	{
		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//condition3: fault triggered. exit
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
			//reset parameter
			PS_cycle_cnt=0;
			PStotaltime = 0;

			//off PS
			ibwrt(PS, "OUTP:STAT OFF", 13);
			PS_Status = FALSE;

			//update status
			PS_Status = FALSE;

			ibonl(PS, 0);

			if (PS_LowOngoing == 1)
			{
				//display msg
				errmsg.Format(_T("Low Volt Test\nNo of Spins: %d. Fault = %d"),PS_cycle_cnt, bFault);
				pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);

				PS_LowOngoing =0;
			}

			if (PS_12VOngoing == 1)
			{
				//display msg
				errmsg.Format(_T("12 Volt Test\nNo of Spins: %d. Fault = %d"),PS_cycle_cnt, bFault);
				pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);

				PS_12VOngoing =0;
			}

			if (PS_HighOngoing == 1)
			{
				//display msg
				errmsg.Format(_T("High Volt Test\nNo of Spins: %d. Fault = %d"),PS_cycle_cnt, bFault);
				pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);

				PS_HighOngoing =0;
			}
		
			return;
		}

		//off PS
		ibwrt(PS, "OUTP:STAT OFF", 13);

		//update status
		PS_Status = FALSE;	

		//reset timer with PSOfftime
		StartTimer (PSOfftime);	
	}

	else
	{
		PS_cycle_cnt++;
		m_EDIT_PSCnt.Format(_T("%d"),PS_cycle_cnt);
		UpdateData(FALSE);

		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
			return;
		}

		
		//condition1: reach nLoop. exit
		if (m_RADIO_PSLoopMode==0)//loop mode
		{
			if(PS_cycle_cnt >= PSnLoop)
			{
				//currently runing test is low volt
				if (PS_LowOngoing == 1)
				{
					PS_LowOngoing =0;

					//check if 12V is checked
					if (m_CHECK_Sel12Volt.GetCheck() == TRUE)
					{
						//reset parameter
						PS_cycle_cnt=0;
						PStotaltime = 0;

						//continue with 12V test
						ibwrt(PS, sPS12V_Setting, 14);
						PS_12VOngoing=1;
						ibwrt(PS, "OUTP:STAT ON", 12);

						//update status
						PS_Status = TRUE;

						StartTimer (PSOntime);
						return;
					}
					else if (m_CHECK_Sel12Volt.GetCheck() == FALSE)
					{
						if (m_CHECK_SelHighVolt.GetCheck() == TRUE)
						{
							//reset parameter
							PS_cycle_cnt=0;
							PStotaltime = 0;

							//continue with high V test
							ibwrt(PS, sPSHighV_Setting, 14);
							PS_HighOngoing=1;
							ibwrt(PS, "OUTP:STAT ON", 12);

							//update status
							PS_Status = TRUE;

							StartTimer (PSOntime);
							return;
						}
					}
				}

				//currently runing test is 12 volt
				else if (PS_12VOngoing == 1)
				{
					PS_12VOngoing =0;

					if (m_CHECK_SelHighVolt.GetCheck() == TRUE)
					{
						//reset parameter
						PS_cycle_cnt=0;
						PStotaltime = 0;

						//continue with high V test
						ibwrt(PS, sPSHighV_Setting, 14);
						PS_HighOngoing=1;
						ibwrt(PS, "OUTP:STAT ON", 12);

						//update status
						PS_Status = TRUE;

						StartTimer (PSOntime);
						return;
					}
				}

				//currently runing test is High volt
				else if (PS_HighOngoing == 1)
				{
					PS_HighOngoing =0;
				}

				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d."),PS_cycle_cnt);
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);

				//reset parameter
				PS_cycle_cnt=0;
				PStotaltime = 0;

				ibonl(PS, 0);
				return;
			}
		}

		//condition2: read preset time. exit
		else if(m_RADIO_PSLoopMode==1)//time mode
		{
			PStotaltime+=PSOntime;
			PStotaltime+=PSOfftime;
			if (PStotaltime > PStimeperiod)
			{
				//currently runing test is low volt
				if (PS_LowOngoing == 1)
				{
					PS_LowOngoing =0;

					//check if 12V is checked
					if (m_CHECK_Sel12Volt.GetCheck() == TRUE)
					{
						//reset parameter
						PS_cycle_cnt=0;
						PStotaltime = 0;

						//continue with 12V test
						ibwrt(PS, sPS12V_Setting, 14);
						PS_12VOngoing=1;
						ibwrt(PS, "OUTP:STAT ON", 12);

						//update status
						PS_Status = TRUE;

						StartTimer (PSOntime);
						return;
					}
					else if (m_CHECK_Sel12Volt.GetCheck() == FALSE)
					{
						if (m_CHECK_SelHighVolt.GetCheck() == TRUE)
						{
							//reset parameter
							PS_cycle_cnt=0;
							PStotaltime = 0;

							//continue with high V test
							ibwrt(PS, sPSHighV_Setting, 14);
							PS_HighOngoing=1;
							ibwrt(PS, "OUTP:STAT ON", 12);

							//update status
							PS_Status = TRUE;

							StartTimer (PSOntime);
							return;
						}
					}
				}

				//currently runing test is 12 volt
				else if (PS_12VOngoing == 1)
				{
					PS_12VOngoing =0;

					if (m_CHECK_SelHighVolt.GetCheck() == TRUE)
					{
						//reset parameter
						PS_cycle_cnt=0;
						PStotaltime = 0;

						//continue with high V test
						ibwrt(PS, sPSHighV_Setting, 14);
						PS_HighOngoing=1;
						ibwrt(PS, "OUTP:STAT ON", 12);

						//update status
						PS_Status = TRUE;

						StartTimer (PSOntime);
						return;
					}
				}

				//currently runing test is High volt
				else if (PS_HighOngoing == 1)
				{
					PS_HighOngoing =0;
				}

				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d.\nTotal Time: %.2fhr."),PS_cycle_cnt,(PStotaltime/(60*60*1000)));
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
				
				//reset parameter
				PS_cycle_cnt=0;
				PStotaltime = 0;

				ibonl(PS, 0);
				return;
			}
		}

		//condition4: continue with next loop.
		//PS on
		//ibclr(PS);//??
		ibwrt(PS, "OUTP:STAT ON", 12);

		//update status
		PS_Status = TRUE;	

		//reset timer with PSOntime
		StartTimer (PSOntime);		
	}
}

void CReliabilityDlg::OnBnClickedButtonPsReliability()
{
	// TODO: Add your control notification handler code here
	CString errmsg,sData,sDatabit;
	UINT TimerVal;
	double fCurrLimit=0,fLowVolt=0,fHighVolt=0;

	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	//clear settings
	PS_cycle_cnt =0;
	PStotaltime = 0;
	m_EDIT_PSCnt.Format(_T("-"));
	UpdateData(FALSE);

	//get input
	m_EDIT_PSOn.GetWindowText(sData);
	PSOntime = _wtoi(sData);

	m_EDIT_PSOff.GetWindowText(sData);
	PSOfftime = _wtoi(sData);

	if ((PSOntime == 0) |(PSOfftime == 0))
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter power supply on time and off time!");
		return;
	}


	if (m_CHECK_SelLowVolt.GetCheck() == TRUE)
	{
		m_EDIT_LowVolt.GetWindowText(sData);
		fLowVolt = _wtof(sData);
		if (fLowVolt <= 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Low Voltage value!");
			return;
		}
	}

	if (m_CHECK_SelHighVolt.GetCheck() == TRUE)
	{
		m_EDIT_HighVolt.GetWindowText(sData);
		fHighVolt = _wtof(sData);
		if (fHighVolt <= 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter High Voltage value!");
			return;
		}
	}

	if (m_RADIO_PSLoopMode==0)//loop mode
	{
		m_EDIT_PSnLoop.GetWindowText(sData);
		PSnLoop = _wtoi(sData);
		if (PSnLoop == 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter number of loop!");
			return;
		}
	}

	else if(m_RADIO_PSLoopMode==1)//time mode
	{
		m_EDIT_PSTimePeriod.GetWindowText(sData);
		PStimeperiod = _wtof(sData);
		if (PStimeperiod <= 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Time Period!");
			return;
		}
		//convert hr to ms
		PStimeperiod = PStimeperiod*60*60*1000;
	}

	m_EDIT_CurrLimit.GetWindowText(sData);
	fCurrLimit = _wtof(sData);
	if (fCurrLimit <= 0)
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter power supply on time and off time!");
		return;
	}

	//setting
	sprintf(sPS12V_Setting, "APPL 12.0, %.1f",fCurrLimit);//length=14
	sprintf(sPSLowV_Setting, "APPL %.1f, %.1f",fLowVolt, fCurrLimit);//length=14
	sprintf(sPSHighV_Setting, "APPL %.1f, %.1f",fHighVolt,fCurrLimit);//length=14


	//open PS GPIB control
	PS = ibdev(0, 5, 0, 10, 1, 0);
	if (ibsta & ERR)
    {
      errmsg.Format(_T("No GPIB connection"));
	  pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
	  return;
    }

	
	//PS setting
	if (m_CHECK_SelLowVolt.GetCheck() == TRUE)
	{
		ibwrt(PS, sPSLowV_Setting, 14);
		PS_LowOngoing =1;
	}

	else if (m_CHECK_Sel12Volt.GetCheck() == TRUE)
	{
		ibwrt(PS, sPS12V_Setting, 14);

		PS_12VOngoing=1;
	}

	else if (m_CHECK_SelHighVolt.GetCheck() == TRUE)
	{
		ibwrt(PS, sPSHighV_Setting, 14);
		PS_HighOngoing=1;
	}


	// set PS on
	ibwrt(PS, "OUTP:STAT ON", 12);

	//init PS_STATUS
	PS_Status = TRUE;

	TimerVal = StartTimer (PSOntime);

	//do{
	//	i++;
	//	ibwrt(PS, "OUTP:STAT ON", 12);
	//	Sleep(1000);
	//	m_EDIT_PSCnt.Format(_T("%d"),i);
	//	UpdateData(FALSE);
	//	UpdateWindow();

	//	y=0;
	//		do{
	//			y++;
	//			dat = pParentParent->rreg( 0x19); // read fault
	//			if (!success) {ibonl(PS, 0);return;};
	//			dat = ((dat & 0x78) >> 3);
	//			Sleep(3000);
	//		}while(y<=20&&!dat);
	//	
	//	ibwrt(PS, "OUTP:STAT OFF", 13);
	//	Sleep(60000);
	//	ibclr(PS);
	//}while(!dat);

	//errmsg.Format(_T("No of Spins: %d. Fault = %d"),i, dat);
	//pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
	//ibonl(PS, 0);
}


void CReliabilityDlg::OnBnClickedRadioRegmode()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_REG_RELIABILITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PS_RELIABILITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PWM_RELIABILITY)->EnableWindow(FALSE);

	m_RADIO_Mode=0;
}


void CReliabilityDlg::OnBnClickedRadioPsmode()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_REG_RELIABILITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PS_RELIABILITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PWM_RELIABILITY)->EnableWindow(FALSE);

	m_RADIO_Mode=1;
}


void CReliabilityDlg::OnBnClickedRadioPwminlowmode()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_REG_RELIABILITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PS_RELIABILITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PWM_RELIABILITY)->EnableWindow(TRUE);

	m_RADIO_Mode=2;
}


void CReliabilityDlg::OnBnClickedButtonPwmReliability()
{
	// TODO: Add your control notification handler code here
	CString errmsg,dats,datbits;
	UINT TimerVal;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);
	int pulse_width1;
	
	//clear settings
	PWM_cycle_cnt =0;
	PWMtotaltime = 0;
	m_EDIT_PWMCnt.Format(_T("-"));
	UpdateData(FALSE);

	//get input
	m_EDIT_PWMOn.GetWindowText(dats);
	PWMOntime = _wtoi(dats);

	m_EDIT_PWMOff.GetWindowText(dats);
	PWMOfftime = _wtoi(dats);

	if ((PWMOntime == 0) |(PWMOfftime == 0))
	{
		pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter PWM on time and off time!");
		return;
	}

	if (m_RADIO_PWMLoopMode==0)//loop mode
	{
		m_EDIT_PWMnLoop.GetWindowText(dats);
		PWMnLoop = _wtoi(dats);
		if (PWMnLoop == 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter number of loop!");
			return;
		}
	}

	else if(m_RADIO_PWMLoopMode==1)//time mode
	{
		m_EDIT_PWMTimePeriod.GetWindowText(dats);
		PWMtimeperiod = _wtof(dats);
		if (PWMtimeperiod <= 0)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Please enter Time Period!");
			return;
		}
		//convert hr to ms
		PWMtimeperiod = PWMtimeperiod*60*60*1000;
	}

	//set PWMIN_SEL=1
	datbits = "1";
	pParentParent->dataupdate_anybits(0x0a,0,datbits,1);
	datbits = "0";
	pParentParent->dataupdate_anybits(0x02,1,datbits,1);

	// set PWM DC=100%, init PWM_STATUS
	if (m_RADIO_PWMMode == 0)//CY PWM
	{
		//set CY PWM DC =100%
		duty_cycle1=100;
		pulse_width1=(255*duty_cycle1)/100;
	    pParentParent->setpowerPWM(pulse_width1);
		pParentParent->UpdatePWM1();

	}
	else if (m_RADIO_PWMMode == 1)//FG PWM
	{
		//open FG GPIB control
		FG = ibdev(0, 15, 0, 10, 1, 0);
		if (ibsta & ERR)
		{
		  errmsg.Format(_T("No GPIB connection"));
		  pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
		  return;
		}
	
		//FG setting
		ibwrt(FG, "APPL:PULS 20000, 5", 18);
		ibwrt(FG, "PULS:WIDT 0.0001", 16);

		// set FG on
		ibwrt(FG, "OUTP ON", 7);//??		
	}

	//init PS_STATUS
	PWM_Status = TRUE;

	TimerVal = StartTimer (PWMOntime);

}

void CReliabilityDlg::PWMReliability (void)
{
	int bFault;
	CString datbits,errmsg;
	BOOL stop;
	int datlength;
	int orig_pos_sns;
	int pos_sns_reg;
	int pulse_width1;
	CIntTest* pParent = (CIntTest*)m_pParent;
	CFanmotorDlg* pParentParent = (CFanmotorDlg*)(pParent->m_pParent);

	if (PWM_Status == TRUE)
	{
		//set PWM DC=0%
		if (m_RADIO_PWMMode == 0)//CY PWM
		{
			//set CY PWM DC =0%
			duty_cycle1=0;
			pulse_width1=(255*duty_cycle1)/100;
			pParentParent->setpowerPWM(pulse_width1);
			pParentParent->UpdatePWM1();
		}

		else if (m_RADIO_PWMMode == 1)//FG PWM
		{
			ibwrt(FG, "PULS:WIDT 0.0", 13);
			PWM_Status = FALSE;
		}

		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//update status
		PWM_Status = FALSE;

		//reset timer with PWMOfftime
		StartTimer (PWMOfftime);	
		
	}

	else
	{
		PWM_cycle_cnt++;
		m_EDIT_PWMCnt.Format(_T("%d"),PWM_cycle_cnt);
		UpdateData(FALSE);

		//kill timer
		stop = StopTimer(IDT_TIMER);
		if (stop == FALSE)
		{
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Error",(LPCWSTR)L"Unable to stop the timer.");
		}

		//exit 1
		if (m_RADIO_PWMLoopMode==0)//loop mode
		{
			if(PWM_cycle_cnt >= PWMnLoop)
			{
				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d."),PWM_cycle_cnt);
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);

				//reset parameter
				PWM_cycle_cnt=0;
				PWMtotaltime = 0;

				ibonl(FG, 0);
				return;
			}

		}

		//exit 2
		else if(m_RADIO_PWMLoopMode==1)//time mode
		{
			PWMtotaltime+=PWMOntime;
			PWMtotaltime+=PWMOfftime;
			if (PWMtotaltime > PWMtimeperiod)
			{
				//display msg
				errmsg.Format(_T("Test is completed.\nNo of Spins: %d.\nTotal Time: %.2fhr."),PWM_cycle_cnt,(PWMtotaltime/(60*60*1000)));
				pParentParent->DisplayInforMessageBox((LPCWSTR)L"Information", errmsg);
				
				//reset parameter
				PWM_cycle_cnt=0;
				PWMtotaltime = 0;

				ibonl(FG, 0);
				return;
			}
		}

		//exit 3
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
			//display msg
			errmsg.Format(_T("No of Spins: %d. Fault = %d"),PWM_cycle_cnt, bFault);
			pParentParent->DisplayErrorMessageBox((LPCWSTR)L"Fault", errmsg);
			
			//reset parameter
			PWM_cycle_cnt=0;
			PWMtotaltime = 0;

			ibonl(FG, 0);
			return;
		}

		//continue test
		//set PWM =100%
		if (m_RADIO_PWMMode == 0)//CY PWM
		{
			//set CY PWM DC =100%
			duty_cycle1=100;
			pulse_width1=(255*duty_cycle1)/100;
			pParentParent->setpowerPWM(pulse_width1);
			pParentParent->UpdatePWM1();
		}
		else if (m_RADIO_PWMMode == 1)//FG PWM
		{
			//ibclr(FG);//??
			ibwrt(FG, "PULS:WIDT 0.0001", 16);			
		}
			
		//update status
		PWM_Status = TRUE;

		//reset timer with PWMOntime//warning: once start timer, the code followed start_timer will not be executed.
		StartTimer (PWMOntime);		
		
	}
}


void CReliabilityDlg::OnBnClickedRadioRegloop()
{
	// TODO: Add your control notification handler code here
	m_RADIO_RegLoopMode=0;
}


void CReliabilityDlg::OnBnClickedRadioRegtime()
{
	// TODO: Add your control notification handler code here
	m_RADIO_RegLoopMode=1;
}


void CReliabilityDlg::OnBnClickedRadioPsloop()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PSLoopMode=0;
}


void CReliabilityDlg::OnBnClickedRadioPstime()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PSLoopMode=1;
}


void CReliabilityDlg::OnBnClickedRadioPwmloop()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWMLoopMode=0;

}


void CReliabilityDlg::OnBnClickedRadioPwmtime()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWMLoopMode=1;
}


void CReliabilityDlg::OnBnClickedRadioPwmcy()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWMMode=0;
}


void CReliabilityDlg::OnBnClickedRadioPwmfg()
{
	// TODO: Add your control notification handler code here
	m_RADIO_PWMMode=1;
}
