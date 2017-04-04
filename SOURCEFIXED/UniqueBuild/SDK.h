#pragma once

#include "SDKStuff.h"
#include "dt_recv2.h"
#include "NetVar.h"

typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];

typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

class CBaseEntity;
class CBaseCombatWeapon;
class model_t;

inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

typedef struct
{
	const char* cPosition;
	int iWins;
	const char* cRank;
	std::string szName;
}player_t;

class Color
{
public:
	Color()
		: R(0),
		G(0),
		B(0),
		A(0)
	{
	}

	Color(int r, int g, int b, int a)
		: R(r),
		G(g),
		B(b),
		A(a)
	{
	}

	Color(int r, int g, int b)
		: R(r),
		G(g),
		B(b),
		A(255)
	{
	}

	static Color White(void) { return Color(255, 255, 255, 255); }
	static Color Black(void) { return Color(0, 0, 0, 255); }
	static Color Red(void) { return Color(255, 0, 0, 255); }
	static Color Green(void) { return Color(0, 255, 0, 255); }
	static Color Blue(void) { return Color(0, 0, 255, 255); }
	static Color Cyan(void) { return Color(0, 127, 255, 255); }
	static Color Yellow(void) { return Color(255, 255, 0, 255); }

	int r(void) { return R; }
	int g(void) { return G; }
	int b(void) { return B; }
	int a(void) { return A; }

	Color& operator = (Color& c)
	{
		R = c.r();
		G = c.g();
		B = c.b();
		A = c.a();
		return *this;
	}

private:
	int R, G, B, A;
};

class ClientClass
{
public:

	const char* GetName(void)
	{
		return *(char**)(this + 0x8);
	}
	RecvTable* GetTable()
	{
		return *(RecvTable**)(this + 0xC);
	}
	ClientClass* NextClass()
	{
		return *(ClientClass**)(this + 0x10);
	}
	int GetClassID(void)
	{
		return *(int*)(this + 0x14);
	}
};

class HLCLient
{
public:
	ClientClass* GetAllClasses(void)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 8)(this);
	}
};

