#include "PlayerObject.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "../Component/CharacterMovementComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/SpriteComponent.h"
#include "../Animation/Animation2D.h"
#include "../Share/Log.h"
#include "SpriteEffect.h"
#include "../Component/WidgetComponent.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/Common/ProgressBar.h"
#include "../UI/UserWidget/HeadInfo.h"
#include "../Scene/SceneAssetManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Object/MonsterObject.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../Scene/SceneUIManager.h"
#include "../Object/SkullHead.h"
#include "../Share/Timer.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Sound/SoundManager.h"


CPlayerObject::CPlayerObject()
{
}


CPlayerObject::CPlayerObject(const CPlayerObject& Obj) : CSceneObject(Obj)
{
}


CPlayerObject::CPlayerObject(CPlayerObject&& Obj) : CSceneObject(Obj)
{
}


CPlayerObject::~CPlayerObject()
{
}


bool CPlayerObject::Init()
{
    mRoot = CreateComponent<CSpriteComponent>("Player");
    mBody = CreateComponent<CColliderAABB2D>();
    mAttackCollider = CreateComponent<CColliderAABB2D>();
    mMovement = CreateComponent<CCharacterMovementComponent>();
    mMovement->SetEditMode(false);
    mMainWidget = mScene->GetMainWidget();
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
    
    

    mCollision = mBody;
    bUseGravity = true;

    mRoot->SetTexture("Player", TEXT("Texture/Character/LittleBone/LittleBone_Idle_0.png"));
    mRoot->SetPivot(0.35f, 0.f);
    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetWorldScale(40.f * gScaleMult, 36.f * gScaleMult, 1.f);
    mRoot->SetRenderLayerName("Player");
    SetRootComponent(mRoot);

    
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(18.f * gScaleMult, 30.f * gScaleMult);
    mBody->SetRelativePos(0, 45.f);
    mRoot->AddChild(mBody);


    mAttackCollider->SetCollisionProfile("PlayerAttack");
    mAttackCollider->SetBoxSize(40.f * gScaleMult, 50.f * gScaleMult);
    mAttackCollider->SetRelativePos(60, 45.f);
    mAttackCollider->SetCollisionBeginFunc<CPlayerObject>(this, &CPlayerObject::AttackCollider_Begin);
    mRoot->AddChild(mAttackCollider);
    mAttackCollider->SetEnable(false);


    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(500.f);


    AnimBind();

    KeyBind();

    

    return true;
}


void CPlayerObject::KeyBind()
{
    // Key
    mScene->GetInput()->AddBindKey("MoveRight", VK_RIGHT);
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveRight",
        EInputType::Hold, this, &CPlayerObject::MoveRight);
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveRight",
        EInputType::Release, this, &CPlayerObject::MoveKey_Release);

    mScene->GetInput()->AddBindKey("MoveLeft", VK_LEFT);
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveLeft",
        EInputType::Hold, this, &CPlayerObject::MoveLeft);
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveLeft",
        EInputType::Release, this, &CPlayerObject::MoveKey_Release);


    mScene->GetInput()->AddBindKey("Dash", 'Z');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("Dash",
        EInputType::Press, this, &CPlayerObject::Dash);


    mScene->GetInput()->AddBindKey("Attack", 'X');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("Attack",
        EInputType::Press, this, &CPlayerObject::Attack);


    mScene->GetInput()->AddBindKey("Jump", 'C');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("Jump",
        EInputType::Press, this, &CPlayerObject::Jump);


    mScene->GetInput()->AddBindKey("SkillA", 'A');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("SkillA",
        EInputType::Press, this, &CPlayerObject::SkillA);


    mScene->GetInput()->AddBindKey("SkillS", 'S');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("SkillS",
        EInputType::Press, this, &CPlayerObject::SkillS);


    mScene->GetInput()->AddBindKey("Key_F", 'F');


    mScene->GetInput()->AddBindKey("TestKey_1", '1');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("TestKey_1",
        EInputType::Press, this, &CPlayerObject::HPMinus);
    
    mScene->GetInput()->AddBindKey("TestKey_2", '2');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("TestKey_2",
        EInputType::Press, this, &CPlayerObject::HPPlus);
    
    mScene->GetInput()->AddBindKey("TestKey_3", '3');
    mScene->GetInput()->AddBindFunction<CPlayerObject>("TestKey_3",
        EInputType::Press, this, &CPlayerObject::DamagePlus);


}

