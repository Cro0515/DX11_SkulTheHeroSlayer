#pragma once

#include "GameInfo.h"

class CGameInstance
{
private:

    FPlayerData mPlayerData;

public:
    bool Init();

    void SetPlayerData(FPlayerData _data) { mPlayerData = _data; }

    void SetHP(int _HP) { mPlayerData.mHP = _HP; }

    void SetHPMax(int _HpMax) { mPlayerData.mHPMax = _HpMax; }

    void SetDamage(int _Damage) { mPlayerData.mDamage = _Damage;  }

    void SetSkillACool(float _Cool) { mPlayerData.mSkillA_CoolAcc = _Cool; }

    void SetSkillBCool(float _Cool) { mPlayerData.mSkillB_CoolAcc = _Cool; }

public:
    FPlayerData GetPlayerData() { return mPlayerData; }

    int GetHP(int _HP) { return mPlayerData.mHP; }

    int GetHPMax(int _HpMax) { return mPlayerData.mHPMax; }

    int GetDamage(int _Damage) { return mPlayerData.mDamage; }

    float GetSkillACool(float _Cool) { return mPlayerData.mSkillA_CoolAcc; }

    float GetSkillBCool(float _Cool) { return mPlayerData.mSkillB_CoolAcc; }

    DECLARE_SINGLE(CGameInstance)
};

