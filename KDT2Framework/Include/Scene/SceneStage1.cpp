#include "SceneStage1.h"
#include "SceneAssetManager.h"
#include "SceneUIManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "../Object/TileMapObj.h"
#include "../Object/PlayerObject.h"
#include "../Object/CameraObject.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../Object/CalleonSoldier.h"
#include "../Object/CalleonArcher.h"
#include "../Scene/SceneStart.h"
#include "../Scene/SceneStage2.h"
#include "../GameInstance.h"
#include "../Object/PortalObject.h"
#include "../Share/Timer.h"


CSceneStage1::CSceneStage1()
{

}

CSceneStage1::~CSceneStage1()
{
}

bool CSceneStage1::InitAsset()
{


    return true;
}

bool CSceneStage1::InitWidget()
{
    mMainWidget = mUIManager->CreateWidget<CMainWidget>("Main");
    mUIManager->AddToViewport(mMainWidget);

    return true;
}

bool CSceneStage1::InitObject()
{
    mPlayer = CreateObj<CPlayerObject>("Player");
    mPlayer->SetPlayerData(CGameInstance::GetInst()->GetPlayerData());
    mPlayer->SetWorldPos(200, 900);

    // HP UI업데이트
    mMainWidget->HPUpdate(mPlayer->GetHP(), mPlayer->GetHPMax());


    mTileMapObj = CreateObj<CTileMapObj>("TileMap");
    TCHAR	FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, gRootPath);
    lstrcat(FullPath, TEXT("Asset\\Data\\Filed_1.tlm"));
    mTileMapObj->Load(FullPath);



    // Scene2으로 넘어가는 문 오브젝트 설치
    mPortal = CreateObj<CPortalObject>("Portal");
    mPortal->SetWorldPos(2300.f, 1700.f);
    mPortal->SetWorking(false);



        
    mInput->AddBindKey("Exit", VK_ESCAPE);
    mInput->AddBindFunction<CSceneStage1>("Exit",
        EInputType::Press, this, &CSceneStage1::Exit);


    mInput->AddBindKey("Scene_Next", 'P');
    mInput->AddBindFunction<CSceneStage1>("Scene_Next",
        EInputType::Press, this, &CSceneStage1::Next);


    mCameraObj = CreateObj<CCameraObject>("CameraObj");
    mCameraObj->SetTarget(mPlayer);
    // 카메라 오브젝트에게 타일맵으로 만든 전체 크기 정보를 전달
    FVector2D MapSize = mTileMapObj->GetMapSize();
    mCameraObj->SetMapSize(MapSize.x, MapSize.y);


    for (int i = 0; i < 3; ++i)
    {
        mSolderVec.push_back(CreateObj<CCalleonSoldier>("CalleonSoldier" + i));
        mEnemyCount++;
    }

    for (int i = 0; i < 1; ++i)
    {
        mArcherVec.push_back(CreateObj<CCalleonArcher>("CalleonArcher" + i));
        mEnemyCount++;
    }


    mMainWidget->SetEnemyCount(mEnemyCount);


    mSolderVec[0]->SetWorldPos(1050.f, 330.f);
    mSolderVec[1]->SetWorldPos(1550.f, 330.f);
    mSolderVec[2]->SetWorldPos(1540.f, 1760.f);
    
    mArcherVec[0]->SetWorldPos(2060.f, 530.f);


    return true;
}

void CSceneStage1::NextScene()
{
    // 플레이어 데이터 게임 인스턴스에 저장
    CGameInstance::GetInst()->SetPlayerData(mPlayer->GetPlayerData());

    CSceneManager::GetInst()->CreateLoadScene<CSceneStage2>();
}


void CSceneStage1::Exit(float DeltaTime)
{
    // 타임 스케일 초기화
    CTimer::SetTimeScale(1.0f);

    // 게임 인스턴스 데이터 초기화
    CGameInstance::GetInst()->Init();

    // 스타트씬으로 이동
    CSceneManager::GetInst()->CreateLoadScene<CSceneStart>();
}

void CSceneStage1::Next(float DeltaTime)
{
}