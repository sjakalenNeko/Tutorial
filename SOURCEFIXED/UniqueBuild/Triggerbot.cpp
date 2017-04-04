#include "Triggerbot.h"

CTrigger g_pTrigger;

void CTrigger::Trigger(CInput::CUserCmd* pCmd, CBaseEntity* pLocal)
{
	if (!GetAsyncKeyState(g_pCvar.getValue("trigger_key")))
		return;

	CTrace::Ray_t ray;
	CTrace::trace_t tr;
	CTrace::CTraceFilter pTraceFilter;
	pTraceFilter.pSkip = pLocal;

	Vector vCurAngles;
	g_pEngine->GetViewAngles(vCurAngles);

	Vector vAngles;
	g_pMath.AngleVectors(vCurAngles, vAngles);
	vAngles *= 8192.f;

	Vector vStart = pLocal->GetEyePosition();
	Vector vEnd = vStart + vAngles;

	ray.Init(vStart, vEnd);
	g_pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX, &pTraceFilter, &tr);

	if (!tr.m_pEntity)
		return;
	if (tr.m_pEntity->GetIndex() == pLocal->GetIndex())
		return;
	if (tr.m_pEntity->IsProtected())
		return;
	if (tr.m_pEntity->GetClientClass()->GetClassID() != CCSPlayer)
		return;
	if (tr.m_pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
		return;
	if (g_pCvar.getValue("check_smoke") == 1 && g_pTools.IsBehindSmoke(tr.m_pEntity))
		return;

	if (tr.hitgroup < 10 && tr.hitgroup > 0)
		pCmd->buttons |= IN_ATTACK;

	if(g_pCvar.getValue("trigger_overshoot") == 1 && tr.m_pEntity->GetHealth() <= 0)
		pCmd->buttons |= IN_ATTACK;
}