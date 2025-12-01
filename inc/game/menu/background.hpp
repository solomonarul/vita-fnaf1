#pragma once

#include "core/timer.hpp"
#include "gl/assets/shader.hpp"
#include "gl/assets/textureatlas.hpp"

#include <memory>

namespace Game::Objects::Menu
{
    struct Background
    {
        GLuint vbo = 0;
        
        double u_alpha = 0.5;
        double u_blip_alpha = 0;
        double u_static_alpha = 0.9;
        uint8_t current_blip_texture = 0;
        uint8_t current_texture = 0;
        std::shared_ptr<GL::TextureArray> t_blip;
        std::shared_ptr<GL::TextureArray> t_background;
        uint8_t current_static_texture = 0;
        std::shared_ptr<GL::TextureArray> t_static;
        std::shared_ptr<GL::Shader> shader;

        bool blip_show = false;

        Core::Timer ti_blip_show = Core::Timer(30.0 / 100);
        Core::Timer ti_blip_image_update = Core::Timer(1.0 / 7);
        Core::Timer ti_blip_alpha_update = Core::Timer(8.0 / 100);

        Core::Timer ti_image_update = Core::Timer(8.0 / 100);

        Core::Timer ti_static_image_update = Core::Timer(1.0 / 50);
        Core::Timer ti_static_alpha_update = Core::Timer(9.0 / 100);

        constexpr static double u_bar_width = 1.0 / 544 * 25;
        double u_bar_offset = -u_bar_width;
        constexpr static double bar_speed = 1.0 / 19;

        Background();
        ~Background();
        void update(double);
        void draw();
    };
};