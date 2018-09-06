#include "stdafx.h"
#include "VPGameEventSink.h"

class CVPGame : IGame
{
public:
	ULONG m_refCount;
    CComPtr<ITypeInfo> m_pTypeInfo;

	CVPGame();
	~CVPGame();

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

	//IGame
	STDMETHOD(CreateGame)(BSTR GameCLSID);
	STDMETHOD(get_GetClassID)(BSTR* pVal);
	STDMETHOD(GetGameDetails)(	BSTR* Name, BSTR* Info, BSTR* SeatList, 
								BSTR* CanChangeSeat, BSTR* CanSelectSeat, 
								SHORT* MinParticipants, SHORT* MaxParticipants, 
								BSTR* Avatar);
	STDMETHOD(StartGame)(	LONG Id, BSTR Name, LONG GroupId, BSTR GroupName, 
							LONG LeaderId, SHORT Capacity, LONG Seat);
	STDMETHOD(SetEventSink)(IUnknown** pUnkEventSink);
	STDMETHOD(EndGame)(void);
	STDMETHOD(JoinGroup)(	LONG Id, BSTR Name, LONG X, LONG Y, LONG GroupId, 
							BSTR GroupName);
	STDMETHOD(Send)(LONG Id, BSTR Name, SHORT Type, LONG ToId, SHORT SendType, 
					BSTR Message, BSTR* Data);
	STDMETHOD(SendFromService)(	LONG Id, SHORT Type, LONG SrvSendType, BSTR Message, 
								BSTR* Data, LONG ReqId);
	STDMETHOD(EnumMembers)(	LONG Current, SHORT Level, LONG Id, BSTR Name, SHORT Type, 
							LONG X, LONG Y);
	STDMETHOD(LeaveGroup)(LONG Id, BSTR Name, LONG GroupId, BSTR GroupName);
	STDMETHOD(DestroyGame)(void);
	STDMETHOD(AuthenticateClient)(VARIANT key);

	enum GameState
	{
		Destroyed,
		VPGDispInstantiated,
		GameInstantiated
	};

private:
	CComBSTR m_ClassID;
	CComPtr<IUnknown> m_pUnkGameEventSink;
	CComPtr<IDispatch> m_pVPGDisp;
	CComPtr<IConnectionPoint> m_pVPGConPnt;
	GameState gmState;
	DWORD m_cookie;
	bool m_IsAuthenticated;

	bool InstantiateGame(LPTSTR clsid);
	void CheckErr(HRESULT hr);
	void CleanUp();
};

//CVPGame IClassFactory
class CVPGameFactory : public IClassFactory
{
	ULONG m_refCount;
public:
	CVPGameFactory();

	//IUnknow implementation
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
    STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	//IClassFactory
	STDMETHOD(CreateInstance)(IUnknown* pUnk, REFIID riid, void** ppv);
    STDMETHOD(LockServer)(BOOL lock);
};	