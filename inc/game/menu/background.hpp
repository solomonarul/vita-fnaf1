#pragma once

#include "gl/shader.hpp"
#include "gl/texture.hpp"

#include <memory>

namespace Game::Objects::Menu
{
    struct Background
    {
        GLuint vbo = 0;
        
        double u_alpha = 0.5;
        double u_static_alpha = 0.9;
        uint8_t current_texture = 0;
        std::shared_ptr<GL::Texture> textures[4];
        uint8_t current_static_texture = 0;
        std::shared_ptr<GL::Texture> static_textures[8];
        std::shared_ptr<GL::Shader> shader;

        constexpr static double update_rate = 8.0 / 100;
        double update_timer = 0;

        constexpr static double static_image_update_rate = 1.0 / 50;
        double static_image_update_timer = 0;

        constexpr static double static_alpha_update_rate = 9.0 / 100;
        double static_alpha_update_timer = 0;

        Background();
        ~Background();
        void update(double dt);
        void draw();
    };
};