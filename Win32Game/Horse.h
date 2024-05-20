#pragma once
#include "GameObject.h"

enum class HorseState
{
    Normal,
    NoBaggage,
    Color
};

class Horse :
    public GameObject
{
public:
    Horse();
    ~Horse();
    void init(bool isTrap);
    virtual void Update();
    virtual void Render();
private:
    Texture* _MyTex;
    HorseState _State;
};

