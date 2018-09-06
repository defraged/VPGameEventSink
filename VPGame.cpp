#include "stdafx.h"
#include "VPGame.h"
#include "RegWorkerFunc.h"
#include <cmath>

//***************** CVPGameEventSink definition ****************//

CVPGame::CVPGame() :	m_refCount(0),
						gmState(GameState::Destroyed),
						m_cookie(NULL),
						m_IsAuthenticated(false)
{
    CComPtr<ITypeLib> pTypeLib;
    HRESULT hr;
    hr = LoadRegTypeLib(LIBID_VPGameEmulatorLib, 1, 0, 0, &pTypeLib);
    CComPtr<ITypeInfo> pTypeInfo;
    hr = pTypeLib->GetTypeInfoOfGuid(IID_IGame, &m_pTypeInfo);
	CoInitialize(NULL);
}

CVPGame::~CVPGame()
{
	CleanUp();
	CoUninitialize();
}

//IUnknown method implementations
STDMETHODIMP_(ULONG) CVPGame::AddRef() 
{
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CVPGame::Release() 
{
    ULONG ret(--m_refCount);
    if(!ret) 
		delete this;
	
    return ret;
}

STDMETHODIMP CVPGame::QueryInterface(REFIID riid, void** ppv) 
{
    if(!ppv) 
		return E_POINTER;
    if(riid == IID_IUnknown || riid == IID_IGame)
		*ppv = static_cast<IGame*>(this);
    else if(riid == IID_IDispatch)
		*ppv = static_cast<IDispatch*>(this);
    else
		return *ppv = NULL, E_NOINTERFACE;
		
	((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

//IDispatch method implementations
STDMETHODIMP CVPGame::GetIDsOfNames(REFIID riid, OLECHAR** rgszNames, UINT cNames,
    LCID lcid, DISPID* rgDispId) 
{
    if(lcid == 0 || lcid == 9 || lcid == 0x409)
        return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);
    return DISP_E_UNKNOWNLCID;
}

STDMETHODIMP CVPGame::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
{
    if(iTInfo) 
		return TYPE_E_ELEMENTNOTFOUND;
    if(!ppTInfo) 
		return E_POINTER;
    if(lcid == 0 || lcid == 9 || lcid == 0x409)
        return m_pTypeInfo.CopyTo(ppTInfo), S_OK;

    return *ppTInfo = NULL, DISP_E_UNKNOWNLCID;
}

STDMETHODIMP CVPGame::GetTypeInfoCount(UINT* pctinfo) 
{
    if(!pctinfo) return E_POINTER;
    return *pctinfo = 1, S_OK;
}

STDMETHODIMP CVPGame::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
    DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgError) 
{
    if(lcid == 0 || lcid == 9 || lcid == 0x409) {
		void *pvThis = static_cast<IGame*>(this);
        return m_pTypeInfo->Invoke(pvThis, dispIdMember, wFlags, pDispParams, NULL,
        NULL, NULL);
    }
    return DISP_E_UNKNOWNLCID;
}

//Define IGame interface
STDMETHODIMP CVPGame::SetEventSink(IUnknown** pUnkEventSink)
{	
	m_pUnkGameEventSink = (IUnknown FAR*)*pUnkEventSink;
	return S_OK;
}

STDMETHODIMP CVPGame::AuthenticateClient(VARIANT key)
{
	if((key.vt & VT_ARRAY) == 0)	//make sure its an array
		return E_INVALIDARG;

	if((key.vt & VT_UI1) == 0)		//make sure its a byte array
		return E_INVALIDARG;

	SYSTEMTIME sysTime;
	SYSTEMTIME encSysTime;
	size_t ushortlen = sizeof(WORD);

	GetSystemTime(&sysTime);

	sysTime.wDayOfWeek += 1;
	sysTime.wHour += 1;
	sysTime.wMinute += 1;
	sysTime.wSecond += 1;
	sysTime.wMilliseconds += 1;

	SAFEARRAY* psa = key.parray;
	BYTE* byteArray;
	SafeArrayAccessData(psa, reinterpret_cast<void**>(&byteArray));
	
	//verify the encrypted SYSTEMTIME struct
	CopyMemory((void*)&encSysTime.wSecond, byteArray, ushortlen);
	encSysTime.wSecond = (WORD)sqrt((float)(encSysTime.wSecond - 77));
	if(encSysTime.wSecond != sysTime.wSecond)
		return SafeArrayUnaccessData(psa), E_FAIL;

	CopyMemory((void*)&encSysTime.wYear, byteArray+2, ushortlen);
	encSysTime.wYear = (encSysTime.wYear - 7 - sysTime.wMinute) / (sysTime.wDayOfWeek);
	if(encSysTime.wYear != sysTime.wYear)
		return SafeArrayUnaccessData(psa), E_FAIL; 

	CopyMemory((void*)&encSysTime.wMonth, byteArray+4, ushortlen);
	encSysTime.wMonth = (encSysTime.wMonth - 5 - sysTime.wSecond) / sysTime.wMinute;
	if(encSysTime.wMonth != sysTime.wMonth)
		return SafeArrayUnaccessData(psa), E_FAIL;
		
	CopyMemory((void*)&encSysTime.wDayOfWeek, byteArray+6, ushortlen);
	encSysTime.wDayOfWeek = (encSysTime.wDayOfWeek + 2 - (sysTime.wSecond * sysTime.wMinute)) / sysTime.wYear;
	if(encSysTime.wDayOfWeek != sysTime.wDayOfWeek)
		return SafeArrayUnaccessData(psa), E_FAIL; 

	CopyMemory((void*)&encSysTime.wDay, byteArray+8, ushortlen);
	encSysTime.wDay = (encSysTime.wDay + 8) - (sysTime.wMonth * sysTime.wSecond);
	if(encSysTime.wDay != sysTime.wDay)
		return SafeArrayUnaccessData(psa), E_FAIL;

	CopyMemory((void*)&encSysTime.wHour, byteArray+10, ushortlen);
	encSysTime.wHour = (encSysTime.wHour - 15) / (sysTime.wSecond + sysTime.wMinute);
	if(encSysTime.wHour != sysTime.wHour)
		return SafeArrayUnaccessData(psa), E_FAIL; 
		
	CopyMemory((void*)&encSysTime.wMinute, byteArray+12, ushortlen);
	encSysTime.wMinute = (encSysTime.wMinute / (sysTime.wSecond + 9)) / 2;
	if(encSysTime.wMinute != sysTime.wMinute)
		return SafeArrayUnaccessData(psa), E_FAIL;

	//client passed the test =]
	m_IsAuthenticated = true;
	SafeArrayUnaccessData(psa);
	
	return S_OK;
}

STDMETHODIMP CVPGame::CreateGame(BSTR GameCLSID)
{
	if(m_IsAuthenticated == false)
		return E_FAIL;

	bool success = false;
	m_ClassID = GameCLSID;
	
	_bstr_t gmCLSID = GameCLSID;
	char * tgmCLSID = (LPTSTR)gmCLSID;

	if(FindGameCLSID(tgmCLSID) == true)
		success = InstantiateGame((LPTSTR)tgmCLSID);

	if(success == true)
		return S_OK;
	else
		return E_FAIL;

}

STDMETHODIMP CVPGame::DestroyGame(void)
{
	return S_OK;
}

STDMETHODIMP CVPGame::get_GetClassID(BSTR* pVal) //<< this is a Get property
{
	if(gmState == GameState::GameInstantiated && m_ClassID.Length() > 0)
		*pVal = m_ClassID.m_str;
	return S_OK;
}

//******************** Member Functions *********************//

bool CVPGame::InstantiateGame(LPTSTR clsid)
{
	CComPtr<IUnknown> m_pVPGUnk;
	CComPtr<IConnectionPointContainer> m_pVPGConPntCntr;
	CComPtr<IProvideClassInfo2> m_pVPGClassInfo;

	USES_CONVERSION;	
	HRESULT hr;			//convert LPTSTR to CLSID
	LPOLESTR oleCLSID = T2OLE(clsid);
	CLSID vpgCLSID;
	
	hr = CLSIDFromString(oleCLSID, &vpgCLSID);

	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error converting clsid to string", "", MB_OK);
		CheckErr(hr);
		return false;
	}
	
	//create instance of the iunknown interface of the selected vp game.
	hr = CoCreateInstance(	vpgCLSID,
							NULL,
							CLSCTX_INPROC,
							IID_IUnknown,
							(void**)&m_pVPGUnk	);
	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error instantiating iunknown", "", MB_OK);
		CheckErr(hr);
		return false;
	}

	//now create instance of the IDispatch interface
	hr = m_pVPGUnk->QueryInterface(IID_IDispatch, 
									(void**)&m_pVPGDisp);
	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error instantiating IDispatch", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}
	
	gmState = GameState::VPGDispInstantiated;

	//now for the instance of the IConnectionPointContainer interface
	hr = m_pVPGUnk->QueryInterface(IID_IConnectionPointContainer,
									(void**)&m_pVPGConPntCntr);
	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "Error instantiating IConnectionPointContainer", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}

	hr = m_pVPGUnk->QueryInterface(IID_IProvideClassInfo2, (void**)&m_pVPGClassInfo);

	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error instantiating IProvideClassInfo2", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}

	IID IID_GameEvents;
	hr = m_pVPGClassInfo->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID, &IID_GameEvents);

	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error geting default source iid", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}

	hr = m_pVPGConPntCntr->FindConnectionPoint(IID_GameEvents, &m_pVPGConPnt);

	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error finding connection point", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}
	
	//grab our properties interface of our event sink so we can set some info.
	CComPtr<IGameEventSinkProperties> gmEventSinkProps;
	hr = m_pUnkGameEventSink->QueryInterface(IID_IGameEventSinkProperties, 
												(void**)&gmEventSinkProps);

	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error grabbing our IGameEventSinkProperties", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}
	
	//we are passing in our connection point IID as BSTR so we need to convert it
	CComBSTR ConPntIIDStr;
	LPOLESTR oleConPntIIDStr;
	StringFromCLSID(IID_GameEvents, &oleConPntIIDStr);
	ConPntIIDStr = oleConPntIIDStr;
	gmEventSinkProps->SetCurGmConPntIID(ConPntIIDStr.m_str);

	//now we need to do a check to see what kind of interface we have.
	DISPID methodID;
	LPOLESTR methodName = L"GetClassID";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&methodName,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&methodID);

	if(methodID == 2)
		gmEventSinkProps->SetGmInterfaceType(0);
	else if(methodID == 3)
		gmEventSinkProps->SetGmInterfaceType(1);

	//now connect our event sink interface
	hr = m_pVPGConPnt->Advise(m_pUnkGameEventSink, &m_cookie);
	 
	CheckErr(hr);

	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL, "error connecting our event sink interface", "", MB_OK);
		CheckErr(hr);
		CleanUp();
		return false;
	}
	
	gmState = GameState::GameInstantiated;

	return true;
}

