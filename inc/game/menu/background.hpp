#pragma once

#include "gl/shader.hpp"
#include "gl/texture.hpp"

#include <memory>

namespace Game::Objects::Menu
{
    struct Background
    {
        GLuint vbo;
        GLint u_alpha;
        GLint u_static_alpha;

        uint8_t current_texture = 0;
        std::shared_ptr<GL::Texture> textures[4];
        uint8_t current_static_texture = 0;
        std::shared_ptr<GL::Texture> static_textures[8];
        std::shared_ptr<GL::Shader> shader;

        constexpr static double update_rate = 8.0 / 100;
        double update_timer = 0;

        constexpr static double static_image_update_rate = 1.0 / 10;
        double static_image_update_timer = 0;

        constexpr static double static_update_rate = 9.0 / 100;
        double static_update_timer = 0;

        Background();
        ~Background();
        void update(double dt);
        void draw();
    };
};