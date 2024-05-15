#pragma once
#include "Scene.h"
#include "globalheader.h"


class TrapSceneTest :
    public Scene
{
public:
    TrapSceneTest();
    ~TrapSceneTest();

    virtual void Start();
    virtual void End();

private:
    std::vector<GameObject*> _ObjectPlace;
    std::vector<std::vector<GameObject*>> _AnomalyObjects;
    std::map<int, bool> _CompleteTrap;
    int _PrevTrapIdx;

    void InitObjectPlace();
    int GetRandomNum(int size);
    void SetCompleteTrap(int idx);
    bool GetCompleteTrap(int idx);
};