class CBaseEntity
{
public:
public:
	const char *GetRankName(DWORD dwPlayerResource, int iIndex)
	{
		switch (this->GetRank(dwPlayerResource, iIndex))
		{
		case 0:
			return "Unranked"; break;
		case 1:
			return "Silver I"; break;
		case 2:
			return "Silver II"; break;
		case 3:
			return "Silver III"; break;
		case 4:
			return "Silver IV"; break;
		case 5:
			return "Silver Elite"; break;
		case 6:
			return "Silver Elite Master"; break;
		case 7:
			return "Gold Nova I"; break;
		case 8:
			return "Gold Nova II"; break;
		case 9:
			return "Gold Nova III"; break;
		case 10:
			return "Gold Nova Master"; break;
		case 11:
			return "Master Guardian I"; break;
		case 12:
			return "Master Guardian II"; break;
		case 13:
			return "Master Guardian Elite"; break;
		case 14:
			return "Distinguished Master Guardian"; break;
		case 15:
			return "Legendary Eagle"; break;
		case 16:
			return "Legendary Eagle Master"; break;
		case 17:
			return "Supreme Master First Class"; break;
		case 18:
			return "Global Elite"; break;
		}
		return "";
	}
public:
	ClientClass* GetClientClass()
	{
		PVOID pNetworkable = (void*)((DWORD)this + 0x8);
		typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}
	Vector& GetAbsOrigin()
	{
		__asm
		{
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
				CALL DWORD PTR DS : [EAX + 0x28]
		}
	}
	QAngle GetAbsAngles()
	{
		__asm
		{
			MOV ECX, this;
			MOV EAX, DWORD PTR DS : [ECX]; Ge
				CALL DWORD PTR DS : [EAX + 0x2C]
		}
	}
	int GetIndex()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, DWORD PTR DS : [EDI + 0x8]	//pointer to iclientrenderable (cbaseentity + 0x8)
				MOV EDX, DWORD PTR DS : [ECX]
				CALL DWORD PTR DS : [EDX + 0x28]	//pointer to getindex()
		}
	}
	bool IsDormant()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, [EDI + 0x8]
				MOV EDX, DWORD PTR DS : [ecx]
				CALL[EDX + 0x24]
		}
	}
	bool SetupBones(matrix3x4* matrix, int maxbones, int mask, float time)
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, DWORD PTR DS : [EDI + 0x4]
				MOV EDX, DWORD PTR DS : [ECX]
				PUSH time
				PUSH mask
				PUSH maxbones
				PUSH matrix
				CALL DWORD PTR DS : [EDX + 0x34]
		}
	}
	model_t* GetModel()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, [EDI + 0x4]
				MOV EDX, DWORD PTR DS : [ECX]
				CALL[EDX + 0x20]
		}
	}
	int GetShotsFired()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_iShotsFired);
	}
	int GetHealth()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_iHealth);
	}
	int GetOwner()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_hOwner);
	}
	int iAccount()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_iAccount);
	}
	const char *GetPosition()
	{
		return (char*)((DWORD)this + Offsets::Player::m_szLastPlaceName);
	}
	int GetTeamNumber()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_iTeamNum);
	}
	int GetArmorValue()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_ArmorValue);
	}
	bool IsProtected()
	{
		return *(bool*)((DWORD)this + Offsets::Player::m_bGunGameImmunity);
	}
	bool isDefusing()
	{
		return *(bool*)((DWORD)this + Offsets::Player::m_bIsDefusing);
	}
	bool isScoping()
	{
		return *(bool*)((DWORD)this + Offsets::Player::m_bIsScoped);
	}
	int GetRank(DWORD dwForPlayerResource, int Index)
	{
		return *(int*)((DWORD)dwForPlayerResource + Offsets::Player::m_iCompetitiveRanking + (int)Index * 4);
	}
	int GetKills(DWORD dwForPlayerResource, int Index)
	{
		return *(int*)((DWORD)dwForPlayerResource + Offsets::Player::m_iKills + (int)Index * 4);
	}
	int GetWins(DWORD dwForPlayerResource, int Index)
	{
		return *(int*)((DWORD)dwForPlayerResource + Offsets::Player::m_iCompetitiveWins + (int)Index * 4);
	}
	int GetCarry(DWORD dwForPlayerResource, int Index)
	{
		return *(int*)((DWORD)dwForPlayerResource + Offsets::Player::m_iPlayerC4 + (int)Index * 4);
	}
	bool hasDefuse()
	{
		return *(bool*)((DWORD)this + Offsets::Player::m_bHasDefuser);
	}
	int GetFlags()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_fFlags);
	}
	int GetHits()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_totalHitsOnServer);
	}
	char GetLifeState()
	{
		return *(char*)((DWORD)this + Offsets::Player::m_lifeState);
	}
	int m_Local()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_Local);
	}
	QAngle GetPunchAngle()
	{
		return *(QAngle*)((DWORD)this + Offsets::Player::m_Local + Offsets::Player::m_aimPunchAngle);
	}
	Vector viewGetPunchAngle()
	{
		return *(Vector*)((DWORD)this + Offsets::Player::m_Local + Offsets::Player::m_ViewPunchAngle);
	}
	Vector vecGetPunchAngle()
	{
		return *(Vector*)((DWORD)this + Offsets::Player::m_Local + Offsets::Player::m_aimPunchAngle);
	}
	Vector GetvecOrigin()
	{
		return *(Vector*)((DWORD)this + Offsets::Player::m_vOrigin);
	}
	Vector GetEyePosition()
	{
		return (*(Vector*)((DWORD)this + Offsets::Player::m_vOrigin) + *(Vector*)((DWORD)this + Offsets::Player::m_vViewOffset));
	}
	int GetTickBase()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_nTickBase);
	}
	int GetFlashDuration()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_flFlashDuration);
	}
	int GetFlashAlpha()
	{
		return *(int*)((DWORD)this + Offsets::Player::m_flFlashMaxAlpha);
	}
	bool HasHelmet()
	{
		return *(bool*)((DWORD)this + Offsets::Player::m_bHasHelmet);
	}
	float GetBombTimer()
	{
		return *(float*)((DWORD)this + Offsets::Player::m_flC4Blow);
	}
	float GetDefuseTimer()
	{
		return *(float*)((DWORD)this + Offsets::Player::m_flDefuseLength);
	}
	bool GetIsTicking()
	{
		return *(bool*)((DWORD)this + Offsets::Bomb::m_bBombTicking);
	}
	Vector GetAbsVelocity()
	{
		return *(Vector*)((DWORD)this + Offsets::Player::m_vVelocity);
	}
	QAngle GetEyeAngles()
	{
		QAngle EyeAngle = *(QAngle*)((DWORD)this + Offsets::Player::m_angEyeAngles);
		return EyeAngle;
	}
	Vector vecGetEyeAngles()
	{
		return *(Vector*)((DWORD)this + Offsets::Player::m_angEyeAngles);
	}
};

