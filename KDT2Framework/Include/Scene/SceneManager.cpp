#include "SceneManager.h"
#include "SceneStart.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mCurrentScene);
}

bool CSceneManager::Init()
{
	// 초기 Start 씬 생성
	mCurrentScene = CreateScene<CSceneStart>();

	return true;
}

void CSceneManager::Input(float DeltaTime)
{
	mCurrentScene->Input(DeltaTime);
}

bool CSceneManager::Update(float DeltaTime)
{
	mCurrentScene->PreUpdate(DeltaTime);

	mCurrentScene->Update(DeltaTime);

	mCurrentScene->PostUpdate(DeltaTime);

	// 새롭게 로드된 씬이 있을 경우,
	if (mLoadScene)
	{





		// 기존 장면을 제거한다.
		SAFE_DELETE(mCurrentScene);

		// 현재 씬을 로드 씬으로
		mCurrentScene = mLoadScene;

		// 로드씬 초기화
		mLoadScene = nullptr;

		return true;
	}

	return false;
}

void CSceneManager::Collision(float DeltaTime)
{
	mCurrentScene->Collision(DeltaTime);
}

void CSceneManager::Render()
{
	mCurrentScene->Render();
}

void CSceneManager::RenderUI()
{
	mCurrentScene->RenderUI();
}

void CSceneManager::EndFrame()
{
	mCurrentScene->EndFrame();
}
