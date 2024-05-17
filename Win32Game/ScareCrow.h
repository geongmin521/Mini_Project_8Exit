#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "ScareCrow_Search.h"

enum class SCARECROW_STATE {
    IDLE,
    WAIT,
    CHASE,
};

class ScareCrow :
    public GameObject
{
public:
    ScareCrow();
    ~ScareCrow();

    virtual void Update();
    virtual void Render();

    void OnTriggerEnter(Collider* collider);

private:
    Texture* _MyTex;
    SCARECROW_STATE _State;

    ScareCrow_Search* _Search;

    float _MoveSpeed;
    float _CoolTime;
    float _WaitTime;

    friend class TrapSceneTest;
};

