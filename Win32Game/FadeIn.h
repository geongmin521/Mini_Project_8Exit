#pragma once
#include "GameObject.h"
#include "Texture.h"

class FadeIn :
    public GameObject
{
public:
    FadeIn();
    ~FadeIn();

    virtual void Update();
    virtual void Render();

    void SetTargetScene(SCENE_LAYER layer) { _TargetScene = layer; }

private:
    Texture* _MyTex;

    SCENE_LAYER _TargetScene;

    float _Alpha;
};

