#pragma once
#include "GameObject.h"
#include "Texture.h"

class WoodHouse :
    public GameObject
{
public:
    WoodHouse();
    ~WoodHouse();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

};

