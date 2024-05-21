#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "FadeIn.h"

class Button_Title :
    public GameObject
{
public:
    Button_Title();
    ~Button_Title();

    virtual void Update();
    virtual void Render();

    void OnClick();

private:
    Texture* _MyTex;

    Vector3 _Pos;
    FadeIn* _FadeIn;

    GameObject* _Parent;

    friend class PauseUI;
};

