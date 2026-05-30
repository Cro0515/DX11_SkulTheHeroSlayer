#include "MainWidget.h"
#include "../Common/Image.h"
#include "../Common/Button.h"
#include "../Common/TextBlock.h"
#include "../Common/ProgressBar.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Device.h"
#include "../../Scene/Input.h"
#include "ResultWidget.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneLobby.h"
#include "../../GameInstance.h"
#include "../../Object/SpriteEffect.h"

CMainWidget::CMainWidget()
{
}

CMainWidget::~CMainWidget()
{ 
}

bool CMainWidget::Init()
{
    CUserWidget::Init();

    FResolution RS = CDevice::GetInst()->GetResolution();


    // 플레이어 Info
    mPlayerInfo = mScene->GetUIManager()->CreateWidget<CImage>("PlayerInfo");
    mPlayerInfo->SetTint(1.f, 1.f, 1.f);
    mPlayerInfo->SetTexture("UIFrame", TEXT("Texture\\UI\\SkulPlayerInfoUI.png"));
    mPlayerInfo->SetSize(168.f * gScaleMult, 66.f * gScaleMult);
    mPlayerInfo->SetPos(-1.f, 0.f);
    AddWidget(mPlayerInfo);




    // 스킬 A 프로그레스 바
    mSkill_A_ProgressBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("Skill_A_ProgressBar");
    mSkill_A_ProgressBar->SetTint(EProgressBarImageType::Back, 1.f, 1.f, 1.f);
    mSkill_A_ProgressBar->SetTexture(EProgressBarImageType::Back, "Skill_A_Image", TEXT("Texture\\UI\\Skill_A_SkullThrowing.png"));

    mSkill_A_ProgressBar->SetTint(EProgressBarImageType::Fill, 1.f, 1.f, 1.f);
    mSkill_A_ProgressBar->SetOpacity(EProgressBarImageType::Fill, 0.f);
    mSkill_A_ProgressBar->SetTexture(EProgressBarImageType::Fill, "Skill_A_Fill", TEXT("Texture\\UI\\Skill_Fill.png"));
    mSkill_A_ProgressBar->SetBarDir(EProgressBarDir::TopToBottom);

    mSkill_A_ProgressBar->SetPos(173.f, 80.f);
    mSkill_A_ProgressBar->SetSize(24.f * gScaleMult, 24.f * gScaleMult);
    AddWidget(mSkill_A_ProgressBar);
    //mSkill_A_ProgressBar->SetPercent(0.4f);


    // 스킬 A 단축키
    CSharedPtr<CImage> Skill_A_Key = mScene->GetUIManager()->CreateWidget<CImage>("Skill_A_Key");
    Skill_A_Key->SetTint(1.f, 1.f, 1.f);
    Skill_A_Key->SetTexture("Skill_A_Key", TEXT("Texture\\UI\\Key_A.png"));
    Skill_A_Key->SetSize(15.f * gScaleMult, 14.f * gScaleMult);
    Skill_A_Key->SetPos(187.f, 135.f);
    AddWidget(Skill_A_Key);




    // 스킬 S 프로그레스 바
    mSkill_S_ProgressBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("mSkill_S_ProgressBar");
    mSkill_S_ProgressBar->SetTint(EProgressBarImageType::Back, 1.f, 1.f, 1.f);
    mSkill_S_ProgressBar->SetGrayScale(EProgressBarImageType::Back, true);
    mSkill_S_ProgressBar->SetTexture(EProgressBarImageType::Back, "Skill_S_Image", TEXT("Texture\\UI\\Skill_S_Rebone.png"));

    mSkill_S_ProgressBar->SetTint(EProgressBarImageType::Fill, 1.f, 1.f, 1.f);
    mSkill_S_ProgressBar->SetOpacity(EProgressBarImageType::Fill, 0.f);
    mSkill_S_ProgressBar->SetTexture(EProgressBarImageType::Fill, "Skill_S_Fill", TEXT("Texture\\UI\\Skill_Fill.png"));
    
    mSkill_S_ProgressBar->SetBarDir(EProgressBarDir::TopToBottom);
    mSkill_S_ProgressBar->SetPos(266.f, 80.f);
    mSkill_S_ProgressBar->SetSize(24.f * gScaleMult, 24.f * gScaleMult);
    AddWidget(mSkill_S_ProgressBar);
    //mSkill_S_ProgressBar->SetPercent(0.7f);






    // 스킬 S 단축키
    CSharedPtr<CImage> Skill_S_Key = mScene->GetUIManager()->CreateWidget<CImage>("Skill_S_Key");
    Skill_S_Key->SetTint(1.f, 1.f, 1.f);
    Skill_S_Key->SetTexture("Skill_S_Key", TEXT("Texture\\UI\\Key_S.png"));
    Skill_S_Key->SetSize(15.f * gScaleMult, 14.f * gScaleMult);
    Skill_S_Key->SetPos(280.f, 135.f);
    AddWidget(Skill_S_Key);





    // HP 프로그레스바
    mHPBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("HPBar");
    mHPBar->SetPos(131.f, 38.f);
    mHPBar->SetTint(EProgressBarImageType::Back, 1.f, 1.f, 1.f);
    mHPBar->SetOpacity(EProgressBarImageType::Back, 0.f);
    mHPBar->SetSize(116.f * gScaleMult, 8.f * gScaleMult);
    mHPBar->SetTexture(EProgressBarImageType::Fill, "HPBar", TEXT("Texture\\UI\\HealthBar_Color.png"));
    AddWidget(mHPBar);
    //mHPBar->SetPercent(0.7f);


    // HP 텍스트
    mHPText = mScene->GetUIManager()->CreateWidget<CTextBlock>("HPText");
    mHPText->SetText(TEXT("100 / 100"));
    mHPText->SetTextColor(255, 255, 255, 255);
    mHPText->SetPos(240.f, 33.f);
    mHPText->SetSize(130.f, 40.f);
    mHPText->SetAlignH(ETextAlignH::Center);
    mHPText->SetFontSize(25.f);
    mHPText->SetShadowEnable(true);
    mHPText->SetShadowOffset(3.f, 3.f);
    AddWidget(mHPText);




    mBloodScreen = mScene->GetUIManager()->CreateWidget<CImage>("BloodScreen");
    mBloodScreen->SetTint(1.f, 0.1f, 0.1f);
    mBloodScreen->SetOpacity(mBloodScreenOpacity);
    mBloodScreen->SetTexture("BloodScreen", TEXT("Texture\\UI\\VignettingFrame.png"));
    mBloodScreen->SetSize(1920.f, 1080.f);
    mBloodScreen->SetPos(0.f, 0.f);
    mBloodScreen->SetEnable(false);
    AddWidget(mBloodScreen);



    // 남은 적 이미지
    mEnemyCntImage = mScene->GetUIManager()->CreateWidget<CImage>("EnemyCntImage");
    mEnemyCntImage->SetTint(1.f, 1.f, 1.f);
    mEnemyCntImage->SetTexture("EnemyCnt", TEXT("Texture\\UI\\Enemy_Icon.png"));
    mEnemyCntImage->SetSize(12.f * gScaleMult, 10.f * gScaleMult);
    mEnemyCntImage->SetPos(1920.f - 50.f, 55.f);
    AddWidget(mEnemyCntImage);



    // 남은 적 텍스트
    mEnemyCntText = mScene->GetUIManager()->CreateWidget<CTextBlock>("EnemyCntText");
    mEnemyCntText->SetText(TEXT(""));
    mEnemyCntText->SetTextColor(255, 255, 255, 255);
    mEnemyCntText->SetPos(1920.f - 155.f, 40.f);
    mEnemyCntText->SetSize(100.f, 60.f);
    mEnemyCntText->SetAlignH(ETextAlignH::Right);
    mEnemyCntText->SetFontSize(30.f);
    AddWidget(mEnemyCntText);





    mResultWidget = mScene->GetUIManager()->CreateWidget<CResultWidget>("Result");
    mResultWidget->SetZOrder(10);
    mResultWidget->SetPos(0.f, 0.f);
    AddWidget(mResultWidget);
    mResultWidget->SetEnable(false);
    
    
    mSkill_A_Effect = mScene->GetUIManager()->CreateWidget<CImage>("Skill_A_EffectUI");
    mSkill_A_Effect->SetTexture("Skill_A_Effect", TEXT("Texture\\Effect\\SkillCoolDown\\Cooldown_Sheet.png"));
    mSkill_A_Effect->SetPos(1920.f / 2, 1080.f / 2);
    mSkill_A_Effect->SetSize(100.f * gScaleMult, 100.f * gScaleMult);

    float StartX = 0.f;
    for(int i = 0; i < 20; ++i)
    {
        StartX = 0 + i / 20.f;

        mSkill_A_Effect->AddBrushFrame(
            StartX , 0,
            1 / 20.f, 1);
    }
    AddWidget(mSkill_A_Effect);
    mSkill_A_Effect->SetEnable(false);
    mSkill_A_Effect->SetBrushAnimation(false);



    mSkill_S_Effect = mScene->GetUIManager()->CreateWidget<CImage>("mSkill_S_EffectUI");
    mSkill_S_Effect->SetTexture("Skill_S_Effect", TEXT("Texture\\Effect\\SkillCoolDown\\Cooldown_Sheet.png"));
    mSkill_S_Effect->SetPos(1920.f / 2, 1080.f / 2);
    mSkill_S_Effect->SetSize(100.f * gScaleMult, 100.f * gScaleMult);

    StartX = 0.f;
    for (int i = 0; i < 20; ++i)
    {
        StartX = 0 + i / 20.f;

        mSkill_S_Effect->AddBrushFrame(
            StartX, 0,
            1 / 20.f, 1);
    }
    AddWidget(mSkill_S_Effect);
    mSkill_S_Effect->SetEnable(false);
    mSkill_S_Effect->SetBrushAnimation(false);

    return true;
}

