#pragma once
#include "GameObject.h"
#include "Texture.h"

class SampleObject :
    public GameObject
{
public:
    SampleObject();
    ~SampleObject();

    void Update();
    void Render();

private:
    Texture* _MyTex;

    float _MoveSpeed = 10.0f;
};

