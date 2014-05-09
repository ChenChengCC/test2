#pragma once
#include "afxwin.h"


// CFWTOR dialog

class CFWTOR : public CDialog
{
	DECLARE_DYNAMIC(CFWTOR)

public:
	CFWTOR(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFWTOR();

// Dialog Data
	enum { IDD = IDD_DIALOG_FW_ADTORQUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnNcDestroy();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
public:
	CWnd* m_pParent;
	CEdit m_EDIT_MinDac;
	CEdit m_EDIT_MaxDac;
	int m_RADIO_Mode;
	CButton m_CHECK_StopFan;
	CEdit m_EDIT_SettleT;
	CButton m_CHECK_FWAdTor;
	CEdit m_EDIT_TorCoarseA;
	CEdit m_EDIT_TorCoarseB;
	CEdit m_EDIT_TorCoarseC;
	CEdit m_EDIT_TorCoarseD;
	CEdit m_EDIT_TorCoarseE;
	CEdit m_EDIT_TorCoarseF;
	CEdit m_EDIT_TorCoarseG;
	CEdit m_EDIT_TorCoarseH;
	CEdit m_EDIT_TorFineA;
	CEdit m_EDIT_TorFineB;
	CEdit m_EDIT_TorFineC;
	CEdit m_EDIT_TorFineD;
	CEdit m_EDIT_TorFineE;
	CEdit m_EDIT_TorFineF;
	CEdit m_EDIT_TorFineG;
	CEdit m_EDIT_TorFineH;
	afx_msg void OnBnClickedButtonStart();
	BOOL GetAdTorInput();
	void PWMRegMeasure();
	void UseFWAdTorque(int );
	afx_msg void OnBnClickedRadioInc();
	afx_msg void OnBnClickedRadioDec();
	CComboBox m_COMBO_TorCoarseA;
	CComboBox m_COMBO__TorCoarseB;
	CComboBox m_COMBO_TorCoarseB;
	CComboBox m_COMBO_TorCoarseC;
	CComboBox m_COMBO_TorCoarseD;
	CComboBox m_COMBO_TorCoarseE;
	CComboBox m_COMBO_TorCoarseF;
	CComboBox m_COMBO_TorCoarseG;
	CComboBox m_COMBO_TorCoarseH;
	CComboBox m_COMBO_TorFineA;
	CComboBox m_COMBO_TorFineB;
	CComboBox m_COMBO_TorFineC;
	CComboBox m_COMBO_TorFineD;
	CComboBox m_COMBO_TorFineE;
	CComboBox m_COMBO_TorFineF;
	CComboBox m_COMBO_TorFineG;
	CComboBox m_COMBO_TorFineH;
};
