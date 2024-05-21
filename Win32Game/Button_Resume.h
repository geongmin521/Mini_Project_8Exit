#pragma once
#include "GameObject.h"
#include "Texture.h"

class Button_Resume :
    public GameObject
{
public:
    Button_Resume();
    ~Button_Resume();

    virtual void Update();
    virtual void Render();

    void OnClick();

private:
    Texture* _MyTex;

    Vector3 _Pos;

    GameObject* _Parent;

    friend class PauseUI;
};

