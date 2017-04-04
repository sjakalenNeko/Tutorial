#pragma once

#include "Main.h"

class CRetVar
{
public:
	CRetVar(std::string szName, int iValue, bool bStyle)
	{
		this->szName = szName;
		this->iValue = iValue;
		this->bStyle = bStyle;
	}

	std::string szName;
	int iValue;
	bool bPrinted;
	bool bSelected;
	bool bStyle;
};

class CVarSystem
{
public:
	std::string command;
	void Init();
	void HandleKeys(int key);
	void HandleCommands(std::string szCommand);
	bool IsActive();
	void InitCommands();
	void addCvar(char* szName, int iValue, bool bStyle);
	int getValue(const char* szName);
	void setValue(const char* szName, int szValue);
	void readConfig(const char* szName);
	void saveConfig(const char* szName);
	std::vector<CRetVar> vars;
private:
	std::vector<std::string> output, autoComplete;
	int counter, selected, iPrintCounter;
	std::string buf;
	BOOL bActive, bComplete;
	int selbuf;
};

extern CVarSystem g_pCvar;