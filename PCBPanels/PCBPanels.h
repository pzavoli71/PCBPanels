
// PCBPanels.h: file di intestazione principale per l'applicazione PCBPanels
//
#pragma once

#ifndef __AFXWIN_H__
	#error "includere 'pch.h' prima di includere questo file per PCH"
#endif

#include "resource.h"       // simboli principali


// CPCBPanelsApp:
// Per l'implementazione di questa classe, vedere PCBPanels.cpp
//

class CPCBPanelsApp : public CWinApp
{
public:
	CPCBPanelsApp() noexcept;


// Override
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementazione
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPCBPanelsApp theApp;
