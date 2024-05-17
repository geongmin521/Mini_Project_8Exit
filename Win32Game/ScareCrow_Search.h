#pragma once
#include "GameObject.h"

class ScareCrow_Search :
    public GameObject
{
public:
    ScareCrow_Search();
    ~ScareCrow_Search();

    virtual void Update();
    virtual void Render();

    const Vector3& GetPlayerDir() { return _PlayerDir; }
    const Vector3& GetPlayerLocation() { return _PlayerLocation; }

    void OnCollision(Collider* collider);
private:
    Vector3 _PlayerDir;
    Vector3 _PlayerLocation;

    friend class ScareCrow;
};

