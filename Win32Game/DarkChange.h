#include "GameObject.h"
#include "ResourceManager.h" 
#include "TimeSystem.h"
#include "RenderSystem.h"
#include <windows.h>
#include <gdiplus.h>
class DarkChange : public GameObject
{
public:
	DarkChange();
	~DarkChange();
	void Update();
	void Render();
	void Min();
	void WM_Paint();
	void die();
	
private:
	void CreateCachedBitmap();
	float _Min;
	float _Down;
	float _Max;
	Texture* _MyTex;
	Gdiplus::Bitmap* _MyTex;
	ResourceManager* ResourceManager;
	TimeManager* TimeManager;
	HBITMAP _hBitmap;
	HDC _hMemDC;
	Gdiplus::CachedBitmap* _cachedBitmap;
	Gdiplus::Graphics* _graphics;
	int _cachedBitmapWidth; // Cached bitmap width
	int _cachedBitmapHeight; // Cached bitmap height
	ULONG_PTR gdiplusToken; // GDI+ ÅäÅ«
};

