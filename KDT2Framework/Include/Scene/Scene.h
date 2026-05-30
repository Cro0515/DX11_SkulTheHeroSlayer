#pragma once

#include "../GameInfo.h"
#include "../Object/SceneObject.h"

class CScene abstract
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

protected:
	class CInput* mInput = nullptr;								// 씬에서의 입력 시스템
	class CCameraManager* mCameraManager = nullptr;				// 씬에서의 카메라 매니저
	class CSceneCollision* mCollision = nullptr;				// 씬에서의 충돌 매니저
	class CSceneAssetManager* mAssetManager = nullptr;			// 씬에서의 에셋 매니저 
	class CSceneUIManager* mUIManager = nullptr;				// 씬에서의 UI 매니저
	class CNavigation* mNavigation = nullptr;					// 길 찾기 시스템
	std::list<CSharedPtr<class CSceneObject>>	mObjList;		// 씬에 소속된 오브젝트들을 가지고 있을 리스트
	bool	mDebugQuadTree = true;								// 디버그용 쿼드트리 출력
	CSharedPtr<class CTileMapObj>	mTileMapObj = nullptr;
	CSharedPtr<class CCameraObject>	mCameraObj = nullptr;

	class CPlayerObject* mPlayer = nullptr;
	class CMainWidget* mMainWidget = nullptr;					// 메인 위젯
	class CPortalObject* mPortal = nullptr;


	int mEnemyCount = 0;
	std::vector<class CCalleonSoldier*> mSolderVec;
	std::vector<class CCalleonArcher*>	mArcherVec;


public:
	void SetPlayer(class CPlayerObject* _Player)
	{
		mPlayer = _Player;
	}

	void SetMainWidget(class CMainWidget* _MainWidget)
	{
		mMainWidget = _MainWidget;
	}
	
	void MinusEnemyCount()
	{
		mEnemyCount--;
	}


public:

	int GetEnemyCount() const
	{
		return mEnemyCount;
	}

	class CPlayerObject* GetPlayer() const
	{
		return mPlayer;
	}

	class CMainWidget* GetMainWidget() const
	{
		return mMainWidget;
	}

	class CCameraObject* GetCameraObj() const
	{
		return mCameraObj;
	}


	class CTileMapObj* GetTileMapObj() const
	{
		return mTileMapObj;
	}

	class CNavigation* GetNavigation()	const
	{
		return mNavigation;
	}

	class CSceneUIManager* GetUIManager()	const
	{
		return mUIManager;
	}

	class CInput* GetInput()	const
	{
		return mInput;
	}

	class CCameraManager* GetCameraManager()	const
	{
		return mCameraManager;
	}

	class CSceneCollision* GetCollision()	const
	{
		return mCollision;
	}

	class CSceneAssetManager* GetAssetManager()	const
	{
		return mAssetManager;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void Input(float DeltaTime);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void EndFrame();
	virtual void NextScene();

protected:
	virtual bool InitAsset() = 0;
	virtual bool InitWidget() = 0;
	virtual bool InitObject() = 0;

public:
	template <typename T>
	T* CreateObj(const std::string& Name)
	{
		T* Obj = new T;

		Obj->mScene = this;
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		mObjList.push_back(Obj);

		return Obj;
	}

	template <typename T>
	T* FindObjectFromType()
	{
		auto	iter = mObjList.begin();
		auto	iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			T* Obj = dynamic_cast<T*>((*iter).Get());

			if (Obj)
				return Obj;
		}

		return nullptr;
	}

	template <typename T>
	T* FindObjectFromName(const std::string& Name)
	{
		auto	iter = mObjList.begin();
		auto	iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return dynamic_cast<T*>((*iter).Get());
		}

		return nullptr;
	}

	template <typename T>
	void FindObjectsFromType(
		std::list<CSharedPtr<T>>& result)
	{
		auto	iter = mObjList.begin();
		auto	iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			T* Obj = dynamic_cast<T*>((*iter).Get());

			if (Obj)
				result.push_back(Obj);
		}
	}
};


