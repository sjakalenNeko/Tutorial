#include "Main.h"

int GetOffset(char *szClassName, char *szVariable)
{
	ClientClass* pClass = g_pClient->GetAllClasses();
	for (; pClass; pClass = pClass->NextClass())
	{
		RecvTable* pTable = pClass->GetTable();
		if (pTable->GetNumProps() <= 1)
			continue;

		for (int i = 0; i < pTable->GetNumProps(); i++)
		{
			RecvProp *pProp = pTable->GetProp(i);
			if (!pProp)
				continue;

			if (!strcmp(pTable->GetName(), szClassName) && !strcmp(pProp->GetName(), szVariable))
				return pProp->GetOffset();

			if (pProp->GetDataTable())
			{
				RecvTable* pTable = pProp->GetDataTable();

				for (int i = 0; i < pTable->GetNumProps(); i++)
				{
					RecvProp* pProp = pTable->GetProp(i);
					if (!pProp)
						continue;

					if (!strcmp(pTable->GetName(), szClassName) && !strcmp(pProp->GetName(), szVariable))
						return pProp->GetOffset();
				}
			}
		}
	}

	return 0;
}

int GetOffset_Nit(const char* szClassName, const char* szNetvar)
{
	ClientClass* pClass = g_pClient->GetAllClasses();

	if (pClass == nullptr || szClassName == nullptr || szNetvar == nullptr)
		return NULL;

	for (; pClass; pClass = pClass->NextClass())
	{
		if (strcmp(szClassName, pClass->GetTable()->GetName()))
			continue;

		for (int i = 0; i < pClass->GetTable()->GetNumProps(); i++)
		{
			RecvProp* pRecvProp = pClass->GetTable()->GetPropA(i);

			if (isdigit(pRecvProp->GetName()[0]))
				continue;

			if (!strcmp(pRecvProp->GetName(), szNetvar))
			{
				return pRecvProp->GetOffset();
			}

			if (!pRecvProp->GetDataTable())
				continue;

			for (int j = 0; j < pRecvProp->GetDataTable()->GetNumProps(); j++)
			{
				RecvProp* pRecvProp2 = pRecvProp->GetDataTable()->GetPropA(j);

				if (isdigit(pRecvProp2->GetName()[0]))
					continue;

				if (!strcmp(pRecvProp2->GetName(), szNetvar))
				{
					return pRecvProp2->GetOffset();
				}

				if (!pRecvProp2->GetDataTable())
					continue;

				for (int k = 0; k < pRecvProp2->GetDataTable()->GetNumProps(); k++)
				{
					RecvProp* pRecvProp3 = pRecvProp2->GetDataTable()->GetPropA(k);

					if (isdigit(pRecvProp3->GetName()[0]))
						continue;

					if (!strcmp(pRecvProp3->GetName(), szNetvar))
					{
						return pRecvProp3->GetOffset();
					}
				}
			}
		}
	}

	return NULL;
}

