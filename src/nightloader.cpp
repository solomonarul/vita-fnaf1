#include "nightloader.hpp"

#include "nex/core/assetmanager.hpp"
#include "night.hpp"

using namespace Game;

States::NightLoader::NightLoader(StateManager& sm, int night) : IState::IState(sm)
{
    sm.states.erase(sm.states.begin());

    MIX_StopAllTracks(AudioManager::get_mixer(), 0);

    this->f_lcdsolid = AssetManager::get<MTSDF::Font>("f_lcdsolid");
    this->t_blip = AssetManager::get<TextureArray>("t_blip");

    this->t_night[0] = std::make_unique<MTSDF::Text>(this->f_lcdsolid, "12:00 AM");
    this->t_night[0]->x = 0;
    this->t_night[0]->y = 105 / 544.0;
    this->t_night[0]->s = 70.0 / 544;
    this->t_night[0]->o_x = -0.5;
    this->t_night[0]->s_x = 0.6;

    std::string result = " Night";
    if (night == 1)
        result = "1st" + result;
    else if (night == 2)
        result = "2nd" + result;
    else if (night == 3)
        result = "3rd" + result;
    else
        result = std::to_string(night) + "th" + result;

    this->t_night[1] = std::make_unique<MTSDF::Text>(this->f_lcdsolid, result);
    this->t_night[1]->x = 0;
    this->t_night[1]->y = -35 / 544.0;
    this->t_night[1]->s = 70.0 / 544;
    this->t_night[1]->o_x = -0.5;
    this->t_night[1]->s_x = 0.6;

    auto blip = AssetManager::get<Audio>("a_blip3");
    MIX_PlayTrack(blip->track, 0);

    GEN_AND_SEND_VBO(this->vbo, NEX::GL::FULLSCREEN_RECT2D, GL_STATIC_DRAW);

    this->loaded_count += AssetManager::queue_from_toml("assets/presets/night.toml");

    AssetManager::remove("a_night_call"); // Unload previously loaded night call.

    this->loaded_count++;
    switch (night)
    {
        case 1:
            AssetManager::queue<Audio>("a_night_call", "assets/audio/night/calls/voiceover1c.mp3", true);
            break;

        case 2:
            AssetManager::queue<Audio>("a_night_call", "assets/audio/night/calls/voiceover2a.mp3", true);
            break;

        case 3:
            AssetManager::queue<Audio>("a_night_call", "assets/audio/night/calls/voiceover3.mp3", true);
            break;

        case 4:
            AssetManager::queue<Audio>("a_night_call", "assets/audio/night/calls/voiceover4.mp3", true);
            break;

        case 5:
            AssetManager::queue<Audio>("a_night_call", "assets/audio/night/calls/voiceover5.mp3", true);
            break;

        default:
            this->loaded_count--;
            break;
    }
}

States::NightLoader::~NightLoader() {}

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

    for (auto index = 0; index < 2; index++)
    {
        this->t_night[index]->color.a = (1.0 - this->ti_fade_out.value / this->ti_fade_out.rate) * 255;
        this->t_night[index]->draw();
    }

    if (this->blip_frame != (uint16_t)-1)
    {
        Texture::default_shader->use();
        Texture::default_shader->setUniform("u_texture", 0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glUniform4f(glGetUniformLocation(Texture::default_shader->id, "u_color"), 1.0, 1.0, 1.0, 1.0);

        GLint a_position = glGetAttribLocation(Texture::default_shader->id, "a_position");
        glEnableVertexAttribArray(a_position);
        glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        GLint a_texcoord = glGetAttribLocation(Texture::default_shader->id, "a_texture_coords");
        glEnableVertexAttribArray(a_texcoord);
        glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        this->t_blip->textures[blip_frame]->activate(GL_TEXTURE0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

void States::NightLoader::update(double dt)
{
    if (blip_frame != (uint16_t)-1)
    {
        this->ti_blip_update.update(dt);
        if (this->ti_blip_update.has_ticked())
        {
            blip_frame = blip_frame + 1;
            if (blip_frame == this->t_blip->textures.size())
                blip_frame = (uint16_t)-1;
        }
    }
    else
    {
        if (AssetManager::enqueued_count() == 0)
        {
            this->ti_fade_out.update(dt);
            if (this->ti_fade_out.has_ticked())
                PUSH_STATE(this->state_manager, States::Night);
        }
        else
        {
            // TODO: add a loading bar or smth.
            AssetManager::process_enqueued();
        }
    }
}

void States::NightLoader::event(SDL_Event& event)
{
    UNUSED(event);
}
