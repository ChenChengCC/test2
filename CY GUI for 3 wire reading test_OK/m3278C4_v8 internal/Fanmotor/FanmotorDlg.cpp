// FanmotorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "FanmotorDlg.h"
#include "debugDlg.h"
#include "conio.h"
//#include "okFrontPanelDLL.h"
#include "m8c.h"
#include "CUSB2IICcom_Exe.h"
#include "afxctl.h"
#include "USB2IICevent_Sink.h"
#include "BridgeFunctionsUsage.h"
#include "BridgeInfo.h"
#include "math.h"

CUSB2IICcom_Exe* Bridge;
CUSB2IICevent_Sink* BridgeEventSink;
DWORD dwCookie;
CString BridgeID;
BYTE DeviceAddress;
//Firmware data readback
#define fTACHO			0xff

int TIMEOUT = 100; // 1s
int comm_port=0; // 1=parallel port, 0=usb port
int sclk_freq=2; // sclk=50KHz
int pwm_freq=2; // pwm_freq=25KHz
int pwm_period=500;
int pwm_dc;
double duty_cycle1=50;
int duty_cycle2=50;
int pwm_in;
int slave_addr=0x92;
int success;

int spin_fan=0;
int pwm_on_mod=18;  // [4:0]=[4]MODE[1,0], [3:1]DEVICE[000--M8618, 001--M3278, 010--M2269], [0]PWM_ON

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CdebugDlg use_debugdlg_main;
CdetailDlg use_detaildlg_main;

// CFanmotorDlg dialog


CFanmotorDlg::CFanmotorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFanmotorDlg::IDD, pParent)
	, m_EDIT_SCL_FREQ(_T(""))
	, m_EDIT_PWM_FREQ(_T(""))
	, m_EDIT_PWM_DC(_T(""))
	, m_EDIT_MODE(_T(""))
	, m_EDIT_Tacho(_T(""))
	, m_edit_read_test(_T(""))
	, m_EDIT_Rtest(_T(""))
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_EDIT_PWM_DC2 = _T("");
}

void CFanmotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_EDIT_ADDR);
	DDX_Text(pDX, IDC_EDIT_SCL_FREQ, m_EDIT_SCL_FREQ);
	DDX_Text(pDX, IDC_EDIT_PWM_FREQ, m_EDIT_PWM_FREQ);
	DDX_Text(pDX, IDC_EDIT_PWM_DC, m_EDIT_PWM_DC);
	DDX_Control(pDX, IDC_CHECK_MODE, m_CHECK_MODE);
	DDX_Text(pDX, IDC_EDIT_MODE, m_EDIT_MODE);
	DDX_Control(pDX, IDC_CHECK_I2C, m_CHECK_I2C);
	DDX_Control(pDX, IDC_COMBO_PWMFREQ, m_COMBO_PWMFREQ);
	//  DDX_Control(pDX, IDC_EDIT_PWM_DC2, m_EDIT_PWM_DC2);
	DDX_Text(pDX, IDC_EDIT_PWM_DC2, m_EDIT_PWM_DC2);
	DDX_Control(pDX, IDC_EDIT_UpdatePWM1, m_EDIT_UpdatePWM1);
	DDX_Text(pDX, IDC_EDIT_Tacho, m_EDIT_Tacho);
	DDX_Control(pDX, IDC_EDIT_test, m_EDIT_test);
	DDX_Text(pDX, IDC_EDIT_test, m_edit_read_test);
	DDX_Text(pDX, IDC_EDIT_Rtest, m_EDIT_Rtest);
}

BEGIN_MESSAGE_MAP(CFanmotorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_NCDESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BUTTON_START, &CFanmotorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(ID_BUTTON_ABOUT, &CFanmotorDlg::OnBnClickedButtonAbout)
	ON_EN_CHANGE(IDC_EDIT_ADDR, &CFanmotorDlg::OnEnChangeEditAddr)
	ON_BN_CLICKED(ID_BUTTON_400KHZ, &CFanmotorDlg::OnBnClickedButton400khz)
	ON_BN_CLICKED(ID_BUTTON_200KHZ, &CFanmotorDlg::OnBnClickedButton200khz)
	ON_BN_CLICKED(ID_BUTTON_50KHZ, &CFanmotorDlg::OnBnClickedButton50khz)
	ON_BN_CLICKED(ID_BUTTON_10KHZ, &CFanmotorDlg::OnBnClickedButton10khz)
	ON_BN_CLICKED(ID_BUTTON_25KHZ, &CFanmotorDlg::OnBnClickedButton25khz)
	ON_BN_CLICKED(ID_BUTTON_70KHZ, &CFanmotorDlg::OnBnClickedButton70khz)
	ON_BN_CLICKED(ID_BUTTON_8KHZ, &CFanmotorDlg::OnBnClickedButton8khz)
	ON_BN_CLICKED(ID_BUTTON_80KHZ, &CFanmotorDlg::OnBnClickedButton80khz)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_UP, &CFanmotorDlg::OnBnClickedButtonPwmDcUp)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_DOWN, &CFanmotorDlg::OnBnClickedButtonPwmDcDown)
	ON_BN_CLICKED(ID_BUTTON_DEBUG, &CFanmotorDlg::OnBnClickedButtonDebug)
	ON_BN_CLICKED(ID_BUTTON_DETAIL, &CFanmotorDlg::OnBnClickedButtonDetail)
	ON_BN_CLICKED(IDC_CHECK_MODE, &CFanmotorDlg::OnBnClickedCheckMode)
	ON_BN_CLICKED(ID_BUTTON_EVALUATION, &CFanmotorDlg::OnBnClickedButtonEvaluation)
	ON_BN_CLICKED(ID_BUTTON_OTP, &CFanmotorDlg::OnBnClickedButtonOtp)
	ON_BN_CLICKED(ID_BUTTON_OTPCAL, &CFanmotorDlg::OnBnClickedButtonOtpcal)
	ON_BN_CLICKED(ID_BUTTON_TEST, &CFanmotorDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_CHECK_I2C, &CFanmotorDlg::OnBnClickedCheckI2c)
	ON_CBN_SELCHANGE(IDC_COMBO_PWMFREQ, &CFanmotorDlg::OnCbnSelchangeComboPwmfreq)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_UPSMALL, &CFanmotorDlg::OnBnClickedButtonPwmDcUpsmall)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_DOWNSMALL, &CFanmotorDlg::OnBnClickedButtonPwmDcDownsmall)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_UP2, &CFanmotorDlg::OnBnClickedButtonPwmDcUp2)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_DOWN3, &CFanmotorDlg::OnBnClickedButtonPwmDcDown3)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_UPSMALL2, &CFanmotorDlg::OnBnClickedButtonPwmDcUpsmall2)
	ON_BN_CLICKED(ID_BUTTON_PWM_DC_DOWNSMALL2, &CFanmotorDlg::OnBnClickedButtonPwmDcDownsmall2)
	ON_BN_CLICKED(IDC_BUTTON_UpdatePWM1, &CFanmotorDlg::OnBnClickedButtonUpdatepwm1)
	ON_BN_CLICKED(ID_BUTTON_INT_TEST, &CFanmotorDlg::OnBnClickedButtonIntTest)
	ON_BN_CLICKED(IDC_BUTTON_Tacho, &CFanmotorDlg::OnBnClickedButtonTacho)
	ON_BN_CLICKED(IDC_BUTTON_FW_ADTORQUE, &CFanmotorDlg::OnBnClickedButtonFwAdtorque)
	ON_BN_CLICKED(IDC_BUTTON_Wtest, &CFanmotorDlg::OnBnClickedButtonWtest)
	ON_BN_CLICKED(IDC_BUTTON_Rtest, &CFanmotorDlg::OnBnClickedButtonRtest)
