#include "CVar.h"

// CREDITS TO FRIEND, NOT ME

CVarSystem g_pCvar;

void CVarSystem::Init()
{

	g_pCvar.addCvar("aimbot_active", 1, false);
	g_pCvar.addCvar("aimbot_key", 1, false);
	g_pCvar.addCvar("aimbot_fov", 4, false);
	g_pCvar.addCvar("aimbot_weapon_group", 0, false);
	g_pCvar.addCvar("aimbot_distance_fov", 1, false);
	g_pCvar.addCvar("aimbot_spot", 0, false);
	g_pCvar.addCvar("aimbot_smooth", 8, false);
	g_pCvar.addCvar("aimbot_rcs", 1, false);
	g_pCvar.addCvar("aimbot_humanize", 1, false);
	//g_pCvar.addCvar("aimbot_silent", 0, false);
	g_pCvar.addCvar("esp_drawspot", 0, false);

	g_pCvar.addCvar("pistol_aimbot_spot", 0, false);
	g_pCvar.addCvar("pistol_aimbot_smooth", 8, false);
	g_pCvar.addCvar("pistol_aimbot_fov", 4, false);
	g_pCvar.addCvar("pistol_aimbot_rcs", 4, false);

	g_pCvar.addCvar("pistol_aimbot_key", 1, false);

	g_pCvar.addCvar("rifle_aimbot_spot", 0, false);
	g_pCvar.addCvar("rifle_aimbot_smooth", 8, false);
	g_pCvar.addCvar("rifle_aimbot_fov", 4, false);
	g_pCvar.addCvar("rifle_aimbot_key", 1, false);
	g_pCvar.addCvar("rifle_aimbot_rcs", 4, false);

	g_pCvar.addCvar("sniper_aimbot_spot", 0, false);
	g_pCvar.addCvar("sniper_aimbot_smooth", 8, false);
	g_pCvar.addCvar("sniper_aimbot_fov", 4, false);
	g_pCvar.addCvar("sniper_aimbot_key", 1, false);
	g_pCvar.addCvar("sniper_aimbot_rcs", 4, false);

	g_pCvar.addCvar("page_2",0 , false);







	g_pCvar.addCvar("esp_active", 1, false);
	g_pCvar.addCvar("esp_box", 1, false);
	g_pCvar.addCvar("esp_name", 1, false);
	g_pCvar.addCvar("esp_health", 1, false);
	g_pCvar.addCvar("esp_weapon", 1, false);
	g_pCvar.addCvar("esp_droppedweapons", 0, false);
	g_pCvar.addCvar("esp_players", 1, false);
	g_pCvar.addCvar("esp_bombinfo", 1, false);
	g_pCvar.addCvar("esp_nade", 1, false);
	g_pCvar.addCvar("esp_chicken", 0, false);
	g_pCvar.addCvar("esp_nade_prediction", 0, false);

	g_pCvar.addCvar("trigger_active", 1, false);
	g_pCvar.addCvar("trigger_key", 5, false);
	g_pCvar.addCvar("trigger_overshoot", 0, false);

	g_pCvar.addCvar("check_smoke", 1, false);

	g_pCvar.addCvar("misc_bhop", 1, false);
	g_pCvar.addCvar("misc_autopistol", 1, false);
	g_pCvar.addCvar("misc_ranks", 1, false);
	//g_pCvar.addCvar("misc_airstuck", 0, false);
	//g_pCvar.addCvar("misc_airstuck_key", 0, false);
	g_pCvar.addCvar("misc_teaminfo", 0, false);
	g_pCvar.addCvar("misc_righthand", 1, false);

	g_pCvar.addCvar("menu_x", 500, false);
	g_pCvar.addCvar("menu_y", 300, false);

	g_pCvar.addCvar("menu_r", 0, false);
	g_pCvar.addCvar("menu_g", 150, false);
	g_pCvar.addCvar("menu_b", 255, false);

	g_pCvar.addCvar("esp_ct_visible_color_r", 50, false);
	g_pCvar.addCvar("esp_ct_visible_color_g", 200, false);
	g_pCvar.addCvar("esp_ct_visible_color_b", 100, false);

	g_pCvar.addCvar("esp_ct_invisible_color_r", 0, false); 
	g_pCvar.addCvar("esp_ct_invisible_color_g", 150, false);
	g_pCvar.addCvar("esp_ct_invisible_color_b", 255, false);

	g_pCvar.addCvar("esp_t_visible_color_r", 50, false);
	g_pCvar.addCvar("esp_t_visible_color_g", 200, false);
	g_pCvar.addCvar("esp_t_visible_color_b", 100, false);

	g_pCvar.addCvar("esp_t_invisible_color_r", 150, false); 
	g_pCvar.addCvar("esp_t_invisible_color_g", 50, false);
	g_pCvar.addCvar("esp_t_invisible_color_b", 50, false);

	g_pCvar.addCvar("esp_text_color_r", 255, false);
	g_pCvar.addCvar("esp_text_color_g", 255, false);
	g_pCvar.addCvar("esp_text_color_b", 255, false);
}

