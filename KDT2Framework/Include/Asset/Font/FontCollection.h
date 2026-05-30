#pragma once

#include "../Asset.h"

class CFontCollection :
    public CAsset
{
    friend class CFontManager;

private:
    CFontCollection();
    ~CFontCollection();

private:
    IDWriteFontCollection1* mCollection = nullptr;      // 폰트 스타일들을 모아둘 컬렉션
    TCHAR                   mFontFaceName[128] = {};    // 폰트 이름

public:
    const TCHAR* GetFontFaceName()  const
    {
        return mFontFaceName;
    }

public:
    bool LoadCollection(IDWriteFactory5* Factory, const TCHAR* FileName);
};

