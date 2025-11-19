#include "core/assetmanager.hpp"

using namespace Core;

bool AssetManager::remove(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex());

    auto& assets = storage();
    auto it = assets.find(key);
    if (it == assets.end())
        return false;

    assets.erase(it);  
    return true;
}

void AssetManager::remove_all()
{
    auto& assets = storage();
    assets.clear();
}

AssetManager::Storage& AssetManager::storage()
{
    static Storage s;
    return s;
}

std::mutex& AssetManager::mutex()
{
    static std::mutex m;
    return m;
}