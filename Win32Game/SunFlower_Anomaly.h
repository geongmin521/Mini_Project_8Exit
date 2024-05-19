#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "FlowerStem.h"

class SunFlower_Anomaly :
    public GameObject
{
public:
    SunFlower_Anomaly();
    ~SunFlower_Anomaly();

    virtual void Update();
    virtual void Render();

    virtual void ResetState();

private:
    Texture* _MyTex;
    FlowerStem* _MyStem;

    Vector3 _Dir = Vector3(0, 1, 0);
    float _StartPos;
    float _EndPos;
    float _MoveSpeed = 200.0f;
};

