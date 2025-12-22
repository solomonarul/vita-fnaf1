#include "game/nightloader.hpp"

#include "core/audio.hpp"
#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "game/night.hpp"
#include "gl/defines.hpp"

#ifdef SCENE_LOAD_LOG
#include <iostream>
#endif

using namespace Game;

States::NightLoader::NightLoader(Core::StateManager& sm, int night) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    MIX_StopAllTracks(Core::AudioManager::get_mixer(), 0);

    this->f_lcdsolid = Core::AssetManager::get<GL::MTSDF::Font>("f_lcdsolid");
    this->t_blip = Core::AssetManager::get<GL::TextureArray>("t_blip");

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
        result = std::to_string(night) + "th " + result;

    this->t_night[1] = std::make_unique<GL::MTSDF::Text>(this->f_lcdsolid, result);
    this->t_night[1]->x = 0;
    this->t_night[1]->y = -35 / 544.0;
    this->t_night[1]->s = 70.0 / 544;
    this->t_night[1]->o_x = -0.5;
    this->t_night[1]->s_x = 0.6;

    auto blip = Core::AssetManager::get<Core::Audio>("a_blip3");
    MIX_PlayTrack(blip->track, 0);

    static float verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    GEN_AND_SEND_VBO(this->vbo, verts, GL_STATIC_DRAW);

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE <<  "[INFO] Created NightLoader state.\n" << TTY_RESET;
#endif

    this->loaded_count++;
    Core::AssetManager::queue<GL::TextureArray>("t_office", std::vector{
        GL::TextureConfig{.path = "assets/images/night/office/1.png"},
        GL::TextureConfig{.path = "assets/images/night/office/2.png"},
        GL::TextureConfig{.path = "assets/images/night/office/3.png"},
        GL::TextureConfig{.path = "assets/images/night/office/4.png"},
        GL::TextureConfig{.path = "assets/images/night/office/5.png"}
    });

    this->loaded_count++;
    Core::AssetManager::queue<GL::Shader>(
        "s_office",
        "assets/shaders/office/background.vert", "assets/shaders/office/background.frag"
    );

    this->loaded_count++;
    Core::AssetManager::queue<Core::Audio>(
        "a_office_buzz", "assets/audio/night/Buzz_Fan_Florescent2.mp3", true
    );

    this->loaded_count++;
    Core::AssetManager::queue<Core::Audio>(
        "a_night_1", "assets/audio/night/calls/voiceover1c.mp3", true
    );
}

States::NightLoader::~NightLoader()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE <<  "[INFO] Destroyed NightLoader state.\n" << TTY_RESET;
#endif
}

void States::NightLoader::draw(int w, int h)
{
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
    {
        this->t_night[index]->color.a = (1.0 - this->ti_fade_out.value / this->ti_fade_out.rate) * 255;
        this->t_night[index]->draw();
    }

    if(this->blip_frame != (uint16_t)-1)
    {
        GL::Texture::default_shader->use();
        GL::Texture::default_shader->setUniform("u_texture", 0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
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
        this->ti_blip_update.update(dt);
        if(this->ti_blip_update.has_ticked())
        {
            blip_frame = blip_frame + 1;
            if(blip_frame == this->t_blip->textures.size()) blip_frame = (uint16_t)-1;
        }
    }
    else
    {
        if(Core::AssetManager::enqueued_count() == 0)
        {
            this->ti_fade_out.update(dt);
            if(this->ti_fade_out.has_ticked())
                PUSH_STATE(this->state_manager, States::Night);
        }
        else
        {
            // TODO: add a loading bar or smth.
            Core::AssetManager::process_enqueued();
        }
    }
}

void States::NightLoader::event(SDL_Event& event)
{
    UNUSED(event);
}
