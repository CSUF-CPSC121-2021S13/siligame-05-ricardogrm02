#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 private:
  graphics::Image game_screen;
  std::vector<std::unique_ptr<Opponent>> opponent_list;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_projectile_list;
  std::vector<std::unique_ptr<PlayerProjectile>> player_projectile_list;
  int score = 0;
  bool has_lost = false;
  Player player;

 public:
  Game() : game_screen(800, 600) {}

  Game(int game_width, int game_height)
      : game_screen(game_width, game_height) {}

  graphics::Image &GetGameScreen() { return game_screen; }

  std::vector<std::unique_ptr<Opponent>> &GetOpponents() {
    return opponent_list;
  }

  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponent_projectile_list;
  }

  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return player_projectile_list;
  }

  Player &GetPlayer() { return player; }

  int GetScore() const { return score; }

  bool HasLost() const { return has_lost; }

  void LaunchProjectiles();

  void RemoveInactive();

  void CreateOpponents() {
    std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>(300, 300);
    opponent_list.push_back(std::move(opponent));
  }

  void MoveGameElements();

  void Init();

  void UpdateScreen();

  void Start();

  void FilterIntersections();

  void OnAnimationStep() override;

  void OnMouseEvent(const graphics::MouseEvent &event) override;
};
#endif
