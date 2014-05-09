#pragma once

class CBridgeInfo
{
public:
	CString BridgeID;
	CString Version;
	
	CBridgeInfo(BSTR BridgeID, BSTR Version);
	void GetBridgeInfo(CString& info);
public:
	~CBridgeInfo(void);
};
