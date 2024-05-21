#include "CartoonObject.h"
#include "SceneManager.h"

CartoonObject::CartoonObject() : _MyTex(nullptr), _RenderTime(0.0f), sceneIdx(1)
{
	_MyTex = resourceManager->GetTexture(L"OpeningScene1", L"Image\\scenes\\1.png");
}

CartoonObject::~CartoonObject()
{
}

void CartoonObject::Update()
{
	_RenderTime -= timeManager->GetDeltaTime();
	if (_RenderTime <= 0) {
		_RenderTime = 0.0f;
		sceneIdx++;
		if (sceneIdx > 4) {
			sceneManager->LoadScene(SCENE_LAYER::PLAY);
		}
		else {
			std::wstring newKey = L"OpeningScene" + std::to_wstring(sceneIdx);
			std::wstring newPath = L"Image\\scenes\\" + std::to_wstring(sceneIdx) + L".png";
			_MyTex = resourceManager->GetTexture(newKey, newPath);
		}
	}
}

void CartoonObject::Render()
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
