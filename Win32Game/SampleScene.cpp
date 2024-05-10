#include "SampleScene.h"
#include "SampleObject.h"
#include "Monster.h"
#include"CollisionManager.h"
#include "Camera.h"

SampleScene::SampleScene()
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::Start()
{
	GameObject* sample = new SampleObject;
	sample->SetLocation(Vector3(100, 100, 0));
	AddObject(sample, LAYER_GROUP::DEFAULT);

	GameObject* monster = new Monster;
	monster->SetLocation(Vector3(500, 500, 0));
	AddObject(monster, LAYER_GROUP::MONSTER);

	CollisionManager::GetInstance()->CheckGroup(LAYER_GROUP::DEFAULT, LAYER_GROUP::MONSTER);

	Vector3 cameraPosition= Vector3(global::GetWinApp().GetWidth() / 2, global::GetWinApp().GetHeight() / 2, 0);
	//TODO: ī�޶��� ������ ����� ������ â�� ũ��� �Ȱ��� ������ �մϴ�.
	Camera::GetInstance()->SetLookPos(cameraPosition);
	Camera::GetInstance()->SetTarget(sample);
}

void SampleScene::End()
{
	CollisionManager::GetInstance()->Reset();
	Scene::SceneEnd();
}
