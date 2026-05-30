#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::AddRef()
{
	++mRefCount;
}

bool CObject::Release()
{
	--mRefCount;

	if (mRefCount == 0)
	{
		delete this;
		return true;
	}

	return false;
}

void CObject::Destroy()
{
	mActive = false;
}
