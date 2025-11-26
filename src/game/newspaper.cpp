#include "game/newspaper.hpp"

#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "game/menu.hpp"

#include <SDL3/SDL_opengles2.h>

#include <iostream>

using namespace Game;

States::Newspaper::Newspaper(Core::StateManager& sm) : IState::IState(sm)
{
    auto menu = (Game::States::Menu*) sm.states.begin()->get();
    menu->updates_disabled = true;

    this->t_newspaper = Core::AssetManager::ensure_loaded<GL::Texture>("t_newspaper", GL::TextureConfig{"assets/images/misc/NEWSPAPER.png"});

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

States::Newspaper::~Newspaper()
{
    glDeleteBuffers(1, &this->vbo);
    std::cout << TTY_BLUE << "[INFO]: Destroyed Newspaper state.\n" << TTY_RESET; 
}

void States::Newspaper::draw(int w, int h)
{
    UNUSED(w); UNUSED(h);
    GL::Texture::default_shader->use();
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glUniform1i(glGetUniformLocation(GL::Texture::default_shader->id, "u_texture"), 0);

    glUniform4f(
        glGetUniformLocation(GL::Texture::default_shader->id, "u_color"),
        1.0, 1.0, 1.0, (float)this->alpha
    );

    GLint a_position = glGetAttribLocation(GL::Texture::default_shader->id, "a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(
        a_position, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );

    GLint a_texcoord = glGetAttribLocation(GL::Texture::default_shader->id, "a_texture_coords");
    glEnableVertexAttribArray(a_texcoord);
    glVertexAttribPointer(
        a_texcoord, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );
    this->t_newspaper->activate(GL_TEXTURE0);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void States::Newspaper::update(double dt)
{
    alpha += (1.0 / 2.5) * dt;
    alpha = (alpha > 1) ? 1 : alpha;
}

void States::Newspaper::event(SDL_Event& event)
{
    UNUSED(event);
}