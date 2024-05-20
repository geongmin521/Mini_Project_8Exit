#pragma once
#include "GameObject.h"
#include "Texture.h"

class Button_Pause :
    public GameObject
{
public:
    Button_Pause();
    ~Button_Pause();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;
    GameObject* _Parent;

    Vector3 _Pos;

    friend class MainGameUI;
};

