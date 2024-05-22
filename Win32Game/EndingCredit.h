#pragma once
#include "Scene.h"

class EndingCredit :
    public Scene
{
public:
    EndingCredit();
    ~EndingCredit();

    virtual void Start();
    virtual void End();
private:

};

