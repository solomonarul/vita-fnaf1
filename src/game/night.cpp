#include "game/night.hpp"

#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "core/inputmanager.hpp"
#include "gl/defines.hpp"

#ifdef SCENE_LOAD_LOG
#include <iostream>
#endif

using namespace Game;

States::Night::Night(Core::StateManager& sm) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    GEN_AND_SEND_VBO(this->vbo, verts, GL_STATIC_DRAW);

    this->t_office = Core::AssetManager::get<GL::TextureArray>("t_office");
    this->s_office = Core::AssetManager::get<GL::Shader>("s_office");

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE <<  "[INFO]: Created Night state.\n" << TTY_RESET;
#endif
}

States::Night::~Night()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE <<  "[INFO]: Destroyed Night state.\n" << TTY_RESET;
#endif
}

void States::Night::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif

    this->s_office->use();
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glUniform1i(glGetUniformLocation(this->s_office->id, "u_texture"), 0);

    glUniform4f(
        glGetUniformLocation(this->s_office->id, "u_color"),
        1.0, 1.0, 1.0, 1.0
    );

    glUniform1f(
        glGetUniformLocation(this->s_office->id, "u_view_offset"),
        this->u_view_offset
    );

    GLint a_position = glGetAttribLocation(this->s_office->id, "a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(
        a_position, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );

    GLint a_texcoord = glGetAttribLocation(this->s_office->id, "a_texture_coords");
    glEnableVertexAttribArray(a_texcoord);
    glVertexAttribPointer(
        a_texcoord, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );
    this->t_office->textures[0]->activate(GL_TEXTURE0);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void States::Night::update(double dt)
{
    auto m_data = Core::InputManager::get_mouse_data();
    if(m_data.x / 960.0 < 0.25)
    {
        u_view_offset -= 3 * dt * ((0.25 - m_data.x / 960.0) / 0.25);
        if(u_view_offset < 0) u_view_offset = 0;
    }
    else if(m_data.x / 960.0 > 0.75)    // TODO: take glViewport into consideration
    {
        u_view_offset += 3 * dt * ((m_data.x / 960.0 - 0.75) / 0.25);
        if(u_view_offset > 1) u_view_offset = 1;           
    }
}

void States::Night::event(SDL_Event& event)
{
    UNUSED(event);
}