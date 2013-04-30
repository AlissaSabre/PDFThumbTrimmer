#pragma once

#include "stdafx.h"

class CClassFactory : public IClassFactory
{
public:
	CClassFactory();
	~CClassFactory();

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	// IClassFactory
	STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
	STDMETHODIMP LockServer(BOOL fLock);

private:
	volatile LONG m_ref;
	IClassFactory *m_parent_factory;
};

