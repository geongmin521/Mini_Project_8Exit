#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"
#include "Camera.h"
#include "Utility.h"
#include "Music.h"

Player::Player(): _MyTex(nullptr), _JumpPower(1800), _Speed(500), _IsRun(false), _RunSpeed(250),
				  _Stamina(10.0f), _MaxStamina(10.0f), _StaminaDrain(5.0f), _StaminaRecovery(10.0f), _CurState(PlayerState::Idle)
{
	_MyTex = resourceManager->GetTexture(L"Player", L"Image\\Player\\Idle\\Player_idle_0.png");
	_AnswerUI = resourceManager->GetTexture(L"Crayon", L"Image\\UI\\Crayon.png");
	GameObject::CreateCollider();
	GameObject::CreateAnimater(L"Player",0.1f);
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GameObject::SetName(L"Player");
	_StaminaBarMin = new StaminaBarMin;
	for (int i = 0; i < 3; i++)
	{
		AnswerCircle* answer = new AnswerCircle;
		_Answer.push_back(answer);
		CreateObject(answer, LAYER_GROUP::UI);

	}
	Circle = 3;
	_FadeIn = new FadeIn;
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
		CheckCircle();
		_StaminaBarMin->SetStaminaPercent(_Stamina / _MaxStamina);
	}
	else
	{
		if (GetAinmater()->GetIsEnd() == true)
		{
			SceneReload();
		}
	}
	StaminaBarActions();

	Vector3 renderPosition = camera->GetRenderPos(GetLocation());
	if ((int)renderPosition._x - (_MyTex->Width() / 2) >= WindowWidth) {
		_FadeIn->SetEnable(true);
	}
	if(_FadeIn->Enable())
		_FadeIn->Update();
	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Update();
	}	
}

void Player::CheckCircle()
{
	if (inputSystem->GetMouseButtonDown(0)) //���� Ŭ����
	{
		if (CheckPositionOnUI() == false && CheckMouseOnScreen()) {
			for (int i = 0; i < _Answer.size(); i++)
			{
				if (CheckPositionOnWorld(_Answer[i]) && _Answer[i]->Enable() == true)
				{
					_Answer[i]->SetEnable(false);//������ ��ġ�� ��Ŭ�� ȸ���ϱ�
					Circle++;
					return;//�Լ�����
				}
			}
			for (int i = 0; i < _Answer.size(); i++)
			{
				if (_Answer[i]->Enable() == false) //��Ȱ��ȭ�� ���׶�̸� ����
				{
					Circle--;
					_Answer[i]->SetEnable(true);
					_Answer[i]->SetLocation(GetWorldMousePos());
					break;
				}
			}
		}
	}
}

void Player::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Render();
	}
	if (_IsRun == true)
	{
		_StaminaBarMin->Render();
	}
	for (int i = 0; i < Circle; i++)
	{
		//Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
		Graphics g(renderSystem->_backDC);
		int sizeX = (int)_AnswerUI->Width();
		int sizeY = (int)_AnswerUI->Height();
		int posX = 0 + i * 60;
		int posY = WindowHeight - 200;
	
		g.DrawImage(_AnswerUI->GetImage(), posX , posY, sizeX , sizeY);
		
	}
	ComponentRender();
	if (_FadeIn->Enable())
		_FadeIn->Render();
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
		speed = _Speed + _RunSpeed;
	else
		speed = _Speed;
	
	if (_IsWalk)
		SetLocation(GetLocation() + dir * timeManager->GetDeltaTime() * speed);

	if (inputSystem->isKey('P'))
		_Speed = 5000;
	
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
			Music::soundManager->StopMusic(Music::eSoundChannel::Player);
			break;
		case PlayerState::Jump:
			stateStr = L"Jump";
			break;
		case PlayerState::Walk:
			stateStr = L"Walk";
			Music::soundManager->PlayMusic(Music::eSoundList::Player_Walk, Music::eSoundChannel::Player);//���� ���
			break;
		case PlayerState::Hit:
			stateStr = L"Hit";
			GetAinmater()->SetIsLoop(false);
			Music::soundManager->PlayMusic(Music::eSoundList::Attacked_by_Objects, Music::eSoundChannel::Effect);//���� ���

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
	if (_StaminaBarMin != nullptr) {
		_StaminaBarMin->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 230.0f, GetLocation()._z));
	}
}

void Player::OnCollisionEnter(Collider* collider)
{
	_IsHit = true;
	ChangeState(PlayerState::Hit); //�ִϸ��̼ǿ��� �������� �ƴ��������� ������������ �˸�����?
	

}

void Player::Init() //�������� ���ε帶�� ���� �������ֱ�
{
	_Runable = true;
	_IsHit = false;
	_IsJump = false;
	ChangeState(PlayerState::Idle);
	GetAinmater()->SetIsEnd(false);
	GetAinmater()->SetIsLoop(true);
}