END_MESSAGE_MAP()


// CFanmotorDlg message handlers

BOOL CFanmotorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	aboutdlg = NULL;
	debugdlg = NULL;
	detaildlg = NULL;
	otpdlg = NULL;
	otpcaldlg = NULL;
	evaluationdlg = NULL;
	testdlg = NULL;
	inttest = NULL;
	
	//CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	//*****************************************************
	/* set virtual_board=false for read back IC reg value.
	set virtual_board=true for read back virtual reg value.*/
	virtual_board=false;
	fOTP=0;
	//*****************************************************
		if(virtual_board==true)
		InitVirtualBoard();


    m_EDIT_ADDR.SetWindowText(_T("92"));
	m_EDIT_SCL_FREQ.Format(_T("400kHz"));
	UpdateData(FALSE);
	//m_EDIT_PWM_FREQ.Format(_T("25kHz"));
	//UpdateData(FALSE);
	m_EDIT_PWM_DC.Format(_T("%.0f%s"),duty_cycle1,"%");
	UpdateData(FALSE);
	m_EDIT_PWM_DC2.Format(_T("%d%s"),duty_cycle2,"%");
	UpdateData(FALSE);

	m_EDIT_MODE.Format(_T("ON"));
	UpdateData(FALSE);
	m_CHECK_MODE.SetCheck(1);
	//OnBnClickedButtonStart();
	

	linkupbridge();
	Sleep(1000);
	CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
    listBoxBridges->SetCurSel(0);//?

	//linkupdevice();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CFanmotorDlg::OnNcDestroy() 
{
	CDialog::OnNcDestroy();
}

void CFanmotorDlg::OnClose() 
{
	DestroyWindow();
}

void CFanmotorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CFanmotorDlg::OnOK() 
{
}

void CFanmotorDlg::OnCancel() 
{
}



void CFanmotorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFanmotorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFanmotorDlg::OnBnClickedButtonStart()
{
	CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
    listBoxBridges->SetCurSel(0);
	
	//setpower5v();
	setspeed400k();
	
		
	/*success = 0;
	// Initialize USB
	use_debugdlg_main.InitUSB();
	if (success){
		// Initialize FPGA with our configuration bitfile.
		use_debugdlg_main.InitFPGA();
		if (success){
			// Initialize PLL
			use_debugdlg_main.InitPLL();
			success = 1;

			pwm_dc=(pwm_period*duty_cycle1)/100;
			pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
			okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x03, pwm_in, 0xffff);// choose SCLK
			okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x04, pwm_on_mod, 0x001f);// choose PWM_IN
	        okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
	        Sleep(1);
		}
	}*/
}

//-----------------------------------------------------------------------
// EVENTS: Connect/Disconnect implementation
//-----------------------------------------------------------------------
void CFanmotorDlg::AddBridgeEvent(BSTR BridgeID)
{
	VARIANT version;
	CString dummyStr = L""; //Need this var in order to VariantClear() ->
	BSTR emptyStr = dummyStr.AllocSysString(); // works in case of empty Version string

	for (int i=0; i<5; i++)
	{	
		VariantInit(&version);
	    VARIANT r = Bridge->GetBridgeVersion(BridgeID, &version);
		Bridge->AbortTransfer(); // Deactivate Bridge (optionally) after "GetBridgeVersion" operation
		if (r.bVal == 34) break;// operation finished successfully
		else version.bstrVal = emptyStr;
	}
	CBridgeInfo* bridgeInfo = new CBridgeInfo(BridgeID,version.bstrVal);
	CString strInfo;
	bridgeInfo->GetBridgeInfo(strInfo);
	
	CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
	int index = listBoxBridges->AddString(strInfo);
	listBoxBridges->SetItemDataPtr(index, bridgeInfo);
	
	VariantClear(&version);
}

void CFanmotorDlg::RemoveBridgeEvent(BSTR BridgeID)
{
	int i;
	CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
	CBridgeInfo* bridgeInfo = NULL;
	
	for (i=0; i<listBoxBridges->GetCount(); i++)
	{
		bridgeInfo = (CBridgeInfo*)listBoxBridges->GetItemDataPtr(i);
		if (bridgeInfo->BridgeID == BridgeID) break;
	}
	if (i == listBoxBridges->GetCurSel())
	{
		CListBox* listBoxDevices = (CListBox*)GetDlgItem(IDC_DEVICE_LISTBOX);
		listBoxDevices->ResetContent();
//		ResetPowerSettings();
//		ResetSpeedSettings();
	}
	if ((i>=0)&&(i<=listBoxBridges->GetCount()))
	{
		delete bridgeInfo;
		listBoxBridges->DeleteString(i);
	}
}

