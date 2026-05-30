#pragma once
#include "Scene.h"

class CSceneStage2 :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneStage2();
	virtual ~CSceneStage2();


protected:
	virtual bool InitAsset();
	virtual bool InitWidget();
	virtual bool InitObject();
	virtual void NextScene();

private:
	void Exit(float DeltaTime);
	void Next(float DeltaTime);

};

