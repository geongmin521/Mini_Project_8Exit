#include "Bonfire.h"
#include "GameManager.h"
#include "Collider.h"
#include "Player.h"
#include "Utility.h"
#include "ResourceManager.h"

Bonfire::Bonfire() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"NPC", L"Bonfire\\Image\\bonfire.png");

	SetLocation(Vector3(300, 300, 0));
	CreateCollider();
	GetCollider()->SetScale(Vector3(600, 600, 0.0f));
	CreateAnimater(L"Bonfire", 0.1f);
	StateChange(BONFIRE_STATE::IDLE);
	SetName(L"Bonfire");
	GetCollider()->SetTrigger(true);
}

Bonfire::~Bonfire()
{
}


void Bonfire::Update()
{
	GetAinmater()->Update();
}

void Bonfire::Render()
{
	if (_BonfireState == BONFIRE_STATE::IDLE)
	{
		GetAinmater()->Render();
		return;
	}
	ComponentRender();
}

void Bonfire::StateChange(BONFIRE_STATE _BonfireState)
{
	if (this->_BonfireState == _BonfireState) //�������¿� ������ �ѱ��
		return;
	this->_BonfireState = _BonfireState;

	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (_BonfireState)
		{
		case BONFIRE_STATE::IDLE:
			stateStr = L"Idle";
			break;

			GetAinmater()->ChangeState(stateStr);
		}
	}
}

void Bonfire::ResetState()
{
	StateChange(BONFIRE_STATE::IDLE);
}