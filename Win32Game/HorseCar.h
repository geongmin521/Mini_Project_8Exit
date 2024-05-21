#pragma once
#include "GameObject.h"
#include "HorseCar_Search.h"

enum class HorseCarState
{
    Normal,
    Cover,
    Silhouette,  
    Move,
    end
};


enum class HorseCarMoveState
{
    Idle,
    Move,
    Wait
};

class HorseCar :
    public GameObject
{
public:
    HorseCar();
    ~HorseCar();
    virtual void Update();
    virtual void Render();
    virtual void ResetState();
    void Init();
    void SetState(HorseCarMoveState _moveState);
    void OnCollisoinEnter(Collider* collider);
 
private:
    Texture* _MyTex; //텍스쳐를 두개 가질수있나?
    HorseCarState _State;
    HorseCarMoveState _MoveState;
    HorseCar_Search* _Search; 
    float _CoolTime;
    float _WaitTime;
    float _MoveSpeed;
    bool _isChase;  
    void ChangeImage();
};

