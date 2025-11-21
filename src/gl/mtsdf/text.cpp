#include "gl/mtsdf/text.hpp"
#include <iostream>

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

    // Calculate maximum sizes.
    float t_w = 0, t_h = 0;
    for(char c : self.text)
    {
        auto it = self.font->glyphs.find(c);
        if(it == self.font->glyphs.end()) continue;

        t_w += self.s * it->second.advance * self.s_x;
    }

    float pen_x = self.x + t_w * self.o_x;
    float pen_y = self.y + t_h * self.o_y;

    for(char c : self.text)
    {
        auto it = self.font->glyphs.find(c);
        if(it == self.font->glyphs.end()) continue;

        SDL_FRect& atlas = it->second.atlas;
        float& u0 = atlas.x;
        float& v0 = atlas.y;
        float& u1 = atlas.w;
        float& v1 = atlas.h;

        SDL_FRect quad = it->second.quad;
        quad.x *= self.s * self.s_x;
        quad.y *= self.s * self.s_y;
        quad.w *= self.s * self.s_x;
        quad.h *= self.s * self.s_y;

        self.vertexData.insert(self.vertexData.end(), {
            pen_x + quad.x, pen_y + quad.y,    
            u0, v1,

            pen_x + quad.w, pen_y + quad.y,
            u1, v1,

            pen_x + quad.w, pen_y + quad.h,
            u1, v0,

            pen_x + quad.x, pen_y + quad.y,
            u0, v1,

            pen_x + quad.w, pen_y + quad.h,
            u1, v0,

            pen_x + quad.x, pen_y + quad.h,
            u0, v0,
        });

        pen_x += self.s * it->second.advance * self.s_x;
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