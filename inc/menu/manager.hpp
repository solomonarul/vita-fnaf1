#pragma once

#include <nex.hpp>
using namespace NEX::Core;
using namespace NEX::GL;

#include <memory>

namespace Game::Objects::Menu
{
    enum Texts
    {
        TEXT_NEW_GAME = 0,
        TEXT_CONTINUE,
        TEXT_COUNT
    };

    struct Manager
    {
        size_t current = 0;
        std::unique_ptr<MTSDF::Text> t_texts[2];
        std::shared_ptr<Audio> a_blip3;
        std::shared_ptr<MTSDF::Font> f_consolas, f_consolas_bold;
        std::unique_ptr<MTSDF::Text> t_pointer, t_night, t_night_count;

        Manager();
        void draw(void);
        void event(SDL_Event&, StateManager&);
    };
}; // namespace Game::Objects::Menu
