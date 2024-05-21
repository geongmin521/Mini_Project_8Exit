#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "FadeIn.h"

class Button_Start :
    public GameObject
{
public:
    Button_Start();
    ~Button_Start();

    virtual void Update();
    virtual void Render();

    void OnClick();

private:
    Texture* _MyTex;
    Vector3 _Pos;
    FadeIn* _FadeIn;
    GameObject* _Parent;

    friend class LobbyUI;
};

