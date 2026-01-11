#pragma once

#include <memory>
#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::Objects::Menu
{
    enum Timers
    {
        TIMER_BLIP_SHOW = 0,
        TIMER_BLIP_IMAGE_UPDATE,
        TIMER_BLIP_ALPHA_UPDATE,
        TIMER_IMAGE_UPDATE,
        TIMER_STATIC_IMAGE_UPDATE,
        TIMER_STATIC_ALPHA_UPDATE,
        TIMER_COUNT
    };

    struct Background
    {
        double u_alpha = 0.5;
        double u_blip_alpha = 0;
        double u_static_alpha = 0.9;
        uint8_t current_blip_texture = 0;
        uint8_t current_texture = 0;
        std::shared_ptr<TextureArray> t_blip;
        std::shared_ptr<Texture> t_background;
        uint8_t current_static_texture = 0;
        std::shared_ptr<Texture> t_static;
        std::shared_ptr<Shader> shader;
        Sprite spr_background;

        bool blip_show = false;

        Timer timers[TIMER_COUNT] = {Timer(30.0 / 100), Timer(1.0 / 7), Timer(8.0 / 100), Timer(8.0 / 100), Timer(1.0 / 50), Timer(9.0 / 100)};

        constexpr static double u_bar_width = 1.0 / 544 * 25;
        double u_bar_offset = -u_bar_width;
        constexpr static double bar_speed = 1.0 / 19;

        Background();
        void update(double);
        void draw();
    };
}; // namespace Game::Objects::Menu
