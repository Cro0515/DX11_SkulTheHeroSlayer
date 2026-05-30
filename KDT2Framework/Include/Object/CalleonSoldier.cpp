#include "CalleonSoldier.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/MonsterMovementComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "MonsterObject.h"
#include "../Animation/Animation2D.h"
#include "PlayerObject.h"
#include "../Object/SpriteEffect.h"
#include "../Scene/Scene.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Scene/SceneAssetManager.h"


CCalleonSoldier::CCalleonSoldier()
{
}

CCalleonSoldier::CCalleonSoldier(const CCalleonSoldier& Obj) :
    CMonsterObject(Obj)
{
}

CCalleonSoldier::CCalleonSoldier(CCalleonSoldier&& Obj) :
    CMonsterObject(Obj)
{
}

CCalleonSoldier::~CCalleonSoldier()
{
}

bool CCalleonSoldier::Init()
{
    CMonsterObject::Init();

    
    // CalleonSoldier 정보 설정
    mDetectDistance = 0.f;      // 감지 콜리전 거리
    mAttackRange = 0.f;         // 공격 콜리전 
    mHP = 100;                  // 체력
    mHPMax = 100;               // 체력
    mDamage = 10;               // 데미지
    mAttackCool = 1.f;          // 공격 쿨타임
    mPatrolCoolAcc = mPatrolCooltime;
    mSpeed = 300.f;

    mPatrolDistMin = 1000.f;
    mPatrolDistMax = 1200.f;


    // mRoot - 이미지 설정
    mRoot->SetTexture("CCalleonSoldier", TEXT("Texture/Monster/Idle_0.png"));
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
    mDetectCollision->SetBoxSize(600.f, 150.f);
    mDetectCollision->SetRelativePos(0, 75.f);
    mDetectAdd = 300.f;

    //mAttackCollision - 공격 감지 콜리전 설정
    mAttackCollision->SetBoxSize(300.f, 150.f);
    mAttackCollision->SetRelativePos(0, 75.f);

    // 애니메이션 설정
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("CalleonSoldier_Idle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("CalleonSoldier_Walk", 1.f, 1.f, true, false);
    mAnimation->AddSequence("CalleonSoldier_Attack", 0.8f, 1.f, false, false);
    mAnimation->AddNotify<CCalleonSoldier>("CalleonSoldier_Attack", 2, this, &CCalleonSoldier::Attack);
    mAnimation->SetBeginFunction< CCalleonSoldier>("CalleonSoldier_Attack", this, &CCalleonSoldier::AttackBegin_Notify);
    mAnimation->SetEndFunction< CCalleonSoldier>("CalleonSoldier_Attack", this, &CCalleonSoldier::AttackEnd_Notify);
    mAnimation->SetEndFunction< CCalleonSoldier>("CalleonSoldier_Attack", this, &CCalleonSoldier::SetAnimEnd);

    mAnimation->AddSequence("CalleonSoldier_Hit_A", 0.5f, 1.f, false, false);
    //mAnimation->SetBeginFunction< CCalleonSoldier>("CalleonSoldier_Hit_A", this, &CCalleonSoldier::SetAnimBegin);
    //mAnimation->AddNotify<CCalleonSoldier>("CalleonSoldier_Hit_A", 1, this, &CCalleonSoldier::SetAnimEnd);
    mAnimation->SetEndFunction< CCalleonSoldier>("CalleonSoldier_Hit_A", this, &CCalleonSoldier::SetAnimEnd);

    mAnimation->AddSequence("CalleonSoldier_Hit_B", 0.3f, 1.f, false, false);
    //mAnimation->SetBeginFunction< CCalleonSoldier>("CalleonSoldier_Hit_B", this, &CCalleonSoldier::SetAnimBegin);
    mAnimation->SetEndFunction< CCalleonSoldier>("CalleonSoldier_Hit_B", this, &CCalleonSoldier::SetAnimEnd);


    mAIAnimationName[(int)EMonsterAI::Idle] = "CalleonSoldier_Idle";
    mAIAnimationName[(int)EMonsterAI::Patrol] = "CalleonSoldier_Walk";
    mAIAnimationName[(int)EMonsterAI::Trace] = "CalleonSoldier_Walk";
    mAIAnimationName[(int)EMonsterAI::Attack] = "CalleonSoldier_Attack";
    mAIAnimationName[(int)EMonsterAI::Hit] = "CalleonSoldier_Hit_A";


    mAttackBeginDelayAcc = mAttackBeginDelay;

    //mAttackAfterDelayAcc = mAttackAfterDelay;

    return true;
}

void CCalleonSoldier::PreUpdate(float DeltaTime)
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

void CCalleonSoldier::Update(float DeltaTime)
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

void CCalleonSoldier::Attack()
{
    CMonsterObject::Attack();

    if (mTarget == nullptr)
        return;


    FVector3D DashDir;
    if (mAnimation->GetReverse() == true)
        DashDir = FVector3D(-1.f, 0.f, 0.f);
    else
        DashDir = FVector3D(1.f, 0.f, 0.f);

    // 일정거리 이동
    mMovement->KnockBack(DashDir, 1.f, 400.f);


    // 공격반경 콜리전내에 있을때,
    if (mAttackCollision->CheckCollisionObject(mTarget->GetCollision()) == true)
    {
        FVector3D PlayerPos = mTarget->GetWorldPosition();
        int dir = PlayerPos.x - GetWorldPosition().x;
        // dir 양수인경우 플레이어가 오른쪽에 있다.
        //     음수인경우 플레이어가 왼쪽에 있다.


        CSpriteEffect* SoldierHitEffect = mScene->CreateObj<CSpriteEffect>("SoldierHitEffect_Obj");
        SoldierHitEffect->SetAnimation("SoldierHitEffect");
        SoldierHitEffect->SetPlayRate("SoldierHitEffect", 2.f);

        FVector3D EffectPos = GetWorldPosition();

        // 왼쪽을 보는 경우
        if (mAnimation->GetReverse() == true && dir < 0)
        {
            // 데미지 처리
            CPlayerObject* Player = dynamic_cast<class CPlayerObject*>(mTarget.Get());
            Player->TakeDamage(mDamage, this);
            EffectPos = FVector3D(EffectPos.x - 120.f, EffectPos.y + 100.f, EffectPos.z);
        }
        // 오른쪽을 보는 경우
        else if (mAnimation->GetReverse() == false && dir > 0)
        {
            // 데미지 처리
            CPlayerObject* Player = dynamic_cast<class CPlayerObject*>(mTarget.Get());
            Player->TakeDamage(mDamage, this);
            EffectPos = FVector3D(EffectPos.x + 120.f, EffectPos.y + 100.f, EffectPos.z);
        }

        mScene->GetAssetManager()->FindSound("SoldierAttackHit")->Play();


        SoldierHitEffect->SetWorldPos(EffectPos);
        SoldierHitEffect->SetWorldScale(150.f * gScaleMult, 100.f * gScaleMult);

    }
}

void CCalleonSoldier::Hit(FVector3D dir)
{
    CMonsterObject::Hit(dir);

  
}

void CCalleonSoldier::AIIdle(float DeltaTime)
{
    CMonsterObject::AIIdle(DeltaTime);


}

void CCalleonSoldier::AIPatrol(float DeltaTime)
{
    CMonsterObject::AIPatrol(DeltaTime);
}

void CCalleonSoldier::AITrace(float DeltaTime)
{
    CMonsterObject::AITrace(DeltaTime);
}

void CCalleonSoldier::AIAttack(float DeltaTime)
{
    CMonsterObject::AIAttack(DeltaTime);

    if (mAttackBeginDelayAcc > 0.f)
        mAttackBeginDelayAcc -= DeltaTime;


    if (mAttackEndDelayAcc > 0.f)
        mAttackEndDelayAcc -= DeltaTime;

    
    if(mAttackBeginDelayAcc <= 0.f)
    {
        if (mAttackEndDelayAcc <= 0.f)
            mAnimation->SetPause(false);
    }
}

void CCalleonSoldier::AIDeath(float DeltaTime)
{
    CMonsterObject::AIDeath(DeltaTime);

}

void CCalleonSoldier::AISkill(float DeltaTime)
{
    CMonsterObject::AISkill(DeltaTime);

}

void CCalleonSoldier::AICustom(float DeltaTime)
{
    CMonsterObject::AICustom(DeltaTime);

}

void CCalleonSoldier::AIHit(float DeltaTime)
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
                mAIAnimationName[(int)EMonsterAI::Hit] = "CalleonSoldier_Hit_A";
            }
            else
            {
                mAIAnimationName[(int)EMonsterAI::Hit] = "CalleonSoldier_Hit_B";
            }
           //     mAnimation->ChangeAnimation("CalleonSoldier_Hit_A");
           // else
           //     mAnimation->ChangeAnimation("CalleonSoldier_Hit_B");


            bAnimEnd = false;
            bHitAnimFlag = !bHitAnimFlag;
        }
    }

}

void CCalleonSoldier::CollisionAttackRangeBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
    CMonsterObject::CollisionAttackRangeBegin(HitPoint, Dest);

}

void CCalleonSoldier::AttackBegin_Notify()
{
    mAttackBeginDelayAcc = mAttackBeginDelay;

    mAnimation->SetPause(true);

    SetDelayTime(mAttackBeginDelay);
}

void CCalleonSoldier::AttackEnd_Notify()
{
    mAttackEndDelayAcc = mAttackEndDelay;

    mAnimation->SetPause(true);
}

