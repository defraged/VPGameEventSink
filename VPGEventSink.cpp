#include "stdafx.h"
#include "VPGEventSink.h"

//CVPGameEventSink definition
CVPGameEventSink::CVPGameEventSink() :	m_refCount(0),
										m_GameInterfaceType(0)
{
}

CVPGameEventSink::~CVPGameEventSink()
{
}

//IUnknown method implementations
STDMETHODIMP_(ULONG) CVPGameEventSink::AddRef() 
{
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CVPGameEventSink::Release() 
{
    ULONG ret(--m_refCount);
    if(!ret) 
		delete this;
	
    return ret;
}

STDMETHODIMP CVPGameEventSink::QueryInterface(REFIID riid, void** ppv) 
{
    if(!ppv) 
		return E_POINTER;
  if(riid == IID_IUnknown || riid == IID_IVPGameEventSink)
		*ppv = static_cast<IVPGameEventSink*>(this);
	else if(riid == IID_IGameEventSinkProperties)
		*ppv = static_cast<IGameEventSinkProperties*>(this);
	else if(riid == IID_IConnectionPointContainer)
		*ppv = static_cast<IConnectionPointContainer*>(this);
	else if(riid == IID_IProvideClassInfo2)
		*ppv = static_cast<IProvideClassInfo2*>(this);
	else if(riid == IID_IPersistStreamInit || riid == IID_IPersistPropertyBag)
		return *ppv = NULL, E_NOINTERFACE;
  else if(riid == m_CurGameConPntIID | riid == IID_IDispatch)
	{
		if(m_GameInterfaceType == 0)
		{
			//set our type info to point to the proper interface
			m_pTypeInfo = NULL;
			CComPtr<ITypeLib> pTypeLib;
			HRESULT hr;
			hr = LoadRegTypeLib(LIBID_VPGameEmulatorLib, 1, 0, 0, &pTypeLib);
			CComPtr<ITypeInfo> pTypeInfo;
			hr = pTypeLib->GetTypeInfoOfGuid(IID_IVPGameEventSink, &m_pTypeInfo);
			*ppv = static_cast<IVPGameEventSink*>(this);
		}
		else if(m_GameInterfaceType == 1)
		{
			m_pTypeInfo = NULL;
			CComPtr<ITypeLib> pTypeLib;
			HRESULT hr;
			hr = LoadRegTypeLib(LIBID_VPGameEmulatorLib, 1, 0, 0, &pTypeLib);
			CComPtr<ITypeInfo> pTypeInfo;
			hr = pTypeLib->GetTypeInfoOfGuid(IID_IVPGameEventSink2, &m_pTypeInfo);
			*ppv = static_cast<IVPGameEventSink2*>(this);
		}
	}
	else
	{
		::MessageBox(NULL, "unknown", "", MB_OK);
		return *ppv = NULL, E_NOINTERFACE;
	}

	
	((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

//IDispatch method implementations
STDMETHODIMP CVPGameEventSink::GetIDsOfNames(REFIID riid, OLECHAR** rgszNames, UINT cNames,
    LCID lcid, DISPID* rgDispId) 
{
	::MessageBox(NULL, "GetIdsOfNames", "", MB_OK);
    if(lcid == 0 || lcid == 9 || lcid == 0x409)
        return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);
    return DISP_E_UNKNOWNLCID;
}

STDMETHODIMP CVPGameEventSink::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
{
	::MessageBox(NULL, "GetTypeInfo", "", MB_OK);
    /*if(iTInfo) 
		return TYPE_E_ELEMENTNOTFOUND;
    if(!ppTInfo) 
		return E_POINTER;
    if(lcid == 0 || lcid == 9 || lcid == 0x409)
        return m_pTypeInfo.CopyTo(ppTInfo), S_OK;*/

    return *ppTInfo = NULL, DISP_E_UNKNOWNLCID;
}

STDMETHODIMP CVPGameEventSink::GetTypeInfoCount(UINT* pctinfo) 
{
	::MessageBox(NULL, "GetTyepInfoCount", "", MB_OK);
    if(!pctinfo) return E_POINTER;
    return *pctinfo = 1, S_OK;
}

STDMETHODIMP CVPGameEventSink::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
    DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgError) 
{
		void *pvThis;
		
		if(m_GameInterfaceType == 0)
			pvThis = static_cast<IVPGameEventSink*>(this);
		else if(m_GameInterfaceType == 1)
			pvThis = static_cast<IVPGameEventSink2*>(this);
		
    return m_pTypeInfo->Invoke(pvThis, dispIdMember, wFlags, pDispParams, NULL,
        NULL, NULL);
}

//Implement all our nested classes, methods for
//IConnectionPointContainer/IConnectionPoint for our outgoing interface (Events)

//IUnknown implementation
STDMETHODIMP CVPGameEventSink::XCPVPGEmulatorEvents::QueryInterface(
		REFIID riid, void** ppv)
{
	if(riid == IID_IUnknown || riid == IID_IConnectionPoint)
		*ppv = static_cast<IConnectionPoint*>(this);
	else
		return *ppv = NULL, E_NOINTERFACE;
	
	((IUnknown*)*ppv)->AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) CVPGameEventSink::XCPVPGEmulatorEvents::AddRef(void)
{
	return This()->AddRef();
}

STDMETHODIMP_(ULONG) CVPGameEventSink::XCPVPGEmulatorEvents::Release(void)
{
	return This()->Release();
}

//IConnectionPoint implementation
STDMETHODIMP CVPGameEventSink::XCPVPGEmulatorEvents::Advise(IUnknown *pUnkSink, DWORD *pdwCookie)
{
	*pdwCookie = 0;

	//QueryInterface for correct callback type
	HRESULT hr = pUnkSink->QueryInterface(IID_IDispatch,
					(void**)&(This()->m_pVPGEmulatorEvents));
	if(hr == E_NOINTERFACE)
		hr = CONNECT_E_NOCONNECTION;
	if(SUCCEEDED(hr)) // make up a meaningful cookie
		*pdwCookie = DWORD(This()->m_pVPGEmulatorEvents);
	
	return hr;
}

STDMETHODIMP CVPGameEventSink::XCPVPGEmulatorEvents::Unadvise(DWORD cookie)
{
	//ensure that the cookie corresponds to a valid connection
	if(DWORD(This()->m_pVPGEmulatorEvents) != cookie)
		return CONNECT_E_NOCONNECTION;
	//release the connection
	This()->m_pVPGEmulatorEvents->Release();
	This()->m_pVPGEmulatorEvents = 0;
	return S_OK;
}

STDMETHODIMP CVPGameEventSink::XCPVPGEmulatorEvents::GetConnectionInterface(IID *piid)
{
	//Assert(piid);
	//return IID of the interface managed by this subobject
	*piid = DIID__IVPGEmulatorEvents;
	return S_OK;
}

STDMETHODIMP CVPGameEventSink::XCPVPGEmulatorEvents::GetConnectionPointContainer(IConnectionPointContainer **ppcpc)
{
	//Assert(ppcpc);
	(*ppcpc = This())->AddRef(); //return containing object
	return S_OK;
}

STDMETHODIMP 
	CVPGameEventSink::XCPVPGEmulatorEvents::EnumConnections(
													IEnumConnections **ppEnum)
{
	return E_NOTIMPL;
}

inline CVPGameEventSink* CVPGameEventSink::XCPVPGEmulatorEvents::This(void)
{
	return (CVPGameEventSink*)((char*)this - offsetof(CVPGameEventSink, 
														m_xcpVPGEmulatorEvents));
}

//IConnectionPointContainer implementation
STDMETHODIMP CVPGameEventSink::FindConnectionPoint(REFIID riid, IConnectionPoint **ppcp)
{
	if(riid == DIID__IVPGEmulatorEvents)
		*ppcp = &m_xcpVPGEmulatorEvents;
	else
		return *ppcp = NULL, CONNECT_E_NOCONNECTION;

	(*ppcp)->AddRef();
	return S_OK;
}

STDMETHODIMP CVPGameEventSink::EnumConnectionPoints(IEnumConnectionPoints **ppEnum)
{
	return E_NOTIMPL;
}

//IProvideClassInfo2 implementation
STDMETHODIMP CVPGameEventSink::GetClassInfo(ITypeInfo **ppti)
{
	//Assert(ppti != 0);
	ITypeLib *ptl = 0;
	HRESULT hr = LoadRegTypeLib(LIBID_VPGameEmulatorLib, 1, 0, 0, &ptl);
	if(SUCCEEDED(hr))
	{
		hr = ptl->GetTypeInfoOfGuid(CLSID_VPGameEventSink, ppti);
		ptl->Release();
	}
	return hr;
}
	
STDMETHODIMP CVPGameEventSink::GetGUID(DWORD dwGuidKind, GUID *pGUID)
{
	if(dwGuidKind != GUIDKIND_DEFAULT_SOURCE_DISP_IID || !pGUID)
		return E_INVALIDARG;
	//IVPGEmulatorEvents must be defined as a dispinterface
	*pGUID = DIID__IVPGEmulatorEvents;
	return S_OK;
}

//implement our methods for IVPGameEventSink
STDMETHODIMP_(void) CVPGameEventSink::LeaveGroup(void)
{
	HRESULT hr;
	DISPPARAMS disp = {NULL, NULL, 0, 0};

	hr = m_pVPGEmulatorEvents->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD,
									&disp, NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::GetPresenceInfo(	long Id, 
														BSTR* Nickname, 
														BSTR* Fullname, 
														BSTR* Location, 
														BSTR* Email)
{
	HRESULT hr;
	CComVariant avarParams[5];
	avarParams[4] = Id;
	avarParams[3] = Nickname;
	avarParams[2] = Fullname;
	avarParams[1] = Location;
	avarParams[0] = Email;
	DISPPARAMS params = { avarParams, NULL, 5, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	2, IID_NULL, LOCALE_USER_DEFAULT, 
										DISPATCH_METHOD, &params, 
										NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::GetParentWnd(long* hWnd)
{
	HRESULT hr;
	CComVariant avarParams[1];
	avarParams[0] = hWnd;
	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	3, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params, 
								NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::SetGameWnd(long hWnd)
{
	HRESULT hr;
	CComVariant avarParams[1];
	avarParams[0] = hWnd;
	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	4, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params,
								NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::DupAvatar(long ParentWnd, 
												long Seat)
{
	HRESULT hr;
	CComVariant avarParams[2];
	avarParams[1] = ParentWnd;
	avarParams[0] = Seat;
	DISPPARAMS params = { avarParams, NULL, 2, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(5, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params, 
								NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::SetAvatarPos(	long Seat, 
													short Left, 
													short Top, 
													short Width, 
													short Height)
{
	HRESULT hr;
	CComVariant avarParams[5];
	avarParams[4] = Seat;
	avarParams[3] = Left;
	avarParams[2] = Top;
	avarParams[1] = Width;
	avarParams[0] = Height;
	DISPPARAMS params = { avarParams, NULL, 5, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	6, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params, 
								NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::EnumMembers(	long Id, 
													short MaxLevel)
{
	HRESULT hr;
	CComVariant avarParams[2];
	avarParams[1] = Id;
	avarParams[0] = MaxLevel;
	DISPPARAMS params = { avarParams, NULL, 2, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	7, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params, 
								NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::Send( long Id, 
											short SendType, 
											BSTR Message, 
											BSTR* Data)
{
	HRESULT hr;
	CComVariant avarParams[4];
	avarParams[3] = Id;
	avarParams[2] = SendType;
	avarParams[1] = Message;
	avarParams[0].SetByRef(Data);
	DISPPARAMS params = { avarParams, NULL, 4, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	8, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, 
								&params, NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::QueryService(	long* Id, 
													short* Type)
{
	HRESULT hr;
	CComVariant avarParams[2];
	avarParams[1] = Id;
	avarParams[0] = Type;
	DISPPARAMS params = { avarParams, NULL, 2, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	9, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params, 
								NULL, NULL, NULL);
}

STDMETHODIMP_(void) CVPGameEventSink::SendToService(long ServiceId, 
													long SrvSendType, 
													BSTR Message, 
													BSTR* Data, 
													long ReqId)
{
	HRESULT hr;
	CComVariant avarParams[5];
	avarParams[4] = ServiceId;
	avarParams[3] = SrvSendType;
	avarParams[2] = Message;
	avarParams[1].SetByRef(Data);
	avarParams[0] = ReqId;
	DISPPARAMS params = { avarParams, NULL, 5, 0 };
	hr = m_pVPGEmulatorEvents->Invoke(	10, IID_NULL, LOCALE_USER_DEFAULT, 
								DISPATCH_METHOD, &params, 
								NULL, NULL, NULL);
}                          

//IGameEventSinkProperties Definition
STDMETHODIMP CVPGameEventSink::SetCurGmConPntIID(BSTR CurGameConPntIID)
{
	USES_CONVERSION;
	_bstr_t conPntIID = CurGameConPntIID;
	char * tconPntIID = (LPTSTR)conPntIID;
	LPOLESTR oconPntIID = T2OLE((LPCTSTR)tconPntIID);
	CLSIDFromString(oconPntIID, &m_CurGameConPntIID);
	return S_OK;
}

STDMETHODIMP CVPGameEventSink::SetGmInterfaceType(SHORT GameInterfaceType)
{
	m_GameInterfaceType = GameInterfaceType;
	return S_OK;
}

//*********** now we'll implement our class factory ******************//

CVPGameEventSinkFactory::CVPGameEventSinkFactory() : m_refCount(0)
{
}

//IUnknow implementation
STDMETHODIMP_(ULONG) CVPGameEventSinkFactory::AddRef() 
{
    //++globalCount;
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CVPGameEventSinkFactory::Release() 
{
    //--globalCount;
    ULONG ret(--m_refCount);
    if(!ret) delete this;
    return ret;
}

STDMETHODIMP CVPGameEventSinkFactory::QueryInterface(REFIID riid, void** ppv) 
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
STDMETHODIMP CVPGameEventSinkFactory::CreateInstance(IUnknown* pUnk, REFIID riid, void** ppv) 
{
    if(pUnk) 
		return CLASS_E_NOAGGREGATION;

    CVPGameEventSink* vpgEventSink = new CVPGameEventSink;
	if(vpgEventSink == NULL)
		return E_OUTOFMEMORY;

    HRESULT hr = vpgEventSink->QueryInterface(riid, ppv);
    
	if(FAILED(hr)) 
		delete vpgEventSink;
	
    return hr;
}

STDMETHODIMP CVPGameEventSinkFactory::LockServer(BOOL lock) 
{ 
	return S_OK; 
}
