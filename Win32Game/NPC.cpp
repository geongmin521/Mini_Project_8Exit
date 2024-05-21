#include "NPC.h"
#include "GameManager.h"
#include "Collider.h"
#include "Player.h"
#include "Utility.h"
#include "ResourceManager.h"
#include "TextBox.h"

NPC::NPC() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"NPC", L"Image\\Cat_Animation\\Cat_Talk_0.png");

	SetLocation(Vector3(300, 300, 0));

	_TextBox = new TextBox(L"ㅎㅇㅎㅇ", 12, Color(255, 0, 0, 0), (int)FontType::dialog);
	CreateObject(_TextBox,LAYER_GROUP::UI);

	CreateCollider();
	GetCollider()->SetScale(Vector3(600, 600, 0.0f));
	GetCollider()->SetTrigger(true);
	_TextBox->SetEnable(false);

	CreateAnimater(L"Cat", 0.1f);
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
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	// 시작 위치와 크기 계산
	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	if (GetAinmater() != nullptr)
	{
		//GetAinmater()->Render();
	}
	else
	{
		// 현재 위치가 렌더링 가능한 위치인지 확인 후, 이미지 그리기
		if (CheckRenderPosition(startX, startY, endX, endY) == true) {
			g.DrawImage(_MyTex->GetImage(),
				startX, startY,
				endX, endY
			);
		}
	}

	_TextBox->SetLocation(Vector3(startX, startY-200, 0));
	ComponentRender();
	//_TextBox->Render();
}


void NPC::OnTriggerEnter(Collider* collider) {
	if (collider->GetOwnerObject()->GetName() == L"Player") {
		//_TextBox->GetTextComponent()->SetText(L"ㅎㅇㅎㅇ");
		_State = NPCState::Talk;
		GetAinmater()->ChangeState(L"Talk");
		_TextBox->SetEnable(true);
	}
}

void NPC::OnTriggerExit(Collider* collider) {
	if (collider->GetOwnerObject()->GetName() == L"Player") {
		_State = NPCState::Idle;
		GetAinmater()->ChangeState(L"Idle");
		_TextBox->SetEnable(false);
	}
}