namespace Offsets
{
	void Init(void)
	{
		Player::m_iHealth = GetOffset("DT_BasePlayer", "m_iHealth");
		Player::m_ArmorValue = GetOffset("DT_CSPlayer", "m_ArmorValue");
		Player::m_iTeamNum = GetOffset("DT_BaseEntity", "m_iTeamNum");
		Player::m_iAccount = GetOffset("DT_CSPlayer", "m_iAccount");
		Player::m_bSpotted = GetOffset("DT_BaseEntity", "m_bSpotted");
		Player::m_hOwner = GetOffset("DT_BaseEntity", "m_hOwnerEntity");
		Player::m_bHasDefuser = GetOffset("DT_CSPlayer", "m_bHasDefuser");
		Player::m_bIsDefusing = GetOffset("DT_CSPlayer", "m_bIsDefusing");
		Player::m_iShotsFired = GetOffset("DT_CSLocalPlayerExclusive", "m_iShotsFired");
		Player::m_fFlags = GetOffset("DT_BasePlayer", "m_fFlags");
		Player::m_lifeState = GetOffset("DT_BasePlayer", "m_lifeState");
		Player::m_hObserverTarget = GetOffset("DT_BasePlayer", "m_hObserverTarget");
		Player::m_Local = GetOffset("DT_LocalPlayerExclusive", "m_Local");
		Player::m_vEyeAngles = GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
		Player::m_bGunGameImmunity = GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
		Player::m_flDefuseLength = GetOffset("DT_PlantedC4", "m_flDefuseCountDown");
		Player::m_flC4Blow = GetOffset("DT_PlantedC4", "m_flC4Blow");
		Player::m_aimPunchAngle = GetOffset("DT_BasePlayer", "m_Local") + 0x70;
		Player::m_ViewPunchAngle = GetOffset("DT_BasePlayer", "m_Local") + 0x64;
		Player::m_BombTimer = GetOffset("DT_BaseCombatWeapon", "m_flModelScale");
		Player::m_vOrigin = GetOffset("DT_CSLocalPlayerExclusive", "m_vecOrigin");
		Player::m_vViewOffset = GetOffset("DT_LocalPlayerExclusive", "m_vecViewOffset[0]");
		Player::m_nTickBase = GetOffset("DT_LocalPlayerExclusive", "m_nTickBase");
		Player::m_hActiveWeapon = GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		Player::m_flFlashDuration = GetOffset("DT_CSPlayer", "m_flFlashDuration");
		Player::m_flFlashMaxAlpha = GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
		Player::m_vVelocity = GetOffset("DT_LocalPlayerExclusive", "m_vecVelocity[0]");
		Player::m_bIsScoped = GetOffset("DT_CSPlayer", "m_bIsScoped");
		Player::m_angEyeAngles = GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
		Player::m_iCompetitiveRanking = GetOffset("DT_CSPlayerResource", "m_iCompetitiveRanking");
		Player::m_dwWeaponTableIndex = GetOffset("WeaponTableIndex", "m_dw_WeaponTableIndex");
		Player::m_iCompetitiveWins = GetOffset("DT_CSPlayerResource", "m_iCompetitiveWins");
		Player::m_iPlayerC4 = GetOffset("DT_CSPlayerResource", "m_iPlayerC4");
		Player::m_iKills = GetOffset("DT_CSPlayerResource", "m_iScore");
		Player::m_szLastPlaceName = GetOffset("DT_BasePlayer", "m_szLastPlaceName");
		Player::m_bHasHelmet = GetOffset("DT_CSPlayer", "m_bHasHelmet");
		Player::m_nHitboxSet = GetOffset("DT_BaseAnimating", "m_nHitboxSet");
		Player::m_totalHitsOnServer = GetOffset("DT_CSPlayer", "m_totalHitsOnServer");
		Player::m_hConstraintEntity = GetOffset("DT_LocalPlayerExclusive", "m_hConstraintEntity");
		Player::m_iObserverMode = GetOffset("DT_BasePlayer", "m_iObserverMode");

		Player::m_vInitialPosition = GetOffset("DT_BaseCSGrenadeProjectile", "m_vecInitialPosition");
		Player::m_vInitialVelocity = GetOffset("DT_BaseCSGrenadeProjectile", "m_vInitialVelocity");

		Weapon::m_iItemDefinitionIndex = GetOffset("DT_ScriptCreatedItem", "m_iItemDefinitionIndex");
		Weapon::m_flNextPrimaryAttack = GetOffset("DT_LocalActiveWeaponData", "m_flNextPrimaryAttack");
		Weapon::m_iViewModelIndex = GetOffset("DT_LocalWeaponData", "m_nViewModelIndex ");
		Weapon::m_iClip1 = GetOffset("DT_BaseCombatWeapon", "m_iClip1");
		Weapon::m_iState = GetOffset("DT_BaseCombatWeapon", "m_iState");
		Weapon::m_bIsBroken = GetOffset("DT_FuncConveyor", "m_bIsBroken");

		Entity::m_CollisionGroup = GetOffset("DT_BaseEntity", "m_CollisionGroup");
		Entity::m_Collision = GetOffset("DT_BaseEntity", "m_Collision");
		Entity::m_vMins = GetOffset("DT_CollisionProperty", "m_vecMins");
		Entity::m_vMaxs = GetOffset("DT_CollisionProperty", "m_vecMaxs");
		Entity::m_rgflCoordinateFrame = Entity::m_CollisionGroup - 48;

		Attribute::m_iItemDefinitionIndex = GetOffset_Nit("DT_BaseAttributableItem", "m_AttributeManager") + GetOffset_Nit("DT_BaseAttributableItem", "m_Item") + GetOffset_Nit("DT_BaseAttributableItem", "m_iItemDefinitionIndex");

		Bomb::m_bBombTicking = GetOffset_Nit("DT_PlantedC4", "m_bBombTicking");
	}

