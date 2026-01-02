#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

#include "office/call.hpp"

namespace Game::States
{
    struct Office : public IState
    {
        Office(StateManager&);

        double u_view_offset = 0.5;
        std::shared_ptr<Shader> s_office;
        std::shared_ptr<Audio> a_office_buzz;
        std::shared_ptr<TextureArray> t_office;
        std::shared_ptr<RenderTexture> tr_office_view;

        Sprite spr_office, spr_office_view;

        Objects::Office::CallHandler o_call_handler;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
}; // namespace Game::States
