#include "Drawing.h"

CDraw g_pDraw;

void CDraw::init()
{
	if (g_pSurface == NULL)
	{
		MessageBox(0, "Surface Problems", "Hook", 0);
		return;
	}

	font_menuarrows = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_menuarrows, "Visitor TT2 BRK", 12, 200, 0, 0, FONTFLAG_ANTIALIAS + FONTFLAG_OUTLINE);
	//g_pSurface->SetFontGlyphSet(font_menuarrows, "Microsoft Sans Serif", 12, 700, 0, 0, FONTFLAG_OUTLINE);
	g_pSurface->SetFontGlyphSet(font_menuarrows, "Segoe UI", 17, 100, 0, 0, FONTFLAG_ANTIALIAS);


	esp_font = g_pSurface->CreateFont();
	// g_pSurface->SetFontGlyphSet(font_menuarrows, "Visitor TT2 BRK", 11, 200, 0, 0, FONTFLAG_ANTIALIAS + FONTFLAG_OUTLINE);
	// g_pSurface->SetFontGlyphSet(esp_font, "Microsoft Sans Serif", 12, 700, 0, 0, FONTFLAG_OUTLINE);
	g_pSurface->SetFontGlyphSet(esp_font, "Consolas", 12, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS);
	

	font_menuoptions = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font_menuoptions, "Segoe UI", 17, 100, 0, 0, FONTFLAG_ANTIALIAS);
	//g_pSurface->SetFontGlyphSet(font_menuoptions, "Razer Regular Italic", 14, 525, 0, 0, FONTFLAG_ANTIALIAS);

	font_menutitle = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_menutitle, "Razer Regular Italic", 21, 200, 0, 0, 0x200);
	g_pSurface->SetFontGlyphSet(font_menutitle, "Segoe UI", 13, 200, 0, 0, FONTFLAG_ANTIALIAS);

	font_menutab = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font_menutab, "Razer Regular Italic", 15, 200, 0, 0, FONTFLAG_ANTIALIAS);

	font_menu = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font_menu, "Razer Regular Italic", 13, 200, 0, 0, FONTFLAG_ANTIALIAS);

	menu_title = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_title, "Verdana", 18, 1, 0, 0, FONTFLAG_ANTIALIAS);

	menu_ready = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_ready, "Verdana", 13, 1, 0, 0, FONTFLAG_ANTIALIAS);

	menu_webdings = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_webdings, "Arial", 22, 100, 0, 0, FONTFLAG_ANTIALIAS);

	menu_tabs = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(menu_tabs, "Razer Regular Italic", 21, 200, 0, 0, 0x200);
	g_pSurface->SetFontGlyphSet(menu_tabs, "Verdana", 13, 20, 0, 0, FONTFLAG_ANTIALIAS);

	menu_features = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_features, "Arial", 22, 100, 0, 0, FONTFLAG_ANTIALIAS);

	font_esp = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_esp, "Razer Regular Italic", 13, 200, 0, 0, FONTFLAG_OUTLINE + FONTFLAG_NONE);
	g_pSurface->SetFontGlyphSet(font_esp, "Visitor TT2 BRK", 9, 200, 0, 0, FONTFLAG_OUTLINE + FONTFLAG_NONE);

}

void CDraw::DrawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void CDraw::FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void CDraw::LineRGBA(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawLine(x1, y1, x2, y2);
}

void CDraw::DrawRect(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawFilledRect(x1, y1, x2, y2);
}

void CDraw::DrawHealthBar(int x, int y, int w, int h, int r, int g, int b, int a, float health)
{
	x -= w / 2;
	y -= h / 2;
	g_pDraw.FillRGBA(x, y, w, h + 1, 0, 0, 0, 255);
	UINT hw = (UINT)(((h + 1) * health) / 100);
	g_pDraw.FillRGBA(x + 1, y + 1, w - 2, hw - 2, r, g, b, a);
}

void CDraw::DrawEspBox(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pDraw.DrawOutlineRect(x - 1, y - 1, w + 2, h + 2, 0, 0, 0, a);
	g_pDraw.DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, 0, 0, 0, a);
	g_pDraw.DrawOutlineRect(x, y, w, h, r, g, b, a);
}

