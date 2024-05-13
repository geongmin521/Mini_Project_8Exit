#include "Trap1.h"
#include "ResourceManager.h"
#include "Collider.h"

Trap1::Trap1() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Trap1", L"Image\\sampleTrap.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));
	SetLocation(Vector3(1000, 100, 0));
	_PrevPosition = GameObject::GetLocation();
}

Trap1::~Trap1()
{

}

void Trap1::Update()
{
	//TODO: 아래로 내려갔다가 사라집니다. Enable == true 일때 작동합니다.
}

void Trap1::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->Width() / 2,
		(int)renderPosition._y - (int)_MyTex->Height() / 2,
		(int)_MyTex->Width(), (int)_MyTex->Height()
	);
}
