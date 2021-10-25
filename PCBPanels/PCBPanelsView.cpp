
// PCBPanelsView.cpp: implementazione della classe CPCBPanelsView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS può essere definito in un'anteprima di implementazione del progetto ATL, nei gestori di anteprime
// e della ricerca e consente di condividere il codice dei documenti con il progetto in questione.
#ifndef SHARED_HANDLERS
#include "PCBPanels.h"
#endif

#include "PCBPanelsDoc.h"
#include "PCBPanelsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPCBPanelsView

IMPLEMENT_DYNCREATE(CPCBPanelsView, CView)

BEGIN_MESSAGE_MAP(CPCBPanelsView, CView)
	// Comandi di stampa standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Costruzione/distruzione di CPCBPanelsView

CPCBPanelsView::CPCBPanelsView() noexcept
{
	// TODO: aggiungere qui il codice di costruzione.

}

CPCBPanelsView::~CPCBPanelsView()
{
}

BOOL CPCBPanelsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificare la classe o gli stili Window modificando
	//  la struttura CREATESTRUCT

	return CView::PreCreateWindow(cs);
}

// Disegno di CPCBPanelsView

void CPCBPanelsView::OnDraw(CDC* /*pDC*/)
{
	CPCBPanelsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: aggiungere qui il codice di disegno per i dati nativi.
}


// Stampa di CPCBPanelsView

BOOL CPCBPanelsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// preparazione predefinita
	return DoPreparePrinting(pInfo);
}

void CPCBPanelsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: inserire un'ulteriore inizializzazione prima della stampa.
}

void CPCBPanelsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: aggiungere pulizia dopo la stampa.
}


// Diagnostica di CPCBPanelsView

#ifdef _DEBUG
void CPCBPanelsView::AssertValid() const
{
	CView::AssertValid();
}

void CPCBPanelsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPCBPanelsDoc* CPCBPanelsView::GetDocument() const // la versione non debug è inline.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCBPanelsDoc)));
	return (CPCBPanelsDoc*)m_pDocument;
}
#endif //_DEBUG


// Gestori di messaggi di CPCBPanelsView
