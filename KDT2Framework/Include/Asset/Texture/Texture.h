#pragma once

#include "../Asset.h"
#include "DirectXTex.h"

struct FTextureInfo
{
    DirectX::ScratchImage* Image = nullptr;         // 이미지
    ID3D11ShaderResourceView* SRV = nullptr;        // 쉐이더 리소스 뷰 - 쉐이더에 리소스를 넘겨주는 역할
    unsigned int    Width = 0;                      // 가로크기
    unsigned int    Height = 0;                     // 세로크기
    TCHAR           FileName[MAX_PATH] = {};        // 파일명

    ~FTextureInfo()
    {
        SAFE_RELEASE(SRV);
        SAFE_DELETE(Image);
    }
};

class CTexture :
    public CAsset
{
    friend class CTextureManager;

protected:
    CTexture();
    virtual ~CTexture();

protected:
    std::vector<FTextureInfo*>  mTextureList;       // 텍스쳐 벡터

public:

    const FVector2D GetTextureSize(int Index = 0)
    {
        FVector2D size = FVector2D(mTextureList[Index]->Width, mTextureList[Index]->Height);
       
        return size;
    }

    const FTextureInfo* GetTexture(int Index = 0)
    {
        return mTextureList[Index];
    }

    int GetTextureCount()   const
    {
        return (int)mTextureList.size();
    }


public:
    bool LoadTexture(const TCHAR* FileName);
    bool LoadTextureFullPath(const TCHAR* FullPath);
    bool LoadTexture(const std::vector<const TCHAR*>& FileName);
    bool LoadTextureFullPath(const std::vector<const TCHAR*>& FullPath);
    bool LoadTexture(const TCHAR* FileName, const TCHAR* Ext,
        int Count);

public:
    void SetShader(int Register, int ShaderBufferType,
        int TextureIndex);
    void ResetShader(int Register, int ShaderBufferType);

protected:
    bool CreateResourceView(int Index = 0);
};

