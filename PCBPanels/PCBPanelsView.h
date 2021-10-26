
// PCBPanelsView.h: interfaccia della classe CPCBPanelsView
//

#pragma once


class CPCBPanelsView : public CScrollView
{
protected: // creare solo da serializzazione.
	CPCBPanelsView() noexcept;
	DECLARE_DYNCREATE(CPCBPanelsView)

// Attributi
public:
	CPCBPanelsDoc* GetDocument() const;

// Operazioni
public:

// Sostituzioni
public:
	virtual void OnDraw(CDC* pDC);  // sottoposto a override per creare questa visualizzazione
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementazione
public:
	virtual ~CPCBPanelsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funzioni generate per la mappa dei messaggi
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImportazioneImportasvgaccoppiati();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // versione di debug in PCBPanelsView.cpp
inline CPCBPanelsDoc* CPCBPanelsView::GetDocument() const
   { return reinterpret_cast<CPCBPanelsDoc*>(m_pDocument); }
#endif

