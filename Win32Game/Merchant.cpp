#include "Merchant.h"
#include "Collider.h"

Merchant::Merchant()
{
	_MyTex = resourceManager->GetTexture(L"Merchant", L"Image\\Merchant.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0.0f));
	GetCollider()->SetTrigger(true);
	SetName(L"Merchant");
	CreateText();
	_TextBox = new TextBox(L"��������");
	CreateObject(_TextBox, LAYER_GROUP::UI);
	_TextBox->SetLocation(GetLocation() + Vector3(800, 200, 0));
	_TextBox->SetEnable(false); //�ؽ�Ʈ�ڽ��� �����̴³��̾��µ� �� ������? �ؽ�Ʈ�ڽ��� 
	//������ ī�޶��������ΰŰ�����
	//���� �����ϱ� 

	GameObject::CreateAnimater(L"Merchant", 0.1f);
	GetAinmater()->ChangeState(L"Idle");
}

Merchant::~Merchant()
{
}

void Merchant::Update()
{
	GetAinmater()->Update();
	//_TextBox->SetLocation(GetLocation() + Vector3(800,200,0));
}

void Merchant::Render()
{
	if (GetAinmater() == nullptr)
	{
		Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
		Graphics g(renderSystem->_backDC);

		//g.dra
		if (_MyTex->GetFlipX() != GetFlipX()) {
			_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);
			_MyTex->SetFlipX(GetFlipX());
		}

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
	}
	else
	{
		GetAinmater()->Render();
	}

}

void Merchant::ResetState()
{
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
	if (_State == state) //�������¿� ������ �ѱ��
		return;
	_State = state;
	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (_State)
		{
		case MerchantState::Idle: //enum�� wstring���� ���� ��ȯ
			stateStr = L"Idle";
			break;
		case MerchantState::Talk:
			stateStr = L"Talk";
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}
