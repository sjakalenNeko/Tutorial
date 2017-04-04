#include "Tools.h"

CTools g_pTools;

bool CTools::IsBehindSmoke(CBaseEntity * pEnt)
{
	typedef bool(__cdecl* oLineGoesThroughSmoke) (Vector, Vector);
	static oLineGoesThroughSmoke LineGoesThroughSmoke = (oLineGoesThroughSmoke)(PatternSearch("client.dll", (PBYTE)"\x83\xEC\x44\x8B\x15", "xxxxx", NULL, NULL) - 3);

	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

	Vector vLocalOrigin = pLocal->GetAbsOrigin();
	Vector vTargetOrigin = pEnt->GetAbsOrigin();

	return LineGoesThroughSmoke(vLocalOrigin, vTargetOrigin);
}

bool CTools::IsVisible(Vector& vStart, Vector& vEnd, CBaseEntity* pEntity)
{
	CTrace::trace_t tr;
	CTrace::Ray_t ray;
	CTrace::CTraceFilter filter;
	filter.pSkip = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

	ray.Init(vStart, vEnd);
	g_pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	return (tr.m_pEntity == pEntity || tr.fraction > 0.99f);
}

void CTools::NormalizeVector(Vector& vAngle)
{
	for (int axis = 0; axis < 3; ++axis)
	{
		while (vAngle[axis] > 180.f)
			vAngle[axis] -= 360.f;
		while (vAngle[axis] < -180.f)
			vAngle[axis] += 360.f;
	}

	vAngle[2] = 0.0f;
}

void CTools::ClampAngle(Vector& vAngle)
{
	if (vAngle.x > 89.0f)
		vAngle.x = 89.0f;

	if (vAngle.x < -89.0f)
		vAngle.x = -89.0f;

	if (vAngle.y > 180)
		vAngle.y = 180;

	if (vAngle.y < -180)
		vAngle.y = -180;

	vAngle.z = 0;
}