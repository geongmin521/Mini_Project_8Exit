#pragma once
#include "GameObject.h"
#include "Texture.h"

class PauseBG :
    public GameObject
{
public:
    PauseBG();
    ~PauseBG();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

    GameObject* _Parent;

    friend class PauseUI;
};

