#include "night.hpp"

using namespace Game;

States::Night::Night(StateManager& sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    this->t_office = AssetManager::get<TextureArray>("t_office");
    this->s_office = AssetManager::get<Shader>("s_office");
    this->a_office_buzz = AssetManager::get<Audio>("a_office_buzz");
    this->a_office_buzz->play_track();
    this->a_office_buzz->set_gain_track(0.2);

    this->tr_office_view = std::make_shared<RenderTexture>(this->t_office->textures[0]->w, this->t_office->textures[0]->h);
}

States::Night::~Night() {}

void States::Night::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->tr_office_view->use();
    Texture::default_shader->use();
    Texture::default_shader->setUniform("u_texture", 0);
    this->t_office->textures[0]->activate(GL_TEXTURE0);
    this->spr_office.draw(*Texture::default_shader);

#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    this->r_view = SDL_Rect{s_w, s_h, w - 2 * s_w, h - 2 * s_h};
    this->tr_office_view->unuse(this->r_view.x, this->r_view.y, this->r_view.w, this->r_view.h);
    InputManager::set_letterbox(this->r_view);
#else
    this->tr_office_view->unuse(0, 0, w, h);
#endif

    this->s_office->use();
    this->s_office->setUniform("u_texture", 0);
    this->s_office->setUniform("u_view_offset", this->u_view_offset);
    this->tr_office_view->activate(GL_TEXTURE0);
    this->spr_office_view.draw(*this->s_office);
    this->o_call_handler.draw();
}

void States::Night::update(double dt)
{
    auto m_data = InputManager::get_mouse_data();
    if (m_data.x / this->r_view.w < 0.25)
    {
        u_view_offset -= 4 * dt * ((0.25 - m_data.x / this->r_view.w) / 0.25);
        if (u_view_offset < 0)
            u_view_offset = 0;
    }
    else if (m_data.x / this->r_view.w > 0.75)
    {
        u_view_offset += 4 * dt * ((m_data.x / this->r_view.w - 0.75) / 0.25);
        if (u_view_offset > 1)
            u_view_offset = 1;
    }

    if (!this->a_office_buzz->is_playing_track())
        this->a_office_buzz->play_track();
}

void States::Night::event(SDL_Event& event)
{
    UNUSED(event);
}
