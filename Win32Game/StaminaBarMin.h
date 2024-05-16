#pragma once
#include "GameObject.h"
#include "RenderSystem.h"
#include "Texture.h"

class StaminaBarMin : public GameObject
{
public:
    StaminaBarMin();
    ~StaminaBarMin();

    void Update();
    void Render();

    void SetStaminaPercent(const float per) { _Percent = per; }

private:

    float _Percent;
    int _BarWidth;
    int _BarHeight;
    Vector3 _Position;
    Texture* _MaxTex;
};
