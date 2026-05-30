#pragma once

#include "SceneObject.h"

class CEditorPlayer :
    public CSceneObject
{
    friend class CScene;

protected:
    CEditorPlayer();
    CEditorPlayer(const CEditorPlayer& Obj);
    CEditorPlayer(CEditorPlayer&& Obj);
    virtual ~CEditorPlayer();

protected:
    CSharedPtr<class CSceneComponent>       mRoot;
    CSharedPtr<class CCharacterMovementComponent>    mMovement;


    float mLimitMinX = 0.f;
    float mLimitMinY = 0.f;
    float mLimitMaxX = 0.f;
    float mLimitMaxY = 0.f;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
};

