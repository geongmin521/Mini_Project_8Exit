#include "SunFlower.h"
#include "ResourceManager.h"

SunFlower::SunFlower() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"SunFlower", L"Image\\SunFlower.png");
	SetLocation(Vector3(100, 100, 0));
	_StartPos = GetLocation();
	_EndPos = Vector3(GetLocation()._x, GetLocation()._y + 280.0f, GetLocation()._z);
}

SunFlower::~SunFlower()
{
}

void SunFlower::Update()
{
	SetLocation(GetLocation() + _Dir * _MoveSpeed * timeManager->GetDeltaTime());
	if (GetLocation()._y >= _EndPos._y || GetLocation()._y <= _StartPos._y) {
		_Dir *= -1;
	}
}

void SunFlower::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->Width() / 2,
		(int)renderPosition._y - (int)_MyTex->Height() / 2,
		(int)_MyTex->Width(), (int)_MyTex->Height()
	);
}
