#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"
#include "Camera.h"
Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(1800), _Speed(500), _IsRun(false), _RunSpeed(250),
				  _Stamina(10.0f), _MaxStamina(10.0f), _StaminaDrain(5.0f), _StaminaRecovery(10.0f), _StaminaBar(nullptr), _CurState(PlayerState::idle)
{
	_MyTex = resourceManager->GetTexture(L"Player", L"Image\\Player\\Idle\\Player_idle_0.png");
	GameObject::CreateCollider();
	GameObject::CreateAnimater(L"Player");
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GameObject::Setname(L"Player");
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
	StateManager();
	_StaminaBarMin->SetStaminaPercent(_Stamina / _MaxStamina);

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
		//_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);플립기능 애니메이션에도 적용하기.. 
		Gdiplus::Graphics g(renderSystem->_backDC);
		g.DrawImage(_MyTex->GetImage(),
			(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
			(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
			(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
		);
	}
	_StaminaBar->Render();
	_StaminaBarMin->Render();
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
	}
	else if (inputSystem->isKey(VK_RIGHT) || inputSystem->isKey('D'))
	{
		_IsWalk = true;
		dir = Vector3(1, 0, 0);
		SetDir(dir);
	}
	else
	{
		_IsWalk = false;
	}

	if (_IsRun) //스피드가 올라감
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
		//파워만큼 y축 증가 감소
		SetLocation(GetLocation() + (Vector3(0, -1, 0) * timeManager->GetDeltaTime() * CurJumpPower));
		//중력가속도에 의해 힘감소
		CurJumpPower -= 4980 * timeManager->GetDeltaTime();
		if (GetLocation()._y >= 230) //땅의 높이가 필요함.. 
		{
			_IsJump = false;
		}			
	}
}



void Player::ChangeState(PlayerState state)
{
	if (this->_CurState == state) //기존상태와 같으면 넘기기
		return;
	this->_CurState = state;

	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (state)
		{
		case PlayerState::idle: //enum을 wstring으로 수동 변환
			stateStr = L"Idle";
			break;
		case PlayerState::jump:
			stateStr = L"Jump";
			break;
		case PlayerState::walk:
			stateStr = L"Walk";
			break;
		case PlayerState::hit:
			stateStr = L"Hit";
			break;
		case PlayerState::run:
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
		ChangeState(PlayerState::jump);
		return;
	}
	else
	{
		if (_IsWalk)
		{
			if (_IsRun)
			{
				ChangeState(PlayerState::run);
			}
			else
			{
				ChangeState(PlayerState::walk);
			}
		}
		else
		{
			ChangeState(PlayerState::idle);
		}
	}
}

void Player::Run()
{
	_CurrentSpeed = _Speed;
	if (inputSystem->isKeyDown(VK_CONTROL) && _Stamina > 0) //달리기
	{
		_IsRun = true;
	}
	if (inputSystem->isKeyUp(VK_CONTROL)) //달리기
	{
		_IsRun = false;
	}

	if (_IsRun)
	{
		_Stamina -= _StaminaDrain * timeManager->GetDeltaTime();
		if (_Stamina < 0)
		{
			_Stamina = 0;
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
	// 스태미너바의 위치를 플레이어 위치로 업데이트
	if (_StaminaBar != nullptr) {
		_StaminaBar->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 300.0f, GetLocation()._z));
		_StaminaBarMin->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 300.0f, GetLocation()._z));
	}
}

void Player::OnCollisionEnter(Collider* collider)
{
	ChangeState(PlayerState::hit); //애니메이션에서 루프인지 아닌지에따라 루프가끝나면 알림오기?
}





