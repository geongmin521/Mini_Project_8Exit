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

    int _AreaSet[5] = {
            0b1001000101,
            0b0100010000,
            0b0010000010,
            0b0000100000,
            0b0000001000
    };

    void InitObjectPlace();
    int GetRandomNum(int size);
    void SetCompleteTrap(int idx);
    bool GetCompleteTrap(int idx);
    GameObject* GetAnomalyObject(int idx);
};

