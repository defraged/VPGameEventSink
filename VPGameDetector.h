#include "stdafx.h"
#include "VPGameEventSink.h"

class CVPGameDetector :	IGameDetector
{
public:
	ULONG m_refCount;
    CComPtr<ITypeInfo> m_pTypeInfo;

	CVPGameDetector();
	~CVPGameDetector();

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

	//IGameDetector
	STDMETHOD(get_GameNames)(VARIANT* pVal);
	STDMETHOD(CLSIDFromGameName)(BSTR GameName, BSTR* GameCLSID);
};

//CVPGameDetector IClassFactory
class CVPGameDetectorFactory : public IClassFactory
{
	ULONG m_refCount;
public:
	CVPGameDetectorFactory();

	//IUnknow implementation
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
    STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	//IClassFactory
	STDMETHOD(CreateInstance)(IUnknown* pUnk, REFIID riid, void** ppv);
    STDMETHOD(LockServer)(BOOL lock);
};	