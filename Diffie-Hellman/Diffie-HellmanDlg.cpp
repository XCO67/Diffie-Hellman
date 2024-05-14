
// Diffie-HellmanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diffie-Hellman.h"
#include "Diffie-HellmanDlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDiffieHellmanDlg dialog



CDiffieHellmanDlg::CDiffieHellmanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiffieHellmanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiffieHellmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_firstPrimeNoEB);
	DDX_Control(pDX, IDC_EDIT2, m_SecondPrimeNoEB);
	DDX_Control(pDX, IDC_EDIT3, m_partyASecretKeyEB);
	DDX_Control(pDX, IDC_EDIT4, m_partyBSecretKeyEB);
}

BEGIN_MESSAGE_MAP(CDiffieHellmanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FIND_KEY_BTN, &CDiffieHellmanDlg::OnBnClickedFindKeyBtn)
END_MESSAGE_MAP()


// CDiffieHellmanDlg message handlers

BOOL CDiffieHellmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	
	SetIcon(m_hIcon, TRUE);			// Set 
	SetIcon(m_hIcon, FALSE);		

	// TODO: Add extra initialization here

/************************* Function Calling ************************ BEGIN*/
	setFontsize(200, IDC_MAIN_LBL);
	setFontsize(110, IDC_SECOND_PRIME_NO_LBL);
	setFontsize(110, IDC_FIRST_PRIME_NO_LBL);
	setFontsize(110, IDC_PARTY_A_SECRET_KEY_LABEL);
	setFontsize(110, IDC_PARTY_B_SECRET_KEY_LABEL);
	setFontsize(170, IDC_FIND_KEY_BTN);
	setFontsize(110, IDC_PARTY_A_LBL);
	setFontsize(110, IDC_PARTY_B_LBL);
	setFontsize(80, IDC_PARTY_A_SECRET_KEY_LBL);
	setFontsize(80, IDC_PARTY_A_PUBLIC_KEY_LBL);
	setFontsize(80, IDC_PARTY_B_SECRET_KEY_LBL);
	setFontsize(80, IDC_PARTY_B_PUBLIC_KEY_LBL);
/************************* Function Calling ************************ END*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiffieHellmanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CDiffieHellmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDiffieHellmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




int convertCStringToInt(CString val) {
	int no = 0;
	no = _wtoi(val);
	return no;
}



long long int power(long long int a, long long int b, long long int P) {

	//If the exponent b is 0, it returns 1 because any number raised to the power of 0 is 1.
	if (b == 0) return 1;
	// If the exponent b is 1, it returns a modulo P.
	if (b == 1) return a % P;
	// For exponents greater than 1, it recursively calculates temp = power(a, b / 2, P). 
	long long int temp = power(a, b / 2, P);
	// It squares temp to get result = (temp * temp) % P.
	long long int result = (temp * temp) % P;
	// If b is odd (i.e., b % 2 == 1), it multiplies result by a and takes the result modulo P. This handles the case where the exponent is odd.
	if (b % 2 == 1) result = (result * a) % P;
	// Finally, it returns the computed result
	return result;
}




void CDiffieHellmanDlg::setKeyOnGUI(int controlID, int value){

	CString strValue;

	if (controlID == IDC_PARTY_A_PUBLIC_KEY_LBL){
		strValue.Format(_T("Public Key of Party A : %d"), value);
		CWnd* publicKeyParty_A_Label = GetDlgItem(IDC_PARTY_A_PUBLIC_KEY_LBL);
		publicKeyParty_A_Label->SetWindowText(strValue);
	}
	else if (controlID == IDC_PARTY_B_PUBLIC_KEY_LBL){
		strValue.Format(_T("Public Key of Party B : %d"), value);
		CWnd* publicKeyParty_B_Label = GetDlgItem(IDC_PARTY_B_PUBLIC_KEY_LBL);
		publicKeyParty_B_Label->SetWindowText(strValue);
	}
	else if (controlID == IDC_PARTY_A_SECRET_KEY_LBL){
		strValue.Format(_T("Secret Key of Party A : %d"), value);
		CWnd* secretKeyParty_A_Label = GetDlgItem(IDC_PARTY_A_SECRET_KEY_LBL);
		secretKeyParty_A_Label->SetWindowText(strValue);
	}
	else if (controlID == IDC_PARTY_B_SECRET_KEY_LBL){
		strValue.Format(_T("Secret Key of Party B : %d"), value);
		CWnd* secretKeyParty_B_Label = GetDlgItem(IDC_PARTY_B_SECRET_KEY_LBL);
		secretKeyParty_B_Label->SetWindowText(strValue);
	}
}





void CDiffieHellmanDlg::OnBnClickedFindKeyBtn()
{


	resetGUIData();
	
	CString firstPrimeNoStr =_T(""),
		secondPrimeNoStr = _T(""),
		partyASecretKeyStr = _T(""),
		partyBSecretKeyStr = _T("");

	m_firstPrimeNoEB.GetWindowText(firstPrimeNoStr);
	m_SecondPrimeNoEB.GetWindowText(secondPrimeNoStr);
	m_partyASecretKeyEB.GetWindowText(partyASecretKeyStr);
	m_partyBSecretKeyEB.GetWindowText(partyBSecretKeyStr);

	if (firstPrimeNoStr == "" || secondPrimeNoStr == "" || partyASecretKeyStr == "" || partyBSecretKeyStr == ""){
		return;
	}


	int firstPrimeNo = convertCStringToInt(firstPrimeNoStr);
	int secondPrimeNo = convertCStringToInt(secondPrimeNoStr);
	int partyASecretKey = convertCStringToInt(partyASecretKeyStr);
	int partyBSecretKey = convertCStringToInt(partyBSecretKeyStr);

	int publicKeyPartyA = power(secondPrimeNo, partyASecretKey, firstPrimeNo);
	int publicKeyPartyB = power(secondPrimeNo, partyBSecretKey, firstPrimeNo);
	int keyPartyA = power(publicKeyPartyB, partyASecretKey, firstPrimeNo);
	int keyPartyB = power(publicKeyPartyA, partyBSecretKey, firstPrimeNo);

	
		/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_A_PUBLIC_KEY_LBL, publicKeyPartyA); 
		/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_B_PUBLIC_KEY_LBL, publicKeyPartyB);
		/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_A_SECRET_KEY_LBL, keyPartyA);
		/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_B_SECRET_KEY_LBL, keyPartyB);


}




void CDiffieHellmanDlg::setFontsize(int fontSize, int BtnID){

	CString str(_T("Arial Bold"));
	CStatic *m_Label;
	CStatic *m_mode;

	CFont *m_font = new CFont();
	m_font->CreatePointFont(fontSize, str);
	m_Label = (CStatic*)GetDlgItem(BtnID);
	m_Label->SetFont(m_font);

}




void CDiffieHellmanDlg::resetGUIData(){
	/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_A_PUBLIC_KEY_LBL, 0);
	/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_B_PUBLIC_KEY_LBL, 0);
	/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_A_SECRET_KEY_LBL, 0);
	/***** Function Calling (setKeyOnGUI) *****/
	setKeyOnGUI(IDC_PARTY_B_SECRET_KEY_LBL, 0);
}
