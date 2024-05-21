#include "StaminaBarMin.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"

StaminaBarMin::StaminaBarMin() :_MaxTex(0), _BarWidth(200), _BarHeight(20), _Position(0, 0, 0), _Percent(0.0f)
{
	_MaxTex = resourceManager->GetTexture(L"StaminaBarMin", L"Image\\UI\\Stamina.png");
}

StaminaBarMin::~StaminaBarMin()
{
}

void StaminaBarMin::Update()
{

}

void StaminaBarMin::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MaxTex->GetImage(),
		(int)renderPosition._x - (int)_MaxTex->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_MaxTex->GetImage()->GetHeight() / 2,
		(int)(_MaxTex->GetImage()->GetWidth()* _Percent), (int)_MaxTex->GetImage()->GetHeight()
	);

}
