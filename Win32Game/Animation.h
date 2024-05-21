#pragma once
#include "RenderSystem.h"
#include "Camera.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "GameObject.h"

class Animation
{
public: //불러오는거?
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
	int CurFrame;		//현재 이미지번호
	float _AnimationSpeed;
	float _AnimationTime; 
	std::wstring state; //보통 상태는 enum으로 처리하지만 범용성을 위해 string 으로 처리함
	std::wstring name; //보통 상태는 enum으로 처리하지만 범용성을 위해 string 으로 처리함
	std::vector<Texture*>  _AnimatedTexture; //텍스쳐 배열
	bool _IsLoop;
	bool _IsEnd;
	friend class GameObject;
};

