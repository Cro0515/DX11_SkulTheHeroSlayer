#include "Animation2DManager.h"
#include "Animation2DData.h"
#include "../../Animation/Animation2D.h"

CAnimation2DManager::CAnimation2DManager()
{
}

CAnimation2DManager::~CAnimation2DManager()
{
    CAnimation2D::DestroyCBuffer();
}

bool CAnimation2DManager::Init()
{
    CAnimation2D::CreateCBuffer();


    // ==== 경로, for문의 프레임 count, 좌표 계산 추후 수정하기
    
#pragma region Player
    

    CreateAnimation("PlayerIdle");
    SetAnimationTextureType("PlayerIdle", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerIdle", "PlayerSprite",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_Idle_Sheet.png"));
    for (int i = 0; i < 4; ++i)
    {
        AddFrame("PlayerIdle", 44.f * i, 0, 
            44.f, 37.f);
    }
    


    CreateAnimation("PlayerWalk");
    SetAnimationTextureType("PlayerWalk", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerWalk", "PlayerWalk",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_Walk_Sheet.png"));
    for (int i = 0; i < 8; ++i)
    {
        AddFrame("PlayerWalk", 47.f * i, 0,
            47.f, 33.f);
    }



    CreateAnimation("PlayerAttack_A");
    SetAnimationTextureType("PlayerAttack_A", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerAttack_A", "PlayerAttack_A",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_AttackA_Sheet.png"));
    for (int i = 0; i < 5; ++i)
    {
        AddFrame("PlayerAttack_A", 63.f * i, 0,
            63.f, 57.f);
    }



    CreateAnimation("PlayerAttack_B");
    SetAnimationTextureType("PlayerAttack_B", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerAttack_B", "PlayerAttack_B",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_AttackB_Sheet.png"));
    for (int i = 0; i < 4; ++i)
    {
        AddFrame("PlayerAttack_B", 60.f * i, 0,
            60.f, 58.f);
    }



    CreateAnimation("PlayerDash");
    SetAnimationTextureType("PlayerDash", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerDash", "PlayerDash",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_Dash_Sheet.png"));
    for (int i = 0; i < 4; ++i)
    {
        AddFrame("PlayerDash", 42.f * i, 0,
            42.f, 28.f);
    }


    CreateAnimation("PlayerSkillA");
    SetAnimationTextureType("PlayerSkillA", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerSkillA", "PlayerSkillA",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_HeadThrow_Sheet.png"));
    for (int i = 0; i < 4; ++i)
    {
        AddFrame("PlayerSkillA", 63.f * i, 0,
            63.f, 37.f);
    }


    CreateAnimation("PlayerJump");
    SetAnimationTextureType("PlayerJump", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerJump", "PlayerJump",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_Jump_Sheet.png"));
    for (int i = 0; i < 2; ++i)
    {
        AddFrame("PlayerJump", 22.f * i, 0,
            22.f, 36.f);
    }



    CreateAnimation("PlayerFall");
    SetAnimationTextureType("PlayerFall", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerFall", "PlayerFall",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_Fall_Sheet.png"));
    for (int i = 0; i < 2; ++i)
    {
        AddFrame("PlayerFall", 34.f * i, 0,
            34.f, 36.f);
    }



    CreateAnimation("PlayerFallRepeat");
    SetAnimationTextureType("PlayerFallRepeat", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerFallRepeat", "PlayerFallRepeat",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_FallRepeat_Sheet.png"));
    for (int i = 0; i < 3; ++i)
    {
        AddFrame("PlayerFallRepeat", 40.f * i, 0,
            40.f, 40.f);
    }


    CreateAnimation("PlayerJumpAttack");
    SetAnimationTextureType("PlayerJumpAttack", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerJumpAttack", "PlayerJumpAttack",
        TEXT("Texture\\Character\\LittleBone\\Normal\\LittleBone_JumpAttack_Sheet.png"));
    for (int i = 0; i < 4; ++i)
    {
        AddFrame("PlayerJumpAttack", 55.f * i, 0,
            55.f, 57.f);
    }


    CreateAnimation("PlayerDeath");
    SetAnimationTextureType("PlayerDeath", EAnimationTextureType::SpriteSheet);
    SetTexture("PlayerDeath", "PlayerDeath",
        TEXT("Texture\\Character\\LittleBone\\LittleBone_Death_Sheet.png"));
    for (int i = 0; i < 6; ++i)
    {
        AddFrame("PlayerDeath", 39.f * i, 0,
            39.f, 25.f);
    }





