#pragma once

#include "Main.h"

class CTrigger
{
public:
	void Trigger(CInput::CUserCmd* pCmd, CBaseEntity* pLocal);
};

extern CTrigger g_pTrigger;