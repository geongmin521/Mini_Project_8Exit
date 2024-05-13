#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"

Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(500), _Speed(500)
{
	_MyTex = resourceManager->GetTexture(L"Charactor", L"Image\\PlayerDump.png");
	GameObject::CreateCollider();
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
}

void Player::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);

	ComponentRender();
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
	if (inputSystem->isKeyDown(VK_SPACE)) //중력가속도 //addforce
	{
		_IsJump = true; 
		_JumpPower = 500;//이것도 맥스파워로 저장할수있게하기? //아니면 지역변수 스태틱으로할까?
		//뭐가 더 나은가? 여기서만 쓰는거면 지역변수 스태틱이 더 좋을듯?
	}
	if (_IsJump)
	{	
		//파워만큼 y축 증가 감소
		SetLocation(GetLocation() + (Vector3(0, -1, 0) * timeManager->GetDeltaTime() * _JumpPower)); 
		//중력가속도에 의해 힘감소
		_JumpPower -= 980 * timeManager->GetDeltaTime();
		if (GetLocation()._y >= 230) //땅의 높이가 필요함.. 
			_IsJump = false;
	}
}
