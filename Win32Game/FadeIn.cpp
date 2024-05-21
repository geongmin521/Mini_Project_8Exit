#include "FadeIn.h"
#include "SceneManager.h"

FadeIn::FadeIn() : _MyTex(nullptr), _Alpha(0.0f), _TargetScene(SCENE_LAYER::END)
{
    _MyTex = resourceManager->GetTexture(L"Fade", L"Image\\FadeObject.png");
    SetEnable(false);
}

FadeIn::~FadeIn()
{
}

void FadeIn::Update()
{
    _Alpha += 1.0f * timeManager->GetDeltaTime();
    if (_Alpha >= 1.0f) {
        if (_TargetScene == SCENE_LAYER::END) {
            SceneReload();
        }
        else {
            sceneManager->LoadScene(_TargetScene);
        }
        SetEnable(false);
        _Alpha = 0.0f;
    }
}

void FadeIn::Render()
{
    ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, _Alpha, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
    ImageAttributes imageAttribute;
    imageAttribute.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

    Graphics g(renderSystem->_backDC);

    int startX = (int)0;
    int startY = (int)0;
    int endX = (int)_MyTex->Width();
    int endY = (int)_MyTex->Height();

    g.DrawImage(_MyTex->GetImage(), Gdiplus::Rect(0, 0, endX, endY), 0, 0, endX, endY, UnitPixel, &imageAttribute);
}
