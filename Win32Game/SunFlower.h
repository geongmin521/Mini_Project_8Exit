#pragma once
#include "GameObject.h"
#include "Texture.h"

class SunFlower :
    public GameObject
{
public:
    SunFlower();
    ~SunFlower();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

};

