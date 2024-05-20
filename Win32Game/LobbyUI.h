#pragma once
#include "GameObject.h"


class LobbyUI :
    public GameObject
{
public:
    LobbyUI();
    ~LobbyUI();

    virtual void Update();
    virtual void Render();

private:
    std::vector<GameObject*> _Child;
};

