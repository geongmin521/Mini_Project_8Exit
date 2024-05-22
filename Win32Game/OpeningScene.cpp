#include "OpeningScene.h"
#include "CartoonObject.h"
#include "FadeIn.h"
#include "FadeOut.h"

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
