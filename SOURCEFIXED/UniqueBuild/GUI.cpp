#include "gui.h"

CGui g_pGui;

CGui::CGui()
{
	cursor = false;
	cursorposition[0] = 0;
	cursorposition[1] = 0;
	bLeftClick = false;
	bLeftClickRelease = false;
	bRightClick = false;
	incombo = false;
	inkeypressed = false;
	ininsertnumber = false;

	for (int n = 0; n <= 25; n++)
	{
		g_pGui.cComboBox[n].Open = false;
		g_pGui.cComboBox[n].Active = true;
	}
}

void CGui::Mouse()
{
	if (cursor)
	{
		g_pSurface->SurfaceGetCursorPos(cursorposition[0], cursorposition[1]);

		g_pDraw.FillRGBA(cursorposition[0] + 1, cursorposition[1], 1, 17, 3, 6, 26, 255);

		for (int i = 0; i < 11; i++)
			g_pDraw.FillRGBA(cursorposition[0] + 2 + i, cursorposition[1] + 1 + i, 1, 1, 3, 6, 26, 255);

		g_pDraw.FillRGBA(cursorposition[0] + 8, cursorposition[1] + 12, 5, 1, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 8, cursorposition[1] + 13, 1, 1, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 9, cursorposition[1] + 14, 1, 2, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 10, cursorposition[1] + 16, 1, 2, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 8, cursorposition[1] + 18, 2, 1, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 7, cursorposition[1] + 16, 1, 2, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 6, cursorposition[1] + 14, 1, 2, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 5, cursorposition[1] + 13, 1, 1, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 4, cursorposition[1] + 14, 1, 1, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 3, cursorposition[1] + 15, 1, 1, 3, 6, 26, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 2, cursorposition[1] + 16, 1, 1, 3, 6, 26, 255);

		for (int i = 0; i < 4; i++)
			g_pDraw.FillRGBA(cursorposition[0] + 2 + i, cursorposition[1] + 2 + i, 1, 14 - (i * 2), 255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255);

		g_pDraw.FillRGBA(cursorposition[0] + 6, cursorposition[1] + 6, 1, 8, 235, 235, 235, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 7, cursorposition[1] + 7, 1, 9, 231, 231, 231, 255);

		for (int i = 0; i < 4; i++)
			g_pDraw.FillRGBA(cursorposition[0] + 8 + i, cursorposition[1] + 8 + i, 1, 4 - i, 227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255);

		g_pDraw.FillRGBA(cursorposition[0] + 8, cursorposition[1] + 14, 1, 4, 207, 207, 207, 255);
		g_pDraw.FillRGBA(cursorposition[0] + 9, cursorposition[1] + 16, 1, 2, 203, 203, 203, 255);
	}
}

bool IsMenuKey(int iKey)
{
	static bool bKeyPressed[256];

	if (GetAsyncKeyState(iKey))
	{
		if (!bKeyPressed[iKey])
		{
			bKeyPressed[iKey] = true;
			return true;
		}
	}
	else
	{
		bKeyPressed[iKey] = false;
	}

	return false;
}

void CGui::GetMouse()
{
	if (cursor)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			bLeftClick = true;
		}
		else
		{
			if (bLeftClick)
				bLeftClickRelease = true;
			else
				bLeftClickRelease = false;

			bLeftClick = false;
		}

		if (GetAsyncKeyState(VK_RBUTTON))
		{
			bRightClick = true;
		}
		else
		{
			if (bRightClick)
				bRightClickRelease = true;
			else
				bRightClickRelease = false;

			bRightClick = false;
		}
	}
}

bool CGui::MouseOver(int x, int y, int w, int h)
{
	if ((cursorposition[0] > x) && (cursorposition[0] < x + w) && (cursorposition[1] > y) && (cursorposition[1] < y + h))
		return true;

	return false;
}

bool CGui::LeftClick(int x, int y, int w, int h)
{
	if (bLeftClickRelease && (cursorposition[0] > x) && (cursorposition[0] < x + w) && (cursorposition[1] > y) && (cursorposition[1] < y + h))
		return true;

	return false;
}

