#include "game/menu/manager.hpp"

using namespace Game::Objects::Menu;

#include "core/assetmanager.hpp"

Manager::Manager()
{
    this->f_consolas = Core::AssetManager::ensure_loaded<GL::MTSDF::Font>("f_consolas", "assets/images/fonts/consolas.stf.png", "assets/images/fonts/consolas.csv");
    this->f_consolas_bold = Core::AssetManager::ensure_loaded<GL::MTSDF::Font>("f_consolas_bold", "assets/images/fonts/consolas_bold.stf.png", "assets/images/fonts/consolas_bold.csv");

    this->t_texts[0] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "New Game");
    this->t_texts[0]->x = -750 / 960.0;
    this->t_texts[0]->y = -70 / 544.0;
    this->t_texts[0]->s = 79 / 544.0;
    this->t_texts[0]->s_x = 0.5;

    this->t_texts[1] = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "Continue");
    this->t_texts[1]->x = -750 / 960.0;
    this->t_texts[1]->y = -210 / 544.0;
    this->t_texts[1]->s = 79 / 544.0;
    this->t_texts[1]->s_x = 0.5;

    this->t_pointer = std::make_unique<GL::MTSDF::Text>(this->f_consolas, ">>");
    this->t_pointer->x = -845 / 960.0;
    this->t_pointer->y = -205 / 544.0;
    this->t_pointer->s = 79 / 544.0;
    this->t_pointer->s_x = 0.5;

    this->t_night = std::make_unique<GL::MTSDF::Text>(this->f_consolas, "Night");
    this->t_night->x = -735 / 960.0;
    this->t_night->y = -275 / 544.0;
    this->t_night->s = 40 / 544.0;
    this->t_night->s_x = 0.6;

    this->t_night_count = std::make_unique<GL::MTSDF::Text>(this->f_consolas_bold, "1");
    this->t_night_count->x = -600 / 960.0;
    this->t_night_count->y = -275 / 544.0;
    this->t_night_count->s = 40 / 544.0;
    this->t_night_count->s_x = 0.6;
}

Manager::~Manager()
{

}

void Manager::draw()
{
    this->t_pointer->draw();

    this->t_night->draw();
    this->t_night_count->draw();

    for(auto index = 0; index < 2; index++)
        this->t_texts[index]->draw();
}

