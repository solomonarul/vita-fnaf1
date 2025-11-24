#include "game/menu.hpp"

#include "core/assetmanager.hpp"
#include "core/defines.hpp"

#include <iostream>

using namespace Game;

States::Menu::Menu(Core::StateManager& sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());
    // TODO: not doing the transition in the follow-up state, if I remove the previous state while still there,
    // undefined behaviour happens on the Vita. I.E removing a state while executing its' code is not ideal.
    // Maybe I am stupid or something again, gotta check this out in detail.

    this->f_consolas = Core::AssetManager::ensure_loaded<GL::MTSDF::Font>("f_consolas", "assets/images/fonts/consolas.stf.png", "assets/images/fonts/consolas.csv");
    this->a_static2 = Core::AssetManager::ensure_loaded<Core::Audio>("a_static2", "assets/audio/static2.mp3", true);
    this->a_darkness_music = Core::AssetManager::ensure_loaded<Core::Audio>("a_darkness_music", "assets/audio/darkness music.mp3", true);
    this->a_blip3 = Core::AssetManager::ensure_loaded<Core::Audio>("a_blip3", "assets/audio/blip3.mp3", true);

    this->t_texts[0] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "Five\nNights\nat\nFreddy's");
    this->t_texts[0]->x = -750 / 960.0;
    this->t_texts[0]->y = 420 / 544.0;
    this->t_texts[0]->s = 79 / 544.0;
    this->t_texts[0]->s_x = 0.5;

    this->t_texts[1] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "v. 1.0");
    this->t_texts[1]->x = -945 / 960.0;
    this->t_texts[1]->y = -1;
    this->t_texts[1]->s = 40 / 544.0;
    this->t_texts[1]->s_x = 0.6;
    this->t_texts[1]->o_y = 1;

    this->t_texts[2] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "©2014 Scott Cawthon");
    this->t_texts[2]->x = 945 / 960.0;
    this->t_texts[2]->y = -1;
    this->t_texts[2]->s = 40 / 544.0;
    this->t_texts[2]->s_x = 0.6;
    this->t_texts[2]->o_x = -1;
    this->t_texts[2]->o_y = 1;

#ifdef APP_IS_DEMO
    this->t_demo = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "Demo");
    this->t_demo->x = -750 / 960.0;
    this->t_demo->y = 100 / 544.0;
    this->t_demo->s = 79 / 544.0;
    this->t_demo->s_x = 0.5;
#endif

    MIX_PlayTrack(this->a_static2->track, 0);
    MIX_PlayTrack(this->a_blip3->track, 0);
    MIX_PlayTrack(this->a_darkness_music->track, 0);
}

States::Menu::~Menu()
{
    if(this->a_static2)
        Core::AssetManager::remove_ptr(this->a_static2);
    Core::AssetManager::remove_ptr(this->a_darkness_music);

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
    for(auto index = 0; index < 3; index++)
        this->t_texts[index]->draw();
    this->selector.draw();

#ifdef APP_IS_DEMO
    this->t_demo->draw();
#endif
}

void States::Menu::update(double dt)
{
    if(!MIX_TrackPlaying(this->a_darkness_music->track))
        MIX_PlayTrack(this->a_darkness_music->track, 0);

    if(this->a_static2 && !MIX_TrackPlaying(this->a_static2->track))
        this->a_static2 = nullptr, Core::AssetManager::remove("a_static2");

    this->bkg.update(dt);
}