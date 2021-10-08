#include "player.h"

#include "opponent.h"

void Player::Draw(graphics::Image &image) {
  image.DrawCircle(x_ + 15, y_ + 15, 15, 30, 96, 219);
  image.DrawCircle(x_ + 15, y_ + 15, 10, 47, 245, 252);
  image.DrawLine(x_ + 14, y_ + 30, x_ + 14, y_ + 40, 0, 229, 69, 8);
  image.DrawLine(x_ + 10, y_ + 10, x_ + 10, y_, 0, 0, 0, 3);
  image.DrawLine(x_ + 19, y_ + 10, x_ + 19, y_, 0, 0, 0, 3);
}

void PlayerProjectile::Draw(graphics::Image &image) {
  if (x_ >= 0 && x_ <= image.GetWidth() && y_ >= 0 && y_ <= image.GetHeight()) {
    image.DrawCircle(x_ + 2, y_ + 2, 2, 0, 50, 240);
    image.DrawCircle(x_ + 1, y_ + 1, 1, 3, 155, 229);
  }
}

void PlayerProjectile::Move(const graphics::Image &game_screen) {
  if (GameElement::IsOutOfBounds(game_screen)) {
    is_active = false;
  } else {
    GameElement::SetX(GameElement::GetX() + 5);
    GameElement::SetY(GameElement::GetY() + 5);
  }
}

void Player::Move(const graphics::Image &game_screen) {}
