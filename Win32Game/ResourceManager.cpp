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
    //여기에 경로와 key를 들고 와서 key에 해당하는 텍스쳐가 존재하면 그결 반환하고, 아니면 파일로드해서 저장하고 반환한다.
    if (_Textures.find(key) != _Textures.end()) {
        return _Textures[key];
    }

    std::wstring filepath = PathManager::GetInstance()->GetContentPath();
    filepath += path;
    
    Texture* newTexture = new Texture;
    newTexture->Load(filepath);
    newTexture->SetKey(key);
    newTexture->SetPath(filepath);
    
    _Textures.insert({ key, newTexture });

    return newTexture;
}