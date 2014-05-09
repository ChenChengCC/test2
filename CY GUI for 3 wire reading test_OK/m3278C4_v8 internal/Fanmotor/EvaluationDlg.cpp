// EvaluationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "conio.h"
#include "Fanmotor.h"
#include "EvaluationDlg.h"
#include "debugDlg.h"
#include "FanmotorDlg.h"
#include "detailDlg.h"

bool data_rangecheck;
int pole;
int var_dac;
int ad_tor_en;
int vardac_cnt;

// CEvaluationDlg dialog
CdebugDlg usedebug_eval;
CdetailDlg usedetail_eval;
CFanmotorDlg use_fanmotordlg_eval;

IMPLEMENT_DYNAMIC(CEvaluationDlg, CDialog)

CEvaluationDlg::CEvaluationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEvaluationDlg::IDD, pParent)
	, m_EDIT_SHOWDAC(_T(""))
	, m_EDIT_RPM_COUNT(_T(""))
{
     m_pParent=pParent;
}

CEvaluationDlg::~CEvaluationDlg()
{
}

void CEvaluationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DACW, m_EDIT_DACW);
	DDX_Text(pDX, IDC_EDIT_SHOWDAC, m_EDIT_SHOWDAC);
	DDX_Control(pDX, IDC_EDIT_MAX_DAC, m_EDIT_MAX_DAC);
	DDX_Control(pDX, IDC_EDIT_MIN_DAC, m_EDIT_MIN_DAC);
	DDX_Control(pDX, IDC_CHECK_VARDAC_EN, m_CHECK_VARDAC_EN);
	DDX_Control(pDX, IDC_COMBO_VARDAC_CNT, m_COMBO_VARDAC_CNT);
	DDX_Control(pDX, IDC_CHECK_ADTOR_EN, m_CHECK_ADTOR_EN);
	DDX_Text(pDX, IDC_EDIT_RPM_COUNT, m_EDIT_RPM_COUNT);
	DDX_Control(pDX, IDC_FAN, m_FAN);
}


BEGIN_MESSAGE_MAP(CEvaluationDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_LOAD, &CEvaluationDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON_DACW, &CEvaluationDlg::OnBnClickedButtonDacw)
	ON_BN_CLICKED(IDC_BUTTON_DACWUP, &CEvaluationDlg::OnBnClickedButtonDacwup)
	ON_BN_CLICKED(IDC_BUTTON_DACWDOWN, &CEvaluationDlg::OnBnClickedButtonDacwdown)
	ON_BN_CLICKED(IDC_BUTTON_DACWUPSMALL, &CEvaluationDlg::OnBnClickedButtonDacwupsmall)
	ON_BN_CLICKED(IDC_BUTTON_DACWDOWNSMALL, &CEvaluationDlg::OnBnClickedButtonDacwdownsmall)
	ON_BN_CLICKED(IDC_CHECK_VARDAC_EN, &CEvaluationDlg::OnBnClickedCheckVardacEn)
	ON_CBN_SELCHANGE(IDC_COMBO_VARDAC_CNT, &CEvaluationDlg::OnCbnSelchangeComboVardacCnt)
	ON_BN_CLICKED(IDC_CHECK_ADTOR_EN, &CEvaluationDlg::OnBnClickedCheckAdtorEn)
	ON_BN_CLICKED(IDC_BUTTON_START, &CEvaluationDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CEvaluationDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_ACCELERATE, &CEvaluationDlg::OnBnClickedButtonAccelerate)
	ON_BN_CLICKED(IDC_BUTTON_DECELERATE2, &CEvaluationDlg::OnBnClickedButtonDecelerate2)
	ON_BN_CLICKED(IDC_RPM_COUNT, &CEvaluationDlg::OnBnClickedRpmCount)
	ON_BN_CLICKED(IDC_BUTTON_DACR, &CEvaluationDlg::OnBnClickedButtonDacr)
	ON_BN_CLICKED(IDC_READ_EVAL, &CEvaluationDlg::OnBnClickedReadEval)
END_MESSAGE_MAP()

