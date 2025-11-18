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

        uint8_t current_texture = 0;
        // TODO: offset these to an "asset manager".
        std::shared_ptr<GL::Texture> textures[4];
        std::shared_ptr<GL::Shader> shader;

        constexpr static double update_rate = 8.0 / 100;
        double update_timer = 0;

        Background();
        ~Background();
        void update(double dt);
        void draw();
    };
};