#include "game/main_loading.hpp"

#include "core/assetmanager.hpp"
#include "core/defines.hpp"

using namespace Game;

States::MainLoading::MainLoading()
{
    this->f_consolas = Core::AssetManager::load<GL::MTSDFFont>("f_consolas", "assets/images/fonts/consolas.stf.png");
}

States::MainLoading::~MainLoading()
{

}

void States::MainLoading::draw(int w, int h)
{
#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif
}

void States::MainLoading::update(double dt)
{
    UNUSED(dt);
}