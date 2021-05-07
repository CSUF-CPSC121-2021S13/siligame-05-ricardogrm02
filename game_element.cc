#include "game_element.h"

bool GameElement::IsOutOfBounds(const graphics::Image& game_screen) {
  if (x_ < 0 || y_ < 0 || x_ + width_ > game_screen.GetWidth() ||
      y_ + height_ > game_screen.GetHeight()) {
    return true;
  } else {
    return false;
  }
}

bool GameElement::IntersectsWith(GameElement* element) {
  return !(x_ > element->GetX() + element->GetWidth() ||
           element->GetX() > GetX() + GetWidth() ||
           y_ > element->GetY() + element->GetHeight() ||
           element->GetY() > GetY() + GetHeight());
}
