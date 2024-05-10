#pragma once
#include "globalheader.h"
#include "Collider.h"

union COLLIDER_ID {
	struct {
		UINT L_ID;
		UINT R_ID;
	};
	ULONGLONG ID;
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager* GetInstance();
	static void DestroyInstance();

	void Init();
	void Update();
	void CheckGroup(LAYER_GROUP a, LAYER_GROUP b);
	void Reset() { memset(_CollisionMatrix, 0, sizeof(_CollisionMatrix)); }

private:
	static CollisionManager* Instance;

	//TODO: ���� �������� �浹 ������ ������ �־�� �մϴ�.
	std::map<ULONGLONG, bool> _CollisionInfo;
	UINT _CollisionMatrix[(int)LAYER_GROUP::END];


	void CollisionGroupUpdate(LAYER_GROUP a, LAYER_GROUP b);

	bool IsCollision(Collider* a, Collider* b);
};

