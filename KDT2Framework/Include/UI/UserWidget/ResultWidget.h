#pragma once

#include "WindowWidget.h"

class CResultWidget :
    public CWindowWidget
{

	friend class CSceneUIManager;

protected:
	CResultWidget();
	virtual ~CResultWidget();


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();

private:


};

