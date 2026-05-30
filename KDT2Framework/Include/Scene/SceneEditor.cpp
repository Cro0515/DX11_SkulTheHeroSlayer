#include "SceneEditor.h"
#include "../Object/TileMapObj.h"
#include "../Object/EditorPlayer.h"
#include "Input.h"
#include "../GameManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneMain.h"
#include "../Scene/SceneStart.h"
#include "../Object/CameraObject.h"


CSceneEditor::CSceneEditor()
{
}

CSceneEditor::~CSceneEditor()
{
}

bool CSceneEditor::InitAsset()
{
    return true;
}

bool CSceneEditor::InitObject()
{

    mTileMapObj = CreateObj<CTileMapObj>("TileMap");
    mTileMapObj->SetEditorMode(mEditorMode);
    mTileMapObj->SetEditorMode(EEditorMode::TileImage);

    mInput->AddBindKey("Exit", VK_ESCAPE);
    mInput->AddBindFunction<CSceneEditor>("Exit",
        EInputType::Press, this, &CSceneEditor::Exit);
    mCameraObj = CreateObj<CCameraObject>("CameraObj");

    // 카메라 오브젝트에게 타일맵으로 만든 전체 크기 정보를 전달
    FVector2D MapSize = mTileMapObj->GetMapSize();
    mCameraObj->SetMapSize(MapSize.x, MapSize.y);

    CEditorPlayer* EditorPlayer = CreateObj<CEditorPlayer>("EditorPlayer");

    mCameraObj->SetTarget(EditorPlayer);

    char KeyArray[20] = { '1','2','3','4',
                        'Q','W','E','R',
                        'A','S','D','F',
                        'Z','X','C','V',
                        'T','Y','U','I'};


    std::string Name;
    int size = sizeof(KeyArray);
    for (int i = 0; i < size; ++i)
    {
        Name = "TileSelect_";
        Name += KeyArray[i];

        mInput->AddBindKey(Name, KeyArray[i]);
        mInput->AddBindFunction<CSceneEditor>(Name,
            EInputType::Press, this, &CSceneEditor::TileSelect, i);
    }


    //mInput->AddBindKey("EditorMode", '1');
    //mInput->AddBindFunction<CSceneEditor>("EditorMode",
    //    EInputType::Press, this, &CSceneEditor::EditorMode);

    //mInput->AddBindKey("TileType", '2');
    //mInput->AddBindFunction<CSceneEditor>("TileType",
    //    EInputType::Press, this, &CSceneEditor::TileTypeKey);



    mInput->AddBindKey("Background_Prev", VK_OEM_COMMA);
    mInput->AddBindFunction<CSceneEditor>("Background_Prev",
        EInputType::Press, this, &CSceneEditor::Background_Prev);

    mInput->AddBindKey("Background_Next", VK_OEM_PERIOD);
    mInput->AddBindFunction<CSceneEditor>("Background_Next",
        EInputType::Press, this, &CSceneEditor::Background_Next);




    mInput->AddBindKey("Save", 'S');
    mInput->ChangeKeyCtrl("Save", true);
    mInput->AddBindFunction<CSceneEditor>("Save",
        EInputType::Press, this, &CSceneEditor::SaveKey);

    mInput->AddBindKey("Load", 'O');
    mInput->ChangeKeyCtrl("Load", true);
    mInput->AddBindFunction<CSceneEditor>("Load",
        EInputType::Press, this, &CSceneEditor::LoadKey);

    return true;
}

bool CSceneEditor::InitWidget()
{
    return true;
}

//void CSceneEditor::EditorMode(float DeltaTime)
//{
//    mEditorMode = (EEditorMode)((int)mEditorMode + 1);
//
//    if (mEditorMode == EEditorMode::End)
//        mEditorMode = EEditorMode::TileType;
//
//    mTileMapObj->SetEditorMode(mEditorMode);
//}
//
//void CSceneEditor::TileTypeKey(float DeltaTime)
//{
//    mTileMapObj->AddTileType();
//}

void CSceneEditor::TileSelect(int index)
{
    mTileMapObj->TileSelect(index);
}

void CSceneEditor::Background_Prev(float DeltaTime)
{
    mTileMapObj->SetBackTexture("Lobby_BackGroundMap");
}

void CSceneEditor::Background_Next(float DeltaTime)
{
    mTileMapObj->SetBackTexture("Field_BackGroundMap");

}













void CSceneEditor::SaveKey(float DeltaTime)
{
    OPENFILENAME    ofn = {};

    // 선택한 경로를 저장하기 위한 배열
    TCHAR   FullPath[MAX_PATH] = {};
    TCHAR   Filter[] = TEXT("모든파일\0*.*\0Map 파일\0*.tlm\0");
    
    TCHAR	DefaultPath[MAX_PATH] = {};

    lstrcpy(DefaultPath, gRootPath);
    lstrcat(DefaultPath, TEXT("Asset\\Data\\"));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CGameManager::GetInst()->GetWindowHandle();
    ofn.lpstrFilter = Filter;
    ofn.lpstrDefExt = TEXT("tlm");
    ofn.lpstrInitialDir = DefaultPath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = FullPath;

    ShowCursor(TRUE);

    if (GetSaveFileName(&ofn) != 0)
    {
        mTileMapObj->Save(FullPath);
    }

    ShowCursor(FALSE);
}

void CSceneEditor::LoadKey(float DeltaTime)
{
    OPENFILENAME    ofn = {};

    // 선택한 경로를 저장하기 위한 배열
    TCHAR   FullPath[MAX_PATH] = {};
    TCHAR   Filter[] = TEXT("모든파일\0*.*\0Map 파일\0*.tlm\0");

    TCHAR	DefaultPath[MAX_PATH] = {};

    lstrcpy(DefaultPath, gRootPath);
    lstrcat(DefaultPath, TEXT("Asset\\Data\\"));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CGameManager::GetInst()->GetWindowHandle();
    ofn.lpstrFilter = Filter;
    ofn.lpstrDefExt = TEXT("tlm");
    ofn.lpstrInitialDir = DefaultPath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = FullPath;

    ShowCursor(TRUE);

    if (GetOpenFileName(&ofn) != 0)
    {
        mTileMapObj->Load(FullPath);
    }

    ShowCursor(FALSE);
}

void CSceneEditor::Exit(float DeltaTime)
{
    CSceneManager::GetInst()->CreateLoadScene<CSceneStart>();
}
