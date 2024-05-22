#include "Credit.h"
#include "SceneManager.h"

Credit::Credit() : _ImgConnect(nullptr), _ImageIdx(0), _Idx(0), _Timer(0.0f), _GifNextTimer(0.03f)
{
	_ImgConnect = new Image(L"data\\Image\\Ending_Credit\\Credit.gif");
	_Count = _ImgConnect->GetFrameDimensionsCount();
	_DimentionIDs = new GUID[_Count];
	_ImgConnect->GetFrameDimensionsList(_DimentionIDs, _Count);
	_FrameCount = _ImgConnect->GetFrameCount(&_DimentionIDs[0]);
	
}

Credit::~Credit()
{
}

void Credit::Update()
{
	if (_ImageIdx < _FrameCount) {
		_Idx = _Count + _ImageIdx;
		_ImgConnect->SelectActiveFrame(&_DimentionIDs[0], _Idx);
		_GifNextTimer -= timeManager->GetDeltaTime();
		if (_GifNextTimer <= 0.0f) {
			_ImageIdx++;
			_GifNextTimer = 0.03f;
		}
	}
	else {
		camera->PlayEffect(FADE_IN);
		_StartTimer = true;
	}
	if (inputSystem->GetMouseButtonDown(0)) {
		camera->PlayEffect(FADE_IN);
		_StartTimer = true;
	}
	if (_StartTimer) {
		_Timer += timeManager->GetDeltaTime();
		if (_Timer >= 1.0f) {
			_StartTimer = false;
			_Timer = 0.0f;
			sceneManager->LoadScene(SCENE_LAYER::MAIN);
		}
	}
}

void Credit::Render()
{
	Graphics g(renderSystem->_backDC);

	g.DrawImage(_ImgConnect, 0, 0, _ImgConnect->GetWidth(), _ImgConnect->GetHeight());

}