// this function will clean the game up accordingly based on the games specified state
void CVPGame::CleanUp()
{
	switch(gmState)
	{
		case GameState::Destroyed: //nothing to do
		break;

		case GameState::GameInstantiated:
			m_pVPGConPnt->Unadvise(m_cookie);
			m_pVPGConPnt.Release();
			m_pUnkGameEventSink.Release();
			m_cookie = NULL;

		case GameState::VPGDispInstantiated:
			m_pVPGDisp.Release();
		break;
	}

	gmState = GameState::Destroyed;
}

//this function is primarily to help me debug.
void CVPGame::CheckErr(HRESULT hr)
{
	switch(hr)
	{
		case E_POINTER:
			::MessageBox(NULL, "Err: E_POINTER", "ERROR!", MB_OK);
		break;

		case CONNECT_E_NOCONNECTION:
			::MessageBox(NULL, "Err: CONNECT_E_NOCONNECTION", "ERROR!", MB_OK);
		break;
		
		case E_NOINTERFACE:
			::MessageBox(NULL, "Err: E_NOINTERFACE", "ERROR!", MB_OK);
		break;

		case E_UNEXPECTED:
			::MessageBox(NULL, "Err: E_UNEXPECTED", "ERROR!", MB_OK);
		break;

		//default:
			//::MessageBox(NULL, "Err: ??????????", "", MB_OK);
		//break;
	}
}

