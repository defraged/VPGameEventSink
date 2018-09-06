

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 21:14:07 2038
 */
/* Compiler settings for VPGameEventSink.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __VPGameEventSink_h_h__
#define __VPGameEventSink_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGame_FWD_DEFINED__
#define __IGame_FWD_DEFINED__
typedef interface IGame IGame;

#endif 	/* __IGame_FWD_DEFINED__ */


#ifndef __IGameDetector_FWD_DEFINED__
#define __IGameDetector_FWD_DEFINED__
typedef interface IGameDetector IGameDetector;

#endif 	/* __IGameDetector_FWD_DEFINED__ */


#ifndef __IVPGameEventSink_FWD_DEFINED__
#define __IVPGameEventSink_FWD_DEFINED__
typedef interface IVPGameEventSink IVPGameEventSink;

#endif 	/* __IVPGameEventSink_FWD_DEFINED__ */


#ifndef __IVPGameEventSink2_FWD_DEFINED__
#define __IVPGameEventSink2_FWD_DEFINED__
typedef interface IVPGameEventSink2 IVPGameEventSink2;

#endif 	/* __IVPGameEventSink2_FWD_DEFINED__ */


#ifndef __IGameEventSinkProperties_FWD_DEFINED__
#define __IGameEventSinkProperties_FWD_DEFINED__
typedef interface IGameEventSinkProperties IGameEventSinkProperties;

#endif 	/* __IGameEventSinkProperties_FWD_DEFINED__ */


#ifndef ___IVPGEmulatorEvents_FWD_DEFINED__
#define ___IVPGEmulatorEvents_FWD_DEFINED__
typedef interface _IVPGEmulatorEvents _IVPGEmulatorEvents;

#endif 	/* ___IVPGEmulatorEvents_FWD_DEFINED__ */


#ifndef __VPGameEventSink_FWD_DEFINED__
#define __VPGameEventSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class VPGameEventSink VPGameEventSink;
#else
typedef struct VPGameEventSink VPGameEventSink;
#endif /* __cplusplus */

#endif 	/* __VPGameEventSink_FWD_DEFINED__ */


#ifndef __VPGameDetector_FWD_DEFINED__
#define __VPGameDetector_FWD_DEFINED__

#ifdef __cplusplus
typedef class VPGameDetector VPGameDetector;
#else
typedef struct VPGameDetector VPGameDetector;
#endif /* __cplusplus */

#endif 	/* __VPGameDetector_FWD_DEFINED__ */


#ifndef __VPGame_FWD_DEFINED__
#define __VPGame_FWD_DEFINED__

#ifdef __cplusplus
typedef class VPGame VPGame;
#else
typedef struct VPGame VPGame;
#endif /* __cplusplus */

#endif 	/* __VPGame_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IGame_INTERFACE_DEFINED__
#define __IGame_INTERFACE_DEFINED__

