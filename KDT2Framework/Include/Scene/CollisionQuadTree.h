#pragma once

#include "../GameInfo.h"

#define	QUADTREE_DEPTH_MAX		4
#define	QUADTREE_DIVISION_COUNT	5

class CCollisionQuadTreeNode
{
	friend class CCollisionQuadTree;

private:
	CCollisionQuadTreeNode();
	~CCollisionQuadTreeNode();

private:
	class CScene* mScene = nullptr;					// 노드를 소유한 씬				
	CCollisionQuadTree* mTree = nullptr;			// 노드를 소유한 쿼드트리
	CCollisionQuadTreeNode* mParent = nullptr;		// 노드를 소유한 부모노드
	CCollisionQuadTreeNode* mChild[4] = {};			// 소유하고있는 자식 노드
	FVector2D mCenter;								// 노드의 중점 좌표
	FVector2D mSize;								// 노드의 크기
	int mDepth = 0;									// 분할 깊이
	int mDivisionCount = QUADTREE_DIVISION_COUNT;	// 분할 조건 (충돌체 개수)
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList;	// 노드에 존재하는 충돌체들 목록

#ifdef _DEBUG
	class CTransformCBuffer* mTransformCBuffer;		// 디버그용 쿼드트리 노드 출력을 위한 상수버퍼
#endif // _DEBUG


public:
	void AddCollider(class CColliderBase* Collider,
		std::vector<CCollisionQuadTreeNode*>& NodePool);
	void CreateChild(std::vector<CCollisionQuadTreeNode*>& NodePool);
	void Collision(float DeltaTime);
	void ReturnNodePool(std::vector<CCollisionQuadTreeNode*>& NodePool);
	void Render(class CMesh* Mesh, class CShader* Shader);

private:
	bool IsInCollider(class CColliderBase* Collider);
};

class CCollisionQuadTree
{
	friend class CSceneCollision;

private:
	CCollisionQuadTree();
	~CCollisionQuadTree();

private:
	class CScene* mScene = nullptr;									// 소속된 씬
	CCollisionQuadTreeNode* mRoot = nullptr;						// 최상위 노드
	int		mDivisionCount = QUADTREE_DIVISION_COUNT;				// 분할 조건
	std::vector<CCollisionQuadTreeNode*>	mNodePool;				// 노드 풀
	std::vector<CCollisionQuadTreeNode*>	mCollisionNodeList;		// 충돌체 목록

#ifdef _DEBUG
	CSharedPtr<class CMesh>		mMesh;			// 디버그 출력용 노드 메쉬
	CSharedPtr<class CShader>	mShader;		// 디버그 출력용 노드 쉐이더
	class CColliderCBuffer* mColliderCBuffer;	// 디버그 출력용 충돌체 상수버퍼
#endif // _DEBUG


public:
	void SetDivisionCount(int Count);
	void AddCollisionNodeList(CCollisionQuadTreeNode* Node)
	{
		mCollisionNodeList.emplace_back(Node);
	}

	void EraseCollisionNodeList(CCollisionQuadTreeNode* Node);

public:
	bool Init();
	void AddCollider(class CColliderBase* Collider);
	void Update(float DeltaTime);
	void Collision(float DeltaTime);
	void Render();
	void ReturnNodePool();
};