//******************** VP Game Methods **********************//

STDMETHODIMP CVPGame::GetGameDetails(BSTR* Name, BSTR* Info, BSTR* SeatList, 
								   BSTR* CanChangeSeat, BSTR* CanSelectSeat, 
								   SHORT* MinParticipants, SHORT* MaxParticipants, 
								   BSTR* Avatar)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"GetGameDetails";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[8] ;
		pvars[7].SetByRef(Name);
		pvars[6].SetByRef(Info);
		pvars[5].SetByRef(SeatList);
		pvars[4].SetByRef(CanChangeSeat);
		pvars[3].SetByRef(CanSelectSeat);
		pvars[2].SetByRef(MinParticipants);
		pvars[1].SetByRef(MaxParticipants);
		pvars[0].SetByRef(Avatar);

		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 8;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}

	return hr;
}

STDMETHODIMP CVPGame::StartGame(LONG Id, BSTR Name, LONG GroupId, BSTR GroupName, 
							  LONG LeaderId, SHORT Capacity, LONG Seat)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"StartGame";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[7];
		pvars[6] = Id;
		pvars[5] = Name;
		pvars[4] = GroupId;
		pvars[3] = GroupName;
		pvars[2] = LeaderId;
		pvars[1] = Capacity;
		pvars[0] = Seat;

		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 7;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);	
	}

	return hr;
}

STDMETHODIMP CVPGame::EndGame(void)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"EndGame";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);

	if(SUCCEEDED(hr))
	{
		DISPPARAMS disp = {NULL, NULL, 0 , 0};
		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}

	return hr;
}