class CBaseCombatWeapon : public CBaseEntity
{
public:
	const char *GetWeaponName(void)
	{
		switch (this->GetWeaponID())
		{
		case WEAPON_DEAGLE:
			return "Deagle"; break;
		case WEAPON_DUALS:
			return "Dualies"; break;
		case WEAPON_FIVE7:
			return "Five-Seven"; break;
		case WEAPON_GLOCK:
			return "Glock"; break;
		case WEAPON_AK47:
			return "AK47"; break;
		case WEAPON_AUG:
			return "AUG"; break;
		case WEAPON_AWP:
			return "AWP"; break;
		case WEAPON_FAMAS:
			return "Famas"; break;
		case WEAPON_G3SG1:
			return "G3SG1"; break;
		case WEAPON_GALIL:
			return "Galil"; break;
		case WEAPON_M249:
			return "M249"; break;
		case WEAPON_M4A1:
			return "M4A1"; break;
		case WEAPON_MAC10:
			return "MAC10"; break;
		case WEAPON_P90:
			return "P90"; break;
		case WEAPON_UMP45:
			return "UMP45"; break;
		case WEAPON_XM1014:
			return "XM1014"; break;
		case WEAPON_BIZON:
			return "Bizon"; break;
		case WEAPON_MAG7:
			return "MAG7"; break;
		case WEAPON_NEGEV:
			return "Negev"; break;
		case WEAPON_SAWEDOFF:
			return "Sawed Off"; break;
		case WEAPON_TEC9:
			return "TEC9"; break;
		case WEAPON_TASER:
			return "Taser"; break;
		case WEAPON_P2000:
			return "P2000"; break;
		case WEAPON_MP7:
			return "MP7"; break;
		case WEAPON_NOVA:
			return "NOVA"; break;
		case WEAPON_P250:
			return "P250"; break;
		case WEAPON_SCAR20:
			return "SCAR20"; break;
		case WEAPON_SG553:
			return "SG553"; break;
		case WEAPON_SCOUT:
			return "Scout"; break;
		case WEAPON_R8REVOLVER:
			return "Revolver"; break;
		case WEAPON_C4:
			return "BOMB"; break;
		case WEAPON_KNIFE_CT:
			return "KNIFE"; break;
		case WEAPON_KNIFE_T:
			return "KNIFE"; break;
		case WEAPON_KNIFE_GUT:
			return "Gut"; break;
		case WEAPON_KNIFE_FLIP:
			return "Flip"; break;
		case WEAPON_KNIFE_BAYONET:
			return "Bayonet"; break;
		case WEAPON_KNIFE_KARAMBIT:
			return "Karambit"; break;
		case WEAPON_KNIFE_M9BAYONET:
			return "M9 Bayonet"; break;
		case WEAPON_KNIFE_BUTTERFLY:
			return "Butterfly"; break;
		case WEAPON_KNIFE_FALCHION:
			return "Falchion"; break;
		case WEAPON_KNIFE_HUNTSMAN:
			return "Huntsman"; break;
		case WEAPON_KNIFE_DAGGERS:
			return "Shadow Daggers"; break;
		case WEAPON_KNIFE_BOWIE:
			return "BOWIE"; break;
		case WEAPON_FLASH:
			return "Flashbang"; break;
		case WEAPON_HE:
			return "Frag"; break;
		case WEAPON_SMOKE:
			return "Smoke"; break;
		case WEAPON_MOLOTOV:
			return "Molotov"; break;
		case WEAPON_DECOY:
			return "Decoy"; break;
		case WEAPON_INC:
			return "Incendiary"; break;
		case WEAPON_M4A1S:
			return "M4A1-S"; break;
		case WEAPON_USPS:
			return "USP-S"; break;
		case WEAPON_CZ75:
			return "CZ75"; break;
		}
		return "";
	}
public:
	int GetClip1()
	{
		return *(int*)((DWORD)this + Offsets::Weapon::m_iClip1); //m_iHealth
	}
	int GetWeaponID()
	{
		return *(int*)((DWORD)this + Offsets::Attribute::m_iItemDefinitionIndex); //m_AttributeManager + m_Item + m_iItemDefinitionIndex
	}
	float GetNextPrimaryAttack()
	{
		return *(float*)((DWORD)this + Offsets::Weapon::m_flNextPrimaryAttack);
	}
	bool IsPistol(void)
	{
		int weap = GetWeaponID();

		switch (this->GetWeaponID())
		{
		case WEAPON_DEAGLE:
			return true;
		case WEAPON_DUALS:
			return true;
		case WEAPON_FIVE7:
			return true;
		case WEAPON_GLOCK:
			return true;
		case WEAPON_TEC9:
			return true;
		case WEAPON_P2000:
			return true;
		case WEAPON_USPS:
			return true;
		case WEAPON_P250:
			return true;
		case WEAPON_CZ75:
			return true;
		case WEAPON_R8REVOLVER:
			return true;
		default:
			return false;
		}
	}
	bool IsShotgun(void)
	{
		switch (this->GetWeaponID())
		{
		case WEAPON_XM1014:
			return true;
		case WEAPON_MAG7:
			return true;
		case WEAPON_SAWEDOFF:
			return true;
		case WEAPON_NOVA:
			return true;
		default:
			return false;
		}
	}
	bool IsAutomatic(void)
	{
		switch (this->GetWeaponID())
		{
		case WEAPON_AK47:
			return true;
		case WEAPON_AUG:
			return true;
		case WEAPON_FAMAS:
			return true;
		case WEAPON_GALIL:
			return true;
		case WEAPON_M249:
			return true;
		case WEAPON_M4A1:
			return true;
		case WEAPON_M4A1S:
			return true;
		case WEAPON_MAC10:
			return true;
		case WEAPON_P90:
			return true;
		case WEAPON_UMP45:
			return true;
		case WEAPON_BIZON:
			return true;
		case WEAPON_NEGEV:
			return true;
		case WEAPON_MP7:
			return true;
		case WEAPON_MP9:
			return true;
		case WEAPON_SG553:
			return true;
		default:
			return false;
		}
	}
	bool IsSniper(void)
	{
		switch (this->GetWeaponID())
		{
		case WEAPON_AWP:
			return true;
		case WEAPON_G3SG1:
			return true;
		case WEAPON_SCAR20:
			return true;
		case WEAPON_SCOUT:
			return true;
		default:
			return false;
		}
	}
	bool IsKnife(void)
	{
		switch (this->GetWeaponID())
		{
		case WEAPON_KNIFE_CT:
			return true;
		case WEAPON_KNIFE_T:
			return true;
		case WEAPON_KNIFE_GUT:
			return true;
		case WEAPON_KNIFE_FLIP:
			return true;
		case WEAPON_KNIFE_BAYONET:
			return true;
		case WEAPON_KNIFE_M9BAYONET:
			return true;
		case WEAPON_KNIFE_KARAMBIT:
			return true;
		case WEAPON_KNIFE_HUNTSMAN:
			return true;
		case WEAPON_KNIFE_BUTTERFLY:
			return true;
		case WEAPON_KNIFE_BOWIE:
			return true;
		case WEAPON_KNIFE_FALCHION:
			return true;
		case WEAPON_KNIFE_DAGGERS:
			return true;
		default:
			return false;
		}
	}
	bool IsOther(void)
	{
		switch (this->GetWeaponID())
		{
		case ITEM_NONE:
			return true;
		case WEAPON_TASER:
			return true;
		case WEAPON_FLASH:
			return true;
		case WEAPON_HE:
			return true;
		case WEAPON_SMOKE:
			return true;
		case WEAPON_MOLOTOV:
			return true;
		case WEAPON_DECOY:
			return true;
		case WEAPON_INC:
			return true;
		case WEAPON_C4:
			return true;
		default:
			return false;
		}
	}
	bool IsGrenade(void)
	{
		int weap = GetWeaponID();

		switch (this->GetWeaponID())
		{
		case WEAPON_FLASH:
			return true;
		case WEAPON_HE:
			return true;
		case WEAPON_SMOKE:
			return true;
		case WEAPON_MOLOTOV:
			return true;
		case WEAPON_DECOY:
			return true;
		case WEAPON_INC:
			return true;
		default:
			return false;
		}
	}
};

