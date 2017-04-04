#include "Main.h"

HLCLient* g_pClient;
CEngineClient* g_pEngine;
ISurface* g_pSurface;
IPanel* g_pPanel;
CEntityList* g_pEntList;
CInput* g_pInput;
CGlobalVars* g_pGlobalVars;
CModelInfo* g_pModel;
CTrace* g_pEngineTrace;
CDebugOverlay* g_pDebugOverlay;

template<class T>T* GetInterface(std::string szModuleName, std::string szInterfaceName, bool bSkip = false)
{
	if (szModuleName.empty() || szInterfaceName.empty())
		return nullptr;

	typedef PVOID(*CreateInterfaceFn)(const char* pszName, int* piReturnCode);
	CreateInterfaceFn hInterface = nullptr;

	while (!hInterface)
	{
		hInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(szModuleName.c_str()), "CreateInterface");
		Sleep(5);
	}

	char pszBuffer[256];

	for (int i = 0; i < 100; i++)
	{
		sprintf_s(pszBuffer, "%s%0.3d", szInterfaceName.c_str(), i);
		PVOID pInterface = hInterface(pszBuffer, nullptr);

		if (pInterface && pInterface != NULL)
		{
			if (bSkip) sprintf_s(pszBuffer, "%s%0.3d", szInterfaceName.c_str(), i + 1);
			Sleep(5);
			break;
		}
	}

	return (T*)hInterface(pszBuffer, nullptr);
}

int InitializeMain()
{
	g_pClient = GetInterface<HLCLient>("client.dll", "VClient");
	g_pEntList = GetInterface<CEntityList>("client.dll", "VClientEntityList");
	g_pEngine = GetInterface<CEngineClient>("engine.dll", "VEngineClient");
	g_pModel = GetInterface<CModelInfo>("engine.dll", "VModelInfoClient");
	g_pDebugOverlay = GetInterface<CDebugOverlay>("engine.dll", "VDebugOverlay");
	g_pEngineTrace = GetInterface<CTrace>("engine.dll", "EngineTraceClient");
	g_pSurface = GetInterface<ISurface>("vguimatsurface.dll", "VGUI_Surface");
	g_pPanel = GetInterface<IPanel>("vgui2.dll", "VGUI_Panel");
	g_pGlobalVars = (CGlobalVars*)*(PDWORD)*(PDWORD)(PatternSearch("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\x8B\x40\x10\x89\x41\x04", "x????xxxxxx", NULL, NULL) + 0x1);

	DWORD* pdwClientVMT2 = (DWORD*)*(DWORD*)g_pClient;
	g_pInput = *(CInput**)(pdwClientVMT2[15] + 0x1);

	PDWORD* pdwPanelVMT = (PDWORD*)g_pPanel;
	PDWORD* pdwClientVMT = (PDWORD*)g_pClient;
	PDWORD* pdwSurface = (PDWORD*)g_pSurface;

	Offsets::Init();
	g_pCvar.Init();
	g_phkPaintTraverse = new CVMTHookManager(pdwPanelVMT);
	g_phkPaintTraverse->dwHookMethod((DWORD)PaintTraverseHook, 41);

	g_phkCreateMove = new CVMTHookManager(pdwClientVMT);
	g_phkCreateMove->dwHookMethod((DWORD)CreateMoveHook, 21);

	//g_phkPlaySound = new CVMTHookManager(pdwSurface);
	//oPlaySound = (PlaySoundFn)g_phkPlaySound->dwHookMethod((DWORD)PlaySoundHook, 82);

	return 0;
}

DWORD WINAPI Unhooking(LPARAM lpParam)
{
	while (true)
	{
		if (GetAsyncKeyState(VK_DELETE) & 1 && GetForegroundWindow() == FindWindowA(NULL, "Counter-Strike: Global Offensive"))
		{
			g_phkCreateMove->UnHook();
			g_phkPaintTraverse->UnHook();
			//g_phkPlaySound->UnHook();
			Sleep(1000);

			FreeConsole();
			FreeLibraryAndExitThread((HMODULE)lpParam, 0);
		}

		Sleep(50);
	}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		InitializeMain();
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Unhooking, 0, 0, 0);
		break;
	}

	return TRUE;
}