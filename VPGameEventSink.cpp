#include "stdafx.h"
#include "VPGEventSink.h"
#include "VPGameDetector.h"
#include "VPGame.h"
#include "VPGameEventSink_i.c"
#include "resource.h"

void RegisterServer(wchar_t* widePath, bool reg) 
{
    ATL::CRegObject ro;
		ro.FinalConstruct();
    ro.AddReplacement(L"Module", widePath);
   
	if(reg == true)
	{
		ro.ResourceRegister(widePath, IDR_VPGEVENTSINK, L"REGISTRY");
		ro.ResourceRegister(widePath, IDR_VPGDETECT, L"REGISTRY");
		ro.ResourceRegister(widePath, IDR_VPG, L"REGISTRY");
	}
	else
	{
        ro.ResourceUnregister(widePath, IDR_VPGEVENTSINK, L"REGISTRY");
		ro.ResourceUnregister(widePath, IDR_VPGDETECT, L"REGISTRY");
		ro.ResourceUnregister(widePath, IDR_VPG, L"REGISTRY");
	}
}

HINSTANCE hInstance;

STDMETHODIMP_(INT) DllMain(HINSTANCE hInstance, DWORD reason, void*) 
{
    ::hInstance = hInstance;
    return 1;
}

void GetPathName(wchar_t* widePath) 
{
    char ansiPath[MAX_PATH];
    GetModuleFileName(hInstance, ansiPath, MAX_PATH);
    MultiByteToWideChar(CP_ACP, 0, ansiPath, lstrlen(ansiPath) + 1, widePath, MAX_PATH);
}

extern "C" STDMETHODIMP DllRegisterServer() 
{
    wchar_t widePath[MAX_PATH];
    GetPathName(widePath);
    RegisterServer(widePath, true);
    CComPtr<ITypeLib> pTypeLib;
    HRESULT hr(LoadTypeLib(widePath, &pTypeLib));
    
	if(hr) 
		return SELFREG_E_TYPELIB;

    hr = RegisterTypeLib(pTypeLib, widePath, 0);
    if(hr) 
		return SELFREG_E_TYPELIB;

    return S_OK;
}

extern "C" STDMETHODIMP DllUnregisterServer() 
{
    wchar_t widePath[MAX_PATH];
    GetPathName(widePath);
    RegisterServer(widePath, false);
    HRESULT hr(UnRegisterTypeLib(LIBID_VPGameEmulatorLib, 1, 0, 0, SYS_WIN32));
    if(hr) return SELFREG_E_TYPELIB;
    return S_OK;
}

//and finally our last dll functions
extern "C" STDMETHODIMP DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
	HRESULT hr = S_OK;
	void* vpgCLSFactory;
	
	if(rclsid == CLSID_VPGameEventSink)
		vpgCLSFactory = new CVPGameEventSinkFactory;
	else if(rclsid == CLSID_VPGameDetector)
		vpgCLSFactory = new CVPGameDetectorFactory;
	else if(rclsid == CLSID_VPGame)
		vpgCLSFactory = new CVPGameFactory;
	else
		return *ppv = NULL, CLASS_E_CLASSNOTAVAILABLE;
	
	hr = static_cast<IUnknown*>(vpgCLSFactory)->QueryInterface(riid, ppv);

	if(!SUCCEEDED(hr)) 
		*ppv = NULL;

	return hr;
}

extern "C" STDMETHODIMP DllCanUnloadNow() 
{
	return S_FALSE;
}