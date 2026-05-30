#include "ProjectileMovementComponent.h"
#include "MovementComponent.h"
#include "../Share/Log.h"
#include "../Scene/Scene.h"
#include "../Object/TileMapObj.h"
#include "../Component/Tile.h"
#include "../Component/ColliderBase.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderAABB2D.h"

CProjectileMovementComponent::CProjectileMovementComponent()
{
}

CProjectileMovementComponent::CProjectileMovementComponent(
	const CProjectileMovementComponent& Com) :
	CMovementComponent(Com)
{
}

CProjectileMovementComponent::CProjectileMovementComponent(
	CProjectileMovementComponent&& Com) :
	CMovementComponent(Com)
{
}

CProjectileMovementComponent::~CProjectileMovementComponent()
{
}

bool CProjectileMovementComponent::Init()
{
	if (!CMovementComponent::Init())
		return false;

	return true;
}

bool CProjectileMovementComponent::Init(const char* FileName)
{
	if (!CMovementComponent::Init(FileName))
		return false;

	return true;
}

void CProjectileMovementComponent::PreUpdate(float DeltaTime)
{
	CMovementComponent::PreUpdate(DeltaTime);


}

void CProjectileMovementComponent::Update(float DeltaTime)
{
	CMovementComponent::Update(DeltaTime);

	if (1.f <= mPower)
	{
		mPower -= DeltaTime * 30.f;

		if (mPower < 1.f)
			mPower = 1.f;
	}


	// 방향벡터가 있다면,
	if (mMoveDir.Length() > 0.f)
	{
		// 이동 할 벡터 구하기
		mMoveStep = mMoveDir * mSpeed * DeltaTime * mPower;
	}

	if (mOwnerObject->GetUseGravity())
	{
		mMoveStep.y += mGravity * 50.f * DeltaTime * mPower;
	}

	bool move = true;

	// 소유한 오브젝트가 콜리전이 있다면,
	if (mOwnerObject->IsCollision())
	{
		move = MapTileCheck();
	}

	if (move == true)
		mUpdateComponent->AddWorldPos(mMoveStep);
	else
		mMoveStep = FVector3D(0.f, 0.f, 0.f);
}

void CProjectileMovementComponent::PostUpdate(float DeltaTime)
{
	CMovementComponent::PostUpdate(DeltaTime);


}

CProjectileMovementComponent* CProjectileMovementComponent::Clone()
{
	return new CProjectileMovementComponent(*this);
}

void CProjectileMovementComponent::EndFrame()
{
	//CMovementComponent::EndFrame();


	if (mVelocityInit)
		mMoveDir = FVector3D::Zero;
}

bool CProjectileMovementComponent::MapTileCheck()
{
	// 현재위치에 mMoveStep 더한다.
	// UpdateComponent의 현재위치를 가져온다.
	FVector3D ownerPos = mUpdateComponent->GetWorldPosition();
	
	// 타일맵 오브젝트 가져오기
	CTileMapObj* tileObj = mScene->GetTileMapObj();
	if (tileObj == nullptr)
		return false;

	// 충돌체 종류 받아오기
	CColliderBase* Collision = mOwnerObject->GetCollision();
	EColliderShape Shape = Collision->GetColliderShape();
	CColliderAABB2D* Box = dynamic_cast<class CColliderAABB2D*>(mOwnerObject->GetCollision());
	CColliderSphere2D* Sphere = dynamic_cast<class CColliderSphere2D*>(mOwnerObject->GetCollision());


	// X 체크========================================================
	// 다음 프레임의 위치를 구한다.
	// mCompenDist = 보정거리 반지름
	FVector2D  nextPos;
	nextPos.x = ownerPos.x + mMoveStep.x; 
	nextPos.y = ownerPos.y;


	if (Shape == EColliderShape::AABB2D)
	{
		float HalfSizeX = Box->GetBoxSize().x / 2;

		// 캐릭터 콜리전 너비 절반 +
		if (mMoveStep.x > 0)
		{
			nextPos.x += HalfSizeX;
		}

		// 캐릭터 콜리전 너비 절반 -
		if (mMoveStep.x < 0)
		{
			nextPos.x -= HalfSizeX;
		}
	}
	else if (Shape == EColliderShape::Sphere2D)
	{
		float Radius = Sphere->GetRadius();

		// 캐릭터 콜리전 너비 절반 +
		if (mMoveStep.x > 0)
		{
			nextPos.x += Radius;
		}

		// 캐릭터 콜리전 너비 절반 -
		if (mMoveStep.x < 0)
		{
			nextPos.x -= Radius;
		}
	}


	// 해당 위치의 타일을 구한다.
	const CTile* tile = tileObj->GetTile(nextPos.x, nextPos.y);
	if (tile == nullptr)
		return false;

	// 타일 타입이 이동할수 없는 타일이라면,
	if (tile->GetType() == ETileType::UnableToMove)
	{
		// 반사 옵션이 켜져있는 경우
		if (bReflection == true)
		{

			/*
			if (0 < mMoveDir.x)
			{
				mMoveDir.x = -1.f;
			}

			if (mMoveDir.x < 0)
			{
				mMoveDir.x = 1.f;
			}

			mOwnerObject->SetUseGravity(true);
			*/
		}
		else
		{
			// X 이동제한
			//mMoveStep.x = 0;
		}

		return false;
	}
		

	// Y 체크========================================================
	// 현재위치에 MoveStep의 Y값을 더하여 다음 프레임의 Y좌표를 구한다.
	nextPos.x = ownerPos.x;
	nextPos.y = ownerPos.y + mMoveStep.y;

	if (Shape == EColliderShape::AABB2D)
	{
		float SizeY = Box->GetBoxSize().y;

		// 캐릭터 콜리전 높이
		if (mMoveStep.y > 0)
		{
			nextPos.y += SizeY;
		}

		if (mMoveStep.y < 0)
		{
			nextPos.y -= SizeY;

		}
	}
	else if (Shape == EColliderShape::Sphere2D)
	{
		float Radius = Sphere->GetRadius();

		// 캐릭터 콜리전 너비 절반 +
		if (mMoveStep.y > 0)
		{
			nextPos.y += Radius;
		}

		// 캐릭터 콜리전 너비 절반 -
		if (mMoveStep.y < 0)
		{
			nextPos.y -= Radius;
		}
	}

	// 다음 위치의 타일을 가져온다.
	tile = tileObj->GetTile(nextPos.x, nextPos.y);
	if (tile == nullptr)
		return false;

	// 타일 타입이 이동할수 없는 타일이라면,
	if (tile->GetType() == ETileType::UnableToMove)
	{
		if (bBounce == true)
		{

		}
		else
		{
			// MoveStep의 y값을 0으로 주어 y이동을 제한한다.
			mMoveStep.y = 0;
		}

		return false;
	}

	return true;
}