void CPlayerObject::AnimBind()
{

    mAnimation->AddSequence("PlayerIdle", 1.f, 1.f, true, false);
    mAnimation->AddNotify<CPlayerObject>("PlayerIdle",
        2, this, &CPlayerObject::IdleNotify);


    mAnimation->AddSequence("PlayerWalk", 1.f, 1.5f, true, false);
    mAnimation->AddNotify<CPlayerObject>("PlayerWalk",
        2, this, &CPlayerObject::WalkNotify);


    mAnimation->AddSequence("PlayerAttack_A", 1.f, 2.f, false, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack_A", this, &CPlayerObject::AttackEnd);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack_A", 2, this, &CPlayerObject::AttackNotify);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack_A", 4, this, &CPlayerObject::ComboAttackNotify);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack_A", this, &CPlayerObject::AttackEnd);



    /*mAnimation->AddSequence("PlayerAttack_A", 1.f, 2.f, false, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack_A",
        this, &CPlayerObject::AttackEnd);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack_A",
        2, this, &CPlayerObject::AttackNotify);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack_A",
        4, this, &CPlayerObject::ComboAttackNotify);*/


    mAnimation->AddSequence("PlayerAttack_B", 1.f, 2.f, false, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack_B",
        this, &CPlayerObject::AttackEnd);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack_B",
        1, this, &CPlayerObject::AttackNotify);


    mAnimation->AddSequence("PlayerDash", 1.f, 1.5f, true, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerDash",
        this, &CPlayerObject::DashEnd);


    mAnimation->AddSequence("PlayerSkillA", 1.f, 2.f, true, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerSkillA",
        this, &CPlayerObject::SkillAEnd);
    mAnimation->AddNotify<CPlayerObject>("PlayerSkillA",
        1, this, &CPlayerObject::SkillA_HeadThrow);


    mAnimation->AddSequence("PlayerJump", 0.5f, 1.f, true, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerJump",
        this, &CPlayerObject::JumpEnd);


    mAnimation->AddSequence("PlayerFall", 0.5f, 1.f, true, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerFall",
        this, &CPlayerObject::FallEnd);


    mAnimation->AddSequence("PlayerFallRepeat", 1.f, 2.f, true, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerFallRepeat",
        this, &CPlayerObject::FallRepeatEnd);

    mAnimation->AddSequence("PlayerJumpAttack", 1.f, 2.f, true, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerJumpAttack",
        this, &CPlayerObject::JumpAttackEnd);

    mAnimation->AddSequence("PlayerDeath", 1.f, 2.f, false, false);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerDeath",
        this, &CPlayerObject::DeathEnd);
}






