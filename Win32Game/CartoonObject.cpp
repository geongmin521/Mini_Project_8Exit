#include "CartoonObject.h"
#include "SceneManager.h"

CartoonObject::CartoonObject() : _MyTex(nullptr), _RenderTime(0.5f), sceneIdx(1), _Timer(0)
{
	_MyTex = resourceManager->GetTexture(L"OpeningScene1", L"Image\\scenes\\1.png");
	sceneIdx = 1;
}

CartoonObject::~CartoonObject()
{
}

void CartoonObject::Update()
{
	_RenderTime -= timeManager->GetDeltaTime();
	if (inputSystem->GetMouseButtonDown(0)) {
		sceneIdx++;
		if (sceneIdx > 5) {
			_StartTimer = true;
			camera->PlayEffect(FADE_IN);
		}
		else {
			std::wstring newKey = L"OpeningScene" + std::to_wstring(sceneIdx);
			std::wstring newPath = L"Image\\scenes\\" + std::to_wstring(sceneIdx) + L".png";
			_MyTex = resourceManager->GetTexture(newKey, newPath);
		}
	}
	if (_StartTimer == true) {
		_Timer += timeManager->GetDeltaTime();
		if (_Timer >= 1.0f) {
			_Timer = 0;
			_StartTimer = false;
			sceneManager->LoadScene(SCENE_LAYER::PLAY);
		}
	}
}

void CartoonObject::Render()
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