class CModelInfo
{
public:
	const char* GetModelName(const model_t* pModel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, const model_t*);
		return getvfunc<OriginalFn>(this, 3)(this, pModel);
	}
	int GetModelIndex(const char* ModelName)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 2)(this, ModelName);
	}
	int GetInt(const char *keyName, int defaultValue = 0)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, const char *, int);
		return getvfunc<OriginalFn>(this, 6)(this, keyName, defaultValue);
	}
	studiohdr_t* GetStudiomodel(const model_t *mod)
	{
		typedef studiohdr_t* (__thiscall* OriginalFn)(PVOID, const model_t*);
		return getvfunc<OriginalFn>(this, 30)(this, mod);
	}
};

class CDebugOverlay
{
public:
	void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const Vector&, const Vector&, const Vector&, QAngle const&, int, int, int, int, float);
		getvfunc<OriginalFn>(this, 3)(this, origin, mins, max, orientation, r, g, b, a, duration);
	}
	void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration);
		getvfunc<OriginalFn>(this, 5)(this, origin, dest, r, g, b, noDepthTest, duration);
	}
	void AddSweptBoxOverlay(const Vector& origin, const Vector& end, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const Vector&, const Vector&, const Vector&, const Vector&, QAngle const&, int, int, int, int, float);
		getvfunc<OriginalFn>(this, 9)(this, origin, end, mins, max, orientation, r, g, b, a, duration);
	}
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, const Vector&, Vector&);
		return getvfunc<OriginalFn>(this, 13)(this, vIn, vOut);
	}
};

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 15)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 16)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 19)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
		getvfunc<OriginalFn>(this, 23)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 25)(this, r, g, b, a);
	}
	void SurfaceGetCursorPos(int &x, int &y)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int &, int &);
		getvfunc<OriginalFn>(this, 100)(this, x, y);
	}
	void SurfaceSetCursorPos(int x, int y)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int);
		getvfunc<OriginalFn>(this, 101)(this, x, y);
	}
	bool AddCustomFontFile(const char* fontName)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 73)(this, fontName);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int);
		getvfunc<OriginalFn>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t *text, int textLen)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t *, int, int);
		return getvfunc<OriginalFn>(this, 28)(this, text, textLen, 0);
	}
	unsigned long CreateFont()
	{
		typedef unsigned int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 71)(this);
	}
	void SetFontGlyphSet(unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		getvfunc<OriginalFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(__thiscall* OriginalFn)(void*, unsigned long font, const wchar_t *text, int &wide, int &tall);
		getvfunc<OriginalFn>(this, 79)(this, font, text, wide, tall);
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(void*, int x0, int y0, int x1, int y1);
		getvfunc<OriginalFn>(this, 18)(this, x0, y0, x1, y1);
	}
	void DrawOutlinedCircle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 108)(this, x, y, radius, segments);
	}
	const char* GetFontName(unsigned long font)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned long);
		return getvfunc<OriginalFn>(this, 134)(this, font);
	}
};

