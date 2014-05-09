#pragma once
#include "CUSB2IICcom_Exe.h"

class CBridgeFunctionsUsage
{
private:
	CUSB2IICcom_Exe* Bridge;
public:
	CBridgeFunctionsUsage(CUSB2IICcom_Exe* Bridge);
public:
	~CBridgeFunctionsUsage(void);

	  //--------------------------------------------------------------
      // Initialization Functions
      //--------------------------------------------------------------
      void InitUSB();
      void InitUSB2IIC();
      void UnInitUSB();
      //--------------------------------------------------------------
      // Configuration and Status Functions
      //--------------------------------------------------------------
      void GetBridgeList();
      void GetBridgeStatus();
      void GetStatusMsg();
      void GetBridgeVersion();
      void GetPowerSpeed();
      void SetPower();
      void SetSpeed();
      void ResetBridge();
      void IsPowerDetected();
      void SetTimeoutPeriod();
      //--------------------------------------------------------------
      // I2C functions
      //--------------------------------------------------------------
      void GetDeviceList();
      void SendIICdata();
      void ReadIICdata();
      void ReadIICdataReg();
      void AbortTransfer();
};
