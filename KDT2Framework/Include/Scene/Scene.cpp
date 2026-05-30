#include "Scene.h"
#include "../Object/SceneObject.h"
#include "Input.h"
#include "CameraManager.h"
#include "SceneCollision.h"
#include "../Share/Log.h"
#include "SceneAssetManager.h"
#include "../Render/RenderManager.h"
#include "SceneUIManager.h"
#include "Navigation.h"
#include "../Object/TileMapObj.h"
#include "../Object/CameraObject.h"
#include "../Object/CalleonSoldier.h"
#include "../Object/CalleonArcher.h"
#include "../Object/PortalObject.h"
#include "../Share/Timer.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	//CRenderManager::GetInst()->ClearRenderList();
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Destroy();
	}
	mObjList.clear();

	/*for (int i = 0; i < mSolderVec.size(); ++i)
	{
		mSolderVec[i]->Destroy();
	}
	mSolderVec.clear();


	for (int i = 0; i < mArcherVec.size(); ++i)
	{
		mArcherVec[i]->Destroy();
	}
	mArcherVec.clear();*/


	SAFE_DELETE(mUIManager);
	SAFE_DELETE(mAssetManager);
	SAFE_DELETE(mCollision);
	SAFE_DELETE(mCameraManager);
	SAFE_DELETE(mInput);
	SAFE_DELETE(mNavigation);
}

bool CScene::Init()
{
	// 입력 시스템 생성 및 초기화
	mInput = new CInput;
	mInput->mScene = this;
	if (!mInput->Init())
		return false;

	// 카메라 생성 및 초기화
	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
		return false;
	
	// 충돌 매니저 생성 및 초기화
	mCollision = new CSceneCollision;
	mCollision->mScene = this;
	if (!mCollision->Init())
		return false;

	// 에셋 매니저 생성 및 초기화
	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
		return false;

	// UI 매니저 생성 및 초기화
	mUIManager = new CSceneUIManager;
	mUIManager->mScene = this;
	if (!mUIManager->Init())
		return false;

	// 길찾기 시스템 생성 및 초기화
	mNavigation = new CNavigation;
	mNavigation->mScene = this;
	if (!mNavigation->Init())
		return false;


	InitAsset();
	InitWidget();
	InitObject();

	CTimer::SetTimeScale(1.0f);


	return true;
}

bool CScene::Init(const char* FileName)
{
	// 카메라 생성 및 초기화
	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
		return false;

	// 입력 시스템 생성 및 초기화
	mInput = new CInput;
	if (!mInput->Init())
		return false;

	// 충돌 매니저 생성 및 초기화
	mCollision = new CSceneCollision;
	mCollision->mScene = this;
	if (!mCollision->Init())
		return false;

	// 에셋 매니저 생성 및 초기화
	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
		return false;

	// UI 매니저 생성 및 초기화
	mUIManager = new CSceneUIManager;
	mUIManager->mScene = this;
	if (!mUIManager->Init())
		return false;

	// 길찾기 시스템 생성 및 초기화
	mNavigation = new CNavigation;
	mNavigation->mScene = this;
	if (!mNavigation->Init())
		return false;

	InitAsset();
	InitWidget();
	InitObject();


	
	return true;
}

void CScene::Input(float DeltaTime)
{
	mInput->Update(DeltaTime);
}

void CScene::PreUpdate(float DeltaTime)
{
	// Object들의 PreUpdate 호출 
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		// 액티브가 꺼져있다면, 리스트에서 제거
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}

		// 액티브는 켜져있지만 비활성 상태라면, 스킵
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		// PreUpdate 호출
		(*iter)->PreUpdate(DeltaTime);

		++iter;
	}
}

void CScene::Update(float DeltaTime)
{
	// Object들의 Update 호출 
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		// 액티브가 꺼져있다면, 리스트에서 제거
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}

		// 액티브는 켜져있지만 비활성 상태라면, 스킵
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		// Update 호출
		(*iter)->Update(DeltaTime);

		++iter;
	}




	mCameraManager->Update(DeltaTime);
	mUIManager->Update(DeltaTime);

	int	Count = (int)mObjList.size();
	
	char	Text[64] = {};
	sprintf_s(Text, "ObjCount : %d", Count);
	//CLog::PrintLog(Text);
}

void CScene::PostUpdate(float DeltaTime)
{
	// Object들의 PostUpdate 호출 
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		// 액티브가 꺼져있다면, 리스트에서 제거
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}

		// 액티브는 켜져있지만 비활성 상태라면, 스킵
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		// PostUpdate 호출
		(*iter)->PostUpdate(DeltaTime);

		++iter;
	}
}

void CScene::Collision(float DeltaTime)
{
	// UI와의 충돌도 Collision 안쪽에서 처리한다.
	mCollision->Update(DeltaTime, mUIManager, mInput);
}

void CScene::Render()
{

// 디버그 모드일때,
#ifdef _DEBUG
	// 쿼드트리 출력이라면
	if (mDebugQuadTree)
		// 충돌 매니저 Render 호출
		mCollision->Render();

#endif // _DEBUG

	// 쿼드트리 노드들을 풀에 반환
	mCollision->ReturnNodePool();

	//std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	//std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	//for (iter = mObjList.begin(); iter != iterEnd;)
	//{
	//	if (!(*iter)->IsActive())
	//	{
	//		// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
	//		iter = mObjList.erase(iter);
	//		iterEnd = mObjList.end();
	//		continue;
	//	}

	//	else if (!(*iter)->IsEnable())
	//	{
	//		++iter;
	//		continue;
	//	}

	//	(*iter)->Render();

	//	++iter;
	//}

}

void CScene::RenderUI()
{
	// UI 출력
	mUIManager->Render();
}

void CScene::EndFrame()
{
	// 오브젝트 리스트들의 EndFrame 호출
	// EndFrame은 한 프레임이 끝나기전에 초기화 할 데이터들을 초기화 시키기 위한 함수
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EndFrame();
	}
}

void CScene::NextScene()
{
}

bool CScene::InitAsset()
{
	return false;
}

bool CScene::InitWidget()
{
	return false;
}

bool CScene::InitObject()
{
	return false;
}