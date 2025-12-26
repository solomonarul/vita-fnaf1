#pragma once

#include <nex.hpp>
#include "menu/background.hpp"
#include "menu/manager.hpp"

using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::States
{
    struct Menu : public IState
    {
        Menu(StateManager &);
        ~Menu();

        std::unique_ptr<MTSDF::Text> t_texts[3];
        std::shared_ptr<MTSDF::Font> f_consolas;
        std::shared_ptr<Audio> a_static2, a_darkness_music, a_blip3;

#ifdef APP_IS_DEMO
        std::unique_ptr<MTSDF::Text> t_demo;
#endif

        int night = 1; // TODO: move to a global game state holder which will also handle saving or
                       // something like that.
        Objects::Menu::Background o_background;
        Objects::Menu::Manager o_selector;
        bool updates_disabled = false;
        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event &) override;
    };
}; // namespace Game::States
