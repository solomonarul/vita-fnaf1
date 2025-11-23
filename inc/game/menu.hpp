#pragma once

#include "core/audio.hpp"
#include "core/state.hpp"
#include "game/menu/background.hpp"
#include "gl/mtsdf/font.hpp"
#include "gl/mtsdf/text.hpp"

namespace Game::States
{
    struct Menu : public Core::IState
    {
        Menu(Core::StateManager&);
        ~Menu();

        std::unique_ptr<GL::MTSDF::Text> t_texts[2];
        std::shared_ptr<GL::MTSDF::Font> f_consolas;
        std::shared_ptr<Core::Audio> a_static2, a_darkness_music, a_blip3;

        Objects::Menu::Background bkg;
        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
    };
};