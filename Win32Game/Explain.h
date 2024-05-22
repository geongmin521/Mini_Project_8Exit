#pragma once
#include "GameObject.h"
class Explain :
    public GameObject
{
public:
    Explain();
    ~Explain();
    void Init(int stage);
    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;
};

