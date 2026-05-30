#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MonsterMovementComponent.h"
#include "../Animation/Animation2D.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Animation/Animation2DSequence.h"
#include "../Component/WidgetComponent.h"
#include "../UI/Common/ProgressBar.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../Object/PlayerObject.h"
#include "../Object/SpriteEffect.h"



CMonsterObject::CMonsterObject()
{

}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj) : CSceneObject(Obj)
{

}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj) : CSceneObject( Obj)
{

}

CMonsterObject::~CMonsterObject()
{

}

bool CMonsterObject::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderAABB2D>();
    mDetectCollision = CreateComponent<CColliderAABB2D>();
    mAttackCollision = CreateComponent<CColliderAABB2D>();
    mMovement = CreateComponent<CMonsterMovementComponent>();
    mInfoWidget = CreateComponent<CWidgetComponent>();

    mHPBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("Monster_HPBar");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);
    mRoot->SetRenderLayerName("Monster");
    SetRootComponent(mRoot);

    // 무브먼트 컴포넌트 설정
    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(mSpeed);


    // 몬스터 피격
    mBody->SetCollisionProfile("Monster");
    mBody->SetBoxSize(100.f, 100.f);
    mBody->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterBegin);
    mBody->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterEnd);
    mRoot->AddChild(mBody);


    // 몬스터 감지
    mDetectCollision->SetCollisionProfile("MonsterDetect");
    mDetectCollision->SetBoxSize(100.f, 100.f);
    mDetectCollision->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionDetectBegin);
    mDetectCollision->SetCollisionOverlapFunc<CMonsterObject>(this, &CMonsterObject::CollisionDetectOverlap);
    mDetectCollision->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionDetectEnd);
    mRoot->AddChild(mDetectCollision);
    mDetectAdd = FVector2D(300.f, 200.f);
    

    // 공격 감지
    mAttackCollision->SetCollisionProfile("MonsterAttack");
    mAttackCollision->SetBoxSize(100.f, 100.f);
    //mAttackCollision->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionAttackRangeBegin);
    mAttackCollision->SetCollisionOverlapFunc<CMonsterObject>(this, &CMonsterObject::CollisionAttackRangeOverlap);
    //mDetectCollision->SetCollisionOverlapFunc<CMonsterObject>(this, &CMonsterObject::CollisionAttackRangeOverlap);
    mAttackCollision->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionAttackRangeEnd);
    mRoot->AddChild(mAttackCollision);

    
    // 중력 사용
    bUseGravity = true;


    // HP바
    mInfoWidget->SetRelativePos(-37.f, -30.f);
    mHPBar->SetSize(25.f * gScaleMult, 4.f * gScaleMult);

    mHPBar->SetOpacity(EProgressBarImageType::Back, 1.f);
    mHPBar->SetTint(EProgressBarImageType::Back, 1.f, 1.f, 1.f);
    mHPBar->SetTexture(EProgressBarImageType::Back, "Monster_HPBarBase_Image", TEXT("Texture\\UI\\EnemyHealthBar_Base.png"));

    mHPBar->SetOpacity(EProgressBarImageType::Fill, 1.f);
    mHPBar->SetTint(EProgressBarImageType::Fill, 1.f, 1.f, 1.f);
    mHPBar->SetTexture(EProgressBarImageType::Fill, "Monster_HPBar_Image", TEXT("Texture\\UI\\EnemyHealthBar.png"));
    mHPBar->SetPercent(1.f);
    mInfoWidget->SetWidget(mHPBar);
    mRoot->AddChild(mInfoWidget);

    return true;
}

