#include "menu.hpp"

using namespace Game;

#define VERSION "v. 1.00 "

#ifdef __unix__
#define PLATFORM "UNIX"
#elif __psp2__
#define PLATFORM "VITA"
#elif EMSCRIPTEN
#define PLATFORM "WEB"
#else
#define PLATFORM "WINDOWS"
#endif

States::Menu::Menu(StateManager& sm, std::shared_ptr<Objects::Cursor> cursor) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    this->f_consolas = AssetManager::get<MTSDF::Font>("f_consolas");
    this->a_static2 = AssetManager::get<Audio>("a_static2");
    this->a_darkness_music = AssetManager::get<Audio>("a_darkness_music");
    this->a_blip3 = AssetManager::get<Audio>("a_blip3");

    this->t_texts[0] = std::make_unique<MTSDF::Text>(this->f_consolas, "Five\nNights\nat\nFreddy's");
    this->t_texts[0]->x = -700 / 960.0;
    this->t_texts[0]->y = 420 / 544.0;
    this->t_texts[0]->s = 79 / 544.0;
    this->t_texts[0]->s_x = 0.5;

    this->t_texts[1] = std::make_unique<MTSDF::Text>(this->f_consolas, VERSION PLATFORM);
    this->t_texts[1]->x = -945 / 960.0;
    this->t_texts[1]->y = -1;
    this->t_texts[1]->s = 40 / 544.0;
    this->t_texts[1]->s_x = 0.6;
    this->t_texts[1]->o_y = 1;

    this->t_texts[2] = std::make_unique<MTSDF::Text>(this->f_consolas, (char*)u8"\u00A92014 Scott Cawthon");
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

    this->a_darkness_music->play_track();
    this->a_static2->play_track();
    this->a_blip3->play_track();

    this->o_cursor = cursor;
    this->o_selector.o_cursor = cursor;
}

void States::Menu::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    NEX::GL::set_view_letterbox({w, h}, {960, 544});

    this->o_background.draw();
    this->o_selector.draw();
    for (auto index = 0; index < 3; index++) this->t_texts[index]->draw();

#ifdef APP_IS_DEMO
    this->t_demo->draw();
#endif

    Texture::default_shader->use();
    this->o_cursor->draw(*Texture::default_shader);
}

void States::Menu::update(double dt)
{
    if (updates_disabled)
    {
        AudioManager::stop_all_tracks();
        return;
    }

    if (!this->a_darkness_music->is_playing_track())
        this->a_darkness_music->play_track();

    this->o_background.update(dt);
    this->o_selector.update();
}

void States::Menu::event(SDL_Event& event)
{
    if (updates_disabled)
        return;
    this->o_selector.event(event, this->state_manager);
    this->o_cursor->event(event);
}
