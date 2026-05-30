#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Component/StaticMeshComponent.h"
#include "SceneAssetManager.h"
#include "../Asset/Material/Material.h"
#include "../UI/UserWidget/MainWidget.h"
#include "SceneUIManager.h"
#include "../Object/TileMapObj.h"
#include "Input.h"
#include "SceneManager.h"
#include "../Scene/SceneStart.h"
#include "../Object/CameraObject.h"
#include "../Object/CalleonSoldier.h"
#include "../Object/CalleonArcher.h"



CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::InitAsset()
{


    return true;
}

bool CSceneMain::InitObject()
{
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");
    Player->SetWorldPos(200, 900);


    mTileMapObj = CreateObj<CTileMapObj>("TileMap");
    TCHAR	FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, gRootPath);
    lstrcat(FullPath, TEXT("Asset\\Data\\Filed_1.tlm"));

    mTileMapObj->Load(FullPath);

    mInput->AddBindKey("Exit", VK_ESCAPE);
    mInput->AddBindFunction<CSceneMain>("Exit",
        EInputType::Press, this, &CSceneMain::Exit);

    mCameraObj = CreateObj<CCameraObject>("CameraObj");
    mCameraObj->SetTarget(Player);
    // 카메라 오브젝트에게 타일맵으로 만든 전체 크기 정보를 전달
    FVector2D MapSize = mTileMapObj->GetMapSize();
    mCameraObj->SetMapSize(MapSize.x, MapSize.y);





    CCalleonSoldier* CalleonSoldier1 = CreateObj<CCalleonSoldier>("CalleonSoldier1");
    CalleonSoldier1->SetWorldPos(1200, 550);
    
    CCalleonArcher* CalleonArcher1 = CreateObj<CCalleonArcher>("CalleonArcher1");
    CalleonArcher1->SetWorldPos(2300, 550);
    
    //CCalleonSoldier* CalleonSoldier2 = CreateObj<CCalleonSoldier>("CalleonSoldier2");
    //CalleonSoldier2->SetWorldPos(1300, 550);







    return true;
}

bool CSceneMain::InitWidget()
{
    //CMainWidget* MainWidget = mUIManager->CreateWidget<CMainWidget>("Main");
    //mUIManager->AddToViewport(MainWidget);

    mMainWidget = mUIManager->CreateWidget<CMainWidget>("Main");
    mUIManager->AddToViewport(mMainWidget);

    return true;
}

void CSceneMain::Exit(float DeltaTime)
{
    CSceneManager::GetInst()->CreateLoadScene<CSceneStart>();
}
