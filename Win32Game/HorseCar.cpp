#include "HorseCar.h"
#include "Collider.h"
#include "Utility.h"


HorseCar::HorseCar() : _MyTex(nullptr)
{
	SetName(L"HorseCar");
	_MyTex = resourceManager->GetTexture(L"Carriage", L"Image\\Carriage_Variation\\Carriage_Variation_0.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0.0f));
	GetCollider()->SetTrigger(true);
	_Search = new HorseCar_Search;
	_Search->SetLocation(GetLocation()); //������ġ�� ����
	CreateObject(_Search, LAYER_GROUP::SEARCH);
	_isChase = false;
	_CoolTime = 2;
	_WaitTime = 1;
	_MoveSpeed = 700;
	GameObject::CreateAnimater(L"Carriage", 0.1f);
	GetAinmater()->ChangeState(L"Idle"); //�ִϸ�����
}

HorseCar::~HorseCar()
{
}

void HorseCar::Update() //�ٸ� Ŭ������ ���� ������ѵ�.. ���θ������.. �̰͵��� ����ĥ������ �ʾҾ�����?
{
	//ChangeImage();
	//�Ʒ��� ��� �ڵ�� �����̴� �����϶��� �۵��ϴ°���?
	if (HorseCarState::Move != _State)
		return;
	_Search->SetLocation(GetLocation());
	
	if (_MoveState == HorseCarMoveState::Idle) {
		if (_Search->GetPlayerLocation()._x - GetLocation()._x >= 640.0f) {
			Music::soundManager->PlayMusic(Music::eSoundList::Carriage_rush, Music::eSoundChannel::HorseCarRush);
			SetState(HorseCarMoveState::Move);
		}
	}
	else if (_MoveState == HorseCarMoveState::Move) {
		GetCollider()->SetTrigger(false);
		if (abs(_Search->GetPlayerLocation()._x - GetLocation()._x) < 10) //�����Ÿ� �����̸� ������ �ʴ´�.
			return;
		Vector3 dir = _Search->GetPlayerLocation()._x - GetLocation()._x > 0 ? Vector3(1, 0, 0) : Vector3(-1, 0, 0);
		SetLocation(GetLocation() + dir * _MoveSpeed * timeManager->GetDeltaTime());
		_CoolTime -= timeManager->GetDeltaTime();
		if (_CoolTime <= 0.0f) {
			SetState(HorseCarMoveState::Wait);
			_CoolTime = 2;
		}
	}
	else if (_MoveState == HorseCarMoveState::Wait) {
		_WaitTime -= timeManager->GetDeltaTime();
		if (_WaitTime <= 0.0f) {
			SetState(HorseCarMoveState::Move);
			_WaitTime = 1;
		}
	}

	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Update();
	}
}

void HorseCar::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	if (GetAinmater() != nullptr && _State == HorseCarState::Move)
	{
		GetAinmater()->Render();
	}
	else
	{
		Graphics g(renderSystem->_backDC);

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
	_Search->Render();
}

void HorseCar::ResetState()
{
	//�̰Ŵ� �־���ϳ�? �𸣰ٴ�.
}

void HorseCar::Init()
{
	_MoveState = HorseCarMoveState::Idle;
	GetCollider()->SetTrigger(true);
	_Search->SetPlayerLocation(Vector3(-10000, -10000, 0));
	if (GetMoveAnomalyState())
	{			
		_State = HorseCarState::Move;
		SetMoveAnomalyState(false);
	}
	else if(GetDiffAnomalyState())
	{
		_State = (HorseCarState)(GetRandomNum(2) + 1);
		SetDiffAnomalyState(false);
	}
	else
	{
		_State = HorseCarState::Normal;
	}
	std::wstring path;
	
	if (_State == HorseCarState::Move) //���°� �̵��϶� �ִϸ��̼� �Ҵ��ϱ�
	{	
		GetCollider()->SetScale(Vector3((float)_MyTex->Width() -440, (float)_MyTex->Height(), 0.0f));
		GetCollider()->SetOffset(Vector3(-220,0,0));
		path = L"Carriage_Variation\\Carriage_Variation_0.png";
	}
	else
	{
		path = L"Carriage_Variation\\Carriage_Variation_" + std::to_wstring((int)_State) + L".png";
	}
	GetAinmater()->ChangeState(L"Idle"); //�ִϸ�����
	_MyTex = resourceManager->GetTexture(L"Carriage" + std::to_wstring((int)_State), L"Image\\" + path);
}

void HorseCar::SetState(HorseCarMoveState _moveState)
{
	if (_MoveState == _moveState) //�������¿� ������ �ѱ��
		return;
	_MoveState = _moveState;
	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (_MoveState)
		{
		case HorseCarMoveState::Idle: //enum�� wstring���� ���� ��ȯ
			stateStr = L"Idle";
			break;
		case HorseCarMoveState::Move: 
			stateStr = L"Move";

			Music::soundManager->PlayMusic(Music::eSoundList::Carriage_moving, Music::eSoundChannel::HorseCarMove);
			break;
		case HorseCarMoveState::Wait:
			Music::soundManager->StopMusic(Music::eSoundChannel::HorseCarMove);
			stateStr = L"Wait";
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}

void HorseCar::OnCollisoinEnter(Collider* collider)
{
	//�÷��̾ �׿����ҵ�?
}

void HorseCar::ChangeImage()
{
	//if (GetDiffAnomalyState() == true || GetMoveAnomalyState() == true) {
	//	Init();// �������� ��ȣ�� �޾ƿ;��ϴµ�.. 
	//	SetDiffAnomalyState(false);
	//}
}
