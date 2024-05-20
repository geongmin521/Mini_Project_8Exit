#include "HorseCar.h"
#include "Collider.h"
#include "Utility.h"
HorseCar::HorseCar() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Carriage", L"Image\\Carriage_Variation\\Carriage_Variation_0.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0.0f));
	_Search = new HorseCar_Search;
	_Search->SetLocation(GetLocation()); //������ġ�� ����
	CreateObject(_Search, LAYER_GROUP::SEARCH);
	SetName(L"HorseCar");

	GetCollider()->SetTrigger(true);
	_isChase = false;
	_CoolTime = 2;
	_WaitTime = 1;

	_MoveSpeed = 300;
	_MoveState = HorseCarMoveState::Idle;

	Init(6, true);//�׽�Ʈ�� 
}

HorseCar::~HorseCar()
{
}

void HorseCar::Update() //�ٸ� Ŭ������ ���� ������ѵ�.. ���θ������.. �̰͵��� ����ĥ������ �ʾҾ�����?
{
	//�Ʒ��� ��� �ڵ�� �����̴� �����϶��� �۵��ϴ°���?
	if (HorseCarState::Move != _State)
		return;
	_Search->SetLocation(GetLocation());
	
	if (_MoveState == HorseCarMoveState::Idle) {
		if (_Search->GetPlayerLocation()._x - GetLocation()._x >= 640.0f) {
			SetState(HorseCarMoveState::Move);
		}
	}
	else if (_MoveState == HorseCarMoveState::Move) {

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
	if (GetAinmater() != nullptr)
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

void HorseCar::Init(int stage, bool isTrap)
{
	if (isTrap)//��������ƴ����� ���� ���� �̱�
	{
		//�������� 6���̸� move ���±��� ����������
		_State = stage == 6 ? (HorseCarState)(GetRandomNum(3) + 1) : (HorseCarState)(GetRandomNum(2) + 1);
	}
	else
	{
		_State = HorseCarState::Normal;
	}
	std::wstring path;
	//_State = HorseCarState::Move;
	if (_State == HorseCarState::Move) //���°� �̵��϶� �ִϸ��̼� �Ҵ��ϱ�
	{
		GameObject::CreateAnimater(L"Carriage", 0.1f);
		GetAinmater()->ChangeState(L"Idle");
		path = L"Carriage_Variation\\Carriage_Variation_0.png";
	}
	else
	{
		path = L"Carriage_Variation\\Carriage_Variation_" + std::to_wstring((int)_State) + L".png";
	}

	_MyTex = resourceManager->GetTexture(L"Carriage", L"Image\\" + path);
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
			break;
		case HorseCarMoveState::Wait:
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
	Init(6,true);// �������� ��ȣ�� �޾ƿ;��ϴµ�.. 
}
