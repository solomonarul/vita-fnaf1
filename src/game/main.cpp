#include "game/main.hpp"

#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "game/menu.hpp"

#include <cmath>
#include <iostream>

using namespace Game;

States::Main::Main(Core::StateManager& sm) : IState::IState(sm)
{
    this->f_tahoma = Core::AssetManager::ensure_loaded<GL::MTSDF::Font>("f_tahoma", "assets/images/fonts/tahoma.stf.png", "assets/images/fonts/tahoma.csv");

    this->t_warning[0] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "WARNING!");
    this->t_warning[0]->x = 0;
    this->t_warning[0]->y = 90 / 544.0;
    
    this->t_warning[1] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "This game contains flashing lights, loud");
    this->t_warning[1]->x = 0;
    this->t_warning[1]->y = 0 / 544.0;

    this->t_warning[2] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "noises, and lots of jumpscares!");
    this->t_warning[2]->x = 0;
    this->t_warning[2]->y = -45 / 544.0;

    for(auto index = 0; index < 3; index++)
    {
        this->t_warning[index]->o_x = -0.5;
        this->t_warning[index]->s = 45 / 544.0;
        this->t_warning[index]->s_x = 0.6;
    }
}

States::Main::~Main()
{
    std::cout << TTY_BLUE <<  "[INFO]: Destroyed Main state.\n" << TTY_RESET; 
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

    for(auto index = 0; index < 3; index++)
    {
        this->t_warning[index]->color.a = std::floor(3.0 - this->timer / 3.0 * 255);
        this->t_warning[index]->draw(GL::MTSDF::Font::default_shader);
    }
}

void States::Main::update(double dt)
{
    this->timer += dt;
    if(this->timer > 3) // TODO: 3 secs or all assets loaded if they take more than 3s to load.
        this->state_manager.states.emplace_back(std::make_shared<Game::States::Menu>(this->state_manager));
}

void States::Main::event(SDL_Event& event)
{
    UNUSED(event);
}