class IPanel
{
public:
	unsigned int GetPanel(int type)
	{
		typedef unsigned int(__thiscall *tGetPanel)(void*, int type);
		return getvfunc<tGetPanel>(this, 1)(this, type);
	}
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned int);
		return getvfunc<OriginalFn>(this, 36)(this, vguiPanel);
	}
};

class CEntityList
{
public:
	CBaseEntity* GetClientEntity(int entnum)
	{
		typedef CBaseEntity* (__thiscall* OriginalFn)(PVOID, int);
		return getvfunc<OriginalFn>(this, 3)(this, entnum);
	}
	CBaseEntity* GetClientEntityFromHandle(int hEnt)
	{
		typedef CBaseEntity* (__thiscall* OriginalFn)(PVOID, int);
		return getvfunc<OriginalFn>(this, 4)(this, hEnt);
	}
	int GetHighestEntityIndex(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 6)(this);
	}
};

class CEngineClient
{
public:
	typedef struct player_info_s
	{
		unsigned long long      unknown;
		unsigned long long      xuid;
		char                    name[128];
		int                     userID;
		char                    guid[32 + 1];
		unsigned int            friendsID;
		char                    friendsName[128];
		bool                    fakeplayer;
		bool                    ishltv;
		unsigned long           customFiles[4];
		unsigned char           filesDownloaded;
	} player_info_t;

	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return getvfunc<OriginalFn>(this, 5)(this, width, height);
	}
	void ClientCmd(const char *szCmdString, ...)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		getvfunc<OriginalFn>(this, 7)(this, szCmdString);
	}
	bool isinGame(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 26)(this);
	}
	bool GetPlayerInfo(int iIndex, player_info_t *pInfo)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t*);
		return getvfunc<OriginalFn>(this, 8)(this, iIndex, pInfo);
	}
	int GetMaxClients(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 20)(this);
	}
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 12)(this);
	}
	float GetLastTimeStamp(void)
	{
		typedef float(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 14)(this);
	}
	const matrix3x4& WorldToScreenMatrix(void)
	{
		typedef const matrix3x4& (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 37)(this);
	}
	void ExecuteClientCmd(char const* szCommand)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, char const* szCommand);
		getvfunc<OriginalFn>(this, 108)(this, szCommand);
	}
	void SetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
		getvfunc<OriginalFn>(this, 19)(this, vAngles);
	}
	void SetQAngles(QAngle& vAngles)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, QAngle&);
		getvfunc<OriginalFn>(this, 19)(this, vAngles);
	}
	void GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
		getvfunc<OriginalFn>(this, 18)(this, vAngles);
	}
	int GetPlayerForUserID(int iUserId)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc< OriginalFn >(this, 9)(this, iUserId);
	}
};

