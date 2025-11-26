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

    this->shader = Core::AssetManager::ensure_loaded<GL::Shader>("s_menu_bg",
        "assets/shaders/menu/background.vert",
        "assets/shaders/menu/background.frag"
    );

    this->t_blip = Core::AssetManager::ensure_loaded<GL::TextureAtlas>("t_menu_blip", std::vector{
        GL::TextureConfig{.path = "assets/images/misc/white_bars/1.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/2.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/3.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/4.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/5.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/6.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/7.png"},
    });

    this->t_background = Core::AssetManager::ensure_loaded<GL::TextureAtlas>("t_menu_bg", std::vector{
        GL::TextureConfig{"assets/images/menu/background/431.png"},
        GL::TextureConfig{"assets/images/menu/background/440.png"},
        GL::TextureConfig{"assets/images/menu/background/441.png"},
        GL::TextureConfig{"assets/images/menu/background/442.png"}
    });
    
    this->t_static = Core::AssetManager::ensure_loaded<GL::TextureAtlas>("t_static", std::vector{
        GL::TextureConfig{"assets/images/menu/static/12.png"},
        GL::TextureConfig{"assets/images/menu/static/13.png"},
        GL::TextureConfig{"assets/images/menu/static/14.png"},
        GL::TextureConfig{"assets/images/menu/static/15.png"},
        GL::TextureConfig{"assets/images/menu/static/16.png"},
        GL::TextureConfig{"assets/images/menu/static/17.png"},
        GL::TextureConfig{"assets/images/menu/static/18.png"},
        GL::TextureConfig{"assets/images/menu/static/20.png"}
    });
}

Background::~Background()
{
    glDeleteBuffers(1, &this->vbo);
    Core::AssetManager::remove("t_menu_bg");
    Core::AssetManager::remove("t_menu_blip");
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
    this->update_timer += dt;
    this->static_image_update_timer += dt;
    this->static_alpha_update_timer += dt;
    this->blip_image_update_timer += dt;
    this->blip_alpha_update_timer += dt;
    this->blip_show_update_timer += dt;
    this->u_bar_offset = this->u_bar_offset + dt * bar_speed;
    this->u_bar_offset = (this->u_bar_offset > 1) ? -u_bar_width : this->u_bar_offset;

    if(this->update_timer > update_rate)
    {
        auto current = Core::Random::range(0, 99);
        if(current < 96) current_texture = 0;
        else current_texture = current - 96;
        this->u_alpha = Core::Random::range(0, 249) / 255.0;
        this->update_timer = std::fmod(this->update_timer, update_rate);
    }

    if(this->static_image_update_timer > static_image_update_rate)
    {
        this->current_static_texture = (this->current_static_texture + 1) % this->t_static->textures.size();
        this->static_image_update_timer = std::fmod(this->static_image_update_timer, static_image_update_rate);
    }

    if(this->static_alpha_update_timer > static_alpha_update_rate)
    {
        this->u_static_alpha = Core::Random::range(50, 149) / 255.0;
        this->static_alpha_update_timer = std::fmod(this->static_alpha_update_timer, static_alpha_update_rate);
    }

    if(this->blip_image_update_timer > blip_image_update_rate)
    {
        this->current_blip_texture = (this->current_blip_texture + 1) % this->t_blip->textures.size();
        this->blip_image_update_timer = std::fmod(this->blip_image_update_timer, blip_image_update_rate);
    }

    if(this->blip_alpha_update_timer > blip_alpha_update_rate)
    {
        this->u_blip_alpha = Core::Random::range(100, 199) / 255.0 / 2;
        this->blip_alpha_update_timer = std::fmod(this->blip_alpha_update_timer, blip_alpha_update_rate);
    }

    if(this->blip_show_update_timer > blip_show_update_rate)
    {
        this->blip_show = Core::Random::range(0, 2) == 1;
        this->blip_show_update_timer = std::fmod(this->blip_show_update_timer, blip_show_update_rate);
    }
}

