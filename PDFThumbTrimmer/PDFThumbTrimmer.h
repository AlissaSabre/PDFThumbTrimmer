#pragma once

#include "stdafx.h"

class PDFThumbTrimmer : public IPersistFile, public IExtractImage
{
public:
	PDFThumbTrimmer(IClassFactory *parentFactory);
	~PDFThumbTrimmer();

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	// IPersist
	STDMETHODIMP GetClassID(CLSID *pClassID);

	// IPersistFile
	STDMETHODIMP Load(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHODIMP GetCurFile(LPOLESTR *ppszFileName);
	STDMETHODIMP IsDirty();
	STDMETHODIMP Save(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHODIMP SaveCompleted(LPCOLESTR pszFileName);

	// IExtractImage
	STDMETHODIMP GetLocation(LPWSTR pszPathBuffer, DWORD cchMax, DWORD *pdwPriority, const SIZE *prgSize, DWORD dwRecClrDepth, DWORD *pdwFlags);
	STDMETHODIMP Extract(HBITMAP *phBmpImage);

private:
	volatile LONG m_ref;
	IExtractImage *m_parent;
};
