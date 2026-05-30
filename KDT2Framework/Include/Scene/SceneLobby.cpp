#include "SceneLobby.h"
#include "SceneUIManager.h"
#include "SceneManager.h"
#include "SceneAssetManager.h"
#include "Input.h"
#include "../Object/PlayerObject.h"
#include "../Object/TileMapObj.h"
#include "../Object/CameraObject.h"
#include "../Scene/SceneStart.h"
#include "../Scene/SceneStage1.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../GameInstance.h"
#include "../Object/PortalObject.h"
#include "../Share/Timer.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Asset/AssetManager.h"



CSceneLobby::CSceneLobby()
{


}

CSceneLobby::~CSceneLobby()
{

}

bool CSceneLobby::InitAsset()
{



	return true;
}

bool CSceneLobby::InitWidget()
{
	//CMainWidget* MainWidget = mUIManager->CreateWidget<CMainWidget>("Main");
	//mUIManager->AddToViewport(MainWidget);

	mMainWidget = mUIManager->CreateWidget<CMainWidget>("Main");
	mUIManager->AddToViewport(mMainWidget);


	return true;
}

bool CSceneLobby::InitObject()
{
	mPlayer = CreateObj<CPlayerObject>("Player");
	mPlayer->SetPlayerData(CGameInstance::GetInst()->GetPlayerData());
	mPlayer->SetWorldPos(200, 900);

	// HP UI업데이트
	mMainWidget->HPUpdate(mPlayer->GetHP(), mPlayer->GetHPMax());

	mTileMapObj = CreateObj<CTileMapObj>("TileMap");
	TCHAR	FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, gRootPath);
	lstrcat(FullPath, TEXT("Asset\\Data\\Lobby.tlm"));

	mTileMapObj->Load(FullPath);



	// Scene1으로 넘어가는 문 오브젝트 설치
	mPortal = CreateObj<CPortalObject>("Portal");
	mPortal->SetWorldPos(2200.f, 360.f);
	mPortal->SetWorking(true);






	mInput->AddBindKey("Exit", VK_ESCAPE);
	mInput->AddBindFunction<CSceneLobby>("Exit",
		EInputType::Press, this, &CSceneLobby::Exit);
	

	mInput->AddBindKey("Scene_Next", VK_OEM_PERIOD);
	mInput->AddBindFunction<CSceneLobby>("Scene_Next",
		EInputType::Press, this, &CSceneLobby::Next);


	mCameraObj = CreateObj<CCameraObject>("CameraObj");
	mCameraObj->SetTarget(mPlayer);

	// 카메라 오브젝트에게 타일맵으로 만든 전체 크기 정보를 전달
	FVector2D MapSize = mTileMapObj->GetMapSize();
	mCameraObj->SetMapSize(MapSize.x, MapSize.y);


	


	return true;
}

void CSceneLobby::NextScene()
{
	// 플레이어 데이터 게임 인스턴스에 저장
	CGameInstance::GetInst()->SetPlayerData(mPlayer->GetPlayerData());
	CSceneManager::GetInst()->CreateLoadScene<CSceneStage1>();
}


void CSceneLobby::Exit(float DeltaTime)
{
	// 타임 스케일 초기화
	CTimer::SetTimeScale(1.0f);
	
	// 게임 인스턴스 데이터 초기화
	CGameInstance::GetInst()->Init();

	// 스타트씬으로 이동
	CSceneManager::GetInst()->CreateLoadScene<CSceneStart>();
}

void CSceneLobby::Next(float DeltaTime)
{

	
}
