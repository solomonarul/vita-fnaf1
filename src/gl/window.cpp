#include "gl/window.hpp"

#include <cstddef>
#include <cstdlib>

using namespace GL;

static size_t window_count = 0;

static bool init_sdl_video()
{
    // Init SDL video
    bool status = SDL_Init(SDL_INIT_VIDEO);

    // Request GLES2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    return status;
}

static void free_sdl_video()
{
    SDL_Quit();
}

Window::Window(WindowConfig cfg)
{
    if(window_count == 0 && !init_sdl_video())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could not init SDL3!", SDL_GetError(), NULL);
        exit(-1);
    }

    this->sdl = SDL_CreateWindow(cfg.title.c_str(), cfg.w, cfg.h, SDL_WINDOW_OPENGL);
    if(!this->sdl)
    {
        if(window_count == 0) free_sdl_video();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could not init SDL3 window!", SDL_GetError(), NULL);
        exit(-1);
    }

    this->gl = SDL_GL_CreateContext(this->sdl);
    if(!this->gl)
    {
        SDL_DestroyWindow(this->sdl), this->sdl = nullptr;
        if(window_count == 0) free_sdl_video();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could not init SDL3 GLES 2.0 context!", SDL_GetError(), NULL);
        exit(-1);
    }

    window_count++;
}

void Window::use()
{
    SDL_GL_MakeCurrent(this->sdl, this->gl);
}

void Window::swap()
{
    SDL_GL_SwapWindow(this->sdl);
}

Window::~Window()
{
    window_count--;
    if(window_count == 0) free_sdl_video();

    if(this->sdl)
        SDL_DestroyWindow(this->sdl), this->sdl = nullptr;

    if(this->gl)
        SDL_GL_DestroyContext(this->gl), this->gl = nullptr;
}