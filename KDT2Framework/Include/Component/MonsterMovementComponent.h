#pragma once
#include "MovementComponent.h"


class CMonsterMovementComponent :
    public CMovementComponent
{
    friend class CScene;
    friend class CSceneObject;
 

protected:
    CMonsterMovementComponent();
    CMonsterMovementComponent(const CMonsterMovementComponent& Com);
    CMonsterMovementComponent(CMonsterMovementComponent&& Com);
    virtual ~CMonsterMovementComponent();


protected:
    bool			bGround = false;
    bool			bMove = true;
    FVector3D	    tempMoveStep;


public:
    virtual bool Init();
    virtual bool Init(const char* FileName);
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CMonsterMovementComponent* Clone();
    virtual void EndFrame();


public:
    FVector3D GetTempMoveStep()
    {
        return tempMoveStep;
    };



public:
    bool	MoveTileCheck();
    bool    MoveTileCheckX();
   

};

