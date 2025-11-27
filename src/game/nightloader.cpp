#include "game/nightloader.hpp"

#include "core/assets/audio.hpp"
#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "gl/defines.hpp"

#include <cmath>
#include <iostream>

using namespace Game;

States::NightLoader::NightLoader(Core::StateManager& sm, int night) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    this->f_lcdsolid = Core::AssetManager::ensure_loaded<GL::MTSDF::Font>("f_lcdsolid", "assets/images/fonts/lcdsolid.sdf.png", "assets/images/fonts/lcdsolid.csv");

    this->t_night[0] = std::make_unique<GL::MTSDF::Text>(this->f_lcdsolid, "12:00 AM");
    this->t_night[0]->x = 0;
    this->t_night[0]->y = 105 / 544.0;
    this->t_night[0]->s = 70.0 / 544;
    this->t_night[0]->o_x = -0.5;
    this->t_night[0]->s_x = 0.6;

    std::string result = " Night";
    if(night == 1)
        result = "1st" + result;
    else if(night == 2)
        result = "2nd" + result;
    else if(night == 3)
        result = "3rd" + result;
    else
        result = std::to_string(night) + "th";

    this->t_night[1] = std::make_unique<GL::MTSDF::Text>(this->f_lcdsolid, result);
    this->t_night[1]->x = 0;
    this->t_night[1]->y = -35 / 544.0;
    this->t_night[1]->s = 70.0 / 544;
    this->t_night[1]->o_x = -0.5;
    this->t_night[1]->s_x = 0.6;

    auto blip = Core::AssetManager::ensure_loaded<Core::Audio>("a_blip3", "assets/audio/blip3.mp3", true);
    MIX_PlayTrack(blip->track, 0);

    this->t_blip = Core::AssetManager::ensure_loaded<GL::TextureAtlas>("t_blip", std::vector{
        GL::TextureConfig{.path = "assets/images/misc/night_blip/4.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/6.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/8.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/9.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/10.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/21.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/22.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/23.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_blip/25.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
    });

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    GEN_AND_SEND_VBO(this->vbo, verts, GL_STATIC_DRAW)
}

States::NightLoader::~NightLoader()
{
    std::cout << TTY_BLUE <<  "[INFO]: Destroyed Night state.\n" << TTY_RESET; 
}

void States::NightLoader::draw(int w, int h)
{
    UNUSED(w); UNUSED(h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif

    for(auto index = 0; index < 2; index++)
        this->t_night[index]->draw();

    if(this->blip_frame != (uint16_t)-1)
    {
        GL::Texture::default_shader->use();
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        glUniform1i(glGetUniformLocation(GL::Texture::default_shader->id, "u_texture"), 0);

        glUniform4f(
            glGetUniformLocation(GL::Texture::default_shader->id, "u_color"),
            1.0, 1.0, 1.0, 1.0
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
        this->t_blip->textures[blip_frame]->activate(GL_TEXTURE0);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

void States::NightLoader::update(double dt)
{
    if(blip_frame != (uint16_t)-1)
    {
        this->blip_timer += dt;
        if(this->blip_timer > blip_timer_update_rate)
        {
            blip_frame = blip_frame + 1;
            if(blip_frame == this->t_blip->textures.size()) blip_frame = (uint16_t)-1;
            this->blip_timer = std::fmod(this->blip_timer, blip_timer_update_rate);
        }
    }
}

void States::NightLoader::event(SDL_Event& event)
{
    UNUSED(event);
}