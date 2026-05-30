#include "MovementComponent.h"
#include "SceneComponent.h"
#include "NavAgent.h"
#include "../Share/Log.h"
#include "../Scene/Scene.h"
#include "../Object/TileMapObj.h"
#include "../Component/Tile.h"



CMovementComponent::CMovementComponent()
{
}

CMovementComponent::CMovementComponent(
    const CMovementComponent& Com)  :
    CComponent(Com)
{
}

CMovementComponent::CMovementComponent(CMovementComponent&& Com) :
    CComponent(Com)
{
}

CMovementComponent::~CMovementComponent()
{
    //SAFE_DELETE(mNavAgent);
}

void CMovementComponent::SetUpdateComponent(CSceneComponent* Target)
{
    mUpdateComponent = Target;
}

bool CMovementComponent::Init()
{
    if (!CComponent::Init())
        return false;

    //mNavAgent = new CNavAgent;

    //mNavAgent->Init();

    return true;
}

bool CMovementComponent::Init(const char* FileName)
{
    if (!CComponent::Init(FileName))
        return false;

    //mNavAgent = new CNavAgent;

    //mNavAgent->Init();

    return true;
}

void CMovementComponent::PreUpdate(float DeltaTime)
{
    CComponent::PreUpdate(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;
    }
}

void CMovementComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    if (mUpdateComponent == nullptr)
        return;

    // 업데이트 컴포넌트의 액티브가 꺼진경우
    if (!mUpdateComponent->IsActive())
    {
        mUpdateComponent = nullptr;
        return;
    }
     

    // 이동 축이 있는경우
    if (mMoveAxis != EAxis::None)
    {
        // 방향 설정
        mMoveDir = mUpdateComponent->GetAxis(mMoveAxis);
    }

    // 단위벡터로 만들기
    mMoveDir.Normalize();




    //if (0.f < mKnockBackTime)
    //{
    //    // 넉백 시간 감소
    //    mKnockBackTime -= DeltaTime;
    //    mKnockBackDir.Normalize();
    //    // 넉백 방향으로 이동
    //    mMoveStep.x = mKnockBackDir.x * mKnockBackSpeed * DeltaTime;

    //    return;
    //}

    if (bOnKnockBack == true)
    {
        // 넉백 시간 누적
        mKnockBackAccTime += DeltaTime;

        // 비율
        float percent = mKnockBackAccTime / mKnockBackTime;

        // 비선형보간
        float factor = 1.f - percent;
        percent = pow(factor, 2);

        mKnockBackDir.Normalize();

        mMoveStep.x = mKnockBackDir.x * mKnockBackSpeed * percent * DeltaTime;


        if (mKnockBackTime <= mKnockBackAccTime)
        {
            bOnKnockBack = false;
            mKnockBackAccTime = 0.f;
        }
    }

}

void CMovementComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;
    }
}

CMovementComponent* CMovementComponent::Clone()
{
    return new CMovementComponent(*this);
}

void CMovementComponent::EndFrame()
{
    CComponent::EndFrame();

    if (mVelocityInit)
        mMoveDir = FVector3D::Zero;

    mMoveStep = FVector3D::Zero;
}

void CMovementComponent::KnockBack(FVector3D dir, float Time, float Speed)
{
    bOnKnockBack = true;

    mKnockBackDir = dir;

    mKnockBackTime = Time;

    mKnockBackSpeed = Speed;
}

