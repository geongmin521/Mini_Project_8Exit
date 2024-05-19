#include "ScareCrow.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "TrapSceneTest.h"
#include "Utility.h"

ScareCrow::ScareCrow() : _MyTex(nullptr), _State(SCARECROW_STATE::IDLE), _MoveSpeed(500.0f * 1.3f), _CoolTime(3.0f), _Search(nullptr), _WaitTime(2.0f)
{
	_MyTex = resourceManager->GetTexture(L"ScareCrow", L"Image\\ScareCrow.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0.0f));
	_Search = new ScareCrow_Search;
	_Search->SetLocation(Vector3(-10000, -10000, 0));
	CreateObject(_Search, LAYER_GROUP::SEARCH);
	SetName(L"ScareCrow");
	GetCollider()->SetTrigger(true);
}

ScareCrow::~ScareCrow()
{
}

void ScareCrow::Update()
{
	Vector3 playerDir = _Search->GetPlayerDir();
	Vector3 playerLocation = _Search->GetPlayerLocation();
	_Search->SetLocation(GetLocation());
	_Search->SetEnable(Enable());

	if (_State == SCARECROW_STATE::IDLE) {
		if (playerLocation._x - GetLocation()._x >= 640.0f) {
			if (GetMoveAnomalyState() == true) {
				_State = SCARECROW_STATE::CHASE;
			}
		}
	}
	else if (_State == SCARECROW_STATE::CHASE) {
		if (playerDir._x >= 1.0f) {
			SetLocation(GetLocation() + playerDir * _MoveSpeed * timeManager->GetDeltaTime());
			_CoolTime -= timeManager->GetDeltaTime();
			if (_CoolTime <= 0.0f) {
				_State = SCARECROW_STATE::WAIT;
				_CoolTime = 3.0f;
			}
		}
		else {
			_State = SCARECROW_STATE::IDLE;
		}
	}
	else if (_State == SCARECROW_STATE::WAIT) {
		_WaitTime -= timeManager->GetDeltaTime();
		if (_WaitTime <= 0.0f) {
			_State = SCARECROW_STATE::CHASE;
			_WaitTime = 2.0f;
		}
	}
}

void ScareCrow::Render()
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

void ScareCrow::ResetState()
{
	_State = SCARECROW_STATE::IDLE;
}

void ScareCrow::OnTriggerEnter(Collider* collider)
{
	if (_State == SCARECROW_STATE::CHASE) {
		_State = SCARECROW_STATE::IDLE;
	}
}
