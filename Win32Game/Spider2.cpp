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

	ComponentRender();
}

void Spider2::OnCollisionExit(Collider* collider)
{
	if (GetLocation()._x < collider->GetOwnerObject()->GetLocation()._x) {
		_MoveDown = true;
	}
}
