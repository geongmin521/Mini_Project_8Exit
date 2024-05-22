#include "NPC.h"
#include "GameManager.h"
#include "Collider.h"
#include "Player.h"
#include "Utility.h"
#include "ResourceManager.h"
#include "TextBox.h"
#include "Utility.h"
NPC::NPC() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"NPC", L"Bonfire\\Image\\bonfire.png");

	SetLocation(Vector3(300, 300, 0));

	CreateText();
	_TextBox = new TextBox(L"ぞしぞし");
	CreateObject(_TextBox,LAYER_GROUP::UI);

	CreateCollider();
	GetCollider()->SetScale(Vector3(600, 600, 0.0f));
	_TextBox->SetEnable(false);
	StateChange(BONFIRE_STATE::IDLE);
	SetName(L"Bonfire");
	CreateAnimater(L"Bonfire");
}

NPC::~NPC()
{
}


void NPC::Update()
{
	GetAinmater()->Update();
}

void NPC::Render()
{
	if (_BonfireState == BONFIRE_STATE::IDLE)
	{
		GetAinmater()->Render();
		return;
	}
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	// 獣拙 是帖人 滴奄 域至
	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	// 薄仙 是帖亜 兄希元 亜管廃 是帖昔走 溌昔 板, 戚耕走 益軒奄
	if (CheckRenderPosition(startX, startY, endX, endY) == true) {
		g.DrawImage(_MyTex->GetImage(),
			startX, startY,
			endX, endY
		);
	}
	_TextBox->SetLocation(Vector3(startX, startY, 0));
	ComponentRender();
	//_TextBox->Render();
}


void NPC::OnCollisionEnter(Collider* collider) {
	if (collider->GetOwnerObject()->GetName() == L"Player") {
		//_TextBox->GetTextComponent()->SetText(L"ぞしぞし");
		_TextBox->SetEnable(true);
	}
}

void NPC::OnCollisionExit(Collider* collider) {
	if (collider->GetOwnerObject()->GetName() == L"Player") {
		_TextBox->SetEnable(false);
	}
}

void NPC::StateChange(BONFIRE_STATE _BonfireState)
{
	if (this->_BonfireState == _BonfireState) //奄糎雌殿人 旭生檎 角奄奄
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

void NPC::ResetState()
{
	StateChange(BONFIRE_STATE::IDLE);
}