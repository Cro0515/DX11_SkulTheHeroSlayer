#include "InfoDialogue.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"


CInfoDialogue::CInfoDialogue()
{
}

CInfoDialogue::~CInfoDialogue()
{
}

bool CInfoDialogue::Init()
{
    mBackground = mScene->GetUIManager()->CreateWidget<CImage>("back");
    mBackground->SetTexture("back", TEXT("Texture\\UI\\Dialogue2.png"));
    mBackground->SetPivot(0.5f, 0.5f);
    mBackground->SetTint(1.f, 1.f, 1.f);
    mBackground->SetOpacity(1.f);
    mBackground->SetPos(0.f, 0.f);
    mBackground->SetSize(90.f * gScaleMult, 24.f * gScaleMult);
    AddWidget(mBackground);

    // 텍스트
    mInfoText = mScene->GetUIManager()->CreateWidget<CTextBlock>("InfoText");
    mInfoText->SetText(TEXT("들어가기"));
    mInfoText->SetPivot(0.5f, 0.5f);
    mInfoText->SetTextColor(255, 255, 255, 255);
    mInfoText->SetPos(-20.f, -10.f);
    mInfoText->SetSize(100.f, 25.f);
    mInfoText->SetAlignH(ETextAlignH::Center);
    mInfoText->SetFontSize(25.f);
    mInfoText->SetShadowEnable(false);
    AddWidget(mInfoText);

    //mIcon
    mIcon = mScene->GetUIManager()->CreateWidget<CImage>("Key_F");
    mIcon->SetTexture("Key_F", TEXT("Texture\\UI\\Key_F.png"));
    mIcon->SetPivot(0.5f, 0.5f);
    mIcon->SetTint(1.f, 1.f, 1.f);
    mIcon->SetOpacity(1.0f);
    mIcon->SetPos(-50.f, 0.f);
    mIcon->SetSize(15.f * gScaleMult, 14.f * gScaleMult);
    AddWidget(mIcon);



    return true;
}

void CInfoDialogue::Render()
{
    CUserWidget::Render();
}

void CInfoDialogue::Render(const FVector3D& Pos)
{
    CUserWidget::Render(Pos);
}
