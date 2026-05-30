#include "CalleonArcher.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/MonsterMovementComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "MonsterObject.h"
#include "../Object/Arrow.h"
#include "../Component/ProjectileMovementComponent.h"



CCalleonArcher::CCalleonArcher()
{
}

CCalleonArcher::CCalleonArcher(const CCalleonArcher& Obj) :
    CMonsterObject(Obj)
{

}

CCalleonArcher::CCalleonArcher(CCalleonArcher&& Obj) :
    CMonsterObject(Obj)
{
}

CCalleonArcher::~CCalleonArcher()
{
}

bool CCalleonArcher::Init()
{
    CMonsterObject::Init();


    // CalleonSoldier 정보 설정
    mDetectDistance = 0.f;      // 감지 콜리전 거리
    mAttackRange = 0.f;         // 공격 콜리전 
    mHP = 50;                  // 체력
    mHPMax = 50;               // 체력
    mDamage = 5;               // 데미지
    mAttackCool = 1.f;          // 공격 쿨타임
    mPatrolCoolAcc = mPatrolCooltime;
    mSpeed = 300.f;

    mPatrolDistMin = 1000.f;
    mPatrolDistMax = 1200.f;


    // mRoot - 이미지 설정
    mRoot->SetTexture("CalleonArcher", TEXT("Texture/Monster/Calleon_Archer/Idle_0.png"));
    mRoot->SetPivot(0.5f, 0.f);
    mRoot->SetWorldScale(80.f * gScaleMult, 80.f * gScaleMult, 1.f);
    SetRootComponent(mRoot);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(mSpeed);





    // mBody - 몬스터 피격 콜리전 설정
    mBody->SetBoxSize(80.f, 150.f);
    mBody->SetRelativePos(0, 75.f);
    mCollision = mBody;


    // mDetectCollision - 몬스터 감지 콜리전 설정
    mDetectCollision->SetBoxSize(1200.f, 150.f);
    mDetectCollision->SetRelativePos(0, 75.f);
    mDetectAdd = 300.f;


    // mAttackCollision - 공격 감지 콜리전 설정
    mAttackCollision->SetBoxSize(1200.f, 150.f);
    mAttackCollision->SetRelativePos(0, 75.f);

    // 애니메이션 설정
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("CalleonArcher_Idle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("CalleonArcher_Walk", 1.f, 1.f, true, false);
    mAnimation->AddSequence("CalleonArcher_Attack", 0.8f, 1.f, false, false);
    mAnimation->SetBeginFunction< CCalleonArcher>("CalleonArcher_Attack", this, &CCalleonArcher::AttackBegin_Notify);
    mAnimation->AddNotify<CCalleonArcher>("CalleonArcher_Attack", 2, this, &CCalleonArcher::AttackBefor_Notify);
    mAnimation->AddNotify<CCalleonArcher>("CalleonArcher_Attack", 3, this, &CCalleonArcher::Attack);
    mAnimation->SetEndFunction< CCalleonArcher>("CalleonArcher_Attack", this, &CCalleonArcher::SetAnimEnd);


    mAnimation->AddSequence("CalleonArcher_Hit_A", 0.5f, 1.f, false, false);
    //mAnimation->SetBeginFunction< CCalleonArcher>("CalleonArcher_Hit_A", this, &CCalleonArcher::SetAnimBegin);
    //mAnimation->AddNotify<CCalleonArcher>("CalleonArcher_Hit_A", 1, this, &CCalleonArcher::SetAnimEnd);
    mAnimation->SetEndFunction< CCalleonArcher>("CalleonArcher_Hit_A", this, &CCalleonArcher::SetAnimEnd);

    mAnimation->AddSequence("CalleonArcher_Hit_B", 0.3f, 1.f, false, false);
    //mAnimation->SetBeginFunction< CCalleonArcher>("CalleonArcher_Hit_B", this, &CCalleonArcher::SetAnimBegin);
    mAnimation->SetEndFunction< CCalleonArcher>("CalleonArcher_Hit_B", this, &CCalleonArcher::SetAnimEnd);


    mAIAnimationName[(int)EMonsterAI::Idle] = "CalleonArcher_Idle";
    mAIAnimationName[(int)EMonsterAI::Patrol] = "CalleonArcher_Walk";
    mAIAnimationName[(int)EMonsterAI::Trace] = "CalleonArcher_Walk";
    mAIAnimationName[(int)EMonsterAI::Attack] = "CalleonArcher_Attack";
    mAIAnimationName[(int)EMonsterAI::Hit] = "CalleonArcher_Hit_A";




    return true;
}

void CCalleonArcher::PreUpdate(float DeltaTime)
{
    CMonsterObject::PreUpdate(DeltaTime);


    // 스테이트 머신
    switch (mAI)
    {
    case EMonsterAI::Idle:
    {

    }
    break;

    case EMonsterAI::Patrol:
    {

    }
    break;

    case EMonsterAI::Trace:
    {

    }
    break;

    case EMonsterAI::Attack:
    {

    }
    break;

    case EMonsterAI::Death:
    {

    }
    break;

    case EMonsterAI::Skill:
    {

    }
    break;
    case EMonsterAI::Custom:
    {

    }
    break;

    case EMonsterAI::Hit:
    {

    }
    break;
    }
}

void CCalleonArcher::Update(float DeltaTime)
{
    CMonsterObject::Update(DeltaTime);

    // 애니메이션 스테이트 머신
    switch (mAI)
    {
    case EMonsterAI::Idle:
        AIIdle(DeltaTime);
        break;
    case EMonsterAI::Patrol:
        AIPatrol(DeltaTime);
        break;
    case EMonsterAI::Trace:
        AITrace(DeltaTime);
        break;
    case EMonsterAI::Attack:
        AIAttack(DeltaTime);
        break;
    case EMonsterAI::Death:
        AIDeath(DeltaTime);
        break;
    case EMonsterAI::Skill:
        AISkill(DeltaTime);
        break;
    case EMonsterAI::Custom:
        AICustom(DeltaTime);
        break;
    case EMonsterAI::Hit:
        AIHit(DeltaTime);
    }
}

void CCalleonArcher::Attack()
{
    CMonsterObject::Attack();

    if (mTarget == nullptr)
        return;


    // 공격반경 콜리전내에 있을때,
    if (mDetectCollision->CheckCollisionObject(mTarget->GetCollision()) == true)
    {
        // 화살발사
        CArrow* Arrow = mScene->CreateObj<CArrow>("Arrow");
        FVector3D Pos = GetWorldPosition();
        Pos.y += 75.f;


        int dir = ShootPos.x - GetWorldPosition().x;
        // dir 양수인경우 플레이어가 오른쪽에 있다.
        //     음수인경우 플레이어가 왼쪽에 있다.


        FVector3D mDirVec;

        // 왼쪽을 보는 경우
        if (mAnimation->GetReverse() == true && dir < 0)
        {
            mDirVec = mRootComponent->GetAxis(EAxis::X) * -1.f;
            Arrow->mSprite->SetRelativeRotation(FVector3D(0.f, 0.f, 180.f));

            float BoxSizeX = dynamic_cast<CColliderAABB2D*>(Arrow->GetCollision())->GetBoxSize().x;

            Arrow->mMovement->SetCompenDist(FVector2D(-BoxSizeX/2, 0.f));
            Pos.x -= 30.f;
        }
        // 오른쪽을 보는 경우
        else if (mAnimation->GetReverse() == false && dir > 0)
        {
            mDirVec = mRootComponent->GetAxis(EAxis::X);
            Pos.x += 30.f;

        }


        Arrow->SetWorldPos(Pos);

       
        Arrow->SetDir(mDirVec);
        Arrow->SetData(this, mDamage);
    }
}

void CCalleonArcher::Hit(FVector3D dir)
{
    CMonsterObject::Hit(dir);


}

void CCalleonArcher::AIIdle(float DeltaTime)
{
    CMonsterObject::AIIdle(DeltaTime);


}

void CCalleonArcher::AIPatrol(float DeltaTime)
{
    CMonsterObject::AIPatrol(DeltaTime);


}

void CCalleonArcher::AITrace(float DeltaTime)
{
    CMonsterObject::AITrace(DeltaTime);


}

void CCalleonArcher::AIAttack(float DeltaTime)
{
    CMonsterObject::AIAttack(DeltaTime);


    if (mAttackBeforeDelayAcc > 0.f)
    {
        mAttackBeforeDelayAcc -= DeltaTime;

        if (mAttackBeforeDelayAcc <= 0.f)
            mAnimation->SetPause(false);
    }

}

void CCalleonArcher::AIDeath(float DeltaTime)
{
    CMonsterObject::AIDeath(DeltaTime);


}

void CCalleonArcher::AISkill(float DeltaTime)
{
    CMonsterObject::AISkill(DeltaTime);


}

void CCalleonArcher::AICustom(float DeltaTime)
{
    CMonsterObject::AICustom(DeltaTime);


}

void CCalleonArcher::AIHit(float DeltaTime)
{
    CMonsterObject::AIHit(DeltaTime);

    if (mAnimation)
    {
        if (mAnimation->GetPause())
            mAnimation->SetPause(false);

        if (bAnimEnd)
        {
            // 애니메이션 일시정지인 경우

            if (bHitAnimFlag)
            {
                mAIAnimationName[(int)EMonsterAI::Hit] = "CalleonArcher_Hit_A";
            }
            else
            {
                mAIAnimationName[(int)EMonsterAI::Hit] = "CalleonArcher_Hit_B";
            }


            bAnimEnd = false;
            bHitAnimFlag = !bHitAnimFlag;
        }
    }
}

void CCalleonArcher::AttackBegin_Notify()
{
    if (mTarget == nullptr)
        return;
    
    ShootPos = mTarget->GetWorldPosition();
}

void CCalleonArcher::AttackBefor_Notify()
{
    mAttackBeforeDelayAcc = mAttackBeforeDelay;
    mAnimation->SetPause(true);
}
