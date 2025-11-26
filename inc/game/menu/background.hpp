#pragma once

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
        std::shared_ptr<GL::TextureAtlas> t_blip;
        std::shared_ptr<GL::TextureAtlas> t_background;
        uint8_t current_static_texture = 0;
        std::shared_ptr<GL::TextureAtlas> t_static;
        std::shared_ptr<GL::Shader> shader;

        bool blip_show = false;
        constexpr static double blip_show_update_rate = 30.0 / 100;
        double blip_show_update_timer = 0;

        constexpr static double blip_alpha_update_rate = 8.0 / 100;
        double blip_alpha_update_timer = 0;

        constexpr static double blip_image_update_rate = 1.0 / 7;
        double blip_image_update_timer = 0;

        constexpr static double u_bar_width = 1.0 / 544 * 25;
        double u_bar_offset = -u_bar_width;
        constexpr static double bar_speed = 1.0 / 19;

        constexpr static double update_rate = 8.0 / 100;
        double update_timer = 0;

        constexpr static double static_image_update_rate = 1.0 / 50;
        double static_image_update_timer = 0;

        constexpr static double static_alpha_update_rate = 9.0 / 100;
        double static_alpha_update_timer = 0;

        Background();
        ~Background();
        void update(double);
        void draw();
    };
};