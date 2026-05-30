#pragma once

#include "Font.h"
#include "FontCollection.h"

class CFontManager
{
	friend class CAssetManager;

private:
	CFontManager();
	~CFontManager();

private:
	IDWriteFactory5* mWriteFactory = nullptr;												// 텍스트 리소스 팩토리
	std::unordered_map<std::string, CSharedPtr<CFont>>	mFontMap;							// 폰트들을 가지고 있을 unordered_map
	std::unordered_map<std::string, CSharedPtr<CFontCollection>>	mCollectionMap;			// 폰트 컬렉션들을 가지고 있을 unordered_map
	std::unordered_map<unsigned int, ID2D1SolidColorBrush*>	mFontColorMap;					// 폰트 색상을 가지고 있을 unordered_map

public:
	bool Init();

public:
	bool LoadFont(const std::string& Name, const TCHAR* FontName,
		int Weight, float FontSize, const TCHAR* LocalName,
		int Stretch = DWRITE_FONT_STRETCH_NORMAL);
	bool LoadFontCollection(const std::string& Name,
		const TCHAR* FileName);
	const TCHAR* GetFontFaceName(const std::string& CollectionName);
	bool CreateFontColor(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a);
	bool CreateFontColor(const FVector4D& Color);

	CFont* FindFont(const std::string& Name);
	CFontCollection* FindFontCollection(const std::string& Name);
	ID2D1SolidColorBrush* FindFontColor(unsigned char r, unsigned char g,
		unsigned char b, unsigned char a);
	ID2D1SolidColorBrush* FindFontColor(const FVector4D& Color);
};

