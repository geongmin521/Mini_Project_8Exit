#pragma once
#include "RenderSystem.h"
#include "Camera.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "GameObject.h"

class Animation
{
public: //�ҷ����°�?
	Animation(std::wstring name, float aniSpeed);
	~Animation();
	void Update();
	void Render();
	void ChangeState(std::wstring state);
	void GetTexture(std::wstring name, std::wstring state);
	void Flip(bool FilpX);
	void SetFlip();
	void FinalUpdate();
	void SetName(std::wstring name) { this->name = name; };
	void SetIsLoop(bool isLoop) { this->_IsLoop = isLoop; };
	bool GetIsLoop() { return _IsLoop; };
	bool GetIsEnd() { return _IsEnd; };
	bool SetIsEnd(bool _IsEnd) { return this->_IsEnd = _IsEnd; };
private:
	GameObject* _Owner;
	int CurFrame;		//���� �̹�����ȣ
	float _AnimationSpeed;
	float _AnimationTime; 
	std::wstring state; //���� ���´� enum���� ó�������� ���뼺�� ���� string ���� ó����
	std::wstring name; //���� ���´� enum���� ó�������� ���뼺�� ���� string ���� ó����
	std::vector<Texture*>  _AnimatedTexture; //�ؽ��� �迭
	bool _IsLoop;
	bool _IsEnd;
	friend class GameObject;
};

