#pragma once

#include <SDL3/SDL_events.h>

namespace Core
{
    struct InputManager
    {
        struct MouseData
        {
            float x, y;
        };

        static void handle_event(SDL_Event& event);
        static MouseData get_mouse_data();

    private:
        MouseData m_data;

        InputManager() = default;
        static InputManager& self();
    };
};