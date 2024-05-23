#include "EndingImage.h"
#include "SceneManager.h"

EndingImage::EndingImage() : _MyTex(nullptr), _Timer(0), _StoryTimer(0)
{
	_MyTex = resourceManager->GetTexture(L"EndingStory", L"Image\\scenes\\6.png");
}

EndingImage::~EndingImage()
{
}

void EndingImage::Update()
{

	_StoryTimer += timeManager->GetDeltaTime();
	if (_StoryTimer >= 2.0f) {
		_StartTimer = true;
		camera->PlayEffect(FADE_IN);
	}
	if (_StartTimer == true) {
		_Timer += timeManager->GetDeltaTime();
		if (_Timer >= 1.0f) {
			sceneManager->LoadScene(SCENE_LAYER::CREDIT);
		}
	}
}

void EndingImage::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		startX, startY,
		endX, endY
	);
}
