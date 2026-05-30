#pragma once

#include "../GameInfo.h"

struct FUIBrush
{
	CSharedPtr<class CTexture>	Texture;
	FVector4D	Tint = FVector4D::White;
	std::vector<FAnimationFrame>	Frames;
	bool	AnimationEnable = false;	
	bool	GrayScale = false;
	int		Frame = 0;					// 현재 프레임
	float	Time = 0.f;					// 현재 플레이 시간
	float	FrameTime = 0.f;
	float	PlayTime = 1.f;
	float	PlayRate = 1.f;
};

