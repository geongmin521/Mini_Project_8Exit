#pragma once
#include "GameObject.h"
#include "Texture.h"

class House :
    public GameObject
{
public:
    House();
    ~House();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;
};

