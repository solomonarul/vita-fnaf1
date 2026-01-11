#include "newspaper.hpp"

#include "menu.hpp"
#include "nightloader.hpp"

using namespace Game;

States::Newspaper::Newspaper(StateManager& sm) : IState::IState(sm)
{
    auto menu = (States::Menu*)sm.states.begin()->get();
    menu->updates_disabled = true;

    this->t_newspaper = AssetManager::get<Texture>("t_newspaper");
    this->spr_newspaper.color.a = 0;

#ifdef __DEBUG__
    SDL_Log("[TRCE] Loaded Newspaper state.\n");
#endif
}

void States::Newspaper::draw(int w, int h)
{
    if (this->state != NEWSPAPER_STATE_FADING_IN)
        NEX::GL::clear_color(SDL_FColor{.r = 0.0f, .g = 0.0, .b = 0.0, .a = 1.0f});

    NEX::GL::set_view_letterbox({w, h}, {960, 544});

    Texture::default_shader->use();
    Texture::default_shader->set_uniform("u_texture", 0);
    this->t_newspaper->activate(GL_TEXTURE0);
    this->spr_newspaper.draw(*Texture::default_shader);
}

void States::Newspaper::load_night()
{
    if (this->state == NEWSPAPER_STATE_FADING_IN)
        this->state_manager.states.erase(this->state_manager.states.begin());
    PUSH_STATE(this->state_manager, Game::States::NightLoader, 1);
}

void States::Newspaper::update(double dt)
{
    float& alpha = this->spr_newspaper.color.a;

    switch (this->state)
    {
        case NEWSPAPER_STATE_FADING_IN:
            alpha += inverse_timer_duration * dt;
            if (alpha > 1)
            {
                alpha = 1, this->state = NEWSPAPER_STATE_HOLD;
                this->state_manager.states.erase(this->state_manager.states.begin());
            }
            break;

        case NEWSPAPER_STATE_HOLD:
            this->hold_timer += dt;
            if (this->hold_timer > timer_duration)
                this->state = NEWSPAPER_STATE_FADING_OUT;
            break;

        case NEWSPAPER_STATE_FADING_OUT:
            alpha -= inverse_timer_duration * dt;
            if (alpha < 0)
                alpha = 0, load_night();
            break;
    }
}

void States::Newspaper::event(SDL_Event& event)
{
    switch (event.type)
    {
#if !defined(__psp2__)
        case SDL_EVENT_KEY_DOWN:
#endif
        case SDL_EVENT_MOUSE_BUTTON_UP:
            load_night();
            break;
    }
}
