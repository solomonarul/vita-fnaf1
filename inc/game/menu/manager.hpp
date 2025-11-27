#pragma once

#include "core/audio.hpp"
#include "core/state.hpp"
#include "gl/mtsdf/font.hpp"
#include "gl/mtsdf/text.hpp"

#include <memory>

namespace Game::Objects::Menu
{
    struct Manager
    {   
        size_t current = 0;
        std::unique_ptr<GL::MTSDF::Text> t_texts[2];
        std::shared_ptr<Core::Audio> a_blip3;
        std::shared_ptr<GL::MTSDF::Font> f_consolas, f_consolas_bold;
        std::unique_ptr<GL::MTSDF::Text> t_pointer, t_night, t_night_count;

        Manager();
        ~Manager();
        void draw();
        void event(SDL_Event&, Core::StateManager&);
    };
};