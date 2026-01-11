#include "objects/menu/manager.hpp"

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

void Manager::update()
{
    auto set_index = [this](size_t index)
    {
        if (this->current != index)
            this->a_blip3->play_audio();
        this->current = index;
    };

    auto mouse = InputManager::get_mouse_data().get_coords_normalized();
    for (size_t index = 0; index < TEXT_COUNT; index++)
    {
        const SDL_FRect text_box = this->t_texts[index]->get_bounding_box();
        if (SDL_PointInRectFloat(&mouse, &text_box))
        {
            set_index(index + 1);
            break;
        }
    }

    this->o_cursor->update();
}

void Manager::draw()
{
    if (this->current > 0)
    {
        this->t_pointer->y = this->t_texts[this->current - 1]->y + 5.0 / 544;
        this->t_pointer->draw();
    }

    if (this->current == TEXT_CONTINUE + 1)
        this->t_night->draw(), this->t_night_count->draw();

    for (auto index = 0; index < TEXT_COUNT; index++) this->t_texts[index]->draw();

    Texture::default_shader->use();
    this->o_cursor->draw(*Texture::default_shader);
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

#if !defined(__psp2__)
    auto set_index = [this](size_t index)
    {
        if (this->current != index)
            this->a_blip3->play_audio();
        this->current = index;
    };
#endif

    switch (event.type)
    {
#if !defined(__psp2__)
        case SDL_EVENT_KEY_DOWN:
        {
            if (event.key.repeat)
                break;

            if (InputManager::get_mouse_data().is_in_normalized_rect(this->t_texts[this->current - 1]->get_bounding_box()))
                break;

            switch (event.key.key)
            {
                case SDLK_W:
                    if (this->current == 0)
                        set_index(TEXT_COUNT);
                    else
                        set_index((this->current == TEXT_NEW_GAME + 1) ? (size_t)TEXT_COUNT : this->current - 1);
                    break;

                case SDLK_S:
                    if (this->current == 0)
                        set_index(1);
                    else
                        set_index((this->current == TEXT_COUNT) ? 1 : this->current + 1);
                    break;

                case SDLK_SPACE:
                    switch_night();
                    break;
            }
            break;
        }
#endif
        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            if (this->current == 0)
                break;

            if (InputManager::get_mouse_data().is_in_normalized_rect(this->t_texts[this->current - 1]->get_bounding_box()))
                switch_night();
        }
            // TODO: gamepad input for Vita / PC.
    }
}
