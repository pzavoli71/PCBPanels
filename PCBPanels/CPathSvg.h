#pragma once
#include "windef.h"
class CPathSvg
{
public:
	CPathSvg() :m_pt(nullptr) {
		m_nPoints = 0;
		m_strokewidth = 0;
		m_bclosed = FALSE;
		m_fillcolor = 0;
		TRACE(_T("Costruttore CPathSvg\n"));
	}

	~CPathSvg() {
		if (m_pt != nullptr)
			delete []m_pt;
	}

public:
	POINT *m_pt;
	int m_nPoints;
	int m_strokewidth;
	BOOL m_bclosed;
	int m_fillcolor;
};

