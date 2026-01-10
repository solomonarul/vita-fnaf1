#include "office.hpp"

using namespace Game;

static SDL_FRect const RECT_FAN = SDL_FRect{.x = -24.0 / 960, .y = -209.0 / 544, .w = 163.0 / 960, .h = 294.0 / 544};
static SDL_FRect const RECT_FREDDY_NOSE = SDL_FRect{.x = 500.0 / 960, .y = 165.0 / 544, .w = 30.0 / 960, .h = 30.0 / 544};

States::Office::Office(StateManager& sm, std::shared_ptr<Objects::Cursor> cursor) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    this->t_office = AssetManager::get<TextureArray>("t_office");
    this->s_office = AssetManager::get<Shader>("s_office");
    this->a_office_buzz = AssetManager::get<Audio>("a_office_buzz");
    this->a_office_buzz->play_track();
    this->a_office_buzz->set_gain_track(0.2);

    this->a_freddy_nose = AssetManager::get<Audio>("a_freddy_nose");
    this->a_freddy_nose->set_gain_track(0.75);

    this->t_fan = AssetManager::get<TextureArray>("t_fan");

    this->tr_office_view = std::make_shared<RenderTexture>(this->t_office->textures[0]->w, this->t_office->textures[0]->h);

    this->spr_fan.refresh_from_rect(RECT_FAN);

    this->o_cursor = cursor;
    this->o_call_handler.o_cursor = cursor;
}

void States::Office::draw(int w, int h)
{
    NEX::GL::clear_color(SDL_FColor{.r = 0.0f, .g = 0.0, .b = 0.0, .a = 1.0f});

    this->tr_office_view->use();
    Texture::default_shader->use();
    Texture::default_shader->set_uniform("u_texture", 0);
    this->t_office->textures[0]->activate(GL_TEXTURE0);
    this->spr_office.draw(*Texture::default_shader);
    Texture::default_shader->use();
    Texture::default_shader->set_uniform("u_texture", 0);
    this->t_fan->textures[this->fan_image]->activate(GL_TEXTURE0);
    this->spr_fan.draw(*Texture::default_shader);
    this->tr_office_view->unuse();

    NEX::GL::set_view_letterbox({w, h}, {960, 544});

    this->s_office->use();
    this->s_office->set_uniform("u_texture", 0);
    this->s_office->set_uniform("u_view_offset", this->u_view_offset);
    this->tr_office_view->activate(GL_TEXTURE0);
    this->spr_office_view.draw(*this->s_office);

    this->o_call_handler.draw();

    Texture::default_shader->use();
    this->o_cursor->draw(*Texture::default_shader);
}

void States::Office::update(double dt)
{
    this->o_cursor->update();

    auto m_data = InputManager::get_mouse_data().get_coords();
    if (m_data.x < 0.25)
    {
        u_view_offset -= 4 * dt * ((0.25 - m_data.x) / 0.25);
        if (u_view_offset <= 0)
            u_view_offset = 0;
        else
            this->o_cursor->type = Objects::CursorType::CURSOR_ARROW_LEFT;
    }
    else if (m_data.x > 0.75)
    {
        u_view_offset += 4 * dt * ((m_data.x - 0.75) / 0.25);
        if (u_view_offset >= 1)
            u_view_offset = 1;
        else
            this->o_cursor->type = Objects::CursorType::CURSOR_ARROW_RIGHT;
    }

    if (!this->a_office_buzz->is_playing_track())
        this->a_office_buzz->play_track();

    this->o_call_handler.update(dt);

    auto mouse = InputManager::get_mouse_data().get_coords();
    mouse.x += u_view_offset * (1210 - 960) / 960.0;
    if (SDL_PointInRectFloat(&mouse, &RECT_FREDDY_NOSE))
        this->o_cursor->type = Objects::CursorType::CURSOR_MASCOT;

    this->ti_fan.update(dt);
    if (this->ti_fan.has_ticked())
        this->fan_image = (this->fan_image + 1) % this->t_fan->textures.size();
}

void States::Office::event(SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            auto mouse = InputManager::get_mouse_data().get_coords();
            mouse.x += u_view_offset * (1210 - 960) / 960.0;
            if (SDL_PointInRectFloat(&mouse, &RECT_FREDDY_NOSE))
                this->a_freddy_nose->play_track();
            break;
        }
    }

    this->o_call_handler.event(event);
    this->o_cursor->event(event);
}
