#include "core/defines.hpp"
#include "core/delta.hpp"
#include "core/state.hpp"
#include "game/main.hpp"
#include "gl/window.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: Probably I don't actually need this much.
int _newlib_heap_size_user   = 100 * 1024 * 1024;   // 100MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;    //  50MB
#endif

// TODO: not a big fan of this but emscripten is being a bitch.
bool running = true;
SDL_Event event;
Core::StateManager manager;
GL::Window window({.title = "Five Nights at Freddy's", .w = 960, .h = 544});
double timer = 0;
constexpr double timer_rate = 1.0 / 60;

bool loop_once(double time, void* userData)
{
    UNUSED(userData);
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

    timer += time;
    while(timer > timer_rate)
    {
        manager.update(timer_rate);
        timer -= timer_rate;    // All my homies like fixed rate delta timing.
    }
    
    window.swap();
    return true;
}

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

    window.use();
    SDL_GL_SetSwapInterval(1);

    manager.states.push_back(std::make_shared<Game::States::Main>(manager));

#ifdef __EMSCRIPTEN__
    emscripten_request_animation_frame_loop(loop_once, 0);
#else
    Core::Delta dt;
    while(running)
    {
        loop_once(dt.tick(), nullptr);
    }
#endif

    return EXIT_SUCCESS;
}
