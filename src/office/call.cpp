#include "office/call.hpp"

using namespace Game::Objects::Office;

CallHandler::CallHandler()
{
    this->a_call = AssetManager::get<Audio>("a_night_call");
    if (this->a_call != nullptr)
        this->a_call->play_track();

    this->t_mute_call = AssetManager::get<Texture>("t_mute_call");
    this->spr_mute_call.color.a = 0.66;
    this->spr_mute_call.refresh_from_rect(rect_call);
}

void CallHandler::draw(void)
{
    if (t_call.ok && this->a_call->is_playing_track())
    {
        Texture::default_shader->use();
        Texture::default_shader->setUniform("u_texture", 0);
        this->t_mute_call->activate(GL_TEXTURE0);
        this->spr_mute_call.draw(*Texture::default_shader);
    }
}

void CallHandler::update(double dt)
{
    if (!t_call.ok)
        this->t_call.update(dt);
}

void CallHandler::event(SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            auto mouse = InputManager::get_mouse_data().get_coords_normalized();
            if (SDL_PointInRectFloat(&mouse, &this->rect_call))
                this->a_call->stop_track();
            break;
        }
    }
}