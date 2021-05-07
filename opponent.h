
#ifndef OPPONENT_H
#define OPPONENT_H
#include <memory>

#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}

  OpponentProjectile(int x, int y) : GameElement(x, y, 10, 10) {}

  void Draw(graphics::Image &game_screen) override;

  void Move(const graphics::Image &game_screen) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}

  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &game_screen) override;

  void Move(const graphics::Image &game_screen) override;

  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int shoot_tracker = 0;
};

#endif
