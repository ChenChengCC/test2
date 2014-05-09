#pragma once

// CAboutDlg dialog

class CAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
	virtual void OnOK();
    virtual void OnCancel();
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void PostNcDestroy();
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CWnd* m_pParent;
	CString m_EDIT_Firmware_Version;
	afx_msg void OnBnClickedButtonFirmwareVersion();
};

