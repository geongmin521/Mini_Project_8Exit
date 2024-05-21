#include "GameBG.h"

GameBG::GameBG() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"GameBG", L"Image\\Background_New.bmp");
}

GameBG::~GameBG()
{
}

void GameBG::Update()
{
}

void GameBG::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	BitBlt(renderSystem->_backDC, 
		renderPosition._x, renderPosition._y, 
		_MyTex->GetBitInfo().bmWidth, _MyTex->GetBitInfo().bmHeight, 
		_MyTex->GetDC(), 0, 0, SRCCOPY
	);
}