void CFanmotorDlg::linkupbridge()
{
	if (Bridge!=NULL) return;
	//Initialize the COM library on the current thread
	CoInitialize(NULL);
	//Create Bridge Instance
	Bridge = new CUSB2IICcom_Exe();
	BOOL r = Bridge->CreateDispatch(L"USB2IIC.USB2IICcom_EXE");
	if (r == 0) {
		DisplayInforMessageBox((LPCWSTR)L"Error", L"Can't Connect to the USB2IIC Automation Object");
		delete Bridge;
		Bridge = NULL;
		CoUninitialize();
		return;
	}
	//Connect Events
	BridgeEventSink = new CUSB2IICevent_Sink();
	LPUNKNOWN pUnkSink = BridgeEventSink->GetIDispatch(FALSE);
	r = AfxConnectionAdvise(Bridge->m_lpDispatch,IID_IUSB2IICevent_Sink,pUnkSink,FALSE,&dwCookie);
	if (r==0){
		DisplayInforMessageBox((LPCWSTR)L"Error",L"Can't Connect Events");
	}
	// Start USB Communication with Bridge
	Bridge->InitUSB2IIC(GetCurrentProcessId());

	// set Reference to main dialog
	BridgeEventSink->dlgWnd = this;
}
void CFanmotorDlg::linkupdevice()
{
	//CString BridgeID;
    CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
    listBoxBridges->SetCurSel(0);
	
	setpower5v();
	setspeed400k();
/*	setpower3v();

	if (GetActiveBridge(BridgeID))
	{
		CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_DEVICE_LISTBOX);
		listBoxBridges->ResetContent();
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
		VARIANT data = Bridge->GetDeviceList(BridgeID);
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		//Process Result
		int lastError = Bridge->GetBridgeStatus(1);
		if (lastError != 34) // failure of bus scanning
			ErrorMsg(lastError);
		else // bus scanned successfully
		{
			SAFEARRAY FAR *List = data.parray;
			long highBound, lowBound, count;
			SafeArrayGetUBound(List, 1, &highBound);
			SafeArrayGetLBound(List, 1, &lowBound);
			count = highBound - lowBound + 1;
			if (count == 1) { //only 0s element, which indicates amount of devices found
				DisplayInforMessageBox((LPCWSTR)L"Error", L"No I2C devices can be found");
				return;
			}

			BYTE HUGEP *pDevice;
			CString strDevice;
			SafeArrayAccessData(List, (void HUGEP* FAR*)&pDevice);
			for (int i = 1; i < count; i++){
				int device = pDevice[i];
				strDevice.Format(L"0x%02X",device);
				listBoxBridges->AddString(strDevice);
			}
			SafeArrayUnaccessData(List);
		}
	}
   CListBox* listBoxDevices = (CListBox*)GetDlgItem(IDC_DEVICE_LISTBOX);
   listBoxDevices->SetCurSel(0);
   setspeed100k();  */
}
void CFanmotorDlg::ErrorMsg(int r) 
{
	CString msg = Bridge->GetStatusMsg(r);
    AfxMessageBox(msg, MB_ICONERROR | MB_OK, 0);
    if (r == 7) // If device is busy by another application
    {
		CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
		listBoxBridges->SetCurSel(-1);
		CListBox* listBoxDevices = (CListBox*)GetDlgItem(IDC_DEVICE_LISTBOX);
        listBoxDevices->ResetContent();
	//	ResetPowerSettings();
	//	ResetSpeedSettings();
        Bridge->AbortTransfer(); // Deactivate any Bridge (free port handle)
    }
}

bool CFanmotorDlg::GetActiveBridge(CString& BridgeID)
{
    CListBox* listBoxBridges = (CListBox*)GetDlgItem(IDC_BRIDGE_LISTBOX);
    listBoxBridges->SetCurSel(0);
	BridgeID = L"";
	if (listBoxBridges->GetCurSel() < 0) 
	{
		DisplayInforMessageBox((LPCWSTR)L"Error", L"Select Active BRIDGE!");
		return false;
	}
    CBridgeInfo* bridgeInfo = (CBridgeInfo*)listBoxBridges->GetItemDataPtr(listBoxBridges->GetCurSel());
	BridgeID = bridgeInfo->BridgeID;
	return true;
}

bool CFanmotorDlg::GetActiveDevice(BYTE& DeviceAddress)
{
	DeviceAddress = 255;
	CListBox* listBoxDevices = (CListBox*)GetDlgItem(IDC_DEVICE_LISTBOX);
	listBoxDevices->SetCurSel(0);
	if (listBoxDevices->GetCurSel() < 0) {
		DisplayInforMessageBox((LPCWSTR)L"Error", L"Select Active DEVICE!\r\nPress \"Device List\" button and Select Device");
		return false;
	}
	CString s;
	int n = listBoxDevices->GetTextLen(listBoxDevices->GetCurSel());
	WCHAR *ch, *buf = s.GetBuffer(n);
	listBoxDevices->GetText(listBoxDevices->GetCurSel(), buf);
	DeviceAddress = (BYTE)wcstol(buf,&ch,16);
	s.ReleaseBuffer();
	return true;
}

void CFanmotorDlg::setpowerext()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetPower(BridgeID, 0x00); //set External
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_POWER_EXT, BST_UNCHECKED);	
}

void CFanmotorDlg::setpower5v()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetPower(BridgeID, 0x01); //set +5V
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_POWER_5V, BST_UNCHECKED);	
}

void CFanmotorDlg::setpower3v()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetPower(BridgeID, 0x02); //set +3V
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_POWER_3V, BST_UNCHECKED);	
}

void CFanmotorDlg::setpowerPWM(int PWM)
{
	//CString BridgeID;

//	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetPower(L"0000011", PWM); //set +3V
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	//}
	//else
	//	CheckDlgButton(IDC_POWER_3V, BST_UNCHECKED);	
}

void CFanmotorDlg::setspeed400k()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x24); //set 400K
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_400K, BST_UNCHECKED);	
}

void CFanmotorDlg::UpdatePWM1()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x24); //set 400K pwm_sel=00
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_400K, BST_UNCHECKED);	
}

void CFanmotorDlg::UpdatePWM2()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x25); //set 400K pwm_sel=01
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_400K, BST_UNCHECKED);	
}


void CFanmotorDlg::setMode()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x24); //set bcontrol[7]=1 at 400k
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_400K, BST_UNCHECKED);	
}


