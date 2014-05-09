
#pragma once

#include "debugDlg.h"
#include "detailDlg.h"
#include "EvaluationDlg.h"
#include "FanmotorDlg.h"
#include "TestDlg.h"

// CUSB2IICevent_Sink command target

class CUSB2IICevent_Sink : public CCmdTarget
{
	DECLARE_DYNAMIC(CUSB2IICevent_Sink)

private:
  void OnBridgeConnect(BSTR BridgeID,
        BSTR str);
  void OnBridgeDisconnect(BSTR BridgeID);

public:
	CUSB2IICevent_Sink();
	virtual ~CUSB2IICevent_Sink();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	// // main Dialog Window reference
	CdebugDlg* dlgWnddebug;
	CdetailDlg* dlgWnddetail;
	CFanmotorDlg* dlgWnd;
	CEvaluationDlg* dlgWndeval;
	CTestDlg* dlgWndtest;
};

extern const IID IID_IUSB2IICevent_Sink;



