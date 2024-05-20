#include "SunFlower.h"
#include "ResourceManager.h"

SunFlower::SunFlower() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"SunFlower_Head", L"Image\\Flower_Head_Crop.png");
	_StartPos = 200.0f - (float)(WindowHeight / 2);
	_EndPos = 400.0f - (float)(WindowHeight / 2);
	SetName(L"SunFlower");
	_MyStem = new FlowerStem;
	_MyStem->SetLocation(Vector3(-10000, -10000, 0));
	CreateObject(_MyStem, LAYER_GROUP::BACKUNIT);
}

SunFlower::~SunFlower()
{
}

void SunFlower::Update()
{
	ChangeImage();

	_MyStem->SetLocation(Vector3(GetLocation()._x, 100.0f, 0));
	_MyStem->SetEnable(Enable());
	SetLocation(GetLocation() + _Dir * _MoveSpeed * timeManager->GetDeltaTime());
	if (GetLocation()._y > _EndPos) {
		_Dir = Vector3(0, -1, 0);
	}
	else if (GetLocation()._y < _StartPos) {
		_Dir = Vector3(0, 1, 0);
	}
}

void SunFlower::Render()
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
}

void SunFlower::ResetState()
{
	_MyStem->SetLocation(Vector3(GetLocation()._x, 100.0f, 0));
	_MyStem->SetEnable(Enable());
	_MyTex = resourceManager->GetTexture(L"SunFlower_Head", L"Image\\Flower_Head_Crop.png");
}

void SunFlower::ChangeImage()
{
	if (GetDiffAnomalyState() == true) {
		std::wstring newKey = GetName() + L"_Anomaly";
		std::wstring newPath = L"Image\\" + newKey + L".png";
		_MyTex = resourceManager->GetTexture(newKey, newPath);
		SetDiffAnomalyState(false);
	}
}
