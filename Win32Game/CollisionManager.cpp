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
    //모든 레이어 행을 돌면서 충돌중인지 체크 해야 합니다.
    //CollisionMatrix를 돌면서 & 면 CollisionGroupUpdate() 호출
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
    //여기서 충돌 매트릭스를 설정해야합니다. 작은값 : 행  //  큰 값 : 열
    _CollisionMatrix[(int)min(a, b)] ^= (1 << (int)max(a, b));
}

void CollisionManager::CollisionGroupUpdate(LAYER_GROUP a, LAYER_GROUP b)
{
    std::map<ULONGLONG, bool>::iterator it;

    //현재 씬에서 해당하는 그룹의 오브젝트들을 전부 가져와서 여기서 업데이트 해줍니다.
    //vector<GameObject*> 타입의 값을 받아와야 합니다.
    const Scene* curScene = SceneManager::GetInstance()->GetCurScene();
    
    const std::vector<GameObject*>& groupA = curScene->GetGroupObject(a);
    const std::vector<GameObject*>& groupB = curScene->GetGroupObject(b);

    //충돌체가 있는 오브젝트만 충돌을 검사해야 합니다.
    //동일한 충돌체가 서로 충돌을 감지하는 일이 없게 해야합니다.
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

            //이전 프레임의 충돌 정보를 가지고 와서 충돌 상태를 판단합니다.
            if (IsCollision(leftCol, rightCol)) {
                if (it->second == false) { // 방금 막 충돌 했다
                    if (!(groupA[i]->IsAlive() == false || groupB[j]->IsAlive() == false)) {
                        // 소멸예정인 오브젝트가 충돌이벤트를 발생시키려고 하려는 경우를 방지합니다.
                        leftCol->OnCollisionEnter(rightCol);
                        rightCol->OnCollisionEnter(leftCol);
                        it->second = true;
                    }
                }
                else { // 충돌 중이다.
                    if (groupA[i]->IsAlive() == false || groupB[j]->IsAlive() == false) {
                        // 충돌중인데 한쪽이 소멸될 예정이다.
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
    //TODO: 여기서 Collider끼리 충돌을 체크 해야 합니다. AABB 사용
    a->GetPos(); a->GetScale();
    b->GetPos(); b->GetScale();
    // 좌상 x, y  , 우하 x, y
    // AABB에서 충돌하지 않는 조건:  a.좌x > b.우x, a.우x < b.좌x, a.상y > b.하y, a.하y < b.상y
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
