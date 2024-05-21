#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject() : _Location(0, 0, 0), _Scale(0, 0, 0), _Name(L""), _Collider(nullptr), _FlipX(false)
{
}
GameObject::~GameObject() 
{
	if (_Collider != nullptr) {
		delete _Collider;
	}
}

void GameObject::CreateCollider()
{
	_Collider = new Collider;
	_Collider->_Owner = this;
}

void GameObject::CreateText(int fontSize,Color color, int fontType)
{
	_Text = new Text(fontSize, color, fontType);
	_Text->_Owner = this;
}

void GameObject::CreateAnimater(std::wstring name,float animationTime)
{
	_Animater = new Animation(name, animationTime);
	_Animater->_Owner = this;
}

void GameObject::FinalUpdate()
{
	if (_Collider != nullptr) {
		_Collider->FinalUpdate();
	}
	//if (_Animater != nullptr) {
	//	_Animater->FinalUpdate();
	//}
	//if (_Text != nullptr) {
	//	_Text->FinalUpdate();
	//}
}

void GameObject::ComponentRender()
{
	if (_Collider != nullptr) {
		_Collider->Render();
	}
	//if (_Animater != nullptr) {
	//	_Animater->Render();
	//}
	//if (_Text != nullptr) {
	//	_Text->Render();
	//}
}