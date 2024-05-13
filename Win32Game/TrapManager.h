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

	void InitTrap();

private:
	static TrapManager* Instance;
};

