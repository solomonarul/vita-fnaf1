#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::States
{
    struct NightLoader : public IState
    {
        NightLoader(StateManager&, int);
        ~NightLoader();

        uint8_t loaded_count = 0;
        uint16_t blip_frame = 0;
        Timer ti_blip_update = Timer(1.0 / 75);
        Sprite spr_blip;

        Timer ti_fade_out = Timer(3);

        std::shared_ptr<TextureArray> t_blip;
        std::shared_ptr<MTSDF::Font> f_lcdsolid;
        std::unique_ptr<MTSDF::Text> t_night[2];

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
}; // namespace Game::States
