#pragma once
#include "UserWidget.h"
#include "../Common/Image.h"
#include "../Common/TextBlock.h"


class CInfoDialogue :
    public CUserWidget
{
	friend class CSceneUIManager;

protected:
	CInfoDialogue();
	virtual ~CInfoDialogue();

protected:
	CSharedPtr<CImage>		mBackground;
	CSharedPtr<CTextBlock>	mInfoText;
	CSharedPtr<CImage>		mIcon;

public:
	virtual bool Init();
	virtual void Render();
	virtual void Render(const FVector3D& Pos);



};

