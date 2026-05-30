#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

struct FTransformCBufferInfo
{
    FMatrix matWorld;
    FMatrix matView;
    FMatrix matProj;
    FMatrix matWV;
    FMatrix matWVP;
    FVector3D   Pivot;
    float       Empty;
};

struct FMaterialCBufferInfo
{
    FVector4D BaseColor;
    float Opacity;
    int TextureWidth;
    int TextureHeight;
    float Empty;
};

struct FColliderCBufferInfo
{
    FVector4D   Color;
};

struct FSpriteCBufferInfo
{
    FVector4D   Tint;       // 16
    float       Flicker;    // 4
    FVector3D   Empty;      // 12
};

struct FAnimation2DCBufferInfo
{
    FVector2D   LTUV;
    FVector2D   RBUV;
    int         AnimEnable;
    int         AnimReverseX;
    FVector2D   Empty;
};

struct FUICBufferInfo
{
    FVector4D   BrushTint;                  // 16바이트
    FVector4D   Color = FVector4D::White;   // 16바이트
    FVector2D   LTUV;                       // 8바이트
    FVector2D   RBUV;                       // 8바이트
    int         BrushAnimEnable;            // 4바이트
    int         BrushTextureEnable;         // 4바이트
    int         GrayScaleEnable;            // 4바이트
    float       BrushEmpty;                 // 4바이트

};

struct FTileMapCBufferInfo
{
    FVector2D   LTUV;
    FVector2D   RBUV;
};