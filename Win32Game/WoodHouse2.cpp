#include "ResourceManager.h"
#include "Collider.h"
#include "WoodHouse2.h"
WoodHouse2::WoodHouse2()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 3);
	index = dis(gen);


	// 7번 위치 ( 25920~ )
	SetLocation(Vector3(1000, 300, 0));
	CreateCollider();
	GetCollider()->SetScale(Vector3(300, 800, 0.0f));
	GetCollider()->SetTrigger(true);
	SetName(L"WoodHouse2");
	std::wstring path = L"Image\\House" + std::to_wstring(index) + L".png";
	_MyTex = resourceManager->GetTexture(L"WoodHouse" + std::to_wstring(index), path);
	_Witch = new Witch();
	_Witch->SetLocation(GetLocation());
	CreateObject(_Witch, LAYER_GROUP::MONSTER);
	_Witch->SetEnable(false);
}

WoodHouse2::~WoodHouse2()
{
}

void WoodHouse2::Update()
{

}

void WoodHouse2::Render()
{
	
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
}

void WoodHouse2::OnTriggerExit(Collider* collider) // 근처에 가면 문 열리는 이미지로 바꿈
{
	if (collider->GetOwnerObject()->GetName() == L"Player")
	{
		_MyTex = resourceManager->
			GetTexture(L"OpenWoodHouse" + std::to_wstring(index), L"Image\\OpenHouse" + std::to_wstring(index) + L".png");
		if (index==1)
		{
			_Witch->SetEnable(true);
		}
	}

}
//이미지 변경되는 오두막 만들기 철창없는 것, 지붕 색 다른 것, 연기 나는 것


void WoodHouse2::ResetState()
{
	//_MyTex[0] = resourceManager->GetTexture(L"WoodHouse", L"Image\\House.png");
}