#pragma once

#include "core/state.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"

#include <memory>

namespace Game::States
{
    struct Menu : public Core::IState
    {
        Menu();
        ~Menu();

        GLuint bg_vbo;
        std::unique_ptr<GL::Texture> bg_texture;
        std::unique_ptr<GL::Texture> bg_texture_1;
        std::unique_ptr<GL::Shader> bg_shader;

        virtual void update() override;
        virtual void draw() override;
    };
};