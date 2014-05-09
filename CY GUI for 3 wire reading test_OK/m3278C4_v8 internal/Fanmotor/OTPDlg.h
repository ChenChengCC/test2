#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COTPDlg dialog

class COTPDlg : public CDialog
{
	DECLARE_DYNAMIC(COTPDlg)

public:
	COTPDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COTPDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OTP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
	virtual void OnOK();
    virtual void OnCancel();
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pParent;
public:
	afx_msg void OnBnClickedRadioOtp1();
public:
	afx_msg void displaytorque();
public:
	afx_msg void OnBnClickedRadioOtpcal();
public:
	CProgressCtrl m_PROGRESS1;
public:
	CButton m_CHECK_PASS1;
public:
	CButton m_CHECK_FAIL1;
public:
	CButton m_CHECK_OTPCALDONE;
public:
	CButton m_CHECK_OTP1DONE;
public:
	afx_msg void OnBnClickedButtonBurnOtp1();
public:
	afx_msg void writeotp1reg();
	afx_msg void readotp1reg();
public:
	CEdit m_EDIT_CALREG0E;
public:
	CComboBox m_COMBO_CALREG0E;
public:
	afx_msg void OnCbnDropdownComboCalreg0e();
public:
	afx_msg void OnBnClickedButtonSaveFileOtpcal();
public:
	CEdit m_EDIT_CALREG11;
public:
	CComboBox m_COMBO_CALREG11;
public:
	afx_msg void OnCbnDropdownComboCalreg11();
public:
	CEdit m_EDIT_CALREG13;
public:
	CComboBox m_COMBO_CALREG13;
public:
	afx_msg void OnCbnDropdownComboCalreg13();
public:
	CEdit m_EDIT_CALREG15;
public:
	CComboBox m_COMBO_CALREG15;
public:
	afx_msg void OnCbnDropdownComboCalreg15();
public:
	CEdit m_EDIT_CALREG03;
public:
	CComboBox m_COMBO_CALREG03;
public:
	afx_msg void OnCbnDropdownComboCalreg03();
public:
	CEdit m_EDIT_CALREG18;
public:
	CComboBox m_COMBO_CALREG18;
public:
	afx_msg void OnCbnDropdownComboCalreg16();
public:
	CEdit m_EDIT_CALREG1B;
public:
	CComboBox m_COMBO_CALREG1B;
public:
	afx_msg void OnCbnDropdownComboCalreg1b();
public:
	CEdit m_EDIT_TORA;
public:
	CComboBox m_COMBO_TORA;
public:
	afx_msg void OnCbnDropdownComboTora();
public:
	CEdit m_EDIT_TORB;
public:
	CComboBox m_COMBO_TORB;
public:
	afx_msg void OnCbnDropdownComboTorb();
public:
	CEdit m_EDIT_TORC;
public:
	CComboBox m_COMBO_TORC;
public:
	afx_msg void OnCbnDropdownComboTorc();
public:
	CEdit m_EDIT_TORD;
public:
	CComboBox m_COMBO_TORD;
public:
	afx_msg void OnCbnDropdownComboTord();
public:
	CEdit m_EDIT_TORE;
public:
	CComboBox m_COMBO_TORE;
public:
	afx_msg void OnCbnDropdownComboTore();
public:
	CEdit m_EDIT_TORF;
public:
	CComboBox m_COMBO_TORF;
public:
	afx_msg void OnCbnDropdownComboTorf();
public:
	CEdit m_EDIT_TORG;
public:
	CComboBox m_COMBO_TORG;
public:
	afx_msg void OnCbnDropdownComboTorg();
public:
	CComboBox m_COMBO_TORH;
public:
	afx_msg void OnCbnDropdownComboTorh();
public:
	CEdit m_EDIT_TORH;
public:
	afx_msg void OnCbnSelchangeComboTore();
public:
	CComboBox m_COMBO_TORQUE_FILELOAD;
public:
	CComboBox m_COMBO_TORQUE_FILESAVE;
public:
	afx_msg void OnBnClickedButtonFileload();
public:
	afx_msg void OnBnClickedButtonFilesave();
public:
	afx_msg void OnCbnDropdownComboTorqueFileload();
public:
	afx_msg void OnCbnDropdownComboTorqueFilesave();
public:
	CString m_EDIT_FILETORA;
public:
	CString m_EDIT_FILETORB;
public:
	CString m_EDIT_FILETORC;
public:
	CString m_EDIT_FILETORD;
public:
	CString m_EDIT_FILETORE;
public:
	CString m_EDIT_FILETORF;
public:
	CString m_EDIT_FILETORG;
public:
	CString m_EDIT_FILETORH;
	CComboBox m_COMBO_MARGIN_RD_EN;
	afx_msg void OnCbnSelchangeComboMarginRdEn();
	afx_msg void OnDropdownComboCheckotp1file();
	CComboBox m_COMBO_CheckOTP1File;
	afx_msg void OnBnClickedButtonCheckotp1file();

	BOOL checkotp1file();
	CButton m_BUTTON_SAVE_FILE_OTPCAL;
};
