#pragma once
#include "GameObject.h"
#include "Collider.h"

#define trapManager TrapManager::GetInstance()

class TrapManager : public GameObject
{
public:
	TrapManager();
	~TrapManager();

	static TrapManager* GetInstance();
	static void DestroyInstance();

	virtual void Update();
	virtual void Render();

	void SetTargetTrap(GameObject* obj) { _TargetTrap = obj; }

	void OnCollisionEnter(Collider* collider);

	void InitTrap();

private:
	static TrapManager* Instance;

	GameObject* _TargetTrap;
};