#pragma endregion Player


#pragma region CalleonSoldier

    CreateAnimation("CalleonSoldier_Idle");
    SetAnimationTextureType("CalleonSoldier_Idle", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Idle", "CalleonSoldier_Idle",
        TEXT("Texture\\Monster\\CalleonSoldier\\Idle_Sheet.png"));
    for (int i = 0; i < 5; ++i)
    {
        AddFrame("CalleonSoldier_Idle", 80.f * i, 0,
            80.f, 80.f);
    }


    CreateAnimation("CalleonSoldier_Walk");
    SetAnimationTextureType("CalleonSoldier_Walk", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Walk", "CalleonSoldier_Walk",
        TEXT("Texture\\Monster\\CalleonSoldier\\Walk_Sheet.png"));
    for (int i = 0; i < 7; ++i)
    {
        AddFrame("CalleonSoldier_Walk", 80.f * i, 0,
            80.f, 80.f);
    }


    CreateAnimation("CalleonSoldier_Attack");
    SetAnimationTextureType("CalleonSoldier_Attack", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Attack", "CalleonSoldier_Attack",
        TEXT("Texture\\Monster\\CalleonSoldier\\Attack_Sheet.png"));
    for (int i = 0; i < 5; ++i)
    {
        AddFrame("CalleonSoldier_Attack", 80.f * i, 0,
            80.f, 80.f);
    }


    CreateAnimation("CalleonSoldier_Hit_A");
    SetAnimationTextureType("CalleonSoldier_Hit_A", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Hit_A", "CalleonSoldier_Hit_A", 
        TEXT("Texture\\Monster\\CalleonSoldier\\Hit_A.png"));
    AddFrame("CalleonSoldier_Hit_A", 0.f, 0.f, 80.f, 80.f);


    CreateAnimation("CalleonSoldier_Hit_B");
    SetAnimationTextureType("CalleonSoldier_Hit_B", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Hit_B", "CalleonSoldier_Hit_B",
        TEXT("Texture\\Monster\\CalleonSoldier\\Hit_B.png"));
    AddFrame("CalleonSoldier_Hit_B", 0.f, 0.f, 80.f, 80.f);


#pragma endregion CalleonSoldier


