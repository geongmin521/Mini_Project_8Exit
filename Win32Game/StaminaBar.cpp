#include "StaminaBar.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
StaminaBar::StaminaBar() :_MaxTex(0), _StamiTex(0), _currentStamina(0), _maxStamina(0), _barWidth(200), _barHeight(20), _position(0, 0, 0)
{
    _MaxTex = resourceManager->GetTexture(L"StaminaBar", L"Image\\MaxTex.png");
    _StamiTex = resourceManager->GetTexture(L"StaminaBar2", L"Image\\MaxTex2.png");
}

StaminaBar::~StaminaBar()
{
}

void StaminaBar::Update()
{
   
}

void StaminaBar::Render()
{
    // 현재 스태미너와 최대 스태미너에 기반하여 스태미너 바의 너비를 계산합니다.
    float barPercentage = _currentStamina / _maxStamina;
    int currentBarWidth = static_cast<int>(_barWidth * barPercentage);

  
}
