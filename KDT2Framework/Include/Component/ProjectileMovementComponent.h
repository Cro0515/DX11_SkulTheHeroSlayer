#pragma once
#include "MovementComponent.h"
class CProjectileMovementComponent :
    public CMovementComponent
{
    friend class CScene;
    friend class CSceneObject;

protected:
	CProjectileMovementComponent();
	CProjectileMovementComponent(const CProjectileMovementComponent& Com);
	CProjectileMovementComponent(CProjectileMovementComponent&& Com);
	virtual ~CProjectileMovementComponent();


protected:
	float mLifeTime = 0.f;
	float mLifeDist = 0.f;
	float mPower = 1.f;


	FVector2D mCompenDist;


	bool bBounce = false;
	bool bReflection = false;

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CProjectileMovementComponent* Clone();
	virtual void EndFrame();




public:
	float GetLifeTime() const
	{
		return mLifeTime;
	}

	float GetLifeDist() const
	{
		return mLifeDist;
	}


public:
	void SetPower(float power)
	{
		mPower = power;
	}

	void SetReflection(bool flag)
	{
		bReflection = flag;
	}

	void SetbBounce(bool flag)
	{
		bBounce = flag;
	}

	void SetCompenDist(FVector2D dist)
	{
		mCompenDist = dist;
	}

	void SetLifeTime(float time)
	{
		mLifeTime = time;
	}

	void SetLifeDist(float dist)
	{
		mLifeDist = dist;
	}

	void SetDir(FVector3D Dir)
	{
		SetMoveDir(Dir);
	}
private:
	bool  MapTileCheck();


};
