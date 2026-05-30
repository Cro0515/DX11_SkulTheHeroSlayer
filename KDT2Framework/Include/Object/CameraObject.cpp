#include "CameraObject.h"
#include "../Component/CameraComponent.h"
#include "../Share/Log.h"


CCameraObject::CCameraObject()
{
}

CCameraObject::CCameraObject(const CCameraObject& Obj) :
	CSceneObject(Obj)
{
}

CCameraObject::CCameraObject(CCameraObject&& Obj) :
	CSceneObject(Obj)
{
}

CCameraObject::~CCameraObject()
{
}

bool CCameraObject::Init()
{
	mRoot = CreateComponent<CCameraComponent>();

	mRoot->SetProjectionType(ECameraProjectionType::Ortho);
	SetRootComponent(mRoot);
	FVector3D temp = mRoot->GetWorldPosition();
	mRoot->SetRelativePos(FVector3D(0, 230.f, 0));

	return true;
}

void CCameraObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

}

void CCameraObject::SetTarget(CSceneObject* Obj)
{
	mRoot->SetTarget(Obj);
}

void CCameraObject::SetMapSize(float Width, float Height)
{
	mRoot->SetMapSize(Width, Height);
}