BOOL CEvaluationDlg::OnInitDialog()
{
	CString datmin,datmax;
	int mask,regval;

	CDialog::OnInitDialog();
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonDacr();
	if (!success){goto end;};

	regval = use_fanmotordlg_eval.rreg(0x01);
    if (!success){goto end;};
	mask=1;
	ad_tor_en=(regval>>3)&mask;

	regval = use_fanmotordlg_eval.rreg(0x10);
    if (!success){goto end;};
	mask=1;
	var_dac=(regval>>6)&mask;

	regval = use_fanmotordlg_eval.rreg(0x0a);
    if (!success){goto end;};
	mask=7;
	vardac_cnt=(regval>>4)&mask;
		
	OnBnClickedRpmCount();
	if (!success){goto end;};
	m_CHECK_ADTOR_EN.SetCheck(ad_tor_en);
	m_CHECK_VARDAC_EN.SetCheck(var_dac);
	m_COMBO_VARDAC_CNT.SetCurSel(vardac_cnt);
	datmin = "40";
	datmax = "c0";
	m_EDIT_MIN_DAC.SetWindowText(datmin);
	m_EDIT_MAX_DAC.SetWindowText(datmax);
	spin_fan = pParent->dataread_anybits(0x04,0,1);
	if (!success){goto end;};
	pole = pParent->dataread_anybits(0x07,6,1);
	if (!success){goto end;};

	if(spin_fan==1){
            m_FAN.Open(_T("fan.avi"));
		    m_FAN.Play(0, (UINT)-1, (UINT)-1);
	}else{
		    m_FAN.Open(_T("fan.avi"));
		    m_FAN.Stop();
	}
   	return TRUE;  // return TRUE  unless you set the focus to a control

	end:;  
}

void CEvaluationDlg::PostNcDestroy() 
{	
    CDialog::PostNcDestroy();
	((CFanmotorDlg*)m_pParent)->evaluationdlg = NULL;
    delete this;
}

void CEvaluationDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void CEvaluationDlg::OnClose() 
{
	DestroyWindow();
}

void CEvaluationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CEvaluationDlg::OnOK() 
{
}

void CEvaluationDlg::OnCancel() 
{
}

