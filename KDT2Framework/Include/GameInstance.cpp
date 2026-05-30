#include "GameInstance.h"

DEFINITION_SINGLE(CGameInstance)

CGameInstance::CGameInstance()
{
}

CGameInstance::~CGameInstance()
{
	
}


bool CGameInstance::Init()
{
    mPlayerData.mHP = 100;
    mPlayerData.mHPMax = 100;
    mPlayerData.mDamage = 20;

    mPlayerData.mMoveDir = EPlayerDir::Right;
    mPlayerData.mSaveDir = EPlayerDir::None;

    mPlayerData.mSkillA_CoolAcc = 0.f;
    mPlayerData.mSkillB_CoolAcc = 0.f;

	return true;
}
