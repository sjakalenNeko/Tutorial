#include "CreateMove.h"

void __fastcall CreateMoveHook(void* thisptr, int edx, int sequence_number, float input_sample_frametime, bool active)
{
	typedef void(__fastcall *original)(void*, int, int, float, bool);
	g_phkCreateMove->GetMethod<original>(21)(thisptr, edx, sequence_number, input_sample_frametime, active);

	CInput::CUserCmd* pCmd = g_pInput->GetUserCmd(0, sequence_number);
	if (!pCmd)
		return;

	CInput::CVerifiedUserCmd *g_pVerifiedCommands = *(CInput::CVerifiedUserCmd**)((DWORD)g_pInput + VERIFIEDCMDOFFSET);
	CInput::CVerifiedUserCmd *pVerified = &g_pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
	if (!pVerified)
		return;

	if (g_pCvar.getValue("misc_ranks") == 1)
		g_pOther.RankReveal(pCmd);

	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
	if (pLocal && pLocal->GetLifeState() == LIFE_ALIVE)
	{
		if (g_pCvar.getValue("misc_bhop") == 1)
			g_pOther.Bunnyhop(pCmd, pLocal);

		/* if (g_pCvar.getValue("misc_airstuck") == 1)
			g_pOther.AirStuck(pLocal, pCmd); */

		if (g_pCvar.getValue("misc_teaminfo") == 1)
			g_pOther.TeamInfo(pLocal);

		CBaseCombatWeapon* pWeapon = g_pAim.GetActiveWeapon(pLocal);
		if (pWeapon)
		{
			if (g_pCvar.getValue("trigger_active") == 1)
				g_pTrigger.Trigger(pCmd, pLocal);

			if (g_pCvar.getValue("aimbot_active") == 1)
				g_pAim.doAim(pCmd, pLocal, pWeapon);

			if (g_pCvar.getValue("misc_autopistol") == 1)
				g_pOther.AutoPistol(pCmd, pLocal, pWeapon);

			if (g_pCvar.getValue("misc_righthand") == 1)
				g_pOther.RightHand(pLocal, pWeapon);
		}
	}

	g_pTools.NormalizeVector(pCmd->viewangles);
	g_pTools.ClampAngle(pCmd->viewangles);

	pVerified->m_cmd = *pCmd;
	pVerified->m_crc = pCmd->GetChecksum();
}