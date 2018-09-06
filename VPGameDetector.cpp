#include "stdafx.h"
#include "VPGameDetector.h"
#include "RegWorkerFunc.h"

//************** CVPGameDetector definition *******************//
CVPGameDetector::CVPGameDetector() : m_refCount(0)						
{
    CComPtr<ITypeLib> pTypeLib;
    HRESULT hr;
    hr = LoadRegTypeLib(LIBID_VPGameEmulatorLib, 1, 0, 0, &pTypeLib);
    CComPtr<ITypeInfo> pTypeInfo;
    hr = pTypeLib->GetTypeInfoOfGuid(IID_IGameDetector, &m_pTypeInfo);
}

CVPGameDetector::~CVPGameDetector()
{
}

//IUnknown method implementations
STDMETHODIMP_(ULONG) CVPGameDetector::AddRef() 
{
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CVPGameDetector::Release() 
{
    ULONG ret(--m_refCount);
    if(!ret) 
		delete this;
	
    return ret;
}

STDMETHODIMP CVPGameDetector::QueryInterface(REFIID riid, void** ppv) 
{
    if(!ppv) 
		return E_POINTER;
    if(riid == IID_IUnknown || riid == IID_IGameDetector)
		*ppv = static_cast<IGameDetector*>(this);
    else if(riid == IID_IDispatch)
		*ppv = static_cast<IDispatch*>(this);
    else
		return *ppv = NULL, E_NOINTERFACE;
		
	((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

//IDispatch method implementations
STDMETHODIMP CVPGameDetector::GetIDsOfNames(REFIID riid, OLECHAR** rgszNames, UINT cNames,
    LCID lcid, DISPID* rgDispId) 
{
    if(lcid == 0 || lcid == 9 || lcid == 0x409)
        return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);
    return DISP_E_UNKNOWNLCID;
}

STDMETHODIMP CVPGameDetector::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
{
    if(iTInfo) 
		return TYPE_E_ELEMENTNOTFOUND;
    if(!ppTInfo) 
		return E_POINTER;
    if(lcid == 0 || lcid == 9 || lcid == 0x409)
        return m_pTypeInfo.CopyTo(ppTInfo), S_OK;

    return *ppTInfo = NULL, DISP_E_UNKNOWNLCID;
}

STDMETHODIMP CVPGameDetector::GetTypeInfoCount(UINT* pctinfo) 
{
    if(!pctinfo) return E_POINTER;
    return *pctinfo = 1, S_OK;
}

STDMETHODIMP CVPGameDetector::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
    DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgError) 
{
    if(lcid == 0 || lcid == 9 || lcid == 0x409) {
		void *pvThis = static_cast<IGameDetector*>(this);
        return m_pTypeInfo->Invoke(pvThis, dispIdMember, wFlags, pDispParams, NULL,
        NULL, NULL);
    }
    return DISP_E_UNKNOWNLCID;
}

//Define IGameDetector

STDMETHODIMP CVPGameDetector::get_GameNames(VARIANT *pVal)
{
	std::vector<CComBSTR> vecGames;

	if(GetGamesList(&vecGames) == true)
	{
		pVal->vt = VT_ARRAY | VT_BSTR;
		SAFEARRAY* psa;
		SAFEARRAYBOUND bounds = {vecGames.size(), 0};
		BSTR* bstrGameNames;
		
		psa = SafeArrayCreate(VT_BSTR, 1, &bounds);
		SafeArrayAccessData(psa, reinterpret_cast<void**>(&bstrGameNames));
		std::vector<CComBSTR>::iterator it;
		
		int i = 0;
		for(it = vecGames.begin(); it != vecGames.end(); it++, i++)
			bstrGameNames[i] = SysAllocString((*it).m_str);

		SafeArrayUnaccessData(psa);
		pVal->parray = psa;

		return S_OK;
	}

	return E_FAIL;
}

STDMETHODIMP CVPGameDetector::CLSIDFromGameName(BSTR GameName, BSTR *GameCLSID)
{
	if(SysStringLen(GameName) == 0)
		return E_FAIL;

	USES_CONVERSION;
	bool success = false;
	char* rootKey = "Software\\Ubique\\VpGames32\\"; //store our root key string
	//convert BSTR gamename to char*
	_bstr_t gmName = GameName;
	char* gName = (LPTSTR)gmName;
	//grab the string lengths, and allocate the memory to hold the data.
	UINT lenRootKey = strlen(rootKey);
	UINT lenGmName = SysStringLen(GameName);
	char* keyName = new char[lenRootKey + lenGmName + 1];
	//concatenate root key, and gamename to create our whole keyname string.
	strcpy(keyName, rootKey);
	strcat(keyName, gName); 
	strcat(keyName, "\0"); //must null terminate string !

	char* clsid;
	if(GetCurrentCLSID(keyName, &clsid))
	{
		*GameCLSID = SysAllocString(T2OLE(clsid));
		delete[] clsid;
		clsid = 0;
		success = true;
	}
	
	delete keyName;
	keyName = 0;
	
	if(success == true)
		return S_OK;
	else
		return E_FAIL;
}

//*********** Define our ClassFactory for CVPGameDetector *****************//

CVPGameDetectorFactory::CVPGameDetectorFactory() : m_refCount(0)
{
}

//IUnknow implementation
STDMETHODIMP_(ULONG) CVPGameDetectorFactory::AddRef() 
{
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CVPGameDetectorFactory::Release() 
{
    ULONG ret(--m_refCount);
    if(!ret) delete this;
    return ret;
}

STDMETHODIMP CVPGameDetectorFactory::QueryInterface(REFIID riid, void** ppv) 
{
    if(!ppv) 
		return E_POINTER;
    if(riid == IID_IUnknown) 
		*ppv = static_cast<IUnknown*>(this);
    else if(riid == IID_IClassFactory) 
		*ppv = static_cast<IClassFactory*>(this);
    else 
		return *ppv = NULL, E_NOINTERFACE;

	static_cast<IUnknown*>(*ppv)->AddRef();

    return S_OK;
}

//IClassFactory implementation
STDMETHODIMP CVPGameDetectorFactory::CreateInstance(IUnknown* pUnk, REFIID riid, void** ppv) 
{
    if(pUnk) 
		return CLASS_E_NOAGGREGATION;

    CVPGameDetector* vpgd = new CVPGameDetector;
	if(vpgd == NULL)
		return E_OUTOFMEMORY;

    HRESULT hr = vpgd->QueryInterface(riid, ppv);
    
	if(FAILED(hr)) 
		delete vpgd;
	
    return hr;
}

STDMETHODIMP CVPGameDetectorFactory::LockServer(BOOL lock) 
{ 
	return S_OK; 
}
