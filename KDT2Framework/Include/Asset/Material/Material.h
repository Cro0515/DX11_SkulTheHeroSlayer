#pragma once

#include "../Asset.h"

namespace ETextureSamplerType
{
    enum Type : unsigned char
    {
        Point,          // 포인트 필터링
        Linear,         // 선형 필터링
        Anisotropic,    // 비등방성 필터링
        End
    };
}

struct FMaterialTextureInfo
{
    std::string Name;                                   // 이름
    CSharedPtr<class CTexture>  Texture;                // 텍스쳐
    int Register = 0;                                   // 레지스터
    int ShaderBufferType = EShaderBufferType::Pixel;    // 쉐이더 타입
    int TextureIndex = 0;                               // 텍스쳐 인덱스
};

class CMaterial :
    public CAsset
{
    friend class CMaterialManager;

protected:
    CMaterial();
    CMaterial(const CMaterial& Material);
    virtual ~CMaterial();

private:
    static ID3D11SamplerState* mSampler[ETextureSamplerType::End];  // 샘플러

private:
    static void SetSampler(ETextureSamplerType::Type Type);
    static void DestroySampler();

protected:
    std::vector<FMaterialTextureInfo*> mTextureList;        // 텍스쳐 배열
    ID3D11PixelShader* mPS = nullptr;                       // 픽셀 쉐이더 - 지정되지 않았으면 기본 픽셀쉐이더 적용,
                                                            //               같은 머티리얼이여도 픽셀쉐이더를 변경하여 출력을 다르게 사용가능
    FVector4D          mBaseColor = FVector4D::White;       // 색상
    float               mOpacity = 1.f;                     // 투명도 - 1불투명, 0투명
    class CMaterialCBuffer* mCBuffer = nullptr;             // 머티리얼 상수 버퍼
    ETextureSamplerType::Type mSamplerType = ETextureSamplerType::Linear;   // 샘플러 타입

public:
    void AddTexture(class CTexture* Texture,
        int Register,
        int ShaderBufferType = EShaderBufferType::Pixel,
        int TextureIndex = 0);
    void AddTexture(const std::string& Name,
        int Register,
        int ShaderBufferType = EShaderBufferType::Pixel,
        int TextureIndex = 0);
    void AddTexture(const std::string& Name,
        const TCHAR* FileName,
        int Register,
        int ShaderBufferType = EShaderBufferType::Pixel,
        int TextureIndex = 0);

    void SetPixelShader(const std::string& Name);
    void SetPixelShader(const std::string& Name,
        const char* EntryName, const TCHAR* FileName);

    void ClearShader();

    void SetBaseColor(float r, float g, float b, float a);
    void SetBaseColor(const FVector4D& Color);

    void SetOpacity(float Opacity);

    void SetSamplerType(ETextureSamplerType::Type SamplerType);

    void SetMaterial();

    void ResetMaterial();

    CMaterial* Clone();
};

