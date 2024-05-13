#include "TrapSceneTest.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Trap1.h"
#include "CollisionManager.h"
#include "TrapManager.h"
#include "Trap2.h"


TrapSceneTest::TrapSceneTest()
{
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
	player->SetLocation(Vector3(-800, 230, 0));
	AddObject(player, LAYER_GROUP::PLAYER);

	GameObject* trap1 = new Trap1;
	trap1->SetEnable(false);
	AddObject(trap1, LAYER_GROUP::MONSTER);

	GameObject* trap2 = new Trap2;
	AddObject(trap2, LAYER_GROUP::BACKUNIT);

	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::TRAPTRIGGER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::BACKUNIT);

	camera->SetTarget(player);

	trapManager->InitTrap();
	trapManager->SetTargetTrap(trap2);
	trapManager->SetLocation(Vector3(trap2->GetLocation()._x + 640, 230, 0));
	AddObject(trapManager, LAYER_GROUP::TRAPTRIGGER);
}

void TrapSceneTest::End()
{
	SceneEnd();
}
