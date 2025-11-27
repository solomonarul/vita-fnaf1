#pragma once

#include "core/assets/audio.hpp"
#include "core/state.hpp"
#include "game/menu/manager.hpp"
#include "game/menu/background.hpp"
#include "gl/mtsdf/font.hpp"
#include "gl/mtsdf/text.hpp"

namespace Game::States
{
    struct Menu : public Core::IState
    {
        Menu(Core::StateManager&);
        ~Menu();
        
        std::unique_ptr<GL::MTSDF::Text> t_texts[3];
        std::shared_ptr<GL::MTSDF::Font> f_consolas;
        std::shared_ptr<Core::Audio> a_static2, a_darkness_music, a_blip3;

#ifdef APP_IS_DEMO
        std::unique_ptr<GL::MTSDF::Text> t_demo;
#endif

        int night = 1;  // TODO: move to a global game state holder which will also handle saving or something like that.
        Objects::Menu::Background bkg;
        Objects::Menu::Manager selector;
        bool updates_disabled = false;
        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};