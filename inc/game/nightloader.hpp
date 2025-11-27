#pragma once

#include "core/state.hpp"
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

        uint16_t blip_frame = 0;
        constexpr static double blip_timer_update_rate = 1.0 / 75;
        double blip_timer = 0;

        std::shared_ptr<GL::TextureAtlas> t_blip;
        std::shared_ptr<GL::MTSDF::Font> f_lcdsolid;
        std::unique_ptr<GL::MTSDF::Text> t_night[2];

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};