// Load Button
void CEvaluationDlg::loadfile()
{
	FILE *fpi;
	char command[1000];
	int regval;
	int wordcnt=0;
	int i=0;
	CString str;
	CString errmsg;
	errno_t err;

	CString FileStr;

	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;

	const TCHAR* fpi_name = L"nidec.txt";
    
	if (err = _wfopen_s(&fpi, fpi_name, _T("r"))!=0)
	{
		//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"File Not Found.");
		goto end_error;
	};

	while (i != EOF){
		regval = 0xffff;
		i = fscanf_s(fpi, "%s", command, 1000);
		if(i == EOF) break;
		wordcnt++;

		if (_stricmp(command, "Reg01h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x01,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg02h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x02,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg03h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x03,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg04h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x04,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg05h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x05,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg06h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (slave_addr,regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x06,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg07h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x07,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg08h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x08,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg09h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x09,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ah") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x0a,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{		
				use_fanmotordlg_eval.wreg(0x0b,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x0c,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x0d,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x0e,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg0Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x0f,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg10h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x10,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg11h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x11,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg12h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x12,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg13h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x13,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg14h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x14,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg15h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x15,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg18h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x18,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Bh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x1b,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Ch") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x1c,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Dh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x1d,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Eh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x1e,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg1Fh") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x1f,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else if (_stricmp(command, "Reg20h") == 0 ){
			fscanf_s(fpi, "%x", &regval);
			if ((regval >= 0x00) && (regval <= 0xff))
			{
				use_fanmotordlg_eval.wreg(0x20,regval);
				if (!success){goto end;};
			}
			else
			{
				goto unknown_format;
			}
		}
		else{
			unknown_format:;
			errmsg.Format(_T("Unknown Format.\nPlease check your command syntax!"));
		//	//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
		};
	};

	end:;
	fclose(fpi);
	end_error:;
}
void CEvaluationDlg::OnBnClickedLoad()
{
	loadfile();
}

void CEvaluationDlg::OnBnClickedButtonDacw()
{
	int dat = 0;
	int temp_int;
	double temp_float;
	int length_dat;
	CString dats,datbits;
	CString temp_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//read user inputs
	m_EDIT_DACW.GetWindowText(dats);
	
	//get the string length of the inputs
	length_dat = m_EDIT_DACW.LineLength();

	//convert input string into integer
	dat = usedebug_eval.string2int(dats, length_dat);
	data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
    datbits = pParent->int2bin_anybits(dat,8);

	if( data_rangecheck = TRUE){
	pParent->dataupdate_anybits(0x18,0,datbits,8);
	if (!success){goto end;};
	}

	temp_int = use_fanmotordlg_eval.rreg(0x18);
	if (!success){goto end;};
	temp_string.Format(_T("%x"),temp_int);
	m_EDIT_DACW.SetWindowText(temp_string);
    temp_float = temp_int*0.3922;
    m_EDIT_SHOWDAC.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE);

end:;
}

void CEvaluationDlg::OnBnClickedButtonDacwup()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_DACW.GetWindowText(dats);
	   	 length_dat = m_EDIT_DACW.LineLength();
    	 dat = usedebug_eval.string2int(dats, length_dat);
	     data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
	

	if(data_rangecheck = TRUE){
	   do {
	    	gain_counter++;
			dat++;
			data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
			if(data_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_DACW.SetWindowTextW(dat_string);
	   OnBnClickedButtonDacw();
	}
}

void CEvaluationDlg::OnBnClickedButtonDacwdown()
{
	int gain_counter=0;
	int gain_step=16;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_DACW.GetWindowText(dats);
	   	 length_dat = m_EDIT_DACW.LineLength();
    	 dat = usedebug_eval.string2int(dats, length_dat);
	     data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
	

	if(data_rangecheck = TRUE){
	   do {
	    	gain_counter++;
			dat--;
			data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
			if(data_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_DACW.SetWindowTextW(dat_string);
	   OnBnClickedButtonDacw();
	}
}

void CEvaluationDlg::OnBnClickedButtonDacwupsmall()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_DACW.GetWindowText(dats);
	   	 length_dat = m_EDIT_DACW.LineLength();
    	 dat = usedebug_eval.string2int(dats, length_dat);
	     data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
	

	if(data_rangecheck = TRUE){
	   do {
	    	gain_counter++;
			dat++;
			data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
			if(data_rangecheck != TRUE){
              dat--;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_DACW.SetWindowTextW(dat_string);
	   OnBnClickedButtonDacw();
	}
}

void CEvaluationDlg::OnBnClickedButtonDacwdownsmall()
{
	int gain_counter=0;
	int gain_step=1;
	int dat = 0;
	int datr = 0;
	int length_dat;
	CString gains;
	CString dats,dat_string;

	     m_EDIT_DACW.GetWindowText(dats);
	   	 length_dat = m_EDIT_DACW.LineLength();
    	 dat = usedebug_eval.string2int(dats, length_dat);
	     data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
	

	if(data_rangecheck = TRUE){
	   do {
	    	gain_counter++;
			dat--;
			data_rangecheck = usedetail_eval.datarangecheck8bits(dat);
			if(data_rangecheck != TRUE){
              dat++;
			  break;
			}
	   }while (gain_counter != gain_step);
       dat_string.Format(_T("%x"),dat);
	   m_EDIT_DACW.SetWindowTextW(dat_string);
	   OnBnClickedButtonDacw();
	}
}

void CEvaluationDlg::OnBnClickedCheckVardacEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_VARDAC_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x10,1,datbits,1);
}

void CEvaluationDlg::OnCbnSelchangeComboVardacCnt()
{
	int seln;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	seln = m_COMBO_VARDAC_CNT.GetCurSel();	
	datbits = pParent->int2bin_anybits(seln,3);
    pParent->dataupdate_anybits(0x0a,1,datbits,3);
}

void CEvaluationDlg::OnBnClickedCheckAdtorEn()
{
	static BOOL check = FALSE;
	CString datbits;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	check = m_CHECK_ADTOR_EN.GetCheck();
	
	if(check == TRUE){
		datbits = "1";
	}else if(check == FALSE){
		datbits = "0";
	}
	
	pParent->dataupdate_anybits(0x01,4,datbits,1);
}

void CEvaluationDlg::OnBnClickedButtonStart()
{
	int auto_spin,datr;
	int timeout_counter=0;
	CString errmsg;
	int datincurrent = 0;
	int datinmin = 0;
	int length_dat;
	CString spinup,datbin;
	CString datmin,dat_string,datcurrent;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	auto_spin = pParent->dataread_anybits(0x04,0,1);
	if (!success){goto end;};
	if(auto_spin==0){
		
		m_EDIT_MIN_DAC.GetWindowText(datmin);
		length_dat = m_EDIT_MIN_DAC.LineLength();
    	datinmin = usedebug_eval.string2int(datmin, length_dat);
	    data_rangecheck = usedetail_eval.datarangecheck8bits(datinmin);
		if( data_rangecheck != TRUE){
	        goto end;
	    }
            
		m_EDIT_DACW.GetWindowText(datcurrent);
		length_dat = m_EDIT_DACW.LineLength();
    	datincurrent = usedebug_eval.string2int(datcurrent, length_dat);
	    data_rangecheck = usedetail_eval.datarangecheck8bits(datincurrent);
		if( data_rangecheck != TRUE){
	        goto end;
	    }
		    
		if(datincurrent < datinmin){
			errmsg.Format(_T("Target DAC value is less than MIN_DAC!\nPlease re-enter target DAC value!"));
			////usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
	    }
	    
		
        use_fanmotordlg_eval.wreg(0x18,datincurrent);
		if (!success){goto end;};
		spinup = "1";
        pParent->dataupdate_anybits(0x04,0,spinup,1);
		if (!success){goto end;};
		
	  do {
		    datr = use_fanmotordlg_eval.rreg(0x19);
			if (!success){goto end;};
	        datbin = pParent->int2bin_anybits(datr,8);
			timeout_counter++;
		if (timeout_counter == 100){
			spinup = "0";
            pParent->dataupdate_anybits(0x04,0,spinup,1);
			if (!success){goto end;};
			////usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Auto spin not done! Please retry.");
			goto end;
	       };
	    }while (datbin[0] == '0' && (timeout_counter != 100));

	    spin_fan=1;
		m_FAN.Open(_T("fan.avi"));
		m_FAN.Play(0, (UINT)-1, (UINT)-1);

		     use_fanmotordlg_eval.wreg(0x18,datincurrent);
			 if (!success){goto end;};
			 OnBnClickedRpmCount();
	}else{
		    errmsg.Format(_T("Motor is spinning!\nPlease stop motor and retry!"));
			//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
	}
end:;
}

void CEvaluationDlg::OnBnClickedButtonStop()
{
	int auto_spin;
	CString errmsg;
	int datincurrent = 0;
	int datinmin = 0;
	int length_dat;
	CString spinup;
	CString datmin,dat_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	auto_spin = pParent->dataread_anybits(0x04,0,1);
	if (!success){goto end;};
	if(auto_spin==1){
		
		m_EDIT_MIN_DAC.GetWindowText(datmin);
		length_dat = m_EDIT_MIN_DAC.LineLength();
    	datinmin = usedebug_eval.string2int(datmin, length_dat);
	    data_rangecheck = usedetail_eval.datarangecheck8bits(datinmin);
		if( data_rangecheck != TRUE){
	        goto end;
	    }

		datincurrent = use_fanmotordlg_eval.rreg(0x18);
		if (!success){goto end;};
		if(datincurrent < datinmin){
			spinup = "0";
            pParent->dataupdate_anybits(0x04,0,spinup,1);
			if (!success){goto end;};
			spin_fan=0;
		    m_FAN.Open(_T("fan.avi"));
		    m_FAN.Stop(); 
			//errmsg.Format(_T("Current DAC value is less than MIN_DAC!\nPlease re-enter target DAC value!"));
			//useserial_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
	    }
	    
		 use_fanmotordlg_eval.wreg(0x18,datinmin);
		 if (!success){goto end;};
         spinup = "0";
         pParent->dataupdate_anybits(0x04,0,spinup,1);
		 if (!success){goto end;};
		 m_EDIT_RPM_COUNT.Format(_T("0"));
	     UpdateData(FALSE);
		 spin_fan=0;
		 m_FAN.Open(_T("fan.avi"));
		 m_FAN.Stop();
	}else{
		    errmsg.Format(_T("Motor is not spinning!\nPlease spin motor and retry!"));
		//	//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
	}
end:;
}

void CEvaluationDlg::OnBnClickedButtonAccelerate()
{
	int auto_spin;
	CString errmsg;
	int datincurrent = 0;
	int datinmax = 0;
	int length_dat;
	CString spinup;
	CString datmax,dat_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	auto_spin = pParent->dataread_anybits(0x04,0,1);
	if (!success){goto end;};
	if(auto_spin==1){
		
		m_EDIT_MAX_DAC.GetWindowText(datmax);
		length_dat = m_EDIT_MAX_DAC.LineLength();
    	datinmax = usedebug_eval.string2int(datmax, length_dat);
	    data_rangecheck = usedetail_eval.datarangecheck8bits(datinmax);
		if( data_rangecheck != TRUE){
	        goto end;
	    }

		datincurrent = use_fanmotordlg_eval.rreg(0x18);
		if (!success){goto end;};
            
		if(datinmax < datincurrent){
			errmsg.Format(_T("Current DAC value is greater than MAX_DAC!\nPlease enter correct DAC values and retry!"));
			//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
		}
        
		     use_fanmotordlg_eval.wreg(0x18,datinmax);
			 if (!success){goto end;};
			 OnBnClickedRpmCount();
	    }else{
		    errmsg.Format(_T("Motor is not spinning!\nPlease spin motor and retry!"));
			//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
	}
end:;
}

void CEvaluationDlg::OnBnClickedButtonDecelerate2()
{
	int auto_spin;
	CString errmsg;
	int datincurrent = 0;
	int datinmin = 0;
	int length_dat;
	CString spinup;
	CString datmin,dat_string;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	auto_spin = pParent->dataread_anybits(0x04,0,1);
	if (!success){goto end;};
	if(auto_spin==1){
		
		m_EDIT_MIN_DAC.GetWindowText(datmin);
		length_dat = m_EDIT_MIN_DAC.LineLength();
    	datinmin = usedebug_eval.string2int(datmin, length_dat);
	    data_rangecheck = usedetail_eval.datarangecheck8bits(datinmin);
		if( data_rangecheck != TRUE){
	        goto end;
	    }

		datincurrent = use_fanmotordlg_eval.rreg(0x18);
		if (!success){goto end;};
            
		if(datincurrent < datinmin){
			errmsg.Format(_T("Current DAC value is less than MIN_DAC!\nPlease enter correct DAC values and retry!"));
			//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
			goto end;
		}
        
		     use_fanmotordlg_eval.wreg(0x18,datinmin);
			 if (!success){goto end;};
			 OnBnClickedRpmCount();
	    }else{
		    errmsg.Format(_T("Motor is not spinning!\nPlease spin motor and retry!"));
			//usedebug_eval.DisplayErrorMessageBox((LPCWSTR)L"Error", errmsg);
	}
end:;
}

void CEvaluationDlg::OnBnClickedRpmCount()
{
	/*int bemf_period,bemf_period_cal;
	int rpm_count,auto_spin,comsel;
    
	pole = pParent->dataread_anybits(0x07,6,1);
	if (!success){goto end;};

	if(pole==0){ 
	    auto_spin = pParent->dataread_anybits(0x04,0,1);
		if (!success){goto end;};
		if(auto_spin==1){
	       okUsbFrontPanel_UpdateWireOuts(usedebug_eval.xem);
           bemf_period =  okUsbFrontPanel_GetWireOutValue(usedebug_eval.xem, 0x22);
		   if(bemf_period==0){
			   m_EDIT_RPM_COUNT.Format(_T("0"));
	           UpdateData(FALSE);
			   goto end;
		   }
	       bemf_period_cal=4*bemf_period;
           rpm_count = 125000000/bemf_period_cal;
	       m_EDIT_RPM_COUNT.Format(_T("%d"),rpm_count);
	       UpdateData(FALSE);
		}else{
			comsel = pParent->dataread_anybits(0x01,0,1);
			if (!success){goto end;};
			if(comsel==1){
				okUsbFrontPanel_UpdateWireOuts(usedebug_eval.xem);
                bemf_period =  okUsbFrontPanel_GetWireOutValue(usedebug_eval.xem, 0x22);
		            if(bemf_period==0){
			               m_EDIT_RPM_COUNT.Format(_T("0"));
	                       UpdateData(FALSE);
			               goto end;
		            }
	            bemf_period_cal=4*bemf_period;
                rpm_count = 125000000/bemf_period_cal;
	            m_EDIT_RPM_COUNT.Format(_T("%d"),rpm_count);
	            UpdateData(FALSE);
			}else{
                    m_EDIT_RPM_COUNT.Format(_T("0"));
	                UpdateData(FALSE);
			}
		}
	}else{
        auto_spin = pParent->dataread_anybits(0x04,0,1);
		if (!success){goto end;};
		if(auto_spin==1){
	       okUsbFrontPanel_UpdateWireOuts(usedebug_eval.xem);
           bemf_period =  okUsbFrontPanel_GetWireOutValue(usedebug_eval.xem, 0x22);
		   if(bemf_period==0){
			   m_EDIT_RPM_COUNT.Format(_T("0"));
	           UpdateData(FALSE);
			   goto end;
		   }
	       bemf_period_cal=6*bemf_period;
           rpm_count = 125000000/bemf_period_cal;
	       m_EDIT_RPM_COUNT.Format(_T("%d"),rpm_count);
	       UpdateData(FALSE);
		}else{
			comsel = pParent->dataread_anybits(0x01,0,1);
			if (!success){goto end;};
			if(comsel==1){
				okUsbFrontPanel_UpdateWireOuts(usedebug_eval.xem);
                bemf_period =  okUsbFrontPanel_GetWireOutValue(usedebug_eval.xem, 0x22);
		            if(bemf_period==0){
			               m_EDIT_RPM_COUNT.Format(_T("0"));
	                       UpdateData(FALSE);
			               goto end;
		            }
	            bemf_period_cal=6*bemf_period;
                rpm_count = 125000000/bemf_period_cal;
	            m_EDIT_RPM_COUNT.Format(_T("%d"),rpm_count);
	            UpdateData(FALSE);
			}else{
                    m_EDIT_RPM_COUNT.Format(_T("0"));
	                UpdateData(FALSE);
			}
		}
	}
  end:;*/
}

void CEvaluationDlg::OnBnClickedButtonDacr()
{
	int datr = 0;
	double temp_float;
	CString datr_string;
	
	datr = use_fanmotordlg_eval.rreg(0x18);
	datr_string.Format(_T("%x"),datr);
	m_EDIT_DACW.SetWindowText(datr_string);
	temp_float = datr*0.3922;
    m_EDIT_SHOWDAC.Format(_T("%.1f%s"),temp_float,"%");
	UpdateData(FALSE);
}

void CEvaluationDlg::OnBnClickedReadEval()
{
	int mask,regval;
	CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	OnBnClickedButtonDacr();
	if (!success){goto end;};

	regval = use_fanmotordlg_eval.rreg(0x01);
    if (!success){goto end;};
	mask=1;
	ad_tor_en=(regval>>3)&mask;

	regval = use_fanmotordlg_eval.rreg(0x10);
    if (!success){goto end;};
	mask=1;
	var_dac=(regval>>6)&mask;

	regval = use_fanmotordlg_eval.rreg(0x0a);
    if (!success){goto end;};
	mask=7;
	vardac_cnt=(regval>>4)&mask;
		
	OnBnClickedRpmCount();
	if (!success){goto end;};
	m_CHECK_ADTOR_EN.SetCheck(ad_tor_en);
	m_CHECK_VARDAC_EN.SetCheck(var_dac);
	m_COMBO_VARDAC_CNT.SetCurSel(vardac_cnt);

	spin_fan = pParent->dataread_anybits(0x04,0,1);
	if (!success){goto end;};
	pole = pParent->dataread_anybits(0x07,6,1);
	if (!success){goto end;};

	if(spin_fan==1){
            m_FAN.Open(_T("fan.avi"));
		    m_FAN.Play(0, (UINT)-1, (UINT)-1);
	}else{
		    m_FAN.Open(_T("fan.avi"));
		    m_FAN.Stop();
	}

end:; 
}
