#include "WoodHouse.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Utility.h"
#include "Bonfire.h"
WoodHouse::WoodHouse() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Cottage1", L"Image\\Cottage\\Idle\\Cottage_Idle_0.png");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 3);
	// 7번 위치 ( 25920~ )
	SetLocation(Vector3(1000, 300, 0));
	CreateCollider();
	GetCollider()->SetScale(Vector3(300, 550, 0.0f));
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
	_WitchGimmick = (WITCH_GIMMICK)GetRandomNum((int)WITCH_GIMMICK::SIZE);
	switch (_WitchGimmick)
	{//기획한테요구하기 , 이미지3개, 혹은 마녀가 문여는거 
	case WITCH_GIMMICK::NORMAL:
		_MyTex = resourceManager->GetTexture(L"Cottage1", L"Image\\Cottage\\Idle\\Cottage_Idle_0.png");
		break;
	case WITCH_GIMMICK::WITCHOPEN:
		_MyTex = resourceManager->GetTexture(L"Cottage1", L"Image\\Cottage\\Idle\\Cottage_Idle_0.png");
		break;
	case WITCH_GIMMICK::VARIATION1:
		//문안열리고 그냥 이미지교체
		_MyTex = resourceManager->GetTexture(L"Cottage2", L"Image\\Cottage\\Cottage_Variation\\Cottage_Variation_2.png");
		break;
	case WITCH_GIMMICK::VARIATION2:
		_MyTex = resourceManager->GetTexture(L"Cottage3", L"Image\\Cottage\\Cottage_Variation\\Cottage_Variation_3.png");
		break;
	}
}

void WoodHouse::Update()
{
	GetAinmater()->Update();
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
void WoodHouse::OnTriggerExit(Collider* collider) // 근처에 가면 문 열리는 이미지로 바꿈
{

	
	if (collider->GetOwnerObject()->GetName() == L"Player")
	{
		if (WITCH_GIMMICK::WITCHOPEN == _WitchGimmick)
		{
		StateChange(WITCH_STATE::OPEN);
		//GetAinmater()
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
			stateStr = L"Open";
			break;
		}
		GetAinmater()->ChangeState(stateStr);
	}
}
