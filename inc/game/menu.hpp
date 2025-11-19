#pragma once

#include "core/audio.hpp"
#include "core/state.hpp"
#include "game/menu/background.hpp"

namespace Game::States
{
    struct Menu : public Core::IState
    {
        Menu();
        ~Menu();

        std::shared_ptr<Core::Audio> a_static2;
        std::shared_ptr<Core::Audio> a_darkness_music;
        std::shared_ptr<Core::Audio> a_blip3;

        Objects::Menu::Background bkg;
        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
    };
};