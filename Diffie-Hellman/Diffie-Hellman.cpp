
// Diffie-Hellman.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Diffie-Hellman.h"
#include "Diffie-HellmanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiffieHellmanApp

BEGIN_MESSAGE_MAP(CDiffieHellmanApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDiffieHellmanApp construction

CDiffieHellmanApp::CDiffieHellmanApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDiffieHellmanApp object

CDiffieHellmanApp theApp;


// CDiffieHellmanApp initialization

BOOL CDiffieHellmanApp::InitInstance()
{
	
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	
	CShellManager *pShellManager = new CShellManager;

	
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CDiffieHellmanDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		
	}
	else if (nResponse == IDCANCEL)
	{
	
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	
	return FALSE;
}

