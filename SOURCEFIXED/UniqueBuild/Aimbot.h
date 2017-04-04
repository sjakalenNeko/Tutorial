#pragma once

#include "Main.h"

class CAim
{
public:
	CBaseCombatWeapon* GetActiveWeapon(CBaseEntity *pEntity);
	Vector Randomize(Vector vAngles);
	void doAim(CInput::CUserCmd *pCmd, CBaseEntity *pLocal, CBaseCombatWeapon *pWeapon);

	void ResetRCS()
	{
		iRCSTarget = -1;
		fBestRCSTarget = 99999.9f;
		vRCSTarget.Init(0.0f, 0.0f, 0.0f);
		vRCSFinal.Init(0.0f, 0.0f, 0.0f);
	}

	bool HasTargetRCS()
	{
		return (iRCSTarget != -1);
	}

	int iRCSTarget;
	float fBestRCSTarget;
	Vector vRCSTarget;
	Vector vRCSFinal;

	float flX;
	float flY;
	float flTargetDestX;
	float flTargetDestY;
	float flCurrentX;
	float flCurrentY;
};

extern CAim g_pAim;