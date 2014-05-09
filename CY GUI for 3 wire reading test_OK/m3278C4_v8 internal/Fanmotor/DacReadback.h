#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CDacReadback dialog

class CDacReadback : public CDialog
{
	DECLARE_DYNAMIC(CDacReadback)

public:
	CDacReadback(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDacReadback();

// Dialog Data
	enum { IDD = IDD_DIALOG_DacReadback };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	public:
	CWnd* m_pParent;

	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	CEdit m_EDIT_Loop_Count;
	afx_msg void OnBnClickedButtonDacreadback();
};
