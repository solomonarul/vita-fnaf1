#include "core/defines.hpp"
#include "core/delta.hpp"
#include "core/state.hpp"
#include "game/menu.hpp"
#include "gl/window.hpp"

#ifdef __psp2__
// PSVita newlib + Sony SDK heap sizes.
// TODO: I don't actually need this much.
int _newlib_heap_size_user   = 100 * 1024 * 1024;   // 100MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;    // 50MB
#endif

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

    // Create and use window.
    // TODO: Make resizable and figure out positioning in the screen for non-16:9 sizes.
    GL::Window window(GL::WindowConfig{.title = "Five Nights at Freddy's", .w = 960, .h = 544});
    window.use();

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

        manager.update(dt.tick());
        manager.draw();

        window.swap();
    }
    
    return EXIT_SUCCESS;
}
