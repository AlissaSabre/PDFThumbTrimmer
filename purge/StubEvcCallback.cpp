#include "StdAfx.h"
#include "StubEvcCallback.h"

// This is just a sort of a stub.  Methods does
// minimum things.  A significant shoddy is its 
// life-cycle management; its AddRef and Release
// don't work.  We need to manage instances by
// ourselves.  It is not a real COM object after 
// all.

STDMETHODIMP StubEvcCallback::QueryInterface(REFIID riid, LPVOID *ppvObject)
{
	if (ppvObject == NULL) return E_POINTER;

	if (IsEqualIID(riid, IID_IUnknown) ||
		IsEqualIID(riid, IID_IEmptyVolumeCacheCallBack))
	{
		*ppvObject = this;
		return S_OK;
	}

	*ppvObject = NULL;
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubEvcCallback::AddRef()
{
	return 1;
}

STDMETHODIMP_(ULONG) StubEvcCallback::Release()
{
	return 1;
}

STDMETHODIMP StubEvcCallback::ScanProgress(DWORDLONG, DWORD, LPCWSTR)
{
	return S_OK;
}

STDMETHODIMP StubEvcCallback::PurgeProgress(DWORDLONG, DWORDLONG, DWORD, LPCWSTR)
{
	return S_OK;
}
