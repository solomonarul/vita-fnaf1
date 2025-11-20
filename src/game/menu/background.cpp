#include "game/menu/background.hpp"

#include "core/random.hpp"

using namespace Game::Objects::Menu;

#include "core/assetmanager.hpp"

Background::Background()
{
    this->shader = Core::AssetManager::load<GL::Shader>("bg-sh",
        "assets/shaders/menu/background.vert",
        "assets/shaders/menu/background.frag"
    );

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    GLint a_position = glGetAttribLocation(this->shader->id, "a_position");
    GLint a_texture_coords = glGetAttribLocation(this->shader->id, "a_texture_coords");

    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glEnableVertexAttribArray(a_texture_coords);
    glVertexAttribPointer(a_texture_coords, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    this->shader->use();

    GLint u_texture = glGetUniformLocation(this->shader->id, "u_texture");
    glUniform1i(u_texture, 0);

    GLint u_static_texture = glGetUniformLocation(this->shader->id, "u_static_texture");
    glUniform1i(u_static_texture, 1);

    this->u_alpha = glGetUniformLocation(this->shader->id, "u_alpha");
    this->u_static_alpha = glGetUniformLocation(this->shader->id, "u_static_alpha");

    // TODO: this is still messy.
    this->textures[0] = Core::AssetManager::load<GL::Texture>("bg-0", "assets/images/menu/background/431.png");
    this->textures[1] = Core::AssetManager::load<GL::Texture>("bg-1", "assets/images/menu/background/440.png");
    this->textures[2] = Core::AssetManager::load<GL::Texture>("bg-2", "assets/images/menu/background/441.png");
    this->textures[3] = Core::AssetManager::load<GL::Texture>("bg-3", "assets/images/menu/background/442.png");
    this->static_textures[0] = Core::AssetManager::load<GL::Texture>("st-0", "assets/images/menu/static/12.png");
    this->static_textures[1] = Core::AssetManager::load<GL::Texture>("st-1", "assets/images/menu/static/13.png");
    this->static_textures[2] = Core::AssetManager::load<GL::Texture>("st-2", "assets/images/menu/static/14.png");
    this->static_textures[3] = Core::AssetManager::load<GL::Texture>("st-3", "assets/images/menu/static/15.png");
    this->static_textures[4] = Core::AssetManager::load<GL::Texture>("st-4", "assets/images/menu/static/16.png");
    this->static_textures[5] = Core::AssetManager::load<GL::Texture>("st-5", "assets/images/menu/static/17.png");
    this->static_textures[6] = Core::AssetManager::load<GL::Texture>("st-6", "assets/images/menu/static/18.png");
    this->static_textures[7] = Core::AssetManager::load<GL::Texture>("st-7", "assets/images/menu/static/20.png");
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
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->textures[current_texture]->activate(GL_TEXTURE0);
    this->static_textures[current_static_texture]->activate(GL_TEXTURE1);

    this->shader->use();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Background::update(double dt)
{
    this->update_timer += dt;
    this->static_image_update_timer += dt;
    this->static_update_timer += dt;

    glUniform1f(this->u_alpha, Core::Random::range(0, 249) / 255.0);

    if(this->update_timer > update_rate)
    {
        auto current = Core::Random::range(0, 99);
        if(current < 96) current_texture = 0;
        else current_texture = current - 96;
        this->update_timer = std::fmod(this->update_timer, update_rate);
    }

    if(this->static_image_update_timer > static_image_update_rate)
    {
        current_static_texture = (current_static_texture + 1) % 7;
        this->static_image_update_timer = std::fmod(this->static_image_update_timer, static_image_update_rate);
    }

    if(this->static_update_timer > static_update_rate)
    {
        glUniform1f(this->u_static_alpha, Core::Random::range(50, 149) / 255.0);
        this->static_update_timer = std::fmod(this->update_timer, static_update_rate);      
    }
}

