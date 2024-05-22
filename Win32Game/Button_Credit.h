#pragma once
#include "GameObject.h"
#include "Texture.h"

class Button_Credit :
    public GameObject
{
public:
    Button_Credit();
    ~Button_Credit();

    virtual void Update();
    virtual void Render();

    void OnClick();

private:
    Texture* _MyTex;
    Vector3 _Pos;

    bool _StartTimer = false;
    float _Timer;
    GameObject* _Parent;

    friend class LobbyUI;
};

