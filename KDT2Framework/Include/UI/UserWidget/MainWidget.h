#pragma once

#include "UserWidget.h"

class CMainWidget :
    public CUserWidget
{
	friend class CSceneUIManager;

protected:
	CMainWidget();
	virtual ~CMainWidget();


protected:
	CSharedPtr<class CImage>			mPlayerInfo;
	CSharedPtr<class CProgressBar>		mHPBar;
	CSharedPtr<class CProgressBar>		mSkill_A_ProgressBar;
	CSharedPtr<class CProgressBar>		mSkill_S_ProgressBar;
	CSharedPtr<class CTextBlock>		mHPText;
	CSharedPtr<class CImage>			mBloodScreen;
	CSharedPtr<class CResultWidget>		mResultWidget;
	CSharedPtr<class CImage>			mEnemyCntImage;
	CSharedPtr<class CTextBlock>		mEnemyCntText;

	CSharedPtr<class CImage>			mSkill_A_Effect;
	CSharedPtr<class CImage>			mSkill_S_Effect;



	float mBloodScreenOpacityAcc = 0.f;
	float mBloodScreenOpacity = 0.7f;
	float mBloodScreenScale = 1.f;
	bool mSkillA_Once = false;
	bool mSkillS_Once = false;
	bool mReturnToLobby = true;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();

public:
	void HPUpdate(int _HP, int _HPMax);
	void SkillA_Update(float _CurCoolTime, float _CoolTime);
	void SkillA_On();
	void SkillA_Off();


	void SkillS_Update(float _CurCoolTime, float _CoolTime);
	void SkillS_On();
	void SkillS_Off();

	void BloodScreenOn();

public:
	bool GetResultEnable();


public:

	void SetResultEnable(bool flag);
	void SetEnemyCount(int count);

};

