#pragma once
#include "nanosvg.h"
#include "nanosvgrast.h"
#include "cpathsvg.h"
#include "afxwin.h"

class CFileSVG
{
	
public:
	CFileSVG();
	~CFileSVG() {
		if ( immagini != nullptr)
			nsvgDelete( immagini);
		if (m_paths != nullptr)
			delete []m_paths;
		if (m_img != nullptr)
			free(m_img);
	}

public:
	BOOL LoadFile(CString& FileName, CDC *dc);
	NSVGimage* GetImmagini() { return immagini; }
	CPathSvg* GetPaths() {
		return m_paths;
	}
	int GetNumPaths() {
		return m_nPaths;
	}
	CBitmap* GetBitmapBits() {
		return &m_bm;
	}

	inline void PremultiplyBitmapAlpha(HDC hDC, HBITMAP hBmp)
	{
		BITMAP bm = { 0 };
		GetObject(hBmp, sizeof(bm), &bm);
		BITMAPINFO* bmi = (BITMAPINFO*)_alloca(sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
		::ZeroMemory(bmi, sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
		bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		BOOL bRes = ::GetDIBits(hDC, hBmp, 0, bm.bmHeight, NULL, bmi, DIB_RGB_COLORS);
		if (!bRes || bmi->bmiHeader.biBitCount != 32) return;
		LPBYTE pBitData = (LPBYTE) ::LocalAlloc(LPTR, bm.bmWidth * bm.bmHeight * sizeof(DWORD));
		if (pBitData == NULL) return;
		LPBYTE pData = pBitData;
		::GetDIBits(hDC, hBmp, 0, bm.bmHeight, pData, bmi, DIB_RGB_COLORS);
		for (int y = 0; y < bm.bmHeight; y++) {
			for (int x = 0; x < bm.bmWidth; x++) {
				pData[0] = (BYTE)((DWORD)pData[0] * pData[3] / 255);
				pData[1] = (BYTE)((DWORD)pData[1] * pData[3] / 255);
				pData[2] = (BYTE)((DWORD)pData[2] * pData[3] / 255);
				pData += 4;
			}
		}
		::SetDIBits(hDC, hBmp, 0, bm.bmHeight, pBitData, bmi, DIB_RGB_COLORS);
		::LocalFree(pBitData);
	}

protected:
	struct NSVGimage* immagini;
	CPathSvg *m_paths;
	int m_nPaths;
	CBitmap m_bm;
	unsigned char* m_img;
};

