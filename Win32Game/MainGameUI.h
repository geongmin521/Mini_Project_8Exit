#pragma once
#include "GameObject.h"


class MainGameUI :
    public GameObject
{
public:
    MainGameUI();
    ~MainGameUI();

    virtual void Update();
    virtual void Render();

private:
    std::vector<GameObject*> _Child;
};

