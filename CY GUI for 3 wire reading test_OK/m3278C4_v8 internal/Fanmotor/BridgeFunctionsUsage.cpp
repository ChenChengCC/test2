#include "StdAfx.h"
#include "BridgeFunctionsUsage.h"

CBridgeFunctionsUsage::CBridgeFunctionsUsage(CUSB2IICcom_Exe* Bridge)
{
	this->Bridge = Bridge;
}

CBridgeFunctionsUsage::~CBridgeFunctionsUsage(void)
{
}

//--------------------------------------------------------------
// Initialization Functions
//--------------------------------------------------------------
void CBridgeFunctionsUsage::InitUSB()
{
        Bridge->InitUSB();
}

void CBridgeFunctionsUsage::InitUSB2IIC()
{
        Bridge->InitUSB2IIC(GetCurrentProcessId());
}

void CBridgeFunctionsUsage::UnInitUSB()
{
        Bridge->UnInitUSB();
}
//--------------------------------------------------------------
// Configuration and Status Functions
//--------------------------------------------------------------
void CBridgeFunctionsUsage::GetBridgeList()
{   VARIANT data = Bridge->GetBridgeList();
	SAFEARRAY FAR *List = data.parray;
	
	long highBound, lowBound, count;
	SafeArrayGetUBound(List, 1, &highBound);
	SafeArrayGetLBound(List, 1, &lowBound);
	count = highBound - lowBound + 1;

	CString str; 
	str.Format (L"Bridges Count: %d%s",count,L"\r\n");
	for (long i=lowBound; i<=highBound; i++){
	  LPCTSTR bridgeID;
	  SafeArrayGetElement(List,&i,&bridgeID);
      str += bridgeID;
      str += L"\r\n";
    }
	AfxMessageBox(str,MB_ICONINFORMATION | MB_OK);
}

