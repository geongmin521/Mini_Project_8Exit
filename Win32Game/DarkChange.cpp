#include "DarkChange.h"
#include "TimeSystem.h"
#include "ResourceManager.h"
#include "InputSystem.h"
DarkChange::DarkChange() :_MyTex(nullptr), _Min(1.0f), _Down(1.0f / 60.0f)
{
	_MyTex = resourceManager->GetTexture(L"DarkChange", L"Image\\DarkChange.png");
}

DarkChange::~DarkChange()
{
}


void DarkChange::Update()
{
	if (inputSystem->isKey('V'))
	{
		Min();
	}
}

void DarkChange::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Gdiplus::Graphics g(renderSystem->_backDC);
	
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);

}
void DarkChange::Min()
{
	_Min -= _Down * timeManager->GetDeltaTime();

	if (_Min < 0.0f)
		_Min = 0.0f;
}
