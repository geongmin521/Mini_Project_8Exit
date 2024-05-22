#include "Bonfire.h"
#include "GameManager.h"
#include "Collider.h"
#include "Player.h"
#include "Utility.h"
#include "ResourceManager.h"
#include "Music.h"

Bonfire::Bonfire() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"NPC", L"Bonfire\\Image\\bonfire.png");

	
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
	if (this->_BonfireState == _BonfireState) //기존상태와 같으면 넘기기
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

void Bonfire::OnTriggerExit(Collider* collision)
{
	Music::soundManager->StopMusic( Music::eSoundChannel::Fire);//음악 재생
}

void Bonfire::OnTriggerEnter(Collider* collision)
{
	Music::soundManager->PlayMusic(Music::eSoundList::bonfire, Music::eSoundChannel::Fire);//음악 재생
}


void Bonfire::ResetState()
{
	StateChange(BONFIRE_STATE::IDLE);
}