#pragma once

#include "Scene.h"

class CSceneMain :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneMain();
	virtual ~CSceneMain();

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();

private:
	void Exit(float DeltaTime);
};

