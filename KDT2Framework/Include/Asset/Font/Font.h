#pragma once

#include "../Asset.h"

class CFont :
    public CAsset
{
    friend class CFontManager;

private:
    CFont();
    ~CFont();

private:
    IDWriteFactory5* mFactory = nullptr;        // 텍스트 관련 리소스를 생성하고 관리하는 팩토리
    IDWriteTextFormat* mFormat = nullptr;       // 폰트 패밀리, 스타일, 굵기, 크기, 정렬 등 텍스트의 서식을 정의

public:
    bool LoadFont(IDWriteFactory5* Factory, const TCHAR* FontName,
        int Weight, float FontSize, const TCHAR* LocalName,
        int Stretch = DWRITE_FONT_STRETCH_NORMAL);
    IDWriteTextLayout* CreateLayout(const TCHAR* Text, int Length,
        float Width, float Height);
};

