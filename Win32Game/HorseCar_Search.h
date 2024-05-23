#pragma once
#include "GameObject.h"

class HorseCar_Search :
    public GameObject
{
public:
    HorseCar_Search();
    ~HorseCar_Search();

    virtual void Update();
    virtual void Render();

    //const Vector3& GetPlayerDir() { return _PlayerDir; }
    const Vector3& GetPlayerLocation() { return _PlayerLocation; }
    const void SetPlayerLocation(Vector3 pos) { _PlayerLocation = pos; }

    void OnTrigger(Collider* collider);
    void OnTriggerExit(Collider* collider);
private:
    Vector3 _PlayerLocation;

    friend class ScareCrow;
};

