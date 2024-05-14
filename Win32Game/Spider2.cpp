#include "Spider2.h"
#include "ResourceManager.h"
#include "Collider.h"

Spider2::Spider2() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Spider2", L"Image\\SpiderTrap2.png");
	SetLocation(Vector3(300, -800, 0));

	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), 2300.0f, 0.0f));
}

Spider2::~Spider2()
{
}

void Spider2::Update()
{
	if (GetLocation()._y >= 0) {
		_MoveDown = false;
	}
	if (_MoveDown == true) {
		SetLocation(GetLocation() + Vector3(0, 1, 0) * 2160.0f * timeManager->GetDeltaTime());
		
	}
}

void Spider2::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->Width() / 2,
		(int)renderPosition._y - (int)_MyTex->Height() / 2,
		(int)_MyTex->Width(), (int)_MyTex->Height()
	);

	ComponentRender();
}

void Spider2::OnCollisionExit(Collider* collider)
{
	_MoveDown = true;
}
