#pragma once

#include "Scene.h"

class CSceneEditor :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneEditor();
	virtual ~CSceneEditor();

private:
	EEditorMode	mEditorMode = EEditorMode::None;

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();

private:
	//void EditorMode(float DeltaTime);
	//void TileTypeKey(float DeltaTime);
	//void TileFrameKey(float DeltaTime);
	void TileSelect(int type);

	void Background_Prev(float DeltaTime);
	void Background_Next(float DeltaTime);

	void SaveKey(float DeltaTime);
	void LoadKey(float DeltaTime);

	void Exit(float DeltaTime);
};