void CPlayerObject::PreUpdate(float DeltaTime)
{
    CSceneObject::PreUpdate(DeltaTime);

    // 대쉬 상태일때,
    if (mAnimState == EAnimState::Dash)
    {
        // 대쉬 시간 누적
        mDashAccTime += DeltaTime;

        // 비율 = 누적시간 / 대쉬시간
        float percent = mDashAccTime / mDashTime;

        // 비선형 보간
        // 처음엔 빠르게 점점 느려지게
        float factor = 1.f - percent;
        percent = 1.f - pow(factor, 3);

        FVector3D DashPos = Lerp(mDashStartPos, mDashTargetPos, percent);
   
        FVector3D MovePos = DashPos - mRootComponent->GetWorldPosition();
        mMovement->SetMoveStep(MovePos);
    }

    if (mDashCoolCalc > 0.f)
    {
        mDashCoolCalc -= DeltaTime;
    }


    if (mAnimState == EAnimState::Jump || mAnimState == EAnimState::JumpAttack)
    {
        // 점프 누적시간이 점프시간에 도달한경우
        if (mJumpAccTime >= mJumpTime)
        {
            // 초기화
            mJumpAccTime = 0.f;
            bUseGravity = true;
            mAutoBasePose = true;

            if (mMovement->IsGround() == false)
            {
                mAnimState = EAnimState::Fall;

                // 이미지 피벗, 크기 조절
                mRoot->SetPivot(0.50f, 0.f);
                mRoot->SetWorldScale(34.f * gScaleMult, 36.f * gScaleMult, 1.f);

                // 떨어지는 애니메이션으로 변경
                mAnimation->ChangeAnimation("PlayerFall");
                mAutoBasePose = false;
            }
        }

        // 점프 시간 누적
        mJumpAccTime += DeltaTime;

        // 비율 = 누적시간 / 점프 지속시간
        float percent = mJumpAccTime / 0.5f;

        // 비선형보간
        float factor = 1.f - percent;
        percent = pow(factor, 2);


        FVector3D moveStep = mMovement->GetMoveStep();
        moveStep.y += 1500.f * percent* DeltaTime;

        mMovement->SetMoveStep(moveStep);
    }
}


void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    //CLog::Debug("CPlayerObject::Update  :  ", (int)mAnimState);

    SkillUpdate(DeltaTime);

    


    if (mMovement->GetVelocityLength() == 0.f && mAutoBasePose)
    {
        if (mMoveDir == EPlayerDir::Right)
            mRoot->SetPivot(0.35f, 0.f);
        else
            mRoot->SetPivot(0.65f, 0.f);

        mRoot->SetWorldScale(44.f * gScaleMult, 37.f * gScaleMult, 1.f);
        mAnimation->ChangeAnimation("PlayerIdle");
        mAnimState = EAnimState::Idle;
    }

    if(mMovement->IsGround() == true)
        bDoubleJump = true;

    if (mMovement->GetMoveStep().y < 0.f && mAnimState != EAnimState::Fall)
    {
        if (mAnimState == EAnimState::Dash || mAnimState == EAnimState::JumpAttack)
            return;

        mAnimState = EAnimState::Fall;

        // 이미지 피벗, 크기 조절
        mRoot->SetPivot(0.50f, 0.f);
        mRoot->SetWorldScale(34.f * gScaleMult, 36.f * gScaleMult, 1.f);

        // 떨어지는 애니메이션으로 변경
        mAnimation->ChangeAnimation("PlayerFall");
        mAutoBasePose = false;
    }


    if (mAnimState == EAnimState::Fall)
    {
        if (mMovement->IsGround())
        {
            if (mMoveDir == EPlayerDir::Right)
                mRoot->SetPivot(0.35f, 0.f);
            else
                mRoot->SetPivot(0.65f, 0.f);

            mRoot->SetWorldScale(44.f * gScaleMult, 37.f * gScaleMult, 1.f);
            mAnimation->ChangeAnimation("PlayerIdle");
            mAnimState = EAnimState::Idle;
        }
    }
}

void CPlayerObject::PostUpdate(float DeltaTime)
{
    CSceneObject::PostUpdate(DeltaTime);

    if (mHP <= 0 && bDeathFinish == false)
    {
        mAnimation->ChangeAnimation("PlayerDeath");
        mRoot->SetWorldScale(39.f * gScaleMult, 25.f * gScaleMult, 1.f);
        mAnimState = EAnimState::Death;
        mAutoBasePose = false;

        if (CTimer::GetTimeScale() >= 1.f)
            CTimer::SetTimeScale(0.3f);
    }

}


void CPlayerObject::Render()
{
    CSceneObject::Render();
}


float CPlayerObject::TakeDamage(float Attack, CSceneObject* Obj)
{
    Attack = CSceneObject::TakeDamage(Attack, Obj);

    if (mDamageEnable == false)
        return Attack;

    
    FVector3D KnokBackDir = GetWorldPosition() - Obj->GetWorldPosition();

    Hit(KnokBackDir);
    mHP -= (int)Attack;
    
    if (mHP <= 0)
    {
        // 사망처리
        mHP = 0;
    }

    // UI 동기화
    mMainWidget->HPUpdate(mHP,mHPMax);
    mMainWidget->BloodScreenOn();



    return Attack;
}



