#include "Trap2.h"
#include "ResourceManager.h"
#include "Collider.h"

Trap2::Trap2() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Scarecrow", L"Image\\Scarecrow.png");
	SetLocation(Vector3(300, 230, 0));
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width() + 5120, (float)_MyTex->Height(), 0));
}

Trap2::~Trap2()
{
}

void Trap2::Update()
{
	if (_Chase == true) {
		SetLocation(GetLocation() + Vector3(1, 0, 0) * (500.0f * 0.9f) * timeManager->GetDeltaTime());
	}
}

void Trap2::Render()
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

void Trap2::OnCollision(Collider* collider)
{
	if (GetCollider()->GetPos()._x + 640.0f <= collider->GetPos()._x) {
		_Chase = true;
	}
}

void Trap2::OnCollisionExit(Collider* collider)
{
	_Chase = false;
}
