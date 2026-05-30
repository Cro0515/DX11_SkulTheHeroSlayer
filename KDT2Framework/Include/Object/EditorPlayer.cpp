#include "EditorPlayer.h"
#include "../Component/CameraComponent.h"
#include "../Component/CharacterMovementComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "../Object/CameraObject.h"
#include "../Share/Log.h"

CEditorPlayer::CEditorPlayer()
{
}

CEditorPlayer::CEditorPlayer(const CEditorPlayer& Obj)  :
    CSceneObject(Obj)
{
}

CEditorPlayer::CEditorPlayer(CEditorPlayer&& Obj) :
    CSceneObject(Obj)
{
}

CEditorPlayer::~CEditorPlayer()
{
}

bool CEditorPlayer::Init()
{
    CSceneObject::Init();
    mRoot = CreateComponent<CSceneComponent>();
    SetRootComponent(mRoot);

    mMovement = CreateComponent<CCharacterMovementComponent>();
    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(1000.f);
    mMovement->SetGround(true);
    mMovement->SetEditMode(true);

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->ChangeKeyShift("MoveUp", true);
    mScene->GetInput()->AddBindKey("MoveDown", 'S');
    mScene->GetInput()->ChangeKeyShift("MoveDown", true);
    mScene->GetInput()->AddBindKey("MoveLeft", 'A');
    mScene->GetInput()->ChangeKeyShift("MoveLeft", true);
    mScene->GetInput()->AddBindKey("MoveRight", 'D');
    mScene->GetInput()->ChangeKeyShift("MoveRight", true);

    mScene->GetInput()->AddBindFunction<CEditorPlayer>("MoveUp",
        EInputType::Hold, this, &CEditorPlayer::MoveUp);

    mScene->GetInput()->AddBindFunction<CEditorPlayer>("MoveDown",
        EInputType::Hold, this, &CEditorPlayer::MoveDown);

    mScene->GetInput()->AddBindFunction<CEditorPlayer>("MoveLeft",
        EInputType::Hold, this, &CEditorPlayer::MoveLeft);

    mScene->GetInput()->AddBindFunction<CEditorPlayer>("MoveRight",
        EInputType::Hold, this, &CEditorPlayer::MoveRight);

    SetUseGravity(false);

    float CameraHalfHeight = mScene->GetCameraObj()->GetCameraComponenet()->GetCameraHalfHeight();
    float CameraHalfWidth = mScene->GetCameraObj()->GetCameraComponenet()->GetCameraHalfWidth();
    float MapHeight = mScene->GetCameraObj()->GetCameraComponenet()->GetMapHeight();
    float MapWidth = mScene->GetCameraObj()->GetCameraComponenet()->GetMapWidth();
    
    mLimitMinX = CameraHalfWidth;
    mLimitMinY = CameraHalfHeight;
    mLimitMaxX = MapWidth - CameraHalfWidth;
    mLimitMaxY = MapHeight - CameraHalfHeight;

    SetWorldPos(mLimitMinX, mLimitMinY);

    return true;
}

void CEditorPlayer::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 이동제한
    FVector3D Pos = GetWorldPosition();

    if (Pos.x < mLimitMinX)
        Pos.x = mLimitMinX;
    else if (Pos.x > mLimitMaxX)
        Pos.x = mLimitMaxX;

    if (Pos.y < mLimitMinY)
        Pos.y = mLimitMinY;
    else if (Pos.y > mLimitMaxY)
        Pos.y = mLimitMaxY;

    SetWorldPos(Pos);
}

void CEditorPlayer::MoveUp(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));
}

void CEditorPlayer::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);
}

void CEditorPlayer::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);
}

void CEditorPlayer::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));
}