void CPlayerObject::IdleNotify()
{
    if (bDoubleDash == false)
    {
        CLog::Debug("더블대쉬 true로 변경");
        bDoubleDash = true;
    }
}


void CPlayerObject::MoveLeft(float DeltaTime)
{
    if (mAnimState == EAnimState::Attack ||
        mAnimState == EAnimState::Dash ||
        mAnimState == EAnimState::SkillA ||
        mAnimState == EAnimState::Death ||
        mMovement->GetKnockBack() == true)
        return;

    // 오른쪽 키와 동시에 눌린 경우,
    if (mScene->GetInput()->GetKeyHold(VK_RIGHT))
        return;
    
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);

    if (mAnimState != EAnimState::Jump &&
        mAnimState != EAnimState::Fall)
    {
        mRoot->SetPivot(0.50f, 0.f);
        mRoot->SetWorldScale(47.f * gScaleMult, 33.f * gScaleMult, 1.f);
        mAnimation->ChangeAnimation("PlayerWalk");

        mAnimState = EAnimState::Walk;
        mAutoBasePose = true;
    }

    // 콜리전의 위치가 0보다 크다면,
    FVector3D pos = mAttackCollider->GetRelativePosition();
    if (0.f < pos.x)
    {
        // -방향으로 
        mAttackCollider->SetRelativePos(-pos.x, pos.y, pos.z);
    }
    mAnimation->SetAnimationReverseX(true);
    mMoveDir = EPlayerDir::Left;
}


void CPlayerObject::MoveRight(float DeltaTime)
{
    if (mAnimState == EAnimState::Attack ||
        mAnimState == EAnimState::Dash ||
        mAnimState == EAnimState::SkillA ||
        mAnimState == EAnimState::Death ||
        mMovement->GetKnockBack() == true)
        return;

    // 왼쪽 키와 동시에 눌린 경우, 리턴
    if (mScene->GetInput()->GetKeyHold(VK_LEFT))
        return;

    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));


    if (mAnimState != EAnimState::Jump &&
        mAnimState != EAnimState::Fall)
    {

        mRoot->SetPivot(0.50f, 0.f);
        mRoot->SetWorldScale(47.f * gScaleMult, 33.f * gScaleMult, 1.f);
        mAnimation->ChangeAnimation("PlayerWalk");

        mAnimState = EAnimState::Walk;
        mAutoBasePose = true;
    }


    // 콜리전 위치가 0보다 작다면,
    FVector3D pos = mAttackCollider->GetRelativePosition();
    if (pos.x < 0)
    {
        mAttackCollider->SetRelativePos(-pos.x, pos.y, pos.z);
    }

    mAnimation->SetAnimationReverseX(false);
    mMoveDir = EPlayerDir::Right;
}


void CPlayerObject::MoveKey_Release(float DeltaTime)
{
    if (mAnimState == EAnimState::Attack ||
        mAnimState == EAnimState::Death)
        return;
}

void CPlayerObject::WalkNotify()
{
  


}



