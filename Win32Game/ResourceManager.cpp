#include "ResourceManager.h"
#include "PathManager.h"

ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (auto i = _Textures.begin(); i != _Textures.end(); i++) {
        delete i->second;
    }
}

ResourceManager* ResourceManager::GetInstance()
{
    if (Instance == nullptr) {
        Instance = new ResourceManager;
    }
    return Instance;
}

void ResourceManager::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

Texture* ResourceManager::GetTexture(const std::wstring& key, const std::wstring& path)
{
    //���⿡ ��ο� key�� ��� �ͼ� key�� �ش��ϴ� �ؽ��İ� �����ϸ� �װ� ��ȯ�ϰ�, �ƴϸ� ���Ϸε��ؼ� �����ϰ� ��ȯ�Ѵ�.
    if (_Textures.find(key) != _Textures.end()) {
        return _Textures[key];
    }

    //std::wstring filepath = PathManager::GetInstance()->GetContentPath();
    //filepath += path;
    
    std::wstring filepath = L"data\\" + path;
    
    Texture* newTexture = new Texture;
    newTexture->Load(filepath);
    newTexture->SetKey(key);
    newTexture->SetPath(filepath);
    
    _Textures.insert({ key, newTexture });

    return newTexture;
}

void ResourceManager::InsertDialog(const std::wstring& key, const std::wstring& value)
{
    _Dialog.insert({ key, value });
}

void ResourceManager::InsertMapObjectPos(const std::wstring& key, const std::vector<Vector3> value)
{
    _MapObjectPos.insert({ key, value });
}
