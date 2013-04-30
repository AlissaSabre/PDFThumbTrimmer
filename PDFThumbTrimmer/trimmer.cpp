#include "stdafx.h"
#include "trimmer.h"

#if _M_IX86

// The trimming code is only needed in 32 bit DLL

#define IS_WHITE(X) (0xFFFFFF == ((X) & 0xFFFFFF))

static bool are_white(LPDWORD p, LONG width, LONG height)
{
	for (int i = 0; i < height; i++)
	{
		if (!IS_WHITE(*p)) return false;
		p += width;
	}
	return true;
}

static HRESULT find_trimmer(LPDWORD bits, LONG width, LONG height, LPRECT rect)
{
	rect->left = 0;
	rect->top = 0;
	rect->right = width;
	rect->bottom = height;

	// Make sure the four corners are all white; otherwise
	// there can be no margines.
	if (!IS_WHITE(bits[0]) ||
		!IS_WHITE(bits[width - 1]) ||
		!IS_WHITE(bits[width * (height - 1)]) ||
		!IS_WHITE(bits[width * height - 1]))
	{
		return E_FAIL;
	}

	// Try top and bottom margines first, because its easier.
	LPDWORD p = bits, q = bits + width * height - 1;
	while (q > bits && IS_WHITE(*q)) --q;
	while (p < q    && IS_WHITE(*p)) p++;

	rect->top += (LONG)(p - bits) / width;
	rect->bottom -= (LONG)(bits + width * height - 1 - q) / width;

	// Try left and right margines, next.
	int m = 0, n = width - 1;
	while (n > 0 && are_white(bits + n, width, height)) --n;
	while (m < n && are_white(bits + m, width, height)) m++;

	rect->left = m;
	rect->right = n + 1;

	return S_OK;
}

struct AutoDC
{
	HDC m_hDC;
	AutoDC()		{ m_hDC = GetDC(NULL); }
	~AutoDC()		{ if (m_hDC) ReleaseDC(NULL, m_hDC); }
	operator HDC()	{ return m_hDC; }
};

template<class T>
struct AutoLP
{
	T *m_ptr;
	AutoLP()				{ m_ptr = NULL; }
	~AutoLP()				{ if (m_ptr) HeapFree(GetProcessHeap(), 0, m_ptr); }
	T *alloc(size_t size)	{ return m_ptr = (T *)HeapAlloc(GetProcessHeap(), 0, size * sizeof(T)); }
};

HRESULT trim(HBITMAP hSrcBitmap, HBITMAP *phOutBitmap)
{
	AutoLP<DWORD> local_bits;
	DWORD *bits = NULL;
	LONG width, height;

	AutoDC hDC;
	if (hDC == NULL)
	{
		return E_UNEXPECTED;
	}

	DIBSECTION dibsec;
	ZeroMemory(&dibsec, sizeof(dibsec));
	int objsize = GetObject(hSrcBitmap, sizeof(dibsec), &dibsec);

	if (sizeof(DIBSECTION) == objsize &&
		dibsec.dsBm.bmWidth * sizeof(DWORD) == dibsec.dsBm.bmWidthBytes * sizeof(BYTE) && 
		1 == dibsec.dsBm.bmPlanes &&
		32 == dibsec.dsBm.bmBitsPixel &&
		NULL != dibsec.dsBm.bmBits &&
		BI_RGB == dibsec.dsBmih.biCompression)
	{
		// Ok.  The source bitmap seems from CreateDIBSection().
		width  = dibsec.dsBm.bmWidth;
		height = dibsec.dsBm.bmHeight;
		bits = (LPDWORD)dibsec.dsBm.bmBits;
	}
	else if (sizeof(BITMAP) == objsize)
	{
		// The source bitmap doesn't appear as one by CreateDIBSection().
		// Simulate the behaviour.

		width  = dibsec.dsBm.bmWidth;
		height = dibsec.dsBm.bmHeight;

		dibsec.dsBmih.biSize = sizeof(BITMAPINFOHEADER);
		dibsec.dsBmih.biWidth = width;
		dibsec.dsBmih.biHeight = -height;
		dibsec.dsBmih.biPlanes = 1;
		dibsec.dsBmih.biBitCount = 32;
		dibsec.dsBmih.biCompression = BI_RGB;

		bits = local_bits.alloc(width * height);
		if (bits == NULL)
		{
			return E_OUTOFMEMORY;
		}

		if (height != GetDIBits(hDC, hSrcBitmap, 0, height, bits, (LPBITMAPINFO)&dibsec.dsBmih, DIB_RGB_COLORS))
		{
			return E_UNEXPECTED;
		}
	}
	else
	{
		return E_UNEXPECTED;
	}

	RECT rect;
	if (FAILED(find_trimmer(bits, width, height, &rect)))
	{
		return E_UNEXPECTED;
	}

	LONG new_width = rect.right - rect.left;
	LONG new_height = rect.bottom - rect.top;
	LPDWORD new_bits;
	dibsec.dsBmih.biWidth = new_width;
	dibsec.dsBmih.biHeight = (dibsec.dsBmih.biHeight > 0 ? new_height : -new_height); // XXX
	*phOutBitmap = CreateDIBSection(hDC, (LPBITMAPINFO)&dibsec.dsBmih, DIB_RGB_COLORS, (VOID **)&new_bits, NULL, 0);
	if (*phOutBitmap == NULL)
	{
		return E_UNEXPECTED;
	}

	DWORD *p = new_bits;
	for (int h = rect.top; h < rect.bottom; h++)
	{
		DWORD const *q = bits + h * width + rect.left;
#if 1
		CopyMemory(p, q, new_width * sizeof(DWORD));
		p += new_width;
#else
		for (int w = rect.left; w < rect.right; w++)
		{
			*p++ = *q++ | 0xFF000000;
		}
#endif
	}

	return S_OK;
}

#endif /* _M_IX86 */
