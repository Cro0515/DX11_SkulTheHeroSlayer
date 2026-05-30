#pragma once

#include "MonsterObject.h"

class CCalleonSoldier :
    public CMonsterObject
{
    friend class CScene;



private:
    float mAttackBeginDelayAcc = 0.f;
    float mAttackBeginDelay = 0.8f;

    float mAttackEndDelayAcc = 0.f;
    float mAttackEndDelay = 0.3f;

protected:
    CCalleonSoldier();
    CCalleonSoldier(const CCalleonSoldier& Obj);
    CCalleonSoldier(CCalleonSoldier&& Obj);
    virtual ~CCalleonSoldier();

public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);

public:
    virtual void Attack();
    virtual void Hit(FVector3D dir);

private:
    virtual void AIIdle(float DeltaTime);
    virtual void AIPatrol(float DeltaTime);
    virtual void AITrace(float DeltaTime);
    virtual void AIAttack(float DeltaTime);
    virtual void AIDeath(float DeltaTime);
    virtual void AISkill(float DeltaTime);
    virtual void AICustom(float DeltaTime);
    virtual void AIHit(float DeltaTime);



    virtual void CollisionAttackRangeBegin(const FVector3D& HitPoint, class CColliderBase* Dest);




private:
    void AttackBegin_Notify();
    void AttackEnd_Notify();
};
