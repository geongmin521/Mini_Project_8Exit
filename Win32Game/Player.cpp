#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"
#include "Camera.h"
Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(200), _Speed(500), _IsRun(false), _RunSpeed(),
				  _Stamina(10.0f), _MaxStamina(10.0f), _StaminaDrain(5.0f), _StaminaRecovery(10.0f), _StaminaBar(nullptr)

Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(500), _Speed(500), _CurState(PlayerState::idle)
{
	_MyTex = resourceManager->GetTexture(L"Player", L"Image\\Player_idle_0.png");
	GameObject::CreateCollider();
	GameObject::CreateAnimater(L"Player");
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));

	_StaminaBar = new StaminaBar;
	_StaminaBarMin = new StaminaBarMin;

}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Jump();
	Run();
	StaminaBarActions();
	StaminaBarMinActions();
	_StaminaBarMin->SetStaminaPercent(_Stamina / _MaxStamina);
}
	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Update();
	}
}

void Player::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Render();
	}
	else
	{
		//_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);�ø���� �ִϸ��̼ǿ��� �����ϱ�.. 
		Gdiplus::Graphics g(renderSystem->_backDC);
		g.DrawImage(_MyTex->GetImage(),
			(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
			(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
			(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
		);
	}

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);
	_StaminaBar->Render();
	_StaminaBarMin->Render();
}

	//ComponentRender();
}

void Player::Move()
{
	if (inputSystem->isKey(VK_LEFT)|| inputSystem->isKey('A'))
	{
		SetLocation(GetLocation() + Vector3(-1, 0 ,0) * timeManager->GetDeltaTime() * _Speed);
		
	}
	if (inputSystem->isKey(VK_RIGHT) || inputSystem->isKey('D'))
	{
		SetLocation(GetLocation() + Vector3(1, 0, 0) * timeManager->GetDeltaTime() * _Speed);
	}
}

void Player::Jump()
{
	static float CurJumpPower = 0;
	if (inputSystem->isKeyDown(VK_SPACE) && _IsJump == false) 
	{
		ChangeState(PlayerState::jump);
		_IsJump = true; 
		CurJumpPower = _JumpPower;
	}
	if (_IsJump)
	{	
		//�Ŀ���ŭ y�� ���� ����
		SetLocation(GetLocation() + (Vector3(0, -1, 0) * timeManager->GetDeltaTime() * CurJumpPower));
		//�߷°��ӵ��� ���� ������
		CurJumpPower -= 980 * timeManager->GetDeltaTime();
		if (GetLocation()._y >= 200) //���� ���̰� �ʿ���.. 
		{
			ChangeState(PlayerState::idle);
			_IsJump = false;
		}
			
	}
}

void Player::ChangeState(PlayerState state)
{
	this->_CurState = state;

	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (state)
		{
		case PlayerState::idle: //enum�� wstring���� ���� ��ȯ
			stateStr = L"Idle";
			break;
		case PlayerState::jump:
			stateStr = L"Jump";
			break;
		case PlayerState::hit:
			stateStr = L"Hit";
			break;
		case PlayerState::move:
			stateStr = L"Move";
			break;
		default:
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}

void Player::Run()
{
	_CurrentSpeed = _Speed;
	if (inputSystem->isKey(VK_CONTROL) && _Stamina > 0) //�޸���
	{
		_IsRun = true;
		_RunSpeed = _Speed + 10000;

		// ���¹̳� �Ҹ�
		_Stamina -= _StaminaDrain * timeManager->GetDeltaTime();
		if (_Stamina < 0) 
		{
			_Stamina = 0;
			_IsRun = false;
		}
	}
	else
	{
		// ���¹̳� ȸ��
		_Stamina += _StaminaRecovery * timeManager->GetDeltaTime();
		if (_Stamina > _MaxStamina)
		{
			_Stamina = _MaxStamina;
		}
	}
	if (_IsRun && _Stamina > 0)
	{
		_CurrentSpeed = _RunSpeed;
		_IsRun = false;
	}
	if (inputSystem->isKey(VK_LEFT) || inputSystem->isKey('A'))
	{
		SetLocation(GetLocation() + Vector3(-1, 0, 0) * timeManager->GetDeltaTime() * _CurrentSpeed);
	}
	if (inputSystem->isKey(VK_RIGHT) || inputSystem->isKey('D'))
	{
		SetLocation(GetLocation() + Vector3(1, 0, 0) * timeManager->GetDeltaTime() * _CurrentSpeed);
	}
	
}

void Player::StaminaBarActions()
{
	// ���¹̳ʹ��� ��ġ�� �÷��̾� ��ġ�� ������Ʈ
	if (_StaminaBar != nullptr) {
		_StaminaBar->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 300.0f, GetLocation()._z));

	}
}

void Player::StaminaBarMinActions()
{
	// �پ��� ���¹̳ʹ��� ��ġ�� �÷��̾� ��ġ�� ������Ʈ
	if (_StaminaBarMin != nullptr) {
		_StaminaBarMin->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 300.0f, GetLocation()._z));
	}
}


