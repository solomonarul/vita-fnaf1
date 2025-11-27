#pragma once

#include <string>
#include "gl/defines.hpp"

namespace GL
{
    struct WindowConfig
    {
        std::string title;
        size_t w, h;
    };

    struct Window
    {
        SDL_Window* sdl = nullptr;
        SDL_GLContext gl = nullptr;
        int w, h;

        void use();
        void swap();
        Window(WindowConfig);
        ~Window();
    };
};