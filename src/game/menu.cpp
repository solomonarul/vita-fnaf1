#include "game/menu.hpp"

#ifdef SCENE_LOAD_LOG
#include <iostream>
#endif

using namespace Game;

States::Menu::Menu(StateManager &sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());
    // TODO: not doing the transition in the follow-up state, if I remove the previous state while
    // still there, undefined behaviour happens on the Vita. I.E removing a state while executing
    // its' code is not ideal. Maybe I am stupid or something again, gotta check this out in detail.

    this->f_consolas = AssetManager::get<MTSDF::Font>("f_consolas");
    this->a_static2 = AssetManager::get<Audio>("a_static2");
    this->a_darkness_music = AssetManager::get<Audio>("a_darkness_music");
    this->a_blip3 = AssetManager::get<Audio>("a_blip3");

    this->t_texts[0] = std::make_unique<MTSDF::Text>(this->f_consolas, "Five\nNights\nat\nFreddy's");
    this->t_texts[0]->x = -700 / 960.0;
    this->t_texts[0]->y = 420 / 544.0;
    this->t_texts[0]->s = 79 / 544.0;
    this->t_texts[0]->s_x = 0.5;

    this->t_texts[1] = std::make_unique<MTSDF::Text>(this->f_consolas, "v. 1.00");
    this->t_texts[1]->x = -945 / 960.0;
    this->t_texts[1]->y = -1;
    this->t_texts[1]->s = 40 / 544.0;
    this->t_texts[1]->s_x = 0.6;
    this->t_texts[1]->o_y = 1;

    this->t_texts[2] = std::make_unique<MTSDF::Text>(this->f_consolas, (char *)u8"\u00A92014 Scott Cawthon");
    this->t_texts[2]->x = 945 / 960.0;
    this->t_texts[2]->y = -1;
    this->t_texts[2]->s = 40 / 544.0;
    this->t_texts[2]->s_x = 0.6;
    this->t_texts[2]->o_x = -1;
    this->t_texts[2]->o_y = 1;

#ifdef APP_IS_DEMO
    this->t_demo = std::make_unique<MTSDF::Text>(this->f_consolas, "Demo");
    this->t_demo->x = -700 / 960.0;
    this->t_demo->y = 100 / 544.0;
    this->t_demo->s = 79 / 544.0;
    this->t_demo->s_x = 0.5;
#endif

    MIX_PlayTrack(this->a_static2->track, 0);
    MIX_PlayTrack(this->a_blip3->track, 0);
    MIX_PlayTrack(this->a_darkness_music->track, 0);

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Created Menu state.\n" << TTY_RESET;
#endif
}

States::Menu::~Menu()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Destroyed Menu state.\n" << TTY_RESET;
#endif
}

void States::Menu::draw(int w, int h)
{
#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif
    this->o_background.draw();
    for (auto index = 0; index < 3; index++) this->t_texts[index]->draw();
    this->o_selector.draw();

#ifdef APP_IS_DEMO
    this->t_demo->draw();
#endif
}

void States::Menu::update(double dt)
{
    if (updates_disabled)
    {
        MIX_StopAllTracks(AudioManager::get_mixer(), 0);
        return;
    }

    if (!MIX_TrackPlaying(this->a_darkness_music->track))
        MIX_PlayTrack(this->a_darkness_music->track, 0);

    this->o_background.update(dt);
}

void States::Menu::event(SDL_Event &event)
{
    if (updates_disabled)
        return;
    this->o_selector.event(event, this->state_manager);
}
