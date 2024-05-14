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
#include "TextBox.h"

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
	GameObject* textBox = new TextBox;
	textBox->SetLocation(Vector3(200,200, 0));
	AddObject(textBox, LAYER_GROUP::UI);

	GameObject* trap1 = new Trap1;
	trap1->SetLocation(Vector3(1000, 100, 0));
	AddObject(trap1, LAYER_GROUP::MONSTER);

	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::MONSTER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::TRAPTRIGGER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::BACKUNIT);

	camera->SetTarget(player);

	//trapManager->InitTrap();
	//trapManager->SetTargetTrap(spider1);
	//trapManager->SetLocation(Vector3(trap2->GetLocation()._x + 640, 230, 0));
	//AddObject(trapManager, LAYER_GROUP::TRAPTRIGGER);
}

void TrapSceneTest::End() 
{
	SceneEnd();
}
