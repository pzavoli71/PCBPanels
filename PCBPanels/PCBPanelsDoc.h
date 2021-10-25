
// PCBPanelsDoc.h: interfaccia della classe CPCBPanelsDoc
//


#pragma once


class CPCBPanelsDoc : public CDocument
{
protected: // creare solo da serializzazione.
	CPCBPanelsDoc() noexcept;
	DECLARE_DYNCREATE(CPCBPanelsDoc)

// Attributi
public:

// Operazioni
public:

// Sostituzioni
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementazione
public:
	virtual ~CPCBPanelsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funzioni generate per la mappa dei messaggi
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Funzione helper che imposta il contenuto della ricerca per il gestore di ricerche
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
