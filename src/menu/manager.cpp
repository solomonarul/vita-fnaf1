#include "menu/manager.hpp"

#include "newspaper.hpp"
#include "nightloader.hpp"

using namespace Game::Objects::Menu;

Manager::Manager()
{
    this->a_blip3 = AssetManager::get<Audio>("a_blip3");
    this->f_consolas = AssetManager::get<MTSDF::Font>("f_consolas");
    this->f_consolas_bold = AssetManager::get<MTSDF::Font>("f_consolas_bold");

    this->t_texts[TEXT_NEW_GAME] = std::make_unique<MTSDF::Text>(this->f_consolas, "New Game");
    this->t_texts[TEXT_NEW_GAME]->x = -700 / 960.0;
    this->t_texts[TEXT_NEW_GAME]->y = -70 / 544.0;
    this->t_texts[TEXT_NEW_GAME]->s = 79 / 544.0;
    this->t_texts[TEXT_NEW_GAME]->s_x = 0.5;

    this->t_texts[TEXT_CONTINUE] = std::make_unique<MTSDF::Text>(this->f_consolas, "Continue");
    this->t_texts[TEXT_CONTINUE]->x = -700 / 960.0;
    this->t_texts[TEXT_CONTINUE]->y = -175 / 544.0;
    this->t_texts[TEXT_CONTINUE]->s = 79 / 544.0;
    this->t_texts[TEXT_CONTINUE]->s_x = 0.5;

    this->t_pointer = std::make_unique<MTSDF::Text>(this->f_consolas, ">>");
    this->t_pointer->x = -800 / 960.0;
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

void Manager::draw(int w, int h)
{
    this->last_w = w;
    this->last_h = h;

    if (this->current > 0)
    {
        this->t_pointer->y = this->t_texts[this->current - 1]->y + 5.0 / 544;
        this->t_pointer->draw();
    }

    if (this->current == TEXT_CONTINUE + 1)
        this->t_night->draw(), this->t_night_count->draw();

    for (auto index = 0; index < TEXT_COUNT; index++) this->t_texts[index]->draw();
}

void Manager::event(SDL_Event& event, StateManager& sm)
{
    auto switch_night = [this, &sm]()
    {
        switch (this->current - 1)
        {
            case TEXT_NEW_GAME:
                PUSH_STATE(sm, Game::States::Newspaper);
                break;
            case TEXT_CONTINUE:
                PUSH_STATE(sm, Game::States::NightLoader, 1);
                // TODO: goto night[nightcount]
                break;
        }
    };

    auto set_index = [this](size_t index)
    {
        if (this->current != index)
            MIX_PlayAudio(AudioManager::get_mixer(), this->a_blip3->audio);
        this->current = index;
    };

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
                    set_index((this->current) % 2 + 1);
                    break;
                case SDLK_SPACE:
                    switch_night();
                    break;
            }
            break;
#endif
        case SDL_EVENT_MOUSE_MOTION:
        {
            const SDL_FPoint mouse_pos = {.x = (event.motion.x / this->last_w - 0.5f) * 2, .y = -(event.motion.y / this->last_h - 0.5f) * 2};

            for (size_t index = 0; index < TEXT_COUNT; index++)
            {
                const SDL_FRect text_box = this->t_texts[index]->get_bounding_box();
                if (SDL_PointInRectFloat(&mouse_pos, &text_box))
                {
                    set_index(index + 1);
                    break;
                }
            }
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            const SDL_FPoint mouse_pos = {.x = (event.button.x / this->last_w - 0.5f) * 2, .y = -(event.button.y / this->last_h - 0.5f) * 2};

            if (this->current == 0)
                break;

            const SDL_FRect text_box = this->t_texts[this->current - 1]->get_bounding_box();
            if (SDL_PointInRectFloat(&mouse_pos, &text_box))
                switch_night();
        }
            // TODO: gamepad input for Vita / PC.
    }
}
