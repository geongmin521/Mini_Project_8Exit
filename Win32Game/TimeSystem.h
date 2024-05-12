#pragma once
#include <Windows.h>

#define timeManager TimeManager::GetInstance()

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	static TimeManager* GetInstance();
	static void DestroyInstance();

	void InitTime();
	void UpdateTime();
	const float GetFrameRate();
	const float GetDeltaTime();

private:
	LARGE_INTEGER _CurTime;
	LARGE_INTEGER _PrevTime;
	LARGE_INTEGER _Frequency;

	float _DeltaTime;

	static TimeManager* Instance;
};