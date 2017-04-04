#pragma once

#pragma warning(disable: 4244)
#pragma warning(disable: 4409)
#pragma warning(disable: 4800)
#pragma warning(disable: 4018)
#pragma warning(disable: 4305)
#pragma warning(disable: 4127)
#pragma warning(disable: 4552)

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <psapi.h>
#include <Mmsystem.h>
#include <process.h>
#include <vector>
#include <map>
#include <ostream>
#include <Shlobj.h>
#include <math.h>
#include <timeapi.h>

#include "Vector.h"
#include "checksum_crc.h"
#include "VMTStuff.h"
#include "SDK.h"
#include "NetVar.h"
#include "Math.h"
#include "Drawing.h"
#include "CVar.h"

#include "CreateMove.h"
#include "PaintTraverse.h"
//#include "PlaySound.h"

#include "GUI.h"
#include "Tools.h"
#include "Aimbot.h"
#include "Triggerbot.h"
#include "Other.h"
#include "Wallhack.h"

extern HLCLient* g_pClient;
extern CEngineClient* g_pEngine;
extern ISurface* g_pSurface;
extern IPanel* g_pPanel;
extern CEntityList* g_pEntList;
extern CInput* g_pInput;
extern CGlobalVars* g_pGlobalVars;
extern CModelInfo* g_pModel;
extern CTrace* g_pEngineTrace;
extern CDebugOverlay* g_pDebugOverlay;