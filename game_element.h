#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "cpputils/graphics/image.h"

class GameElement {
 protected:
  int x_, y_, width_, height_;
  bool is_active = true;

 public:
  GameElement() : x_(0), y_(0), width_(10), height_(10) {}

  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}

  int GetX() const { return x_; }

  int GetY() const { return y_; }

  int GetWidth() const { return width_; }

  int GetHeight() const { return height_; }

  bool GetIsActive() const { return is_active; }

  void SetIsActive(bool new_status) { is_active = new_status; }

  void SetX(int x) { x_ = x; }

  void SetY(int y) { y_ = y; }

  virtual void Draw(graphics::Image &game_screen) = 0;

  virtual void Move(const graphics::Image &game_screen) = 0;

  bool IsOutOfBounds(const graphics::Image &game_screen);

  bool IntersectsWith(GameElement *element);
};
#endif
