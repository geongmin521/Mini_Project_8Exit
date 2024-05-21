#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "WoodHouse.h"
#include "Witch.h"
enum class WOODHOUSE2_STATE {
    IDLE
};
class WoodHouse2 :
    public GameObject
{
public:
    WoodHouse2();
    ~WoodHouse2();

    virtual void Update();
    virtual void Render();
    void OnTriggerExit(Collider* collider);

    void ResetState();
private:
    Texture* _MyTex;
    WOODHOUSE2_STATE _State;
    WoodHouse* _MyStem;
    Witch* _Witch;
    int index;
};