void CMainWidget::Update(float DeltaTime)
{
    CUserWidget::Update(DeltaTime);

    // 블러드 스크린 활성화라면
    if (mBloodScreen->IsEnable() == true)
    {
        // 오파시티 델타타임만큼 감소시키면서 줄이기
        mBloodScreenOpacityAcc -= DeltaTime * mBloodScreenScale;
        mBloodScreen->SetOpacity(mBloodScreenOpacityAcc);

        // 오파시티 0이면 Enable 비활성화
        if (mBloodScreenOpacityAcc <= 0)
        {
            mBloodScreen->SetEnable(false);
        }
    }

    // 결과창이 뜬 경우
    if (mResultWidget->IsEnable() && mReturnToLobby == true)
    {
        // X키가 눌렸다면,
        if (mScene->GetInput()->GetKeyPress('X'))
        {
            mReturnToLobby = false;

            // 데이터 초기화
            CGameInstance::GetInst()->Init();

            // 로비씬으로
            CSceneManager::GetInst()->CreateLoadScene<CSceneLobby>();

        }
    }

}

void CMainWidget::Render()
{
    CUserWidget::Render();
}

void CMainWidget::HPUpdate(int _HP, int _HPMax)
{
    // HP 텍스트 동기화
    mHPText->SetText((std::to_wstring(_HP) + L" / " + std::to_wstring(_HPMax)).c_str());
 
    // HP 프로그레스 바 동기화
    mHPBar->SetPercent((float)_HP / (float)_HPMax);

}

