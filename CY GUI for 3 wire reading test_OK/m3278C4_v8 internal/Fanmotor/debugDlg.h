#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CdebugDlg dialog

class CdebugDlg : public CDialog
{
	DECLARE_DYNAMIC(CdebugDlg)

public:
	CdebugDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CdebugDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DEBUG };

protected:
	virtual void OnOK();
    virtual void OnCancel();
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pParent;
public:
//	okUSBFRONTPANEL_HANDLE xem;
//	okPLL22150_HANDLE pll;
	void InitUSB ( void );
	void InitFPGA ( void );
	void InitPLL ( void );

	int string2int (CString, int);


public:
	CEdit m_EDIT_WREG_01;
public:
	afx_msg void OnBnClickedButtonWreg01();
public:
	CString m_EDIT_RREG_01;
public:
	afx_msg void OnBnClickedButtonRreg01();
public:
	CComboBox m_COMBO_RREG_01;
public:
	afx_msg void OnCbnDropdownComboRreg01();
public:
	CEdit m_EDIT_WREG_02;
public:
	afx_msg void OnBnClickedButtonWreg02();
public:
	CString m_EDIT_RREG_02;
public:
	afx_msg void OnBnClickedButtonRreg02();
public:
	CComboBox m_COMBO_RREG_02;
public:
	afx_msg void OnCbnDropdownComboRreg02();
public:
	CEdit m_EDIT_WREG_03;
public:
	afx_msg void OnBnClickedButtonWreg03();
public:
	CString m_EDIT_RREG_03;
public:
	afx_msg void OnBnClickedButtonRreg03();
public:
	CComboBox m_COMBO_RREG_03;
public:
	afx_msg void OnCbnDropdownComboRreg03();
	afx_msg void readsparereg();
public:
	CEdit m_EDIT_WREG_04;
public:
	afx_msg void OnBnClickedButtonWreg04();
public:
	CString m_EDIT_RREG_04;
public:
	afx_msg void OnBnClickedButtonRreg04();
public:
	CComboBox m_COMBO_RREG_04;
public:
	CEdit m_EDIT_WREG_05;
public:
	afx_msg void OnBnClickedButtonWreg05();
public:
	afx_msg void OnCbnDropdownComboRreg04();
public:
	CString m_EDIT_RREG_05;
public:
	afx_msg void OnBnClickedButtonRreg05();
public:
	afx_msg void OnCbnDropdownComboRreg05();
public:
	CComboBox m_COMBO_RREG_05;
public:
	CEdit m_EDIT_WREG_06;
public:
	afx_msg void OnBnClickedButtonWreg06();
public:
	CString m_EDIT_RREG_06;
public:
	afx_msg void OnBnClickedButtonRreg06();
public:
	CComboBox m_COMBO_RREG_06;
public:
	afx_msg void OnCbnDropdownComboRreg06();
public:
	CEdit m_EDIT_WREG_07;
public:
	afx_msg void OnBnClickedButtonWreg07();
public:
	CString m_EDIT_RREG_07;
public:
	afx_msg void OnBnClickedButtonRreg07();
public:
	CComboBox m_COMBO_RREG_07;
public:
	afx_msg void OnCbnDropdownComboRreg07();
public:
	CEdit m_EDIT_WREG_08;
public:
	afx_msg void OnBnClickedButtonWreg08();
public:
	CString m_EDIT_RREG_08;
public:
	afx_msg void OnBnClickedButtonRreg08();
public:
	CComboBox m_COMBO_RREG_08;
public:
	afx_msg void OnCbnDropdownComboRreg08();
public:
	CEdit m_EDIT_WREG_09;
public:
	afx_msg void OnBnClickedButtonWreg09();
public:
	CString m_EDIT_RREG_09;
public:
	afx_msg void OnBnClickedButtonRreg09();
public:
	CComboBox m_COMBO_RREG_09;
public:
	afx_msg void OnCbnDropdownComboRreg09();
public:
	CEdit m_EDIT_WREG_0a;
public:
	afx_msg void OnBnClickedButtonWreg0a();
public:
	CString m_EDIT_RREG_0a;
public:
	afx_msg void OnBnClickedButtonRreg0a();
public:
	CComboBox m_COMBO_RREG_0a;
public:
	afx_msg void OnCbnDropdownComboRreg0a();
