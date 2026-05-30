#pragma once
#include "SceneObject.h"


class CArrow :
    public CSceneObject
{
    friend class CScene;
    friend class CCalleonArcher;

protected:
    CArrow();
    CArrow(const CArrow& Obj);
    CArrow(CArrow&& Obj);
    virtual ~CArrow();

protected:
    CSharedPtr<class CSceneComponent>       mRoot;
    CSharedPtr<class CSpriteComponent>      mSprite;
    CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<class CProjectileMovementComponent>    mMovement;
    float   mSpeed = 1500.f;
    float   mMoveDistance = 1500.f;
    int   mDamage = 15;
    class CMonsterObject* mOwner = nullptr;


public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);


private:
    void CollisionBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionEnd(class CColliderBase* Dest);

public:
    void SetDir(FVector3D dir);
    void SetMoveDist(float dist)
    {
        mMoveDistance = dist;
    }
    void SetData(class CMonsterObject* owner, int Damage)
    {
        mOwner = owner;
        mDamage = Damage;
    }

};

