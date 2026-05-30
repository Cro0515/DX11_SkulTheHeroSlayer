#include "SkullHead.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/ProjectileMovementComponent.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/SpriteComponent.h"
#include "../Share/Log.h"
#include "PlayerObject.h"
#include "MonsterObject.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAssetManager.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Asset/AssetManager.h"
CSkullHead::CSkullHead()
{
}

CSkullHead::CSkullHead(const CSkullHead& Obj) :
	CSceneObject(Obj)
{
}

CSkullHead::CSkullHead(CSkullHead&& Obj) :
	CSceneObject(Obj)
{
}

CSkullHead::~CSkullHead()
{
	if(mOwner->GetSkulHead() != nullptr)
		mOwner->DestroySkull();
}

bool CSkullHead::Init()
{
	mRoot = CreateComponent<CSceneComponent>();
	mSprite = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderSphere2D>();
	mMovement = CreateComponent<CProjectileMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();
	SetRootComponent(mRoot);
	mCollision = mBody;
	bUseGravity = false;

	mSprite->SetTexture("SkullHead", TEXT("Texture/Character/LittleBone/LittleBone_Skill.png"));
	mSprite->SetPivot(0.5f, 0.5f);
	mSprite->SetWorldScale(15.f * gScaleMult,13.f * gScaleMult, 1.f);
	mRoot->AddChild(mSprite);

	mBody->SetRadius(23.f);
	mBody->SetCollisionProfile("SkulHead");
	mBody->SetCollisionBeginFunc<CSkullHead>(this, &CSkullHead::CollisionBegin);
	mRoot->AddChild(mBody);

	mMovement->SetUpdateComponent(mRoot);
	//mMovement->SetMoveAxis(EAxis::X);
	mMovement->SetMoveSpeed(mSpeed);
	mMovement->SetCompenDist(FVector2D(23.f, 23.f));
	mMovement->SetReflection(true);

	mRotation->SetUpdateComponent(mSprite);
	mRotation->SetVelocityInit(false);
	mRotation->SetMoveZ(360.f);
	mRotation->SetSpeedFactor(-2.f);

	return true;
}

void CSkullHead::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mMoveDistance -= mMovement->GetMoveDistance();

	if (mMoveDistance <= 0.f)
	{
		// 튕기기


		// 부모 오브젝트에 등록된 SkullHead 제거
		//mOwner->DestroySkull();
		//Destroy();
	}

}





void CSkullHead::CollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CLog::Debug("스컬 헤드 충돌");

	bUseGravity = true;

	CSceneObject* Obj = Dest->GetOwner();

	CPlayerObject* Player = dynamic_cast<CPlayerObject*>(Obj);
	CMonsterObject* Monster = dynamic_cast<CMonsterObject*>(Obj);
	mScene->GetAssetManager()->FindSound("SkulHeadHit")->Play();


	if (Player)
	{
		Player->SkillA_Reset();
		
		// 헤드 제거
		mOwner->DestroySkull();
		Destroy();


		return;
	}
	else if (Monster)
	{
		Monster->TakeDamage(mDamage, this);

		// 머리 팅기기
		FVector3D imp = mMovement->GetMoveDir();

		FVector3D v = FVector3D(-imp.x, 5.f, 1);
		v.Normalize();

		// 파워 설정
		//mMovement->SetPower(500.f);
		mMovement->SetMoveDir(FVector3D(-imp.x, 1, 1));
		return;
	}


}

void CSkullHead::SetDir(EPlayerDir dir)
{
	if (dir == EPlayerDir::Left)
	{
		mMovement->SetMoveDir(FVector3D(-1, 0, 0));
	}
	else
	{
		mMovement->SetMoveDir(FVector3D(1, 0, 0));
	}



	/*if (dir == EPlayerDir::Right && mSpeed < 0 ||
		dir == EPlayerDir::Left && mSpeed > 0)
	{
		mSpeed *= -1.f;
	}
	else
	{
		return;
	}

	mMovement->SetMoveSpeed(mSpeed);*/
}

