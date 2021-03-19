#include "pch.h"
#include "FileIconOverlayImpl.h"

HRESULT STDMETHODCALLTYPE CFileIconOverlayImpl::GetOverlayInfo(
    __RPC__out_ecount_full_string(cchMax) LPWSTR pwszIconFile,
    int cchMax,
    __RPC__out int *pIndex,
    __RPC__out DWORD *pdwFlags
) {
    if (pwszIconFile == nullptr || pIndex == nullptr || pdwFlags == nullptr) {
        return E_POINTER;
    }
    if (cchMax < 1) {
        return E_INVALIDARG;
    }

    lstrcpy(pwszIconFile, L"E:\\Icon.ico");
    *pdwFlags = ISIOI_ICONFILE;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileIconOverlayImpl::GetPriority(
    __RPC__out int *pPriority
) {
    if (pPriority == nullptr) {
        return E_POINTER;
    }
    *pPriority = 0; // 0 (highest) - 100 (lowest)
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileIconOverlayImpl::IsMemberOf(
    __RPC__in_string LPCWSTR pwszPath,
    DWORD dwAttrib
) {
    if (std::wcscmp(pwszPath, L"E:\\School") == 0) {
        return S_OK;
    }
    return S_FALSE;
}
