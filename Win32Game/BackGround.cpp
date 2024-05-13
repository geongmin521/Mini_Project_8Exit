#include "BackGround.h"
#include "ResourceManager.h"

BackGround::BackGround() : _MyTex(0)
{
	_MyTex = resourceManager->GetTexture(L"BackGround", L"Image\\BackGround.png");
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
}

void BackGround::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x, (int)renderPosition._y,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);
}
