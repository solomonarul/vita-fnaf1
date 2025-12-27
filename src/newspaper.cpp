#include "newspaper.hpp"

#include "menu.hpp"
#include "nightloader.hpp"

using namespace Game;

States::Newspaper::Newspaper(StateManager& sm) : IState::IState(sm)
{
    auto menu = (States::Menu*)sm.states.begin()->get();
    menu->updates_disabled = true;

    this->t_newspaper = AssetManager::get<Texture>("t_newspaper");

    GEN_AND_SEND_VBO(this->vbo, NEX::GL::FULLSCREEN_RECT2D, GL_STATIC_DRAW);
}

States::Newspaper::~Newspaper()
{
    glDeleteBuffers(1, &this->vbo);
}

void States::Newspaper::draw(int w, int h)
{
    if (this->state != NEWSPAPER_STATE_FADING_IN)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    UNUSED(w);
    UNUSED(h);
    Texture::default_shader->use();
    Texture::default_shader->setUniform("u_texture", 0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glUniform4f(glGetUniformLocation(Texture::default_shader->id, "u_color"), 1.0, 1.0, 1.0, (float)this->alpha);

    GLint a_position = glGetAttribLocation(Texture::default_shader->id, "a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    GLint a_texcoord = glGetAttribLocation(Texture::default_shader->id, "a_texture_coords");
    glEnableVertexAttribArray(a_texcoord);
    glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    this->t_newspaper->activate(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void States::Newspaper::update(double dt)
{
    switch (this->state)
    {
        case NEWSPAPER_STATE_FADING_IN:
            this->alpha += inverse_timer_duration * dt;
            if (this->alpha > 1)
            {
                this->alpha = 1, this->state = NEWSPAPER_STATE_HOLD;
                this->state_manager.states.erase(this->state_manager.states.begin());
            }
            break;

        case NEWSPAPER_STATE_HOLD:
            this->hold_timer += dt;
            if (this->hold_timer > timer_duration)
                this->state = NEWSPAPER_STATE_FADING_OUT;
            break;

        case NEWSPAPER_STATE_FADING_OUT:
            this->alpha -= inverse_timer_duration * dt;
            if (this->alpha < 0)
                this->alpha = 0, PUSH_STATE(this->state_manager, Game::States::NightLoader, 1);
            break;
    }
}

void States::Newspaper::event(SDL_Event& event)
{
    UNUSED(event);
}
