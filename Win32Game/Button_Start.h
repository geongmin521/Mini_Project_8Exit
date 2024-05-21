#pragma once
#include "GameObject.h"
#include "Texture.h"

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

    GameObject* _Parent;

    friend class LobbyUI;
};
