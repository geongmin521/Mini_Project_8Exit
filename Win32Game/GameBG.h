#pragma once
#include "GameObject.h"
#include "Texture.h"

class GameBG :
    public GameObject
{
public:
    GameBG();
    ~GameBG();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;
};

