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
	Graphics g(renderSystem->_backDC);

	int startX = 0;
	int startY = 0;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		startX, startY,
		endX, endY
	);
}
