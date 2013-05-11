#include "stdafx.h"
#include "StubEvcCallback.h"

static const WCHAR EVC_KEY[] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VolumeCaches";
static const WCHAR THUMBNAIL_CACHE[] = L"Thumbnail Cache";

#define ROOT_NAME_LENGTH 4
typedef WCHAR RootName[ROOT_NAME_LENGTH];

#define MAX_DRIVES 26
static RootName roots[MAX_DRIVES + 1];

static StubEvcCallback callback;

static void fatal(LPCSTR cause, HRESULT hr)
{
	fprintf(stderr, "Fatal error (%s) 0x%08lx", cause, hr);
	exit(EXIT_FAILURE);
}

static void init_roots()
{
	DWORD const drive_bits = GetLogicalDrives();
	if (drive_bits == 0) fatal("GetLogicalDrives", HRESULT_FROM_WIN32(GetLastError()));

	// ZeroMemory(roots, sizeof(roots));
	RootName *r = roots;
	for (DWORD drv = 0, bit = 1; drv < MAX_DRIVES; drv++, bit <<= 1)
	{
		if (drive_bits & bit)
		{
			LPWSTR const p = *r;

			p[0] = (WCHAR)('A' + drv);
			p[1] = L':';
			p[2] = L'\\';

			UINT type = GetDriveTypeW(p);
			if (type == DRIVE_FIXED || type == DRIVE_RAMDISK)
			{
				r++;
			}
		}
	}
}

static void purge()
{
	HRESULT hr;
	LONG lr;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) fatal("CoInitialize", hr);

	HKEY hKeyEVC = NULL;
	lr = RegOpenKeyExW(HKEY_LOCAL_MACHINE, EVC_KEY, 0, KEY_READ, &hKeyEVC);
	if (lr != ERROR_SUCCESS) fatal("RegOpenKey/EVC", HRESULT_FROM_WIN32(lr));

	HKEY hKeyHandler = NULL;
	lr = RegOpenKeyExW(hKeyEVC, THUMBNAIL_CACHE, 0, KEY_READ, &hKeyHandler);
	if (lr != ERROR_SUCCESS) fatal("RegOpenKey/Handler", HRESULT_FROM_WIN32(lr));

	DWORD reg_type = 0;
	WCHAR clsid_string[64];
	DWORD size = sizeof(clsid_string);
	lr = RegQueryValueExW(hKeyHandler, NULL, 0, &reg_type, (LPBYTE)clsid_string, &size);
	if (lr != ERROR_SUCCESS) fatal("RegQueryValue/(default)", HRESULT_FROM_WIN32(lr));

	CLSID clsid;
	hr = CLSIDFromString(clsid_string, &clsid);
	if (FAILED(hr)) fatal("CLSIDFromString", hr);

	for (RootName const *r = roots; **r; r++)
	{
		IEmptyVolumeCache2 *evc = NULL;
		hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IEmptyVolumeCache2, (LPVOID *)&evc);
		if (FAILED(hr)) fatal("CoCreateInstance", hr);

		LPWSTR disp = NULL, desc = NULL, button = NULL; // We don't need these, but *do* need to prepare for receiving.
		DWORD flags = 0;
		hr = evc->InitializeEx(hKeyHandler, *r, THUMBNAIL_CACHE, &disp, &desc, &button, &flags);
		if (FAILED(hr)) fatal("InitializeEx", hr);
		CoTaskMemFree(disp);
		CoTaskMemFree(desc);
		CoTaskMemFree(button);

		DWORDLONG space;
		hr = evc->GetSpaceUsed(&space, &callback);
		if (FAILED(hr)) fatal("GetSpaceUsed", hr);

		hr = evc->Purge(space, &callback);
		if (FAILED(hr)) fatal("Purge", hr);

		flags = 0;
		hr = evc->Deactivate(&flags);
		if (FAILED(hr)) fatal("Deactivate", hr);

		evc->Release();
		evc = NULL;
	}

	lr = RegCloseKey(hKeyHandler);
	if (lr != ERROR_SUCCESS) fatal("RegCloseKey/Handler", HRESULT_FROM_WIN32(lr));
	hKeyHandler = NULL;

	lr = RegCloseKey(hKeyEVC);
	if (lr != ERROR_SUCCESS) fatal("RegCloseKey/EVC", HRESULT_FROM_WIN32(lr));
	hKeyEVC = NULL;
}

int main()
{
	init_roots();
	purge();
	return 0;
}
