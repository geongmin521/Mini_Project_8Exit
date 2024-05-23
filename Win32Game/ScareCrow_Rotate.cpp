#include "ScareCrow_Rotate.h"
#include "ResourceManager.h"
#include "Collider.h"

ScareCrow_Rotate::ScareCrow_Rotate() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"ScareCrow_Rotated", L"Image\\ScareCrow.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), 2300.0f, 0));
	GetCollider()->SetTrigger(true);
	SetName(L"ScareCrow_Rotated");
}

ScareCrow_Rotate::~ScareCrow_Rotate()
{
}

void ScareCrow_Rotate::Update()
{
	ChangeImage();

	if (_MoveDown == true) {
		SetLocation(GetLocation() + Vector3(0, 1, 0) * 3500.0f * timeManager->GetDeltaTime());
		if (GetLocation()._y >= 230) {
			Music::soundManager->PlayMusic(Music::eSoundList::Scarecrow_drop_from_Web, Music::eSoundChannel::Effect);
			_MoveDown = false;
		}
	}
}

void ScareCrow_Rotate::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);



	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	Matrix matrix;
	Gdiplus::PointF point((REAL)renderPosition._x, (REAL)renderPosition._y);
	matrix.RotateAt(REAL(-45), point);
	g.SetTransform(&matrix);

	if (CheckRenderPosition(startX, startY, endX, endY) == true) {
		g.DrawImage(_MyTex->GetImage(),
			startX, startY,
			endX, endY
		);
	}
	//ComponentRender();
}

void ScareCrow_Rotate::ResetState()
{
	_MoveDown = false;
	_MyTex = resourceManager->GetTexture(L"ScareCrow_Rotated", L"Image\\ScareCrow.png");
}

void ScareCrow_Rotate::OnTriggerExit(Collider* collider)
{
	if(GetMoveAnomalyState() == true && GetLocation()._y < 230.0f) {
		_MoveDown = true;
		
	}
}

void ScareCrow_Rotate::ChangeImage()
{
	if (GetDiffAnomalyState() == true) {
		std::wstring newKey = GetName() + L"_Anomaly";
		std::wstring newPath = L"Image\\" + newKey + L".png";
		_MyTex = resourceManager->GetTexture(newKey, newPath);
		SetDiffAnomalyState(false);
	}
}