void Menu3D(int x, int y, int w, int h, unsigned long title)
{
	g_pDraw.DrawOutlineRect(x - 1, y - 1, w + 2, h + 2, 0, 0, 0, 200);
	g_pDraw.FillRGBA(x, y, w, h, 60, 60, 60, 255);
	g_pDraw.FillRGBA(x, y + h - 10, w, 5, 90, 90, 90, 255);

	for (int i = 0; i < 20; i++)
	{
		g_pDraw.FillRGBA(x + i + 145, y - i + 5, 150, 15, 60, 60, 60, 255);
		g_pDraw.FillRGBA(x - i + 211, y - i + 5, 150, 15, 60, 60, 60, 255);
	}

	g_pDraw.LineRGBA(x + (float)164.5f, y - 15, x + (float)342.5f, y - 15, 0, 0, 0, 200);
	g_pDraw.LineRGBA(x + 150, y - 1, x + 164, y - 15, 0, 0, 0, 200);
	g_pDraw.LineRGBA(x + 341, y - 15, x + 355, y - 1, 0, 0, 0, 200);

	g_pDraw.LineRGBA(x, y + 5, x + 150, y + 5, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	g_pDraw.LineRGBA(x + 150, y + 5, x + 165, y - 10, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	g_pDraw.LineRGBA(x + 165, y - 10, x + 340, y - 10, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	g_pDraw.LineRGBA(x + 340, y - 10, x + 355, y + 5, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	g_pDraw.LineRGBA(x + 355, y + 5, x + w, y + 5, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);

	g_pDraw.FillRGBA(x, y + 20, w, 30, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);

	g_pDraw.FillRGBA(x, y + 55, w, 5, 90, 90, 90, 255);

	g_pDraw.DrawString(title, true, x + w / 2, y - 7, 255, 255, 255, 255, "M I N A Y E H O O K");

	g_pDraw.DrawOutlineRect(x + 10, y + 25, 150, 20, 20, 20, 20, 200);
	g_pDraw.DrawOutlineRect(x + 180, y + 25, 150, 20, 20, 20, 20, 200);
	g_pDraw.DrawOutlineRect(x + 350, y + 25, 140, 20, 20, 20, 20, 200);
}

void CGui::DrawCombobox(int x, int y, const char* var, int num, int max, std::string* structs, int distance)
{
	cComboBox[num].Name = const_cast<char*>(structs[g_pCvar.getValue(var)].c_str());
	g_pDraw.FillRGBA(x + distance, y - 2, 75, 22, 45, 44, 49, 255);
	g_pDraw.DrawOutlineRect(x + distance, y - 2, 75, 23, 110, 110, 110, 255);

	if (MouseOver(x + distance, y - 2, 75, 22) && !cComboBox[num].Open)
		g_pDraw.FillRGBA(x + distance, y - 2, 75, 22, 200, 200, 200, 50);

	if (cComboBox[num].Active)
	{
		cComboBox[num].iSelect = g_pCvar.getValue(var);

		if (MouseOver(x + distance, y - 2, 75, 22) && bLeftClickRelease)
		{
			cComboBox[num].Open = true;
			cComboBox[num].Active = false;
			incombo = true;
		}

		g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x + 6 + distance, y + 2, 200, 200, 200, 255, cComboBox[num].Name);
	}
	else
	{
		if (cComboBox[num].Open)
		{
			for (int i = 0; i < max; i++)
			{
				g_pDraw.FillRGBA(x + 2 + distance, y - 1 + (i * 20), 71, 20, 45, 44, 49, 255);
				g_pDraw.DrawOutlineRect(x + 2 + distance, y + (i * 20), 71, 20, 150, 150, 150, 50);

				if (MouseOver(x + 4 + distance, y + (i * 20), 68, 20))
				{
					g_pDraw.FillRGBA(x + 2 + distance, y + 1 + (i * 20), 71, 20, 200, 200, 200, 50);

					if (bLeftClickRelease)
					{
						cComboBox[num].iSelect = i;
						cComboBox[num].Name = const_cast<char*>(structs[cComboBox[num].iSelect].c_str());
						g_pCvar.setValue(var, cComboBox[num].iSelect);
						cComboBox[num].Open = false;
						incombo = false;
						cComboBox[num].Active = true;
					}
				}

				g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x + 6 + distance, y + 2 + (i * 20), 200, 200, 200, 255, structs[i].c_str());
			}
		}
	}

	if (!MouseOver(x + distance, y - 2, 75, 22) && bLeftClickRelease)
	{
		cComboBox[num].Open = false;
		cComboBox[num].Active = true;
		incombo = false;
	}

	if (cComboBox[num].Active == true)
		g_pDraw.DrawString(g_pDraw.font_menutab, false, x + 60 + distance, y + 2, 200, 200, 200, 255, "+");
}

void Checkbox(int x, int y, const char* var, int distance, unsigned long font)
{
	g_pDraw.DrawString(font, false, x, y + (float)1.5, 150, 150, 150, 255, var);

	if (g_pGui.LeftClick(x + distance, y + 2, 12, 12))
	{
		if (g_pCvar.getValue(var) != 1)
			g_pCvar.setValue(var, 1);
		else
			g_pCvar.setValue(var, 0);
	}

	if (g_pCvar.getValue(var) == 1)
		g_pDraw.FillRGBA(x + distance, y + 2, 12, 12, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);

	g_pDraw.DrawOutlineRect(x + distance, y + 2, 12, 12, 150, 150, 150, 255);
}

void PlusMinus(int x, int y, const char* var, int distance, int min, int max, unsigned long font)
{
	g_pDraw.DrawString(font, false, x, y + 2, 150, 150, 150, 255, var);

	g_pDraw.DrawOutlineRect(x + distance - 6, y + 3, 12, 12, 150, 150, 150, 255);
	g_pDraw.DrawString(g_pDraw.menu_tabs, false, x - 4 + distance, y + 1, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255, "<");

	g_pDraw.DrawOutlineRect(x + 55 + distance, y + 3, 12, 12, 150, 150, 150, 255);
	g_pDraw.DrawString(g_pDraw.menu_tabs, false, x + (float)56.8 + distance, y + 1, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255, ">");

	if (g_pCvar.getValue(var) >= 0 && g_pCvar.getValue(var) < 10)
		g_pDraw.DrawString(font, false, x + 27 + distance, y + 2, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));

	if (g_pCvar.getValue(var) > 9 && g_pCvar.getValue(var) < 100)
		g_pDraw.DrawString(font, false, x + 24 + distance, y + 2, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));

	if (g_pCvar.getValue(var) > 99 && g_pCvar.getValue(var) < 1000)
		g_pDraw.DrawString(font, false, x + 22 + distance, y + 2, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));

	int value = g_pCvar.getValue(var);

	if (g_pGui.LeftClick(x + distance - 6, y + 3, 12, 12))
		g_pCvar.setValue(var, value -= 1);

	if (g_pGui.LeftClick(x + 55 + distance, y + 3, 12, 12))
		g_pCvar.setValue(var, value += 1);

	if (g_pCvar.getValue(var) > max)
		g_pCvar.setValue(var, min);

	if (g_pCvar.getValue(var) < min)
		g_pCvar.setValue(var, max);
}

