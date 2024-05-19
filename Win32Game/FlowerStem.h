#pragma once
#include "GameObject.h"
#include "Texture.h"

class FlowerStem :
    public GameObject
{
public:
    FlowerStem();
    ~FlowerStem();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;
};