void CBridgeFunctionsUsage::GetBridgeStatus()
{
	int lastError = Bridge->GetBridgeStatus(1);
	CString str;
	str.Format(L"Last operation status: %d",lastError);
	AfxMessageBox(str,MB_ICONINFORMATION | MB_OK);
}
void CBridgeFunctionsUsage::GetStatusMsg()
{
	CString msg = Bridge->GetStatusMsg(34);
	AfxMessageBox(msg,MB_ICONINFORMATION | MB_OK);
}
void CBridgeFunctionsUsage::GetBridgeVersion()
{
	VARIANT version; 
	VariantInit(&version);
    VARIANT r = Bridge->GetBridgeVersion(L"86A4D2890E0B", &version);
    if (r.bVal == 34) // operation finished successfully
    {
      CString str = L"Version = "; 
	  str += version.bstrVal;
      AfxMessageBox(str,MB_ICONINFORMATION | MB_OK);
    }
	VariantClear(&version);
}
void CBridgeFunctionsUsage::GetPowerSpeed()
{
	VARIANT Power, Speed, r;
    VariantInit(&Power);
	VariantInit(&Speed);
    r = Bridge->GetPowerSpeed(L"86A4D2890E0B", &Power, &Speed);
    if (r.bVal == 34) // operation finished successfully
    {
      int iPower = Power.intVal;
      int iSpeed = Speed.intVal;
      //...
	  CString str; str.Format(L"Power: %d\r\nSpeed: %d",iPower, iSpeed);
	  AfxMessageBox(str,MB_ICONINFORMATION | MB_OK);
    }
	VariantClear(&Power);
	VariantClear(&Speed);
}
void CBridgeFunctionsUsage::SetPower()
{
	VARIANT r = Bridge->SetPower(L"86A4D2890E0B", 0x01); //set +5V
    if (r.bVal != 34)
    {
	  AfxMessageBox(Bridge->GetStatusMsg(r.bVal),MB_ICONERROR | MB_OK);
    }
}
void CBridgeFunctionsUsage::SetSpeed()
{
	VARIANT r = Bridge->SetSpeed(L"86A4D2890E0B", 0x20); //set 100K
}
void CBridgeFunctionsUsage::ResetBridge()
{
	VARIANT r = Bridge->ResetBridge(L"86A4D2890E0B");
    if (r.bVal == 34)
      AfxMessageBox(L"I2C bus Reset Sucessfully!",MB_ICONINFORMATION | MB_OK);
    else
      AfxMessageBox(Bridge->GetStatusMsg(r.bVal),MB_ICONERROR | MB_OK);
}
void CBridgeFunctionsUsage::IsPowerDetected()
{
	signed char PowerStatus;
    VARIANT r = Bridge->IsPowerDetected(L"86A4D2890E0B", &PowerStatus);
    if (r.bVal == 34)
    {
      if (PowerStatus == 0)
          AfxMessageBox(L"No Power Detected",MB_ICONINFORMATION | MB_OK);
      else
          AfxMessageBox(L"POWERED",MB_ICONINFORMATION | MB_OK);
	}
}
void CBridgeFunctionsUsage::SetTimeoutPeriod()
{
    Bridge->SetTimeoutPeriod(2000);
}
//--------------------------------------------------------------
// I2C functions
//--------------------------------------------------------------
void CBridgeFunctionsUsage::GetDeviceList()
{
	VARIANT data = Bridge->GetDeviceList(L"86A4D2890E0B");
	int lastError = Bridge->GetBridgeStatus(1);
	if (lastError != 34) // failure of bus scanning
		AfxMessageBox(Bridge->GetStatusMsg(lastError),
		              MB_ICONERROR | MB_OK);
	else // bus scanned successfully
	{
		SAFEARRAY FAR *List = data.parray;
		long highBound, lowBound, count;
		SafeArrayGetUBound(List, 1, &highBound);
		SafeArrayGetLBound(List, 1, &lowBound);
		count = highBound - lowBound + 1;

		BYTE HUGEP *pDevice;
		CString s,strDevice;
		s.Format(L"Devices Count: %d\n\r",count-1);
		SafeArrayAccessData(List, (void HUGEP* FAR*)&pDevice);
		for (int i = 1; i < count; i++){
			int device = pDevice[i];
			strDevice.Format(L"0x%02X\r\n",device);
			s += strDevice;
		}
		SafeArrayUnaccessData(List);
		AfxMessageBox(s,MB_ICONINFORMATION | MB_OK);
	}
}
void CBridgeFunctionsUsage::SendIICdata()
{
	VARIANT FAR data;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;    // low bound is 0
	rgsabound[0].cElements = 8;  // number of elements is 8
	data.vt = VT_ARRAY | VT_UI1; // array of bytes
	data.parray = SafeArrayCreate(VT_UI1,1,rgsabound);
	for (long i=0; i<8; i++) {
		BYTE byte = (BYTE)i;
		SafeArrayPutElement(data.parray, &i, &byte);
	}
	VARIANT r = Bridge->SendIICdata(L"86A4D2890E0B", 0x00, data);
	if (r.bVal != 34) // Error occured
	{
		AfxMessageBox(Bridge->GetStatusMsg(r.bVal),
					  MB_ICONERROR | MB_OK);
	}
	else  // data sent successfully
	{ 
		//... 
	}
	SafeArrayDestroy(data.parray);
}
void CBridgeFunctionsUsage::ReadIICdata()
{
	VARIANT dataIn;
	VariantInit(&dataIn);
	long r = Bridge->ReadIICdata(L"86A4D2890E0B", 0x00, 5, &dataIn);
	if (r == 34) // data read successfully
	{
		CString s = L"Read 5 bytes from Device 0x00: ";
		CString strByte;
		for (long i = 0; i < 5; i++) {
			BYTE ReadByte;
			SafeArrayGetElement(dataIn.parray, &i, &ReadByte);
			strByte.Format(L"%02X ",ReadByte);
			s += strByte;
		}
		AfxMessageBox(s,MB_ICONINFORMATION | MB_OK);
	}
	VariantClear(&dataIn);
}
void CBridgeFunctionsUsage::ReadIICdataReg()
{
	CByteArray baAddr;
	baAddr.SetSize (2);   // 2 byte Address of EEPROM storage cell
	baAddr.SetAt(0,0x01); // High of 0x0100 EEPROM address
	baAddr.SetAt(1,0x00); // Low of 0x0100 EEPROM address
	COleVariant ReadAddress(baAddr); // Create ReadAddress argument
	VARIANT dataIn;
	VariantInit(&dataIn);
	long r = Bridge->ReadIICdataReg(L"86A4D2890E0B", 0x5B, ReadAddress, 
                                   3, &dataIn);
	if (r == 34) // data read successfully
	{
		CString s = L"Read data from addr 0x0100 of EEPROM Device 0x5B: ";
		CString strByte;
		for (long i = 0; i < 3; i++) {
			BYTE ReadByte;
			SafeArrayGetElement(dataIn.parray, &i, &ReadByte);
			strByte.Format(L"%02X ",ReadByte);
			s += strByte;
		}
		AfxMessageBox(s,MB_ICONINFORMATION | MB_OK);
	}
	VariantClear(&dataIn);
}
void CBridgeFunctionsUsage::AbortTransfer()
{
	Bridge->AbortTransfer();
}
