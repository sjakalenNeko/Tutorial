#pragma once

#include "Main.h"

class CWallhack
{
public:
	void doDraw();

	inline float flGetDistance(Vector vOrigin, Vector vLocalOrigin)
	{
		Vector vDelta = vOrigin - vLocalOrigin;
		int m_fDistance = sqrt(vDelta.Length());
		if (m_fDistance < 1.0)
			return 1.0;

		return m_fDistance;
	}
};

extern CWallhack g_pWallhack;