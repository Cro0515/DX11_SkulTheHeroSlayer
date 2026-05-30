#include "PortalObject.h"
#include "../Scene/Scene.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/SpriteComponent.h"
#include "../Object/PlayerObject.h"
#include "../Scene/Input.h"
#include "../GameInstance.h"
#include "../Scene/SceneMain.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneUIManager.h"
#include "../Scene/SceneStage1.h"
#include "../UI/UserWidget/InfoDialogue.h"
#include "../Component/WidgetComponent.h"


CPortalObject::CPortalObject()
{
}

CPortalObject::CPortalObject(const CPortalObject& Obj) : CSceneObject(Obj)
{
}

CPortalObject::CPortalObject(CPortalObject&& Obj) : CSceneObject(Obj)
{
}

CPortalObject::~CPortalObject()
{
}


void CPortalObject::SetPortalType(EPortalType type)
{
	mPortalType = type;

	// 포탈 타입에 따른 이미지
	PortalClose();
}

void CPortalObject::SetWorking(bool flag)
{
	if (flag == true)
	{
		PortalOpen();
	}
	else
	{
		PortalClose();
	}
}

void CPortalObject::SetTexture(const std::string& Name, const TCHAR* FileName, int TextureIndex)
{
	mRoot->SetTexture(Name, FileName, TextureIndex);
}

bool CPortalObject::Init()
{

	mRoot = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	mInfoWidget = CreateComponent<CWidgetComponent>();

	bUseGravity = false;
	mCollision = mBody;

	mPortalType = EPortalType::Normal;
	mRoot->SetTexture("NormalPortal_DeActive", TEXT("Texture/Object/Normal_Deactive.png"));
	mRoot->SetPivot(0.5f, 0.f);
	mRoot->SetWorldPos(0.f, 0.f, 0.f);
	mRoot->SetWorldScale(176.f * gScaleMult, 128.f * gScaleMult, 1.f);
	SetRootComponent(mRoot);

	mBody->SetCollisionProfile("Portal");
	mBody->SetBoxSize(250.f, 128.f * gScaleMult);
	mBody->SetRelativePos(13.f, 200.f);	
	mBody->SetCollisionBeginFunc<CPortalObject>(this, &CPortalObject::PortalBegin);
	mBody->SetCollisionEndFunc<CPortalObject>(this, &CPortalObject::PortalEnd);
	mRoot->AddChild(mBody);



	CSharedPtr<CInfoDialogue> InfoDialogue = mScene->GetUIManager()->CreateWidget<CInfoDialogue>("Dialogue");
	mInfoWidget->SetRelativePos(0.f, -50.f);
	mInfoWidget->SetPivot(0.5f, 0.5f);
	mInfoWidget->SetWidget(InfoDialogue);
	mRoot->AddChild(mInfoWidget);
	mInfoWidget->SetEnable(false);

	return true;
}

void CPortalObject::PreUpdate(float DeltaTime)
{
	CSceneObject::PreUpdate(DeltaTime);

}

void CPortalObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
	
	if (mWorking == false)
	{
		if (mScene->GetEnemyCount() <= 0)
		{
			mWorking = true;
			
			// 열린 이미지로 변경
			PortalOpen();
		}
	}

	if (mWorking == true)
	{
		if (mDetect == true)
		{
			// F키가 눌렸을때
			if (mScene->GetInput()->GetKeyPress('F'))
			{
				mDetect = false;

				// 각 씬에 등록된 NextScene함수 호출
				mScene->NextScene();
			}
		}
	}
	
}

void CPortalObject::PostUpdate(float DeltaTime)
{
	CSceneObject::PostUpdate(DeltaTime);


}

void CPortalObject::Render()
{
	CSceneObject::Render();

}

void CPortalObject::PortalBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CPlayerObject* Player = dynamic_cast<CPlayerObject*>(Dest->GetOwner());

	// 플레이어가 있고
	if (Player)
	{
		mDetect = true;

		if (mWorking == true)
		{
			// 안내메세지 UI Enable 활성화
			mInfoWidget->SetEnable(true);
		}
	}
}

void CPortalObject::PortalEnd(CColliderBase* Dest)
{
	CPlayerObject* Player = dynamic_cast<CPlayerObject*>(Dest->GetOwner());

	if (Player)
	{
		mDetect = false;


		if (mWorking == true)
		{
			// 안내메세지 UI Enable 비활성화
			mInfoWidget->SetEnable(false);
		}
	}
}

void CPortalObject::PortalOpen()
{
	// 열린 이미지로 변경
	if (mPortalType == EPortalType::Normal)
	{
		mRoot->SetTexture("NormalPortal_Active", TEXT("Texture/Object/Normal_Active.png"));
	}
	else if (mPortalType == EPortalType::Boss)
	{
		mRoot->SetTexture("BossPortal_Active", TEXT("Texture/Object/Boss_Active.png"));
	}
}

void CPortalObject::PortalClose()
{
	if (mPortalType == EPortalType::Normal)
	{
		mRoot->SetTexture("NormalPortal_Deactive", TEXT("Texture/Object/Normal_Deactive.png"));
	}
	else if (mPortalType == EPortalType::Boss)
	{
		mRoot->SetTexture("BossPortal_Deactive", TEXT("Texture/Object/Boss_Deactive.png"));
	}
}
