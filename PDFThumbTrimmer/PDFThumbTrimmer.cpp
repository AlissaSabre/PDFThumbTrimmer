#include "stdafx.h"
#include "dllmain.h"
#include "PDFThumbTrimmer.h"
#include "trimmer.h"

PDFThumbTrimmer::PDFThumbTrimmer(IClassFactory *parentFactory)
	: m_ref(1)
{
	HRESULT hr;

	m_parent = NULL;
	m_this_as_runnable_task = NULL;

	if (!parentFactory) throw E_NOTIMPL;
	hr = parentFactory->CreateInstance(NULL, IID_IExtractImage, (LPVOID *)&m_parent);
	if (FAILED(hr)) throw hr;

	hr = m_parent->QueryInterface(IID_IRunnableTask, (LPVOID *)&m_this_as_runnable_task);
	if (FAILED(hr)) m_this_as_runnable_task = NULL;

	InterlockedIncrement(&g_ref);
}

PDFThumbTrimmer::~PDFThumbTrimmer()
{
	InterlockedDecrement(&g_ref);

	if (m_this_as_runnable_task) m_this_as_runnable_task->Release();

	if (m_parent) m_parent->Release();
	m_parent = NULL;
}

STDMETHODIMP PDFThumbTrimmer::QueryInterface(REFIID riid, void **ppvObject)
{
	if (IsEqualIID(riid, IID_IPersistFile) ||
		IsEqualIID(riid, IID_IPersist) ||
		IsEqualIID(riid, IID_IUnknown))
	{
		*ppvObject = static_cast<IPersistFile *>(this);
		this->AddRef();
		return S_OK;
	}

	if (IsEqualIID(riid, IID_IExtractImage))
	{
		*ppvObject = static_cast<IExtractImage *>(this);
		this->AddRef();
		return S_OK;
	}

	if (IsEqualIID(riid, IID_IRunnableTask) && m_this_as_runnable_task)
	{
		*ppvObject = static_cast<IRunnableTask *>(this);
		this->AddRef();
		return S_OK;
	}
		
	*ppvObject = NULL;
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) PDFThumbTrimmer::AddRef()
{
	return (ULONG)InterlockedIncrement(&m_ref);
}


STDMETHODIMP_(ULONG) PDFThumbTrimmer::Release()
{
	ULONG n = (ULONG)InterlockedDecrement(&m_ref);
	if (n == 0) delete this;
	return n;
}

STDMETHODIMP PDFThumbTrimmer::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDFThumbTrimmer;
	return S_OK;
}

STDMETHODIMP PDFThumbTrimmer::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
	HRESULT hr;
	IPersistFile *persist_file;
	hr = m_parent->QueryInterface(IID_IPersistFile, (LPVOID *)&persist_file);
	if (FAILED(hr)) return E_UNEXPECTED;
	hr = persist_file->Load(pszFileName, dwMode);
	persist_file->Release();
	return hr;
}

STDMETHODIMP PDFThumbTrimmer::GetCurFile(LPOLESTR *ppszFileName)
{
	ppszFileName = NULL;
	return E_NOTIMPL;
}

STDMETHODIMP PDFThumbTrimmer::IsDirty()
{
	return S_FALSE;
}

STDMETHODIMP PDFThumbTrimmer::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP PDFThumbTrimmer::SaveCompleted(LPCOLESTR pszFileName)
{
	return E_NOTIMPL;
}

STDMETHODIMP PDFThumbTrimmer::GetLocation(LPWSTR pszPathBuffer, DWORD cchMax, DWORD *pdwPriority, const SIZE *prgSize, DWORD dwRecClrDepth, DWORD *pdwFlags)
{
	HRESULT hr = m_parent->GetLocation(pszPathBuffer, cchMax, pdwPriority, prgSize, dwRecClrDepth, pdwFlags);
#if 0
	// I'm not sure how E_PENDING return from GetLocation and 
	// IRunnableTasks interface meant to interact, primarily
	// because the related MSDN pages are so cryptic, and 
	// probably because I'm a fool, but I *surely* know that 
	// returning E_PENDING from my own thumbnail handler causes 
	// a lot of troubles...
	if (E_PENDING == hr) hr = S_OK;
#else
	// Well, I think this is how.  Not just this part of the
	// program, but the entire change is.  The code now works
	// with no significant problems.  I guss The "problem" I 
	// wrote above was caused by the PDFThumbTrimmer's 
	// behaviour that its GetLocation returns E_PENDING *and*
	// its QueryInterface(IID_IRunnableTask) returns E_NOINTERFACE,
	// where Windows Explorer apparently couldn't handle.
#endif
	return hr;
}

STDMETHODIMP PDFThumbTrimmer::Extract(HBITMAP *phBmpImage)
{
#if _M_IX86
	// In 32 bit version, we ask our parent (i.e., original PDF 
	// Shell Extension) to extract a thumbnail image, and then 
	// trim the image.

	HRESULT hr;
	*phBmpImage = NULL;

	HBITMAP hBmp1;
	hr = m_parent->Extract(&hBmp1);
	if (FAILED(hr)) return hr;

	HBITMAP hBmp2;
	hr = trim(hBmp1, &hBmp2);
	if (FAILED(hr))
	{
		// The trimming failed for some reason, but we have
		// a valid handle to the original image.  Returning
		// an untrimmed image is probably better than nothing.
		*phBmpImage = hBmp1;
		return S_OK;
	}

	DeleteObject(hBmp1);
	*phBmpImage = hBmp2;
	return S_OK;
#else
	// In 64 bit version, we don't need to trim the returned
	// image, since the parent is the 32 bit version of this
	// class, and it should have trimmed the image (as you
	// see above.)
	return m_parent->Extract(phBmpImage);
#endif
}

STDMETHODIMP_(ULONG) PDFThumbTrimmer::IsRunning()
{
	return m_this_as_runnable_task->IsRunning();
}

STDMETHODIMP PDFThumbTrimmer::Run()
{
	return m_this_as_runnable_task->Run();
}

STDMETHODIMP PDFThumbTrimmer::Kill(BOOL fUnused)
{
	return m_this_as_runnable_task->Kill(fUnused);
}

STDMETHODIMP PDFThumbTrimmer::Resume()
{
	return m_this_as_runnable_task->Resume();
}

STDMETHODIMP PDFThumbTrimmer::Suspend()
{
	return m_this_as_runnable_task->Suspend();
}

