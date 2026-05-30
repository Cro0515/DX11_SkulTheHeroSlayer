#include "Arrow.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/ProjectileMovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/SpriteComponent.h"
#include "../Object/PlayerObject.h"
#include "../Object/SpriteEffect.h"
#include "../Scene/Scene.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Scene/SceneAssetManager.h"

CArrow::CArrow()
{
}

CArrow::CArrow(const CArrow& Obj) :
	CSceneObject(Obj)
{
}

CArrow::CArrow(CArrow&& Obj) :
	CSceneObject(Obj)
{
}

CArrow::~CArrow()
{
}

bool CArrow::Init()
{
	mRoot = CreateComponent<CSceneComponent>();
	mSprite = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	mMovement = CreateComponent<CProjectileMovementComponent>();
	SetRootComponent(mRoot);
	mCollision = mBody;
	bUseGravity = false;


	mSprite->SetTexture("Arrow", TEXT("Texture/Monster/CalleonArcher/Arrow.png"));
	mSprite->SetPivot(0.5f, 0.5f);
	mSprite->SetWorldScale(100.f * 2.f, 15.f * 2.f, 1.f);
	mRoot->AddChild(mSprite);


	mBody->SetCollisionProfile("MonsterAttack");
	mBody->SetBoxSize(80, 10.f);
	mBody->SetCollisionBeginFunc<CArrow>(this, &CArrow::CollisionBegin);
	mRoot->AddChild(mBody);


	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::X);
	mMovement->SetMoveSpeed(mSpeed);
	mMovement->SetCompenDist(FVector2D(80.f/2,10.f/2));



	

	return true;
}

void CArrow::PreUpdate(float DeltaTime)
{
	CSceneObject::PreUpdate(DeltaTime);
}

void CArrow::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mMoveDistance -= mMovement->GetMoveDistance();


	float test = mMovement->GetMoveStep().Length();
	if (mMoveDistance <= 0.f || mMovement->GetMoveStep().Length() == 0)
	{
		Destroy();
	}
}

void CArrow::CollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CSceneObject* Obj = Dest->GetOwner();
	CPlayerObject* Player = dynamic_cast<CPlayerObject*>(Obj);
	
	if (Player)
		Player->TakeDamage(mDamage, this);


	CSpriteEffect* ArcherHitEffect = mScene->CreateObj<CSpriteEffect>("ArcherHitEffect_Obj");
	ArcherHitEffect->SetAnimation("ArcherHitEffect");
	ArcherHitEffect->SetPlayRate("ArcherHitEffect", 2.f);
	FVector3D EffectPos = HitPoint;
	ArcherHitEffect->SetWorldPos(HitPoint);
	ArcherHitEffect->SetWorldScale(150.f * gScaleMult, 100.f * gScaleMult);


	mScene->GetAssetManager()->FindSound("ArcherAttackHit")->Play();


	Destroy();
}

void CArrow::CollisionEnd(CColliderBase* Dest)
{
}

void CArrow::SetDir(FVector3D dir)
{
	// 왼쪽 방향이고, Speed가 양수일때
	// 오른쪽 방향이고, Speed가 음수일때
	if (dir.x < 0 && 0 < mSpeed ||
		dir.x > 0 && mSpeed < 0)
	{
		mSpeed *= -1.f;
	}
	else
	{
		return;
	}

	mMovement->SetMoveSpeed(mSpeed);
}
