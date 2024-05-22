#pragma once
#include "GameObject.h"

#define camera Camera::GetInstance()
#define FADE_IN		0
#define FADE_OUT	1

class Camera
{
public:
	Camera();
	~Camera();

	static Camera* GetInstance();
	static void DestroyInstance();

	void SetLookPos(Vector3& pos) { _LookPos = pos; }
	void SetTarget(GameObject* target) { _TargetObject = target; }

	void Update();
	void CalDiff();

	void SetEffectEnd() { _EffectEnd = true; }
	void PlayEffect(int idx);
	bool EffectEnd() { return _EffectEnd; }
	void RenderScreenEffect();

	Vector3 GetRenderPos(const Vector3& objPos) const { return objPos - _Diff; }
	Vector3 GetWorldPos(const Vector3& objPos) const { return  objPos + Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0) + _CameraPos; }

private:
	Vector3 _LookPos;
	Vector3 _Diff; // 카메라 중심과 화면 중앙 좌표와의 차이
	Vector3 _CameraPos;
	GameObject* _TargetObject;

	bool _EffectEnd = false;

	std::vector<GameObject*> _ScreenEffects;

	static Camera* Instance;
};

