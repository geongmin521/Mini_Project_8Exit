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

    void InitObjectPlace();
    bool NextStage(bool playerHit);

private:
    std::vector<GameObject*> _DefaultObjects;
    std::vector<std::vector<GameObject*>> _AnomalyObjects;
    std::map<int, bool> _CompleteTrap;
    int _PrevTrapIdx;
    int _AreaWidth;
    int _StageNum;
    const int _AreaCount = 6;
    int _AreaSettingState[6];
    std::pair<int, int> _StageSet[7] = { //  { 틀린 그림 개수, 활동 오브젝트 개수 }
        {0, 0},
        {0, 0},
        {1, 0},
        {2, 0},
        {1, 1},
        {2, 1},
        {2, 2}
    };
    int _AreaObjectCount[6] = {
        5,
        4,
        5,
        3,
        6,
        1
    };
    int _AreaMoveAnomalyCount[6] = {
        1,
        1,
        1,
        0,
        1,
        1
    };
    std::vector<std::pair<int, int>> _AnomalyIdx;
    
    void SetDiffAnomaly(int count);
    void SetMoveAnomaly(int count);
    void ResetObjectPos();
    bool CheckCorrect();
};