STDMETHODIMP CVPGame::JoinGroup(LONG Id, BSTR Name, LONG X, LONG Y, LONG GroupId, 
							  BSTR GroupName)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"JoinGroup";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[6];
		pvars[5] = Id;
		pvars[4] = Name;
		pvars[3] = X;
		pvars[2] = Y;
		pvars[1] = GroupId;
		pvars[0] = GroupName;
		
		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 6;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}

	return hr;
}

STDMETHODIMP CVPGame::Send(LONG Id, BSTR Name, SHORT Type, LONG ToId, SHORT SendType, 
						 BSTR Message, BSTR* Data)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"Send";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[7];
		pvars[6] = Id;
		pvars[5] = Name;
		pvars[4] = Type;
		pvars[3] = ToId;
		pvars[2] = SendType;
		pvars[1] = Message;
		pvars[0].SetByRef(Data);

		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 7;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;
		
		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}
	
	return hr;
}

STDMETHODIMP CVPGame::SendFromService(LONG Id, SHORT Type, LONG SrvSendType, 
									BSTR Message, BSTR* Data, LONG ReqId)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"SendFromService";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[6];
		pvars[5] = Id;
		pvars[4] = Type;
		pvars[3] = SrvSendType;
		pvars[2] = Message;
		pvars[1].SetByRef(Data);
		pvars[0] = ReqId;
		
		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 6;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}
	
	return hr;
}

STDMETHODIMP CVPGame::EnumMembers(LONG Current, SHORT Level, LONG Id, BSTR Name, 
								SHORT Type, LONG X, LONG Y)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"EnumMembers";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[7];
		pvars[6] = Current;
		pvars[5] = Level;
		pvars[4] = Id;
		pvars[3] = Name;
		pvars[2] = Type;
		pvars[1] = X;
		pvars[0] = Y;

		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 7;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}

	return hr;
}

STDMETHODIMP CVPGame::LeaveGroup(LONG Id, BSTR Name, LONG GroupId, BSTR GroupName)
{
	if(gmState == GameState::Destroyed)
		return E_FAIL;

	HRESULT hr;
	DISPID pDispID;
	LPOLESTR pNames = L"LeaveGroup";

	hr = m_pVPGDisp->GetIDsOfNames(	IID_NULL,
									&pNames,
									1,
									LOCALE_SYSTEM_DEFAULT,
									&pDispID);
	if(SUCCEEDED(hr))
	{
		CComVariant pvars[4];
		pvars[3] = Id;
		pvars[2] = Name;
		pvars[1] = GroupId;
		pvars[0] = GroupName;
		
		DISPPARAMS disp;
		disp.rgvarg = pvars;
		disp.cArgs = 4;
		disp.rgdispidNamedArgs = NULL;
		disp.cNamedArgs = 0;

		EXCEPINFO excepInfo;

		hr = m_pVPGDisp->Invoke(pDispID,
								IID_NULL,
								LOCALE_USER_DEFAULT,
								DISPATCH_METHOD,
								&disp,
								NULL, &excepInfo, NULL);
	}

	return hr;
}

//*********** Define our ClassFactory for CVPGame *****************//

CVPGameFactory::CVPGameFactory() : m_refCount(0)
{
}

//IUnknow implementation
STDMETHODIMP_(ULONG) CVPGameFactory::AddRef() 
{
    //++globalCount;
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) CVPGameFactory::Release() 
{
    //--globalCount;
    ULONG ret(--m_refCount);
    if(!ret) delete this;
    return ret;
}

STDMETHODIMP CVPGameFactory::QueryInterface(REFIID riid, void** ppv) 
{
    if(!ppv) 
		return E_POINTER;
    if(riid == IID_IUnknown) 
		*ppv = static_cast<IUnknown*>(this);
    else if(riid == IID_IClassFactory) 
		*ppv = static_cast<IClassFactory*>(this);
    else 
		return *ppv = NULL, E_NOINTERFACE;

	((IUnknown*)*ppv)->AddRef();

    return S_OK;
}

//IClassFactory Implementation
STDMETHODIMP CVPGameFactory::CreateInstance(IUnknown* pUnk, REFIID riid, void** ppv) 
{
    if(pUnk) 
		return CLASS_E_NOAGGREGATION;

    CVPGame* vpg = new CVPGame;
	if(vpg == NULL)
		return E_OUTOFMEMORY;

    HRESULT hr = vpg->QueryInterface(riid, ppv);
    
	if(FAILED(hr)) 
		delete vpg;
	
    return hr;
}

STDMETHODIMP CVPGameFactory::LockServer(BOOL lock) 
{ 
	return S_OK; 
}
