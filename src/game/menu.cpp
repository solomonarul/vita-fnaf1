#include "game/menu.hpp"

using namespace Game;

void States::Menu::draw()
{
    glViewport(0, 0, 960, 544);
    this->bkg.draw();
}

void States::Menu::update(double dt)
{
    this->bkg.update(dt);
}