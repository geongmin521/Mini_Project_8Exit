#include "HorseCar_Search.h"
#include "Collider.h"

HorseCar_Search::HorseCar_Search()
{
	CreateCollider();
	GetCollider()->SetScale(Vector3(3840.0f, 500.0f, 0));
	GetCollider()->SetTrigger(true);
}

HorseCar_Search::~HorseCar_Search()
{
}

void HorseCar_Search::Update()
{

}

void HorseCar_Search::Render()
{
	//ComponentRender();
}

void HorseCar_Search::OnTrigger(Collider* collider)
{
	//_PlayerDir = collider->GetOwnerObject()->GetDir();
	_PlayerLocation = collider->GetOwnerObject()->GetLocation();
}

void HorseCar_Search::OnTriggerExit(Collider* collider)
{
	
}


