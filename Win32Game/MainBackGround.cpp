#include "MainBackGround.h"
#include "ResourceManager.h"

MainBackGround::MainBackGround() :_MyTex(0)
{
	_MyTex = resourceManager->GetTexture(L"MainBackGround", L"Image\\MainBG.jpg");
}

MainBackGround::~MainBackGround()
{
}

void MainBackGround::Update()
{
}

void MainBackGround::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x, (int)renderPosition._y,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);

}