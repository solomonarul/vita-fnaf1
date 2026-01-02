#include "nightloader.hpp"

#include "nex/core/assetmanager.hpp"
#include "office.hpp"

using namespace Game;

States::NightLoader::NightLoader(StateManager& sm, int night) : IState::IState(sm)
{
    AudioManager::stop_all_tracks();
    sm.states.erase(sm.states.begin());

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

    AssetManager::remove("a_night_call"); // Unload previously loaded night call.
    // clang-format off
    static std::string call_paths[5] = {
        "assets/audio/night/calls/voiceover1c.mp3",
        "assets/audio/night/calls/voiceover2a.mp3",
        "assets/audio/night/calls/voiceover3.mp3",
        "assets/audio/night/calls/voiceover4.mp3", 
        "assets/audio/night/calls/voiceover5.mp3",
    };
    // clang-format on
    if (night >= 1 && night <= 5)
    {
        this->loaded_count++;
        AssetManager::queue<Audio>("a_night_call", call_paths[night - 1], true);
    }

    this->loaded_count += AssetManager::queue_from_toml("assets/presets/night.toml");

    this->t_loader = AssetManager::get<Texture>("t_loader");
    this->spr_loader.refresh_from_rect(SDL_FRect{.x = 856.0 / 960, .y = -500.0 / 544, .w = 64.0 / 960, .h = 64.0 / 544});

    AssetManager::get<Audio>("a_blip3")->play_track();
}

void States::NightLoader::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    NEX::GL::set_view_letterbox({w, h}, {960, 544});

    for (auto index = 0; index < 2; index++)
    {
        this->t_night[index]->color.a = (1.0 - this->ti_fade_out.progress()) * 255;
        this->t_night[index]->draw();
    }

    if (this->blip_frame != (uint16_t)-1)
    {
        Texture::default_shader->use();
        Texture::default_shader->setUniform("u_texture", 0);
        this->t_blip->textures[blip_frame]->activate(GL_TEXTURE0);
        spr_blip.draw(*Texture::default_shader);
    }

    if (AssetManager::enqueued_count() != 0)
    {
        Texture::default_shader->use();
        Texture::default_shader->setUniform("u_texture", 0);
        this->t_loader->activate(GL_TEXTURE0);
        this->spr_loader.draw(*Texture::default_shader);
    }
}

void States::NightLoader::update(double dt)
{
    if (this->blip_frame != (uint16_t)-1)
    {
        this->ti_blip_update.update(dt);
        if (this->ti_blip_update.has_ticked())
        {
            this->blip_frame = this->blip_frame + 1;
            if (this->blip_frame == this->t_blip->textures.size())
                this->blip_frame = (uint16_t)-1;
        }
    }
    else
    {
        if (AssetManager::enqueued_count() == 0)
        {
            this->ti_fade_out.update(dt);
            if (this->ti_fade_out.has_ticked())
                PUSH_STATE(this->state_manager, States::Office);
        }
        else
            AssetManager::process_enqueued();
    }
}

void States::NightLoader::event(SDL_Event& event)
{
    if (this->blip_frame != (uint16_t)-1)
        return;

    switch (event.type)
    {
#ifndef __psp2__
        case SDL_EVENT_KEY_DOWN:
#endif
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (AssetManager::enqueued_count() == 0)
                this->ti_fade_out.update(this->ti_fade_out.rate);
            break;
    }
}
