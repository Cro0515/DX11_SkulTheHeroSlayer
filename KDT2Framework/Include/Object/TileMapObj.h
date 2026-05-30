#pragma once

#include "SceneObject.h"
#include "../Component/TileMapComponent.h"
#include "../Component/TileMapRendererComponent.h"

class CTileMapObj :
    public CSceneObject
{
    friend class CScene;

protected:
    CTileMapObj();
    CTileMapObj(const CTileMapObj& Obj);
    CTileMapObj(CTileMapObj&& Obj);
    virtual ~CTileMapObj();

private:
    CSharedPtr<CTileMapRendererComponent>   mTileMapRenderer;
    CSharedPtr<CTileMapComponent>   mTileMap;
    ETileType       mEditTileType = ETileType::Normal;
    ETileType       mOnMousePrevTileType = ETileType::None;
    int             mOnMousePrevIndex = -1;
    EEditorMode     mEditorMode = EEditorMode::None;
    float MouseX = 0.f;
    float MouseY = 0.f;

    int         mEditTileFrame = 0;

    float mMult = 3.f;



public:
    int GetTileIndex(FVector2D Pos)
    {
        if (mTileMap == nullptr)
            return -1;

        return mTileMap->GetTileIndex(Pos);
    }

    bool IsValidTile(int index)
    {
        const CTile* foundData = mTileMap->GetTile(index);
        if (foundData == nullptr)
            return false;

        if (foundData->GetTextureFrame() == -1)
            return false;

        return true;
    }

    const int GetTileCountY() const
    {
        return mTileMap->GetTileCountY();
    }

    const int GetTileCountX() const
    {
        return mTileMap->GetTileCountX();
    }

    ETileType GetTileType(int index)
    {
        return mTileMap->GetTileType(index);
    }

    const CTile* GetTile(int index)
    {
        return mTileMap->GetTile(index);
    }

    const CTile* GetTile(float x, float y)
    {
        return mTileMap->GetTile(x, y);
    }


public:
    void SetEditorMode(EEditorMode Mode)
    {
        mEditorMode = Mode;
    }

    void AddTileType();
    void TileSelect(int index);

    void SetBackTexture(const std::string& Name)
    {
        mTileMapRenderer->SetBackTexture(Name);
    }

public:
    CTileMapComponent* GetTileMapComponent() const
    {
        return mTileMap;
    }

    FVector2D GetMapSize() const
    {
        FVector2D TileSize = mTileMap->GetTileSize();

        FVector2D MapSize;
        MapSize.x = TileSize.x * mTileMap->GetTileCountX();
        MapSize.y = TileSize.y * mTileMap->GetTileCountY();


        return MapSize;
    }


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void Save(const TCHAR* FullPath);
    void Load(const TCHAR* FullPath);

private:
    void PrintMousePos(float DeltaTime);
};

