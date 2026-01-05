#include "objects/cursor.hpp"

using namespace Game::Objects;

Cursor::Cursor(std::shared_ptr<Texture> texture, size_t w, size_t h)
{
    this->type = CursorType::CURSOR_NORMAL;
    this->t_cursor = texture;
    this->spr_cursor = SpriteAtlas(w, h);
}

void Cursor::draw(Shader& shader)
{
    const auto mouse_pos = InputManager::get_mouse_data().get_coords_normalized();
    this->spr_cursor.push_sprite(this->type, SDL_FRect{.x = mouse_pos.x, .y = mouse_pos.y, .w = 48.0 / 960, .h = -48.0 / 544});

    shader.setUniform("u_texture", 0);
    this->t_cursor->activate(GL_TEXTURE0);
    this->spr_cursor.draw(shader);

    this->type = CursorType::CURSOR_NORMAL;
}