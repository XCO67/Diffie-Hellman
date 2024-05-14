
// Diffie-HellmanDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CDiffieHellmanDlg dialog
class CDiffieHellmanDlg : public CDialogEx
{
/****************************** Project Generated Function (BEGIN) /******************************/
// Construction
public:
	CDiffieHellmanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DIFFIEHELLMAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
/****************************** Project Generated Function (END) /******************************/
public:

	afx_msg void OnBnClickedFindKeyBtn();			/****** Button Clicked Event Handler ******/
	CEdit m_firstPrimeNoEB;							/*********** Edit Box Variable ************/
	CEdit m_SecondPrimeNoEB;						/*********** Edit Box Variable ************/
	CEdit m_partyASecretKeyEB;						/*********** Edit Box Variable ************/
	CEdit m_partyBSecretKeyEB;						/************ Edit Box Variable ***********/
	void setFontsize(int fontSize, int BtnID);		/********** Function Declaration **********/
	void setKeyOnGUI(int controlID, int value);		/********** Function Declaration **********/
	void resetGUIData();							/********** Function Declaration **********/
};	
