#pragma once
#include "nanosvg.h"

class CFileSVG
{
	
public:
	CFileSVG();
	~CFileSVG() {
		if ( immagini != nullptr)
			delete immagini;
	}

public:
	BOOL LoadFile(CString& FileName);
	NSVGimage* GetImmagini() { return immagini; }
protected:
	struct NSVGimage* immagini;
};

