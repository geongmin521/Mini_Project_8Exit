#pragma once
#include "GameObject.h"

#define camera Camera::GetInstance()

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

	Vector3 GetRenderPos(const Vector3& objPos) const { return objPos - _Diff; }
	Vector3 GetWorldPos(const Vector3& objPos) const { return  objPos + Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2) -200, 0) + _LookPos; }

private:
	Vector3 _LookPos;
	Vector3 _Diff; // 카메라 중심과 화면 중앙 좌표와의 차이
	GameObject* _TargetObject;

	static Camera* Instance;
};

