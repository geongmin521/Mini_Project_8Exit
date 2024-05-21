#pragma once
#include "GameObject.h"
#include "Texture.h"

enum class WITCH_STATE {
    IDLE
};
class WoodHouse :
    public GameObject
{
public:
    WoodHouse();
    ~WoodHouse();

    virtual void Update();
    virtual void Render();
    virtual void OnTriggerExit(Collider* collider);
    void ResetState();
        
private:
    Texture* _MyTex;
    WITCH_STATE _WitchState;
    float _CoolTime;
    float _WitchMoveSpeed;
    float _WaitTime;

};

