#pragma once

#include "SceneComponent.h"
#include "../Animation/Animation2D.h"

class CSpriteComponent :
    public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSpriteComponent();
	CSpriteComponent(const CSpriteComponent& Com);
	CSpriteComponent(CSpriteComponent&& Com);
	virtual ~CSpriteComponent();

protected:
	CSharedPtr<class CMesh>			mMesh;		// 메쉬
	CSharedPtr<class CShader>		mShader;	// 쉐이더
	CSharedPtr<class CTexture>		mTexture;	// 이미지 텍스쳐
	CAnimation2D* mAnimation = nullptr;			// 애니메이션 
	FVector4D	mTint = FVector4D::White;		// 색상 설정
	float		mFlickerValue = 0.f;			// 플리커 효과 적용값
	float		mFlickerInit = 0.8f;			// 플리커 효과 초기값
	int			mTextureIndex = 0;				// 텍스쳐 인덱스
	class CSpriteCBuffer* mSpriteCBuffer = nullptr;		// 스프라이트용 상수 버퍼

public:
	template <typename T>
	T* GetAnimationInstance()	const
	{
		return dynamic_cast<T*>(mAnimation);
	}

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);
	void SetTexture(const std::string& Name,
		int TextureIndex = 0);
	void SetTexture(const std::string& Name,
		const TCHAR* FileName,
		int TextureIndex = 0);
	void SetTexture(class CTexture* Texture,
		int TextureIndex = 0);
	void SetTint(float r, float g, float b);
	void SetOpacity(float Opacity);
	void SetTextureIndex(int Index);
	void SetPlayRate(const std::string& Name, float PlayRate);
	void FlickerStart();

	void SetAnimationReverseX(bool Reverse);



public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CSpriteComponent* Clone();

public:
	template <typename T>
	T* CreateAnimation2D()
	{
		mAnimation = new T;

		mAnimation->mOwner = this;
		mAnimation->mScene = mScene;

		if (!mAnimation->Init())
		{
			SAFE_DELETE(mAnimation);
			return nullptr;
		}

		return (T*)mAnimation;
	}
};