void CPlayerObject::Dash(float DeltaTime)
{
    if (mAnimState == EAnimState::Attack || 
        mAnimState == EAnimState::Death ||
        mDashCoolCalc > 0.f || 
        mMovement->GetKnockBack() == true)
        return;

    if (mAnimState == EAnimState::Dash)
    {
        if (bDoubleDash == true)
        {
            // ======= 키입력상태 확인
            // 대시 입력시 누른 방향 저장
            // 더블대시할때 둘다 눌려있다면
            if (mScene->GetInput()->GetKeyHold(VK_RIGHT) && mScene->GetInput()->GetKeyHold(VK_LEFT))
            {
                // 기존 방향으로
                mMoveDir = mSaveDir;
            }
            // 저장된 방향과 현재 누르고있는 키가 반대라면
            // 반대방향으로
            else
            {
                if (mSaveDir == EPlayerDir::Left && mScene->GetInput()->GetKeyHold(VK_RIGHT))
                {
                    mMoveDir = EPlayerDir::Right;
                    mAnimation->SetAnimationReverseX(false);
                }
                else if (mSaveDir == EPlayerDir::Right && mScene->GetInput()->GetKeyHold(VK_LEFT))
                {
                    mMoveDir = EPlayerDir::Left;
                    mAnimation->SetAnimationReverseX(true);
                }
            }

            // 애니메이션 프레임 초기화
            mAnimation->ResetFrame();
            bDoubleDash = false;
        }
        else
        {
            return;
        }
        
    }

    mAnimState = EAnimState::Dash;



    // ======== 대쉬 초기설정
    mDamageEnable = false;
     
    // 대쉬 시작위치 (현재위치)
    mDashStartPos = mRoot->GetWorldPosition();

    // 대쉬방향
    FVector3D mDirVec;
    if (mMoveDir == EPlayerDir::Left)
        mDirVec = mRootComponent->GetAxis(EAxis::X) * -1.f;
    else if (mMoveDir == EPlayerDir::Right)
        mDirVec = mRootComponent->GetAxis(EAxis::X);

    mSaveDir = mMoveDir;

    // 캐릭터의 바라보는 방향(dashDirection)에 따라 목표 위치 계산
    // 현재위치 + (바라보는 방향벡터 * 이동거리)
    mDashTargetPos = mDashStartPos + mDirVec * mDashDist;
    
    // 대쉬 누적시간 초기화
    mDashAccTime = 0.0f;
    // ======== 대쉬 초기설정
    


    // 대쉬 스프라이트 피벗 설정
    mRoot->SetPivot(0.50f, 0.f);
    mRoot->SetWorldScale(42.f * gScaleMult, 28.f * gScaleMult, 1.f);
    
    // 대쉬 콜리전 피벗 설정
    mBody->SetBoxSize(37.f * gScaleMult, 25.f * gScaleMult);
    mBody->SetRelativePos(0.f, 38.f);

    // 애니메이션 전환
    mAnimation->ChangeAnimation("PlayerDash");
    mAutoBasePose = false;
    mScene->GetAssetManager()->FindSound("SkulDash")->Play();


    // 이펙트 출력
    CSpriteEffect* DashEffect = mScene->CreateObj<CSpriteEffect>("DashSmokeEffefct_Obj");
    DashEffect->SetAnimation("DashSmokeEffefct");
    DashEffect->SetPlayRate("DashSmokeEffefct", 1.5f);
    FVector3D EffectPos = GetWorldPosition();

    DashEffect->SetWorldPos(EffectPos.x, EffectPos.y + 50.f);
    DashEffect->SetWorldScale(50.f * gScaleMult, 50.f * gScaleMult);


    // 왼쪽
    if (mMoveDir == EPlayerDir::Left)
    {
        DashEffect->SetAnimationReverseX(true);
    }
    else
    {
        DashEffect->SetAnimationReverseX(false);
    }


}

 
void CPlayerObject::DashEnd()
{
    mDashCoolCalc = mDashCool;
    mJumpAccTime = 0.f;
    bUseGravity = true;

    if (bDoubleDash == false)
    {
        CLog::Debug("더블대쉬 true로 변경");
        bDoubleDash = true;
    }
    mBody->SetBoxSize(18.f * gScaleMult, 30.f * gScaleMult);
    mBody->SetRelativePos(0, 45.f);
    mAnimState = EAnimState::Idle;
    mAutoBasePose = true;
    mDamageEnable = true;

}


