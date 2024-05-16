#pragma once
#include "PathManager.h"
#include "Texture.h"
#include "globalheader.h"
#include "Vector3.h"
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
	//getter �����
private:
	static ResourceManager* Instance;
	std::map<std::wstring, Texture*> _Textures;
	std::map<std::wstring, std::wstring> _Dialog;//��ȭ
	std::map<std::wstring, std::vector<Vector3>> _MapObjectPos;//������Ʈ ��ġ
};

