#pragma once
#include "GameObject.h"

class PauseUI :
    public GameObject
{
public:
    PauseUI();
    ~PauseUI();

    virtual void Update();
    virtual void Render();

private:
    std::vector<GameObject*> _Child;
};

