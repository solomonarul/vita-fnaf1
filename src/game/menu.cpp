#include "game/menu.hpp"

#include "core/assetmanager.hpp"
#include "core/defines.hpp"

#include <iostream>

using namespace Game;

States::Menu::Menu(Core::StateManager& sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    this->f_consolas = Core::AssetManager::ensure_loaded<GL::MTSDF::Font>("f_consolas", "assets/images/fonts/consolas.stf.png", "assets/images/fonts/consolas.csv");
    this->a_static2 = Core::AssetManager::ensure_loaded<Core::Audio>("a_static2", "assets/audio/static2.mp3", true);
    this->a_darkness_music = Core::AssetManager::ensure_loaded<Core::Audio>("a_darkness_music", "assets/audio/darkness music.mp3", true);
    this->a_blip3 = Core::AssetManager::ensure_loaded<Core::Audio>("a_blip3", "assets/audio/blip3.mp3", true);

    this->t_texts[0] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "Five\nNights\nat\nFreddy's");
    this->t_texts[0]->x = -750 / 960.0;
    this->t_texts[0]->y = 400 / 544.0;
    this->t_texts[0]->s = 82 / 544.0;
    this->t_texts[0]->s_x = 0.6;

    this->t_texts[1] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "v. 1.0");
    this->t_texts[1]->x = -945 / 960.0;
    this->t_texts[1]->y = -1;
    this->t_texts[1]->s = 41 / 544.0;
    this->t_texts[1]->s_x = 0.6;
    this->t_texts[1]->o_y = 1;

    MIX_PlayTrack(this->a_static2->track, 0);
    MIX_PlayTrack(this->a_blip3->track, 0);
    MIX_PlayTrack(this->a_darkness_music->track, 0);
}

States::Menu::~Menu()
{
    if(this->a_static2)
        Core::AssetManager::remove_ptr(this->a_static2);
    Core::AssetManager::remove_ptr(this->a_darkness_music);
    Core::AssetManager::remove_ptr(this->a_blip3);

    std::cout << TTY_BLUE << "[INFO]: Destroyed Menu state.\n" << TTY_RESET; 
}

void States::Menu::draw(int w, int h)
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
    this->bkg.draw();
    for(auto index = 0; index < 2; index++)
        this->t_texts[index]->draw();
}

void States::Menu::update(double dt)
{
    if(!MIX_TrackPlaying(this->a_darkness_music->track))
        MIX_PlayTrack(this->a_darkness_music->track, 0);

    if(this->a_static2 && !MIX_TrackPlaying(this->a_static2->track))
        this->a_static2 = nullptr, Core::AssetManager::remove("a_static2");

    this->bkg.update(dt);
}