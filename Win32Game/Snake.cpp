#include "Snake.h"
#include "ResourceManager.h"
#include "Collider.h"

Snake::Snake() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Snake", L"Image\\Snake.png");
	SetLocation(Vector3(1300, -850, 0));
	CreateCollider();

	GetCollider()->SetScale(Vector3(_MyTex->Width(), 2300.0f, 0));
	SetName(L"Snake");
}

Snake::~Snake()
{
}

void Snake::Update()
{
	if (_State == SNAKE_STATE::CHASE) {
		SetLocation(GetLocation() + _RunDir * _MoveSpeed * 2 * timeManager->GetDeltaTime());
	}
	else if (_State == SNAKE_STATE::MOVEDOWN) {
		SetLocation(GetLocation() + Vector3(0, 1, 0) * _MoveSpeed * timeManager->GetDeltaTime());
		if (GetLocation()._y >= 300) {
			_State = SNAKE_STATE::WAIT;
		}
	}
	else if (_State == SNAKE_STATE::WAIT) {
		_CoolTime -= timeManager->GetDeltaTime();
		if (_CoolTime <= 0) {
			_State = SNAKE_STATE::CHASE;
		}
	}
}

void Snake::Render()
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

void Snake::OnCollisionEnter(Collider* collider)
{
	//if (_State == SNAKE_STATE::CHASE) {
	//	SceneReload();
	//}
}

void Snake::OnCollisionExit(Collider* collider)
{
	if (_State == SNAKE_STATE::IDLE && GetLocation()._x < collider->GetOwnerObject()->GetLocation()._x) {
		GetCollider()->SetScale(Vector3(278.0f, 200.0f, 0.0f));
		_RunDir = Vector3(1, 0, 0);
		_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);
		_State = SNAKE_STATE::MOVEDOWN;
	}
}
