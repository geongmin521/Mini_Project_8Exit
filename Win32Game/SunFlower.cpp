#include "SunFlower.h"
#include "ResourceManager.h"

SunFlower::SunFlower() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"SunFlower", L"Image\\SunFlower.png");
	SetLocation(Vector3(100, 100, 0));
}

SunFlower::~SunFlower()
{
}

void SunFlower::Update()
{
}

void SunFlower::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	if (CheckRenderPosition(startX, startY, endX, endY) == true) {
		g.DrawImage(_MyTex->GetImage(),
			startX, startY,
			endX, endY
		);
	}
}