void CPlayerObject::Jump(float DeltaTime)
{
    // 대쉬중이거나 or 더블점프가 비활성인경우
    if (mAnimState == EAnimState::Dash || 
        mAnimState == EAnimState::Attack || 
        mAnimState == EAnimState::Death ||
        mMovement->GetKnockBack() == true ||
        bDoubleJump == false)
        return;
    

    // 점프중이거나 or 떨어지고있는 경우
    if (mAnimState == EAnimState::Jump || mAnimState == EAnimState::Fall) 
    {
        CLog::Debug("더블점프 !!!");
        bDoubleJump = false;
        mJumpAccTime = 0.f;
        mAnimation->ResetFrame();

        mScene->GetAssetManager()->FindSound("SkulJump_B")->Play();

        // 이펙트 출력
        CSpriteEffect* DoubleJumpEffect = mScene->CreateObj<CSpriteEffect>("DoubleJump_Obj");
        DoubleJumpEffect->SetAnimation("DoubleJumpEffect");
        DoubleJumpEffect->SetPlayRate("DoubleJumpEffect", 2.f);
        DoubleJumpEffect->SetWorldPos(GetWorldPosition());
        DoubleJumpEffect->SetWorldScale(110.f * gScaleMult, 50.f * gScaleMult);

    }
    else
    {
        mScene->GetAssetManager()->FindSound("SkulJump_A")->Play();
    }

    mAnimState = EAnimState::Jump;

    // 땅에 닿고있지 않음.
    mMovement->SetGround(false);

    bUseGravity = false;

    // 이미지 피벗, 크기 조절
    mRoot->SetPivot(0.50f, 0.f);
    mRoot->SetWorldScale(22.f * gScaleMult, 36.f * gScaleMult, 1.f);

    // 점프 애니메이션으로 변경
    mAnimation->ChangeAnimation("PlayerJump");

    mAutoBasePose = false;
}


void CPlayerObject::JumpEnd()
{
    


}


void CPlayerObject::FallEnd()
{
    if (mMovement->IsGround() == false)
    {
        // 이미지 피벗, 크기 조절
        mRoot->SetPivot(0.50f, 0.f);
        mRoot->SetWorldScale(40.f * gScaleMult, 40.f * gScaleMult, 1.f);

        // 계속 떨어지는 애니메이션으로 변경
        mAnimation->ChangeAnimation("PlayerFallRepeat");
        mAutoBasePose = false;
    }
    else
    {

    }
}


void CPlayerObject::FallRepeatEnd()
{

}


void CPlayerObject::Attack(float DeltaTime)
{
    // 대시, 공중일때 리턴
    if (mAnimState == EAnimState::Dash ||
        mAnimState == EAnimState::Death )
        return;

    if (mMovement->IsGround() != true)
    {
        bJumpAttack = true;
        return;
    }


    // 점프시간 누적 변수 초기화
    mJumpAccTime = 0.f;

 
    // 공격상태가 아닐때,
    if (mAnimState != EAnimState::Attack)
    {
        if (mMoveDir == EPlayerDir::Right)
            mRoot->SetPivot(0.4f, 0.12f);
        else
            mRoot->SetPivot(0.6f, 0.12f);

        // 첫번째 공격
        mRoot->SetWorldScale(63.f * gScaleMult, 57.f * gScaleMult, 1.f);
        mAnimation->ChangeAnimation("PlayerAttack_A");
        mAnimState = EAnimState::Attack;
        mAutoBasePose = false;

        mAttackSoundName = "SkulAttackHit_A";
        mScene->GetAssetManager()->FindSound("SkulAttack_A")->Play();

    }
    // 공격 상태일때,
    else
    {

        // 콤보어택 활성화
        bAttackCombo = true;
    }

    mAnimState = EAnimState::Attack;
}


void CPlayerObject::AttackNotify()
{

   mAttackCollider->SetEnable(true);
}


void CPlayerObject::AttackEnd()
{
    CLog::PrintLog("AttackEnd");
    mAttackCollider->SetEnable(false);

    mAnimState = EAnimState::Idle;
    bAttackCombo = false;
    mAutoBasePose = true;
}


void CPlayerObject::ComboAttackNotify()
{
    // 콤보어택이 입력된경우
    if (bAttackCombo)
    {
        // 두번째 공격
        if (mMoveDir == EPlayerDir::Right)
            mRoot->SetPivot(0.4f, 0.16f);
        else
            mRoot->SetPivot(0.6f, 0.16f);

        mRoot->SetWorldScale(63.f * gScaleMult, 57.f * gScaleMult, 1.f);
        mAnimation->ChangeAnimation("PlayerAttack_B");
        mAutoBasePose = false;
        mAttackCollider->SetEnable(false);
        mAttackSoundName = "SkulAttackHit_B";
        mScene->GetAssetManager()->FindSound("SkulAttack_B")->Play();
    }
}


