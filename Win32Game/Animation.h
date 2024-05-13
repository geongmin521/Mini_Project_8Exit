#pragma once
#include "Texture.h"
#include "globalheader.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Vector3.h"
#include "GameObject.h"

class Animation
{
public: //�ҷ����°�?
	Animation():_Owner(nullptr)
	{
		while(true)
		{
			int index = 0;
			Texture* tx = resourceManager->GetTexture(L"Charactor", L"Image\\alpha100_" + std::to_wstring(index) + L".png");
			if (tx == nullptr)
			{
				break;
			}
			else
			{			
				_AnimatedTexture.push_back(tx);
				index++;
			}			
		}
		
	}
	~Animation();

	void Render()
	{
		Vector3 renderPosition = camera->GetRenderPos(_Owner->GetLocation());
		
		Graphics g(renderSystem->_backDC);
		g.DrawImage(_AnimatedTexture[CurFrame]->GetImage(),
			(int)renderPosition._x - (int)_AnimatedTexture[CurFrame]->GetImage()->GetWidth() / 2,
			(int)renderPosition._y - (int)_AnimatedTexture[CurFrame]->GetImage()->GetHeight() / 2,
			(int)_AnimatedTexture[CurFrame]->GetImage()->GetWidth(), (int)_AnimatedTexture[CurFrame]->GetImage()->GetHeight()
		);
	}
private:
	GameObject* _Owner;
	int _FrameSize; //�̹� �迭�� ũ��
	int CurFrame; //�̹� �迭�� ũ��
	float _AnimationSpeed;// �ʿ��ϰ���?
	std::vector<Texture*>  _AnimatedTexture; //�ؽ��� �迭
};