public:
	CEdit m_EDIT_WREG_0b;
public:
	afx_msg void OnBnClickedButtonWreg0b();
public:
	CString m_EDIT_RREG_0b;
public:
	afx_msg void OnBnClickedButtonRreg0b();
public:
	CComboBox m_COMBO_RREG_0b;
public:
	afx_msg void OnCbnSelchangeComboRreg0b();
public:
	afx_msg void OnCbnDropdownComboRreg0b();
public:
	CString m_EDIT_RREG_0c;
public:
	afx_msg void OnBnClickedButtonRreg0c();
public:
	CComboBox m_COMBO_RREG_0c;
public:
	afx_msg void OnCbnDropdownComboRreg0c();
public:
	CEdit m_EDIT_WREG_0d;
public:
	afx_msg void OnBnClickedButtonWreg0d();
public:
	CString m_EDIT_RREG_0d;
public:
	CComboBox m_COMBO_RREG_0d;
public:
	CString m_EDIT_RREG_0e;
public:
	afx_msg void OnBnClickedButtonRreg0e();
public:
	CComboBox m_COMBO_RREG_0e;
public:
	afx_msg void OnCbnDropdownComboRreg0e();
public:
	afx_msg void OnBnClickedButtonRreg0d();
public:
	afx_msg void OnCbnDropdownComboRreg0d();
public:
	CString m_EDIT_RREG_0f;
public:
	afx_msg void OnBnClickedButtonRreg0f();
public:
	CComboBox m_COMBO_RREG_0f;
public:
	afx_msg void OnCbnDropdownComboRreg0f();
public:
	CEdit m_EDIT_WREG_10;
public:
	afx_msg void OnBnClickedButtonWreg10();
public:
	CString m_EDIT_RREG_10;
public:
	afx_msg void OnBnClickedButtonRreg10();
public:
	CComboBox m_COMBO_RREG_10;
public:
	afx_msg void OnCbnDropdownComboRreg10();
public:
	CEdit m_EDIT_WREG_11;
public:
	afx_msg void OnBnClickedButtonWreg11();
public:
	CString m_EDIT_RREG_11;
public:
	afx_msg void OnBnClickedButtonRreg11();
public:
	CComboBox m_COMBO_RREG_11;
public:
	afx_msg void OnCbnDropdownComboRreg11();
public:
	CEdit m_EDIT_WREG_12;
public:
	afx_msg void OnBnClickedButtonWreg12();
public:
	CString m_EDIT_RREG_12;
public:
	afx_msg void OnBnClickedButtonRreg12();
public:
	CComboBox m_COMBO_RREG_12;
public:
	afx_msg void OnCbnDropdownComboRreg12();
public:
	CString m_EDIT_RREG_13;
public:
	afx_msg void OnBnClickedButtonRreg13();
public:
	CComboBox m_COMBO_RREG_13;
public:
	afx_msg void OnCbnDropdownComboRreg13();
public:
	CString m_EDIT_RREG_14;
public:
	afx_msg void OnBnClickedButtonRreg14();
public:
	CComboBox m_COMBO_RREG_14;
public:
	afx_msg void OnCbnDropdownComboRreg14();
public:
	afx_msg void OnBnClickedButtonStart();
public:
	afx_msg void OnBnClickedButtonWriteall();
public:
	afx_msg void OnBnClickedButtonReadall();
public:
	CComboBox m_COMBO_LOAD;
public:
	afx_msg void OnCbnDropdownComboLoad();
public:
	afx_msg void OnBnClickedButtonLoad();
public:
	CComboBox m_COMBO_SAVE;
public:
	afx_msg void OnCbnDropdownComboSave();
public:
	afx_msg void OnBnClickedButtonSave();
public:
	CEdit m_EDIT_WREG_0c;
public:
	afx_msg void OnBnClickedButtonWreg0c();
public:
	CEdit m_EDIT_WREG_0e;
public:
	afx_msg void OnBnClickedButtonWreg0e();
public:
	CEdit m_EDIT_WREG_0f;
public:
	afx_msg void OnBnClickedButtonWreg0f();
public:
	CEdit m_EDIT_WREG_13;
public:
	afx_msg void OnBnClickedButtonWreg13();
public:
	CEdit m_EDIT_WREG_14;
public:
	afx_msg void OnBnClickedButtonWreg14();
