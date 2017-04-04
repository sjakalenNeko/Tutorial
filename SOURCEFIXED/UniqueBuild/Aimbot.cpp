#include "Aimbot.h"

CAim g_pAim;

CBaseCombatWeapon* CAim::GetActiveWeapon(CBaseEntity *pEntity)
{
	ULONG hHandle = (ULONG)*(PDWORD)((DWORD)pEntity + Offsets::Player::m_hActiveWeapon);
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_pEntList->GetClientEntityFromHandle(hHandle);
	return pWeapon;
}

void Smooth(CInput::CUserCmd *pCmd, Vector& vAim, const char *var)
{
	Vector vDelta = pCmd->viewangles - vAim;
	g_pTools.NormalizeVector(vDelta);

	Vector NormalizedSmooth = pCmd->viewangles - vDelta / g_pCvar.getValue(var) * 0.5;
	g_pTools.NormalizeVector(NormalizedSmooth);

	vAim = NormalizedSmooth;
}

void RecoilControl(Vector& vecPunchAngles, Vector& vecAimAngles)
{
	vecPunchAngles *= 2.f;

	float fLength = g_pMath.VectorNormalize(vecPunchAngles);
	fLength -= (10.f + fLength * 0.5f) * g_pGlobalVars->interval_per_tick;
	fLength = max(fLength, 0.f);
	vecPunchAngles *= fLength;

	g_pTools.NormalizeVector(vecPunchAngles);
	g_pTools.ClampAngle(vecPunchAngles);
	vecAimAngles -= vecPunchAngles;
}

float GetFoV(Vector vLocalOrigin, Vector vPosition, Vector vForward)
{
	Vector vLocal;
	VectorSubtract(vPosition, vLocalOrigin, vLocal);
	vLocal.NormalizeInPlace();

	float fValue = vForward.Dot(vLocal);
	if (fValue < -1.0f)
		fValue = -1.0f;
	if (fValue > 1.0f)
		fValue = 1.0f;

	return RAD2DEG(acos(fValue));
}

Vector CAim::Randomize(Vector vAngles)
{
	if (abs(flCurrentX - flTargetDestX) < .05f)
	{
		flTargetDestX = rand() % (int)(30 * 10) + 1;
		flTargetDestX /= 500;

		int iRand = rand() % 2 + 1;
		if (iRand == 2)
			flTargetDestX = -flTargetDestX;
	}

	if (abs(flCurrentY - flTargetDestY) < .05f)
	{
		flTargetDestY = rand() % (int)(30 * 10) + 1;
		flTargetDestY /= 500;

		int iRand = rand() % 2 + 1;
		if (iRand == 2)
			flTargetDestY = -flTargetDestY;
	}

	flCurrentX += (flTargetDestX - flCurrentX) / 2;
	flCurrentY += (flTargetDestY - flCurrentY) / 2;

	vAngles.x += flCurrentY;
	vAngles.y += flCurrentY;

	flX = flCurrentX;
	flY = flCurrentY;

	return vAngles;
}


bool bIsPistol()
{


}

void CAim::doAim(CInput::CUserCmd* pCmd, CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon)
{
	if (g_pCvar.getValue("aimbot_weapon_group") == 1)
	{
		if (pWeapon->IsPistol())
		{
		
			g_pCvar.setValue("aimbot_fov", g_pCvar.getValue("pistol_aimbot_fov"));
			g_pCvar.setValue("aimbot_smooth", g_pCvar.getValue("pistol_aimbot_smooth"));
			g_pCvar.setValue("aimbot_spot", g_pCvar.getValue("pistol_aimbot_spot"));
			g_pCvar.setValue("aimbot_rcs", g_pCvar.getValue("pistol_aimbot_rcs"));
		}

		if (pWeapon->IsAutomatic())
		{
			
			g_pCvar.setValue("aimbot_fov", g_pCvar.getValue("rifle_aimbot_fov"));
			g_pCvar.setValue("aimbot_smooth", g_pCvar.getValue("rifle_aimbot_smooth"));
			g_pCvar.setValue("aimbot_spot", g_pCvar.getValue("rifle_aimbot_spot"));
			g_pCvar.setValue("aimbot_rcs", g_pCvar.getValue("rifle_aimbot_rcs"));
		}
		if (pWeapon->IsSniper())
		{
	
			g_pCvar.setValue("aimbot_fov", g_pCvar.getValue("sniper_aimbot_fov"));
			g_pCvar.setValue("aimbot_smooth", g_pCvar.getValue("sniper_aimbot_smooth"));
			g_pCvar.setValue("aimbot_spot", g_pCvar.getValue("sniper_aimbot_spot"));
			g_pCvar.setValue("aimbot_rcs", g_pCvar.getValue("sniper_aimbot_rcs"));
		}


	}

	if (!GetAsyncKeyState(g_pCvar.getValue("aimbot_key")))
		return;

	if (pWeapon->IsOther() || pWeapon->IsGrenade() || pWeapon->IsKnife())
		return;

	static Vector vClientViewAngles;
	g_pEngine->GetViewAngles(vClientViewAngles);

	static Vector vAngle;
	g_pMath.AngleVectors(vClientViewAngles, vAngle);

	ResetRCS();

	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
		if (!pEntity)
			continue;
		if (pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (pEntity->IsProtected())
			continue;
		if (pEntity->GetClientClass()->GetClassID() != CCSPlayer)
			continue;
		if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
			continue;
		if (!g_pMath.GetHitboxPosition(g_pCvar.getValue("aimbot_spot"), vRCSTarget, pLocal->GetAbsAngles(), i))
			continue;
		if (!g_pTools.IsVisible(pLocal->GetEyePosition(), vRCSTarget, pEntity))
			continue;
		if (g_pCvar.getValue("check_smoke") == 1 && g_pTools.IsBehindSmoke(pEntity))
			continue;

		float fCurrentFOV = GetFoV(pLocal->GetEyePosition(), vRCSTarget, vAngle);
		if (fBestRCSTarget < fCurrentFOV)
			continue;

		fBestRCSTarget = fCurrentFOV;
		vRCSFinal = vRCSTarget;
		iRCSTarget = i;
	}

	if (HasTargetRCS())
	{
		float fLen = Vector(vRCSFinal - pLocal->GetEyePosition()).Length();

		Vector vAngle;
		g_pMath.CalcAngle(pLocal->GetEyePosition(), vRCSFinal, vAngle);
		g_pTools.NormalizeVector(vAngle);

		if (g_pCvar.getValue("aimbot_rcs") == 1)
		{
			Vector vPunchangle = pLocal->vecGetPunchAngle();

			if (pWeapon->GetWeaponID() != WEAPON_DEAGLE)
				RecoilControl(vPunchangle, vAngle);

			g_pTools.NormalizeVector(vAngle);
		}

		static Vector vForward;
		g_pMath.AngleVectors(vAngle, vForward);
		vForward = (vForward * fLen) + pLocal->GetEyePosition();

		if (g_pMath.GetFov2(pCmd->viewangles, pLocal->GetEyePosition(), vForward, g_pCvar.getValue("aimbot_distance_fov")) <= g_pCvar.getValue("aimbot_fov"))
		{
			if (g_pCvar.getValue("aimbot_randomize") == 1)
				Randomize(vAngle);

			Smooth(pCmd, vAngle, "aimbot_smooth");

			g_pTools.ClampAngle(vAngle);
			g_pTools.NormalizeVector(vAngle);

			g_pEngine->SetViewAngles(vAngle);

			/*if (g_pCvar.getValue("aimbot_silent") == 1)
				pCmd->viewangles = vAngle;*/
		}
	}
}