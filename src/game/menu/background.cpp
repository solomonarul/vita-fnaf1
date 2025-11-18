#include "game/menu/background.hpp"

#include "core/random.hpp"

using namespace Game::Objects::Menu;

Background::Background()
{
    // Build shaders
    std::ifstream shader_in("assets/shaders/menu/background.vert");
    GL::VertexShader vs(shader_in);
    shader_in.close();
    shader_in.open("assets/shaders/menu/background.frag");
    GL::FragmentShader fs(shader_in);
    shader_in.close();

    this->shader = std::make_unique<GL::Shader>(vs, fs);

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

    GLint u_texture = glGetUniformLocation(this->shader->id, "u_texture");
    glUniform1i(u_texture, 0);

    this->u_alpha = glGetUniformLocation(this->shader->id, "u_alpha");

    this->textures[0] = std::make_shared<GL::Texture>("assets/images/431.png");
    this->textures[1] = std::make_shared<GL::Texture>("assets/images/440.png");
    this->textures[2] = std::make_shared<GL::Texture>("assets/images/441.png");
    this->textures[3] = std::make_shared<GL::Texture>("assets/images/442.png");
}

Background::~Background()
{
    glDeleteBuffers(1, &this->vbo);
}

void Background::draw()
{
    this->textures[current_texture]->activate(GL_TEXTURE0);

    this->shader->use();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Background::update(double dt)
{
    update_timer += dt;

    auto alpha = Core::Random::range(0, 249) / 255.0;
    glUniform1f(this->u_alpha, alpha);

    while(update_timer > update_rate)
    {
        auto current = Core::Random::range(0, 99);
        if(current < 96) current_texture = 0;
        else current_texture = current - 96;
        update_timer -= update_rate;
    }
}