public:
	CEdit m_EDIT_WREG_15;
public:
	afx_msg void OnBnClickedButtonWreg15();
public:
	CString m_EDIT_RREG_15;
public:
	afx_msg void OnBnClickedButtonRreg15();
public:
	CComboBox m_COMBO_RREG_15;
public:
	afx_msg void OnCbnDropdownComboRreg15();

public:
	CString m_EDIT_RREG_16;
public:
	afx_msg void OnBnClickedButtonRreg16();
public:
	CComboBox m_COMBO_RREG_16;
public:
	afx_msg void OnCbnDropdownComboRreg16();
public:
	CString m_EDIT_RREG_17;
public:
	afx_msg void OnBnClickedButtonRreg17();
public:
	CComboBox m_COMBO_RREG_17;
public:
	afx_msg void OnCbnDropdownComboRreg17();
public:
	CEdit m_EDIT_WREG_18;
public:
	afx_msg void OnBnClickedButtonWreg18();
public:
	CString m_EDIT_RREG_18;
public:
	afx_msg void OnBnClickedButtonRreg18();
public:
	CComboBox m_COMBO_RREG_18;
public:
	afx_msg void OnCbnDropdownComboRreg18();
public:
	CString m_EDIT_RREG_19;
public:
	afx_msg void OnBnClickedButtonRreg19();
public:
	CComboBox m_COMBO_RREG_19;
public:
	afx_msg void OnCbnDropdownComboRreg19();
public:
	CString m_EDIT_RREG_1a;
public:
	afx_msg void OnBnClickedButtonRreg1a();
public:
	CComboBox m_COMBO_RREG_1a;
public:
	afx_msg void OnCbnDropdownComboRreg1a();
public:
	CEdit m_WREG_1B;
public:
	CString m_EDIT_RREG_1b;
public:
	CComboBox m_COMBO_RREG_1b;
public:
	afx_msg void OnBnClickedButtonWreg1b();
public:
	afx_msg void OnBnClickedButtonRreg1b();
public:
	afx_msg void OnCbnDropdownComboRreg1b();
public:
	CEdit m_EDIT_WREG_1C;
public:
	CString m_EDIT_RREG_1c;
public:
	CEdit m_EDIT_WREG_1D;
public:
	CString m_EDIT_RREG_1d;
public:
	afx_msg void OnBnClickedButtonWreg1c();
public:
	afx_msg void OnBnClickedButtonRreg1c();
public:
	afx_msg void OnBnClickedButtonWreg1d();
public:
	afx_msg void OnBnClickedButtonRreg1d();
public:
	afx_msg void OnCbnDropdownComboRreg1d();
public:
	CComboBox m_COMBO_RREG_1d;
public:
	CComboBox m_COMBO_RREG_1c;
public:
	afx_msg void OnCbnDropdownComboRreg1c();
public:
	CEdit m_EDIT_WREG_1E;
public:
	afx_msg void OnBnClickedButtonWreg1e();
public:
	CString m_EDIT_RREG_1e;
public:
	afx_msg void OnBnClickedButtonRreg1e();
public:
	CComboBox m_COMBO_RREG_1e;
public:
	afx_msg void OnCbnDropdownComboRreg1e();
public:
	CEdit m_EDIT_WREG_1F;
public:
	afx_msg void OnBnClickedButtonWreg1f();
public:
	CString m_EDIT_RREG_1f;
public:
	afx_msg void OnBnClickedButtonRreg1f();
public:
	CComboBox m_COMBO_RREG_1f;
public:
	afx_msg void OnCbnDropdownComboRreg1f();
public:
	CEdit m_EDIT_WREG_20;
public:
	afx_msg void OnBnClickedButtonWreg20();
public:
	CString m_EDIT_RREG_20;
public:
	afx_msg void OnBnClickedButtonRreg20();
public:
	CComboBox m_COMBO_RREG_20;
public:
	afx_msg void OnCbnDropdownComboRreg20();

public:
	CEdit m_EDIT_WREG_2A;
public:
//	CEdit m_EDIT_WREG_2B;
public:
	CEdit m_EDIT_WREG_3D;
public:
	afx_msg void OnBnClickedButtonWreg2a();
public:
	afx_msg void OnBnClickedButtonWreg3d();
