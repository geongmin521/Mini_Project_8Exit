#include "TrapSceneTest.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Spider1.h"
#include "CollisionManager.h"
#include "TrapManager.h"
#include "Trap2.h"
#include "Spider2.h"
#include "SunFlower.h"


TrapSceneTest::TrapSceneTest() : _PrevTrapIdx(-1), _ObjectPlace(10, nullptr)
{
	//TODO: 여기서 각 구역 별 기믹오브젝트를 생성해야 합니다.
}

TrapSceneTest::~TrapSceneTest()
{
}

void TrapSceneTest::Start()
{
	GameObject* bg = new BackGround;
	bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(bg, LAYER_GROUP::BACKGROUND);

	GameObject* player = new Player;
	player->SetLocation(Vector3(-800, 200, 0));
	AddObject(player, LAYER_GROUP::PLAYER);

	GameObject* spider1 = new Spider1;
	spider1->SetEnable(true);
	AddObject(spider1, LAYER_GROUP::MONSTER);

	GameObject* spider2 = new Spider2;
	spider2->SetEnable(true);
	AddObject(spider2, LAYER_GROUP::MONSTER);

	//GameObject* trap2 = new Trap2;
	//AddObject(trap2, LAYER_GROUP::BACKUNIT);

	GameObject* sunFlower = new SunFlower;
	AddObject(sunFlower, LAYER_GROUP::MONSTER);

	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::MONSTER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::TRAPTRIGGER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::BACKUNIT);

	camera->SetTarget(player);

}

void TrapSceneTest::End()
{
	SceneEnd();
}

void TrapSceneTest::InitObjectPlace()
{
	int idx;
	while (true) {
		idx = GetRandomNum();
		if (GetCompleteTrap(idx) == false && _PrevTrapIdx != idx) break;
	}
	_PrevTrapIdx = idx;

	//TODO: idx의 값에 따라 오브젝트들을 심어야 합니다.
	/*
		0 : Spider
		1 : SunFlower	HasTrap = 1
		2 : ScareCrow	HasTrap = 1
		3 : Spider		HasTrap = 1
		4 : HorseCar	HasTrap = 1	
		5 : SunFlower	HasTrap = 1
		6 : WoodHouse	HasTrap = 1
		7 : Spider		HasTrap = 1
		8 : ScareCrow	HasTrap = 1
		9 : Spider		
	
	*/

}

int TrapSceneTest::GetRandomNum()
{
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<int> dist(0, 9);
	return dist(mt);
}

void TrapSceneTest::SetCompleteTrap(int idx)
{
	_CompleteTrap.insert({ idx, true });
}

bool TrapSceneTest::GetCompleteTrap(int idx)
{
	if (_CompleteTrap.find(idx) == _CompleteTrap.end()) {
		return false;
	}
	else {
		return true;
	}
}