class CInput
{
public:
	class CUserCmd
	{
	public:
		CRC32_t GetChecksum(void) const
		{
			CRC32_t crc;
			CRC32_Init(&crc);
			CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
			CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
			CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
			CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection)); //new
			CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
			CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
			CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
			CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
			CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
			CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
			CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
			CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
			CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
			CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));
			CRC32_Final(&crc);
			return crc;
		}
		BYTE u1[4];
		int command_number;
		int tick_count;
		Vector viewangles;
		Vector aimdirection;
		float forwardmove;
		float sidemove;
		float upmove;
		int buttons;
		BYTE impulse;
		int weaponselect;
		int weaponsubtype;
		int random_seed;
		short mousedx;
		short mousedy;
		bool hasbeenpredicted;
		Vector headangles;
		Vector headoffset;
	};
	class CVerifiedUserCmd
	{
	public:
		CUserCmd			m_cmd;
		unsigned long		m_crc;
	};
	CUserCmd* GetUserCmd(int slot, int seq)
	{
		typedef CUserCmd* (__thiscall* OriginalFn)(PVOID, int, int);
		return getvfunc<OriginalFn>(this, 8)(this, slot, seq);
	}
};

class CGlobalVars
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float unknown;
	float curtime;
	float frametime;
	int maxclients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
};

class CTrace
{
public:
	enum TraceType_t
	{
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
		TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
		TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
	};
	struct cplane_t
	{
		Vector normal;
		float dist;
		BYTE type;
		BYTE signBits;
		BYTE pad[2];
	};
	struct csurface_t
	{
		const char*		name;
		short			surfaceProps;
		unsigned short	flags;
	};
	struct Ray_t
	{
		VectorAligned	 m_Start;	// starting point, centered within the extents
		VectorAligned	 m_Delta;	// direction + length of the ray
		VectorAligned	 m_StartOffset;	// Add this to m_Start to get the actual ray start
		VectorAligned	 m_Extents;	// Describes an axis aligned box extruded along a ray
		const matrix3x4* m_pWorldAxisTransform;
		bool			 m_IsRay;	// are the extents zero?
		bool			 m_IsSwept;	// is delta != 0?