#pragma region CalleonArcher


    CreateAnimation("CalleonArcher_Idle");
    SetAnimationTextureType("CalleonArcher_Idle", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonArcher_Idle", "CalleonArcher_Idle",
        TEXT("Texture\\Monster\\CalleonArcher\\Idle_Sheet.png"));
    for (int i = 0; i < 5; ++i)
    {
        AddFrame("CalleonArcher_Idle", 80.f * i, 0,
            80.f, 80.f);
    }
    

    CreateAnimation("CalleonArcher_Walk");
    SetAnimationTextureType("CalleonArcher_Walk", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonArcher_Walk", "CalleonArcher_Walk",
        TEXT("Texture\\Monster\\CalleonArcher\\Walk_Sheet.png"));
    for (int i = 0; i < 6; ++i)
    {
        AddFrame("CalleonArcher_Walk", 80.f * i, 0,
            80.f, 80.f);
    }



    CreateAnimation("CalleonArcher_Attack");
    SetAnimationTextureType("CalleonArcher_Attack", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonArcher_Attack", "CalleonArcher_Attack",
        TEXT("Texture\\Monster\\CalleonArcher\\Attack_Sheet.png"));
    for (int i = 0; i < 4; ++i)
    {
        AddFrame("CalleonArcher_Attack", 80.f * i, 0, 80.f, 80.f);
    }
    AddFrame("CalleonArcher_Attack", 80.f * 3, 0, 80.f, 80.f);


    CreateAnimation("CalleonArcher_Hit_A");
    SetAnimationTextureType("CalleonArcher_Hit_A", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonArcher_Hit_A", "CalleonArcher_Hit_A", TEXT("Texture\\Monster\\CalleonArcher\\Hit_A.png"));
    AddFrame("CalleonArcher_Hit_A", 0.f, 0.f, 80.f, 80.f);


    CreateAnimation("CalleonArcher_Hit_B");
    SetAnimationTextureType("CalleonArcher_Hit_B", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonArcher_Hit_B", "CalleonArcher_Hit_B", TEXT("Texture\\Monster\\CalleonArcher\\Hit_B.png"));
    AddFrame("CalleonArcher_Hit_B", 0.f, 0.f, 80.f, 80.f);



    CreateAnimation("CalleonSoldier_Hit_A");
    SetAnimationTextureType("CalleonSoldier_Hit_A", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Hit_A", "CalleonSoldier_Hit_A", TEXT("Texture\\Monster\\CalleonSoldier\\Hit_A.png"));
    AddFrame("CalleonSoldier_Hit_A", 0.f, 0.f, 80.f, 80.f);


    CreateAnimation("CalleonSoldier_Hit_B");
    SetAnimationTextureType("CalleonSoldier_Hit_B", EAnimationTextureType::SpriteSheet);
    SetTexture("CalleonSoldier_Hit_B", "CalleonSoldier_Hit_B", TEXT("Texture\\Monster\\CalleonSoldier\\Hit_B.png"));
    AddFrame("CalleonSoldier_Hit_B", 0.f, 0.f, 80.f, 80.f);

#pragma endregion CalleonArcher


#pragma region Effect

    CreateAnimation("LittleBoneHitEffect");
    SetAnimationTextureType("LittleBoneHitEffect", EAnimationTextureType::SpriteSheet);
    SetTexture("LittleBoneHitEffect", "LittleBoneHitEffect",
        TEXT("Texture\\Effect\\LittleBone_HIt\\Hit_Skul_Sheet.png"));
    for (int i = 0; i < 10; ++i)
    {
        AddFrame("LittleBoneHitEffect", 107.f * i, 0, 
                                        107.f, 119.f);
    }


    CreateAnimation("EnemyDeadEffect");
    SetAnimationTextureType("EnemyDeadEffect", EAnimationTextureType::SpriteSheet);
    SetTexture("EnemyDeadEffect", "EnemyDeadEffect",
        TEXT("Texture\\Effect\\Enemy_Dead\\Enemy_Dead_Sheet.png"));
    for (int i = 0; i < 5; ++i)
    {
        AddFrame("EnemyDeadEffect", 150.f * i, 0, 150.f, 150.f);
    }


   
    CreateAnimation("SoldierHitEffect");
    SetAnimationTextureType("SoldierHitEffect", EAnimationTextureType::SpriteSheet);
    SetTexture("SoldierHitEffect", "SoldierHitEffect",
        TEXT("Texture\\Effect\\Soldir\\Hit_Normal_Sheet.png"));
    for (int i = 0; i < 12; ++i)
    {
        AddFrame("SoldierHitEffect", 100.f * i, 0, 100.f, 100.f);
    }


    CreateAnimation("ArcherHitEffect");
    SetAnimationTextureType("ArcherHitEffect", EAnimationTextureType::SpriteSheet);
    SetTexture("ArcherHitEffect", "ArcherHitEffect",
        TEXT("Texture\\Effect\\Critical\\Hit_SlashCritical_Sheet.png"));
    for (int i = 0; i < 7; ++i)
    {
        AddFrame("ArcherHitEffect", 150.f * i, 0, 150.f, 100.f);
    }


    /*CreateAnimation("PortalOpenEffect");
    SetAnimationTextureType("PortalOpenEffect", EAnimationTextureType::SpriteSheet);
    SetTexture("PortalOpenEffect", "PortalOpenEffect",
        TEXT("Texture\\Effect\\Reward\\MapReward_Spawn_Sheet.png"));
    for (int i = 0; i < 7; ++i)
    {
        AddFrame("PortalOpenEffect", 150.f * i, 0, 150.f, 100.f);
    }*/


    CreateAnimation("DashSmokeEffefct");
    SetAnimationTextureType("DashSmokeEffefct", EAnimationTextureType::SpriteSheet);
    SetTexture("DashSmokeEffefct", "DashSmokeEffefct",
        TEXT("Texture\\Effect\\DashSmoke_1\\Dash_Smok_Sheet.png"));
    for (int i = 0; i < 15; ++i)
    {
        AddFrame("DashSmokeEffefct", 50.f * i, 0, 50.f, 50.f);
    }



    CreateAnimation("DoubleJumpEffect");
    SetAnimationTextureType("DoubleJumpEffect", EAnimationTextureType::SpriteSheet);
    SetTexture("DoubleJumpEffect", "DoubleJumpEffect",
        TEXT("Texture\\Effect\\DoubleJumpSmoke\\DoubleJump_Smoke_Sheet.png"));
    for (int i = 0; i < 10; ++i)
    {
        AddFrame("DoubleJumpEffect", 110.f * i, 0, 110.f, 50.f);
    }

#pragma endregion Effect






    return true;
}

bool CAnimation2DManager::CreateAnimation(
    const std::string& Name)
{
    if (FindAnimation(Name))
        return false;

    CAnimation2DData* Animation = new CAnimation2DData;

    Animation->SetName(Name);

    mAnimationMap.insert(std::make_pair(Name, Animation));

    return true;
}

bool CAnimation2DManager::SetAnimationTextureType(
    const std::string& Name, EAnimationTextureType Type)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetAnimationTextureType(Type);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name, 
    CTexture* Texture)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(Texture);

    return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, 
    const std::string& TextureName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name, 
    const std::string& TextureName, const TCHAR* FileName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName, FileName);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name,
    const std::string& TextureName,
    std::vector<const TCHAR*> FileName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName, FileName);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name, 
    const std::string& TextureName, const TCHAR* FileName,
    const TCHAR* Ext, int Count)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName, FileName,
        Ext, Count);

    return true;
}

