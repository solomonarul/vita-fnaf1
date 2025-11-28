#include "game/menu/background.hpp"

#include "core/random.hpp"
#include "core/assetmanager.hpp"
#include "gl/defines.hpp"

using namespace Game::Objects::Menu;

Background::Background()
{
    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    GEN_AND_SEND_VBO(this->vbo, verts, GL_STATIC_DRAW)

    this->shader = Core::AssetManager::get<GL::Shader>("s_menu_background");
    this->t_blip = Core::AssetManager::get<GL::TextureAtlas>("t_menu_blip");
    this->t_background = Core::AssetManager::get<GL::TextureAtlas>("t_menu_background");
    this->t_static = Core::AssetManager::get<GL::TextureAtlas>("t_static");
}

Background::~Background()
{
    glDeleteBuffers(1, &this->vbo);
}

void Background::draw()
{
    this->shader->use();
    
    glUniform1f(glGetUniformLocation(this->shader->id, "u_alpha"), this->u_alpha);
    glUniform1f(glGetUniformLocation(this->shader->id, "u_bar_offset"), this->u_bar_offset);
    glUniform1f(
        glGetUniformLocation(this->shader->id, "u_blip_alpha"),
        this->blip_show ? this->u_blip_alpha : 0
    );
    glUniform1f(glGetUniformLocation(this->shader->id, "u_bar_width"), this->u_bar_width);

    glUniform1i(glGetUniformLocation(this->shader->id, "u_texture"), 0);
    this->t_background->textures[current_texture]->activate(GL_TEXTURE0);

    glUniform1i(glGetUniformLocation(this->shader->id, "u_static_texture"), 1);
    this->t_static->textures[current_static_texture]->activate(GL_TEXTURE1);

    glUniform1i(glGetUniformLocation(this->shader->id, "u_blip_texture"), 2);
    this->t_blip->textures[current_blip_texture]->activate(GL_TEXTURE2);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    GLint a_position = glGetAttribLocation(shader->id, "a_position");
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(
        a_position, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );

    GLint a_texcoord = glGetAttribLocation(shader->id, "a_texture_coords");
    glEnableVertexAttribArray(a_texcoord);
    glVertexAttribPointer(
        a_texcoord, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Background::update(double dt)
{
    this->ti_image_update.update(dt);
    this->ti_static_image_update.update(dt);
    this->ti_static_alpha_update.update(dt);
    this->ti_blip_image_update.update(dt);
    this->ti_blip_alpha_update.update(dt);
    this->ti_blip_show.update(dt);
    this->u_bar_offset = this->u_bar_offset + dt * bar_speed;
    this->u_bar_offset = (this->u_bar_offset > 1) ? -u_bar_width : this->u_bar_offset;

    if(this->ti_image_update.has_ticked())
    {
        auto current = Core::Random::range(0, 99);
        if(current < 96) current_texture = 0;
        else current_texture = current - 96;
        this->u_alpha = Core::Random::range(0, 249) / 255.0;
    }

    if(this->ti_static_image_update.has_ticked())
        this->current_static_texture = (this->current_static_texture + 1) % this->t_static->textures.size();

    if(this->ti_static_alpha_update.has_ticked())
        this->u_static_alpha = Core::Random::range(50, 149) / 255.0;

    if(this->ti_blip_image_update.has_ticked())
        this->current_blip_texture = (this->current_blip_texture + 1) % this->t_blip->textures.size();

    if(this->ti_blip_alpha_update.has_ticked())
        this->u_blip_alpha = Core::Random::range(50, 100) / 255.0;

    if(this->ti_blip_show.has_ticked())
        this->blip_show = Core::Random::range(0, 2) == 1;
}

