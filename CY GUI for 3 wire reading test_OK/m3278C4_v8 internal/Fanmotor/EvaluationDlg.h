#pragma once

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CEvaluationDlg dialog

class CEvaluationDlg : public CDialog
{
	DECLARE_DYNAMIC(CEvaluationDlg)

public:
	CEvaluationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEvaluationDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_EVALUATION };

protected:
	virtual void OnOK();
    virtual void OnCancel();
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnNcDestroy();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pParent;
public:
	afx_msg void loadfile();
public:
	afx_msg void OnBnClickedLoad();
public:
	CEdit m_EDIT_DACW;
public:
	CString m_EDIT_SHOWDAC;
public:
	afx_msg void OnBnClickedButtonDacw();
public:
	afx_msg void OnBnClickedButtonDacwup();
public:
	afx_msg void OnBnClickedButtonDacwdown();
public:
	afx_msg void OnBnClickedButtonDacwupsmall();
public:
	afx_msg void OnBnClickedButtonDacwdownsmall();
public:
	CEdit m_EDIT_MAX_DAC;
public:
	CEdit m_EDIT_MIN_DAC;
public:
	CButton m_CHECK_VARDAC_EN;
public:
	CComboBox m_COMBO_VARDAC_CNT;
public:
	afx_msg void OnBnClickedCheckVardacEn();
public:
	afx_msg void OnCbnSelchangeComboVardacCnt();
public:
	afx_msg void OnBnClickedCheckAdtorEn();
public:
	CButton m_CHECK_ADTOR_EN;
public:
	afx_msg void OnBnClickedButtonStart();
public:
	afx_msg void OnBnClickedButtonStop();
public:
	afx_msg void OnBnClickedButtonAccelerate();
public:
	afx_msg void OnBnClickedButtonDecelerate2();
public:
	CString m_EDIT_RPM_COUNT;
public:
	afx_msg void OnBnClickedRpmCount();
public:
	CAnimateCtrl m_FAN;
public:
	afx_msg void OnBnClickedButtonDacr();
public:
	afx_msg void OnBnClickedReadEval();
};
