#include "stdafx.h"
#include "dllmain.h"
#include "ClassFactory.h"

// {0ADA2DB4-A310-40BC-8AD8-423B6A333D5A}
const CLSID CLSID_PDFThumbTrimmer = {0x0ADA2DB4, 0xA310, 0x40BC, {0x8A,0xD8,0x42,0x3B,0x6A,0x33,0x3D,0x5A}};

// {F9DB5320-233E-11D1-9F84-707F02C10627}
const CLSID CLSID_PDFShellExtension = {0xF9DB5320, 0x233E, 0x11D1, {0x9F,0x84,0x70,0x7F,0x02,0xC1,0x06,0x27}};

HINSTANCE g_hInstDll;
volatile LONG g_ref;

BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		g_hInstDll = hModule;
		g_ref = 0;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

STDAPI DllCanUnloadNow()
{
	return (g_ref == 0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

	if (IsEqualCLSID(rclsid, CLSID_PDFThumbTrimmer))
	{
		try
		{
			CClassFactory *obj = new CClassFactory();
			HRESULT result = obj->QueryInterface(riid, ppv);
			obj->Release();
			return result;
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

	return CLASS_E_CLASSNOTAVAILABLE;
}
