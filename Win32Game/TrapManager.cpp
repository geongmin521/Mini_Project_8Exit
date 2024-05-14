#include "TrapManager.h"

TrapManager* TrapManager::Instance = nullptr;

TrapManager::TrapManager() : _TargetTrap(nullptr)
{
    CreateCollider();
}

TrapManager::~TrapManager()
{

}

TrapManager* TrapManager::GetInstance()
{
    if (Instance == nullptr) {
        Instance = new TrapManager;
    }
    return Instance;
}

void TrapManager::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

void TrapManager::Update()
{
}

void TrapManager::Render()
{
    ComponentRender();
}

void TrapManager::OnCollisionEnter(Collider* collider)
{
    _TargetTrap->SetEnable(true);
}

void TrapManager::InitTrap()
{
    //TODO: 함정을 초기화 할 때 랜덤 엑세스를 하여 정보를 받아와야 합니다.
    GetCollider()->SetScale(Vector3(50, 430, 0));
}
