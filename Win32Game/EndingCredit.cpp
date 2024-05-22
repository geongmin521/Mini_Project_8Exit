#include "EndingCredit.h"
#include "Credit.h"

EndingCredit::EndingCredit()
{
}

EndingCredit::~EndingCredit()
{
	
}

void EndingCredit::Start()
{
	camera->ResetLookPos();
	camera->SetTarget(nullptr);
	camera->PlayEffect(FADE_OUT);

	GameObject* credit = new Credit;
	AddObject(credit, LAYER_GROUP::BACKGROUND);
}

void EndingCredit::End()
{
	SceneEnd();
}
