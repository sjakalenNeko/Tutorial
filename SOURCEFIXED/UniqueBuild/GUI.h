#pragma once

#include "Main.h"

class CGui
{
public:
	struct sComboBox
	{
		bool Open, Active;
		int iSelect;
		char* Name;
	} cComboBox[21];

	bool cursor, incombo, inkeypressed, ininsertnumber;
	int cursorposition[2];
public:
	void LoadConfig();
	void SaveConfig();
	CGui();
	void Mouse();
	void GetMouse();
	bool MouseOver(int x, int y, int w, int h);
	bool LeftClick(int x, int y, int w, int h);
	void DrawCombobox(int x, int y, const char* var, int num, int max, std::string* structs, int distance);
	void DrawSlider(int x, int y, int w, int h, const char* var, int min, int max, int distance);
	void Slider(int x, int y, int w, int h, int min, int max, const char* cvar, int r, int g, int b, int a);
	void GetKeyPressed(int x, int y, int w, int h, int r, int g, int b, int a, const char* cvar, int distance);
	void GetNumbersInsert(int x, int y, int w, int h, int r, int g, int b, int a, const char* cvar, int distance);
	void DragMenu(const char* x, const char* y, int w, int h, int& xdif, int& ydif);
	void DrawMenu();
private:
	bool bLeftClick, bRightClick, bLeftClickRelease, bRightClickRelease;
};

extern CGui g_pGui;