void CMainWidget::SkillA_Update(float _CurCoolTime, float _CoolTime)
{
    // 처음 들어왔을때,
    if (mSkillA_Once == false)
        SkillA_Off();   // 스킬 끄기

    // 프로그래스바 조절
    mSkill_A_ProgressBar->SetPercent(_CurCoolTime / _CoolTime);

    // 쿨타임이 끝났다면,
    if (_CurCoolTime <= 0.f)
        SkillA_On();    // 스킬 켜기
}   

void CMainWidget::SkillA_On()
{
    // 이펙트
    mSkill_A_Effect->SetBrushAnimation(true);
    FVector2D EffectPos = mSkill_A_ProgressBar->GetPos();
    mSkill_A_Effect->SetPos(EffectPos.x - 105.f, EffectPos.y - 73.f);

    mSkill_A_ProgressBar->SetGrayScale(EProgressBarImageType::Back, false);
    mSkill_A_ProgressBar->SetTint(EProgressBarImageType::Back, 1.f, 1.f, 1.f);
    mSkill_A_ProgressBar->SetTint(EProgressBarImageType::Fill, 1.f, 1.f, 1.f);
    mSkill_A_ProgressBar->SetOpacity(EProgressBarImageType::Fill, 0.f);
    mSkillA_Once = false;
}

void CMainWidget::SkillA_Off()
{
    //한번만 실행되어야 할 코드
    mSkill_A_ProgressBar->SetGrayScale(EProgressBarImageType::Back, true);
    mSkill_A_ProgressBar->SetTint(EProgressBarImageType::Fill, 0.f, 0.f, 0.f);
    mSkill_A_ProgressBar->SetOpacity(EProgressBarImageType::Fill, 0.7f);
    mSkillA_Once = true;
}

void CMainWidget::SkillS_Update(float _CurCoolTime, float _CoolTime)
{
    // 처음 들어왔을때,
    if (mSkillS_Once == false)
        SkillS_Off();   // 스킬 끄기

    // 프로그래스바 조절
    mSkill_S_ProgressBar->SetPercent(_CurCoolTime / _CoolTime);

    // 쿨타임이 끝났다면,
    if (_CurCoolTime <= 0.f)
    {
        // 이펙트
        mSkill_S_Effect->SetBrushAnimation(true);
        FVector2D EffectPos = mSkill_S_ProgressBar->GetPos();
        mSkill_S_Effect->SetPos(EffectPos.x - 105.f, EffectPos.y - 73.f);
    }

}

void CMainWidget::SkillS_On()
{

    mSkill_S_ProgressBar->SetGrayScale(EProgressBarImageType::Back, false);
    mSkillS_Once = false;

}

void CMainWidget::SkillS_Off()
{

    mSkill_S_ProgressBar->SetTint(EProgressBarImageType::Fill, 0.f, 0.f, 0.f);
    mSkill_S_ProgressBar->SetOpacity(EProgressBarImageType::Fill, 0.7f);
    mSkill_S_ProgressBar->SetGrayScale(EProgressBarImageType::Back, true);
    mSkillS_Once = true;

}

void CMainWidget::BloodScreenOn()
{
    mBloodScreenOpacityAcc = mBloodScreenOpacity;
    mBloodScreen->SetEnable(true);
}

bool CMainWidget::GetResultEnable()
{
    return mResultWidget->IsEnable();
}

void CMainWidget::SetResultEnable(bool flag)
{
    mResultWidget->SetEnable(flag);
}

void CMainWidget::SetEnemyCount(int count)
{
    mEnemyCntText->SetText(std::to_wstring(count).c_str());
}

