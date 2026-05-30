#pragma once

#include "Scene.h"

class CSceneLobby :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneLobby();
	virtual ~CSceneLobby();


protected:
	virtual bool InitAsset();
	virtual bool InitWidget();
	virtual bool InitObject();
	virtual void NextScene();

private:
	void Exit(float DeltaTime);
	void Next(float DeltaTime);

};

