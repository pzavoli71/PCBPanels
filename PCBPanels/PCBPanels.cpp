
// PCBPanels.cpp: definisce i comportamenti delle classi per l'applicazione.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PCBPanels.h"
#include "MainFrm.h"

#include "PCBPanelsDoc.h"
#include "PCBPanelsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPCBPanelsApp

BEGIN_MESSAGE_MAP(CPCBPanelsApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPCBPanelsApp::OnAppAbout)
	// Comandi di documenti basati su file standard
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Comando di stampa standard
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Costruzione di CPCBPanelsApp

CPCBPanelsApp::CPCBPanelsApp() noexcept
{
	// supporto Gestione riavvio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Se l'applicazione è compilata mediante il supporto CLR (/clr):
	//     1) Questa ipostazione è necessaria per il corretto funzionamento del supporto di Gestione riavvio.
	//     2) Nel progetto è necessario aggiungere un riferimento a System.Windows.Forms per eseguire la compilazione.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: sostituire la stringa dell'ID applicazione seguente con una stringa di ID univoca; il formato consigliato
	// per la stringa è NomeSocietà.NomeProdotto.Sottoprodotto.Versione
	SetAppID(_T("PCBPanels.AppID.NoVersion"));

	// TODO: aggiungere qui il codice di costruzione.
	// Inserire l'inizializzazione significativa in InitInstance.
}

// Unico oggetto CPCBPanelsApp

CPCBPanelsApp theApp;


// Inizializzazione di CPCBPanelsApp

BOOL CPCBPanelsApp::InitInstance()
{
	// InitCommonControlsEx() è necessario in Windows XP se nel manifesto
	// di un'applicazione è specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per abilitare
	// gli stili visuali.  In caso contrario, non sarà possibile creare finestre.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Effettuare questa impostazione in modo da includere tutte le classi di controlli comuni da utilizzare
	// nell'applicazione.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Inizializzare le librerie OLE.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Per usare il controllo RichEdit, è richiesto AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Inizializzazione standard
	// Se non si utilizzano queste funzionalità e si desidera ridurre la dimensione
	// dell'eseguibile finale, è necessario rimuovere dal seguente codice
	// le specifiche routine di inizializzazione che non sono necessarie.
	// Modificare la chiave del Registro di sistema in cui sono memorizzate le impostazioni
	// TODO: è necessario modificare questa stringa in modo appropriato,
	// inserendo ad esempio il nome della società o dell'organizzazione.
	SetRegistryKey(_T("Applicazioni locali generate tramite la Creazione guidata applicazioni"));
	LoadStdProfileSettings(4);  // Caricare le opzioni del file INI standard (inclusa MRU).


	// Registrare i modelli di documenti dell'applicazione.  I modelli di documenti
	//  funzionano da connessione tra documenti, finestre cornice e viste.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPCBPanelsDoc),
		RUNTIME_CLASS(CMainFrame),       // finestra cornice SDI principale
		RUNTIME_CLASS(CPCBPanelsView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Analizzare la riga di comando per i comandi shell standard, DDE, apri file
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Abilitare apertura esecuzione DDE.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Invia i comandi specificati nella riga di comando.  Restituisce FALSE se
	// l'applicazione è stata avviata con l'opzione /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// L'unica e sola finestra è stata inizializzata, quindi è possibile visualizzarla e aggiornarla.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// richiamare DragAcceptFiles solo se è presente un suffisso.
	//  In un'applicazione SDI questo deve verificarsi dopo ProcessShellCommand.
	// Abilitare il trascinamento della selezione.
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

int CPCBPanelsApp::ExitInstance()
{
	//TODO: gestire le altre risorse eventualmente aggiunte.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Gestori di messaggi di CPCBPanelsApp


// finestra di dialogo CAboutDlg utilizzata per visualizzare le informazioni sull'applicazione.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dati della finestra di dialogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // supporto DDX/DDV

// Implementazione
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// comando dell'applicazione per eseguire la finestra di dialogo
void CPCBPanelsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Gestori di messaggi di CPCBPanelsApp



