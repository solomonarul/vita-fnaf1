#include "menu/background.hpp"

using namespace Game::Objects::Menu;

Background::Background()
{
    this->shader = AssetManager::get<Shader>("s_menu_background");
    this->t_blip = AssetManager::get<TextureArray>("t_menu_blip");
    this->t_background = AssetManager::get<TextureArray>("t_menu_background");
    this->t_static = AssetManager::get<TextureArray>("t_static");
}

void Background::draw()
{
    this->shader->use();
    this->shader->setUniform("u_alpha", this->u_alpha);
    this->shader->setUniform("u_bar_offset", this->u_bar_offset);
    this->shader->setUniform("u_blip_alpha", this->blip_show ? this->u_blip_alpha : 0);
    this->shader->setUniform("u_bar_width", this->u_bar_width);

    this->shader->setUniform("u_texture", 0);
    this->t_background->textures[current_texture]->activate(GL_TEXTURE0);

    this->shader->setUniform("u_static_texture", 1);
    this->t_static->textures[current_static_texture]->activate(GL_TEXTURE1);

    this->shader->setUniform("u_blip_texture", 2);
    this->t_blip->textures[current_blip_texture]->activate(GL_TEXTURE2);

    this->spr_background.draw(*shader);
}

void Background::update(double dt)
{
    for (auto index = 0; index < TIMER_COUNT; index++) this->timers[index].update(dt);

    this->u_bar_offset = this->u_bar_offset + dt * bar_speed;
    this->u_bar_offset = (this->u_bar_offset > 1) ? -u_bar_width : this->u_bar_offset;

    if (this->timers[TIMER_IMAGE_UPDATE].has_ticked())
    {
        auto current = Random::range(0, 99);
        if (current < 96)
            current_texture = 0;
        else
            current_texture = current - 96;
        this->u_alpha = Random::range(0, 249) / 255.0;
    }

    if (this->timers[TIMER_STATIC_IMAGE_UPDATE].has_ticked())
        this->current_static_texture = (this->current_static_texture + 1) % this->t_static->textures.size();

    if (this->timers[TIMER_STATIC_ALPHA_UPDATE].has_ticked())
        this->u_static_alpha = Random::range(50, 149) / 255.0;

    if (this->timers[TIMER_BLIP_SHOW].has_ticked())
        this->blip_show = Random::range(0, 2) == 1;

    if (this->timers[TIMER_BLIP_IMAGE_UPDATE].has_ticked())
        this->current_blip_texture = (this->current_blip_texture + 1) % this->t_blip->textures.size();

    if (this->timers[TIMER_BLIP_ALPHA_UPDATE].has_ticked())
        this->u_blip_alpha = Random::range(50, 100) / 255.0;
}
