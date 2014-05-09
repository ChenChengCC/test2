// USB2IICevent_Sink.cpp : implementation file
//

#include "stdafx.h"
#include "Fanmotor.h"
#include "USB2IICevent_Sink.h"


// CUSB2IICevent_Sink

IMPLEMENT_DYNAMIC(CUSB2IICevent_Sink, CCmdTarget)


CUSB2IICevent_Sink::CUSB2IICevent_Sink()
: dlgWnd(NULL)
{
	EnableAutomation();
}

CUSB2IICevent_Sink::~CUSB2IICevent_Sink()
{
}


void CUSB2IICevent_Sink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CUSB2IICevent_Sink, CCmdTarget)
END_MESSAGE_MAP()

void CUSB2IICevent_Sink::OnBridgeConnect(BSTR BridgeID, BSTR str)
{
	//Delegate Event to Dialog Window
	dlgWnd->AddBridgeEvent(BridgeID);
}

void CUSB2IICevent_Sink::OnBridgeDisconnect(BSTR BridgeID)
{
	// Delegate Event to Dialog Window
	dlgWnd->RemoveBridgeEvent(BridgeID);
}

BEGIN_DISPATCH_MAP(CUSB2IICevent_Sink, CCmdTarget)
	DISP_FUNCTION_ID(CUSB2IICevent_Sink,"BridgeConnected",1,OnBridgeConnect,VT_EMPTY,VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CUSB2IICevent_Sink,"BridgeDisconnected",2,OnBridgeDisconnect,VT_EMPTY,VTS_BSTR)
END_DISPATCH_MAP()

// Note: we add support for IID_IUSB2IICevent_Sink to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {4B2ED98F-C8D3-472D-994A-13C8EB8B2475}
static const IID IID_IUSB2IICevent_Sink =
{ 0x80efe271, 0xeb62, 0x4e20, { 0x96, 0x9f, 0x23, 0x20, 0x8b, 0xe1, 0x9e, 0x10} };

BEGIN_INTERFACE_MAP(CUSB2IICevent_Sink, CCmdTarget)
	INTERFACE_PART(CUSB2IICevent_Sink, IID_IUSB2IICevent_Sink, Dispatch)
END_INTERFACE_MAP()


// CUSB2IICevent_Sink message handlers
