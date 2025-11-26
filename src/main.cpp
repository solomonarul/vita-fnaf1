#include "core/defines.hpp"
#include "core/delta.hpp"
#include "core/state.hpp"
#include "game/main.hpp"
#include "gl/window.hpp"

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: Probably I don't actually need this much.
int _newlib_heap_size_user   = 100 * 1024 * 1024;   // 100MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;    //  50MB
#endif

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

    // Create and use window.
    GL::Window window({.title = "Five Nights at Freddy's", .w = 960, .h = 544});
    window.use();
    SDL_GL_SetSwapInterval(1);

    Core::StateManager manager;
    manager.states.emplace_back(std::make_shared<Game::States::Main>(manager));

    bool running = true;
    SDL_Event event;
    Core::Delta dt;

    double timer = 0;
    constexpr double timer_rate = 1.0 / 60;

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
                manager.send(event);
                break;
            }
        }

        manager.draw(window.w, window.h);

        timer += dt.tick();
        while(timer > timer_rate)
        {
            manager.update(timer_rate);
            timer -= timer_rate;    // Fixed rate delta timing.
        }
        
        window.swap();
    }

    return EXIT_SUCCESS;
}
