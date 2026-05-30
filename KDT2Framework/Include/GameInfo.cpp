
#include "GameInfo.h"

int Clamp(int Value, int Min, int Max)
{
	if (Value < Min)
		Value = Min;

	else if (Value > Max)
		Value = Max;

	return Value;
}

float Clamp(float Value, float Min, float Max)
{
	if (Value < Min)
		Value = Min;

	else if (Value > Max)
		Value = Max;

	return Value;
}

FVector3D Lerp(FVector3D Start, FVector3D End, float Time)
{
	return Start + (End - Start) * Time;
}

float Lerp(float Start, float End, float Time)
{
	return Start + (End - Start) * Time;	
}

int Lerp(int Start, int End, float Time)
{
	return Start + (End - Start) * Time;
}