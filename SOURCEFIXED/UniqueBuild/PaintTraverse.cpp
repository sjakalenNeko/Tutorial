#include "PaintTraverse.h"

void __stdcall PaintTraverseHook(unsigned vguiPanel, bool forceRepaint, bool allowForce)
{
	static DWORD dwOrgPaintTraverse = g_phkPaintTraverse->dwGetMethodAddress(41);

	__asm
	{
		PUSH allowForce;
		PUSH forceRepaint;
		PUSH vguiPanel;
		MOV ECX, g_pPanel;
		CALL dwOrgPaintTraverse;
	}

	static bool bDoOnce = true;
	if (bDoOnce)
	{
		g_pDraw.init();
		bDoOnce = false;
	}

	const char* pszPanelName = g_pPanel->GetName(vguiPanel);
	if (pszPanelName && pszPanelName[0] == 'M' && pszPanelName[3] == 'S' && pszPanelName[9] == 'T' && pszPanelName[12] == 'P')
	{
		static bool bDoOnce = true;
		if (bDoOnce)
		{
			g_pCvar.readConfig("Config");
			bDoOnce = false;
		}
		else if (g_pCvar.getValue("menu_x") == 0)
		{
			g_pCvar.Init();
			g_pCvar.saveConfig("Config");
		}

		if (g_pCvar.getValue("esp_active") == 1)
			g_pWallhack.doDraw();


		g_pGui.GetMouse();
		g_pGui.DrawMenu();
		g_pGui.Mouse();
	}
}