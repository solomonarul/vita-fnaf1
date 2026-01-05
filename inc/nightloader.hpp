#pragma once

#include <nex.hpp>

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

#include "objects/cursor.hpp"

namespace Game::States
{
    struct NightLoader : public IState
    {
        NightLoader(StateManager&, std::shared_ptr<Objects::Cursor>, int);

        uint8_t loaded_count = 0;
        uint16_t blip_frame = 0;
        Timer ti_blip_update = Timer(1.0 / 75);
        Sprite spr_blip;

        Timer ti_fade_out = Timer(3);

        std::shared_ptr<TextureArray> t_blip;
        std::shared_ptr<MTSDF::Font> f_lcdsolid;
        std::unique_ptr<MTSDF::Text> t_night[2];

        std::shared_ptr<Texture> t_loader;
        Sprite spr_loader;

        std::shared_ptr<Objects::Cursor> o_cursor;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
}; // namespace Game::States
