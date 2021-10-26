
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

IMPLEMENT_DYNCREATE(CPCBPanelsView, CScrollView)

BEGIN_MESSAGE_MAP(CPCBPanelsView, CScrollView)
	// Comandi di stampa standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_IMPORTAZIONE_IMPORTASVGACCOPPIATI, &CPCBPanelsView::OnImportazioneImportasvgaccoppiati)
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

#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

void CPCBPanelsView::OnImportazioneImportasvgaccoppiati()
{

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.Flags |= OFN_ALLOWMULTISELECT;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;
	if (dlgFile.DoModal() != IDOK)
		return;

	fileName.ReleaseBuffer();

	CPCBPanelsDoc* doc = GetDocument();
	wchar_t* pBufEnd = p + FILE_LIST_BUFFER_SIZE - 2;
	wchar_t* start = p;
	while ((p < pBufEnd) && (*p))
		p++;
	wchar_t* cartella;
	if (p > start)
	{
		_tprintf(_T("Path to folder where files were selected:  %s\r\n\r\n"), start);
		cartella = start;
		p++;
		if (ofn.lpstrFileTitle != nullptr) {
			CFileSVG* svg = new CFileSVG();
			svg->LoadFile(CString(cartella));
			doc->AddSVGFile(svg);
			return;
		}

		int fileCount = 1;
		while ((p < pBufEnd) && (*p))
		{
			start = p;
			while ((p < pBufEnd) && (*p))
				p++;
			if (p > start) {
				_tprintf(_T("%2d. %s\r\n"), fileCount, start);
				CFileSVG* svg = new CFileSVG();
				svg->LoadFile(CString(cartella) + CString("\\") + CString(start));
				doc->AddSVGFile(svg);
			}
			p++;
			fileCount++;
		}
	}
}


void CPCBPanelsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize DocSize(21*10*100,29.7*10*100);
	SetScrollSizes(MM_HIMETRIC, DocSize, CSize(5000, 5000), CSize(500, 500));
	// TODO: aggiungere qui il codice specifico e/o chiamare la classe di base
}
