#include "CharacterMovementComponent.h"
#include "MovementComponent.h"
#include "../Share/Log.h"
#include "../Scene/Scene.h"
#include "../Object/TileMapObj.h"
#include "../Component/Tile.h"
#include "../Component/ColliderBase.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderAABB2D.h"


CCharacterMovementComponent::CCharacterMovementComponent()
{
}

CCharacterMovementComponent::CCharacterMovementComponent(
	const CCharacterMovementComponent& Com) :
	CMovementComponent(Com)
{
}

CCharacterMovementComponent::CCharacterMovementComponent(
    CCharacterMovementComponent&& Com):
	CMovementComponent(Com)
{
}

CCharacterMovementComponent::~CCharacterMovementComponent()
{

}

bool CCharacterMovementComponent::Init()
{
	if (!CMovementComponent::Init())
		return false;

	return true;
}

bool CCharacterMovementComponent::Init(const char* FileName)
{
	if (!CMovementComponent::Init(FileName))
		return false;

	return true;
}

void CCharacterMovementComponent::PreUpdate(float DeltaTime)
{
    CMovementComponent::PreUpdate(DeltaTime);


	if (bEditMode == true)
		return;

    //===========발밑 타일 체크
    // 타일 오브젝트 가져오기
    CTileMapObj* sceneTileObj = mScene->GetTileMapObj();
    if (nullptr == sceneTileObj)
        return;

    // mUpdateComponent의 월드위치 가져오기
    FVector3D ownerPos = mUpdateComponent->GetWorldPosition();

    // 현재 위치의 타일 인덱스 가져오기
    int index = sceneTileObj->GetTileIndex(FVector2D(ownerPos.x, ownerPos.y));
    if (index == -1)
        return;

    // 발아래에 위치한 타일이 존재하는지 체크 존재하지 않는다면, 
    if (sceneTileObj->IsValidTile(index - sceneTileObj->GetTileCountX()) == false)
        bGround = false;
    //===========발밑 타일 체크
}

void CCharacterMovementComponent::Update(float DeltaTime)
{
    CMovementComponent::Update(DeltaTime);
    
    if (bOnKnockBack == false)
    {
        // 방향벡터가 있다면,
        if (mMoveDir.Length() > 0.f)
        {
            if (bGround == true)
                // 이동 할 벡터 구하기
                mMoveStep = mMoveDir * mSpeed * DeltaTime;
            else
                // 공중에서 x 이동 적용
                mMoveStep.x = mMoveDir.x * mSpeed * DeltaTime;
        }
    }

    if (mOwnerObject->GetUseGravity())
    {
        if (bGround == false)
            mMoveStep.y += mGravity * 100.f * DeltaTime;
    }

    bMove = true;

    tempMoveStep = mMoveStep;

    // 소유한 오브젝트가 콜리전이 있다면,
    if (mOwnerObject->IsCollision())
        // 이동가능한 타일인지 체크
        bMove = MoveTileCheck();


    if (bMove == true)
        mUpdateComponent->AddWorldPos(mMoveStep);
}

void CCharacterMovementComponent::PostUpdate(float DeltaTime)
{
    CMovementComponent::PostUpdate(DeltaTime);

}

CCharacterMovementComponent* CCharacterMovementComponent::Clone()
{
	return new CCharacterMovementComponent(*this);
}

void CCharacterMovementComponent::EndFrame()
{
    CMovementComponent::EndFrame();

}

bool CCharacterMovementComponent::MoveTileCheck()
{
    // UpdateComponent의 현재위치를 가져온다.
    FVector3D ownerPos = mUpdateComponent->GetWorldPosition();

    // 타일맵 오브젝트 가져오기
    CTileMapObj* tileObj = mScene->GetTileMapObj();
    if (tileObj == nullptr)
        return false;

    // 충돌체 종류 받아오기
    CColliderBase* Collision = mOwnerObject->GetCollision();
    EColliderShape Shape = Collision->GetColliderShape();
    CColliderAABB2D* Collider = dynamic_cast<class CColliderAABB2D*>(mOwnerObject->GetCollision());


    // X 체크
    // 현재위치에 MoveStep의 X값을 더하여 다음 프레임의 X좌표를 구한다.
    FVector2D  nextPos;
    nextPos.x = ownerPos.x + mMoveStep.x;
    nextPos.y = ownerPos.y;

    if (Shape == EColliderShape::AABB2D)
    {
        float HalfSizeX = Collider->GetBoxSize().x / 2;

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

    }

    // 다음 위치의 타일을 가져온다.
    const CTile* tile = tileObj->GetTile(nextPos.x, nextPos.y);
    if (tile == nullptr)
        return false;

    // 타일 타입이 이동할수 없는 타일이라면,
    if (tile->GetType() == ETileType::UnableToMove)
        // MoveStep의 x값을 0으로 주어 x이동을 제한한다.
        mMoveStep.x = 0;









    // Y 체크
    // 현재위치에 MoveStep의 Y값을 더하여 다음 프레임의 Y좌표를 구한다.
    nextPos.x = ownerPos.x;
    nextPos.y = ownerPos.y + mMoveStep.y;

    if (Shape == EColliderShape::AABB2D)
    {
        float SizeY = Collider->GetBoxSize().y;

        // 캐릭터 콜리전 높이
        if (mMoveStep.y > 0)
        {
            nextPos.y += SizeY;
        }

        if (mMoveStep.y < 0)
        {

        }
    }
    else if (Shape == EColliderShape::Sphere2D)
    {

    }

    // 다음 위치의 타일을 가져온다.
    tile = tileObj->GetTile(nextPos.x, nextPos.y);
    if (tile == nullptr)
        return false;

    // 타일 타입이 이동할수 없는 타일이라면,
    if (tile->GetType() == ETileType::UnableToMove)
    {
        // MoveStep의 y값을 0으로 주어 y이동을 제한한다.
        mMoveStep.y = 0;
        // 땅에 닿은상태로 변경한다.
        bGround = true;
    }

    return true;
}