void CMonsterObject::PreUpdate(float DeltaTime)
{
    CSceneObject::PreUpdate(DeltaTime);


    CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());

    // 플레이어인 경우
    if (Player)
    {
        // 플레이어의 HP가 없고, 타겟이 존재한다면,
        if (Player->GetHP() <= 0 && mTarget != nullptr)
        {
            mTarget = nullptr;
            mAI = EMonsterAI::Idle;
        }
    }


    // 타겟이 있지만 && 액티브 꺼져있다면
    if (mTarget && !mTarget->IsActive())
    {
        // 아이들 상태로 전환
        mAI = EMonsterAI::Idle;
        // 타겟 초기화
        mTarget = nullptr;

        mMovement->SetMoveDir(FVector3D(0.f, 0.f, 0.f));
    }


    // 스테이트 머신
    switch (mAI)
    {
    case EMonsterAI::Idle:
    {
        if (0 < mAttackCoolAcc)
        {
            mAttackCoolAcc -= DeltaTime;

            if (mAttackCoolAcc <= 0.f)
            {
                // Attack콜리전 범위에 있을 경우
                if (mTarget == nullptr)
                {
                    mAI = EMonsterAI::Trace;
                }
                else if (mAttackCollision->CheckCollisionObject(mTarget->GetCollision()) == true)
                {
                    mAI = EMonsterAI::Attack;
                }
            }
        }
        else
        {
            // 패트롤 쿨타임이 남아있다면, 감소
            if (0 < mPatrolCoolAcc)
            {
                mPatrolCoolAcc -= DeltaTime;
            }

            // 패트롤 쿨타임이 끝났다면, 패트롤 상태로 전환
            else
            {
                // 패트롤 상태로 전환
                mAI = EMonsterAI::Patrol;

                // 랜덤한 패트롤 이동거리
                mPatrolDist = mPatrolDistMin + (rand() % (int)(mPatrolDistMax - mPatrolDistMin + 1));

                // 랜덤 방향 뽑기
                IDir = rand() % 2;
            }
        }
    }
        break;

    case EMonsterAI::Patrol:
    {
        // 왼쪽
        if (IDir == 1)
        {
            mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);
            mAnimation->SetAnimationReverseX(true);
        }
        // 오른쪽
        else
        {
            mAnimation->SetAnimationReverseX(false);
            mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));
        }
    }
        break;

    case EMonsterAI::Trace:
    {
        if (mTarget == nullptr)
            return;

        FVector3D TargetDir = mTarget->GetWorldPosition() - GetWorldPosition();
        TargetDir.y = 0;
        TargetDir.z = 0;
        TargetDir.Normalize();

        if (0 < TargetDir.x)
            mAnimation->SetAnimationReverseX(false);
        else
            mAnimation->SetAnimationReverseX(true);

        mMovement->AddMove(TargetDir);
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

void CMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);


    CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());

    // 플레이어인 경우
    if (Player)
    {
        // 플레이어의 HP가 없고, 타겟이 존재한다면,
        if (Player->GetHP() <= 0 && mTarget != nullptr)
        {
            mTarget = nullptr;
            mAI = EMonsterAI::Idle;
        }
    }

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

void CMonsterObject::PostUpdate(float DeltaTime)
{
    CSceneObject::PostUpdate(DeltaTime);


    CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());

    // 플레이어인 경우
    if (Player)
    {
        // 플레이어의 HP가 없고, 타겟이 존재한다면,
        if (Player->GetHP() <= 0 && mTarget != nullptr)
        {
            mTarget = nullptr;
            mAI = EMonsterAI::Idle;
        }
    }
}



void CMonsterObject::AIIdle(float DeltaTime)
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
}

void CMonsterObject::AIPatrol(float DeltaTime)
{
    // 이동속도 설정
    mMovement->SetMoveSpeed(mSpeed);

    mPatrolDist -= mMovement->GetMoveDistance();


    // 이동 불가능 타일에 닿았거나
    // 모든 이동이 끝난경우
    if (mMovement->MoveTileCheckX() == false || mPatrolDist <= 0.f)
    {
        // Idle 상태로 변경
        mAI = EMonsterAI::Idle;

        // 쿨타임 초기화
        mPatrolCoolAcc = mPatrolCooltime;
    }

    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Patrol]);
}

void CMonsterObject::AITrace(float DeltaTime)
{
    // 타겟 방향으로 이동

    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Trace]);


    if (mTarget == nullptr)
    {
        mAI = EMonsterAI::Idle;
    }
    else if (mDetectCollision->CheckCollisionObject(mTarget->GetCollision()) == false)
    {
        if (bAttacking == false)
        {
            mAI = EMonsterAI::Idle;
            mTarget = nullptr;
        }
    }

}

void CMonsterObject::AIAttack(float DeltaTime)
{
    if (mTarget == nullptr)
        return;


    // 공격 애니메이션의 시작인 경우
    if (bAttacking == false)
    {
        FVector3D TargetDir = mTarget->GetWorldPosition() - GetWorldPosition();
        TargetDir.Normalize();

        // 왼쪽
        if (TargetDir.x < 0)
        {
            mAnimation->SetAnimationReverseX(true);
        }
        // 오른쪽
        else
        {
            mAnimation->SetAnimationReverseX(false);
        }
    }

    // 애니메이션 실행중
    bAttacking = true;



    if (mAnimation)
    {
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Attack]);
       
      
        if (bAnimEnd)
        {
            bAnimEnd = false;

            if (mDelayTime > 0.f)
            {
                mDelayAccTime = mDelayTime;
            }
            else
            {

                bAttacking = false;


                //    // 공격 쿨타임 적용
                mAttackCoolAcc = mAttackCool;
                mAI = EMonsterAI::Idle;
                // AttackCollision에 타겟 콜리전이 있는지 체크
                if (mAttackCollision->CheckCollisionObject(mTarget->GetCollision()) == false)
                {
                    // 공격중이지 않다면, 추적 상태로 변경
                    if (bAttacking == false)
                        mAI = EMonsterAI::Trace;
                }
            }

        }
        else
        {

            if (mDelayAccTime > 0.f)
            {
                mDelayAccTime -= DeltaTime;
            }
            else if (mDelayAccTime < 0.f)
            {
                mDelayAccTime = 0.f;
                bAttacking = false;

                // 공격 쿨타임 적용
                mAttackCoolAcc = mAttackCool;
                mAI = EMonsterAI::Idle;
                // AttackCollision에 타겟 콜리전이 있는지 체크
                if (mAttackCollision->CheckCollisionObject(mTarget->GetCollision()) == false)
                {
                    // 공격중이지 않다면, 추적 상태로 변경
                    if (bAttacking == false)
                        mAI = EMonsterAI::Trace;
                }
            }
        }



    }
}

