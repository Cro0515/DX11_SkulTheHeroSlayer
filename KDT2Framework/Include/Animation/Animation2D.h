#pragma once

#include "../GameInfo.h"
#include "Animation2DSequence.h"
#include "../Shader/Animation2DCBuffer.h"

class CAnimation2D
{
	friend class CSpriteComponent;

private:
	static CAnimation2DCBuffer* mAnimCBuffer;

public:
	static void CreateCBuffer();
	static void DestroyCBuffer();
	static void DisableAnimation();

private:
	CAnimation2D();
	CAnimation2D(const CAnimation2D& Anim);
	virtual ~CAnimation2D();

private:
	class CScene* mScene = nullptr;							// 소유한 씬
	class CSpriteComponent* mOwner = nullptr;				// 소유한 스프라이트 컴포넌트
	CAnimation2DSequence* mCurrentSequence = nullptr;		// 현재 출력중인 애니메이션 시퀀스(모션)
	std::unordered_map<std::string, CAnimation2DSequence*>	mSequenceMap;	// 애니메이션 시퀀스들을 담아 둘 unoredered_map
	bool				mReverse = false;
	bool				mPause = false;

public:

public:
	bool Init();
	void Update(float DeltaTime);
	bool AddSequence(const std::string& Name,
		float PlayTime = 1.f, float PlayRate = 1.f,
		bool Loop = false, bool Reverse = false);
	bool AddSequence(class CAnimation2DData* Asset,
		float PlayTime = 1.f, float PlayRate = 1.f,
		bool Loop = false, bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime);
	void SetPlayRate(const std::string& Name, float PlayRate);
	void SetLoop(const std::string& Name, bool Loop);
	void SetReverse(const std::string& Name, bool Reverse);
	void ChangeAnimation(const std::string& Name);
	CAnimation2D* Clone();
	void SetShader();
	void SetAnimationReverseX(bool Reverse);

	void SetPause(bool pause)
	{ 
		mPause = pause; 
	}


public:

	bool GetReverse() const
	{
		return mReverse;
	}

	bool GetPause() const 
	{
		return mPause;
	}

	CAnimation2DSequence* GetSequence() const
	{
		return mCurrentSequence;
	}

	CSpriteComponent* GetOwner()
	{
		return mOwner;
	}
	
	float GetPlayRate(const std::string& Name)
	{
		CAnimation2DSequence* Sequence = FindSequence(Name);

		return Sequence->GetPlayRate();
	}

	void ResetFrame()
	{
		mCurrentSequence->mFrame = 0;
		mCurrentSequence->mTime = 0.f;
	}
private:
	CAnimation2DSequence* FindSequence(
		const std::string& Name);

public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		CAnimation2DSequence* Sequence = FindSequence(Name);

		if (!Sequence)
			return;

		Sequence->SetEndFunction<T>(Obj, Func);
	}

	template <typename T>
	void SetBeginFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		CAnimation2DSequence* Sequence = FindSequence(Name);

		if (!Sequence)
			return;

		Sequence->SetBeginFunction<T>(Obj, Func);
	}


	template <typename T>
	void AddNotify(const std::string& Name,
		int Frame, T* Obj, void(T::* Func)())
	{
		CAnimation2DSequence* Sequence = FindSequence(Name);

		if (!Sequence)
			return;

		Sequence->AddNotify<T>(Name, Frame, Obj, Func);
	}
};

