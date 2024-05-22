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

    virtual void OnTriggerEnter(Collider* collider);

private:
    Texture* _MyTex;
};

