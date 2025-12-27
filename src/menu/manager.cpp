#include "menu/manager.hpp"

#include "newspaper.hpp"
#include "nightloader.hpp"

using namespace Game::Objects::Menu;

Manager::Manager()
{
    this->a_blip3 = AssetManager::get<Audio>("a_blip3");
    this->f_consolas = AssetManager::get<MTSDF::Font>("f_consolas");
    this->f_consolas_bold = AssetManager::get<MTSDF::Font>("f_consolas_bold");

    this->t_texts[0] = std::make_unique<MTSDF::Text>(this->f_consolas, "New Game");
    this->t_texts[0]->x = -700 / 960.0;
    this->t_texts[0]->y = -70 / 544.0;
    this->t_texts[0]->s = 79 / 544.0;
    this->t_texts[0]->s_x = 0.5;

    this->t_texts[1] = std::make_unique<MTSDF::Text>(this->f_consolas, "Continue");
    this->t_texts[1]->x = -700 / 960.0;
    this->t_texts[1]->y = -175 / 544.0;
    this->t_texts[1]->s = 79 / 544.0;
    this->t_texts[1]->s_x = 0.5;

    this->t_pointer = std::make_unique<MTSDF::Text>(this->f_consolas, ">>");
    this->t_pointer->x = -810 / 960.0;
    this->t_pointer->s = 79 / 544.0;
    this->t_pointer->s_x = 0.5;

    this->t_night = std::make_unique<MTSDF::Text>(this->f_consolas, "Night");
    this->t_night->x = -680 / 960.0;
    this->t_night->y = -240 / 544.0;
    this->t_night->s = 40 / 544.0;
    this->t_night->s_x = 0.6;

    this->t_night_count = std::make_unique<MTSDF::Text>(this->f_consolas_bold, "1");
    this->t_night_count->x = -545 / 960.0;
    this->t_night_count->y = -240 / 544.0;
    this->t_night_count->s = 40 / 544.0;
    this->t_night_count->s_x = 0.6;
}

Manager::~Manager() {}

void Manager::draw()
{
    if (this->current > 0)
    {
        this->t_pointer->y = this->t_texts[this->current - 1]->y + 5.0 / 544;
        this->t_pointer->draw();
    }

    if (this->current == 2)
        this->t_night->draw(), this->t_night_count->draw();

    for (auto index = 0; index < 2; index++) this->t_texts[index]->draw();
}

void Manager::event(SDL_Event& event, StateManager& sm)
{
    UNUSED(sm);
    switch (event.type)
    {
#ifndef __psp2__
        case SDL_EVENT_KEY_DOWN:
            // TODO: maybe move this to update and have a global input state manager?
            if (event.key.repeat)
                break;
            switch (event.key.key)
            {
                case SDLK_W:
                case SDLK_S:
                    this->current = (this->current) % 2 + 1;
                    MIX_PlayAudio(AudioManager::get_mixer(), this->a_blip3->audio);
                    break;
                case SDLK_SPACE:
                    switch (this->current)
                    {
                        case 1:
                            PUSH_STATE(sm, Game::States::Newspaper);
                            break;
                        case 2:
                            PUSH_STATE(sm, Game::States::NightLoader, 1);
                            // TODO: goto night[nightcount]
                            break;
                    }
                    break;
            }
            break;
#endif
            // TODO: gamepad input for Vita / PC.
            break;
    }
}
