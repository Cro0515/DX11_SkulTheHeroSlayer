#pragma once

#include "SceneObject.h"


enum class EAnimState
{
    Idle,
    Walk,
    Dash,
    Jump,
    Fall,
    Attack,
    JumpAttack,
    SkillA,
    SkillS,
    Death,
};



class CPlayerObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CPlayerObject();
    CPlayerObject(const CPlayerObject& Obj);
    CPlayerObject(CPlayerObject&& Obj);
    virtual ~CPlayerObject();

protected:
    CSharedPtr<class CSpriteComponent>      mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<class CColliderAABB2D>       mAttackCollider;
    CSharedPtr<class CCharacterMovementComponent>    mMovement;
    class CMainWidget* mMainWidget; 



    class CAnimation2D* mAnimation = nullptr;
    class CSkullHead* mSkullHead = nullptr;

    bool                mAutoBasePose = true;
    //int                 mHP = 100;
    int                 mHP = 0;
    //int                 mHPMax = 200;
    int                 mHPMax = 0;
    //int                 mDamage = 10;
    int                 mDamage = 0;
    //EPlayerDir          mMoveDir = EPlayerDir::Right;
    //EPlayerDir          mSaveDir = EPlayerDir::None;
    EPlayerDir          mMoveDir = EPlayerDir::None;
    EPlayerDir          mSaveDir = EPlayerDir::None;


    EAnimState          mAnimState = EAnimState::Idle;


    bool                bAttackCombo = false;

    float               mDashTime = 0.8f;           // 대쉬 시간
    float               mDashAccTime = 0.f;         // 대쉬 누적시간
    FVector3D           mDashStartPos;              // 대쉬 시작위치
    FVector3D           mDashTargetPos;             // 대쉬 도착위치
    float               mDashDist = 300.f;          // 대쉬 거리
    bool                bDoubleDash = true;         // 더블대쉬 가능여부
    float               mDashCool = 0.3f;           // 대쉬 쿨타임
    float               mDashCoolCalc = 0.f;        // 대쉬 쿨타임 계산용
    
    float               mJumpAccTime = 0.f;         // 점프 누적시간
    float               mJumpTime = 0.5f;           // 점프 지속시간
    bool                bDoubleJump = true;         // 더블점프 가능여부
    bool                bJumpAttack = false;        // 점프어택 가능여부  

    //float               mSkillA_CoolAcc = 0.f;      // 쿨타임 계산용
    float               mSkillA_CoolAcc = 999.f;      // 쿨타임 계산용
    float               mSkillA_Cool = 6.f;         // 해골 던지기 스킬 쿨타임 

    //float               mSkillB_CoolAcc = 0.f;      // 쿨타임 계산용
    float               mSkillB_CoolAcc = 999.f;      // 쿨타임 계산용
    float               mSkillB_Cool = 3.f;         // 해골 던지기 스킬 쿨타임 


    bool                bKey_F_Press = false;       // F키 누른
    bool                bDeathFinish = false;
   
    std::string mAttackSoundName;


public:
    EAnimState GetAnimState() const
    {
        return mAnimState;
    }

    class CSkullHead* GetSkulHead() const
    {
        return mSkullHead;
    }

    FPlayerData GetPlayerData() 
    { 
        FPlayerData data;

        data.mHP = mHP;
        data.mHPMax = mHPMax;
        data.mDamage = mDamage;

        data.mMoveDir = mMoveDir;
        data.mSaveDir = mSaveDir;

        data.mSkillA_CoolAcc = mSkillA_CoolAcc;
        data.mSkillB_CoolAcc = mSkillB_CoolAcc;

        return data;
    }

    int GetHP() { return mHP; }

    int GetHPMax() { return mHPMax; }

    int GetDamage() { return mDamage; }

    float GetSkillACool() { return mSkillA_CoolAcc; }

    float GetSkillBCool() { return mSkillB_CoolAcc; }

    bool GetKey_F_Press() { return bKey_F_Press; }

public:
    void SetAnimState(EAnimState state)
    {
        mAnimState = state;
    }

    void SetPlayerData(FPlayerData data)
    {
        mHP = data.mHP;
        mHPMax = data.mHPMax;
        mDamage = data.mDamage;

        mMoveDir = data.mMoveDir;
        mSaveDir = data.mSaveDir;

        mSkillA_CoolAcc = data.mSkillA_CoolAcc;
        mSkillB_CoolAcc = data.mSkillB_CoolAcc;

    }

    void SetHP(int _HP) { mHP = _HP; }

    void SetHPMax(int _HpMax) { mHPMax = _HpMax; }

    void SetDamage(int _Damage) { mDamage = _Damage; }

    void SetSkillACool(float _Cool) { mSkillA_CoolAcc = _Cool; }

    void SetSkillBCool(float _Cool) { mSkillB_CoolAcc = _Cool; }


public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual float TakeDamage(float Attack, CSceneObject* Obj);


private:
    void KeyBind();
    void AnimBind();



    void IdleNotify();

    void MoveRight(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveKey_Release(float DeltaTime);
    void WalkNotify();

    void Jump(float DeltaTime);
    void JumpEnd();
    void FallEnd();
    void FallRepeatEnd();

    void Attack(float DeltaTime);
    void AttackNotify();
    void AttackEnd();
    void ComboAttackNotify();
    void JumpAttackEnd();

    void Hit(FVector3D KnokBackDir);


    void Dash(float DeltaTime);
    void DashEnd();

    void SkillA(float DeltatTime);
    void SkillAEnd();
    void SkillA_HeadThrow();

    void SkillS(float DeltatTime);

    void SkillUpdate(float DeltaTime);

    void DeathEnd();


    void HPPlus(float DeltaTime);
    void HPMinus(float DeltaTime);
    void DamagePlus(float DeltaTime);


public:
    void DestroySkull();
    void SkillA_Reset();


private:
    virtual void AttackCollider_Begin(const FVector3D& HitPoint, class CColliderBase* Dest);
    
};

