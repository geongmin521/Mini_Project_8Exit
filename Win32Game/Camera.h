#pragma once
#include "GameObject.h"

class Camera
{
public:
	Camera();
	~Camera();

	static Camera* GetInstance();
	static void DestroyInstance();

	void SetLookPos(Vector3& pos) { _LookPos = pos; }

	void Update();
	void CalDiff();

private:
	Vector3 _LookPos;
	GameObject* _TargetObject;

	static Camera* Instance;
};

