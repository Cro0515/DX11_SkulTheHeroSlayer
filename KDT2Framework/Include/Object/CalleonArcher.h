#pragma once

#include "MonsterObject.h"

class CCalleonArcher :
    public CMonsterObject
{
    friend class CScene;

private:

    FVector3D ShootPos;

    float mAttackBeforeDelayAcc = 0.f;
    float mAttackBeforeDelay = 1.0f;


protected:
    CCalleonArcher();
    CCalleonArcher(const CCalleonArcher& Obj);
    CCalleonArcher(CCalleonArcher&& Obj);
    virtual ~CCalleonArcher();



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


private:
    void AttackBegin_Notify();
    void AttackBefor_Notify();

};

