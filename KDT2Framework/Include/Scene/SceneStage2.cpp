#include "SceneStage2.h"
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
#include "../GameInstance.h"
#include "../Object/PortalObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Share/Timer.h"


CSceneStage2::CSceneStage2()
{
}

CSceneStage2::~CSceneStage2()
{
}

bool CSceneStage2::InitAsset()
{
    return true;
}


bool CSceneStage2::InitWidget()
{

    mMainWidget = mUIManager->CreateWidget<CMainWidget>("Main");
    mUIManager->AddToViewport(mMainWidget);

    return true;
}

bool CSceneStage2::InitObject()
{
    mPlayer = CreateObj<CPlayerObject>("Player");
    mPlayer->SetPlayerData(CGameInstance::GetInst()->GetPlayerData());
    mPlayer->SetWorldPos(200, 900);

    // HP UI업데이트
    mMainWidget->HPUpdate(mPlayer->GetHP(), mPlayer->GetHPMax());


    mTileMapObj = CreateObj<CTileMapObj>("TileMap");
    TCHAR	FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, gRootPath);
    lstrcat(FullPath, TEXT("Asset\\Data\\Filed_2.tlm"));
    mTileMapObj->Load(FullPath);


    // Scene1으로 넘어가는 문 오브젝트 설치
    mPortal = CreateObj<CPortalObject>("Portal");
    mPortal->SetTexture("Portal", TEXT("Texture/Object/Boss_Deactive.png"));
    mPortal->SetWorldPos(1440.f, 270.f);
    mPortal->GetBody()->SetRelativePos(0.f, 200.f);
    mPortal->SetWorking(false);
    mPortal->SetPortalType(EPortalType::Boss);

    for (int i = 0; i < 3; ++i)
    {
        mSolderVec.push_back(CreateObj<CCalleonSoldier>("CalleonSoldier" + i));
        mEnemyCount++;
    }

    for (int i = 0; i < 2; ++i)
    {
        mArcherVec.push_back(CreateObj<CCalleonArcher>("CalleonArcher" + i));
        mEnemyCount++;
    }

    mMainWidget->SetEnemyCount(mEnemyCount);


    mSolderVec[0]->SetWorldPos(860.f, 330.f);
    mSolderVec[1]->SetWorldPos(2060.f, 330.f);
    mSolderVec[2]->SetWorldPos(1440.f, 1490.f);

    mArcherVec[0]->SetWorldPos(1000.f, 1000.f);
    mArcherVec[1]->SetWorldPos(1870.f, 1000.f);





    mInput->AddBindKey("Exit", VK_ESCAPE);
    mInput->AddBindFunction<CSceneStage2>("Exit",
        EInputType::Press, this, &CSceneStage2::Exit);



    mInput->AddBindKey("Scene_Next", VK_OEM_PERIOD);
    mInput->AddBindFunction<CSceneStage2>("Scene_Next",
        EInputType::Press, this, &CSceneStage2::Next);


    mCameraObj = CreateObj<CCameraObject>("CameraObj");
    mCameraObj->SetTarget(mPlayer);
    // 카메라 오브젝트에게 타일맵으로 만든 전체 크기 정보를 전달
    FVector2D MapSize = mTileMapObj->GetMapSize();
    mCameraObj->SetMapSize(MapSize.x, MapSize.y);

    return true;
}

void CSceneStage2::NextScene()
{
    CLog::Debug("보스보스보스보스보스보스보스보스보스보스");
}

void CSceneStage2::Exit(float DeltaTime)
{
    CSceneManager::GetInst()->CreateLoadScene<CSceneStart>();
}

void CSceneStage2::Next(float DeltaTime)
{
    // 타임 스케일 초기화
    CTimer::SetTimeScale(1.0f);

    // 게임 인스턴스 데이터 초기화
    CGameInstance::GetInst()->Init();

    // 스타트씬으로 이동
    CSceneManager::GetInst()->CreateLoadScene<CSceneStart>();

}
