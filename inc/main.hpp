#pragma once

#include <nex.hpp>

#include "objects/cursor.hpp"

using namespace NEX::Prefabs;
using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::States
{
    struct Main : public IState
    {
        Main(StateManager&);

        uint8_t loaded_count = 0;
        std::unique_ptr<MTSDF::Text> t_warning[3];
        std::shared_ptr<MTSDF::Font> f_tahoma;

        std::shared_ptr<Texture> t_loader;
        Sprite spr_loader;

        std::shared_ptr<Objects::Cursor> o_cursor;

        Timer ti_transition = Timer(3.0);

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
}; // namespace Game::States