void CGui::DrawSlider(int x, int y, int w, int h, const char* var, int min, int max, int distance)
{
	g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x, y + (float)1.5, 150, 150, 150, 255, var);

	float sliderpos, barpos;

	int xd = x + distance;

	int value = g_pCvar.getValue(var);

	if (MouseOver(xd - 2, y + (float)1.5, w + 4, h + 4) && bLeftClick)
		sliderpos = (cursorposition[0] - xd);
	else
		sliderpos = (((value * 100) * 2) / max);

	if (sliderpos <= 1)
		sliderpos = 0;

	g_pCvar.setValue(var, max * (sliderpos / 2) / 100);

	barpos = (sliderpos / w * 100) * 2;

	if (barpos > w)
		barpos = w;

	g_pCvar.setValue(var, clamp(g_pCvar.getValue(var), min, max));

	g_pDraw.FillRGBA(x + distance, y + (float)4.5, barpos, h, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	g_pDraw.DrawOutlineRect(x + distance, y + (float)4.5, w + 1, h, 0, 0, 0, 255);

	g_pDraw.FillRGBA(x + barpos + distance, y + (float)2.8, 2, 10, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	g_pDraw.DrawOutlineRect(x + barpos + distance, y + (float)2.8, 3, 11, 0, 0, 0, 255);

	if (g_pCvar.getValue(var) >= 0 && g_pCvar.getValue(var) < 10)
		g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x + w + 15 + distance, y - 3, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));

	if (g_pCvar.getValue(var) > 9 && g_pCvar.getValue(var) < 100)
		g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x + w + 12 + distance, y - 3, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));

	if (g_pCvar.getValue(var) > 99 && g_pCvar.getValue(var) < 1000)
		g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x + w + 9 + distance, y - 3, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));

	if (g_pCvar.getValue(var) > 999 && g_pCvar.getValue(var) < 10000)
		g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x + w + 6 + distance, y - 3, 150, 150, 150, 255, "%i", g_pCvar.getValue(var));
}

