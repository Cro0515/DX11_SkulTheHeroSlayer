#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList2D;	// 2D충돌체 배열
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList3D;	// 3D충돌체 배열
	class CCollisionQuadTree* mQuadTree;	// 충돌체크용 쿼드트리
	class CScene* mScene = nullptr;			// 소속된 씬
	float	mInterval = 0.f;				// 충돌체크 빈도수	/ 0이라면 매프레임 계산
	float	mIntervalTime = 0.f;			// 충돌체크 빈도수 계산용

public:
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime, class CSceneUIManager* UIManager,
		class CInput* Input);
	void Render();
	void ReturnNodePool();
};