void CFanmotorDlg::setspeed100k()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		//VARIANT r = Bridge->SetSpeed(BridgeID, 0x20); //set 100K
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x20); //set bcontrol[7]=1 at 100K
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_100K, BST_UNCHECKED);	
}

void CFanmotorDlg::setspeed50k()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
	//	VARIANT r = Bridge->SetSpeed(BridgeID, 0x28); //set 50K
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x28); //set bcontrol[7]=1 at 50K
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_50K, BST_UNCHECKED);
}

void CFanmotorDlg::setspeedreserve()
{
	CString BridgeID;
	if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetSpeed(BridgeID, 0x2C); //set reserved bits
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	}
	//else
	//	CheckDlgButton(IDC_SPEED_50K, BST_UNCHECKED);
}

void CFanmotorDlg::OnBnClickedButtonAbout()
{
	if(aboutdlg)
	{
		aboutdlg->SetForegroundWindow();
	}
	else
	{		
		aboutdlg = new CAboutDlg(this);
		aboutdlg->Create(IDD_ABOUTBOX,GetDesktopWindow());
		aboutdlg->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::OnBnClickedButtonDebug()
{
	if(debugdlg)
	{
		debugdlg->SetForegroundWindow();
	}
	else
	{		
		debugdlg = new CdebugDlg(this);
		debugdlg->Create(IDD_DIALOG_DEBUG,GetDesktopWindow());
		debugdlg->ShowWindow(SW_SHOW);
	}
}


void CFanmotorDlg::OnBnClickedButtonDetail()
{
	if(detaildlg)
	{
		detaildlg->SetForegroundWindow();
	}
	else
	{		
		detaildlg = new CdetailDlg(this);
		detaildlg->Create(IDD_DIALOG_DETAIL,GetDesktopWindow());
		detaildlg->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::OnBnClickedButtonEvaluation()
{
	if(evaluationdlg)
	{
		evaluationdlg->SetForegroundWindow();
	}
	else
	{		
		evaluationdlg = new CEvaluationDlg(this);
		evaluationdlg->Create(IDD_DIALOG_EVALUATION,GetDesktopWindow());
		evaluationdlg->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::OnEnChangeEditAddr()
{
	CString str;
	int length_dat;
	int dat = 0;

	// read user input
    m_EDIT_ADDR.GetWindowText(str);
	// get the string length of the inputs
	length_dat = m_EDIT_ADDR.LineLength();
	// convert input string into integer
	slave_addr = use_debugdlg_main.string2int(str, length_dat);
}

void CFanmotorDlg::OnBnClickedButton400khz()
{
	sclk_freq = 0;
	m_EDIT_SCL_FREQ.Format(_T("400kHz"));
	UpdateData(FALSE);
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
}

void CFanmotorDlg::OnBnClickedButton200khz()
{
	sclk_freq = 1;
	m_EDIT_SCL_FREQ.Format(_T("200kHz"));
	UpdateData(FALSE);
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
}

void CFanmotorDlg::OnBnClickedButton50khz()
{
	sclk_freq = 2;
	m_EDIT_SCL_FREQ.Format(_T("50kHz"));
	UpdateData(FALSE);
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
}

void CFanmotorDlg::OnBnClickedButton10khz()
{
	/*//if(pwm_on==1){goto end;};
	pwm_freq = 1;
	m_EDIT_PWM_FREQ.Format(_T("10kHz"));
	UpdateData(FALSE);
	pwm_period=1250;
	pwm_dc=(pwm_period*duty_cycle1)/100;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x03, pwm_in, 0xffff);// choose SCLK
	okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
	Sleep(1);
//end:;*/
}

void CFanmotorDlg::OnBnClickedButton25khz()
{
	/*//if(pwm_on==1){goto end;};
	pwm_freq = 2;
	m_EDIT_PWM_FREQ.Format(_T("25kHz"));
	UpdateData(FALSE);
	pwm_period=500;
	pwm_dc=(pwm_period*duty_cycle1)/100;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x03, pwm_in, 0xffff);// choose SCLK
	okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
	Sleep(1);
//end:;*/
}

void CFanmotorDlg::OnBnClickedButton70khz()
{
	/*//if(pwm_on==1){goto end;};
	pwm_freq = 3;
	m_EDIT_PWM_FREQ.Format(_T("70kHz"));
	UpdateData(FALSE);
	pwm_period=177.5;
	pwm_dc=(pwm_period*duty_cycle1)/100;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x03, pwm_in, 0xffff);// choose SCLK
	okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
	Sleep(1);
//end:;*/
}

void CFanmotorDlg::OnBnClickedButton8khz()
{
	/*//if(pwm_on==1){goto end;};
	pwm_freq = 0;
	m_EDIT_PWM_FREQ.Format(_T("8kHz"));
	UpdateData(FALSE);
	pwm_period=1562.5;
	pwm_dc=(pwm_period*duty_cycle1)/100;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x03, pwm_in, 0xffff);// choose SCLK
	okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
	Sleep(1);
//end:;*/
}

void CFanmotorDlg::OnBnClickedButton80khz()
{
	/*CString pwm_dc_s, pwm_in_s;

	//if(pwm_on==1){goto end;};
	pwm_freq = 4;
	m_EDIT_PWM_FREQ.Format(_T("80kHz"));
	UpdateData(FALSE);
	pwm_period=156.25;
	pwm_dc=(pwm_period*duty_cycle1)/100;
	pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x03, pwm_in, 0xffff);// choose SCLK
	okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
	Sleep(1);
//end:;*/
}

void CFanmotorDlg::OnBnClickedButtonPwmDcUp()
{
	int gain_counter=0;
    int gain_step=5; //duty_cycle1 step
	int pulse_width1;

    //if(pwm_on==1){goto end;};
	if(duty_cycle1 < 100){
	   do {
	    	gain_counter++;	
		    duty_cycle1++;
	      }while ((gain_counter != gain_step) && (duty_cycle1 <100));

	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   pulse_width1=(255*duty_cycle1)/100;
	   //use_debugdlg_main.OnBnClickedSpeed50k();
	   //setspeed50k();
	  // setMode();
	   //Sleep(1000);
	   setpowerPWM(pulse_width1);//pass DC value through firmware bpower register
	   UpdatePWM1();
	   //SetPwm(pulse_width1);
	   //setspeed400k();//exit Mode
	   //Sleep(1);
	   m_EDIT_PWM_DC.Format(_T("%.0f%s"),duty_cycle1,"%");
	   UpdateData(FALSE);
	}
//end:;	
}

void CFanmotorDlg::OnBnClickedButtonPwmDcDown()
{
	int gain_counter=0;
	int gain_step=5; //duty_cycle1 step
	int pulse_width1;

	//if(pwm_on==1){goto end;};
	if(duty_cycle1 > 0){
	   do {
	    	gain_counter++;	
		    duty_cycle1--;
	   }while ((gain_counter != gain_step) && (duty_cycle1 >0));
	   
	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   pulse_width1=(255*duty_cycle1)/100;
	   // setspeed50k();
	//	setMode();
		//SetPwm(pulse_width1);//pass DC value through I2C block
		setpowerPWM(pulse_width1);
		UpdatePWM1();
		//setspeed400k();
	   //Sleep(1);
	   m_EDIT_PWM_DC.Format(_T("%.0f%s"),duty_cycle1,"%");
	   UpdateData(FALSE);
	}		
//end:;
}



void CFanmotorDlg::OnBnClickedCheckMode()
{
	/*static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_MODE.GetCheck();
	
	if(check == TRUE){
		pwm_on_mod=18;  // ON mode, 0x04[4]=1
		okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x04, pwm_on_mod, 0x001f);// choose PWM_IN
		okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
		m_EDIT_MODE.Format(_T("ON"));
	    UpdateData(FALSE);
	}else if(check == FALSE){
		pwm_on_mod=2;  // OFF mode, 0x04[4]=0
		okUsbFrontPanel_SetWireInValue(use_debugdlg_main.xem, 0x04, pwm_on_mod, 0x001f);// choose PWM_IN
		okUsbFrontPanel_UpdateWireIns(use_debugdlg_main.xem);
		m_EDIT_MODE.Format(_T("OFF"));
	    UpdateData(FALSE);
	}
	*/
}



void CFanmotorDlg::OnBnClickedButtonOtp()
{
	if(otpdlg)
	{
		otpdlg->SetForegroundWindow();
	}
	else
	{		
		otpdlg = new COTPDlg(this);
		otpdlg->Create(IDD_DIALOG_OTP,GetDesktopWindow());
		otpdlg->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::OnBnClickedButtonOtpcal()
{
	if(otpcaldlg)
	{
		otpcaldlg->SetForegroundWindow();
	}
	else
	{		
		otpcaldlg = new COTPcalDlg(this);
		otpcaldlg->Create(IDD_DIALOG_OTPCAL,GetDesktopWindow());
		otpcaldlg->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::OnBnClickedButtonTest()
{
	if(testdlg)
	{
		testdlg->SetForegroundWindow();
	}
	else
	{		
		testdlg = new CTestDlg(this);
		testdlg->Create(IDD_DIALOG_TEST,GetDesktopWindow());
		testdlg->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::OnBnClickedCheckI2c()
{
	static BOOL check = FALSE;
	CString datbits;
	
	check = m_CHECK_I2C.GetCheck();
	
	if(check == TRUE){
		wreg(0x2a,6);
		wreg(0x3d,5);
	}else if(check == FALSE){
		wreg(0x3d,0);
		wreg(0x2a,0);
	}
	
}

void CFanmotorDlg::OnCbnSelchangeComboPwmfreq()
{
	int seln;
	CString datbits;

	seln = m_COMBO_PWMFREQ.GetCurSel();	
	if(seln==0){
		OnBnClickedButton8khz();
	}else if(seln==1){
		OnBnClickedButton10khz();
	}else if(seln==2){
		OnBnClickedButton25khz();
	}else if(seln==3){
		OnBnClickedButton70khz();
	}else if(seln==4){
		OnBnClickedButton80khz();
	}

}


void CFanmotorDlg::OnBnClickedButtonPwmDcUpsmall()
{
	int gain_counter=0;
    int gain_step=1; //duty_cycle1 step
	int pulse_width1;

    //if(pwm_on==1){goto end;};
	if(duty_cycle1 < 100){
	   do {
	    	gain_counter++;	
		    duty_cycle1++;
	   }while (gain_counter != gain_step);

	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   pulse_width1=(255*duty_cycle1)/100;
	   setpowerPWM(pulse_width1);
		UpdatePWM1();
	   //Sleep(1);
	   m_EDIT_PWM_DC.Format(_T("%.0f%s"),duty_cycle1,"%");
	   UpdateData(FALSE);
	}
//end:;	
}


void CFanmotorDlg::OnBnClickedButtonPwmDcDownsmall()
{
	int gain_counter=0;
	int gain_step=1; //duty_cycle1 step
    int pulse_width1;

	//if(pwm_on==1){goto end;};
	if(duty_cycle1 > 0){
	   do {
	    	gain_counter++;	
		    duty_cycle1--;
	   }while (gain_counter != gain_step);
	   
	   pulse_width1=(255*duty_cycle1)/100;
	   setpowerPWM(pulse_width1);
		UpdatePWM1();
	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   //Sleep(1);
	   m_EDIT_PWM_DC.Format(_T("%.0f%s"),duty_cycle1,"%");
	   UpdateData(FALSE);
	}		
//end:;
}
// Read Operation
int CFanmotorDlg::rreg(int reg_addr)
{
success=1;

	CString s;
	int dat=0;
	long r;
	int timeout_counter=0;
	CByteArray baAddr;
	baAddr.SetSize (1);   
	baAddr.SetAt(0,reg_addr); 
	COleVariant ReadAddress(baAddr); // Create ReadAddress argument
	VARIANT dataIn;
	VariantInit(&dataIn);
	int datalen=2;//in bytes

	if(this->virtual_board)
	{
		dat = ReadVirtualBoardReg(reg_addr, fOTP);
	}

	else
	{
		r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress,datalen, &dataIn); 
		//r = Bridge->ReadIICdataReg(L"0000011", reg_addr, ReadAddress,datalen, &dataIn); 
		//Sleep(500);
		//r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress,datalen, &dataIn);//no data received.????
		//do{
		//	timeout_counter++;
		//	if (timeout_counter == TIMEOUT){
		//		DisplayInforMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Device is not available.\nPlease check your hardware connection and power supply!");
		//		success = 0;
		//	}
		//	r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress,datalen, &dataIn); 
		//}while ((r !=34) && (timeout_counter != TIMEOUT));

			CString strByte;
			for (long i = 0; i < datalen; i++) {
				BYTE ReadByte;
				SafeArrayGetElement(dataIn.parray, &i, &ReadByte);
				strByte.Format(L"%02x",ReadByte);
				s += strByte;
			}
			dat=use_debugdlg_main.string2int(s,2*datalen);
		//	success=1;
		//}
		//else {ErrorMsg(r);};
		VariantClear(&dataIn);
	}
	return dat;
	Sleep(20);
}

// Write Operation
void CFanmotorDlg::wreg(int reg_addr, int datr)
{
	success=1;

	VARIANT r;
	CByteArray baData;
	CStringArray dataStr;

	//separate input 2 bytes datr into 1byte + 1byte
	int datrH=datr/256;
	int datrL=datr%256;

	CString regstring;
	regstring.Format(_T("%02x "),reg_addr);
	CString strinputH;
    strinputH.Format(_T("%02x "),datrH);
	CString strinputL;
    strinputL.Format(_T("%02x"),datrL);

	CString str = regstring+strinputH+strinputL;

	
	int timeout_counter=0;

	if(this->virtual_board)
	{
		WriteVirtualBoardReg(reg_addr, datr, fOTP);
		return;
	}


	int parseResult = ParseString(dataStr,str);
	if (parseResult != -1){
		AfxMessageBox(L"Incorrect Data (\""+dataStr[parseResult]+L"\") is Typed. Please correct it",
						MB_ICONERROR | MB_OK,0);
		return;
	}
	else{
		if (dataStr.GetSize() == 0) {
			AfxMessageBox(L"Type some HEX data to send!",MB_ICONERROR | MB_OK,0);
			return;
		}
	}
	for (int i=0; i<dataStr.GetSize(); i++) {
		WCHAR *ch,*buf;
		buf = dataStr[i].GetBuffer(dataStr[i].GetLength());
		BYTE dataByte = (BYTE)wcstol(buf,&ch,16);
		dataStr[i].ReleaseBuffer();
		baData.Add(dataByte);
	}

	COleVariant data(baData); // Create array of Data
	// Send Data To Bridge

	r = Bridge->SendIICdata(L"0000011", 0x49, data);//spi comm, no acknowledge signal return to r.cannot check connection success.

	//do{
	//	timeout_counter++;
	//	if (timeout_counter == TIMEOUT){
	//		DisplayInforMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Device is not available.\nPlease check your hardware connection and power supply!");
	//		success = 0;
	//	}
	//	r = Bridge->SendIICdata(L"0000011", 0x49, data); 
	//}while ((r.bVal != 34) && (timeout_counter != TIMEOUT));

    Sleep(20);
end:;
}
int CFanmotorDlg::ParseString(CStringArray& strArray, CString& str)
{
	CString strTemp;
	int i=0, iStart, result, badWordIndex;
	result = -1; // successfully parsed
	badWordIndex = 0;
	while (i<str.GetLength())
	{
		while (iswspace(str[i])){
			i++;
			if (i>=str.GetLength()) goto stop_scanning;
		}
		iStart = i;
		while (!iswspace(str[i])){
			if (!isxdigit(str[i])) if (result==-1) result = badWordIndex;
			i++;
			if (i>=str.GetLength()) break;
		}
		strTemp = str.Mid(iStart, i-iStart);
		if (strTemp.GetLength()>2) if (result==-1) result = badWordIndex;
		strArray.Add(strTemp);
		badWordIndex++;
	}
stop_scanning:
	return result;
}
void CFanmotorDlg::SetPwm(int pulse_width1)
{
		
	//if (GetActiveBridge(BridgeID)){
		VARIANT r = Bridge->SetSpeed(L"0000011", 0x28); //set 50k
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	//}
	//setspeed50k();
	//CString BridgeID;
	wreg(0x35,pulse_width1);

	//if (GetActiveBridge(BridgeID)){
		r = Bridge->SetSpeed(L"0000011", 0x24); //set 400K
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	//}
	//Sleep(1000);
	//if (GetActiveBridge(BridgeID)){
	//	Bridge->SetSpeed(BridgeID, 0x28); //set 5K
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	//OnBnClickedSpeed50k();
	//OnBnClickedSpeedReserve();
	//Sleep(1000);
	// 		Bridge->SetSpeed(BridgeID, 0x20); //set 100K
		//if (r.bVal != 34) ErrorMsg(r.bVal);
	//setspeed400k();
	//Sleep(1);
	//OnBnClickedSpeed400k();
	//Sleep(1000);
	//OnBnClickedSpeedReserve();
	//Sleep(1000);
	//OnBnClickedSpeed100k();
	
}

void CFanmotorDlg::OnBnClickedButtonPwmDcUp2()
{
	// TODO: Add your control notification handler code here
	int gain_counter=0;
    int gain_step=5; //duty_cycle1 step
	int pulse_width2;

    //if(pwm_on==1){goto end;};
	if(duty_cycle2 < 100){
	   do {
	    	gain_counter++;	
		    duty_cycle2++;
	      }while ((gain_counter != gain_step) && (duty_cycle2 <100));

	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   pulse_width2=(255*duty_cycle2)/100;
	   //use_debugdlg_main.OnBnClickedSpeed50k();
	   //setspeed400k();
	   //setMode();
	   setpowerPWM(pulse_width2);//pass DC value through firmware bpower register
	   UpdatePWM2();
	   //setspeed400k();
	   //Sleep(1);
	   m_EDIT_PWM_DC2.Format(_T("%d%s"),duty_cycle2,"%");
	   UpdateData(FALSE);
	}
//end:;	
}


void CFanmotorDlg::OnBnClickedButtonPwmDcDown3()
{
	// TODO: Add your control notification handler code here
	int gain_counter=0;
	int gain_step=5; //duty_cycle1 step
	int pulse_width2;

	//if(pwm_on==1){goto end;};
	if(duty_cycle2 > 0){
	   do {
	    	gain_counter++;	
		    duty_cycle2--;
	   }while ((gain_counter != gain_step) && (duty_cycle2 >0));
	   
	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   pulse_width2=(255*duty_cycle2)/100;
	  // setspeed50k();
		//setMode();
	    setpowerPWM(pulse_width2);
		UpdatePWM2();
		//setspeed400k();
	   //Sleep(1);
	   m_EDIT_PWM_DC2.Format(_T("%d%s"),duty_cycle2,"%");
	   UpdateData(FALSE);
	}		
//end:;
}


void CFanmotorDlg::OnBnClickedButtonPwmDcUpsmall2()
{
	// TODO: Add your control notification handler code here
	int gain_counter=0;
    int gain_step=1; //duty_cycle1 step
	int pulse_width2;

    //if(pwm_on==1){goto end;};
	if(duty_cycle2 < 100){
	   do {
	    	gain_counter++;	
		    duty_cycle2++;
	   }while ((gain_counter != gain_step) && (duty_cycle2 <100));

	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   pulse_width2=(255*duty_cycle2)/100;
	   setpowerPWM(pulse_width2);//pass DC value through firmware bpower register
	   UpdatePWM2();
	   //Sleep(1);
	   m_EDIT_PWM_DC2.Format(_T("%d%s"),duty_cycle2,"%");
	   UpdateData(FALSE);
	}
//end:;	
}


void CFanmotorDlg::OnBnClickedButtonPwmDcDownsmall2()
{
	// TODO: Add your control notification handler code here
	int gain_counter=0;
	int gain_step=1; //duty_cycle1 step
    int pulse_width2;

	//if(pwm_on==1){goto end;};
	if(duty_cycle2 > 0){
	   do {
	    	gain_counter++;	
		    duty_cycle2--;
	   }while (gain_counter != gain_step);
	   
	   pulse_width2=(255*duty_cycle2)/100;
	   setpowerPWM(pulse_width2);//pass DC value through firmware bpower register
	   UpdatePWM2();
	   //pwm_dc=(pwm_period*duty_cycle1)/100;
	   //pwm_in = (pwm_dc<<5)+(pwm_freq<<2)+sclk_freq;
	   //Sleep(1);
	   m_EDIT_PWM_DC2.Format(_T("%d%s"),duty_cycle2,"%");
	   UpdateData(FALSE);
	}		
//end:;
}


void CFanmotorDlg::OnBnClickedButtonUpdatepwm1()
{
	// TODO: Add your control notification handler code here
		int PWM_duty_cycle_percent;
		int length;
		int pulse_width1;
		CString PWM_duty_cycle_str,PWM_Hex_str;

		m_EDIT_UpdatePWM1.GetWindowText(PWM_duty_cycle_str);
		duty_cycle1=_wtof(PWM_duty_cycle_str);

	    if((duty_cycle1 <= 100) && (duty_cycle1 >= 0))
	    {
	        pulse_width1=(255*duty_cycle1)/100;
	    	setpowerPWM(pulse_width1);
			UpdatePWM1();

	    	m_EDIT_PWM_DC.Format(_T("%.0f%s"),duty_cycle1,"%");
		    UpdateData(FALSE);
    	}
}

CString CFanmotorDlg::GetFirmwareVersion()
{
	CString str;
	VARIANT FVersion;
	VariantInit(&FVersion);
	VARIANT r = Bridge->GetBridgeVersion(L"0000011", &FVersion);
	if (r.bVal == 34) // operation finished successfully 
	{ 
		str = L"Version = "; 
		str += FVersion.bstrVal; 
		//AfxMessageBox(str,MB_ICONINFORMATION | MB_OK); 
	} 
	VariantClear(&FVersion);
	return str;
}

void CFanmotorDlg::OnBnClickedButtonIntTest()
{
	// TODO: Add your control notification handler code here
		if(inttest)
	{
		inttest->SetForegroundWindow();
	}
	else
	{		
		inttest = new CIntTest(this);
		inttest->Create(IDD_DIALOG_INT_TEST,GetDesktopWindow());
		inttest->ShowWindow(SW_SHOW);
	}
}

void CFanmotorDlg::InitVirtualBoard(void)
{
	//load reg in file "no_board.txt" to virtual_board_reg[256].
	for (int i=0; i<256; i++)
	{
		this->virtual_board_reg[i]=0;
		this->virtual_board_otp[i]=0;
	}
	//FILE *fpi;
	//const TCHAR* fpi_name=L"no_board.txt";
	//if(_wfopen_s(&fpi,fpi_name,L"r")!=0)
	//{
	//	DisplayInforMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"no_board.txt File Not Found.");
	//	success=0;
	//	return;
	//}

	////load register value from file to array
	//int regaddr, regvalue;
	//int j = 0;
	//while(1)
	//{
	//	regaddr = 0xffff; regvalue = 0xffff;
	//	j = fscanf_s(fpi,"Reg%xh %x\n", &regaddr, &regvalue);
	//	if (j == EOF)
	//			break;
	//	this->virtual_board_reg[regaddr] = regvalue;
	//}
	//fclose(fpi);
}

void CFanmotorDlg::WriteVirtualBoardReg(int reg_addr, int reg_value, int fOTP)
{
	if (fOTP==0)
	{
		if(reg_addr <= 255 && this->virtual_board)
			this->virtual_board_reg[reg_addr] = reg_value;
		else
			return;
	}
	else
	{
		if(reg_addr <= 255 && this->virtual_board)
			this->virtual_board_otp[reg_addr] = reg_value;
		else
			return;
	}
}

int CFanmotorDlg::ReadVirtualBoardReg(int reg_addr, int fOTP)
{
	if (fOTP==0)
	{
		if(this->virtual_board && reg_addr <= 255)
			return virtual_board_reg[reg_addr];
		return -1;
	}
	else
	{
		if(this->virtual_board && reg_addr <= 255)
			return virtual_board_otp[reg_addr];
		return -1;
	}

}

void CFanmotorDlg::dataupdate_anybits(int addr, int ind, CString datbits,int length)
{
		
	int temp,datupdated;
	CString datbintemp;
	temp = rreg(addr);
	if (!success){goto end;};
	datbintemp = int2bin(temp);

	for(int i = 0;i<length;i++){
		datbintemp.SetAt(ind+i,datbits[i]);
	}

	datupdated = bin2int(datbintemp);
	wreg(addr,datupdated);
	if (!success){goto end;};
    end:;
}

int CFanmotorDlg::dataread_anybits(int addr,int ind,int length)
{
	int datr,datr_section;
	CString datstring,dat_section;
	datr = rreg(addr);
	if (!success){goto end;};
	datstring = int2bin(datr);
	for(int i=0;i<length;i++){
		dat_section += datstring[ind + i];
	}

	datr_section = bin2intwl(dat_section,length);
	return datr_section;
    end:;
}

CString CFanmotorDlg::int2bin(int dec)
{
	CString result;
	int i;
	for(i = 7; i >=0; i--) {
		if(dec%2){
			result += "1";
		} 
		else {
			result += "0";
		}
	dec = dec/2;
	}
	result.MakeReverse();
	return result;
}

CString CFanmotorDlg::int2bin_anybits(int dec, int length)
{
	CString result;
	int i;
	for(i = (length - 1); i >=0; i--) {
		if(dec%2){
			result += "1";
		} 
		else {
			result += "0";
		}
	dec = dec/2;
	}
	result.MakeReverse();
	return result;
}

int CFanmotorDlg::bin2int(CString datb)
{	
	int i,intform;
	intform = 0;
	for(i=0;i<=7;i++){
		if(datb[i] == '1'){
			intform += pow(2.0,(7-i));
		}
	}
	return intform;
}

int CFanmotorDlg::bin2intwl(CString datb, int length)
{	
	int i,intform;
	intform = 0;
	for(i=0;i<length;i++){
		if(datb[i] == '1'){
			intform += pow(2.0,(length-1-i));
		}
	}
	return intform;
}

void CFanmotorDlg::OnBnClickedButtonTacho()
{
	// TODO: Add your control notification handler code here
	int TachoFreq = 0;
	int TachoLen = 2;
	
	//disable button
	GetDlgItem(IDC_BUTTON_Tacho)->EnableWindow(FALSE);

	GetTachoFreq();

	m_EDIT_Tacho.Format(_T("%s"), L"Reading...");
	UpdateData(FALSE);

	TachoFreq = rFWData(fTACHO,TachoLen);
	//TachoFreq = rreg(fTACHO);

	m_EDIT_Tacho.Format(_T("%d"), TachoFreq);
	UpdateData(FALSE);

	//enable button
	GetDlgItem(IDC_BUTTON_Tacho)->EnableWindow(TRUE);
}

int CFanmotorDlg::rFWData(int fType, int nByte)
{
	success=1;
	CString s;
	int dat=0;
	int timeout_counter=0;
	long r;
	CByteArray baAddr;
	baAddr.SetSize (1);   
	baAddr.SetAt(0,fType); 
	COleVariant ReadAddress(baAddr); // Create ReadAddress argument
	VARIANT dataIn;
	VariantInit(&dataIn);

	///*Sleep(50);*/
	//long r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress, 
 //                                  1, &dataIn);  
	do{
		timeout_counter++;
		if (timeout_counter == TIMEOUT){
			DisplayInforMessageBox((LPCWSTR)L"Error", (LPCWSTR)L"Device is not available.\nPlease check your hardware connection and power supply!");
			success = 0;
		}
		r = Bridge->ReadIICdataReg(L"0000011", 0x49, ReadAddress,nByte, &dataIn); 
	}while ((r !=34) && (timeout_counter != TIMEOUT));
	//{
		CString strByte;
		for (long i = 0; i < nByte; i++) {
			BYTE ReadByte;
			SafeArrayGetElement(dataIn.parray, &i, &ReadByte);
			strByte.Format(L"%02x",ReadByte);
			s += strByte;
		}
		dat=use_debugdlg_main.string2int(s,2*nByte);
		success=1;
	//}
	//else {ErrorMsg(r);};
	VariantClear(&dataIn);
	return dat;	
}

void CFanmotorDlg::GetTachoFreq()//bcontrol[4]=PWM/SCLK=0,set50k(10b),mode_sel=10
{
		Bridge->SetSpeed(L"0000011", 0x2a);
}

int CFanmotorDlg::DisplayErrorMessageBox(LPCTSTR msgTitle, LPCTSTR msgText)
{
    int msgboxID = MessageBox(
		(_T("\r\n%s"), msgText),
        (_T("\r\n%s"), msgTitle),
        MB_ICONSTOP | MB_OK | MB_DEFBUTTON1
    );

    switch (msgboxID)
    {
    case IDOK:
        break;
    }
    return msgboxID;
}

int CFanmotorDlg::DisplayInforMessageBox(LPCTSTR msgTitle, LPCTSTR msgText)
{
    int msgboxID = MessageBox(
		(_T("\r\n%s"), msgText),
        (_T("\r\n%s"), msgTitle),
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1
    );

    switch (msgboxID)
    {
    case IDOK:
        break;
    }
    return msgboxID;
}

int CFanmotorDlg::DisplayQueryMessageBox(LPCTSTR msgTitle, LPCTSTR msgText)
{
    int msgboxID = MessageBox(
		(_T("\r\n%s"), msgText),
        (_T("\r\n%s"), msgTitle),
        MB_ICONQUESTION | MB_OKCANCEL | MB_DEFBUTTON1
    );

    return msgboxID;
}

void CFanmotorDlg::OnBnClickedButtonFwAdtorque()
{
	// TODO: Add your control notification handler code here
	//if(fwtordlg)
	//{
	//	fwtordlg->SetForegroundWindow();
	//}
	//else
	//{		
	//	fwtordlg = new CFWTOR(this);
	//	fwtordlg->Create(IDD_DIALOG_FW_ADTORQUE,GetDesktopWindow());
	//	fwtordlg->ShowWindow(SW_SHOW);
	//}
}


void CFanmotorDlg::OnBnClickedButtonWtest()
{
	// TODO: Add your control notification handler code here
		int data = 0x23;
//// CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
//	// read user inputs
//	m_EDIT_test.GetWindowText(datw);
//	// get the string length of the inputs
//	length_dat = m_EDIT_test.LineLength();
//	if (length_dat == 0){return;};
//	// convert input string into integer
//	dat = string2int(datw, length_dat);
	// write reg
	wreg(0x01,data);
}


void CFanmotorDlg::OnBnClickedButtonRtest()
{
	// TODO: Add your control notification handler code here
		int datr = 0;
	//CFanmotorDlg* pParent = (CFanmotorDlg*)m_pParent;
	// read reg
	datr = rreg(0x81);//MSB is R/W bit!!!!!!!!!!!!
    
	// display data
	m_EDIT_Rtest.Format(_T("%x"), datr);
	UpdateData(FALSE);
}
