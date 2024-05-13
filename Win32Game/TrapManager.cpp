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
    //TODO: ������ �ʱ�ȭ �� �� ���� �������� �Ͽ� ������ �޾ƿ;� �մϴ�.
    GetCollider()->SetScale(Vector3(50, 430, 0));
}
