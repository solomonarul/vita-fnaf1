#include "core/assetmanager.hpp"

using namespace Core;

bool AssetManager::remove(const std::string& key)
{
    std::lock_guard<std::recursive_mutex> lock(mutex());

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

bool AssetManager::process_enqueued()
{
    std::lock_guard<std::recursive_mutex> lock(mutex());

    auto& q = get_queue();
    if (q.empty()) return false;

    auto task = q.front();
    q.erase(q.begin());

    storage()[task.key] = task.loader();
    return true;
}

size_t AssetManager::enqueued_count()
{
    return get_queue().size();
}

AssetManager::Storage& AssetManager::storage()
{
    static Storage s;
    return s;
}

std::recursive_mutex& AssetManager::mutex()
{
    static std::recursive_mutex m;
    return m;
}

std::vector<AssetManager::AssetLoad>& AssetManager::get_queue()
{
    static std::vector<AssetLoad> q;
    return q;
}