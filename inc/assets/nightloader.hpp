#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

inline void queue_assets(uint8_t* count, int night)
{
    // clang-format off
    AssetManager::remove("a_night_call"); // Unload previously loaded night call.

    static std::string call_paths[5] = {
        "assets/audio/night/calls/voiceover1c.mp3",
        "assets/audio/night/calls/voiceover2a.mp3",
        "assets/audio/night/calls/voiceover3.mp3",
        "assets/audio/night/calls/voiceover4.mp3", 
        "assets/audio/night/calls/voiceover5.mp3",
    };
    
    if (night >= 1 && night <= 5)
    {
        (*count)++;
        AssetManager::queue<Audio>("a_night_call", call_paths[night - 1], true);
    }

    (*count)++;
    AssetManager::queue<TextureArray>("t_office", std::vector<TextureConfig>{
        TextureConfig{.path = "assets/images/night/office/1.png"},
        TextureConfig{.path = "assets/images/night/office/2.png"},
        TextureConfig{.path = "assets/images/night/office/3.png"},
        TextureConfig{.path = "assets/images/night/office/4.png"},
        TextureConfig{.path = "assets/images/night/office/5.png"},
    });

    (*count)++;
    AssetManager::queue<TextureArray>("t_fan", std::vector<TextureConfig>{
        TextureConfig{.path = "assets/images/night/fan/1.png"},
        TextureConfig{.path = "assets/images/night/fan/2.png"},
        TextureConfig{.path = "assets/images/night/fan/3.png"},
    });

    (*count)++;
    AssetManager::queue<Texture>("t_mute_call",
        TextureConfig{.path = "assets/images/night/MUTE_CALL_BUTTON.png"}
    );

    (*count)++;
    AssetManager::queue<Texture>("t_camera_flip",
        TextureConfig{.path = "assets/images/night/FLIP.png"}
    );

    (*count)++;
    AssetManager::queue<Shader>("s_office",
        "assets/shaders/office/background.vert", "assets/shaders/office/background.frag"
    );

    (*count)++;
    AssetManager::queue<Audio>("a_freddy_nose",
        "assets/audio/night/freddy_nose.mp3", true
    );

    (*count)++;
    AssetManager::queue<Audio>("a_office_buzz",
        "assets/audio/night/Buzz_Fan_Florescent2.mp3", true
    );
    // clang-format on
}