void CGui::Slider(int x, int y, int w, int h, int min, int max, const char* cvar, int r, int g, int b, int a)
{
	int step = max / w;

	if (MouseOver(x - 2, y - 2, w + 4, h + 4) && bLeftClick)
		g_pCvar.setValue(cvar, cursorposition[0] - x * step);

	g_pDraw.DrawString(g_pDraw.font_menutab, false, x + w + 10, y - 4, 150, 150, 150, 255, "%i", g_pCvar.getValue(cvar));

	g_pDraw.FillRGBA(x, y, g_pCvar.getValue(cvar) / step, h, r, g, b, a);
	g_pDraw.DrawOutlineRect(x, y, w, h, 0, 0, 0, 255);
	g_pDraw.FillRGBA(x + g_pCvar.getValue(cvar) / step, y - (float)1.7, 2, 10, r, g, b, a);
	g_pDraw.DrawOutlineRect(x + g_pCvar.getValue(cvar) / step, y - (float)1.7, 3, 11, 0, 0, 0, a);

	if (g_pCvar.getValue(cvar) > max)
		g_pCvar.setValue(cvar, max);

	if (g_pCvar.getValue(cvar) < min)
		g_pCvar.setValue(cvar, min);
}

void CGui::GetKeyPressed(int x, int y, int w, int h, int r, int g, int b, int a, const char* cvar, int distance)
{
	static int iCount = 0;
	g_pDraw.DrawString(g_pDraw.font_menuoptions, false, x, y + (float)1.5, 150, 150, 150, 255, cvar);

	g_pDraw.DrawOutlineRect(x + distance, y, w, h, 150, 150, 150, 255);

	if (LeftClick(x - 2 + distance, y - 2, w + 4, h + 4))
		inkeypressed = true;

	if (inkeypressed)
	{
		iCount++;

		if (iCount > 1500)
			iCount = 0;

		if (iCount > 0 && iCount < 500)
			g_pDraw.DrawString(g_pDraw.font_menuoptions, true, x + w / 2 + distance, y + 1, 150, 150, 150, 255, ".");
		else if (iCount > 500 && iCount < 1000)
			g_pDraw.DrawString(g_pDraw.font_menuoptions, true, x + w / 2 + distance, y + 1, 150, 150, 150, 255, "..");
		else if (iCount > 1000 && iCount < 1500)
			g_pDraw.DrawString(g_pDraw.font_menuoptions, true, x + w / 2 + distance, y + 1, 150, 150, 150, 255, "...");

		for (int i = 1; i < 255; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				g_pCvar.setValue(cvar, i);
				inkeypressed = false;
			}
		}
	}
	else
	{
		g_pDraw.DrawString(g_pDraw.font_menuoptions, true, x + w / 2 + distance, y - 2, 150, 150, 150, 255, "%i", g_pCvar.getValue(cvar));
	}
}

void CGui::GetNumbersInsert(int x, int y, int w, int h, int r, int g, int b, int a, const char* cvar, int distance)
{
	static int iCount = 0;
	g_pDraw.DrawString(g_pDraw.font_menutab, false, x, y + (float)1.5, 150, 150, 150, 255, cvar);

	g_pDraw.DrawOutlineRect(x + distance, y, w, h, 150, 150, 150, 255);

	if (LeftClick(x - 2 + distance, y - 2, w + 4, h + 4))
		ininsertnumber = true;

	if (ininsertnumber)
	{
		iCount++;

		if (iCount > 1000)
			iCount = 0;

		if (iCount > 500)
			g_pDraw.DrawString(g_pDraw.font_menutab, true, x + w / 2 + distance, y, 150, 150, 150, 255, "|");

		for (int i = 48; i < 106; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				if (i == 96 || i == 48)
					g_pCvar.setValue(cvar, 0);
				else if (i == 97 || i == 49)
					g_pCvar.setValue(cvar, 1);
				else if (i == 98 || i == 50)
					g_pCvar.setValue(cvar, 2);
				else if (i == 99 || i == 51)
					g_pCvar.setValue(cvar, 3);
				else if (i == 100 || i == 52)
					g_pCvar.setValue(cvar, 4);
				else if (i == 101 || i == 53)
					g_pCvar.setValue(cvar, 5);
				else if (i == 102 || i == 54)
					g_pCvar.setValue(cvar, 6);
				else if (i == 103 || i == 55)
					g_pCvar.setValue(cvar, 7);
				else if (i == 104 || i == 56)
					g_pCvar.setValue(cvar, 8);
				else if (i == 105 || i == 57)
					g_pCvar.setValue(cvar, 9);

				ininsertnumber = false;
			}
		}
	}
	else
	{
		g_pDraw.DrawString(g_pDraw.font_menuoptions, true, x + w / 2 + distance, y + 1, 150, 150, 150, 255, "%i", g_pCvar.getValue(cvar));
	}
}

