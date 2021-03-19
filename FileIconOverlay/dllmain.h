// dllmain.h : Declaration of module class.

class CFileIconOverlayModule : public ATL::CAtlDllModuleT< CFileIconOverlayModule > {
public:
    DECLARE_LIBID(LIBID_FileIconOverlayLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILEICONOVERLAY, "{61982caa-30fc-4f28-9ba1-84ccb7ddd71d}")
};

extern class CFileIconOverlayModule _AtlModule;
