#pragma once
#include "Scene.h"

class EndingScene :
    public Scene
{
public:
    EndingScene();
    ~EndingScene();

    virtual void Start();
    virtual void End();

private:

};