	namespace Attribute
	{
		DWORD m_iItemDefinitionIndex = NULL;
		DWORD m_iItemIDHigh = NULL;
		DWORD m_iItemIDLow = NULL;
		DWORD m_OriginalOwnerXuidLow = NULL;
		DWORD m_OriginalOwnerXuidHigh = NULL;
		DWORD m_nFallbackPaintKit = NULL;
		DWORD m_nFallbackSeed = NULL;
		DWORD m_flFallbackWear = NULL;
		DWORD m_nFallbackStatTrak = NULL;
	}

	namespace Player
	{
		DWORD   m_hConstraintEntity = NULL;
		DWORD	m_iHealth = NULL;
		DWORD	m_ArmorValue = NULL;
		DWORD	m_iTeamNum = NULL;
		DWORD	m_fFlags = NULL;
		DWORD	m_iKills = NULL;
		DWORD   m_bHasDefuser = NULL;
		DWORD	m_bIsDefusing = NULL;
		DWORD	m_lifeState = NULL;
		DWORD   m_hOwner = NULL;
		DWORD   m_bIsScoped = NULL;
		DWORD	m_flFlashDuration = NULL;
		DWORD   m_dwLoadFromBuffer = NULL;
		DWORD   m_iAccount = NULL;
		DWORD   m_szLastPlaceName = NULL;
		DWORD   m_hObserverTarget = NULL;
		DWORD   m_iObserverMode = NULL;

		DWORD	m_flDefuseLength = NULL;
		DWORD   m_iCompetitiveWins = NULL;
		DWORD   m_iPlayerC4 = NULL;
		DWORD   m_dwWeaponTableIndex = NULL;
		DWORD   m_bSpotted = NULL;
		DWORD   m_iCompetitiveRanking = NULL;
		DWORD   m_BombTimer = NULL;
		DWORD	m_flFlashMaxAlpha = NULL;
		DWORD	m_Local = NULL;
		DWORD   m_flC4Blow = NULL;
		DWORD	m_bGunGameImmunity = NULL;
		DWORD	m_vPunchAngle = NULL;
		DWORD	m_aimPunchAngle = NULL;
		DWORD   m_ViewPunchAngle = NULL;
		DWORD	m_vOrigin = NULL;
		DWORD	m_vViewOffset = NULL;
		DWORD	m_nTickBase = NULL;
		DWORD   m_totalHitsOnServer = NULL;

		DWORD	m_hActiveWeapon = NULL;
		DWORD	m_vVelocity = NULL;
		DWORD	m_vEyeAngles = NULL;
		DWORD	m_angEyeAngles = NULL;
		DWORD	m_bHasHelmet = NULL;
		DWORD	m_nHitboxSet = NULL;
		DWORD	m_clrRender = NULL;
		DWORD	m_iShotsFired = NULL;

		DWORD   m_vInitialVelocity = NULL;
		DWORD   m_vInitialPosition = NULL;
	}

	namespace Weapon
	{
		DWORD	m_iClip1 = NULL;
		DWORD	m_flNextPrimaryAttack = NULL;
		DWORD	m_iState = NULL;
		DWORD	m_iItemDefinitionIndex = NULL;
		DWORD   m_iViewModelIndex = NULL;
		DWORD   m_bIsBroken = NULL;
	}

	namespace Entity
	{
		DWORD m_CollisionGroup = NULL;
		DWORD m_Collision = NULL;
		DWORD m_vMins = NULL;
		DWORD m_vMaxs = NULL;
		DWORD m_rgflCoordinateFrame = NULL;
	}

	namespace Bomb
	{
		DWORD m_bBombTicking = NULL;
	}
}
#pragma endregion