#pragma once

#include "gl/mtsdf/font.hpp"
#include "gl/mtsdf/text.hpp"

#include <memory>

namespace Game::Objects::Menu
{
    struct Manager
    {   
        std::unique_ptr<GL::MTSDF::Text> t_texts[2];
        std::shared_ptr<GL::MTSDF::Font> f_consolas, f_consolas_bold;
        std::unique_ptr<GL::MTSDF::Text> t_pointer, t_night, t_night_count;

        Manager();
        ~Manager();
        void draw();
    };
};