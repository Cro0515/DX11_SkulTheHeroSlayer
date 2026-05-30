#pragma once

#include "SceneObject.h"

class CCameraObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CCameraObject();
    CCameraObject(const CCameraObject& Obj);
    CCameraObject(CCameraObject&& Obj);
    virtual ~CCameraObject();

protected:
    CSharedPtr<class CCameraComponent>  mRoot;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);


public:
    void SetTarget(CSceneObject* Obj);
    void SetMapSize(float Width, float Height);

public:
    class CCameraComponent* GetCameraComponenet() const
    {
        return mRoot;
    }

};

