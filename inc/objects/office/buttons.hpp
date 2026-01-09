#pragma once

#include <memory>
#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

#include "objects/cursor.hpp"

namespace Game::Objects::Office
{
    struct ButtonsHandler
    {
        std::shared_ptr<Objects::Cursor> o_cursor;

        ButtonsHandler();

        void draw(void);
        void update(double);
        void event(SDL_Event&);
    };
}; // namespace Game::Objects::Office
