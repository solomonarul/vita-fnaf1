#include "game/newspaper.hpp"

#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "game/menu.hpp"
#include "game/nightloader.hpp"
#include "gl/defines.hpp"

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

    GEN_AND_SEND_VBO(this->vbo, verts, GL_STATIC_DRAW);
}

States::Newspaper::~Newspaper()
{
    glDeleteBuffers(1, &this->vbo);
    std::cout << TTY_BLUE << "[INFO]: Destroyed Newspaper state.\n" << TTY_RESET; 
}

void States::Newspaper::draw(int w, int h)
{
    if(this->state != NEWSPAPER_STATE_FADING_IN)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

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
    switch(this->state)
    {
    case NEWSPAPER_STATE_FADING_IN:
        this->alpha += inverse_timer_duration * dt;
        if(this->alpha > 1)
        {
            this->alpha = 1, this->state = NEWSPAPER_STATE_HOLD;

            // Clean the menu state.
            this->state_manager.states.erase(this->state_manager.states.begin());
        }
        break;

    case NEWSPAPER_STATE_HOLD:
        this->hold_timer += dt;
        if(this->hold_timer > timer_duration) this->state = NEWSPAPER_STATE_FADING_OUT;
        break;

    case NEWSPAPER_STATE_FADING_OUT:
        this->alpha -= inverse_timer_duration * dt;
        if(this->alpha < 0) this->alpha = 0, this->state_manager.states.push_back(std::make_shared<Game::States::NightLoader>(this->state_manager, 1));
        break;
    }
}

void States::Newspaper::event(SDL_Event& event)
{
    UNUSED(event);
}