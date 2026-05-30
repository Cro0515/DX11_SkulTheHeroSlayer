#pragma once

#include "Component.h"

class CMovementComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;
	friend class CCharacterMovementComponent;
	friend class CProjectileMovementComponent;

protected:
	CMovementComponent();
	CMovementComponent(const CMovementComponent& Com);
	CMovementComponent(CMovementComponent&& Com);
	virtual ~CMovementComponent();

protected:
	CSharedPtr<class CSceneComponent>	mUpdateComponent;
	EAxis::Type		mMoveAxis = EAxis::None;
	//class CNavAgent* mNavAgent = nullptr;

protected:
	FVector3D		mMoveDir;
	FVector3D		mMoveStep;
	float			mSpeed = 1.f;
	bool			mVelocityInit = true;

	float			mGravity = -9.8f;

	bool			bOnKnockBack = false;
	float			mKnockBackAccTime = 0.f;
	float			mKnockBackTime = 0.5f;
	float			mKnockBackSpeed = 300.f;
	FVector3D		mKnockBackDir;

public:
	FVector3D GetMoveDir()
	{
		return mMoveDir;
	}

	bool GetKnockBack()
	{
		return bOnKnockBack;
	}

	const FVector3D& GetMoveStep()	const
	{
		return mMoveStep;
	}

	const FVector3D& GetVelocity()	const
	{
		return mMoveDir;
	}

	float GetVelocityLength()	const
	{
		return mMoveDir.Length();
	}

	float GetMoveDistance()	const
	{
		return mMoveStep.Length();
	}

public:
	void SetMoveStep(const FVector3D& Pos)
	{
		mMoveStep = Pos;
	}

	void SetUpdateComponent(class CSceneComponent* Target);
	
	void SetMoveSpeed(float Speed)
	{
		mSpeed = Speed;
	}

	void AddMove(const FVector3D& Dir)
	{
		mMoveDir += Dir;
	}

	void SetMoveDir(const FVector3D& Dir)
	{
		mMoveDir = Dir;
	}

	void SetVelocityInit(bool VelocityInit)
	{
		mVelocityInit = VelocityInit;
	}

	void SetMoveAxis(EAxis::Type Axis)
	{
		mMoveAxis = Axis;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMovementComponent* Clone();
	virtual void EndFrame();
	virtual void KnockBack(FVector3D dir, float Time = 0.5f, float Speed = 300.f);

};


