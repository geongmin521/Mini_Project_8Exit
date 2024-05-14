#pragma once
#include "GameObject.h"  
#include "Texture.h"
class SignMonster : 
    public GameObject
{
public:
    SignMonster();
    ~SignMonster();

    void Update() override;
    void Render() override;

    void OnCollisionEnter(Collider* collider);

private:
    Texture* _MyTex;
};
