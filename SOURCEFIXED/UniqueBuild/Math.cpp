#include "Math.h"

#define SQUARE( x ) ( x * x )

CMath g_pMath;

void inline SinCos(float radians, float *sine, float *cosine)
{
	_asm
	{
		fld		DWORD PTR[radians]
		fsincos

			mov edx, DWORD PTR[cosine]
			mov eax, DWORD PTR[sine]

			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
	}
}

float CMath::VectorNormalize(Vector& vec)
{
	float flLength = (float)sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
	if (flLength)
	{
		float flTemp = 1.f / flLength;
		vec[0] *= flTemp;
		vec[1] *= flTemp;
		vec[2] *= flTemp;
	}

	return flLength;
}

float CMath::flGetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = sqrt(vDelta.Length());
	if (m_fDistance < 1.0f)
		return 1.0f;

	return m_fDistance;
}

void CMath::CalcAngle(Vector &src, const Vector &dst, Vector &angles)
{
	Vector delta = Vector((src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]));
	double hyp = sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);
	angles[0] = (float)(atan(delta[2] / hyp) * (180.0 / M_PI));
	angles[1] = (float)(atan(delta[1] / delta[0]) * (180.0 / M_PI));
	angles[2] = 0.0f;
	if (delta[0] >= 0.0) { angles[1] += 180.0f; }
}

void CMath::AngleVectors(const Vector& vecAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	SinCos((float)(vecAngles[1] * (M_PI / 180.f)), &sy, &cy);
	SinCos((float)(vecAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp * cy;
	vecForward[1] = cp * sy;
	vecForward[2] = -sp;
}

void MakeVector(Vector angle, Vector& vector)
{
	float pitch = float(angle[0] * M_PI / 180);
	float yaw = float(angle[1] * M_PI / 180);
	float tmp = float(cos(pitch));
	vector[0] = float(-tmp * -cos(yaw));
	vector[1] = float(sin(yaw)*tmp);
	vector[2] = float(-sin(pitch));
}

float CMath::GetFov2(Vector angle, Vector src, Vector dst, bool bDistance)
{
	Vector ang, aim;
	float fFoV;

	CalcAngle(src, dst, ang);
	MakeVector(angle, aim);
	MakeVector(ang, ang);

	float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
	float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
	float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

	fFoV = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI);

	if (bDistance)
	{
		float xDist = abs(src[0] - dst[0]);
		float yDist = abs(src[1] - dst[1]);
		float Distance = sqrt((xDist * xDist) + (yDist * yDist));

		Distance /= 650;

		if (Distance < 0.7f)
			Distance = 0.7f;
		if (Distance > 6.5)
			Distance = 6.5;

		fFoV *= Distance;
	}

	return fFoV;
}

__forceinline float DotProduct(const float *a, const float *b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void CMath::VectorTransform(const float *in1, const matrix3x4& in2, float *out)
{
	Assert(in1 != out);
	out[0] = DotProduct(in1, in2[0]) + in2[0][3];
	out[1] = DotProduct(in1, in2[1]) + in2[1][3];
	out[2] = DotProduct(in1, in2[2]) + in2[2][3];
}

void CMath::VectorTransform(const Vector& in1, const matrix3x4& in2, Vector& out)
{
	VectorTransform(&in1.x, in2, &out.x);
}

void MatrixVector(const matrix3x4& pMatrix, Vector& out)
{
	out[0] = pMatrix[0][3];
	out[1] = pMatrix[1][3];
	out[2] = pMatrix[2][3];
}

void MatrixAngles(const matrix3x4& matrix, QAngle angles)
{
	float forward[3];
	float left[3];
	float up[3];

	forward[0] = matrix[0][0];
	forward[1] = matrix[1][0];
	forward[2] = matrix[2][0];
	left[0] = matrix[0][1];
	left[1] = matrix[1][1];
	left[2] = matrix[2][1];
	up[2] = matrix[2][2];

	float xyDist = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);

	if (xyDist > 0.001f)
	{
		angles.y = RAD2DEG(atan2f(forward[1], forward[0]));
		angles.x = RAD2DEG(atan2f(-forward[2], xyDist));
		angles.z = RAD2DEG(atan2f(left[2], up[2]));
	}
	else
	{
		angles.y = RAD2DEG(atan2f(-left[0], left[1]));
		angles.x = RAD2DEG(atan2f(-forward[2], xyDist));
		angles.z = 0;
	}
}

inline void MatrixAngles(const matrix3x4& matrix, QAngle angles, Vector &position)
{
	MatrixAngles(matrix, angles);
	MatrixVector(matrix, position);
}

bool CMath::GetHitboxPosition(int iHitBox, Vector& vecOrigin, QAngle qAngles, int index)
{
	if (iHitBox < 0 || iHitBox >= 20)
		return false;

	matrix3x4 pmatrix[128];
	Vector vMin, vMax;

	CBaseEntity* pEntity = g_pEntList->GetClientEntity(index);
	if (!pEntity)
		return false;
	if (pEntity->IsDormant())
		return false;

	const model_t* pModel = pEntity->GetModel();
	if (pModel)
	{
		studiohdr_t* pStudioHdr = g_pModel->GetStudiomodel(pModel);
		if (!pStudioHdr)
			return false;

		if (pEntity->SetupBones(pmatrix, 128, 0x00000100, GetTickCount()) == false)
			return false;

		mstudiohitboxset_t* pSet = pStudioHdr->pHitboxSet(0);
		if (!pSet)
			return false;

		mstudiobbox_t* pBox = NULL;

		pBox = pStudioHdr->pHitbox(iHitBox, 0);
		MatrixAngles(pmatrix[pBox->bone], qAngles, vecOrigin);
		VectorTransform(pBox->bbmin, pmatrix[pBox->bone], vMin);
		VectorTransform(pBox->bbmax, pmatrix[pBox->bone], vMax);
		vecOrigin = (vMin + vMax) * 0.5f;
		return true;
	}

	return true;
}

void CMath::VectorAngles(const Vector &vecForward, Vector &vecAngles)
{
	Vector vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}