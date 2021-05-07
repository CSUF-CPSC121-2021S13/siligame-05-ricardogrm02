#ifndef PLAYER_H
#define PLAYER_H

#include "game_element.h"
#include "opponent.h"

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}

  PlayerProjectile(int x, int y) : GameElement(x, y, 10, 10) {}

  void Draw(graphics::Image &game_screen) override;

  void Move(const graphics::Image &game_screen) override;
};

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}

  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &game_screen) override;
  // prototype for opponent collision

  void Move(const graphics::Image &game_screen) override;
};

#endif
