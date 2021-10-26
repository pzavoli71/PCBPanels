#include "pch.h"
#include "CFileSVG.h"

CFileSVG::CFileSVG():immagini(nullptr) {

}


BOOL CFileSVG::LoadFile(CString& FileName) {
	USES_CONVERSION;
	struct NSVGimage* image;
	image = nsvgParseFromFile(T2A((LPCTSTR)FileName), "mm", 96);
	if (image == nullptr)
		return FALSE;
	immagini = image;
	printf("size: %f x %f\n", image->width, image->height);
	return TRUE;
}