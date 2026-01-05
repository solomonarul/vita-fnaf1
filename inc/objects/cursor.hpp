#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::Objects
{
    // This is the format of the assets/images/cursor.png image.
    enum CursorType
    {
        CURSOR_NORMAL = 0,
        CURSOR_WAIT,
        CURSOR_ERROR,
        CURSOR_HELP,
        CURSOR_NOTIFICATION,
        CURSOR_CLEAR,
        CURSOR_MASCOT,
        CURSOR_HIGHLIGHT,
        CURSOR_ARROW_LEFT,
        CURSOR_ARROW_RIGHT,
        CURSOR_ARROW_TOP,
        CURSOR_ARROW_BOTTOM,
        CURSOR_ARROW_LEFT_UP,
        CURSOR_ARROW_RIGHT_UP,
        CURSOR_ARROW_LEFT_BOTTOM,
        CURSOR_ARROW_RIGHT_BOTTOM,
        CURSOR_HOURGLASS_FRAME_0,
        CURSOR_HOURGLASS_FRAME_1,
        CURSOR_HOURGLASS_FRAME_2,
        CURSOR_HOURGLASS_FRAME_3,
        CURSOR_HOURGLASS_FRAME_4,
        CURSOR_HOURGLASS_FRAME_5,
        CURSOR_HOURGLASS_FRAME_6,
        CURSOR_HOURGLASS_FRAME_7,
        CURSOR_COUNT
    };

    struct Cursor
    {
        CursorType type;
        std::shared_ptr<Texture> t_cursor;
        SpriteAtlas spr_cursor;
        bool enabled;

        Cursor(std::shared_ptr<Texture>, size_t, size_t);
        void draw(Shader&);
        void event(SDL_Event&);
    };
}; // namespace Game::Objects