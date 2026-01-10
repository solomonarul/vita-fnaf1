#include <nex.hpp>
#include "main.hpp"

#include <SDL3/SDL_main.h>

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: Probably I don't actually need this much.
int _newlib_heap_size_user = 100 * 1024 * 1024; // 100MB
unsigned int sceLibcHeapSize = 4 * 1024 * 1024; // 4MB
unsigned int sceLibcHeapExtendedAlloc = 1;      // Lets libc resize automatically on getting full.
#endif

using namespace NEX::Core;
using namespace NEX::GL;

struct AppState : public IAppState
{
    double timer = 0;
    StateManager states;
#ifdef APP_IS_DEMO
    Window window = Window({.title = "Five Nights at Freddy's DEMO", .w = 960, .h = 544});
#else
    Window window = Window({.title = "Five Nights at Freddy's", .w = 960, .h = 544});
#endif
};

bool main_loop(double time, void* userData)
{
    constexpr double timer_rate = 1.0 / 60;
    constexpr double delta_time_limit = 1.0 / 2; // If less than 2 fps, ignore the update.

    AppState* const status = static_cast<AppState*>(userData);
    if (time < delta_time_limit)
        status->timer += time;

    while (status->timer > timer_rate)
    {
        status->states.update(timer_rate);
        status->timer -= timer_rate; // All my homies like fixed rate delta timing.
    }

    status->states.draw(status->window.w, status->window.h);
    status->window.swap();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        InputManager::handle_event(event);

        switch (event.type)
        {
            case SDL_EVENT_WINDOW_RESIZED:
                status->window.w = event.window.data1;
                status->window.h = event.window.data2;
                break;

            case SDL_EVENT_QUIT:
                status->running = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key)
                {
                    case SDLK_F11:
                        status->window.set_fullscreen(!status->window.fullscreen);
                        break;

                    default:
                        status->states.send(event);
                        break;
                }
                break;

            default:
                status->states.send(event);
                break;
        }
    }

    SDL_DelayNS(SDL_SECONDS_TO_NS(timer_rate - status->timer));

    return true;
}

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    SDL_Log("%s[INFO] App initialization complete.%s\n", TTY_BLUE, TTY_RESET);
    // TODO: figure out why the Vita doesn't allocate the heaps unless I do this.

    AppState status;
    status.window.use();
    status.window.vsync(true);
    SDL_HideCursor();
    PUSH_STATE(status.states, Game::States::Main);
    RUN_MAIN_LOOP(main_loop, &status);
    return EXIT_SUCCESS;
}
