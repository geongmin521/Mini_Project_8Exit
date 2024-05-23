#include "Player.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"
#include "Camera.h"
#include "Utility.h"


Player::Player() : _MyTex(nullptr), _JumpPower(1800), _Speed(500), _IsRun(false), _RunSpeed(250),
_Stamina(500.0f), _MaxStamina(500.0f), _StaminaDrain(100.0f), _StaminaRecovery(150.0f), _CurState(PlayerState::Idle), _Timer(0)
{
	_MyTex = resourceManager->GetTexture(L"Player", L"Image\\Player\\Idle\\Player_idle_0.png");
	_AnswerUI = resourceManager->GetTexture(L"Crayon", L"Image\\UI\\Crayon.png");
	GameObject::CreateCollider();
	GameObject::CreateAnimater(L"Player",0.1f);
	GetCollider()->SetScale(Vector3((float)_MyTex->Width() * 0.7f, (float)_MyTex->Height(), 0) * 0.70f);
	GameObject::SetName(L"Player");
	_StaminaBarMin = new StaminaBarMin;
	for (int i = 0; i < 4; i++)
	{
		AnswerCircle* answer = new AnswerCircle;
		answer->SetLocation(Vector3(-10000.0f, -10000.0f, 0));
		_Answer.push_back(answer);
		CreateObject(answer, LAYER_GROUP::INGAMEUI);

	}
	Circle = 4;
}

Player::~Player()
{
}

void Player::Update()
{
	Music::soundManager->ManageMusic(GetLocation());
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
			_IsHit = false;
			SceneReload(true);
		}
	}
	StaminaBarActions();

	Vector3 renderPosition = camera->GetRenderPos(GetLocation());
	if ((int)renderPosition._x - (_MyTex->Width() / 2) >= WindowWidth) {
		SceneReload(false);
	}
	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Update();
	}	
}

void Player::CheckCircle()
{
	if (_Timer <= 20) {
		return;
	}
	if (inputSystem->GetMouseButtonDown(0)) //왼쪽 클릭시
	{
		if (CheckPositionOnUI() == false && CheckMouseOnScreen()) {
			Music::soundManager->PlayMusic(Music::eSoundList::click, Music::eSoundChannel::Click);
			for (int i = 0; i < _Answer.size(); i++)
			{
				if (CheckPositionOnWorld(_Answer[i]) && _Answer[i]->Enable() == true)
				{
					_Answer[i]->SetEnable(false);//기존에 설치한 서클을 회수하기
					Circle++;
					return;//함수종료
				}
			}
			for (int i = 0; i < _Answer.size(); i++)
			{
				if (_Answer[i]->Enable() == false) //비활성화된 동그라미만 가능
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
	//ComponentRender();
}

void Player::Move()
{
	if (_Timer <= 20)
	{
		if (inputSystem->GetMouseButtonDown(0))
		{
			_Timer += 2.0f;
		}
		_Timer += timeManager->GetDeltaTime();
		return;
	}		

	float speed;
	Vector3 dir;
	if (inputSystem->isKey(VK_LEFT)|| inputSystem->isKey('A')) 
	{
		if (GetLocation()._x - _MyTex->Width() / 2 < -960)
			return;
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

	if (_IsRun) //스피드가 올라감
		speed = _Speed + _RunSpeed;
	else
		speed = _Speed;
	
	if (_IsWalk)
		SetLocation(GetLocation() + dir * timeManager->GetDeltaTime() * speed);

	//if (inputSystem->isKey('P'))
	//	_Speed = 5000;
	
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
		case PlayerState::Idle: //enum을 wstring으로 수동 변환
			stateStr = L"Idle";
			Music::soundManager->StopMusic(Music::eSoundChannel::Player);
			break;
		case PlayerState::Jump:
			stateStr = L"Jump";
			break;
		case PlayerState::Walk:
			stateStr = L"Walk";
			Music::soundManager->PlayMusic(Music::eSoundList::Player_Walk, Music::eSoundChannel::Player);
			break;
		case PlayerState::Hit:
			stateStr = L"Hit";
			GetAinmater()->SetIsLoop(false);
			Music::soundManager->PlayMusic(Music::eSoundList::Attacked_by_Objects, Music::eSoundChannel::Effect);

			break;
		case PlayerState::Run:
			stateStr = L"Run";
			Music::soundManager->PlayMusic(Music::eSoundList::Player_run, Music::eSoundChannel::Player);
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
	if (inputSystem->isKey(VK_LSHIFT) && _Stamina > 0 && _Runable&&_IsWalk)//스테이터스 
	{
		_IsRun = true;
	}
	else
	{
		
		_IsRun = false;
	}

	if (!inputSystem->isKey(VK_LSHIFT))
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
	// 스태미너바의 위치를 플레이어 위치로 업데이트
	if (_StaminaBarMin != nullptr) {
		_StaminaBarMin->SetLocation(Vector3(GetLocation()._x, GetLocation()._y - 230.0f, GetLocation()._z));
	}
}

void Player::OnCollisionEnter(Collider* collider)
{
	_IsHit = true;
	ChangeState(PlayerState::Hit); //애니메이션에서 루프인지 아닌지에따라 루프가끝나면 알림오기?
	

}

void Player::Init() //스테이지 리로드마다 상태 변경해주기
{
	for (int i = 0; i < 4; i++)
	{
		_Answer[i]->SetLocation(Vector3(-10000.0f, -10000.0f, 0));
		_Answer[i]->SetEnable(false);
	}
	Circle = 4;
	SetLocation(Vector3(-800, 230, 0));
	_Runable = true;
	_IsHit = false;
	_IsJump = false;
	ChangeState(PlayerState::Idle);
	GetAinmater()->SetIsEnd(false);
	GetAinmater()->SetIsLoop(true);
}