void ThreeDBorder(int x, int y, int w, int h, const char* text)
{
	g_pDraw.FillRGBA(x, y, w, h, 0, 0, 0, 255);

	g_pDraw.FillRGBA(x + 1, y - 3, w - 2, 60, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
	

	

	g_pDraw.DrawString(g_pDraw.font_menutitle, true, x + w / 2, y + 5, 255, 255, 255, 255, text);

	g_pDraw.FillRGBA(x + 1, y + 22, w - 2, h - 23, 50, 50, 50, 255);
	g_pDraw.LineRGBA(x + 1, y + 22, x + w - 2, y + 22, 130, 130, 130, 50);
}

void CGui::DragMenu(const char* x, const char* y, int w, int h, int& xdif, int& ydif)
{
	int valuex = g_pCvar.getValue(x);
	int valuey = g_pCvar.getValue(y);

	if (MouseOver(g_pCvar.getValue(x), g_pCvar.getValue(y), w, h) && bLeftClick)
	{
		if (xdif == -1 || ydif == -1)
		{
			xdif = cursorposition[0] - g_pCvar.getValue(x);
			ydif = cursorposition[1] - g_pCvar.getValue(y);
		}

		g_pCvar.setValue(x, valuex += cursorposition[0] - (xdif + g_pCvar.getValue(x)));
		g_pCvar.setValue(y, valuey += cursorposition[1] - (ydif + g_pCvar.getValue(y)));
	}
	else
	{
		xdif = -1;
		ydif = -1;
	}
}

void CGui::DrawMenu()
{
	if (IsMenuKey(VK_INSERT))
	{
		cursor = !cursor;

		if (g_pEngine->isinGame())
		{
			char buf[32];
			sprintf(buf, "cl_mouseenable %i", !cursor);
			g_pEngine->ExecuteClientCmd(buf);
		}
	}

	if (GetAsyncKeyState(VK_END))
		g_pCvar.saveConfig("config");

	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

	if (cursor)
	{
		static int x1, y1;

		int w = 540;
		int h = 360; // 310;

		DragMenu("menu_x", "menu_y", w, 60, x1, y1);

		static int iTab = 1;
		ThreeDBorder(g_pCvar.getValue("menu_x"), g_pCvar.getValue("menu_y"), w, h, "M I N A Y E H O O K");

		int xspace = 1;

		if (LeftClick(g_pCvar.getValue("menu_x") + 0, g_pCvar.getValue("menu_y") + 39, 108, 25))
			iTab = 1;

		if (LeftClick(g_pCvar.getValue("menu_x") + 108,g_pCvar.getValue("menu_y") + 39, 108, 25))
			iTab = 2;

		if (LeftClick(g_pCvar.getValue("menu_x") + 216, g_pCvar.getValue("menu_y") + 39, 108, 25))
			iTab = 3;

		if (LeftClick(g_pCvar.getValue("menu_x") + 324, g_pCvar.getValue("menu_y") + 39, 108, 25))
			iTab = 4;

		if (LeftClick(g_pCvar.getValue("menu_x") + 432, g_pCvar.getValue("menu_y") + 39, 108, 25) && g_pCvar.getValue("esp_players") == 1)
			iTab = 5;


		if (MouseOver(g_pCvar.getValue("menu_x") + 1, g_pCvar.getValue("menu_y") + 39, 108, 25))
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + 1, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 100);

		if (MouseOver(g_pCvar.getValue("menu_x") + 108, g_pCvar.getValue("menu_y") + 39, 108, 25))
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + 108, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 100);

		if (MouseOver(g_pCvar.getValue("menu_x") + 216, g_pCvar.getValue("menu_y") + 39, 108, 25))
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + 216, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 100);

		if (MouseOver(g_pCvar.getValue("menu_x") + 324, g_pCvar.getValue("menu_y") + 39, 108, 25) && g_pCvar.getValue("esp_players") == 1)
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + 324, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 100);

		if (MouseOver(g_pCvar.getValue("menu_x") + 432, g_pCvar.getValue("menu_y") + 39, 108, 25))
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + 431, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 100);

		g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 , g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "AIMBOT");
		g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 108, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "VISUALS");
		g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 216, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "MISC");
		g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 324, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "COLOURS");
		if (g_pCvar.getValue("esp_players") == 1)
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 432, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "PLAYERS");

		xspace = 108;

		if (iTab == 1)
		{
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2, g_pCvar.getValue("menu_y") + 43, 255, 255, 255, 255, "AIMBOT");
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2, g_pCvar.getValue("menu_y") + 4, 255, 255, 255, 255, "AIMBOT");

			int spaceX = 65;

			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "aimbot_active", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			if (g_pCvar.getValue("aimbot_weapon_group") != 1)
			{
				DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "aimbot_fov", 0, 20, 237);
				spaceX += 25;
				DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "aimbot_spot", 0, 20, 237);
				spaceX += 25;
				DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "aimbot_smooth", 1, 20, 237);
				spaceX += 25;
				Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "aimbot_rcs", 450, g_pDraw.font_menuoptions);
				spaceX += 25;
				Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "aimbot_humanize", 450, g_pDraw.font_menuoptions);
				spaceX += 25;
				Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "trigger_active", 450, g_pDraw.font_menuoptions);
				spaceX += 25;
				Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "trigger_overshoot", 450, g_pDraw.font_menuoptions);
				spaceX += 25;
				Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "check_smoke", 450, g_pDraw.font_menuoptions);
				spaceX += 25;
				GetKeyPressed(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 50, 15, 150, 150, 150, 255, "trigger_key", 430);
				spaceX += 25;
				GetKeyPressed(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 50, 15, 150, 150, 150, 255, "aimbot_key", 430);
				spaceX += 25;
				Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "aimbot_weapon_group", 450, g_pDraw.font_menuoptions);
			}
			if (g_pCvar.getValue("aimbot_weapon_group") == 1)
			{
				if (g_pCvar.getValue("page_2") != 1)
				{
					int spaceX = 65;
					spaceX += 25;
					g_pDraw.DrawString(g_pDraw.font_menuoptions, true, g_pCvar.getValue("menu_x") + 108 / 2 + 108, g_pCvar.getValue("menu_y") + 43, 255, 255, 255, 255, "Pistols");

					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "pistol_aimbot_fov", 0, 20, 237);
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "pistol_aimbot_spot", 0, 20, 237);
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "pistol_aimbot_smooth", 1, 20, 237);
					spaceX += 25;
					Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "pistol_aimbot_rcs", 450, g_pDraw.font_menuoptions);
					spaceX += 25;

					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "rifle_aimbot_fov", 0, 20, 237);
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "rifle_aimbot_spot", 0, 20, 237);
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "rifle_aimbot_smooth", 1, 20, 237);
					spaceX += 25;
					Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "rifle_aimbot_rcs", 450, g_pDraw.font_menuoptions);
					spaceX += 25;

					Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "page_2", 450, g_pDraw.font_menuoptions);
					spaceX += 25;
					Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "aimbot_weapon_group", 450, g_pDraw.font_menuoptions);
				}
				if (g_pCvar.getValue("page_2") == 1)
				{
					int spaceX = 65;
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "sniper_aimbot_fov", 0, 20, 237);
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "sniper_aimbot_spot", 0, 20, 237);
					spaceX += 25;
					DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "sniper_aimbot_smooth", 1, 20, 237);
					spaceX += 25;
					Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "sniper_aimbot_rcs", 450, g_pDraw.font_menuoptions);
					spaceX += 25;

					Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "page_2", 450, g_pDraw.font_menuoptions);
				}
			}

		}

		xspace += 108;

		if (iTab == 2)
		{
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + xspace - 108, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 108, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "VISUALS");

			int spaceX = 65;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_active", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_box", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_name", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_health", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_weapon", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_droppedweapons", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_drawspot", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_players", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_bombinfo", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_nade", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_chicken", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "esp_nade_prediction", 450, g_pDraw.font_menuoptions);
		}

		xspace += 108;

		if (iTab == 3)
		{
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + xspace - 108, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 216, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "MISC");

			int spaceX = 65;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "misc_bhop", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "misc_ranks", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "misc_teaminfo", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "misc_autopistol", 450, g_pDraw.font_menuoptions);
			spaceX += 25;
			Checkbox(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, "misc_righthand", 450, g_pDraw.font_menuoptions);

			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + 390, 200, 6, "menu_r", 0, 250, 237);

			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + 255, 200, 6, "menu_g", 0, 250, 237);

			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + 280, 200, 6, "menu_b", 0, 250, 237);
		}

		xspace += 108;

		if (iTab == 4)
		{
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + xspace - 108, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 324, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "COLOURS");

			int spaceX = 65;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_ct_visible_color_r", 0, 250, 237);
			spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_ct_visible_color_g", 0, 250, 237);
			spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_ct_visible_color_b", 0, 250, 237);
			spaceX += 25; spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_t_visible_color_r", 0, 250, 237);
			spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_t_visible_color_g", 0, 250, 237);
			spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_t_visible_color_b", 0, 250, 237);
			spaceX += 25; spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp__color_r", 0, 250, 237);
			spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_text_color_g", 0, 250, 237);
			spaceX += 25;
			DrawSlider(g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + spaceX, 200, 6, "esp_text_color_b", 0, 250, 237);

		}

		xspace += 108;

		if (iTab == 5 && g_pCvar.getValue("esp_players") == 1)
		{
			g_pDraw.FillRGBA(g_pCvar.getValue("menu_x") + xspace - 109, g_pCvar.getValue("menu_y") + 39, 108, 25, g_pCvar.getValue("menu_r"), g_pCvar.getValue("menu_g"), g_pCvar.getValue("menu_b"), 255);
			g_pDraw.DrawString(g_pDraw.font_menuarrows, true, g_pCvar.getValue("menu_x") + 108 / 2 + 432, g_pCvar.getValue("menu_y") +  43, 255, 255, 255, 255, "PLAYERS");
			

			static DWORD dwForPlayerResource = NULL;

			if (dwForPlayerResource == NULL)
				dwForPlayerResource = (DWORD)PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF8\x81\xEC\x00\x00\x00\x00\x83\x3D\x00\x00\x00\x00\x00\x53\x56\x8B\xD9\xC7", "xxxxxxxx????xx?????xxxxx", NULL, NULL) + 0xE;

			DWORD dwPlayerRes = **(PDWORD*)dwForPlayerResource;

			std::vector<player_t> vPlayer;

			CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
			if (pLocal)
			{
				CEngineClient::player_info_t pInfo;

				vPlayer.clear();

				for (int i = 1; i <= g_pEngine->GetMaxClients(); i++)
				{
					CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
					if (!pEntity)
						continue;
					if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
						continue;
					if (pEntity->GetLifeState() != LIFE_ALIVE)
						continue;
					if (!g_pEngine->GetPlayerInfo(i, &pInfo))
						continue;

					player_t player;
					player.cPosition = pEntity->GetPosition();
					player.iWins = pEntity->GetWins(dwPlayerRes, i);
					player.cRank = pEntity->GetRankName(dwPlayerRes, i);
					player.szName = pInfo.name;
					vPlayer.push_back(player);

					for (size_t i = 0; i < vPlayer.size(); i++)
					{
						g_pDraw.DrawString(g_pDraw.font_menuoptions, false, g_pCvar.getValue("menu_x") + 30, g_pCvar.getValue("menu_y") + (i * 20) + 55, 150, 150, 150, 255, "%.15s", vPlayer.at(i).szName.c_str());
						g_pDraw.DrawString(g_pDraw.font_menuoptions, false, g_pCvar.getValue("menu_x") + 180, g_pCvar.getValue("menu_y") + (i * 20) + 55, 150, 150, 150, 255, vPlayer.at(i).cPosition);
						g_pDraw.DrawString(g_pDraw.font_menuoptions, false, g_pCvar.getValue("menu_x") + 280, g_pCvar.getValue("menu_y") + (i * 20) + 55, 150, 150, 150, 255, "Wins: %i", vPlayer.at(i).iWins);
						g_pDraw.DrawString(g_pDraw.font_menuoptions, false, g_pCvar.getValue("menu_x") + 355, g_pCvar.getValue("menu_y") + (i * 20) + 55, 150, 150, 150, 255, vPlayer.at(i).cRank);
					}
				}
			}
		}


	
	}
}