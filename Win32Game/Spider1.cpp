#include "Spider1.h"
#include "ResourceManager.h"
#include "Collider.h"

Spider1::Spider1() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Spider", L"Image\\Spider_Small.png");
	SetLocation(Vector3(800, -700, 0));
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), 2300.0f, 0.0f));
	SetName(L"Spider");
	GetCollider()->SetTrigger(true);
}

Spider1::~Spider1()
{

}

void Spider1::Update()
{
	ChangeImage();

	if (GetLocation()._y >= 0) {
		_MoveDown = false;
	}
	if (_MoveDown == true) {
		SetLocation(GetLocation() + Vector3(0, 1, 0) * 1200.0f * timeManager->GetDeltaTime());
		
	}
}

void Spider1::Render()
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

void Spider1::ResetState()
{
	_MoveDown = false;
	_MyTex = resourceManager->GetTexture(L"Spider", L"Image\\Spider_Small.png");
}

void Spider1::OnTriggerExit(Collider* collider) {
	if (GetLocation()._x < collider->GetOwnerObject()->GetLocation()._x) {
		_MoveDown = true;
	}
	
}

void Spider1::ChangeImage()
{
	if (GetDiffAnomalyState() == true) {
		std::wstring newKey = GetName() + L"_Anomaly";
		std::wstring newPath = L"Image\\" + newKey + L".png";
		_MyTex = resourceManager->GetTexture(newKey, newPath);
		SetDiffAnomalyState(false);
	}
}
