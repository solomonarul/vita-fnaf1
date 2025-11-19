#include "core/assetmanager.hpp"

using namespace Core;

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