bool CVarSystem::IsActive()
{
	if (!bActive)
		return false;
	else
		return true;
}

char* stringToLower(char *string)
{
	int len = strlen(string);

	for (int i = 0; i < len; i++)
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
			string[i] += 32;
	}

	return string;
}

bool bIsDigitInString(std::string pszString)
{
	for (int ax = 0; ax <= 9; ax++)
	{
		char buf[MAX_PATH];
		_snprintf(buf, (size_t)255, "%d", ax);

		if (strstr(pszString.c_str(), buf))
			return true;
	}

	return false;
}

void CVarSystem::addCvar(char *szName, int iValue, bool bStyle)
{
	CRetVar buf = CRetVar(szName, iValue, bStyle);
	vars.push_back(buf);
}

int CVarSystem::getValue(const char* szName)
{
	for (int ax = 0; ax < vars.size(); ax++)
	{
		if (vars[ax].szName == szName)
			return vars[ax].iValue;
	}

	return 0;
}

void CVarSystem::setValue(const char* szName, int szValue)
{
	for (int ax = 0; ax < vars.size(); ax++)
	{
		if (vars[ax].szName == szName)
			vars[ax].iValue = szValue;
	}
}

void CVarSystem::HandleCommands(std::string szCommand)
{
	if (szCommand.empty())
		return;

	int r = getValue("printfont_r");
	int g = getValue("printfont_g");
	int b = getValue("printfont_b");

	char szCommandBuffer[512] = "";
	strcpy(szCommandBuffer, szCommand.c_str());

	szCommand = stringToLower(szCommandBuffer);

	if (strcmp(szCommand.c_str(), "help") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].bStyle == true)
				continue;
		}

		return;
	}

	std::string szCmd, szValue;
	int iValue;
	size_t nPos;

	bool isDigitInString = bIsDigitInString(szCommand);
	bool isTextCmd = strstr(szCommand.c_str(), "echo") || strstr(szCommand.c_str(), "exec") || strstr(szCommand.c_str(), "save");
	if (isDigitInString || isTextCmd)
	{
		nPos = szCommand.find_first_of(" ");

		if (nPos != std::string::npos)
		{
			szCmd = szCommand.substr(0, nPos);
			szCommand.erase(0, nPos + 1);

			if (szCommand.length() > 0)
				szValue = szCommand;
		}
	}

	if (strcmp(szCmd.c_str(), "echo") == 0)
	{
		// print(r, g, b, szValue.c_str());
		return;
	}
	if (strcmp(szCmd.c_str(), "exec") == 0)
	{
		readConfig(szValue.c_str());
	}
	if (strcmp(szCmd.c_str(), "save") == 0)
	{
		saveConfig(szValue.c_str());
	}

	iValue = atoi(szValue.c_str());

	for (int ax = 0; ax < vars.size(); ax++)
	{
		if (strcmp(vars[ax].szName.c_str(), szCmd.c_str()) == 0)
		{
			vars[ax].iValue = iValue;

			if (vars[ax].bStyle == true)
				continue;
		}
	}
}

void CVarSystem::readConfig(const char* szName)
{
	std::string line;
	std::string crtlDir = "C:\\";
	std::string path = crtlDir + szName + ".cfg";

	std::fstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (strstr(line.c_str(), "//"))
				continue;

			HandleCommands(line);
		}

		myfile.close();
	}
}
void CVarSystem::saveConfig(const char* szName)
{
	std::string line;
	std::string crtlDir = "C:\\";
	std::string path = crtlDir + szName + ".cfg";

	std::fstream myfile(path, std::ios::out);
	if (myfile.is_open())
	{
		myfile.clear();

		for (int ax = 0; ax < vars.size(); ax++)
		{
			std::string cmd = vars[ax].szName + " " + std::to_string(vars[ax].iValue) + "\n";
			myfile << cmd;
		}

		myfile.close();
	}
}