#include "SampleScene.h"
#include "SampleObject.h"
#include "Monster.h"
#include"CollisionManager.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
SampleScene::SampleScene()
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::Start()
{
	GameObject* sample = new SampleObject;
	sample->SetLocation(Vector3(0, 0, 0));
	AddObject(sample, LAYER_GROUP::PLAYER);

	GameObject* player = new Player;
	player->SetLocation(Vector3(0, 0, 0));
	AddObject(player, LAYER_GROUP::PLAYER);

	GameObject* monster = new Monster;
	monster->SetLocation(Vector3(500, 500, 0));
	AddObject(monster, LAYER_GROUP::MONSTER);

	GameObject* backGround = new BackGround;
	backGround->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(backGround, LAYER_GROUP::BACKGROUND);


	collisionManager->CheckGroup(LAYER_GROUP::DEFAULT, LAYER_GROUP::MONSTER);

	//Vector3 cameraPosition = Vector3(0, 0, 0);
	//Vector3 cameraPosition= Vector3((float)(WindowWidth / 2), (float)(WindowHeight / 2), 0);
	//TODO: 카메라의 랜더링 사이즈를 윈도우 창의 크기와 똑같이 만들어야 합니다.
	//camera->SetLookPos(cameraPosition);
	camera->SetTarget(player);
}

void SampleScene::End()
{
	collisionManager->Reset();
	Scene::SceneEnd();
}
