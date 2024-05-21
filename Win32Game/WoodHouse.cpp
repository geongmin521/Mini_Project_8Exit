#include "WoodHouse.h"
#include "ResourceManager.h"
#include "Collider.h"


WoodHouse::WoodHouse() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"WoodHouse1", L"Image\\House1.png");
	// 7번 위치 ( 25920~ )
	SetLocation(Vector3(1000, 300, 0));
	CreateCollider();
	GetCollider()->SetScale(Vector3(300, 550, 0.0f));
	GetCollider()->SetTrigger(true);
	SetName(L"WoodHouse");

}

WoodHouse::~WoodHouse()
{
}

void WoodHouse::Update()
{

}

void WoodHouse::Render()
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
		_MyTex = resourceManager->GetTexture(L"OpenWoodHouse1", L"Image\\OpenHouse1.png");
	}
}

void WoodHouse::ResetState()
{
	_WitchState = WITCH_STATE::IDLE;
	_MyTex = resourceManager->GetTexture(L"WoodHouse1", L"Image\\House1.png");
}