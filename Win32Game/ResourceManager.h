#pragma once
#include "PathManager.h"
#include "Texture.h"
#include "globalheader.h"
#include "Vector3.h"
#include "Text.h"
#define resourceManager ResourceManager::GetInstance()

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance();
	static void DestroyInstance();

	Texture* GetTexture(const std::wstring& key, const std::wstring& path);
	void InsertDialog(const std::wstring& key, const std::wstring& value);
	void InsertMapObjectPos(const std::wstring& key, const std::vector<Vector3> value);
	const std::vector<Vector3>& GetMapPos(const std::wstring& key) { return _MapObjectPos[key]; }
	const std::wstring& GetDialog(const std::wstring& key) { return _Dialog[key]; }
	//getter 만들기
	Gdiplus::FontFamily& GetFont(int fonttype) { return pFontFamily[fonttype]; }
private:
	static ResourceManager* Instance;
	std::map<std::wstring, Texture*> _Textures;
	std::map<std::wstring, std::wstring> _Dialog;//대화
	std::map<std::wstring, std::vector<Vector3>> _MapObjectPos;//오브젝트 위치
	Gdiplus::FontFamily pFontFamily[2]; //리로스매니저에서 안될이유가 잇나?
};

