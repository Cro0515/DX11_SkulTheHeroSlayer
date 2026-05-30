#pragma once

#include "SceneObject.h"

class CSpriteEffect :
    public CSceneObject
{
    friend class CScene;

protected:
    CSpriteEffect();
    CSpriteEffect(const CSpriteEffect& Obj);
    CSpriteEffect(CSpriteEffect&& Obj);
    virtual ~CSpriteEffect();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;      // 출력 할 스프라이트 컴포넌트
    class CAnimation2D* mAnimation = nullptr;       // 이펙트를 출력하기 위한 애니메이션 매니저 클래스
    CSharedPtr<class CAudioComponent>  mAudio;      // 사운드 출력을 위한 오디오 컴포넌트
    bool        mLoop = false;                      // 반복재생 여부

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void SetAnimation(const std::string& Name,
        float PlayTime = 1.f, float PlayRate = 1.f,
        bool Loop = false, bool Reverse = false);

    void SetPlayRate(const std::string& Name, float PlayRate);
    void SetAnimationReverseX(bool flag);
private:
    void AnimationEnd();
};

