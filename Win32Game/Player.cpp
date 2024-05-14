#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"

Player::Player(): _MyTex(nullptr), _IsHit(false), _IsJump(false), _JumpPower(200), _Speed(500), _IsRun(false), _RunSpeed(),
				  _Stamina(10.0f), _MaxStamina(10.0f), _StaminaDrain(10.0f), _StaminaRecovery(2.0f)
{
	_MyTex = resourceManager->GetTexture(L"Charactor", L"Image\\PlayerDump.png");
	GameObject::CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));
}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Jump();
	Run();
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
	_staminaBar->Render();
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
	if (inputSystem->isKeyDown(VK_SPACE)) //�߷°��ӵ� //addforce
	{
		_IsJump = true; 
		_JumpPower = 500;//�̰͵� �ƽ��Ŀ��� �����Ҽ��ְ��ϱ�? //�ƴϸ� �������� ����ƽ�����ұ�?
		//���� �� ������? ���⼭�� ���°Ÿ� �������� ����ƽ�� �� ������?
	}
	if (_IsJump)
	{	
		//�Ŀ���ŭ y�� ���� ����
		SetLocation(GetLocation() + (Vector3(0, -1, 0) * timeManager->GetDeltaTime() * _JumpPower)); 
		//�߷°��ӵ��� ���� ������
		_JumpPower -= 980 * timeManager->GetDeltaTime();
		if (GetLocation()._y >= 0) //���� ���̰� �ʿ���.. 
			_IsJump = false;
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
