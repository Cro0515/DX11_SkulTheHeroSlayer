#pragma once

#include "Sound.h"

class CSoundManager
{
	friend class CAssetManager;

private:
	CSoundManager();
	~CSoundManager();

private:
	FMOD::System* mSystem = nullptr;					// Sound 시스템 객체
	FMOD::ChannelGroup* mMasterGroup = nullptr;			// 마스터 그룹
	std::unordered_map<std::string, FMOD::ChannelGroup*>	mChannelGroupMap;	// 채널그룹을 모아 둘 unordered_map
	std::unordered_map<std::string, CSharedPtr<CSound>>		mSoundMap;			// 사운드 에셋들을 모아 둘 unordered_map

public:
	bool Init();
	void Update();
	bool CreateChannelGroup(const std::string& Name);
	bool LoadSound(const std::string& Name, const std::string& GroupName,
		bool Loop, const char* FileName);
	bool LoadSoundFullPath(const std::string& Name, const std::string& GroupName,
		bool Loop, const char* FullPath);

	void Play(const std::string& Name);
	void Stop(const std::string& Name);
	void Pause(const std::string& Name);
	void Resume(const std::string& Name);
	// Volume : 0 ~ 100
	void SetMasterVolume(int Volume);
	void SetGroupVolume(const std::string& GroupName, int Volume);

private:
	FMOD::ChannelGroup* FindChannelGroup(const std::string& Name);

public:
	CSound* FindSound(const std::string& Name);

	void ReleaseSound(class CAsset* Sound);
};

