#pragma once
#include "GameObject.h"
#include "Texture.h"

class MainBG :
    public GameObject
{
public:
    MainBG();
    ~MainBG();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

};

