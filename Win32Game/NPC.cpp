#include "NPC.h"
#include "GameManager.h"
#include "Collider.h"
#include "Player.h"
#include "Utility.h"
#include "ResourceManager.h"
#include "TextBox.h"

NPC::NPC(std::wstring DialogKey) : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"NPC", L"Image\\Cat_Animation\\Cat_Talk_0.png");

	SetLocation(Vector3(300, 300, 0));
	_DialogKey = DialogKey;

	_TextBox = new TextBox(resourceManager->GetDialog(_DialogKey + L"0"), 24, Color(255, 0, 0, 0), (int)FontType::dialog, true, true);
	CreateObject(_TextBox,LAYER_GROUP::INGAMEUI);

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
	if (_DialogKey == L"StartCat")
	{
		TutorialDiaLog();
	}
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
		GetAinmater()->Render();
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
	_TextBox->SetLocation(Vector3((float)(startX + 400), (float)(startY - 50) , 0));
	ComponentRender();
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

void NPC::Init(int stage)
{
	_StageNum = stage - 1;
	if (_DialogKey == L"EndCat")
	{
		EndDioLog();
	}
	else if (_DialogKey == L"StageCat"|| _DialogKey == L"StartCat")
	{
		if (_StageNum == 0)
		{
			_DialogKey = L"StartCat";
			GetAinmater()->ChangeState(L"Talk");
			_TextBox->SetEnable(true);
			_TextBox->GetTextComponent()->SetText(resourceManager->GetDialog(L"StartCat0"));
		}
		else
		{
			_DialogKey = L"StageCat";
			_TextBox->SetEnable(false);
			StageDioLog();
		}	
	}
}

void NPC::StageDioLog()
{
	std::wstring text = resourceManager->GetDialog(L"StageCat" + std::to_wstring(_StageNum));
	_TextBox->GetTextComponent()->SetText(text);
}

void NPC::TutorialDiaLog() //콜라이더 와 상관없이 진행하기?
{
	static int dialogCount=0;
	static float Timer=0;
	Timer += timeManager->GetDeltaTime();	
	if (inputSystem->isKeyDown(VK_RETURN))
	{
		Timer = 1.9;
	}
		
	if (Timer >= 2)
	{
		Timer = 0;
		std::wstring text = resourceManager->GetDialog(L"StartCat" + std::to_wstring(dialogCount));
		if(dialogCount<=10)
			_TextBox->GetTextComponent()->SetText(text); 
		dialogCount++;
	}
}

void NPC::EndDioLog()
{
	std::wstring text;
	if (_StageNum == 0)
	{
		text = resourceManager->GetDialog(L"EndCat0");
	}
	else
	{
		text = resourceManager->GetDialog(L"EndCat" + std::to_wstring(GetRandomNum(13)+1));
	}
	_TextBox->GetTextComponent()->SetText(text);
}

