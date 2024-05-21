#include "OpeningScene.h"
#include "CartoonObject.h"

OpeningScene::OpeningScene()
{
}

OpeningScene::~OpeningScene()
{
}

void OpeningScene::Start()
{
	GameObject* cartoon = new CartoonObject;
	AddObject(cartoon, LAYER_GROUP::BACKGROUND);
}

void OpeningScene::End()
{
	SceneEnd();
}
