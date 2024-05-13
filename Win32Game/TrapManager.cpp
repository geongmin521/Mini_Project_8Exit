#include "TrapManager.h"

TrapManager* TrapManager::Instance = nullptr;

TrapManager::TrapManager()
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
}

void TrapManager::InitTrap()
{
    //TODO: ������ �ʱ�ȭ �� �� ���� �������� �Ͽ� ������ �޾ƿ;� �մϴ�.
}
