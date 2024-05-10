#pragma once
#include "GameObject.h"
#include "Texture.h"

class Monster :
    public GameObject
{
public:
    Monster();
    ~Monster();

    void Update();
    void Render();

    void OnCollisionEnter(Collider* collider);

private:
    Texture* _MyTex;
};