void CPlayerObject::JumpAttackEnd()
{
    bJumpAttack = true;
    mAutoBasePose = true;
}

void CPlayerObject::Hit(FVector3D KnokBackDir)
{
    // 플레이어 이미지 Tint 하얀색으로 변경
    mRoot->FlickerStart();
    mMovement->KnockBack(KnokBackDir, 0.7f, 500.f);

}


void CPlayerObject::SkillA(float DeltatTime)
{
    if (mAnimState == EAnimState::Dash ||
        mAnimState == EAnimState::Attack ||
        mAnimState == EAnimState::Death ||
        0.f < mSkillA_CoolAcc )
        return;

    bUseGravity = false;


    mJumpAccTime = 0.f;

    CLog::Debug("PlayerSkillA");

    mRoot->SetWorldScale(63.f * gScaleMult, 37.f * gScaleMult, 1.f);

    if (mMoveDir == EPlayerDir::Right)
        mRoot->SetPivot(0.35f, 0.f);
    else
        mRoot->SetPivot(0.65f, 0.f);

    mAnimation->ChangeAnimation("PlayerSkillA");
    mAnimState = EAnimState::SkillA;
    mAutoBasePose = false;
    mScene->GetAssetManager()->FindSound("SkulHeadThrow")->Play();

}


void CPlayerObject::SkillA_HeadThrow()
{
    mSkullHead = mScene->CreateObj<CSkullHead>("SkullHead");
    CSceneComponent* Root = mSkullHead->GetRootComponent();
    mSkullHead->SetDir(mMoveDir);
    mSkullHead->SetLifeTime(5.8f);
    mSkullHead->SetOwner(this);

    FVector3D Pos = mRoot->GetWorldPosition();
    if (mMoveDir == EPlayerDir::Right)
        Pos.x += 50.f;
    else
        Pos.x -= 50.f;

    Pos.y += 23.f * gScaleMult;
    Root->SetWorldPos(Pos);


    // 스킬 A 쿨타임 적용
    mSkillA_CoolAcc = mSkillA_Cool;

    // 스킬 S 활성화
    mMainWidget->SkillS_On();
}

void CPlayerObject::SkillA_Reset()
{
    // 스킬 A 쿨타임 초기화
    mSkillA_CoolAcc = 0.f;

    // 스킬 A 활성화
    mMainWidget->SkillA_On();

}


void CPlayerObject::SkillAEnd()
{
    bUseGravity = true;
    mAutoBasePose = true;
}


void CPlayerObject::DestroySkull()
{
    mMainWidget->SkillS_Off();
    mSkullHead = nullptr;
}


void CPlayerObject::SkillS(float DeltatTime)
{
    if (mSkullHead == nullptr ||
        mAnimState == EAnimState::Death )
        return;

    FVector3D WarpPos = mSkullHead->GetWorldPosition();
    
    
    //WarpPos.y -= 23.f * gScaleMult;

    this->SetWorldPos(WarpPos);


    CSpriteEffect* SkulHeadDestroy = mScene->CreateObj<CSpriteEffect>("EnemyDeadEffect_Obj");
    SkulHeadDestroy->SetAnimation("EnemyDeadEffect");
    SkulHeadDestroy->SetPlayRate("EnemyDeadEffect", 2.f);
    SkulHeadDestroy->SetWorldPos(WarpPos);
    SkulHeadDestroy->SetWorldScale(150.f * gScaleMult, 150.f * gScaleMult);


    mSkullHead->Destroy();
    mSkullHead = nullptr;
    mMovement->SetGround(false);
    bUseGravity = true;
    mAutoBasePose = true;
    mSkillB_CoolAcc = mSkillB_Cool;

    // 스킬 S 비활성화
    mMainWidget->SkillS_Off();

    
}

