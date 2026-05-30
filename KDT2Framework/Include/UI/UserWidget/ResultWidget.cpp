#include "ResultWidget.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/TextBlock.h"
#include "../Common/Image.h"


CResultWidget::CResultWidget()
{
}

CResultWidget::~CResultWidget()
{
}

bool CResultWidget::Init()
{
    CWindowWidget::Init();

    // 백그라운드 이미지
    CSharedPtr<CImage> Background = mScene->GetUIManager()->CreateWidget<CImage>("Background");
    Background->SetTexture("Background", TEXT("Texture\\UI\\Background.png"));
    Background->SetTint(0.f, 0.f, 0.f);
    Background->SetOpacity(0.9f);
    Background->SetPos(0.f, 0.f);
    Background->SetSize(1920.f, 1080.f);
    AddWidget(Background);

    // 안내 창
    CSharedPtr<CImage> InfoFrame = mScene->GetUIManager()->CreateWidget<CImage>("InfoFrame");
    InfoFrame->SetTexture("InfoFrame", TEXT("Texture\\UI\\Quintessence_Frame_3.png"));
    InfoFrame->SetPivot(0.5f, 0.5f);
    InfoFrame->SetTint(1.f, 1.f, 1.f);
    InfoFrame->SetOpacity(1.0f);
    InfoFrame->SetPos(1920.f / 2.f, 1080.f / 2.f);
    InfoFrame->SetSize(332.f * 2.f, 206.f * 2.4);
    AddWidget(InfoFrame);


    // 타이틀 텍스트
    CSharedPtr<CTextBlock> TitleText = mScene->GetUIManager()->CreateWidget<CTextBlock>("TitleText");
    TitleText->SetText(TEXT("산산조각 났습니다!"));
    TitleText->SetPivot(0.5f, 0.5f);
    TitleText->SetTextColor(75, 53, 50, 255);
    TitleText->SetPos(450.f, 638.f);
    TitleText->SetSize(1000.f, 100.f);
    TitleText->SetAlignH(ETextAlignH::Center);
    TitleText->SetFontSize(25.f);
    TitleText->SetShadowEnable(false);
    AddWidget(TitleText);
    
    
    // 안내 텍스트
    CSharedPtr<CTextBlock> InfoText = mScene->GetUIManager()->CreateWidget<CTextBlock>("InfoText");
    InfoText->SetText(TEXT("당신은 적의 경험치가 되었습니다!!"));
    InfoText->SetPivot(0.5f, 0.5f);
    InfoText->SetTextColor(121, 86, 79, 255);
    InfoText->SetPos(700.f, 570.f);
    InfoText->SetSize(500.f, 60.f);
    InfoText->SetAlignH(ETextAlignH::Center);
    InfoText->SetFontSize(25.f);
    InfoText->SetShadowEnable(false);
    AddWidget(InfoText);




    CSharedPtr<CTextBlock> InfoText2 = mScene->GetUIManager()->CreateWidget<CTextBlock>("InfoText2");
    InfoText2->SetText(TEXT("처음으로 돌아가기"));
    InfoText2->SetPivot(0.5f, 0.5f);
    InfoText2->SetTextColor(121, 86, 79, 255);
    InfoText2->SetPos(700.f, 413.f);
    InfoText2->SetSize(500.f, 60.f);
    InfoText2->SetAlignH(ETextAlignH::Center);
    InfoText2->SetFontSize(20.f);
    InfoText2->SetShadowEnable(false);
    AddWidget(InfoText2);

    // X버튼 아이콘
    CSharedPtr<CImage> KeyIcon_X = mScene->GetUIManager()->CreateWidget<CImage>("KeyIcon_X");
    KeyIcon_X->SetTexture("KeyIcon_X", TEXT("Texture\\UI\\Key_X.png"));
    KeyIcon_X->SetPivot(0.5f, 0.5f);
    KeyIcon_X->SetTint(1.f, 1.f, 1.f);
    KeyIcon_X->SetOpacity(1.0f);
    KeyIcon_X->SetPos(1920.f/2.f, 400.f);
    KeyIcon_X->SetSize(15.f*2.f, 14.f*2.f);
    AddWidget(KeyIcon_X);


    return true;
}

void CResultWidget::Update(float DeltaTime)
{
    CWindowWidget::Update(DeltaTime);

}

void CResultWidget::Render()
{
    CWindowWidget::Render();


}
