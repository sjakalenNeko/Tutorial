#pragma once

#include "Main.h"

class COther
{
public:
	void Bunnyhop(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal);
	void AutoPistol(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon);
	void RankReveal(CInput::CUserCmd* pUserCmd);
	void AirStuck(CBaseEntity* pLocal, CInput::CUserCmd* pCmd);
	void TeamInfo(CBaseEntity* pLocal);
	void RightHand(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon);
};

extern COther g_pOther;