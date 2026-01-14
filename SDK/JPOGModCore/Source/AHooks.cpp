#include "pch.h"
#include "AHooks.h"
#include "HookHelpers.h"
#include "AModLoader.h"

#include <TRender/TModel.h>

#include <JPOGSDK/Interface.h>
#include <JPOGSDK/SDKHooks.h>

TOSHI_NAMESPACE_USING

static TBOOL s_bIsLoadingModel = TFALSE;

static void HooksPrint(const TCHAR *a_pchFormat, ...)
{
	TCHAR s_szBuffer[512];

	va_list list;
	va_start(list, a_pchFormat);
	vsprintf_s(s_szBuffer, a_pchFormat, list);
	va_end(list);

	printf(s_szBuffer);
}

MEMBER_HOOK(Interface::TKernelInterface + 0xb360, Toshi::TModel, TFileManager_CreateFile, Toshi::TFile *, const Toshi::TCString &a_strName, TUINT a_uiMode)
{
	HooksPrint("[ModCore] TFileManager::CreateFile (file=%s; mode=%u)\n", a_strName.GetString(), a_uiMode);

	return CallOriginal(a_strName, a_uiMode);
}

MEMBER_HOOK(Interface::TKernelInterface + 0x14c90, Toshi::TKernelInterface, TKernelInterface_LoadInterface, void *, const Toshi::TCString &a_strName)
{
	HooksPrint("[ModCore] TKernelInterface::LoadInterface (file=%s)\n", a_strName.GetString());

	// Patch name of the dll, since exe name is referenced by the Units.dll
	if (a_strName == "Units") return CallOriginal("JPModUnits");

	return CallOriginal(a_strName);
}

MEMBER_HOOK(Interface::TRenderInterface + 0x9730, Toshi::TModel, TModel_LoadTMD, TBOOL, const TCHAR *a_pchFileName)
{
	HooksPrint("[ModCore] Game loads TModel (name=%s)\n", a_pchFileName);

	s_bIsLoadingModel = TTRUE;
	TBOOL bResult     = CallOriginal(a_pchFileName);
	s_bIsLoadingModel = TFALSE;

	return bResult;
}

//-----------------------------------------------------------------------------
// Patch to allow using any TKL at any digsite
//-----------------------------------------------------------------------------
struct TKeyframeLibraryManager {};
struct TKeyframeLibrary {};
MEMBER_HOOK(Interface::TRenderInterface + 0x6850, TKeyframeLibraryManager, TKeyframeLibraryManager_UnloadLibrary, void, TKeyframeLibrary *a_pKeyframeLibrary)
{
	HooksPrint("[ModCore] Preventing TKeyframeLibrary from destroying...\n");
}

MEMBER_HOOK(Interface::TRenderInterface + 0x5850, TKeyframeLibraryManager, TKeyframeLibraryManager_GetLibrary, TKeyframeLibrary *, const TCHAR *a_pchKeyLibName)
{
	HooksPrint("[ModCore] Game requests TKeyframeLibrary (name=%s)\n", a_pchKeyLibName);

	TKeyframeLibrary *pResult = CallOriginal(a_pchKeyLibName);
	if (pResult) return pResult;

	// If the keyframe library wasn't found, need to load it
	HooksPrint("[ModCore] Couldn't find keyframe library, so will try to load it...\n");
	TCHAR s_szBuffer[MAX_PATH];
	sprintf_s(s_szBuffer, "Data\\Models\\%s.tkl", a_pchKeyLibName);

	// TKeyframeLibraryManager::LoadLibrary
	pResult = CALL_THIS(Interface::TRenderInterface + 0x57a0, TKeyframeLibraryManager *, TKeyframeLibrary *, this, const TCHAR *, s_szBuffer);

	if (!pResult) HooksPrint("[ModCore] Couldn't load the TKL file\n");

	return pResult;
}

void AHooks::Initialise()
{
	InstallHook<TKernelInterface_LoadInterface>();
	InstallHook<TFileManager_CreateFile>();
	InstallHook<TModel_LoadTMD>();
	InstallHook<TKeyframeLibraryManager_UnloadLibrary>();
	InstallHook<TKeyframeLibraryManager_GetLibrary>();
}

