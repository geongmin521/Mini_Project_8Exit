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
	//TODO: ī�޶��� ������ ����� ������ â�� ũ��� �Ȱ��� ������ �մϴ�.
	//camera->SetLookPos(cameraPosition);
	camera->SetTarget(player);
}

void SampleScene::End()
{
	collisionManager->Reset();
	Scene::SceneEnd();
}
