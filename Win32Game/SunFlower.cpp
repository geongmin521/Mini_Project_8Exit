#include "SunFlower.h"
#include "ResourceManager.h"

SunFlower::SunFlower() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"SunFlower_Head", L"Image\\Flower_Head.png");
	SetLocation(Vector3(100, 100, 0));
	_StartPos = GetLocation();
	_EndPos = Vector3(GetLocation()._x, GetLocation()._y + 280.0f, GetLocation()._z); 
	SetName(L"SunFlower");
}

SunFlower::~SunFlower()
{
}

void SunFlower::Update()
{
	SetLocation(GetLocation() + _Dir * _MoveSpeed * timeManager->GetDeltaTime());
	if (GetLocation()._y > _EndPos._y ||GetLocation()._y < _StartPos._y) {
		_Dir *= -1;
	}
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
