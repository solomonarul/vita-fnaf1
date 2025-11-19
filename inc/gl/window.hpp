#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>

#include <string>

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