void CPlayerObject::SkillUpdate(float DeltaTime)
{
    if (0.f < mSkillA_CoolAcc)
    {
        mSkillA_CoolAcc -= DeltaTime;
        mMainWidget->SkillA_Update(mSkillA_CoolAcc, mSkillA_Cool);

        if (mSkillA_CoolAcc <= 0.f)
        {
            // 스킬 A 쿨타임이 끝난경우, S 스킬 비활성화
            mMainWidget->SkillS_Off();
        }
    }

    if (0.f < mSkillB_CoolAcc)
    {
        mSkillB_CoolAcc -= DeltaTime;
        mMainWidget->SkillS_Update(mSkillB_CoolAcc, mSkillB_Cool);

        if (mSkillB_CoolAcc <= 0.f)
        {
            // 스킬 S 쿨타임이 끝난경우
            mMainWidget->SkillS_Off();
            //mMainWidget->
        }
    }


}

void CPlayerObject::DeathEnd()
{
    bDeathFinish = true;

    if (CTimer::GetTimeScale() < 1.f)
        CTimer::SetTimeScale(1.f);
    
    // 사망 UI 띄우기
    mMainWidget->SetResultEnable(true);

}

void CPlayerObject::HPPlus(float DeltaTime)
{
    mHP += 10;

    if (mHP >= mHPMax)
    {
        mHP = mHPMax;
    }

    // UI 동기화
    mMainWidget->HPUpdate(mHP, mHPMax);
}

void CPlayerObject::HPMinus(float DeltaTime)
{
    mHP -= 10;

    if (mHP <= 0)
    {
        // 사망처리
        mHP = 0;
    }
    // UI 동기화
    mMainWidget->HPUpdate(mHP, mHPMax);
    mMainWidget->BloodScreenOn();
}

void CPlayerObject::DamagePlus(float DeltaTime)
{
    mDamage += 10;
}


void CPlayerObject::AttackCollider_Begin(const FVector3D& HitPoint, class CColliderBase* Dest)
{
    CMonsterObject* Monster = dynamic_cast<CMonsterObject*>(Dest->GetOwner());

    if (Monster != nullptr)
    {
        // 이펙트 출력
        CSpriteEffect* AttackEffec = mScene->CreateObj<CSpriteEffect>("LittleBoneHitEffect_Obj");
        AttackEffec->SetAnimation("LittleBoneHitEffect");
        AttackEffec->SetPlayRate("LittleBoneHitEffect", 3.f);


        FVector3D EffectPos;

        //// 랜덤으로 45도 회전
        FVector3D rot = AttackEffec->GetWorldRotation();

        int rnd = rand() % 2;
        if (rnd == 1)
        {
            if (mMoveDir == EPlayerDir::Right)
            {
                //오른쪽 위
                AttackEffec->SetAnimationReverseX(false);
                EffectPos = FVector3D(HitPoint.x + 100.f, HitPoint.y + 30.f, HitPoint.z);
            }
            else
            {
                //왼쪽 아래
                AttackEffec->SetAnimationReverseX(true);
                EffectPos = FVector3D(HitPoint.x - 60.f, HitPoint.y - 80.f, HitPoint.z);
            }
            
            AttackEffec->SetWorldRotation(rot.x, rot.y, rot.z + 40.f);
        }
        else
        {
            if (mMoveDir == EPlayerDir::Right)
            {
                //오른쪽 아래
                AttackEffec->SetAnimationReverseX(false);
                EffectPos = FVector3D(HitPoint.x + 50.f, HitPoint.y - 80.f, HitPoint.z);
            }
            else
            {
                //왼쪽 위
                AttackEffec->SetAnimationReverseX(true);
                EffectPos = FVector3D(HitPoint.x - 100.f, HitPoint.y + 30.f, HitPoint.z);
            }

            AttackEffec->SetWorldRotation(rot.x, rot.y, rot.z - 40.f);

        }
        AttackEffec->SetWorldPos(EffectPos);
        AttackEffec->SetWorldScale(107.f * gScaleMult, 107.f * gScaleMult);


        mScene->GetAssetManager()->FindSound(mAttackSoundName)->Play();

        Monster->TakeDamage(mDamage, this);
    }

}
