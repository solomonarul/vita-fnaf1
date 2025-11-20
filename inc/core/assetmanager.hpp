#pragma once

#include <memory>
#include <string>
#include <mutex>
#include <unordered_map>

#include "asset.hpp"

namespace Core
{
    // TODO: check this, looks all right.

    using AssetPtr = std::shared_ptr<Asset>;

    struct AssetManager
    {
        AssetManager() = delete;

        template<typename T, typename... Args>
        static std::shared_ptr<T> load(const std::string& key, Args&&... args)
        {
            std::lock_guard<std::mutex> lock(mutex());

            auto& assets = storage();
            auto it = assets.find(key);
            if (it != assets.end())
                return std::dynamic_pointer_cast<T>(it->second);

            auto asset = std::make_shared<T>(std::forward<Args>(args)...);
            assets[key] = asset;
            return asset;
        }

        template<typename T>
        static bool save(const std::string& key, const std::shared_ptr<T>& asset)
        {
            if (!asset)
                return false;

            std::lock_guard<std::mutex> lock(mutex());

            auto& assets = storage();
            auto it = assets.find(key);

            if (it != assets.end())
                if (!std::dynamic_pointer_cast<T>(it->second))
                    return false;

            assets[key] = asset;
            return true;
        }

        template<typename T>
        static std::shared_ptr<T>& get(const std::string& key)
        {
            std::lock_guard<std::mutex> lock(mutex());

            auto& assets = storage();
            auto it = assets.find(key);
            if (it == assets.end())
                return nullptr;

            return std::dynamic_pointer_cast<T>(it->second);
        }

        static bool remove(const std::string& key);
        static void remove_all();

        template<typename T>
        static bool remove_ptr(const std::shared_ptr<T>& ptr)
        {
            if (!ptr)
                return false;

            std::lock_guard<std::mutex> lock(mutex());

            auto& assets = storage();

            for (auto it = assets.begin(); it != assets.end(); ++it)
                if (std::dynamic_pointer_cast<T>(it->second) == ptr)
                {
                    assets.erase(it);
                    return true;
                }
            return false;
        }

    private:
        using Storage = std::unordered_map<std::string, AssetPtr>;

        static Storage& storage();
        static std::mutex& mutex();
    };
};