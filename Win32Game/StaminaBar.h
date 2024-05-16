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
    Texture* _MaxTex;
};
