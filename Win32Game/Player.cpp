#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"

Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(500), _Speed(500)
{
	_MyTex = resourceManager->GetTexture(L"Player", L"Image\\Player.png");
	GameObject::CreateCollider();
	GameObject::CreateAnimater(L"alpha100");
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	//etCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));
}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Jump();
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
		Graphics g(renderSystem->_backDC);
		g.DrawImage(_MyTex->GetImage(),
			(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
			(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
			(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
		);
	}
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
		//파워만큼 y축 증가 감소
		SetLocation(GetLocation() + (Vector3(0, -1, 0) * timeManager->GetDeltaTime() * CurJumpPower));
		//중력가속도에 의해 힘감소
		CurJumpPower -= 980 * timeManager->GetDeltaTime();
		if (GetLocation()._y >= 0) //땅의 높이가 필요함.. 
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
		case PlayerState::idle: //enum을 wstring으로 수동 변환
			stateStr = L"idle";
			break;
		case PlayerState::jump:
			stateStr = L"jump";
			break;
		case PlayerState::hit:
			stateStr = L"hit";
			break;
		case PlayerState::move:
			stateStr = L"move";
			break;
		default:
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}
