#pragma once

#include "resource.h"
#include "FileIconOverlay_i.h"
#include "Utils.hpp"

#include <shlobj.h>
#include <string>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

class ATL_NO_VTABLE CFileIconOverlayImpl :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CFileIconOverlayImpl, &CLSID_FileIconOverlayImpl>,
    public IDispatchImpl<IFileIconOverlayImpl, &IID_IFileIconOverlayImpl, &LIBID_FileIconOverlayLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IShellIconOverlayIdentifier {

public:

    CFileIconOverlayImpl() { }

    DECLARE_REGISTRY_RESOURCEID(106)

    BEGIN_COM_MAP(CFileIconOverlayImpl)
        COM_INTERFACE_ENTRY(IFileIconOverlayImpl)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct() {
        return S_OK;
    }

    void FinalRelease() { }

public:

    virtual HRESULT STDMETHODCALLTYPE GetOverlayInfo(
        /* [size_is][string][out] */
        __RPC__out_ecount_full_string(cchMax) LPWSTR pwszIconFile,
        /* [in] */
        int cchMax,
        /* [out] */
        __RPC__out int *pIndex,
        /* [out] */
        __RPC__out DWORD *pdwFlags
    );

    virtual HRESULT STDMETHODCALLTYPE GetPriority(
        /* [out] */
        __RPC__out int *pPriority
    );

    virtual HRESULT STDMETHODCALLTYPE IsMemberOf(
        /* [string][in] */
        __RPC__in_string LPCWSTR pwszPath,
        /* [in] */
        DWORD dwAttrib
    );

};

OBJECT_ENTRY_AUTO(__uuidof(FileIconOverlayImpl), CFileIconOverlayImpl)
