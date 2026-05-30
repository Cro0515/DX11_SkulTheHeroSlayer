#pragma once

#include "SceneComponent.h"

enum class ECameraProjectionType
{
	Perspective,	// 원근 투영 - 깊이(Z)값에 따른 크기조절로 3D에서 사용
	Ortho			// 직교 투영 - x,y만 사용한 평면출력 2D에서 사용
};

class CCameraComponent :
    public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& Com);
	CCameraComponent(CCameraComponent&& Com);
	virtual ~CCameraComponent();

protected:
	ECameraProjectionType	mProjType = ECameraProjectionType::Perspective;		// 투영 타입
	FMatrix	mmatView;				// 뷰 행렬
	FMatrix	mmatProj;				// 투영 행렬
	
	float mViewAngle = 90.f;		// 카메라 FOV값
	float mWidth = 1920.f;			// 카메라 해상도 (가로)
	float mHeight = 1080.f;			// 카메라 해상도 (세로)
	float mViewDistance = 100.f;	// 카메라 시야거리
	float mCameraZoomLevel = 2.f;	// 카메라 확대 레벨

	float mMapWidth = 0.f;
	float mMapHeight = 0.f;

	CSceneObject* mTarget = nullptr;

public:

	float GetCameraHalfWidth()
	{
		return mWidth / 2;
	}

	float GetCameraHalfHeight()
	{
		return mHeight / 2;
	}

	float GetMapWidth()
	{
		return mMapWidth;
	}
	
	float GetMapHeight()
	{
		return mMapHeight;
	}

	const float GetCameraZoomLevel()
	{
		return mCameraZoomLevel;
	}

	const FMatrix& GetViewMatrix()	const
	{
		return mmatView;
	}

	const FMatrix& GetProjMatrix()	const
	{
		return mmatProj;
	}

	

public:
	void SetMapSize(float Width, float Height)
	{
		mMapWidth = Width;
		mMapHeight = Height;
	}

	void SetTarget(CSceneObject* Target)
	{
		mTarget = Target;
	}

	void SetProjectionType(ECameraProjectionType Type);
	void SetViewAngle(float Angle)
	{
		mViewAngle = Angle;
	}

	void SetViewResolution(float Width, float Height)
	{
		mWidth = Width;
		mHeight = Height;
	}

	void SetViewDistance(float Dist)
	{
		mViewDistance = Dist;
	}

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
	virtual CCameraComponent* Clone();
};

