#pragma once
#include "GameObject.h"
#include "Texture.h"

class Spider2 :
    public GameObject
{
public:
    Spider2();
    ~Spider2();

    virtual void Update();
    virtual void Render();

    virtual void OnCollisionExit(Collider* collider);

private:
    Texture* _MyTex;

    bool _MoveDown = false;
};

