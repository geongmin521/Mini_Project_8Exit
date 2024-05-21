#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"
#include "Camera.h"
Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(1800), _Speed(500), _IsRun(false), _RunSpeed(250),
				  _Stamina(10.0f), _MaxStamina(10.0f), _StaminaDrain(5.0f), _StaminaRecovery(10.0f), _StaminaBar(nullptr), _CurState(PlayerState::Idle)
{
	_MyTex = resourceManager->GetTexture(L"Player", L"Image\\Player\\Idle\\Player_idle_0.png");
	GameObject::CreateCollider();
	GameObject::CreateAnimater(L"Player",0.1f);
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GameObject::SetName(L"Player");
	_Runable = true;
	_StaminaBar = new StaminaBar;
	_StaminaBarMin = new StaminaBarMin;
}

Player::~Player()
{
}

void Player::Update()
{
	if (_IsHit == false)
	{
		Move();
		Jump();
		Run();		
		StateManager();
		_StaminaBarMin->SetStaminaPercent(_Stamina / _MaxStamina);
	}
	StaminaBarActions();

	Vector3 renderPosition = camera->GetRenderPos(GetLocation());
	if ((int)renderPosition._x - (_MyTex->Width() / 2) >= WindowWidth) {
		SceneReload();
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
	if (_IsRun == true)
	{
		_StaminaBar->Render();
		_StaminaBarMin->Render();
	}
	//Gdiplus::
	ComponentRender();
}

void Player::Move()
{
	float speed;
	Vector3 dir;
	if (inputSystem->isKey(VK_LEFT)|| inputSystem->isKey('A')) 
	{
		_IsWalk = true;
		dir = Vector3(-1, 0, 0);
		SetDir(dir);
		SetFlipX(true);
	}
	else if (inputSystem->isKey(VK_RIGHT) || inputSystem->isKey('D'))
	{
		_IsWalk = true;
		dir = Vector3(1, 0, 0);
		SetDir(dir);
		SetFlipX(false);
	}
	else
	{
		_IsWalk = false;
	}

	if (_IsRun) //���ǵ尡 �ö�
	{
		speed = _Speed + _RunSpeed;
	}
	else
	{
		speed = _Speed;
	}

	if (_IsWalk)
	{
		SetLocation(GetLocation() + dir * timeManager->GetDeltaTime() * speed);
	}
}

void Player::Jump()
{
	static float CurJumpPower = 0;
	if (inputSystem->isKeyDown(VK_SPACE) && _IsJump == false) 
	{
		_IsJump = true; 
		CurJumpPower = _JumpPower;
	}
	if (_IsJump)
	{	
		//�Ŀ���ŭ y�� ���� ����
		SetLocation(GetLocation() + (Vector3(0, -1, 0) * timeManager->GetDeltaTime() * CurJumpPower));
		//�߷°��ӵ��� ���� ������
		CurJumpPower -= 4980 * timeManager->GetDeltaTime();
		if (GetLocation()._y >= 230) //���� ���̰� �ʿ���.. 
		{
			_IsJump = false;
		}			
	}
}

void Player::ChangeState(PlayerState state)
{
	if (this->_CurState == state) //�������¿� ������ �ѱ��
		return;
	this->_CurState = state;

	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (state)
		{
		case PlayerState::Idle: //enum�� wstring���� ���� ��ȯ
			stateStr = L"Idle";
			break;
		case PlayerState::Jump:
			stateStr = L"Jump";
			break;
		case PlayerState::Walk:
			stateStr = L"Walk";
			break;
		case PlayerState::Hit:
			stateStr = L"Hit";
			break;
		case PlayerState::Run:
			stateStr = L"Run";
			break;
		default:
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}

void Player::StateManager()
{
	if (_IsJump)
	{
		ChangeState(PlayerState::Jump);
		return;
	}
	else
	{
		if (_IsWalk)
		{
			if (_IsRun)
			{
				ChangeState(PlayerState::Run);
			}
			else
			{
				ChangeState(PlayerState::Walk);
			}
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
	}
}

void Player::Run()
{
	if (inputSystem->isKey(VK_CONTROL) && _Stamina > 0 && _Runable&&_IsWalk)//�������ͽ� 
	{
		_IsRun = true;
	}
	else
	{
		
		_IsRun = false;
	}

	if (!inputSystem->isKey(VK_CONTROL))
	{
		_Runable = true;
	}

	if (_IsRun)
	{
		_Stamina -= _StaminaDrain * timeManager->GetDeltaTime();
		if (_Stamina < 0)
		{
			_Stamina = 0;
			_Runable = false;
			_IsRun = false;
		}
	}
	else
	{
		_Stamina += _StaminaRecovery * timeManager->GetDeltaTime();
		if (_Stamina > _MaxStamina)
		{
			_Stamina = _MaxStamina;
		}
	}
}

void Player::StaminaBarActions()
{
	// ���¹̳ʹ��� ��ġ�� �÷��̾� ��ġ�� ������Ʈ
	if (_StaminaBar != nullptr) {
		_StaminaBar->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 300.0f, GetLocation()._z));
		_StaminaBarMin->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 300.0f, GetLocation()._z));
	}
}

void Player::OnCollisionEnter(Collider* collider)
{
	_IsHit = true;
	ChangeState(PlayerState::Hit); //�ִϸ��̼ǿ��� �������� �ƴ��������� ������������ �˸�����?
	SceneReload();

}