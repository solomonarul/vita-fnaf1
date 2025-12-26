#pragma once

#include <nex.hpp>

using namespace NEX::GL;
using namespace NEX::Core;

namespace Game::States
{
    struct Night : public IState
    {
        Night(StateManager &);
        ~Night();

        GLuint vbo = 0;
        SDL_Rect r_view;
        double u_view_offset = 0.5;
        std::shared_ptr<Shader> s_office;
        std::shared_ptr<Audio> a_office_buzz, a_call;
        std::shared_ptr<TextureArray> t_office;
        std::shared_ptr<RenderTexture> tr_office_view;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event &) override;
    };
}; // namespace Game::States
