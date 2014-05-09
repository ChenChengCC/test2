#include "StdAfx.h"
#include "BridgeInfo.h"

CBridgeInfo::CBridgeInfo(BSTR BridgeID, BSTR Version)
{
	this->BridgeID = BridgeID;
	this->Version = Version;
}

void CBridgeInfo::GetBridgeInfo(CString& info)
{
  if (Version==L"") info = BridgeID;
  else info=BridgeID+L"  Version: "+Version;
}

CBridgeInfo::~CBridgeInfo(void)
{
}
