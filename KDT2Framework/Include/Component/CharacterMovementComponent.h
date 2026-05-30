#pragma once
#include "MovementComponent.h"
class CCharacterMovementComponent :
    public CMovementComponent
{
    friend class CScene;
    friend class CSceneObject;

protected:
	CCharacterMovementComponent();
	CCharacterMovementComponent(const CCharacterMovementComponent& Com);
	CCharacterMovementComponent(CCharacterMovementComponent&& Com);
	virtual ~CCharacterMovementComponent();

protected:
	bool			bGround = false;
	bool			bJump = true;
	bool			bEditMode = false;
	bool			bMove = true;
	FVector3D	    tempMoveStep;

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CCharacterMovementComponent* Clone();
	virtual void EndFrame();

public:
	bool GetMovePossible()
	{
		return bMove;
	}

	FVector3D GetTempMoveStep()
	{
		return tempMoveStep;
	}

public:
	void SetEditMode(bool flag)
	{
		bEditMode = flag;
	}

	void SetGround(bool flag)
	{
		bGround = flag;
	}

	bool IsGround() const
	{
		return bGround;
	}


public:
	bool	MoveTileCheck();


};

