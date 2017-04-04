#pragma once

#include "Main.h"

namespace Offsets
{
	extern void				Init(void);

	namespace Player
	{
		extern DWORD	m_iHealth;
		extern DWORD	m_ArmorValue;
		extern DWORD	m_iTeamNum;
		extern DWORD	m_fFlags;
		extern DWORD    m_iAccount;
		extern DWORD    m_szLastPlaceName;
		extern DWORD	m_lifeState;
		extern DWORD	m_bIsDefusing;
		extern DWORD	m_Local;
		extern DWORD    m_flC4Blow;
		extern DWORD	m_aimPunchAngle;
		extern DWORD    m_ViewPunchAngle;
		extern DWORD	m_hOwner;
		extern DWORD	m_iPlayerC4;
		extern DWORD	m_iCompetitiveRanking;
		extern DWORD	m_flDefuseLength;
		extern DWORD	m_bSpotted;
		extern DWORD	m_bHasDefuser;
		extern DWORD	m_BombTimer;
		extern DWORD	m_bIsScoped;
		extern DWORD	m_iKills;
		extern DWORD	m_vOrigin;
		extern DWORD	m_flFlashDuration;
		extern DWORD	m_flFlashMaxAlpha;
		extern DWORD	m_vViewOffset;
		extern DWORD	m_bGunGameImmunity;
		extern DWORD	m_dwWeaponTableIndex;
		extern DWORD	m_nTickBase;
		extern DWORD    m_dwLoadFromBuffer;
		extern DWORD    m_hObserverTarget;
		extern DWORD    m_totalHitsOnServer;
		extern DWORD    m_hConstraintEntity;
		extern DWORD    m_iObserverMode;

		extern DWORD	m_hActiveWeapon;
		extern DWORD	m_iShotsFired;
		extern DWORD	m_vVelocity;
		extern DWORD	m_angEyeAngles;
		extern DWORD	m_vEyeAngles;
		extern DWORD	m_bHasHelmet;
		extern DWORD	m_nHitboxSet;
		extern DWORD	m_clrRender;
		extern DWORD	m_vAngles;
		extern DWORD	m_iCompetitiveWins;

		extern DWORD   m_vInitialVelocity;
		extern DWORD   m_vInitialPosition;
	}

	namespace Attribute
	{
		extern DWORD m_iItemDefinitionIndex;
		extern DWORD m_iItemIDHigh;
		extern DWORD m_iItemIDLow;
		extern DWORD m_OriginalOwnerXuidLow;
		extern DWORD m_OriginalOwnerXuidHigh;
		extern DWORD m_nFallbackPaintKit;
		extern DWORD m_nFallbackSeed;
		extern DWORD m_flFallbackWear;
		extern DWORD m_nFallbackStatTrak;
	}

	namespace Weapon
	{
		extern DWORD	m_iClip1;
		extern DWORD	m_flNextPrimaryAttack;
		extern DWORD	m_iState;
		extern DWORD	m_iItemDefinitionIndex;
		extern DWORD 	m_iViewModelIndex;
		extern DWORD    m_bIsBroken;
	}

	namespace Entity
	{
		extern DWORD m_CollisionGroup;
		extern DWORD m_Collision;
		extern DWORD m_vMins;
		extern DWORD m_vMaxs;
		extern DWORD m_rgflCoordinateFrame;
	}

	namespace Bomb
	{
		extern DWORD m_bBombTicking;
	}
}