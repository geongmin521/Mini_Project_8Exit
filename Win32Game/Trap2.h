#pragma once
#include "GameObject.h"
#include "Texture.h"

class Trap2 :
    public GameObject
{
public:
    Trap2();
    ~Trap2();

    virtual void Update();
    virtual void Render();

    virtual void OnCollision(Collider* collider);
    virtual void OnCollisionExit(Collider* collider);

private:
    Texture* _MyTex;

    bool _Chase = false;
};

