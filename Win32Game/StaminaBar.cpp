#include "StaminaBar.h"
#include "RenderSystem.h"
#include "ResourceManager.h"


StaminaBar::StaminaBar() :_MaxTex(0)
{
    _MaxTex = resourceManager->GetTexture(L"StaminaBar", L"Image\\MaxTex.png");
   
}

StaminaBar::~StaminaBar()
{
}

void StaminaBar::Update()
{
}
void StaminaBar::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MaxTex->GetImage(),
		(int)renderPosition._x - (int)_MaxTex->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_MaxTex->GetImage()->GetHeight() / 2,
		(int)_MaxTex->GetImage()->GetWidth(), (int)_MaxTex->GetImage()->GetHeight()
	);
}
