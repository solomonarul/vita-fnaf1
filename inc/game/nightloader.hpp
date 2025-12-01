#pragma once

#include "core/state.hpp"
#include "core/timer.hpp"
#include "gl/mtsdf/text.hpp"
#include "gl/mtsdf/font.hpp"
#include "gl/assets/textureatlas.hpp"

namespace Game::States
{
    struct NightLoader : public Core::IState
    {
        NightLoader(Core::StateManager&, int);
        ~NightLoader();

        GLuint vbo;

        uint8_t loaded_count = 0;
        uint16_t blip_frame = 0;
        Core::Timer ti_blip_update = Core::Timer(1.0 / 75);

        Core::Timer ti_fade_out = Core::Timer(3);

        std::shared_ptr<GL::TextureArray> t_blip;
        std::shared_ptr<GL::MTSDF::Font> f_lcdsolid;
        std::unique_ptr<GL::MTSDF::Text> t_night[2];

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};