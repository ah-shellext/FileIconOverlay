// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "FileIconOverlay_i.h"
#include "dllmain.h"

CFileIconOverlayModule _AtlModule;

// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
