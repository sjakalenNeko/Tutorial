#include "Wallhack.h"

CWallhack g_pWallhack;

void BoundingBox(CBaseEntity* pEntity, int r, int g, int b, int a, const char* name)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)pEntity + Offsets::Entity::m_rgflCoordinateFrame);

	Vector min = *(Vector*)((DWORD)pEntity + Offsets::Entity::m_Collision + Offsets::Entity::m_vMins);
	Vector max = *(Vector*)((DWORD)pEntity + Offsets::Entity::m_Collision + Offsets::Entity::m_vMaxs);

	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	Vector pointsTransformed[8];

	for (int i = 0; i < 8; i++)
		g_pMath.VectorTransform(points[i], trans, pointsTransformed[i]);

	Vector flb;
	Vector brt;
	Vector blb;
	Vector frt;
	Vector frb;
	Vector brb;
	Vector blt;
	Vector flt;

	if (!g_pDebugOverlay->ScreenPosition(pointsTransformed[3], flb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[5], brt) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[0], blb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[4], frt) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[2], frb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[1], brb) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[6], blt) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[7], flt) != 1)
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bot = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bot < arr[i].y)
			bot = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	float h = (bot - top);
	float w = h / 2;

	g_pDraw.LineRGBA(left, top, right, top, r, g, b, a);
	g_pDraw.LineRGBA(left - 1, top - 1, right + 1, top - 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(right, bot, left, bot, r, g, b, a);
	g_pDraw.LineRGBA(right + 1, bot + 1, left - 1, bot + 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(left, bot, left, top, r, g, b, a);
	g_pDraw.LineRGBA(left - 1, bot + 1, left - 1, top - 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(right, top, right, bot, r, g, b, a);
	g_pDraw.LineRGBA(right + 1, top - 1, right + 1, bot + 1, 0, 0, 0, a);

	g_pDraw.DrawString(g_pDraw.esp_font, true, left + w, top - 15, r, g, b, a, name);
}

void DrawEntityESP(CBaseEntity* pEntity)
{
	if (pEntity->GetAbsAngles().x == 0.f && pEntity->GetAbsAngles().z == 0.f)
		return;

	std::string szCurrenModelName = g_pModel->GetModelName(pEntity->GetModel());
	if (szCurrenModelName.find("dropped", 0) != std::string::npos)
	{
		szCurrenModelName.erase(0, szCurrenModelName.find_first_of("_", std::string("abc").length()) + 1);
		szCurrenModelName.erase(szCurrenModelName.find_last_of("_"), 12);

		if (!strcmp(szCurrenModelName.c_str(), "ied"))
			szCurrenModelName = "C4";
		else if (!strcmp(szCurrenModelName.c_str(), "223"))
			szCurrenModelName = "USP-S";
		else if (!strcmp(szCurrenModelName.c_str(), "75"))
			szCurrenModelName = "CZ75";
		else if (!strcmp(szCurrenModelName.c_str(), "s"))
			szCurrenModelName = "M4A1-S";

		BoundingBox(pEntity, 255, 255, 255, 255, szCurrenModelName.c_str());
	}
}

void DrawHead(CBaseEntity* pLocal, int pEntityIndex, CBaseEntity* pEntity)
{
	Vector vPlayer;
	g_pMath.GetHitboxPosition(g_pCvar.getValue("aimbot_spot"), vPlayer, pLocal->GetAbsAngles(), pEntityIndex);

	Vector vHead;
	if (g_pDebugOverlay->ScreenPosition(vPlayer, vHead) != 1)
	{
		g_pDraw.FillRGBA(vHead.x, vHead.y, 4, 4, 255, 255, 255, 255);
		g_pDraw.DrawOutlineRect(vHead.x, vHead.y, 4, 4, 0, 0, 0, 255);
	}
}

__forceinline float DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void PredictNade(CBaseEntity* pLocal)
{
	const float TIMEALIVE = 5.f;
	const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

	float fStep = 0.1f;
	float fGravity = 800.0f / 8.f;

	Vector vPos, vThrow, vThrow2;
	Vector vStart;

	int iCollisions = 0;

	Vector vViewAngles;
	g_pEngine->GetViewAngles(vViewAngles);

	vThrow[0] = vViewAngles[0];
	vThrow[1] = vViewAngles[1];
	vThrow[2] = vViewAngles[2];

	if (vThrow[0] < 0)
		vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
	else
		vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

	float fVel = (90 - vThrow[0]) * 4;
	if (fVel > 500)
		fVel = 500;

	g_pMath.AngleVectors(vThrow, vThrow2);

	Vector vEye = pLocal->GetEyePosition();
	vStart[0] = vEye[0] + vThrow2[0] * 16;
	vStart[1] = vEye[1] + vThrow2[1] * 16;
	vStart[2] = vEye[2] + vThrow2[2] * 16;

	vThrow2[0] = (vThrow2[0] * fVel) + pLocal->GetAbsVelocity()[0];
	vThrow2[1] = (vThrow2[1] * fVel) + pLocal->GetAbsVelocity()[1];
	vThrow2[2] = (vThrow2[2] * fVel) + pLocal->GetAbsVelocity()[2];	// casualhacker for da magic calc help

	for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
	{
		vPos = vStart + vThrow2 * fStep;

		CTrace::Ray_t ray;
		CTrace::trace_t tr;
		CTrace::CTraceFilter loc;
		loc.pSkip = pLocal;

		ray.Init(vStart, vPos);
		g_pEngineTrace->TraceRay(ray, MASK_SOLID, &loc, &tr);

		if (tr.DidHit())
		{
			vThrow2 = tr.plane.normal * -2.0f * DotProduct(vThrow2, tr.plane.normal) + vThrow2;
			vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

			iCollisions++;
			if (iCollisions > 2)
				break;

			vPos = vStart + vThrow2 * tr.fraction * fStep;
			fTime += (fStep * (1 - tr.fraction));
		}

		Vector vOutStart, vOutEnd;

		if (g_pDebugOverlay->ScreenPosition(vStart, vOutStart) != 1, g_pDebugOverlay->ScreenPosition(vPos, vOutEnd) != 1)
			g_pDraw.LineRGBA(vOutStart.x, vOutStart.y, vOutEnd.x, vOutEnd.y, 255, 255, 255, 255);

		vStart = vPos;
		vThrow2.z -= fGravity * tr.fraction * fStep;
	}
}

void Chicken(CBaseEntity* pEntity, int iIndex)
{
	if (pEntity->GetClientClass()->GetClassID() == CChicken)
		BoundingBox(pEntity, 50, 150, 200, 255, "Chicken");
}

void Bomb(CBaseEntity* pEntity)
{
	Vector vPlayer, vScreen;

	if (pEntity->GetClientClass()->GetClassID() == CPlantedC4)
	{
		if (pEntity->GetIsTicking())
		{
			float flBombTimer = pEntity->GetBombTimer();
			float flTimeLeft = (g_pGlobalVars->curtime - flBombTimer) * -1;
			if (flTimeLeft < 0)
				flTimeLeft = 0;

			vPlayer = pEntity->GetAbsOrigin();
			if (g_pDebugOverlay->ScreenPosition(vPlayer, vScreen) != 1)
				g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y, 255, 255, 255, 255, "%2.0f Seconds", flTimeLeft);
		}
	}

	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pDefuser = g_pEntList->GetClientEntity(i);
		if (!pDefuser)
			continue;
		if (pDefuser->IsDormant())
			continue;
		if (pDefuser->GetLifeState() != LIFE_ALIVE)
			continue;

		if (pDefuser->isDefusing() && pEntity->GetClientClass()->GetClassID() == CPlantedC4)
		{
			if (pEntity->GetIsTicking())
			{
				float flDefuseTimer = pEntity->GetDefuseTimer();

				float TimeLeft = (g_pGlobalVars->curtime - flDefuseTimer) * -1;

				if (TimeLeft < 0)
					TimeLeft = 0;

				vPlayer = pEntity->GetAbsOrigin();

				if (g_pDebugOverlay->ScreenPosition(vPlayer, vScreen) != 1 && TimeLeft > 0)
				{
					if (pDefuser->hasDefuse() == 0)
						g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y + 8, 0, 255, 0, 255, "%2.0f without Kit", TimeLeft);
					else
						g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y + 8, 255, 255, 0, 255, "%2.0f with Kit", TimeLeft);
				}
			}
		}
	}
}

