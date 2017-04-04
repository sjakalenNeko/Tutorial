#pragma once

#include "Main.h"
#include "Vector.h"

class CMath
{
public:
	void CalcAngle(Vector &src, const Vector &dst, Vector &angles);
	float flGetDistance(Vector vOrigin, Vector vLocalOrigin);
	float VectorNormalize(Vector& vec);
	void AngleVectors(const Vector& vecAngles, Vector& vecForward);
	float GetFov2(Vector angle, Vector src, Vector dst, bool bDistance);
	void VectorAngles(const Vector &vecForward, Vector &vecAngles);
	bool GetHitboxPosition(int iHitBox, Vector& vecOrigin, QAngle qAngles, int index);
	void VectorTransform(const float *in1, const matrix3x4& in2, float *out);
	void VectorTransform(const Vector& in1, const matrix3x4& in2, Vector& out);
};

extern CMath g_pMath;