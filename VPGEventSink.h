#include "stdafx.h"
#include "VPGameEventSink.h"

//#include <iostream>
//#include <fstream>

//using std::ofstream;
//using std::ios;

//implement our class object
class CVPGameEventSink :	public IVPGameEventSink,
							public IVPGameEventSink2,
							public IGameEventSinkProperties,
							public IConnectionPointContainer,
							public IProvideClassInfo2
{
public:
	//Constructor/Deconstructor
	CVPGameEventSink();
	~CVPGameEventSink();

    ULONG m_refCount;
    CComPtr<ITypeInfo> m_pTypeInfo;
	IDispatch* m_pVPGEmulatorEvents;

	//Nested class for IConnectionPoint
	class XCPVPGEmulatorEvents : public IConnectionPoint
	{
	public:
		//CVPGameEvents;
		inline CVPGameEventSink* This(void);
	
		//IUnknown implementation
		STDMETHOD(QueryInterface)(REFIID riid, void** ppv);
		STDMETHOD_(ULONG, AddRef)(void);
		STDMETHOD_(ULONG, Release)(void);

		//IConnectionPoint
		STDMETHOD(Advise)(IUnknown *pUnkSink, DWORD *pdwCookie);
		STDMETHOD(Unadvise)(DWORD cookie);
		STDMETHOD(GetConnectionInterface)(IID *piid);
		STDMETHOD(GetConnectionPointContainer)(IConnectionPointContainer **ppcpc);
		STDMETHOD(EnumConnections)(IEnumConnections **ppEnum);

	} m_xcpVPGEmulatorEvents;
	
	//IUnknown
	STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();
    STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	//IDispatch
	STDMETHOD(GetIDsOfNames)(REFIID riid, OLECHAR** rgszNames, UINT cNames,
        LCID lcid, DISPID* rgDispId);
    STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);
    STDMETHOD(GetTypeInfoCount)(UINT* pctinfo);
    STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
        DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgError);

	//IConnectionPointContainer implementation
	STDMETHOD(FindConnectionPoint)(REFIID riid, IConnectionPoint **ppcp);
	STDMETHOD(EnumConnectionPoints)(IEnumConnectionPoints **ppEnum);

	//IProvideClassInfo2
	STDMETHOD(GetClassInfo)(ITypeInfo **ppti);
	STDMETHOD(GetGUID)(DWORD dwGuidKind, GUID *pGUID);

	//IVPGameEventSink, IVPGameEventSink2
	STDMETHOD_(void, LeaveGroup)(void);

	STDMETHOD_(void, GetPresenceInfo)(	long Id, 
										BSTR* Nickname, 
										BSTR* Fullname, 
										BSTR* Location, 
										BSTR* Email);

	STDMETHOD_(void, GetParentWnd)(long* hWnd);

	STDMETHOD_(void, SetGameWnd)(long hWnd);

	STDMETHOD_(void, DupAvatar)(long ParentWnd, 
								long Seat);

	STDMETHOD_(void, SetAvatarPos)(	long Seat, 
									short Left, 
									short Top, 
									short Width, 
									short Height);

	STDMETHOD_(void, EnumMembers)(	long Id, 
									short MaxLevel);

	STDMETHOD_(void, Send)( long Id, 
							short SendType, 
							BSTR Message, 
							BSTR* Data);

	STDMETHOD_(void, QueryService)(	long* Id, 
									short* Type);

	STDMETHOD_(void, SendToService)(long ServiceId, 
									long SrvSendType, 
									BSTR Message, 
									BSTR* Data, 
									long ReqId);

	//IGameEventSinkProperties
	STDMETHOD(SetCurGmConPntIID)(BSTR CurGameConPntIID);
	STDMETHOD(SetGmInterfaceType)(SHORT GameInterfaceType);

private:
	IID m_CurGameConPntIID;
	SHORT m_GameInterfaceType;
};

//CVPGameEvents IClassFactory
class CVPGameEventSinkFactory : public IClassFactory
{
	ULONG m_refCount;
public:
	CVPGameEventSinkFactory();

	//IUnknow implementation
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
    STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	//IClassFactory
	STDMETHOD(CreateInstance)(IUnknown* pUnk, REFIID riid, void** ppv);
    STDMETHOD(LockServer)(BOOL lock);
};	