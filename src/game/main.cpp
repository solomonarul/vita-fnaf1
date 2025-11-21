#include "game/main.hpp"

#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "game/menu.hpp"

#include <iostream>

using namespace Game;

States::Main::Main(Core::StateManager& sm) : IState::IState(sm)
{
    this->f_tahoma = Core::AssetManager::load<GL::MTSDF::Font>("f_tahoma", "assets/images/fonts/tahoma.stf.png", "assets/images/fonts/tahoma.csv");

    // TODO: ugly

    this->t_warning[0] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "WARNING!");
    this->t_warning[0]->o_x = -0.5;
    this->t_warning[0]->x = 0;
    this->t_warning[0]->y = 80 / 544.0;
    this->t_warning[0]->s = 40 / 544.0;
    this->t_warning[0]->s_x = 0.66;
    
    this->t_warning[1] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "This game contains flashing lights, loud");
    this->t_warning[1]->o_x = -0.5;
    this->t_warning[1]->x = 0;
    this->t_warning[1]->y = 0 / 544.0;
    this->t_warning[1]->s = 40 / 544.0;
    this->t_warning[1]->s_x = 0.66;

    this->t_warning[2] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "noises, and lots of jumpscares!");
    this->t_warning[2]->o_x = -0.5;
    this->t_warning[2]->x = 0;
    this->t_warning[2]->y = -40 / 544.0;
    this->t_warning[2]->s = 40 / 544.0;
    this->t_warning[2]->s_x = 0.66;
}

States::Main::~Main()
{
    Core::AssetManager::remove("f_tahoma");
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
        this->t_warning[index]->draw(GL::MTSDF::Font::default_shader);
}

void States::Main::update(double dt)
{
    this->timer += dt;
    if(this->timer > 3)
        this->state_manager.states.emplace_back(std::make_unique<Game::States::Menu>(this->state_manager));
}