void DrawGrenades(CBaseEntity* pEntity)
{
	Vector vGrenadePos2D = Vector(0.f, 0.f, 0.f);
	Vector vGrenadePos3D = Vector(0.f, 0.f, 0.f);

	float fGrenadeModelSize = 0.0f;

	Color colGrenadeColor = Color(0, 0, 0, 0);

	char* szModelName = "";

	int ClassID = pEntity->GetClientClass()->GetClassID();
	if (ClassID == 9 || ClassID == 95 || ClassID == 86 || ClassID == 41 || ClassID == 23 || ClassID == 130)
	{
		const model_t* pModel = pEntity->GetModel();
		if (pModel)
		{
			studiohdr_t* pHdr = g_pModel->GetStudiomodel(pModel);
			if (pHdr)
			{
				std::string grenades = g_pModel->GetModelName(pModel);
				std::string grenade = g_pModel->GetModelName(pEntity->GetModel());

				if (grenade.find("_thrown", 0) != std::string::npos || grenade.find("dropped", 0) != std::string::npos)
				{
					if (!(grenade.find("w_eq", 0) != std::string::npos) || (grenade.find("taser", 0) != std::string::npos) || (grenade.find("defuser", 0) != std::string::npos) || (grenade.find("multimeter", 0) != std::string::npos))
						return;

					vGrenadePos3D = pEntity->GetAbsOrigin();
					fGrenadeModelSize = sqrt(pHdr->hull_max.DistToSqr(pHdr->hull_min));

					if (g_pDebugOverlay->ScreenPosition(vGrenadePos3D, vGrenadePos2D) == 1)
						return;

					if (grenade.find("flash") != std::string::npos)
					{
						colGrenadeColor = Color(255, 255, 0, 255);

						szModelName = "Flash";
					}
					if (grenade.find("incendiarygrenade") != std::string::npos || grenade.find("molotov") != std::string::npos || grenade.find("fraggrenade") != std::string::npos)
					{
						colGrenadeColor = Color(255, 0, 0, 255);

						if (grenade.find("incendiarygrenade") != std::string::npos)
							szModelName = "Inc Grenade";
						if (grenade.find("molotov") != std::string::npos)
							szModelName = "Molotov";
						if (grenade.find("fraggrenade") != std::string::npos)
							szModelName = "HE Grenade";
					}
					if (grenade.find("smoke") != std::string::npos || grenade.find("decoy") != std::string::npos)
					{
						colGrenadeColor = Color(0, 255, 0, 255);

						if (grenade.find("smoke") != std::string::npos)
							szModelName = "Smoke";
						if (grenade.find("decoy") != std::string::npos)
							szModelName = "Decoy";
					}

					g_pDraw.DrawString(g_pDraw.esp_font, true, vGrenadePos2D.x, vGrenadePos2D.y + 15, colGrenadeColor.r(), colGrenadeColor.g(), colGrenadeColor.b(), 255, szModelName);
				}
			}
		}
	}
}

