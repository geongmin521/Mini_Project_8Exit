#pragma once
#include "GameObject.h"
#include "Texture.h"

class ScareCrow_Rotate :
    public GameObject
{
public:
    ScareCrow_Rotate();
    ~ScareCrow_Rotate();

    virtual void Update();
    virtual void Render();

    virtual void ResetState();

    virtual void OnTriggerExit(Collider* collider);

private:
    Texture* _MyTex;

    bool _MoveDown = false;

    void ChangeImage();
};

