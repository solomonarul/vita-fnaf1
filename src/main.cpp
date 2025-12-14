#include "gl/all.hpp"
#include "core/all.hpp"
#include "game/main.hpp"

#include <iostream>

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: Probably I don't actually need this much.
int _newlib_heap_size_user   = 50 * 1024 * 1024;   // 50MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;   // 50MB
#endif

struct AppState : public Core::IAppState {
	double timer = 0;
	Core::StateManager states;
	GL::Window window = GL::Window({.title = "Five Nights at Freddy's", .w = 960, .h = 544});
};

bool main_loop(double time, void* userData)
{
	constexpr double timer_rate = 1.0 / 60;
	constexpr double delta_time_limit = 1.0 / 2;    // If less than 2 fps, ignore the update.

	AppState* const status = static_cast<AppState*>(userData);
    status->states.draw(status->window.w, status->window.h);
    status->window.swap();

    if(time < delta_time_limit)
        status->timer += time;

    while(status->timer > timer_rate)
    {
        status->states.update(timer_rate);
        status->timer -= timer_rate;    // All my homies like fixed rate delta timing.
    }

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        Core::InputManager::handle_event(event);

        switch(event.type)
        {
        case SDL_EVENT_WINDOW_RESIZED:
           	status->window.w = event.window.data1;
            status->window.h = event.window.data2;
            break;

        case SDL_EVENT_QUIT:
            status->running = false;
            break;

        default:
            status->states.send(event);
            break;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

    std::cout << TTY_BLUE << "[INFO] App initialization complete.\n" << TTY_RESET;
    // TODO: figure out why the Vita doesn't allocate the heaps unless I do this.

    AppState status;
    status.window.use();
    status.window.vsync(true);
    PUSH_STATE(status.states, Game::States::Main);
    RUN_MAIN_LOOP(main_loop, &status);
    return EXIT_SUCCESS;
}
