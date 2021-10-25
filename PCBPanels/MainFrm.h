
// MainFrm.h: interfaccia della classe CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // creare solo da serializzazione.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributi
public:

// Operazioni
public:

// Sostituzioni
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementazione
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // membri incorporati della barra di controllo
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Funzioni generate per la mappa dei messaggi
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


