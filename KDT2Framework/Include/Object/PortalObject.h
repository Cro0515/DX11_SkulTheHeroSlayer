#pragma once
#include "SceneObject.h"

enum class EPortalType : unsigned int
{
    Normal,
    Boss,
    End
};



class CPortalObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CPortalObject();
    CPortalObject(const CPortalObject& Obj);
    CPortalObject(CPortalObject&& Obj);
    virtual ~CPortalObject();


protected:
    CSharedPtr<class CSpriteComponent>      mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<class CWidgetComponent>      mInfoWidget;


    EPortalType mPortalType = EPortalType::Normal;
    bool mWorking = false;       // 포탈 열림 닫힘 유무
    bool mDetect = false;       // 포탈이 캐릭터와 접촉 유무

public:
    bool GetWorking() const
    {
        return mWorking;
    }

    bool GetDetect() const
    {
        return mDetect;
    }

    class CColliderAABB2D* GetBody() const
    {
        return mBody;
    }


public:
    void SetPortalType(EPortalType type);

    void SetWorking(bool flag);
  

    void SetDetect(bool flag)
    {
        mDetect = flag;
    }

    void SetTexture(const std::string& Name,
        const TCHAR* FileName,
        int TextureIndex = 0);

public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();


private:
    void PortalBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
    void PortalEnd(class CColliderBase* Dest);
    void PortalOpen();
    void PortalClose();

};

