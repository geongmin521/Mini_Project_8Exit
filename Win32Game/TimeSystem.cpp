#include "TimeSystem.h"
#include "globalheader.h"

TimeManager* TimeManager::Instance = nullptr;

TimeManager::TimeManager() : _CurTime{ 0 }, _PrevTime{ 0 }, _Frequency{ 0 } , _DeltaTime(0)
{
}

TimeManager::~TimeManager()
{
}

TimeManager* TimeManager::GetInstance() {
	if (Instance == nullptr) {
		Instance = new TimeManager();
	}
	return Instance;
}

void TimeManager::DestroyInstance() {
	delete Instance;
	Instance = nullptr;
}

void TimeManager::InitTime()
{
	QueryPerformanceFrequency(&_Frequency);
	QueryPerformanceCounter(&_CurTime);
}

void TimeManager::UpdateTime()
{
	_PrevTime = _CurTime;
	QueryPerformanceCounter(&_CurTime);

	_DeltaTime = (float)(_CurTime.QuadPart - _PrevTime.QuadPart) / ((float)(_Frequency.QuadPart));

//#ifdef _DEBUG
//	if (_DeltaTime > (1.f / 60.f)) {
//		_DeltaTime = (1.f / 60.f);
//	}
//#endif
}

const float TimeManager::GetFrameRate()
{
	if (_DeltaTime == 0) return 0;

	return ceil(((1.0f / _DeltaTime)));
}

const float TimeManager::GetDeltaTime()
{
	return _DeltaTime;
}
