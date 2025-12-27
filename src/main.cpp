#include "main.hpp"

#include "menu.hpp"

using namespace Game;

States::Main::Main(StateManager &sm) : IState::IState(sm)
{
    // TODO: check later if this is needed elsewhere and cache it in the asset manager if needed.
    this->f_tahoma = std::make_shared<MTSDF::Font>("assets/images/fonts/tahoma.sdf.png", "assets/images/fonts/tahoma.csv");

    this->t_warning[0] = std::make_unique<MTSDF::Text>(f_tahoma, "WARNING!");
    this->t_warning[0]->y = 90 / 544.0;

    this->t_warning[1] = std::make_unique<MTSDF::Text>(f_tahoma, "This game contains flashing lights, loud");
    this->t_warning[1]->y = 0 / 544.0;

    this->t_warning[2] = std::make_unique<MTSDF::Text>(f_tahoma, "noises, and lots of jumpscares!");
    this->t_warning[2]->y = -45 / 544.0;

    for (auto index = 0; index < 3; index++)
    {
        this->t_warning[index]->x = 0;
        this->t_warning[index]->o_x = -0.5;
        this->t_warning[index]->s = 45 / 544.0;
        this->t_warning[index]->s_x = 0.6;
    }

    this->loaded_count += AssetManager::queue_from_toml("assets/presets/main.toml");

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Created Main state.\n" << TTY_RESET;
#endif
}

States::Main::~Main()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Destroyed Main state.\n" << TTY_RESET;
#endif
}

void States::Main::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif

    for (auto index = 0; index < 3; index++)
    {
        if (AssetManager::enqueued_count() == 0)
            this->t_warning[index]->color.a = (1.0 - this->ti_transition.value / this->ti_transition.rate) * 255;
        else
            this->t_warning[index]->color.a = 255;
        this->t_warning[index]->draw(MTSDF::Font::default_shader);
    }
}

void States::Main::update(double dt)
{
    if (AssetManager::enqueued_count() == 0)
    {
        this->ti_transition.update(dt);
        if (this->ti_transition.has_ticked())
            PUSH_STATE(this->state_manager, Game::States::Menu);
    }
    else
    {
        // TODO: add a loading bar or smth.
        AssetManager::process_enqueued();
    }
}

void States::Main::event(SDL_Event &event)
{
    UNUSED(event);
}
