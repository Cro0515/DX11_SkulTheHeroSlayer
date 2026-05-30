#pragma once

#include "SceneObject.h"

enum class EMonsterAI : unsigned char
{
    Idle,   
    Patrol,
    Trace,
    Attack,
    Death,
    Skill,
    Custom,
    Hit,
    End,
};

class CMonsterObject :
    public CSceneObject
{
    friend class CScene;
    friend class CCalleonSoldier;
    friend class CCalleonArcher;

protected:
    CMonsterObject();
    CMonsterObject(const CMonsterObject& Obj);
    CMonsterObject(CMonsterObject&& Obj);
    virtual ~CMonsterObject();

protected:
    CSharedPtr<class CSpriteComponent>      mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;              // 몸통 콜리전
    CSharedPtr<class CColliderAABB2D>       mDetectCollision;   // 감지 콜리전
    CSharedPtr<class CColliderAABB2D>       mAttackCollision;   // 공격 콜리전
    CSharedPtr<class CMonsterMovementComponent>    mMovement;
    CSharedPtr<class CWidgetComponent>      mInfoWidget;             // HP바
    CSharedPtr<class CProgressBar>          mHPBar;
    


    CSharedPtr<CSceneObject>                mTarget;            // 타겟
    class CAnimation2D* mAnimation = nullptr;
    EMonsterAI          mAI = EMonsterAI::Idle;
    std::string         mAIAnimationName[(int)EMonsterAI::End];


    int             mHP = 50;                   // 체력
    int             mHPMax = 50;                   // 체력
    int             mDamage = 10;               // 데미지



    float           mDetectDistance = 0.f;      // 감지 콜리전 거리
    FVector2D       mDetectAdd;                 // 감지시 감지거리 증가값

    float           mAttackRange = 0.f;         // 공격 콜리전 범위
    float           mAttackCoolAcc = 0.f;       // 공격 쿨타임 누적용
    float           mAttackCool = 2.f;          // 공격 쿨타임
    float           mSpeed = 300.f;             // 스피드
    bool            bAttacking = false;         // 공격 애니메이션 출력중


    float           mPatrolCoolAcc = 0.f;       // 패트롤 쿨타임 누적용
    float           mPatrolCooltime = 2.f;      // 패트롤 쿨타임
    int             mPatrolDist = 0.f;          // 패트롤 이동 거리
    float           mPatrolDistMin = 200.f;     // 패트롤 이동 최소거리
    float           mPatrolDistMax = 400.f;     // 패트롤 이동 최대거리

    bool            bHitAnimFlag = true;


    bool bDir = true;
    int  IDir = 0;

    bool            bAnimBegin = false;
    bool            bAnimEnd = false;
    float           mDelayAccTime = 0.f;
    float           mDelayTime = 0.f;


public:
    void SetDelayTime(float time)
    {
        mDelayTime = time;
    }


    void SetAnimBegin()
    {
        bAnimBegin = true;
    }


    void SetAnimEnd()
    {
        bAnimEnd = true;
    }

    void SetTarget(class CSceneObject* Target)
    {
        mTarget = Target;
    }



public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);

public:
    virtual float TakeDamage(float Attack, CSceneObject* Obj);
    virtual void Attack();
    virtual void Hit(FVector3D dir);

protected:
    virtual void DetectTarget();
    virtual void DetectTargetRelease();

private:
    virtual void CollisionMonsterBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
    virtual void CollisionMonsterEnd(class CColliderBase* Dest);
    
    virtual void CollisionDetectBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
    virtual void CollisionDetectOverlap(class CColliderBase* Dest);
    virtual void CollisionDetectEnd(class CColliderBase* Dest);
    
    virtual void CollisionAttackRangeBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
    virtual void CollisionAttackRangeOverlap(class CColliderBase* Dest);
    virtual void CollisionAttackRangeEnd(class CColliderBase* Dest);


protected:  // ============ AI Virtual Function ===============
    virtual void AIIdle(float DeltaTime);
    virtual void AIPatrol(float DeltaTime);
    virtual void AITrace(float DeltaTime);
    virtual void AIAttack(float DeltaTime);
    virtual void AIDeath(float DeltaTime);
    virtual void AISkill(float DeltaTime);
    virtual void AICustom(float DeltaTime);
    virtual void AIHit(float DeltaTime);
        
};