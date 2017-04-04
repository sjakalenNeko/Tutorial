#pragma once

#include "Main.h"

class CDraw
{
public:
	void init();

	void DrawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a);
	void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
	void LineRGBA(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
	void DrawRect(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
	void DrawHealthBar(int x, int y, int w, int h, int r, int g, int b, int a, float health);
	void DrawEspBox(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawMinimizeWindow(int x, int y, int w, int h, int r, int g, int b, int a, int r1, int g1, int b1, int a1);
	void VSLogo(int x, int y, int w, int h, int r, int g, int b, int a);

	void DrawString(unsigned long Font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...);
	int getWidth(unsigned long font, const char* input, ...);
	std::wstring stringToWide(const std::string& text);

	void DrawBone(CBaseEntity* pLocal, int pEntityIndex, int a);

	unsigned long font_esp, font_menu, font_menutab, font_menutitle, font_menuarrows, menu_title, menu_webdings, menu_ready, menu_tabs, menu_features, font_menuoptions, esp_font;
};

extern CDraw g_pDraw;