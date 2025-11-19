#pragma once

#include "asset.hpp"

#include <SDL3_mixer/SDL_mixer.h>

#include <string>

namespace Core
{
    struct Audio : public Asset
    {
        MIX_Audio* audio = nullptr;
        MIX_Track* track = nullptr;
        std::string path;

        Audio(const std::string&, bool = true);
        ~Audio();
    };

    struct AudioManager
    {
        AudioManager() = delete;

        static MIX_Mixer* get_mixer();

    private:
        struct AudioManagerInner
        {
            MIX_Mixer* mixer;

            AudioManagerInner();
            ~AudioManagerInner();
        };

        static AudioManagerInner& get_instance();
    };
};