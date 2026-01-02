#include "office.hpp"

using namespace Game;

States::Office::Office(StateManager& sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    this->t_office = AssetManager::get<TextureArray>("t_office");
    this->s_office = AssetManager::get<Shader>("s_office");
    this->a_office_buzz = AssetManager::get<Audio>("a_office_buzz");
    this->a_office_buzz->play_track();
    this->a_office_buzz->set_gain_track(0.2);

    this->a_freddy_nose = AssetManager::get<Audio>("a_freddy_nose");
    this->a_freddy_nose->set_gain_track(0.75);

    this->tr_office_view = std::make_shared<RenderTexture>(this->t_office->textures[0]->w, this->t_office->textures[0]->h);

    this->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
    this->hover_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
}

States::Office::~Office()
{
    SDL_DestroyCursor(this->cursor);
    SDL_DestroyCursor(this->hover_cursor);
}

void States::Office::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->tr_office_view->use();
    Texture::default_shader->use();
    Texture::default_shader->setUniform("u_texture", 0);
    this->t_office->textures[0]->activate(GL_TEXTURE0);
    this->spr_office.draw(*Texture::default_shader);
    this->tr_office_view->unuse();

    NEX::GL::set_view_letterbox({w, h}, {960, 544});

    this->s_office->use();
    this->s_office->setUniform("u_texture", 0);
    this->s_office->setUniform("u_view_offset", this->u_view_offset);
    this->tr_office_view->activate(GL_TEXTURE0);
    this->spr_office_view.draw(*this->s_office);

    this->o_call_handler.draw();
}

void States::Office::update(double dt)
{
    auto m_data = InputManager::get_mouse_data();
    if (m_data.x < 0.25)
    {
        u_view_offset -= 4 * dt * ((0.25 - m_data.x) / 0.25);
        if (u_view_offset < 0)
            u_view_offset = 0;
    }
    else if (m_data.x > 0.75)
    {
        u_view_offset += 4 * dt * ((m_data.x - 0.75) / 0.25);
        if (u_view_offset > 1)
            u_view_offset = 1;
    }

    if (!this->a_office_buzz->is_playing_track())
        this->a_office_buzz->play_track();

    this->o_call_handler.update(dt);
}

void States::Office::event(SDL_Event& event)
{
    SDL_FRect const rect_freddy_nose = SDL_FRect{.x = 495.0, .y = 165.0, .w = 30.0, .h = 30.0};

    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
        {
            auto mouse = InputManager::get_mouse_data().get_coords();
            mouse.x *= 960;
            mouse.y *= 540;
            mouse.x += u_view_offset * (1210 - 960);
            if (SDL_PointInRectFloat(&mouse, &rect_freddy_nose))
                SDL_SetCursor(this->hover_cursor);
            else
                SDL_SetCursor(this->cursor);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            auto mouse = InputManager::get_mouse_data().get_coords();
            mouse.x *= 960;
            mouse.y *= 540;
            mouse.x += u_view_offset * (1210 - 960);
            if (SDL_PointInRectFloat(&mouse, &rect_freddy_nose))
                this->a_freddy_nose->play_track();
            break;
        }
    }

    this->o_call_handler.event(event);
}