void CMonsterObject::AIDeath(float DeltaTime)
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Death]);
}

void CMonsterObject::AISkill(float DeltaTime)
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Skill]);
}

void CMonsterObject::AICustom(float DeltaTime)
{
}

void CMonsterObject::AIHit(float DeltaTime)
{
    //mAnimation->ChangeAnimation("CalleonSoldier_Hit_A");
    mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Hit]);

    mAttackCollision->SetEnable(false);

    if (bAnimEnd)
    {
        mAttackCollision->SetEnable(true);

        mAI = EMonsterAI::Idle;
    }

    //if (bAnimBegin)
    //{
    //    if (mAnimation)
    //        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Hit]);
    //}
}



float CMonsterObject::TakeDamage(float Attack, CSceneObject* Obj)
{
    float Dmg = CSceneObject::TakeDamage(Attack, Obj);



    mAI = EMonsterAI::Hit;

    FVector3D KnokBackDir = GetWorldPosition() - Obj->GetWorldPosition();

    Hit(KnokBackDir);

    // 넉백 방향이 왼쪽인 경우
    if (KnokBackDir.x < 0)
    {
        // 오른쪽에서 맞았으므로 플립x
        mAnimation->SetAnimationReverseX(false);
    }
    else
    {
        // 왼쪽에서 맞았으므로 플립x
        mAnimation->SetAnimationReverseX(true);
    }


    mHP -= (int)Dmg;
    mHPBar->SetPercent((float)mHP / (float)mHPMax);
    

    if (mHP <= 0)
    {
        // 사망 이펙트
        mScene->MinusEnemyCount();
        mScene->GetMainWidget()->SetEnemyCount(mScene->GetEnemyCount());

        CSpriteEffect* EnemyDeadEffect = mScene->CreateObj<CSpriteEffect>("EnemyDeadEffect_Obj");
        EnemyDeadEffect->SetAnimation("EnemyDeadEffect");
        EnemyDeadEffect->SetPlayRate("EnemyDeadEffect", 1.5f);
        FVector3D EffectPos = GetWorldPosition();
        EnemyDeadEffect->SetWorldPos(EffectPos.x, EffectPos.y + 50.f, EffectPos.z);
        EnemyDeadEffect->SetWorldScale(150.f * gScaleMult, 150.f * gScaleMult);


        Destroy();
    }

    return Dmg;
}

void CMonsterObject::Attack()
{
    if (mTarget == nullptr)
        return;

}

void CMonsterObject::Hit(FVector3D dir)
{
    // 플리커 및 피격 색상 변경
    mRoot->SetTint(0.8f, 0.2f, 0.2f);
    mRoot->FlickerStart();

    // 넉백
    mMovement->KnockBack(dir);
}



void CMonsterObject::DetectTarget()
{
    // 콜리전 범위 증가
    FVector2D Size = mDetectCollision->GetBoxSize();

    mDetectCollision->SetBoxSize(Size.x + mDetectAdd.x, Size.y + mDetectAdd.y);
}

void CMonsterObject::DetectTargetRelease()
{
    FVector2D Size = mDetectCollision->GetBoxSize();

    mDetectCollision->SetBoxSize(Size.x - mDetectAdd.x, Size.y - mDetectAdd.y);
}





void CMonsterObject::CollisionMonsterBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
    // CLog::PrintLog("Collision");
}

void CMonsterObject::CollisionMonsterEnd(CColliderBase* Dest)
{
    // CLog::PrintLog("CollisionEnd");
}





void CMonsterObject::CollisionDetectBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
    // 타겟으로 등록
    mTarget = Dest->GetOwner();
    mAI = EMonsterAI::Trace;
    DetectTarget();

}

void CMonsterObject::CollisionDetectOverlap(CColliderBase* Dest)
{
    if (bAttacking == true || mAI == EMonsterAI::Attack || mAI == EMonsterAI::Hit)
        return;

    mAI = EMonsterAI::Trace;

    

}

void CMonsterObject::CollisionDetectEnd(CColliderBase* Dest)
{
    if (bAttacking == false)
    {
        mTarget = nullptr;
        mAI = EMonsterAI::Idle;
    }
    DetectTargetRelease();

}





void CMonsterObject::CollisionAttackRangeBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
    mAI = EMonsterAI::Attack;

}

void CMonsterObject::CollisionAttackRangeOverlap(CColliderBase* Dest)
{
    if (mAI == EMonsterAI::Hit)
        return;

    if(mAnimation->GetSequence()->GetName() != mAIAnimationName[(int)EMonsterAI::Attack])
        mAI = EMonsterAI::Attack;
}




void CMonsterObject::CollisionAttackRangeEnd(CColliderBase* Dest)
{


}