		Ray_t() : m_pWorldAxisTransform(NULL) {}

		void Init(Vector const& start, Vector const& end)
		{
			Assert(&end);
			VectorSubtract(end, start, m_Delta);

			m_IsSwept = (m_Delta.LengthSqr() != 0);

			VectorClear(m_Extents);
			m_pWorldAxisTransform = NULL;
			m_IsRay = true;

			// Offset m_Start to be in the center of the box...
			VectorClear(m_StartOffset);
			VectorCopy(start, m_Start);
		}
		void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
		{
			Assert(&end);
			VectorSubtract(end, start, m_Delta); //wait

			m_pWorldAxisTransform = NULL;
			m_IsSwept = (m_Delta.LengthSqr() != 0);

			VectorSubtract(maxs, mins, m_Extents);
			m_Extents *= 0.5f;
			m_IsRay = (m_Extents.LengthSqr() < 1e-6);

			// Offset m_Start to be in the center of the box...
			VectorAdd(mins, maxs, m_StartOffset);
			m_StartOffset *= 0.5f;
			VectorAdd(start, m_StartOffset, m_Start);
			m_StartOffset *= -1.f;
		}
		Vector InvDelta() const
		{
			Vector vecInvDelta;
			for (int iAxis = 0; iAxis < 3; ++iAxis)
			{
				if (m_Delta[iAxis] != 0.f)
				{
					vecInvDelta[iAxis] = 1.f / m_Delta[iAxis];
				}
				else
				{
					vecInvDelta[iAxis] = FLT_MAX;
				}
			}

			return vecInvDelta;
		}
	private:
	};
	struct trace_t
	{
		Vector		 start;
		Vector		 endpos;
		cplane_t	 plane;
		float		 fraction;
		int			 contents;
		WORD		 dispFlags;
		bool		 allSolid;
		bool		 startSolid;
		float		 fractionLeftSolid;
		csurface_t	 surface;
		int			 hitgroup;
		short		 physicsBone;
		WORD		 m_nWorldSurfaceIndex;
		CBaseEntity* m_pEntity;
		int			 hitbox;

		bool DidHitWorld(CEntityList* EntList)
		{
			return m_pEntity == (CBaseEntity*)EntList->GetClientEntity(0);
		}
		bool DidHitNonWorldEntity(CEntityList* EntList)
		{
			return m_pEntity != NULL && !DidHitWorld(EntList);
		}
		bool DidHit() const
		{
			return fraction < 1.0f || allSolid || startSolid;
		}
	};
	class ITraceFilter
	{
	public:
		virtual bool ShouldHitEntity(CBaseEntity *pEntity, int contentsMask) = 0;
		virtual TraceType_t    GetTraceType() const = 0;
	};
	class CTraceFilter : public ITraceFilter
	{
	public:
		bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
		{
			return !(pEntityHandle == pSkip);
		}
		virtual TraceType_t GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void* pSkip;
	};
	class CTraceFilterSkipTwoEntities : public ITraceFilter
	{
	public:
		CTraceFilterSkipTwoEntities(void *pPassEnt1, void *pPassEnt2)
		{
			passentity1 = pPassEnt1;
			passentity2 = pPassEnt2;
		}
		virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
		{
			return !(pEntityHandle == passentity1 || pEntityHandle == passentity2);
		}
		virtual TraceType_t    GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void *passentity1;
		void *passentity2;
	};
public:
	void TraceRay(const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void(__thiscall* oTraceRay)(PVOID, const Ray_t&, unsigned int, CTraceFilter *, trace_t*);
		getvfunc<oTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
	void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, CBaseEntity *pEnt, trace_t *pTrace)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const Ray_t &, unsigned int, CBaseEntity *, trace_t *);
		getvfunc<OriginalFn>(this, 3)(this, ray, fMask, pEnt, pTrace);
	}
	int GetPointContents(const Vector &vecAbsPosition, unsigned int fMask, CBaseEntity** ppEntity = NULL)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, const Vector &, unsigned int, CBaseEntity**);
		return getvfunc<OriginalFn>(this, 0)(this, vecAbsPosition, fMask, ppEntity);
	}
};