int CDraw::getWidth(unsigned long font, const char* input, ...)
{
	INT iWide = 0;
	INT iTall = 0;
	INT iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

	wchar_t* pszUnicode = new wchar_t[iBufSize];
	MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

	g_pSurface->GetTextSize(font, pszUnicode, iWide, iTall);

	delete[] pszUnicode;

	return iWide;
}

std::wstring CDraw::stringToWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

void CDraw::DrawMinimizeWindow(int x, int y, int w, int h, int r, int g, int b, int a, int r1, int g1, int b1, int a1)
{
	DrawOutlineRect(x, y, w, h, r, g, b, a);
	FillRGBA(x - 3, y + 3, w, h, r1, g1, b1, a1);
	FillRGBA(x, y + 1, w, 1, r, g, b, a);

	DrawOutlineRect(x - 3, y + 3, w, h, r, g, b, a);
	FillRGBA(x - 3, y + 4, w, 1, r, g, b, a);
}

void CDraw::VSLogo(int x, int y, int w, int h, int r, int g, int b, int a)
{
	FillRGBA(x, y + h / 4, 2, h - h / 2, r, g, b, a);

	FillRGBA(x + w, y, 3, h, r, g, b, a);

	LineRGBA(x + w, y, x, y + h / (float)1.3, r, g, b, a);
	LineRGBA(x + w + 1, y, x + 1, y + h / (float)1.3, r, g, b, a);
	LineRGBA(x + w + 2, y, x + 2, y + h / (float)1.3, r, g, b, a);

	LineRGBA(x, y + h / 4, x + w, y + h, r, g, b, a);
	LineRGBA(x + 1, y + h / 4, x + w + 1, y + h, r, g, b, a);
	LineRGBA(x + 2, y + h / 4, x + w + 2, y + h, r, g, b, a);
}

void CDraw::DrawString(unsigned long Font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...)
{
	CHAR szBuffer[MAX_PATH];

	if (!input)
		return;

	vsprintf(szBuffer, input, (char*)&input + _INTSIZEOF(input));

	if (center)
		x -= getWidth(Font, szBuffer) / 2;

	g_pSurface->DrawSetTextColor(r, g, b, a);
	g_pSurface->DrawSetTextFont(Font);
	g_pSurface->DrawSetTextPos(x, y);

	std::wstring wide = stringToWide(std::string(szBuffer));
	g_pSurface->DrawPrintText(wide.c_str(), wide.length());
}

void CDraw::DrawBone(CBaseEntity* pLocal, int pEntityIndex, int a)
{
	Vector vBones[19];

	for (int iBone = 0; iBone < 19; iBone++)
	{
		Vector vPlayer;
		g_pMath.GetHitboxPosition(iBone, vPlayer, pLocal->GetAbsAngles(), pEntityIndex);
		g_pDebugOverlay->ScreenPosition(vPlayer, vBones[iBone]) != 1;
	}

	g_pDraw.LineRGBA(vBones[0].x, vBones[0].y, vBones[1].x, vBones[1].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[1].x, vBones[1].y, vBones[2].x, vBones[2].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[2].x, vBones[2].y, vBones[3].x, vBones[3].y, 255, 255, 255, a);

	g_pDraw.LineRGBA(vBones[0].x, vBones[0].y, vBones[4].x, vBones[4].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[4].x, vBones[4].y, vBones[5].x, vBones[5].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[5].x, vBones[5].y, vBones[6].x, vBones[6].y, 255, 255, 255, a);

	g_pDraw.LineRGBA(vBones[0].x, vBones[0].y, vBones[9].x, vBones[9].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[9].x, vBones[9].y, vBones[10].x, vBones[10].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[10].x, vBones[10].y, vBones[11].x, vBones[11].y, 255, 255, 255, a);

	g_pDraw.LineRGBA(vBones[10].x, vBones[10].y, vBones[12].x, vBones[12].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[12].x, vBones[12].y, vBones[13].x, vBones[13].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[13].x, vBones[13].y, vBones[14].x, vBones[14].y, 255, 255, 255, a);

	g_pDraw.LineRGBA(vBones[10].x, vBones[10].y, vBones[15].x, vBones[15].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[15].x, vBones[15].y, vBones[16].x, vBones[16].y, 255, 255, 255, a);
	g_pDraw.LineRGBA(vBones[16].x, vBones[16].y, vBones[17].x, vBones[17].y, 255, 255, 255, a);
}