#include "Spider2.h"
#include "ResourceManager.h"
#include "Collider.h"

Spider2::Spider2() : _MyTex(nullptr), _CoolTime(0.7f), _State(SPIDER_STATE::IDLE)
{
	_MyTex = resourceManager->GetTexture(L"Spider2", L"Image\\Spider.png");
	SetLocation(Vector3(300, -800, 0));

	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), 2300.0f, 0.0f));
}

Spider2::~Spider2()
{
}

void Spider2::Update()
{
	if (_State == SPIDER_STATE::MOVEDOWN) {
		SetLocation(GetLocation() + Vector3(0, 1, 0) * 2160.0f * timeManager->GetDeltaTime());
		if (GetLocation()._y >= 230) {
			_State = SPIDER_STATE::WAIT;
		}
	}
	else if (_State == SPIDER_STATE::WAIT) {
		_CoolTime -= timeManager->GetDeltaTime();
		if (_CoolTime <= 0) {
			_State = SPIDER_STATE::RUN;
		}
	}
	else if (_State == SPIDER_STATE::RUN) {
		SetLocation(GetLocation() + Vector3(1, 0, 0) * _MoveSpeed * timeManager->GetDeltaTime());
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
	if (_State == SPIDER_STATE::IDLE && GetLocation()._x < collider->GetOwnerObject()->GetLocation()._x) {
		_State = SPIDER_STATE::MOVEDOWN;
	}
}
