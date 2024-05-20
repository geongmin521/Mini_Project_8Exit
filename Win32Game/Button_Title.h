#pragma once
#include "GameObject.h"
#include "Texture.h"

class Button_Title :
    public GameObject
{
public:
    Button_Title();
    ~Button_Title();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

    Vector3 _Pos;

    GameObject* _Parent;

    friend class PauseUI;
};

