#pragma once
#include "GameObject.h"
#include "RenderSystem.h"
#include "Texture.h"

class StaminaBar : public GameObject
{
public:
    StaminaBar();
    ~StaminaBar();

    void Update();
    void Render();

private:
    float _currentStamina;
    float _maxStamina;
    int _barWidth;
    int _barHeight;
    Vector3 _position;
    Texture* _MaxTex;
    Texture* _StamiTex;
};
