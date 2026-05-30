#pragma once

#include "../GameInfo.h"

class CNavAgent
{
	friend class CMovementComponent;

private:
	CNavAgent();
	~CNavAgent();

public:
	bool Init();
};

