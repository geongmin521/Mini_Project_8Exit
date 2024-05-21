#pragma once
#include "GameObject.h"
#include "Texture.h"

class CartoonObject :
    public GameObject
{
public:
    CartoonObject();
    ~CartoonObject();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

    float _RenderTime;
    int sceneIdx;
};

