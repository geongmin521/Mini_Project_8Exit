#include "HomeScene.h"
#include "House.h"
#include "CollisionManager.h"
#include "Player.h"
#include "GameBG.h"

HomeScene::HomeScene()
{
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::TRAPTRIGGER);
}

HomeScene::~HomeScene()
{
}

void HomeScene::Start()
{
	camera->PlayEffect(FADE_OUT);

	GameObject* bg = new GameBG;
	bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(bg, LAYER_GROUP::BACKGROUND);

	GameObject* player = new Player(20.0f);
	player->SetLocation(Vector3(-800, 230, 0));
	AddObject(player, LAYER_GROUP::PLAYER);

	camera->SetTarget(nullptr);
	camera->ResetLookPos();
	
	GameObject* house = new House;
	house->SetLocation(Vector3(500.0f, 100.0f, 0));
	AddObject(house, LAYER_GROUP::TRAPTRIGGER);

	
}

void HomeScene::End()
{
	SceneEnd();
}
