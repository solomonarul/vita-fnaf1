#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

inline void queue_assets(uint8_t* count)
{
    // clang-format off
    (*count)++;
    AssetManager::queue<Texture>("t_menu_background", TextureConfig{.path = "assets/images/menu/background.png"});

    (*count)++;
    AssetManager::queue<TextureArray>("t_menu_blip", std::vector<TextureConfig>{
        TextureConfig{.path = "assets/images/misc/white_bars/1.png"},
        TextureConfig{.path = "assets/images/misc/white_bars/2.png"},
        TextureConfig{.path = "assets/images/misc/white_bars/3.png"},
        TextureConfig{.path = "assets/images/misc/white_bars/4.png"},
        TextureConfig{.path = "assets/images/misc/white_bars/5.png"},
        TextureConfig{.path = "assets/images/misc/white_bars/6.png"},
        TextureConfig{.path = "assets/images/misc/white_bars/7.png"},
    });

    (*count)++;
    AssetManager::queue<Texture>("t_static", TextureConfig{.path = "assets/images/static.png"});

    (*count)++;
    AssetManager::queue<TextureArray>("t_blip", std::vector<TextureConfig>{
        TextureConfig{.path = "assets/images/misc/night_bars/1.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/2.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/3.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/4.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/5.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/6.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/7.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/8.png"},
        TextureConfig{.path = "assets/images/misc/night_bars/9.png"},
    });

    (*count)++;
    AssetManager::queue<TextureArray>("t_door_right", std::vector<TextureConfig>{
        TextureConfig{.path = "assets/images/night/office/buttons/right/1-STOPPED.png"},
        TextureConfig{.path = "assets/images/night/office/buttons/right/2-DOOR.png"},
        TextureConfig{.path = "assets/images/night/office/buttons/right/3-LIGHT.png"},
        TextureConfig{.path = "assets/images/night/office/buttons/right/4-BOTH.png"}
    });

    (*count)++;
    AssetManager::queue<TextureArray>("t_door_left", std::vector<TextureConfig>{
        TextureConfig{.path = "assets/images/night/office/buttons/left/1-STOPPED.png"},
        TextureConfig{.path = "assets/images/night/office/buttons/left/2-DOOR.png"},
        TextureConfig{.path = "assets/images/night/office/buttons/left/3-LIGHT.png"},
        TextureConfig{.path = "assets/images/night/office/buttons/left/4-BOTH.png"}
    });

    (*count)++;
    AssetManager::queue<Texture>("t_newspaper",
        TextureConfig{.path = "assets/images/misc/NEWSPAPER.png"}
    );

    (*count)++;
    AssetManager::queue<Shader>("s_menu_background",
        "assets/shaders/menu/background.vert", "assets/shaders/menu/background.frag"
    );

    (*count)++;
    AssetManager::queue<Audio>("a_static2",
        "assets/audio/menu/static2.mp3", true
    );

    (*count)++;
    AssetManager::queue<Audio>("a_blip3",
        "assets/audio/blip3.mp3", true
    );

    (*count)++;
    AssetManager::queue<Audio>("a_darkness_music",
        "assets/audio/menu/darkness music.mp3", true
    );

    (*count)++;
    AssetManager::queue<NEX::GL::MTSDF::Font>("f_consolas",
        "assets/images/fonts/consolas.sdf.png", "assets/images/fonts/consolas.csv"
    );

    (*count)++;
    AssetManager::queue<NEX::GL::MTSDF::Font>("f_lcdsolid",
        "assets/images/fonts/lcdsolid.sdf.png", "assets/images/fonts/lcdsolid.csv"
    );

    (*count)++;
    AssetManager::queue<NEX::GL::MTSDF::Font>("f_consolas_bold",
        "assets/images/fonts/consolas_bold.sdf.png", "assets/images/fonts/consolas_bold.csv"
    );
    // clang-format on
}