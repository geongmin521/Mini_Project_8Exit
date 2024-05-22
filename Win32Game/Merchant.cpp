#include "Merchant.h"
#include "Collider.h"
#include "Utility.h"
#include "Music.h"

Merchant::Merchant()
{
	_MyTex = resourceManager->GetTexture(L"Merchant", L"Image\\Merchant.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0.0f));
	GetCollider()->SetTrigger(true);
	SetName(L"Merchant");
	_TextBox = new TextBox(L"거미 먹을래?",12,Color(255,0,0,0),(int)FontType::dialog);
	CreateObject(_TextBox, LAYER_GROUP::UI);
	_TextBox->SetEnable(false); 

	GameObject::CreateAnimater(L"Merchant", 0.1f);
}

Merchant::~Merchant()
{
}

void Merchant::Init()
{
	if (GetDiffAnomalyState())
	{
		int gimmick = GetRandomNum(2); //0,1
		switch (gimmick)
		{
		case 0://색깔 		
			_MyTex = resourceManager->GetTexture(L"Mercnant_Red", L"Image\\Merchant_Red.png");
			GetAinmater()->SetName(L"RedMerchant");
			break;
		case 1://대화 내용
			_TextBox->GetTextComponent()->SetText(L"거ㅁ 먹ㅁㅁ?");
			break;
		}
		SetDiffAnomalyState(false);
	}
	else
	{
		_MyTex = resourceManager->GetTexture(L"Merchant", L"Image\\Merchant.png");
		_TextBox->GetTextComponent()->SetText(L"거미 먹을래?");
		GetAinmater()->SetName(L"Merchant");
		//노말
	}
	GetAinmater()->ChangeState(L"ClearAnimator");
	GetAinmater()->ChangeState(L"Idle");
}

void Merchant::Update()
{
	ChangeImage();
	GetAinmater()->Update();
	//_TextBox->SetLocation(GetLocation() + Vector3(800,200,0));
}

void Merchant::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();
	if (GetAinmater() == nullptr)
	{
	
		Graphics g(renderSystem->_backDC);
		//g.dra
		if (_MyTex->GetFlipX() != GetFlipX()) {
			_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);
			_MyTex->SetFlipX(GetFlipX());
		}
		if (CheckRenderPosition(startX, startY, endX, endY) == true) {
			g.DrawImage(_MyTex->GetImage(),
				startX, startY,
				endX, endY
			);
		}
	
	}
	else
	{
		_TextBox->SetLocation(Vector3((float)(startX + 500), (float)(startY + 130), 0));
		GetAinmater()->Render();
	}
	//_TextBox->Render();

}

void Merchant::ResetState()
{
	Init();
}

void Merchant::OnTriggerEnter(Collider* collider)
{
	if (collider->GetOwnerObject()->GetName() == L"Player") {
		_TextBox->SetEnable(true);
		ChangeState(MerchantState::Talk);
	}
}

void Merchant::OnTriggerExit(Collider* collider)
{
	if (collider->GetOwnerObject()->GetName() == L"Player") {
		_TextBox->SetEnable(false);
		ChangeState(MerchantState::Idle);
	}
}

void Merchant::ChangeState(MerchantState state)
{
	if (_State == state) //기존상태와 같으면 넘기기
		return;
	_State = state;
	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (_State)
		{
		case MerchantState::Idle: //enum을 wstring으로 수동 변환
			stateStr = L"Idle";
			Music::soundManager->StopMusic(Music::eSoundChannel::Talk); //대화 배경음악 꺼버리기
			break;
		case MerchantState::Talk:
			stateStr = L"Talk";
			Music::soundManager->PlayMusic(Music::eSoundList::Merchant_chat, Music::eSoundChannel::Talk);
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}

void Merchant::ChangeImage()
{

}
