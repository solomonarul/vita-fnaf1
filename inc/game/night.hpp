#pragma once

#pragma once

#include "core/state.hpp"
#include "gl/assets/textureatlas.hpp"

#include <SDL3/SDL_opengles2.h>

namespace Game::States
{
    struct Night : public Core::IState
    {
        Night(Core::StateManager&);
        ~Night();

        GLuint vbo = 0;
        double u_view_offset = 0;
        std::shared_ptr<GL::Shader> s_office;
        std::shared_ptr<GL::TextureArray> t_office;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};