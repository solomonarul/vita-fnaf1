#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

#include <memory>

namespace Game::Objects::Office
{
    struct CallHandler
    {
        std::shared_ptr<Audio> a_call;
        std::shared_ptr<Texture> t_mute_call;
        Sprite spr_mute_call;

        Timer t_call = Timer(15);
        SDL_FRect rect_call = SDL_FRect{.x = -900.0 / 960, .y = 444.0 / 544, .w = 192.0 / 960, .h = 48.0 / 544};

        CallHandler();

        void draw(void);
        void update(double dt);
        void event(SDL_Event&);
    };
}; // namespace Game::Objects::Office
