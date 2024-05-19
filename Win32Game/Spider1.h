#pragma once
#include "GameObject.h"
#include "Texture.h"

class Spider1 :
    public GameObject
{
public:
    Spider1();
    ~Spider1();

    virtual void Update();
    virtual void Render();

    void OnTriggerExit(Collider* collision);

private:
    Texture* _MyTex;

    Vector3 _PrevPosition;

    bool _MoveDown = false;
};

