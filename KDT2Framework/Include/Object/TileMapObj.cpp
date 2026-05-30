#include "TileMapObj.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "../Share/Log.h"
#include "../Scene/SceneAssetManager.h"
#include "../Asset/Texture/Texture.h"

CTileMapObj::CTileMapObj()
{
}

CTileMapObj::CTileMapObj(const CTileMapObj& Obj) :
    CSceneObject(Obj)
{
}

CTileMapObj::CTileMapObj(CTileMapObj&& Obj) :
    CSceneObject(Obj)
{
}

CTileMapObj::~CTileMapObj()
{
}

void CTileMapObj::AddTileType()
{
    mEditTileType = (ETileType)((int)mEditTileType + 1);

    if (mEditTileType == ETileType::End)
        mEditTileType = ETileType::Normal;
}

void CTileMapObj::TileSelect(int index)
{
    mEditTileFrame = index;
}



bool CTileMapObj::Init()
{
    CSceneObject::Init();

    mTileMapRenderer = CreateComponent<CTileMapRendererComponent>();
    mTileMap = CreateComponent<CTileMapComponent>();

    mTileMap->SetTileOutLineRender(true);

    mScene->GetAssetManager()->LoadTexture("Field_BackGroundMap",
        TEXT("Texture\\BackGround\\Field\\Filed_BackGroundMap.png"));

    mScene->GetAssetManager()->LoadTexture("Field_BackGroundMap2",
        TEXT("Texture\\BackGround\\Field\\Filed_BackGroundMap_2.png"));

    mTileMapRenderer->SetBackTexture("Lobby_BackGroundMap",
        TEXT("Texture\\BackGround\\Lobby\\Lobby_BackGroundMap.png"));


    mTileMapRenderer->SetTileTexture("Tile",
        TEXT("Texture\\BackGround\\Tile\\1\\Tile01_Sheet.png"));


    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mTileMap->AddTileTextureFrame(j * 32.f,
                i * 32.f,
                32.f, 32.f);
        }
    }
    SetRootComponent(mTileMapRenderer);

    FVector2D BackTextureSize =  mTileMapRenderer->GetBackTexture()->GetTextureSize();
    int TileCountX = BackTextureSize.x / 32.f;
    int TileCountY = BackTextureSize.y / 32.f;


    //mTileMap->CreateTile(ETileShape::Rect,
    //    TileCountX, TileCountY, FVector2D(32.f * mMult, 32.f * mMult), -1);

    mTileMap->CreateTile(ETileShape::Rect,
        30, 26, FVector2D(32.f * mMult, 32.f * mMult), -1);



    mScene->GetInput()->AddBindKey("MovePoint", VK_RBUTTON);

    mScene->GetInput()->AddBindFunction<CTileMapObj>("MovePoint",
        EInputType::Press, this, &CTileMapObj::PrintMousePos);



    return true;
}

void CTileMapObj::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);


    // 마우스 위치 받아오기
    const FVector2D& MousePos = mScene->GetInput()->GetMouseWorldPos2D();
    MouseX = MousePos.x;
    MouseY = MousePos.y;

    //char	FPSText[64] = {};
    //sprintf_s(FPSText, "Mouse X : %f, Y : %f", MousePos.x, MousePos.y);
    //CLog::PrintLog(FPSText);

    if (mEditorMode == EEditorMode::TileImage)
    {
        // 왼쪽 버튼 꾹 눌렀을때, 타일 이미지 변경
        if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
            mTileMap->ChangeTileFrame(mEditTileFrame, MousePos);

        else if (mScene->GetInput()->GetMouseHold(EMouseButtonType::RButton))
            mTileMap->ChangeTileFrame(-1, MousePos);
    }

    /*

    // 에디트 모드가 타일타입일 경우
    if (mEditorMode == EEditorMode::TileType)
    {
        // LMB 누르고 있을경우
        if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
        {
            // 현재 타일타입 받아두기
            mOnMousePrevTileType = mEditTileType;

            // 타일타입 변경
            mTileMap->ChangeTileType(mEditTileType, MousePos);
        }

        // LMB 한번 누른경우
        else if (!mScene->GetInput()->GetMouseDown(EMouseButtonType::LButton))
        {
            // 현재 마우스 위치의 인덱스 구하기
            int Index = mTileMap->GetTileIndex(MousePos);

            // 현재 인덱스와 이전 클릭위치가 다를경우
            if (Index != mOnMousePrevIndex)
            {
                // 현재 마우스 위치의 타일을 MouseOver로 변경하고, 현재 마우스 위치의 타일타입 저장
                ETileType PrevType = mTileMap->ChangeTileType(ETileType::MouseOver, MousePos);

                // 현재 마우스 위치의 타일타입이 None이 아니라면
                if (PrevType != ETileType::None)
                {
                    이전 클릭위치가 있다면,
                    if (mOnMousePrevIndex != -1)
                    {
                        // 이전 클릭위치의 타일을 이전 클릭위치 타일타입으로 변경
                        mTileMap->ChangeTileType(mOnMousePrevTileType, mOnMousePrevIndex);
                    }

                    // 현재 마우스 인덱스 받아두기
                    mOnMousePrevIndex = mTileMap->GetTileIndex(MousePos);

                    // 이전 마우스 위치의 타일타입을 이전타입으로 변경
                    mOnMousePrevTileType = PrevType;
                }
                // 현재 마우스 위치의 타일타입이 None이라면
                else
                {
                    // 이전마우스 위치의 타입타입을 이전 타일타입으로 변경
                    mTileMap->ChangeTileType(mOnMousePrevTileType, mOnMousePrevIndex);
                    mOnMousePrevTileType = ETileType::None;
                    mOnMousePrevIndex = -1;
                }
            }
        }
    }

    // 타일 이미지 변경 모드일때,
    else if (mEditorMode == EEditorMode::TileImage)
    {
        // 왼쪽 버튼 꾹 눌렀을때, 타일 이미지 변경
        if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
            mTileMap->ChangeTileFrame(mEditTileFrame, MousePos);
    }
    */
}

void CTileMapObj::Save(const TCHAR* FullPath)
{
    mTileMap->Save(FullPath);
}

void CTileMapObj::Load(const TCHAR* FullPath)
{
    mTileMap->Load(FullPath);

    // 콜리전 생성 함수 호출

}

void CTileMapObj::PrintMousePos(float DeltaTime)
{
    CLog::Debug("[CTileMapObj::PrintMousePos] MousePos = ", MouseX, ", ", MouseY);
}
