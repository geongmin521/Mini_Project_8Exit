#include "Horse.h"
#include "Collider.h"

Horse::Horse() //생각해보니 이부분좀 더 얘기 해야겠는데?
{
	init(true); //테스용init
	
}

Horse::~Horse()
{
}

void Horse::init(bool isTrap)
{
	if (isTrap)//기믹인지아닌지에 따라 상태 뽑기
	{
		//스테이지 6번이면 move 상태까지 뽑을수있음
		_State = (HorseState)(GetRandomNum(2)+1);
	}
	else
	{
		_State = HorseState::Normal;
	}

	std::wstring path = L"Image\\Horse_Variation\\Horse_Variation_" + std::to_wstring((int)_State) + L".png"; //이미 변경 기믹
	_MyTex = resourceManager->GetTexture(L"Horse", path);
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetCollider()->SetTrigger(true);
	
}

void Horse::Update()
{
	if (GetDiffAnomalyState() == true) {
		init(true);
		SetDiffAnomalyState(false);
	}
}

void Horse::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	if (_MyTex->GetFlipX() != GetFlipX()) {
		_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);
		_MyTex->SetFlipX(GetFlipX());
	}

	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	if (CheckRenderPosition(startX, startY, endX, endY) == true) {
		g.DrawImage(_MyTex->GetImage(),
			startX, startY,
			endX, endY
		);
	}
}
