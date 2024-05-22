#include "EndingScene.h"
#include "EndingImage.h"

EndingScene::EndingScene()
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::Start()
{
	camera->PlayEffect(FADE_OUT);
	camera->SetTarget(nullptr);
	camera->ResetLookPos();

	GameObject* ending = new EndingImage;
	AddObject(ending, LAYER_GROUP::BACKGROUND);
}

void EndingScene::End()
{
	SceneEnd();
}