public:
//	CEdit m_EDIT_WREG_21;
public:
//	afx_msg void OnBnClickedButtonWreg21();
public:
	CString m_EDIT_RREG_21;
public:
	CComboBox m_COMBO_RREG_21;
public:
	afx_msg void OnBnClickedButtonRreg21();
public:
	afx_msg void OnCbnDropdownComboRreg21();
public:
	CEdit m_EDIT_WREG_22;
public:
	CString m_EDIT_RREG_22;
public:
	CComboBox m_COMBO_RREG_22;
public:
	CEdit m_EDIT_WREG_23;

public:
	CString m_EDIT_RREG_23;
public:
	CComboBox m_COMBO_RREG_23;
public:
	afx_msg void OnBnClickedButtonWreg22();
public:
	afx_msg void OnBnClickedButtonRreg22();
public:
	afx_msg void OnCbnDropdownComboRreg22();
public:
	afx_msg void OnBnClickedButtonWreg23();
public:
	afx_msg void OnBnClickedButtonRreg23();
public:
	afx_msg void OnCbnDropdownComboRreg23();
public:
	CEdit m_EDIT_WREG_24;
public:
	afx_msg void OnBnClickedButtonWreg24();
public:
	CString m_EDIT_RREG_24;
public:
	afx_msg void OnBnClickedButtonRreg24();
public:
	CComboBox m_COMBO_RREG_24;
public:
	CEdit m_EDIT_WREG_25;
public:
	CButton m_BUTTON_WREG_25;
public:
	afx_msg void OnBnClickedButtonWreg25();
public:
	afx_msg void OnBnClickedButtonRreg25();
public:
	CComboBox m_COMBO_RREG_25;
public:
	afx_msg void OnCbnDropdownComboRreg25();
public:
	afx_msg void OnCbnDropdownComboRreg24();
public:
	CString m_EDIT_RREG_25;
public:
	CEdit m_EDIT_WREG_26;
public:
	afx_msg void OnBnClickedButtonWreg26();
public:
	CString m_EDIT_RREG_26;
public:
	afx_msg void OnBnClickedButtonRreg26();
public:
	CComboBox m_COMBO_RREG_26;
public:
	CEdit m_EDIT_WREG_27;
public:
	afx_msg void OnBnClickedButtonWreg27();
public:
	CString m_EDIT_RREG_27;
public:
	afx_msg void OnBnClickedButtonRreg27();
public:
	CComboBox m_COMBO_RREG_27;
public:
	CEdit m_EDIT_WREG_28;
public:
	afx_msg void OnBnClickedButtonWreg28();
public:
	CString m_EDIT_RREG_28;
public:
	afx_msg void OnBnClickedButtonRreg28();
public:
	afx_msg void OnCbnDropdownComboRreg26();
public:
	afx_msg void OnCbnDropdownComboRreg27();
public:
	CComboBox m_COMBO_RREG_28;
public:
	afx_msg void OnCbnDropdownComboRreg28();
public:
	CEdit m_EDIT_WREG_29;
public:
	afx_msg void OnBnClickedButtonWreg29();
public:
	CString m_EDIT_RREG_29;
public:
	afx_msg void OnBnClickedButtonRreg29();
public:
	CComboBox m_COMBO_RREG_29;
public:
	afx_msg void OnCbnDropdownComboRreg29();
//	afx_msg void OnCbnSelchangeComboLoad();
	void RemoveAdTor();
	afx_msg void OnCbnSetfocusComboLoad();
	afx_msg void OnCbnSetfocusComboSave();
	afx_msg void OnCbnEditchangeComboLoad();
	afx_msg void OnCbnSelchangeComboLoad();
	afx_msg void OnCbnEditupdateComboLoad();
	afx_msg void OnCbnEditchangeComboSave();

	void SetDropDownHeight(CComboBox* , int );
	CEdit m_EDIT_WREG_16;
	CEdit m_EDIT_WREG_17;
	CEdit m_EDIT_WREG_19;
	CEdit m_EDIT_WREG_1A;
	CEdit m_EDIT_WREG_21;
	afx_msg void OnBnClickedButtonWreg16();
	afx_msg void OnBnClickedButtonWreg17();
	afx_msg void OnBnClickedButtonWreg19();
	afx_msg void OnBnClickedButtonWreg1a();
	afx_msg void OnBnClickedButtonWreg21();
};
