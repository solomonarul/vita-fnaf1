#pragma once

#include "core/state.hpp"
#include "gl/assets/shader.hpp"
#include "gl/assets/texture.hpp"

namespace Game::States
{
    struct Newspaper : public Core::IState
    {
        Newspaper(Core::StateManager&);
        ~Newspaper();

        std::shared_ptr<GL::Shader> s_texture_default;
        std::shared_ptr<GL::Texture> t_newspaper;

        GLuint vbo = 0;
        double alpha = 0;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};