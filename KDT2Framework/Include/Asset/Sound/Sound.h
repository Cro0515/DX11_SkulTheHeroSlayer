#pragma once

#include "../Asset.h"
#include "fmod.hpp"

class CSound :
    public CAsset
{
    friend class CSoundManager;

protected:
    CSound();
    virtual ~CSound();

protected:
    FMOD::System* mSystem = nullptr;        // FMOD 시스템 객체
    FMOD::ChannelGroup* mGroup = nullptr;   // 채널 그룹
    FMOD::Channel* mChannel = nullptr;      // 채널 - 사운드 재생 인스턴스
    FMOD::Sound* mSound = nullptr;          // 사운드 에셋
    bool        mLoop = false;              // 반복재생 여부
    int         mPlayCount = 0;             // 현재 재생되고 있는 사운드의 수

public:
    bool LoadSound(FMOD::System* System, FMOD::ChannelGroup* Group,
        bool Loop, const char* FileName);
    bool LoadSoundFullPath(FMOD::System* System, FMOD::ChannelGroup* Group,
        bool Loop, const char* FullPath);
    void Play();
    void Stop();
    void Pause();
    void Resume();

public:
    // 사운드 재생이 종료될 경우 호출될 콜백함수.
    static FMOD_RESULT SoundEnd(FMOD_CHANNELCONTROL* ChannelControl,
        FMOD_CHANNELCONTROL_TYPE Type,
        FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
        void* commanddata1, void* commanddata2);
};

