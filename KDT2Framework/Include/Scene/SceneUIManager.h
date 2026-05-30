#pragma once

#include "../UI/UserWidget/WindowWidget.h"

class CSceneUIManager
{
	friend class CScene;

private:
	CSceneUIManager();
	~CSceneUIManager();

private:
	class CScene* mScene = nullptr;			// 소속된 씬
	std::unordered_map<std::string, CSharedPtr<CWindowWidget>>	mWindowMap;		// 창 위젯들을 가지고 있을 unordered_map
	std::vector<CSharedPtr<CWidget>>	mWidgetList;							// 모든 위젯 배열
	CSharedPtr<CWidget>					mMouseHoveredWidget;					// 마우스에 피킹된 UI

public:
	void AddWindowWidget(const std::string& Name,
		CWindowWidget* Widget)
	{
		if (FindWindowWidget(Name))
			return;

		mWindowMap.insert(std::make_pair(Name, Widget));
	}

	CWindowWidget* FindWindowWidget(const std::string& Name)
	{
		auto	iter = mWindowMap.find(Name);

		if (iter == mWindowMap.end())
			return nullptr;

		return iter->second;
	} 

	void AddToViewport(CWidget* Widget);

public:
	bool Init();
	void Update(float DeltaTime);
	bool CollisionMouse(float DeltaTime, const FVector2D& MousePos);
	void Collision(float DeltaTime);
	void Render();

private:
	static bool SortCollision(const CSharedPtr<CWidget>& Src,
		const CSharedPtr<CWidget>& Dest);

	static bool SortRender(const CSharedPtr<CWidget>& Src,
		const CSharedPtr<CWidget>& Dest);

public:
	template <typename T>
	T* CreateWidget(const std::string& Name,
		CSceneObject* Owner = nullptr)
	{
		T* Widget = new T;

		Widget->mScene = mScene;
		Widget->mOwnerObject = Owner;
		Widget->mName = Name;

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		return Widget;
	}


public:
	template <typename T>
	static T* CreateWidgetStatic(const std::string& Name)
	{
		T* Widget = new T;

		Widget->mName = Name;

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		return Widget;
	}
};

