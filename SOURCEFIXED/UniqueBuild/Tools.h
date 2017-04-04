#pragma once

#include "Main.h"

class CTools
{
public:
	bool IsBehindSmoke(CBaseEntity* pEnt);
	bool IsVisible(Vector& vStart, Vector& vEnd, CBaseEntity* pEntity);
	void NormalizeVector(Vector& vAngle);
	void ClampAngle(Vector& vAngle);
};

extern CTools g_pTools;