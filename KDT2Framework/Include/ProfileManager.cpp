#include "ProfileManager.h"

DEFINITION_SINGLE(CProfileManager)

CProfileManager::CProfileManager()
{
}

CProfileManager::~CProfileManager()
{
	auto	iter = mProfileMap.begin();
	auto	iterEnd = mProfileMap.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CProfileManager::Init()
{
	CreateProfile("Default", ECollisionChannel::Default, true, ECollisionInteraction::Collision);

	CreateProfile("Player", ECollisionChannel::Player, true, ECollisionInteraction::Collision);

	CreateProfile("Monster", ECollisionChannel::Monster, true, ECollisionInteraction::Collision);
	
	CreateProfile("SkulHead", ECollisionChannel::SkulHead, true, ECollisionInteraction::Collision);



	CreateProfile("PlayerAttack", ECollisionChannel::PlayerAttack, true, ECollisionInteraction::Ignore);

	CreateProfile("MonsterAttack", ECollisionChannel::MonsterAttack, true, ECollisionInteraction::Ignore);

	CreateProfile("MonsterDetect", ECollisionChannel::MonsterDetect, true, ECollisionInteraction::Ignore);

	CreateProfile("Portal", ECollisionChannel::Portal, true, ECollisionInteraction::Ignore);



	// 플레이어 인터렉션 (기본 충돌)
	SetInteraction("Player", ECollisionChannel::Player,
		ECollisionInteraction::Ignore);
	SetInteraction("Player", ECollisionChannel::PlayerAttack,
		ECollisionInteraction::Ignore);
	

	// 몬스터 인터렉션 (기본 충돌)
	SetInteraction("Monster", ECollisionChannel::Monster,
		ECollisionInteraction::Ignore);
	SetInteraction("Monster", ECollisionChannel::MonsterAttack,
		ECollisionInteraction::Ignore);


	// 스컬 헤드 (기본 충돌)
	SetInteraction("SkulHead", ECollisionChannel::PlayerAttack,
		ECollisionInteraction::Ignore);
	SetInteraction("SkulHead", ECollisionChannel::MonsterAttack,
		ECollisionInteraction::Ignore);
	SetInteraction("SkulHead", ECollisionChannel::MonsterDetect,
		ECollisionInteraction::Ignore);


	// 플레이어 어택 인터렉션 (기본 무시)
	SetInteraction("PlayerAttack", ECollisionChannel::Default,
		ECollisionInteraction::Collision);
	SetInteraction("PlayerAttack", ECollisionChannel::Monster,
		ECollisionInteraction::Collision);


	// 몬스터 어택 인터렉션 (기본 무시)
	SetInteraction("MonsterAttack", ECollisionChannel::Default,
		ECollisionInteraction::Collision);
	SetInteraction("MonsterAttack", ECollisionChannel::Player,
		ECollisionInteraction::Collision);


	// 몬스터 감지 인터렉션 (기본 무시)
	SetInteraction("MonsterDetect", ECollisionChannel::Player,
		ECollisionInteraction::Collision);

	// 몬스터 감지 인터렉션 (기본 무시)
	SetInteraction("Portal", ECollisionChannel::Player,
		ECollisionInteraction::Collision);

	return true;
}

bool CProfileManager::CreateProfile(const std::string& Name,
	ECollisionChannel::Type Channel,
	bool Enable, ECollisionInteraction::Type Interaction)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	Profile = new FCollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;

	for (int i = 0; i < ECollisionChannel::End; ++i)
	{
		Profile->Interaction[i] = Interaction;
	}

	mProfileMap.insert(std::make_pair(Name, Profile));

	return true;
}

bool CProfileManager::SetInteraction(const std::string& Name,
	ECollisionChannel::Type Channel,
	ECollisionInteraction::Type Interaction)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->Interaction[Channel] = Interaction;

	return true;
}

bool CProfileManager::SetEnable(const std::string& Name,
	bool Enable)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->Enable = Enable;

	return true;
}

FCollisionProfile* CProfileManager::FindProfile(
	const std::string& Name)
{
	auto	iter = mProfileMap.find(Name);

	if (iter == mProfileMap.end())
		return nullptr;

	return iter->second;
}
