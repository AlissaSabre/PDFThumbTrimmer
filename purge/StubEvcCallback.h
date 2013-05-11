#pragma once

#include "stdafx.h"

/// This is a stub implementation of the callback,
/// that does nothing.
class StubEvcCallback :	public IEmptyVolumeCacheCallBack
{
public:

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	// IEmptyVolumeCacheCallback
	STDMETHODIMP ScanProgress(DWORDLONG, DWORD, LPCWSTR);
	STDMETHODIMP PurgeProgress(DWORDLONG, DWORDLONG, DWORD, LPCWSTR);
};

