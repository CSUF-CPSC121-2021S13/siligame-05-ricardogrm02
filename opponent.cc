
#include "opponent.h"

void OpponentProjectile::Draw(graphics::Image &image) {
  if (x_ >= 0 && x_ <= image.GetWidth() && y_ >= 0 && y_ <= image.GetHeight()) {
    image.DrawCircle(x_ + 2, y_ + 2, 2, 244, 57, 0);
    image.DrawCircle(x_ + 1, y_ + 1, 1, 252, 155, 0);
  }
}

void Opponent::Draw(graphics::Image &image) {
  image.DrawCircle(x_ + 15, y_ + 15, 15, 237, 71, 0);
  image.DrawCircle(x_ + 15, y_ + 15, 10, 255, 178, 0);
  image.DrawLine(x_ + 14, y_ + 30, x_ + 14, y_ + 40, 0, 229, 69, 8);
  image.DrawLine(x_ + 10, y_ + 10, x_ + 10, y_, 0, 0, 0, 3);
  image.DrawLine(x_ + 19, y_ + 10, x_ + 19, y_, 0, 0, 0, 3);
}

void Opponent::Move(const graphics::Image &game_screen) {
  if (GameElement::IsOutOfBounds(game_screen)) {
    is_active = false;
  } else {
    GameElement::SetX(GameElement::GetX() + 5);
    GameElement::SetY(GameElement::GetY() + 5);
  }
}

void OpponentProjectile::Move(const graphics::Image &game_screen) {
  if (GameElement::IsOutOfBounds(game_screen)) {
    is_active = false;
  } else {
    GameElement::SetX(GameElement::GetX() + 5);
    GameElement::SetY(GameElement::GetY() + 5);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  shoot_tracker++;
  if (shoot_tracker % 5 == 0) {
    shoot_tracker = 0;
    std::unique_ptr<OpponentProjectile> fire_ball =
        std::make_unique<OpponentProjectile>(Opponent::GetX(),
                                             Opponent::GetY());
    return std::move(fire_ball);
  } else {
    return nullptr;
  }
}
