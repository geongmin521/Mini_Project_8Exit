#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "FlowerStem.h"

class SunFlower :
    public GameObject
{
public:
    SunFlower();
    ~SunFlower();

    virtual void Update();
    virtual void Render();

    virtual void ResetState();

private:
    Texture* _MyTex;
    FlowerStem* _MyStem;

    Vector3 _Dir = Vector3(0, 1, 0);
    float _StartPos;
    float _EndPos;
    float _MoveSpeed = 100.0f;
};