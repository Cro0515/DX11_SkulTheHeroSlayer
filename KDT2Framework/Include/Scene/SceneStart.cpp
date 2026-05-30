#include "SceneStart.h"
#include "SceneAssetManager.h"
#include "../UI/UserWidget/StartWidget.h"
#include "SceneUIManager.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Asset/AssetManager.h"

CSceneStart::CSceneStart()
{
}

CSceneStart::~CSceneStart()
{
}

bool CSceneStart::InitAsset()
{
    return true;
}

bool CSceneStart::InitWidget()
{
    CStartWidget* Widget = mUIManager->CreateWidget<CStartWidget>("Start");
    
    mUIManager->AddToViewport(Widget);

    return true;
}

bool CSceneStart::InitObject()
{
    GetAssetManager()->FindSound("BGM")->Stop();

    GetAssetManager()->FindSound("BGM")->Play();


    return true;
}
