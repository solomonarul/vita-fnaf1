#pragma once

#include <nex.hpp>
using namespace NEX::Core;
using namespace NEX::GL;

#include <memory>

namespace Game::Objects::Menu
{
    struct Manager
    {
        size_t current = 0;
        std::unique_ptr<MTSDF::Text> t_texts[2];
        std::shared_ptr<Audio> a_blip3;
        std::shared_ptr<MTSDF::Font> f_consolas, f_consolas_bold;
        std::unique_ptr<MTSDF::Text> t_pointer, t_night, t_night_count;

        Manager();
        ~Manager();
        void draw();
        void event(SDL_Event &, StateManager &);
    };
}; // namespace Game::Objects::Menu
