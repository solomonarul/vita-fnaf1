#include "gl/mtsdf/text.hpp"

using namespace GL;

GL::MTSDF::Text::Text(std::shared_ptr<Font> f, const std::string& str) : font(std::move(f)), text(str)
{
    glGenBuffers(1, &vbo);
}

GL::MTSDF::Text::~Text()
{
    if(vbo)
        glDeleteBuffers(1, &vbo), vbo = 0;
}

inline void buildVertices(GL::MTSDF::Text& self)
{
    // TODO: not optimal.
    self.vertexData.clear();

    float pen_x = self.x;
    float pen_y = self.y;

    for(char c : self.text)
    {
        auto it = self.font->rects.find(c);
        if(it == self.font->rects.end()) continue;

        SDL_FRect rect = it->second;
        float w = self.w;
        float h = self.h;

        float u0 = rect.x;
        float v0 = rect.y;
        float u1 = (rect.x + rect.w);
        float v1 = (rect.y + rect.h);

        self.vertexData.insert(self.vertexData.end(), {
            pen_x,     pen_y,     u0, v0,
            pen_x+w,   pen_y,     u1, v0,
            pen_x+w,   pen_y+h,   u1, v1,

            pen_x,     pen_y,     u0, v0,
            pen_x+w,   pen_y+h,   u1, v1,
            pen_x,     pen_y+h,   u0, v1,
        });

        pen_x += w;
        break;
    }

    glBindBuffer(GL_ARRAY_BUFFER, self.vbo);
    glBufferData(GL_ARRAY_BUFFER, self.vertexData.size() * sizeof(float), self.vertexData.data(), GL_DYNAMIC_DRAW);
}

void GL::MTSDF::Text::draw(std::unique_ptr<GL::Shader>& shader)
{
    buildVertices(*this);

    if(!font || !font->texture || vertexData.empty()) return;

    shader->use();

    GLint u_color = glGetUniformLocation(shader->id, "u_texture");
    glUniform4f(u_color, color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
    
    font->texture->activate(GL_TEXTURE0);
    GLint u_texture = glGetUniformLocation(shader->id, "u_texture");
    glUniform1i(u_texture, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 4);
}