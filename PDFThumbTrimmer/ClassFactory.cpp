#include "stdafx.h"
#include "dllmain.h"
#include "ClassFactory.h"
#include "PDFThumbTrimmer.h"

#if _M_IX86
// 32 bit version delegates to the original PDF Shell Extension DLL (and performs post processing.)
#define PARENT_CLSID CLSID_PDFShellExtension
#define PARENT_CLSCTX CLSCTX_INPROC_SERVER
#else
// 64 bit version delegates to the 32 bit version of this class, through a DLL surrogate.
#define PARENT_CLSID CLSID_PDFThumbTrimmer
#define PARENT_CLSCTX (CLSCTX_LOCAL_SERVER | CLSCTX_ACTIVATE_32_BIT_SERVER)
#endif

CClassFactory::CClassFactory()
	: m_ref(1)
{
	m_parent_factory = NULL;
	CoGetClassObject(PARENT_CLSID, PARENT_CLSCTX, NULL, IID_IClassFactory, (LPVOID *)&m_parent_factory);
	InterlockedIncrement(&g_ref);
}

CClassFactory::~CClassFactory()
{
	InterlockedDecrement(&g_ref);
	if (m_parent_factory) m_parent_factory->Release();
	m_parent_factory = NULL;
}

STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	if (IsEqualIID(riid, IID_IClassFactory) ||
		IsEqualIID(riid, IID_IUnknown))
	{
		*ppvObject = static_cast<IClassFactory *>(this);
		this->AddRef();
		return S_OK;
	}
		
	*ppvObject = NULL;
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CClassFactory::AddRef()
{
	return (ULONG)InterlockedIncrement(&m_ref);
}


STDMETHODIMP_(ULONG) CClassFactory::Release()
{
	ULONG n = (ULONG)InterlockedDecrement(&m_ref);
	if (n == 0) delete this;
	return n;
}

STDMETHODIMP CClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;

	if (pUnkOuter)
	{
		return CLASS_E_NOAGGREGATION;
    }

	try
	{
		PDFThumbTrimmer *obj = new PDFThumbTrimmer(m_parent_factory);
		HRESULT hr = obj->QueryInterface(riid, ppvObject);
		obj->Release();
		return hr;
	}
	catch (HRESULT result)
	{
		return result;
	}
	catch (std::bad_alloc)
	{
		return E_OUTOFMEMORY;
	}
	catch (...)
	{
		return E_UNEXPECTED;
	}
}

STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
	return S_OK;
}


