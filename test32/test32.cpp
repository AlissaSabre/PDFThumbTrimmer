// test32.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <shobjidl.h>
#include <stdio.h>

const CLSID CLSID_PDFThumbTrimmer = {0x0ADA2DB4, 0xA310, 0x40BC, {0x8A,0xD8,0x42,0x3B,0x6A,0x33,0x3D,0x5A}};

int main()
{
	int argc;
	WCHAR **argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	CoInitialize(NULL);
	HMODULE hDll = LoadLibraryA("PDFThumbTrimmer.DLL");
	if (!hDll)
	{
		exit(11);
	}
	LPFNGETCLASSOBJECT getClassObject = (LPFNGETCLASSOBJECT)GetProcAddress(hDll, "DllGetClassObject");
	if (!getClassObject)
	{
		exit(12);
	}
	HRESULT hr;
	IClassFactory *factory;
	hr = getClassObject(CLSID_PDFThumbTrimmer, IID_IClassFactory, (LPVOID *)&factory);
	if (FAILED(hr))
	{
		exit(1);
	}
	for (int i = 1; i < argc; i++)
	{
		IPersistFile *pf;
		hr = factory->CreateInstance(NULL, IID_IPersistFile, (LPVOID *)&pf);
		if (FAILED(hr))
		{
			exit(2);
		}
		hr = pf->Load(argv[i], STGM_READ | STGM_SHARE_DENY_WRITE);
		if (FAILED(hr))
		{
			exit(3);
		}
		IExtractImage *ei;
		hr = pf->QueryInterface(IID_IExtractImage, (LPVOID *)&ei);
		if (FAILED(hr))
		{
			exit(4);
		}
		OLECHAR path[2048];
		DWORD priority = 0;
		SIZE size = { 256, 256 };
		DWORD flags = IEIFLAG_SCREEN; 
		hr = ei->GetLocation(path, sizeof(path) / sizeof(OLECHAR), &priority, &size, 32, &flags);
		if (FAILED(hr) && hr != E_PENDING)
		{
			exit(5);
		}
		HBITMAP hBmp;
		hr = ei->Extract(&hBmp);
		if (FAILED(hr))
		{
			exit(6);
		}
		DeleteObject(hBmp);
		ei->Release();
		pf->Release();
	}
	factory->Release();
	CoUninitialize();
	return 0;
}