bool CAnimation2DManager::SetTextureFullPath(
    const std::string& Name, 
    const std::string& TextureName, const TCHAR* FullPath)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTextureFullPath(TextureName, FullPath);

    return true;
}

bool CAnimation2DManager::SetTextureFullPath(
    const std::string& Name, 
    const std::string& TextureName,
    std::vector<const TCHAR*> FullPath)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTextureFullPath(TextureName, FullPath);

    return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name,
    const FVector2D& Start, const FVector2D& Size)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrame(Start, Size);

    return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name,
    float StartX, float StartY, float SizeX, float SizeY)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrame(StartX, StartY, SizeX, SizeY);

    return true;
}

bool CAnimation2DManager::AddFrameCount(
    const std::string& Name, int Count, 
    const FVector2D& Start, const FVector2D& Size)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrameCount(Count, Start, Size);

    return true;
}

bool CAnimation2DManager::AddFrameCount(
    const std::string& Name, int Count,
    float StartX, float StartY, float SizeX, float SizeY)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrameCount(Count,
        StartX, StartY, SizeX, SizeY);

    return true;
}

CAnimation2DData* CAnimation2DManager::FindAnimation(
    const std::string& Name)
{
    auto    iter = mAnimationMap.find(Name);

    if (iter == mAnimationMap.end())
        return nullptr;

    return iter->second;
}

void CAnimation2DManager::ReleaseAnimation(
    CAsset* Animation)
{
    auto    iter = mAnimationMap.find(Animation->GetName());

    if (iter != mAnimationMap.end())
    {
        // 다른곳에서 가지고 있는게 없기 때문에 제거한다.
        if (iter->second->GetRefCount() == 1)
        {
            mAnimationMap.erase(iter);
        }
    }
}