/* interface IGame */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A258D17-01DA-4378-A02B-71E2409CC227")
    IGame : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateGame( 
            /* [in] */ BSTR GameCLSID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetClassID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGameDetails( 
            /* [out] */ BSTR *Name,
            /* [out] */ BSTR *Info,
            /* [out] */ BSTR *SeatList,
            /* [out] */ BSTR *CanChangeSeat,
            /* [out] */ BSTR *CanSelectSeat,
            /* [out] */ SHORT *MinParticipants,
            /* [out] */ SHORT *MaxParticipants,
            /* [out] */ BSTR *Avatar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartGame( 
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ LONG GroupId,
            /* [in] */ BSTR GroupName,
            /* [in] */ LONG LeaderId,
            /* [in] */ SHORT Capacity,
            /* [in] */ LONG Seat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown **pUnkEventSink) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndGame( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE JoinGroup( 
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [in] */ LONG GroupId,
            /* [in] */ BSTR GroupName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ SHORT Type,
            /* [in] */ LONG ToId,
            /* [in] */ SHORT SendType,
            /* [in] */ BSTR Message,
            /* [out][in] */ BSTR *Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendFromService( 
            /* [in] */ LONG Id,
            /* [in] */ SHORT Type,
            /* [in] */ LONG SrvSendType,
            /* [in] */ BSTR Message,
            /* [out][in] */ BSTR *Data,
            /* [in] */ LONG ReqId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumMembers( 
            /* [in] */ LONG Current,
            /* [in] */ SHORT Level,
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ SHORT Type,
            /* [in] */ LONG X,
            /* [in] */ LONG Y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LeaveGroup( 
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ LONG GroupId,
            /* [in] */ BSTR GroupName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DestroyGame( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AuthenticateClient( 
            /* [in] */ VARIANT key) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGame * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGame * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGame * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGame * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGame * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGame * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGame * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateGame )( 
            IGame * This,
            /* [in] */ BSTR GameCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GetClassID )( 
            IGame * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGameDetails )( 
            IGame * This,
            /* [out] */ BSTR *Name,
            /* [out] */ BSTR *Info,
            /* [out] */ BSTR *SeatList,
            /* [out] */ BSTR *CanChangeSeat,
            /* [out] */ BSTR *CanSelectSeat,
            /* [out] */ SHORT *MinParticipants,
            /* [out] */ SHORT *MaxParticipants,
            /* [out] */ BSTR *Avatar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartGame )( 
            IGame * This,
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ LONG GroupId,
            /* [in] */ BSTR GroupName,
            /* [in] */ LONG LeaderId,
            /* [in] */ SHORT Capacity,
            /* [in] */ LONG Seat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            IGame * This,
            /* [in] */ IUnknown **pUnkEventSink);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndGame )( 
            IGame * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *JoinGroup )( 
            IGame * This,
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [in] */ LONG GroupId,
            /* [in] */ BSTR GroupName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            IGame * This,
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ SHORT Type,
            /* [in] */ LONG ToId,
            /* [in] */ SHORT SendType,
            /* [in] */ BSTR Message,
            /* [out][in] */ BSTR *Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendFromService )( 
            IGame * This,
            /* [in] */ LONG Id,
            /* [in] */ SHORT Type,
            /* [in] */ LONG SrvSendType,
            /* [in] */ BSTR Message,
            /* [out][in] */ BSTR *Data,
            /* [in] */ LONG ReqId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumMembers )( 
            IGame * This,
            /* [in] */ LONG Current,
            /* [in] */ SHORT Level,
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ SHORT Type,
            /* [in] */ LONG X,
            /* [in] */ LONG Y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LeaveGroup )( 
            IGame * This,
            /* [in] */ LONG Id,
            /* [in] */ BSTR Name,
            /* [in] */ LONG GroupId,
            /* [in] */ BSTR GroupName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DestroyGame )( 
            IGame * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AuthenticateClient )( 
            IGame * This,
            /* [in] */ VARIANT key);
        
        END_INTERFACE
    } IGameVtbl;

    interface IGame
    {
        CONST_VTBL struct IGameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGame_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGame_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGame_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGame_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGame_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGame_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGame_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGame_CreateGame(This,GameCLSID)	\
    ( (This)->lpVtbl -> CreateGame(This,GameCLSID) ) 

#define IGame_get_GetClassID(This,pVal)	\
    ( (This)->lpVtbl -> get_GetClassID(This,pVal) ) 

#define IGame_GetGameDetails(This,Name,Info,SeatList,CanChangeSeat,CanSelectSeat,MinParticipants,MaxParticipants,Avatar)	\
    ( (This)->lpVtbl -> GetGameDetails(This,Name,Info,SeatList,CanChangeSeat,CanSelectSeat,MinParticipants,MaxParticipants,Avatar) ) 

#define IGame_StartGame(This,Id,Name,GroupId,GroupName,LeaderId,Capacity,Seat)	\
    ( (This)->lpVtbl -> StartGame(This,Id,Name,GroupId,GroupName,LeaderId,Capacity,Seat) ) 

#define IGame_SetEventSink(This,pUnkEventSink)	\
    ( (This)->lpVtbl -> SetEventSink(This,pUnkEventSink) ) 

#define IGame_EndGame(This)	\
    ( (This)->lpVtbl -> EndGame(This) ) 

#define IGame_JoinGroup(This,Id,Name,X,Y,GroupId,GroupName)	\
    ( (This)->lpVtbl -> JoinGroup(This,Id,Name,X,Y,GroupId,GroupName) ) 

#define IGame_Send(This,Id,Name,Type,ToId,SendType,Message,Data)	\
    ( (This)->lpVtbl -> Send(This,Id,Name,Type,ToId,SendType,Message,Data) ) 

#define IGame_SendFromService(This,Id,Type,SrvSendType,Message,Data,ReqId)	\
    ( (This)->lpVtbl -> SendFromService(This,Id,Type,SrvSendType,Message,Data,ReqId) ) 

#define IGame_EnumMembers(This,Current,Level,Id,Name,Type,X,Y)	\
    ( (This)->lpVtbl -> EnumMembers(This,Current,Level,Id,Name,Type,X,Y) ) 

#define IGame_LeaveGroup(This,Id,Name,GroupId,GroupName)	\
    ( (This)->lpVtbl -> LeaveGroup(This,Id,Name,GroupId,GroupName) ) 

#define IGame_DestroyGame(This)	\
    ( (This)->lpVtbl -> DestroyGame(This) ) 

#define IGame_AuthenticateClient(This,key)	\
    ( (This)->lpVtbl -> AuthenticateClient(This,key) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGame_INTERFACE_DEFINED__ */


#ifndef __IGameDetector_INTERFACE_DEFINED__
#define __IGameDetector_INTERFACE_DEFINED__

/* interface IGameDetector */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGameDetector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("315A5253-0B46-493d-8856-C968FE8F7E44")
    IGameDetector : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GameNames( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CLSIDFromGameName( 
            /* [in] */ BSTR GameName,
            /* [out] */ BSTR *GameCLSID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGameDetectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGameDetector * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGameDetector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGameDetector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGameDetector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGameDetector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGameDetector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGameDetector * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GameNames )( 
            IGameDetector * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CLSIDFromGameName )( 
            IGameDetector * This,
            /* [in] */ BSTR GameName,
            /* [out] */ BSTR *GameCLSID);
        
        END_INTERFACE
    } IGameDetectorVtbl;

    interface IGameDetector
    {
        CONST_VTBL struct IGameDetectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGameDetector_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGameDetector_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGameDetector_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGameDetector_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGameDetector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGameDetector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGameDetector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGameDetector_get_GameNames(This,pVal)	\
    ( (This)->lpVtbl -> get_GameNames(This,pVal) ) 

#define IGameDetector_CLSIDFromGameName(This,GameName,GameCLSID)	\
    ( (This)->lpVtbl -> CLSIDFromGameName(This,GameName,GameCLSID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGameDetector_INTERFACE_DEFINED__ */


#ifndef __IVPGameEventSink_INTERFACE_DEFINED__
#define __IVPGameEventSink_INTERFACE_DEFINED__

/* interface IVPGameEventSink */
/* [hidden][unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IVPGameEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9E2408E6-90BD-4538-A32D-169EB5858117")
    IVPGameEventSink : public IDispatch
    {
    public:
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE LeaveGroup( void) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE GetPresenceInfo( 
            long Id,
            BSTR *Nickname,
            BSTR *Fullname,
            BSTR *Location,
            BSTR *Email) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE GetParentWnd( 
            long *hWnd) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE SetGameWnd( 
            long hWnd) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE DupAvatar( 
            long ParentWnd,
            long Seat) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE SetAvatarPos( 
            long Seat,
            short Left,
            short Top,
            short Width,
            short Height) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE EnumMembers( 
            long Id,
            short MaxLevel) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE Send( 
            long Id,
            short SendType,
            BSTR Message,
            BSTR *Data) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE QueryService( 
            long *Id,
            short *Type) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE SendToService( 
            long ServiceId,
            long SrvSendType,
            BSTR Message,
            BSTR *Data,
            long ReqId) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVPGameEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVPGameEventSink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVPGameEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVPGameEventSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVPGameEventSink * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVPGameEventSink * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVPGameEventSink * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVPGameEventSink * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *LeaveGroup )( 
            IVPGameEventSink * This);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *GetPresenceInfo )( 
            IVPGameEventSink * This,
            long Id,
            BSTR *Nickname,
            BSTR *Fullname,
            BSTR *Location,
            BSTR *Email);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *GetParentWnd )( 
            IVPGameEventSink * This,
            long *hWnd);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *SetGameWnd )( 
            IVPGameEventSink * This,
            long hWnd);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *DupAvatar )( 
            IVPGameEventSink * This,
            long ParentWnd,
            long Seat);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *SetAvatarPos )( 
            IVPGameEventSink * This,
            long Seat,
            short Left,
            short Top,
            short Width,
            short Height);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *EnumMembers )( 
            IVPGameEventSink * This,
            long Id,
            short MaxLevel);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *Send )( 
            IVPGameEventSink * This,
            long Id,
            short SendType,
            BSTR Message,
            BSTR *Data);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *QueryService )( 
            IVPGameEventSink * This,
            long *Id,
            short *Type);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *SendToService )( 
            IVPGameEventSink * This,
            long ServiceId,
            long SrvSendType,
            BSTR Message,
            BSTR *Data,
            long ReqId);
        
        END_INTERFACE
    } IVPGameEventSinkVtbl;

    interface IVPGameEventSink
    {
        CONST_VTBL struct IVPGameEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVPGameEventSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVPGameEventSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVPGameEventSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVPGameEventSink_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVPGameEventSink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVPGameEventSink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVPGameEventSink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IVPGameEventSink_LeaveGroup(This)	\
    ( (This)->lpVtbl -> LeaveGroup(This) ) 

#define IVPGameEventSink_GetPresenceInfo(This,Id,Nickname,Fullname,Location,Email)	\
    ( (This)->lpVtbl -> GetPresenceInfo(This,Id,Nickname,Fullname,Location,Email) ) 

#define IVPGameEventSink_GetParentWnd(This,hWnd)	\
    ( (This)->lpVtbl -> GetParentWnd(This,hWnd) ) 

#define IVPGameEventSink_SetGameWnd(This,hWnd)	\
    ( (This)->lpVtbl -> SetGameWnd(This,hWnd) ) 

#define IVPGameEventSink_DupAvatar(This,ParentWnd,Seat)	\
    ( (This)->lpVtbl -> DupAvatar(This,ParentWnd,Seat) ) 

#define IVPGameEventSink_SetAvatarPos(This,Seat,Left,Top,Width,Height)	\
    ( (This)->lpVtbl -> SetAvatarPos(This,Seat,Left,Top,Width,Height) ) 

#define IVPGameEventSink_EnumMembers(This,Id,MaxLevel)	\
    ( (This)->lpVtbl -> EnumMembers(This,Id,MaxLevel) ) 

#define IVPGameEventSink_Send(This,Id,SendType,Message,Data)	\
    ( (This)->lpVtbl -> Send(This,Id,SendType,Message,Data) ) 

#define IVPGameEventSink_QueryService(This,Id,Type)	\
    ( (This)->lpVtbl -> QueryService(This,Id,Type) ) 

#define IVPGameEventSink_SendToService(This,ServiceId,SrvSendType,Message,Data,ReqId)	\
    ( (This)->lpVtbl -> SendToService(This,ServiceId,SrvSendType,Message,Data,ReqId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVPGameEventSink_INTERFACE_DEFINED__ */


#ifndef __IVPGameEventSink2_INTERFACE_DEFINED__
#define __IVPGameEventSink2_INTERFACE_DEFINED__

/* interface IVPGameEventSink2 */
/* [hidden][unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IVPGameEventSink2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8ED92FC1-2CF0-4f56-B4D7-75696473B97D")
    IVPGameEventSink2 : public IDispatch
    {
    public:
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE DupAvatar( 
            long ParentWnd,
            long Seat) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE EnumMembers( 
            long Id,
            short MaxLevel) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE GetParentWnd( 
            long *hWnd) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE GetPresenceInfo( 
            long Id,
            BSTR *Nickname,
            BSTR *Fullname,
            BSTR *Location,
            BSTR *Email) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE LeaveGroup( void) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE QueryService( 
            long *Id,
            short *Type) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE Send( 
            long Id,
            short SendType,
            BSTR Message,
            BSTR *Data) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE SendToService( 
            long ServiceId,
            long SrvSendType,
            BSTR Message,
            BSTR *Data,
            long ReqId) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE SetAvatarPos( 
            long Seat,
            short Left,
            short Top,
            short Width,
            short Height) = 0;
        
        virtual /* [hidden][local][id] */ void STDMETHODCALLTYPE SetGameWnd( 
            long hWnd) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVPGameEventSink2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVPGameEventSink2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVPGameEventSink2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVPGameEventSink2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVPGameEventSink2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVPGameEventSink2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVPGameEventSink2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVPGameEventSink2 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *DupAvatar )( 
            IVPGameEventSink2 * This,
            long ParentWnd,
            long Seat);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *EnumMembers )( 
            IVPGameEventSink2 * This,
            long Id,
            short MaxLevel);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *GetParentWnd )( 
            IVPGameEventSink2 * This,
            long *hWnd);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *GetPresenceInfo )( 
            IVPGameEventSink2 * This,
            long Id,
            BSTR *Nickname,
            BSTR *Fullname,
            BSTR *Location,
            BSTR *Email);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *LeaveGroup )( 
            IVPGameEventSink2 * This);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *QueryService )( 
            IVPGameEventSink2 * This,
            long *Id,
            short *Type);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *Send )( 
            IVPGameEventSink2 * This,
            long Id,
            short SendType,
            BSTR Message,
            BSTR *Data);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *SendToService )( 
            IVPGameEventSink2 * This,
            long ServiceId,
            long SrvSendType,
            BSTR Message,
            BSTR *Data,
            long ReqId);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *SetAvatarPos )( 
            IVPGameEventSink2 * This,
            long Seat,
            short Left,
            short Top,
            short Width,
            short Height);
        
        /* [hidden][local][id] */ void ( STDMETHODCALLTYPE *SetGameWnd )( 
            IVPGameEventSink2 * This,
            long hWnd);
        
        END_INTERFACE
    } IVPGameEventSink2Vtbl;

    interface IVPGameEventSink2
    {
        CONST_VTBL struct IVPGameEventSink2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVPGameEventSink2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVPGameEventSink2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVPGameEventSink2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVPGameEventSink2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVPGameEventSink2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVPGameEventSink2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVPGameEventSink2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IVPGameEventSink2_DupAvatar(This,ParentWnd,Seat)	\
    ( (This)->lpVtbl -> DupAvatar(This,ParentWnd,Seat) ) 

#define IVPGameEventSink2_EnumMembers(This,Id,MaxLevel)	\
    ( (This)->lpVtbl -> EnumMembers(This,Id,MaxLevel) ) 

#define IVPGameEventSink2_GetParentWnd(This,hWnd)	\
    ( (This)->lpVtbl -> GetParentWnd(This,hWnd) ) 

#define IVPGameEventSink2_GetPresenceInfo(This,Id,Nickname,Fullname,Location,Email)	\
    ( (This)->lpVtbl -> GetPresenceInfo(This,Id,Nickname,Fullname,Location,Email) ) 

#define IVPGameEventSink2_LeaveGroup(This)	\
    ( (This)->lpVtbl -> LeaveGroup(This) ) 

#define IVPGameEventSink2_QueryService(This,Id,Type)	\
    ( (This)->lpVtbl -> QueryService(This,Id,Type) ) 

#define IVPGameEventSink2_Send(This,Id,SendType,Message,Data)	\
    ( (This)->lpVtbl -> Send(This,Id,SendType,Message,Data) ) 

#define IVPGameEventSink2_SendToService(This,ServiceId,SrvSendType,Message,Data,ReqId)	\
    ( (This)->lpVtbl -> SendToService(This,ServiceId,SrvSendType,Message,Data,ReqId) ) 

#define IVPGameEventSink2_SetAvatarPos(This,Seat,Left,Top,Width,Height)	\
    ( (This)->lpVtbl -> SetAvatarPos(This,Seat,Left,Top,Width,Height) ) 

#define IVPGameEventSink2_SetGameWnd(This,hWnd)	\
    ( (This)->lpVtbl -> SetGameWnd(This,hWnd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVPGameEventSink2_INTERFACE_DEFINED__ */


#ifndef __IGameEventSinkProperties_INTERFACE_DEFINED__
#define __IGameEventSinkProperties_INTERFACE_DEFINED__

/* interface IGameEventSinkProperties */
/* [hidden][unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGameEventSinkProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E223B3B1-10B8-4be8-A2B7-529254DB2D2D")
    IGameEventSinkProperties : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetCurGmConPntIID( 
            /* [in] */ BSTR CurGameConPntIID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetGmInterfaceType( 
            /* [in] */ SHORT GameInterfaceType) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGameEventSinkPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGameEventSinkProperties * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGameEventSinkProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGameEventSinkProperties * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetCurGmConPntIID )( 
            IGameEventSinkProperties * This,
            /* [in] */ BSTR CurGameConPntIID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetGmInterfaceType )( 
            IGameEventSinkProperties * This,
            /* [in] */ SHORT GameInterfaceType);
        
        END_INTERFACE
    } IGameEventSinkPropertiesVtbl;

    interface IGameEventSinkProperties
    {
        CONST_VTBL struct IGameEventSinkPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGameEventSinkProperties_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGameEventSinkProperties_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGameEventSinkProperties_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGameEventSinkProperties_SetCurGmConPntIID(This,CurGameConPntIID)	\
    ( (This)->lpVtbl -> SetCurGmConPntIID(This,CurGameConPntIID) ) 

#define IGameEventSinkProperties_SetGmInterfaceType(This,GameInterfaceType)	\
    ( (This)->lpVtbl -> SetGmInterfaceType(This,GameInterfaceType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGameEventSinkProperties_INTERFACE_DEFINED__ */



#ifndef __VPGameEmulatorLib_LIBRARY_DEFINED__
#define __VPGameEmulatorLib_LIBRARY_DEFINED__

/* library VPGameEmulatorLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VPGameEmulatorLib;

#ifndef ___IVPGEmulatorEvents_DISPINTERFACE_DEFINED__
#define ___IVPGEmulatorEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IVPGEmulatorEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IVPGEmulatorEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6C8AB957-E347-4b99-AAD8-94C8253554D9")
    _IVPGEmulatorEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IVPGEmulatorEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IVPGEmulatorEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IVPGEmulatorEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IVPGEmulatorEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IVPGEmulatorEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IVPGEmulatorEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IVPGEmulatorEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IVPGEmulatorEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IVPGEmulatorEventsVtbl;

    interface _IVPGEmulatorEvents
    {
        CONST_VTBL struct _IVPGEmulatorEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IVPGEmulatorEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IVPGEmulatorEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IVPGEmulatorEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IVPGEmulatorEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IVPGEmulatorEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IVPGEmulatorEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IVPGEmulatorEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IVPGEmulatorEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_VPGameEventSink;

#ifdef __cplusplus

class DECLSPEC_UUID("C4B93828-2377-4224-9DBA-0A173A463BE5")
VPGameEventSink;
#endif

EXTERN_C const CLSID CLSID_VPGameDetector;

#ifdef __cplusplus

class DECLSPEC_UUID("E186B192-54BE-471b-A982-9C9C97967873")
VPGameDetector;
#endif

EXTERN_C const CLSID CLSID_VPGame;

#ifdef __cplusplus

class DECLSPEC_UUID("09CDEFC2-BAB8-4db1-B8B8-78BEA0CD06F3")
VPGame;
#endif
#endif /* __VPGameEmulatorLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


