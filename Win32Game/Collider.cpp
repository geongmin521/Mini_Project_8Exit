#include "Collider.h"
#include "RenderSystem.h"
#include "Camera.h"

UINT Collider::_NextID = 0;

Collider::Collider() : _Owner(nullptr), _ID(_NextID++)
{
}

Collider::Collider(const Collider& origin) :
	_Owner(nullptr),
	_Offset(origin._Offset),
	_Scale(origin._Scale),
	_ID(_NextID++)
{

}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	Vector3 objpos = _Owner->GetLocation();
	_ColliderPos = objpos + _Offset;
}

void Collider::Render()
{
	HPEN greenpen = renderSystem->GetPen(PEN_TYPE::GREEN);
	HPEN oldpen = (HPEN)SelectObject(renderSystem->_backDC, greenpen);

	HBRUSH hollowbrush = renderSystem->GetBrush(BRUSH_TYPE::HOLLOW);
	HBRUSH oldbrush = (HBRUSH)SelectObject(renderSystem->_backDC, hollowbrush);

	Vector3 renderPos = camera->GetRenderPos(_ColliderPos);

	Rectangle(renderSystem->_backDC,
		(int)(renderPos._x - _Scale._x / 2.f),
		(int)(renderPos._y - _Scale._y / 2.f),
		(int)(renderPos._x + _Scale._x / 2.f),
		(int)(renderPos._y + _Scale._y / 2.f)
	);

	//Rectangle(renderSystem->_backDC,
	//	(int)(_ColliderPos._x - _Scale._x / 2.f),
	//	(int)(_ColliderPos._y - _Scale._y / 2.f),
	//	(int)(_ColliderPos._x + _Scale._x / 2.f),
	//	(int)(_ColliderPos._y + _Scale._y / 2.f)
	//	);

	SelectObject(renderSystem->_backDC, oldpen);
	SelectObject(renderSystem->_backDC, oldbrush);
	
}

void Collider::OnCollisionEnter(Collider* collider)
{
	_Owner->OnCollisionEnter(collider);
}

void Collider::OnCollision(Collider* collider)
{
	_Owner->OnCollision(collider);
}

void Collider::OnCollisionExit(Collider* collider)
{
	_Owner->OnCollisionExit(collider);
}

void Collider::OnTriggerEnter(Collider* collider)
{
	_Owner->OnTriggerEnter(collider);
}

void Collider::OnTrigger(Collider* collider)
{
	_Owner->OnTrigger(collider);
}

void Collider::OnTriggerExit(Collider* collider)
{
	_Owner->OnTriggerEnter(collider);
}
