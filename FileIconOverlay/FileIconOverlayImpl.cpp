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

    std::wstring icon_path;
    bool ok = Utils::GetOverlayIconPath(&icon_path);
    if (!ok) {
        return S_FALSE;
    }

   lstrcpy(pwszIconFile, icon_path.c_str());
    *pdwFlags = ISIOI_ICONFILE;
    *pIndex = 0;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileIconOverlayImpl::GetPriority(
    __RPC__out int *pPriority
) {
    if (pPriority == nullptr) {
        return E_POINTER;
    }

    int priority;
    bool ok = Utils::GetOverlayIconPriority(&priority);
    if (!ok) {
        *pPriority = 100;
        return S_FALSE;
    }

    *pPriority = priority; // 0 (highest) - 100 (lowest)
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileIconOverlayImpl::IsMemberOf(
    __RPC__in_string LPCWSTR pwszPath,
    DWORD dwAttrib
) {
    std::vector<std::wstring> paths = {};
    auto ok = Utils::GetNeedOverlayFilePaths(&paths);
    if (!ok) {
        return S_FALSE;
    }
    for (auto path : paths) {
        if (std::wcscmp(pwszPath, path.c_str()) == 0) {
            return S_OK;
        }
    }
    return S_FALSE;
}
