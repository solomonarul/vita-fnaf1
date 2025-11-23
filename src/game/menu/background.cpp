#include "game/menu/background.hpp"

#include "core/random.hpp"

using namespace Game::Objects::Menu;

#include "core/assetmanager.hpp"

Background::Background()
{
    this->shader = Core::AssetManager::ensure_loaded<GL::Shader>("s_menu_bg",
        "assets/shaders/menu/background.vert",
        "assets/shaders/menu/background.frag"
    );

    glGenBuffers(1, &this->vbo);

    this->shader->use();

    // TODO: this is still messy.
    this->textures[0] = Core::AssetManager::ensure_loaded<GL::Texture>("t_bg_0", GL::TextureConfig{"assets/images/menu/background/431.png"});
    this->textures[1] = Core::AssetManager::ensure_loaded<GL::Texture>("t_bg_1", GL::TextureConfig{"assets/images/menu/background/440.png"});
    this->textures[2] = Core::AssetManager::ensure_loaded<GL::Texture>("t_bg_2", GL::TextureConfig{"assets/images/menu/background/441.png"});
    this->textures[3] = Core::AssetManager::ensure_loaded<GL::Texture>("t_bg_3", GL::TextureConfig{"assets/images/menu/background/442.png"});
    this->static_textures[0] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_0", GL::TextureConfig{"assets/images/menu/static/12.png"});
    this->static_textures[1] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_1", GL::TextureConfig{"assets/images/menu/static/13.png"});
    this->static_textures[2] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_2", GL::TextureConfig{"assets/images/menu/static/14.png"});
    this->static_textures[3] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_3", GL::TextureConfig{"assets/images/menu/static/15.png"});
    this->static_textures[4] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_4", GL::TextureConfig{"assets/images/menu/static/16.png"});
    this->static_textures[5] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_5", GL::TextureConfig{"assets/images/menu/static/17.png"});
    this->static_textures[6] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_6", GL::TextureConfig{"assets/images/menu/static/18.png"});
    this->static_textures[7] = Core::AssetManager::ensure_loaded<GL::Texture>("t_st_7", GL::TextureConfig{"assets/images/menu/static/20.png"});
}

Background::~Background()
{
    glDeleteBuffers(1, &this->vbo);
    for(size_t index = 0; index < 4; index++)
        Core::AssetManager::remove_ptr(this->textures[index]);

    for(size_t index = 0; index < 8; index++)
        Core::AssetManager::remove_ptr(this->static_textures[index]);
}

void Background::draw()
{
    this->shader->use();
    
    glUniform1f(
        glGetUniformLocation(this->shader->id, "u_alpha"),
        this->u_alpha
    );
    glUniform1f(
        glGetUniformLocation(this->shader->id, "u_static_alpha"),
        175 / 255.0
    );

    glUniform1i(glGetUniformLocation(this->shader->id, "u_texture"), 0);
    this->textures[current_texture]->activate(GL_TEXTURE0);

    glUniform1i(glGetUniformLocation(this->shader->id, "u_static_texture"), 1);
    this->static_textures[current_static_texture]->activate(GL_TEXTURE1);

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

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
        current_static_texture = (current_static_texture + 1) % 7;
        this->static_image_update_timer = std::fmod(this->static_image_update_timer, static_image_update_rate);
    }

    if(this->static_alpha_update_timer > static_alpha_update_rate)
    {
        this->u_static_alpha = Core::Random::range(50, 149) / 255.0;
        this->static_alpha_update_timer = std::fmod(this->static_alpha_update_timer, static_alpha_update_rate);
    }
}

