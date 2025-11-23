#include "core/defines.hpp"
#include "core/delta.hpp"
#include "core/state.hpp"
#include "game/main.hpp"
#include "gl/window.hpp"

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: I don't actually need this much.
int _newlib_heap_size_user   = 100 * 1024 * 1024;   // 100MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;    //  50MB
#endif

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

    // Create and use window.
    GL::Window window({.title = "Five Nights at Freddy's", .w = 960, .h = 544});
    window.use();

    Core::StateManager manager;
    manager.states.emplace_back(std::make_unique<Game::States::Main>(manager));

    bool running = true;
    SDL_Event event;
    Core::Delta dt;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_EVENT_WINDOW_RESIZED:
                window.w = event.window.data1;
                window.h = event.window.data2;
                break;

            case SDL_EVENT_QUIT:
                running = false;
                break;
            
            default:
                // TODO: propagate through state manager.
                break;
            }
        }
        manager.draw(window.w, window.h);
        manager.update(dt.tick());
        window.swap();
    }

    return EXIT_SUCCESS;
}
