#include "LastBackGround.h"
#include "ResourceManager.h"

LastBackGround::LastBackGround() :_MyTex(0)
{
	_MyTex = resourceManager->GetTexture(L"LastBackGround", L"Image\\LastBackGround.png");
}

LastBackGround::~LastBackGround()
{
}

void LastBackGround::Update()
{
}

void LastBackGround::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x, (int)renderPosition._y,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);

}
