#pragma once

#include "Scene.h"

class CSceneStage1 :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneStage1();
	virtual ~CSceneStage1();



protected:
	virtual bool InitAsset();
	virtual bool InitWidget();
	virtual bool InitObject();
	virtual void NextScene();

private:
	void Exit(float DeltaTime);
	void Next(float DeltaTime);


};

