#include "core/defines.hpp"
#include "core/delta.hpp"
#include "core/state.hpp"
#include "game/menu.hpp"
#include "gl/window.hpp"

#include <SDL3_mixer/SDL_mixer.h>

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: I don't actually need this much.
int _newlib_heap_size_user   = 10 * 1024 * 1024;   // 10MB
unsigned int sceLibcHeapSize = 5 * 1024 * 1024;    //  5MB
#endif

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

    // Create and use window.
    // TODO: Make resizable and figure out positioning in the screen for non-16:9 sizes.
    GL::Window window(GL::WindowConfig{.title = "Five Nights at Freddy's", .w = 960, .h = 544});
    window.use();

    // Audio mix.
    if(!MIX_Init())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could not init SDL3 mixer!", SDL_GetError(), NULL);
        exit(-1);
    }

    // TODO: decouple someday states from renderer so we can perhaps draw states to a texture.
    Core::StateManager manager;
    manager.states.push_back(std::make_shared<Game::States::Menu>());

    bool running = true;
    SDL_Event event;
    Core::Delta dt;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            default:
                // TODO: propagate through state manager.
                break;
            }
        }

        int window_x, window_y;
        SDL_GetWindowSize(window.sdl, &window_x, &window_y);

        manager.update(dt.tick());
        manager.draw(window_x, window_y);

        window.swap();
    }

    MIX_Quit();
    
    return EXIT_SUCCESS;
}
