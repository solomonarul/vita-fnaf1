#pragma once

#include "core/state.hpp"
#include "game/menu/background.hpp"

#include <SDL3_mixer/SDL_mixer.h>

namespace Game::States
{
    struct Menu : public Core::IState
    {
        Menu();
        ~Menu();

        MIX_Mixer* a_mixer;
        MIX_Audio* a_static2;
        MIX_Audio* a_blip3;
        MIX_Audio* a_darkness_music;
        MIX_Track* a_darkness_music_track;

        Objects::Menu::Background bkg;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
    };
};