void CWallhack::doDraw()
{
	if (g_pEngine->isinGame())
	{
		CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
		if (!pLocal)
			return;

		CBaseCombatWeapon* pWeapon = g_pAim.GetActiveWeapon(pLocal);
		if (pWeapon && pWeapon->IsGrenade() && g_pCvar.getValue("esp_nade_prediction") == 1)
			PredictNade(pLocal);

		for (int i = 1; i < g_pEntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
			if (!pEntity)
				continue;

			if (g_pCvar.getValue("esp_nade") == 1)
				DrawGrenades(pEntity);

			if (g_pCvar.getValue("esp_bombinfo") == 1)
				Bomb(pEntity);

			if (g_pCvar.getValue("esp_chicken") == 1)
				Chicken(pEntity, i);

			if (g_pCvar.getValue("esp_droppedweapons") == 1)
				DrawEntityESP(pEntity);

			if (pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
				continue;
			if (pEntity->GetClientClass()->GetClassID() != CCSPlayer)
				continue;
			if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
				continue;

			Vector vScreenBot, vScreenTop;
			Vector vTop, vBot;
			vBot = pEntity->GetAbsOrigin();
			
			bool isEnemyVis = g_pTools.IsVisible(pLocal->GetEyePosition(), pEntity->GetEyePosition(), pEntity) && pLocal->GetTeamNumber() != pEntity->GetTeamNumber();

			int r, g, b;
			if (pEntity->GetTeamNumber() == 2) // terrorists
				isEnemyVis ? r = g_pCvar.getValue("esp_t_visible_color_r") : r = g_pCvar.getValue("esp_t_invisible_color_r"), isEnemyVis ? g = g_pCvar.getValue("esp_t_visible_color_g") : g = g_pCvar.getValue("esp_t_invisible_color_g"), isEnemyVis ? b = g_pCvar.getValue("esp_ct_visible_color_b") : b = g_pCvar.getValue("esp_t_invisible_color_b");
			else if (pEntity->GetTeamNumber() == 3 ) // counter terrorists
				isEnemyVis ? r = g_pCvar.getValue("esp_ct_visible_color_r") : r = g_pCvar.getValue("esp_t_invisible_color_r"), isEnemyVis ? g = g_pCvar.getValue("esp_ct_visible_color_g") : g = g_pCvar.getValue("esp_ct_invisible_color_g"), isEnemyVis ? b = g_pCvar.getValue("esp_ct_visible_color_b") : b = g_pCvar.getValue("esp_ct_invisible_color_b");

			if (g_pCvar.getValue("esp_drawspot") == 1)
				DrawHead(pLocal, i, pEntity);

			if (pEntity->GetFlags() & FL_DUCKING)
				vTop = vBot + Vector(0, 0, 55.f);
			else
				vTop = vBot + Vector(0, 0, 75.f);

			int iHealth = pEntity->GetHealth();

			if (g_pDebugOverlay->ScreenPosition(vBot, vScreenBot) != 1 && g_pDebugOverlay->ScreenPosition(vTop, vScreenTop) != 1)
			{
				float h = (vScreenBot.y - vScreenTop.y);
				float w = (vScreenBot.y - vScreenTop.y) / 4;
				float healthbarh = w * 2.5;
				float rechts = w * 1.7;

				CEngineClient::player_info_t pInfo;
				if (g_pEngine->GetPlayerInfo(i, &pInfo))
				{
					if (g_pCvar.getValue("esp_box") == 1)
						g_pDraw.DrawEspBox(vScreenTop.x - w, vScreenTop.y + 1, w * 2, h, r, g, b, 255);

					if (g_pCvar.getValue("esp_name") == 1)
						//g_pDraw.DrawString(g_pDraw.esp_font, true, vScreenTop.x, vScreenTop.y - 13, 255, 255, 255, 255, pInfo.name);
						g_pDraw.DrawString(g_pDraw.esp_font, false, vScreenTop.x + w + 6, vScreenTop.y, g_pCvar.getValue("esp_text_color_r"), g_pCvar.getValue("esp_text_color_g"), g_pCvar.getValue("esp_text_color_b"), 255, pInfo.name);

					if (g_pCvar.getValue("esp_health") == 1)
						g_pDraw.DrawHealthBar(vScreenTop.x - w - 5, vScreenBot.y - h / 2, 4, h, 255.f - iHealth * 2.55f, iHealth * 2.55f, 0, 255, pEntity->GetHealth());

					if (g_pCvar.getValue("esp_weapon") == 1)
						//g_pDraw.DrawString(g_pDraw.esp_font, true, vScreenTop.x, vScreenBot.y - 16, 255, 255, 255, 255, g_pAim.GetActiveWeapon(pEntity)->GetWeaponName());
						g_pDraw.DrawString(g_pDraw.esp_font, false, vScreenTop.x + w + 6, vScreenTop.y + 20, g_pCvar.getValue("esp_text_color_r"), g_pCvar.getValue("esp_text_color_g"), g_pCvar.getValue("esp_text_color_b"), 255, g_pAim.GetActiveWeapon(pEntity)->GetWeaponName());
				}
			}
		}
	}
}