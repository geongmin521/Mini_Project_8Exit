#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "NPC.h"
enum class WITCH_STATE {
    IDLE,
    OPEN
};

enum class WITCH_GIMMICK {
    NORMAL,
    WITCHOPEN,
    VARIATION1,
    VARIATION2,
    SIZE
};
class WoodHouse :
    public GameObject
{
public:
    WoodHouse();
    ~WoodHouse();
    void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerExit(Collider* collider);
    void ResetState();
    void StateChange(WITCH_STATE witchState);
private:
    Texture* _MyTex;
    WITCH_STATE _WitchState;
    float _CoolTime;
    float _WitchMoveSpeed;
    float _WaitTime;
    int index;
    NPC* _Npc;
};

