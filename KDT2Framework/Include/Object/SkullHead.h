#pragma once
#include "SceneObject.h"


class CSkullHead :
    public CSceneObject
{
    friend class CScene;
    friend class CPlayerObject;

protected:
    CSkullHead();
    CSkullHead(const CSkullHead& Obj);
    CSkullHead(CSkullHead&& Obj);
    virtual ~CSkullHead();

protected:
    CSharedPtr<class CSceneComponent>       mRoot;
    CSharedPtr<class CSpriteComponent>      mSprite;
    CSharedPtr<class CColliderSphere2D>     mBody;
    CSharedPtr<class CProjectileMovementComponent>    mMovement;
    CSharedPtr<class CRotationComponent>    mRotation;
    int     mDamage = 20.f;
    float   mSpeed = 1000.f;
    float   mMoveDistance = 1000.f;
    class CPlayerObject* mOwner = nullptr;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);


private:
    void CollisionBegin(const FVector3D& HitPoint, class CColliderBase* Dest);

public:
    void SetDir(EPlayerDir dir);
    void SetOwner(class CPlayerObject* owner) 
    {
        mOwner = owner;
    }
};

