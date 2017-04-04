#include "Other.h"

COther g_pOther;

void COther::Bunnyhop(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal)
{
	static bool bLastJumped = false;
	static bool bShouldFake = false;

	if (!bLastJumped && bShouldFake)
	{
		bShouldFake = false;
		pUserCmd->buttons |= IN_JUMP;
	}
	else if (pUserCmd->buttons & IN_JUMP)
	{
		if (pLocal->GetFlags() & FL_ONGROUND)
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			pUserCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}

void COther::AutoPistol(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon)
{
	if (pWeapon->GetWeaponID() == WEAPON_DEAGLE)
		return;

	if (!pWeapon->IsPistol())
		return;

	if (pWeapon->GetClip1() == 0)
		return;

	if (pUserCmd->buttons & IN_ATTACK)
	{
		float flServerTime = (float)pLocal->GetTickBase() * g_pGlobalVars->interval_per_tick;
		float flNextPrimaryAttack = pWeapon->GetNextPrimaryAttack();

		if (flNextPrimaryAttack > flServerTime)
			pUserCmd->buttons &= ~IN_ATTACK;
	}
}

void COther::RankReveal(CInput::CUserCmd* pUserCmd)
{
	using RevealAllFn = void(*)(int);
	static RevealAllFn fnReveal = (RevealAllFn)PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????", NULL, NULL);

	int iBuffer[1];

	if (pUserCmd->buttons & IN_SCORE)
		fnReveal(iBuffer[1]);
}

/* void COther::AirStuck(CBaseEntity* pLocal, CInput::CUserCmd* pCmd)
{
	if (!(pCmd->buttons & IN_ATTACK) && !(pLocal->GetFlags() & FL_ONGROUND))
	{
		static bool bStuck = false;
		if (GetAsyncKeyState(g_pCvar.getValue("misc_airstuck_key")) & 1)
			bStuck = !bStuck;

		if (bStuck)
			pCmd->tick_count = 0xFFFFFF;
	}
} */

void COther::TeamInfo(CBaseEntity* pLocal)
{
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
		if (!pEntity)
			continue;
		if (pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (pEntity->GetClientClass()->GetClassID() != CCSPlayer)
			continue;
		if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
			continue;

		CEngineClient::player_info_t pInfo;
		if (g_pEngine->GetPlayerInfo(i, &pInfo))
		{
			if (pInfo.name == "GOTV" || pInfo.name == "")
				continue;

			char szCmd[256];
			sprintf(szCmd, "say_team \"%s is at %s\"", pInfo.name, pEntity->GetPosition());

			g_pEngine->ClientCmd(szCmd);
		}
	}
}

void COther::RightHand(CBaseEntity * pLocal, CBaseCombatWeapon * pWeapon)
{
	char szCmd[256];
	int bRight = -1;

	 (pWeapon->IsKnife() || pWeapon->IsGrenade()) ? bRight = 1 : bRight = 0;

	sprintf(szCmd, "cl_righthand %i", bRight);

	g_pEngine->ExecuteClientCmd(szCmd);

}

