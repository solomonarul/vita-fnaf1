#pragma once

#include <memory>
#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

#include "objects/cursor.hpp"

namespace Game::Objects::Office
{
    struct CallHandler
    {
        std::shared_ptr<Audio> a_call;
        std::shared_ptr<Texture> t_mute_call;
        Sprite spr_mute_call;

        Timer t_call = Timer(16);
        std::shared_ptr<Objects::Cursor> o_cursor;

        CallHandler();

        void draw(void);
        void update(double);
        void event(SDL_Event&);
    };
}; // namespace Game::Objects::Office
