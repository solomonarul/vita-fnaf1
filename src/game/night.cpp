#include "game/night.hpp"

#ifdef SCENE_LOAD_LOG
#include <iostream>
#endif
#include <SDL3_mixer/SDL_mixer.h>

using namespace Game;

States::Night::Night(StateManager &sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    };

    GEN_AND_SEND_VBO(this->vbo, verts, GL_STATIC_DRAW);

    this->t_office = AssetManager::get<TextureArray>("t_office");
    this->s_office = AssetManager::get<Shader>("s_office");
    this->a_office_buzz = AssetManager::get<Audio>("a_office_buzz");
    this->a_call = AssetManager::get<Audio>("a_night_1");
    MIX_PlayTrack(this->a_office_buzz->track, 0);
    MIX_SetTrackGain(this->a_office_buzz->track, 0.2);
    MIX_PlayTrack(this->a_call->track, 0);

    this->tr_office_view = std::make_shared<RenderTexture>(this->t_office->textures[0]->w, this->t_office->textures[0]->h);

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Created Night state.\n" << TTY_RESET;
#endif
}

States::Night::~Night()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Destroyed Night state.\n" << TTY_RESET;
#endif
}

void States::Night::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->tr_office_view->use();

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    Texture::default_shader->use();
    Texture::default_shader->setUniform("u_texture", 0);

    glUniform4f(glGetUniformLocation(Texture::default_shader->id, "u_color"), 1.0, 1.0, 1.0, 1.0);

    GLint a_position = glGetAttribLocation(Texture::default_shader->id, "a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

    GLint a_texcoord = glGetAttribLocation(Texture::default_shader->id, "a_texture_coords");
    glEnableVertexAttribArray(a_texcoord);
    glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    this->t_office->textures[0]->activate(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glUniform4f(glGetUniformLocation(this->s_office->id, "u_color"), 1.0, 1.0, 1.0, 1.0);

    a_position = glGetAttribLocation(this->s_office->id, "a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

    a_texcoord = glGetAttribLocation(this->s_office->id, "a_texture_coords");
    glEnableVertexAttribArray(a_texcoord);
    glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    this->tr_office_view->activate(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // TODO: I need to clean the shit out of this.
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

    if (!MIX_TrackPlaying(this->a_office_buzz->track))
        MIX_PlayTrack(this->a_office_buzz->track, 0);
}

void States::Night::event(SDL_Event &event)
{
    UNUSED(event);
}
