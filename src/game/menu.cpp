#include "game/menu.hpp"

using namespace Game;

States::Menu::Menu()
{
    // Build shaders
    std::ifstream shader_in("assets/shaders/bg.vert");
    GL::VertexShader vs(shader_in);
    shader_in.close();
    shader_in.open("assets/shaders/bg.frag");
    GL::FragmentShader fs(shader_in);
    shader_in.close();

    bg_shader = std::make_unique<GL::Shader>(vs, fs);

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    glGenBuffers(1, &this->bg_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bg_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    GLint a_position = glGetAttribLocation(this->bg_shader->id, "a_position");
    GLint a_texture_coords = glGetAttribLocation(this->bg_shader->id, "a_texture_coords");

    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glEnableVertexAttribArray(a_texture_coords);
    glVertexAttribPointer(a_texture_coords, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    GLint u_texture = glGetUniformLocation(this->bg_shader->id, "u_texture");
    glUniform1i(u_texture, 0);

    bg_texture = std::make_unique<GL::Texture>("assets/images/431.png");
    bg_texture_1 = std::make_unique<GL::Texture>("assets/images/440.png");
}

States::Menu::~Menu()
{
    glDeleteBuffers(1, &this->bg_vbo);
}

void States::Menu::draw()
{
    glViewport(0, 0, 960, 544);

    static bool current = false;

    if(!current)
        this->bg_texture->activate(GL_TEXTURE0);
    else
        this->bg_texture_1->activate(GL_TEXTURE0);
    current = !current;

    this->bg_shader->use();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void States::Menu::update()
{

}