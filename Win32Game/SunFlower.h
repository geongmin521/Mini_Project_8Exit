#pragma once
#include "GameObject.h"
#include "Texture.h"

class SunFlower :
    public GameObject
{
public:
    SunFlower();
    ~SunFlower();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

    Vector3 _Dir = Vector3(0, 1, 0);
    Vector3 _StartPos;
    Vector3 _EndPos;
    float _MoveSpeed = 280.0f;
};