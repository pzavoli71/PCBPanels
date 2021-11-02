#include "pch.h"
#include "CFileSVG.h"

CFileSVG::CFileSVG():immagini(nullptr),m_paths(nullptr),m_img(nullptr) {
	m_nPaths = 0;
}


BOOL CFileSVG::LoadFile(CString& FileName, CDC *dc) {
	USES_CONVERSION;
	struct NSVGimage* image;
	image = nsvgParseFromFile(T2A((LPCTSTR)FileName), "mm", 100);
	if (image == nullptr)
		return FALSE;

	CFileSVG* file = this;
	NSVGimage* img = image;
	// Prima conto le shapes contenute nel file
	int nshapes = 0, npaths = 0;
	NSVGshape* shape = img->shapes;
	while (shape != nullptr) {
		nshapes++;
		NSVGpath* path = shape->paths;
		while (path != nullptr) {
			npaths++;
			path = path->next;
		}
		shape = shape->next;
	}
	m_paths = new CPathSvg[npaths];

	// Ora costruisco l'array di punti
	int nshape = 0, npath = 0;
	shape = img->shapes;
	while (shape != nullptr) {
		NSVGpath* path = shape->paths;
		while (path != nullptr) {
			float* f = path->pts;
			int npoints = 0;
			TRACE("Leggo il path n.%d\n", npath);
			CPathSvg* pathsvg = &(m_paths[npath]);
			if ( path->closed)
				pathsvg->m_pt = new POINT[path->npts * 2 + 1];
			else
				pathsvg->m_pt = new POINT[path->npts * 2];
			for (int i = 0; i < path->npts; i += 1) {
				pathsvg->m_pt[i].x = f[i * 2] * 100 + 10000; pathsvg->m_pt[i].y = -f[i * 2 + 1] * 100;
				npoints++;
			}
			if (shape->strokeWidth > 0)
				pathsvg->m_strokewidth = shape->strokeWidth * 100;
			if (path->closed) {
				pathsvg->m_bclosed = TRUE;
				//pathsvg->m_pt[path->npts].x = pathsvg->m_pt[0].x;
				//pathsvg->m_pt[path->npts].y = pathsvg->m_pt[0].y;
				//npoints++;
			}
			if (shape->fill.color != 0 && shape->opacity == 1) {
				pathsvg->m_fillcolor = 16777215;
			}
			pathsvg->m_nPoints = npoints;

			path = path->next;
			npath++;
		}
		shape = shape->next;
		nshape++;
	}
	m_nPaths = npath;
	immagini = image;


	struct NSVGrasterizer* rast = nsvgCreateRasterizer();
	//m_bm.CreateBitmap(image->width, image->height,4,1,NULL);
	m_bm.CreateCompatibleBitmap(dc, image->width, image->height);
	if (m_img != nullptr)
		free(m_img);
	m_img = (unsigned char *) malloc(image->width * image->height * 4);
	nsvgRasterize(rast, img, 0, 0, 3, m_img, image->width, image->height, image->width * 4); // Era * 4
	for (int i = 0; i < image->width * image->height * 4; i += 4) {
		unsigned char r = m_img[i + 0];
		unsigned char g = m_img[i + 1];
		unsigned char b = m_img[i + 2];
		unsigned char a = m_img[i + 3];
		r = (BYTE)((DWORD) r * a / 255);
		g = (BYTE)((DWORD) g * a / 255);
		b = (BYTE)((DWORD) b * a / 255);
		m_img[i + 0] = r;
		m_img[i + 1] = g;
		m_img[i + 2] = b;
		//m_img[i + 3] = 0;

	}
	m_bm.SetBitmapBits(image->width * image->height * 4, m_img);
	nsvgDeleteRasterizer(rast);
	//PremultiplyBitmapAlpha(dc->m_hDC, m_bm);

	printf("size: %f x %f\n", image->width, image->height);
	return TRUE;
}