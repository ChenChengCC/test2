// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#pragma once

//#import "F:\\WORK\\C#\\PSoC_Express\\ActiveX\\ActiveX_Sources\\05_21_2007_ISSP+\\USB2IIC.exe" no_namespace
// CUSB2IICcom_Exe wrapper class
#import "C:\\USB2IIC.exe" no_namespace


class CUSB2IICcom_Exe : public COleDispatchDriver
{
public:
	CUSB2IICcom_Exe(){} // Calls COleDispatchDriver default constructor
	CUSB2IICcom_Exe(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CUSB2IICcom_Exe(const CUSB2IICcom_Exe& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IUSB2IICcom_Exe methods
public:
	VARIANT GetBridgeList()
	{
		VARIANT result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT GetDeviceList(LPCTSTR BridgeID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID);
		return result;
	}
	VARIANT DataTransfer(LPCTSTR BridgeID, unsigned char DeviceAddr, long Mode, long DataLen, VARIANT& InData, long SyncMode, VARIANT * OutData)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_UI1 VTS_I4 VTS_I4 VTS_VARIANT VTS_I4 VTS_PVARIANT ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, DeviceAddr, Mode, DataLen, &InData, SyncMode, OutData);
		return result;
	}
	signed char GetBridgeStatus(signed char WhatStatus)
	{
		signed char result;
		static BYTE parms[] = VTS_I1 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I1, (void*)&result, parms, WhatStatus);
		return result;
	}
	void AbortTransfer()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT DataTransferBurst(LPCTSTR BridgeID, unsigned char DeviceAddr, long DataLen)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_UI1 VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, DeviceAddr, DataLen);
		return result;
	}
	void StopBurstMode(LPCTSTR BridgeID)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, BridgeID);
	}
	void InitUSB()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void UnInitUSB()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT SetPower(LPCTSTR BridgeID, long Power)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, Power);
		return result;
	}
	VARIANT SetSpeed(LPCTSTR BridgeID, long Speed)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, Speed);
		return result;
	}
	VARIANT GetPowerSpeed(LPCTSTR BridgeID, VARIANT * Power, VARIANT * Speed)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, Power, Speed);
		return result;
	}
	VARIANT GetBridgeVersion(LPCTSTR BridgeID, VARIANT * Version)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT ;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, Version);
		return result;
	}
	VARIANT ResetBridge(LPCTSTR BridgeID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID);
		return result;
	}
	VARIANT SendIICdata(LPCTSTR BridgeID, long DeviceAddress, VARIANT& Data)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_VARIANT ;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, DeviceAddress, &Data);
		return result;
	}
	long ReadIICdata(LPCTSTR BridgeID, long DeviceAddress, long DataLen, VARIANT * DataIn)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_PVARIANT ;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, BridgeID, DeviceAddress, DataLen, DataIn);
		return result;
	}
	long ReadIICdataReg(LPCTSTR BridgeID, long DeviceAddress, VARIANT& ReadAddr, long DataLen, VARIANT * DataIn)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_VARIANT VTS_I4 VTS_PVARIANT ;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, BridgeID, DeviceAddress, &ReadAddr, DataLen, DataIn);
		return result;
	}
	CString GetStatusMsg(long MsgCode)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, MsgCode);
		return result;
	}
	void InitUSB2IIC(long ProcessID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ProcessID);
	}
	VARIANT ISSP_GetSupportedFamilyList()
	{
		VARIANT result;
		InvokeHelper(0xd3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT ISSP_Init(LPCTSTR BridgeID, LPCTSTR ICtype, signed char PowerMode, LPCTSTR HexFile, VARIANT * Blocks, BSTR * ChipID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I1 VTS_BSTR VTS_PVARIANT VTS_PBSTR ;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, ICtype, PowerMode, HexFile, Blocks, ChipID);
		return result;
	}
	VARIANT ISSP_ProgramBlock(long * BlockID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0xd5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BlockID);
		return result;
	}
	VARIANT ISSP_Abort()
	{
		VARIANT result;
		InvokeHelper(0xd6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT ISSP_ProgramAll(LPCTSTR BridgeID, LPCTSTR ICtype, signed char PowerMode, LPCTSTR HexFile, VARIANT * Blocks, BSTR * ChipID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I1 VTS_BSTR VTS_PVARIANT VTS_PBSTR ;
		InvokeHelper(0xd7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, ICtype, PowerMode, HexFile, Blocks, ChipID);
		return result;
	}
	void SetTimeoutPeriod(long timeout)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, timeout);
	}
	VARIANT ISSP_GetFamilyList()
	{
		VARIANT result;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT ISSP_GetFamilyICsList(LPCTSTR Family)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Family);
		return result;
	}
	VARIANT ISSP_GetICInfo(LPCTSTR Name, long * Pins, long * Flash, signed char * PowerMode)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_PI4 VTS_PI4 VTS_PI1 ;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Name, Pins, Flash, PowerMode);
		return result;
	}
	VARIANT IsPowerDetected(LPCTSTR BridgeID, signed char * PowerStatus)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_PI1 ;
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, PowerStatus);
		return result;
	}
	VARIANT ISSP_InitEx(LPCTSTR BridgeID, LPCTSTR ICtype, signed char PowerMode, LPCTSTR HexFile, VARIANT * Blocks, BSTR * ChipID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I1 VTS_BSTR VTS_PVARIANT VTS_PBSTR ;
		InvokeHelper(0xdd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, ICtype, PowerMode, HexFile, Blocks, ChipID);
		return result;
	}
	VARIANT ISSP_ProgramBlockEx(long * BlockID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0xde, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BlockID);
		return result;
	}
	VARIANT ISSP_AbortEx()
	{
		VARIANT result;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT ISSP_ProgramAllEx(LPCTSTR BridgeID, LPCTSTR ICtype, signed char PowerMode, LPCTSTR HexFile, VARIANT * Blocks, BSTR * ChipID)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I1 VTS_BSTR VTS_PVARIANT VTS_PBSTR ;
		InvokeHelper(0xe0, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, BridgeID, ICtype, PowerMode, HexFile, Blocks, ChipID);
		return result;
	}

	// IUSB2IICcom_Exe properties
public:

};
