#pragma once
#include "GameObject.h"
#include "Texture.h"

class EndingImage :
    public GameObject
{
public:
    EndingImage();
    ~EndingImage();

    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;

    float _StoryTimer;
    float _Timer;
    bool _StartTimer = false;
};

