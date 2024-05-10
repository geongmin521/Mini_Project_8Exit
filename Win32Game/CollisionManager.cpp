#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "globalheader.h"


CollisionManager* CollisionManager::Instance = nullptr;

CollisionManager::CollisionManager() : _CollisionMatrix{}
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
    if (Instance == nullptr) {
        Instance = new CollisionManager;
    }
    return Instance;
}

void CollisionManager::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
    //��� ���̾� ���� ���鼭 �浹������ üũ �ؾ� �մϴ�.
    //CollisionMatrix�� ���鼭 & �� CollisionGroupUpdate() ȣ��
    for (int row = 0; row < (int)LAYER_GROUP::END; row++) {
        for (int col = row; col < (int)LAYER_GROUP::END; col++) {
            if (_CollisionMatrix[row] & (1 << col)) {
                CollisionGroupUpdate((LAYER_GROUP)row, (LAYER_GROUP)col);
            }
        }
    }

}

void CollisionManager::CheckGroup(LAYER_GROUP a, LAYER_GROUP b)
{
    //���⼭ �浹 ��Ʈ������ �����ؾ��մϴ�. ������ : ��  //  ū �� : ��
    _CollisionMatrix[(int)min(a, b)] ^= (1 << (int)max(a, b));
}

void CollisionManager::CollisionGroupUpdate(LAYER_GROUP a, LAYER_GROUP b)
{
    std::map<ULONGLONG, bool>::iterator it;

    //���� ������ �ش��ϴ� �׷��� ������Ʈ���� ���� �����ͼ� ���⼭ ������Ʈ ���ݴϴ�.
    //vector<GameObject*> Ÿ���� ���� �޾ƿ;� �մϴ�.
    const Scene* curScene = SceneManager::GetInstance()->GetCurScene();
    
    const std::vector<GameObject*>& groupA = curScene->GetGroupObject(a);
    const std::vector<GameObject*>& groupB = curScene->GetGroupObject(b);

    //�浹ü�� �ִ� ������Ʈ�� �浹�� �˻��ؾ� �մϴ�.
    //������ �浹ü�� ���� �浹�� �����ϴ� ���� ���� �ؾ��մϴ�.
    for (int i = 0; i < groupA.size(); i++) {
        if (groupA[i]->GetCollider() == nullptr) continue;
        for (int j = 0; j < groupB.size(); j++) {
            if (groupB[j]->GetCollider() == nullptr || groupA[i] == groupB[j]) {
                continue;
            }

            Collider* leftCol = groupA[i]->GetCollider();
            Collider* rightCol = groupB[j]->GetCollider();

            COLLIDER_ID ID;
            ID.L_ID = leftCol->GetColliderID();
            ID.R_ID = rightCol->GetColliderID();
            
            it = _CollisionInfo.find(ID.ID);
            if (it == _CollisionInfo.end()) {
                _CollisionInfo.insert({ ID.ID, false });
                it = _CollisionInfo.find(ID.ID);
            }

            //���� �������� �浹 ������ ������ �ͼ� �浹 ���¸� �Ǵ��մϴ�.
            if (IsCollision(leftCol, rightCol)) {
                if (it->second == false) { // ��� �� �浹 �ߴ�
                    if (!(groupA[i]->IsAlive() == false || groupB[j]->IsAlive() == false)) {
                        // �Ҹ꿹���� ������Ʈ�� �浹�̺�Ʈ�� �߻���Ű���� �Ϸ��� ��츦 �����մϴ�.
                        leftCol->OnCollisionEnter(rightCol);
                        rightCol->OnCollisionEnter(leftCol);
                        it->second = true;
                    }
                }
                else { // �浹 ���̴�.
                    if (groupA[i]->IsAlive() == false || groupB[j]->IsAlive() == false) {
                        // �浹���ε� ������ �Ҹ�� �����̴�.
                        leftCol->OnCollisionExit(rightCol);
                        rightCol->OnCollisionExit(leftCol);
                        it->second = false;
                    }
                    else {
                        leftCol->OnCollision(rightCol);
                        rightCol->OnCollision(leftCol);
                    }
                }
            }
            else {
                if (it->second == true) {
                    leftCol->OnCollisionExit(rightCol);
                    rightCol->OnCollisionExit(leftCol);
                    it->second = false;
                }
            }
        }
    }
}

bool CollisionManager::IsCollision(Collider* a, Collider* b)
{
    //TODO: ���⼭ Collider���� �浹�� üũ �ؾ� �մϴ�. AABB ���
    a->GetPos(); a->GetScale();
    b->GetPos(); b->GetScale();
    // �»� x, y  , ���� x, y
    // AABB���� �浹���� �ʴ� ����:  a.��x > b.��x, a.��x < b.��x, a.��y > b.��y, a.��y < b.��y
    Vector3 LeftA = a->GetPos() - (a->GetScale() / 2);
    Vector3 RightA = a->GetPos() + (a->GetScale() / 2);
    Vector3 LeftB = b->GetPos() - (b->GetScale() / 2);
    Vector3 RightB = b->GetPos() + (b->GetScale() / 2);

    if (LeftA._x > RightB._x ||
        RightA._x < LeftB._x ||
        LeftA._y > RightB._y ||
        RightA._y < LeftB._y) 
    {
        return false;
    }

    return true;
}
