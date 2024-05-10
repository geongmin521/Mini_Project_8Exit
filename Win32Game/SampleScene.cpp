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

	Vector3 cameraSize(global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), 0);
	//TODO: 카메라의 랜더링 사이즈를 윈도우 창의 크기와 똑같이 만들어야 합니다.
}

void SampleScene::End()
{
	CollisionManager::GetInstance()->Reset();
	Scene::SceneEnd();
}
