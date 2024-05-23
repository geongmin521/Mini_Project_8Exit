#include "WoodHouse.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Utility.h"
#include "Bonfire.h"
#include "Music.h"

WoodHouse::WoodHouse() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Cottage1", L"Image\\Cottage\\Idle\\Cottage_Idle_0.png");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 3);
	// 7번 위치 ( 25920~ )
	CreateCollider();
	GetCollider()->SetScale(Vector3(_MyTex->Width(), _MyTex->Height() , 0.0f)); //중심 +100과 플레이어 위치로부터 
	GetCollider()->SetTrigger(true);
	SetName(L"Cottage");
	StateChange(WITCH_STATE::IDLE);
	CreateAnimater(L"Cottage", 0.1f);
	_Bonfire = new Bonfire;
	CreateObject(_Bonfire,LAYER_GROUP::SEARCH);

	Init();
}

WoodHouse::~WoodHouse()
{
}

void WoodHouse::Init()
{
	//_WitchGimmick = (WITCH_GIMMICK)GetRandomNum((int)WITCH_GIMMICK::SIZE);
	if (GetMoveAnomalyState())
	{
		_WitchGimmick = WITCH_GIMMICK::WITCHOPEN;
		_MyTex = resourceManager->GetTexture(L"Cottage1", L"Image\\Cottage\\Idle\\Cottage_Idle_0.png");
	}
	else if (GetDiffAnomalyState())
	{
		int index = GetRandomNum(2);
		if (index == 0)
		{
			_WitchGimmick = WITCH_GIMMICK::VARIATION1;
			_MyTex = resourceManager->GetTexture(L"Cottage2", L"Image\\Cottage\\Cottage_Variation\\Cottage_Variation_2.png");
		}
		else
		{
			_WitchGimmick = WITCH_GIMMICK::VARIATION2;
			_MyTex = resourceManager->GetTexture(L"Cottage3", L"Image\\Cottage\\Cottage_Variation\\Cottage_Variation_3.png");
		}
		SetDiffAnomalyState(false);
	}
	else
	{
		_WitchGimmick = WITCH_GIMMICK::NORMAL;
		_MyTex = resourceManager->GetTexture(L"Cottage1", L"Image\\Cottage\\Idle\\Cottage_Idle_0.png");
	}
}

void WoodHouse::Update()
{
	GetAinmater()->Update();
	_Bonfire->SetLocation(GetLocation() + Vector3(-800, 200, 0));
	//_Bonfire->Update();
}



void WoodHouse::Render()
{
	if (_WitchState == WITCH_STATE::OPEN)
	{
		GetAinmater()->Render();
		return;
	}

	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

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
	ComponentRender();
	//_Bonfire->Render();
}

//void WoodHouse::ResetState()
//{
//	_MyStem->SetLocation(Vector3(GetLocation()._x, 100.0f, 0));
//	_MyStem->SetEnable(Enable());
//}
//마녀 나오는 오두막 만들기 기본적으로 둘다 적용되는 근처에 가면 문 열리는 기믹 만들기
// 마녀 등장
void WoodHouse::OnTrigger(Collider* collider) // 근처에 가면 문 열리는 이미지로 바꿈
{
	if (collider->GetOwnerObject()->GetName() == L"Player")
	{
		if (WITCH_GIMMICK::WITCHOPEN == _WitchGimmick&& collider->GetOwnerObject()->GetLocation()._x >= GetLocation()._x +100)
		{
			StateChange(WITCH_STATE::OPEN);			
		}
	}
}

void WoodHouse::ResetState()
{
	StateChange(WITCH_STATE::IDLE);
}

void WoodHouse::StateChange(WITCH_STATE witchState)
{
	if (this->_WitchState == witchState) //기존상태와 같으면 넘기기
		return;
	this->_WitchState = witchState;

	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		switch (_WitchState)
		{
		case WITCH_STATE::IDLE:
			stateStr = L"Idle";
			break;
		case WITCH_STATE::OPEN:
			GetAinmater()->SetIsLoop(false);
			Music::soundManager->PlayMusic(Music::eSoundList::Cottage_door_open, Music::eSoundChannel::Effect);//음악 재생
			stateStr = L"Open";
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}
