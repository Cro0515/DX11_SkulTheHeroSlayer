#pragma once

#include "../GameInfo.h"

struct FAnimation2DNotify
{
	std::string	Name;					// 노티파이 이름
	int		Frame = 0;					// 노티파이가 호출 될 프레임
	std::function<void()>	Function;	// 호출 될 함수 포인터
};

class CAnimation2DSequence
{
	friend class CAnimation2D;

private:
	CAnimation2DSequence();
	CAnimation2DSequence(const CAnimation2DSequence& Anim);
	~CAnimation2DSequence();

private:
	class CAnimation2D* mOwner = nullptr;			// 소유한 애니메이션 클래스
	CSharedPtr<class CAnimation2DData>	mAsset;		// 애니메이션 에셋 데이터

	int		mFrame = 0;					// 애니메이션의 현재 출력중인 프레임
	float	mTime = 0.f;				// 애니메이션 출력을 위한 누적 시간
	float	mFrameTime = 0.f;			// 프레임 간격 시간
	float	mPlayTime = 1.f;			// 애니메이션 하나를 출력하는 최종 시간
	float	mPlayRate = 1.f;			// 재생속도 배율
	bool	mLoop = false;				// 반복재생 여부
	bool	mReverse = false;			// 역재생 여부
	bool	mEndFunctionEnable = true;	// 모션 재생이 끝날때마다 호출 될 함수포인터 존재 여부
	bool	mBeginFuncEnable = true;

	std::function<void()>	mEndFunction;				// 모션 재생이 끝날때마다 호출 될 함수 포인터
	std::function<void()>	mBeginFunction;

	std::vector<FAnimation2DNotify*>	mNotifyList;	// 노티파이 배열

public:
	CAnimation2DData* GetAnimationAsset()	const
	{
		return mAsset;
	}

	int GetFrame()	const
	{
		return mFrame;
	}

	float GetTime()	const
	{
		return mTime;
	}

	float GetPlayRate() const
	{
		return mPlayRate;
	}

	const std::string& GetName()	const;

public:
	void SetAsset(class CAnimation2DData* Asset);
	void SetPlayTime(float PlayTime);

	void SetPlayRate(float Rate)
	{
		mPlayRate = Rate;
	}

	void SetLoop(bool Loop)
	{
		mLoop = Loop;
	}

	void SetReverse(bool Reverse)
	{
		mReverse = Reverse;
	}

public:
	void Update(float DeltaTime);
	CAnimation2DSequence* Clone();

private:
	void CallNotify();
	
public:
	template <typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		mEndFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void SetBeginFunction(T* Obj, void(T::* Func)())
	{
		mBeginFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void AddNotify(const std::string& Name,
		int Frame, T* Obj, void(T::* Func)())
	{
		FAnimation2DNotify* Notify = new FAnimation2DNotify;

		Notify->Name = Name;
		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		mNotifyList.emplace_back(Notify);
	}
};

