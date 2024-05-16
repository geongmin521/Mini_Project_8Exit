#include "WoodHouse.h"
#include "ResourceManager.h"
#include "Collider.h"

WoodHouse::WoodHouse() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"WoodHouse", L"Image\\WoodHouse_Dummy.png");
	// 7¹ø À§Ä¡ ( 25920~ )
	SetLocation(Vector3(27840, 540, 0));
}

WoodHouse::~WoodHouse()
{
}

void WoodHouse::Update()
{
}

void WoodHouse::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->Width() / 2,
		(int)renderPosition._y - (int)_MyTex->Height() / 2,
		(int)_MyTex->Width(), (int)_MyTex->Height()
	);
}
