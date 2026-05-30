#pragma once

#include "../GameInfo.h"
#include "../Share/Log.h"

class CObject	abstract
{
public:
	CObject();
	virtual ~CObject();

protected:
	int		mRefCount = 0;		// 생명주기 관리를 위한 래퍼런스 카운트
	bool	mActive = true;		// 생명 상태
	bool	mEnable = true;		// 활성화 상태

public:
	bool IsActive()	const
	{
		return mActive;
	}

	bool IsEnable()	const
	{
		return mEnable;
	}

	int GetRefCount()	const
	{
		return mRefCount;
	}

public:
	virtual void AddRef();
	virtual bool Release();
	virtual void Destroy();
	virtual void SetEnable(bool Enable)
	{
		mEnable = Enable;
	}
};

