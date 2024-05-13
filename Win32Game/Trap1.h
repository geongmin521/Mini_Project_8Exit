#pragma once
#include "GameObject.h"
#include "Texture.h"

class Trap1 :
    public GameObject
{
public:
    Trap1();
    ~Trap1();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

    Vector3 _PrevPosition;
};

