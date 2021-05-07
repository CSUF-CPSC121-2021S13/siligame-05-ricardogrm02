#include "game.h"

void Game::Init() {
  game_screen.AddMouseEventListener(*this);
  game_screen.AddAnimationEventListener(*this);
  player.SetX(player.GetX() + 500);
  player.SetY(player.GetY() + 500);
}

void Game::UpdateScreen() {
  std::string score_tracker = "Score: " + std::to_string(score);

  game_screen.DrawRectangle(0, 0, game_screen.GetWidth(),
                            game_screen.GetHeight(), 255, 255, 255);

  game_screen.DrawText(0, 0, score_tracker, 12, 0, 0, 0);
  if (has_lost == true) {
    game_screen.DrawText((game_screen.GetWidth() * 0.5) - 200,
                         (game_screen.GetHeight() * 0.5) - 200, "GAME OVER", 80,
                         255, 20, 20);
  }

  for (int i = 0; i < opponent_list.size(); i++) {
    if (opponent_list[i]->GetIsActive()) {
      opponent_list[i]->Draw(game_screen);
    }
  }

  for (int j = 0; j < opponent_projectile_list.size(); j++) {
    if (opponent_projectile_list[j]->GetIsActive()) {
      opponent_projectile_list[j]->Draw(game_screen);
    }
  }

  for (int h = 0; h < player_projectile_list.size(); h++) {
    if (player_projectile_list[h]->GetIsActive()) {
      player_projectile_list[h]->Draw(game_screen);
    }
  }
  if (player.GetIsActive()) {
    player.Draw(game_screen);
  }
}

void Game::Start() { game_screen.ShowUntilClosed(); }

void Game::RemoveInactive() {
  for (int i = opponent_list.size() - 1; i >= 0; i--) {
    if (!(opponent_list[i]->GetIsActive())) {
      opponent_list.erase(opponent_list.begin() + i);
    }
  }
  for (int i = opponent_projectile_list.size() - 1; i >= 0; i--) {
    if (!(opponent_projectile_list[i]->GetIsActive())) {
      opponent_projectile_list.erase(opponent_projectile_list.begin() + i);
    }
  }
  for (int i = player_projectile_list.size() - 1; i >= 0; i--) {
    if (!(player_projectile_list[i]->GetIsActive())) {
      player_projectile_list.erase(player_projectile_list.begin() + i);
    }
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_list.size(); i++) {
    std::unique_ptr<OpponentProjectile> fire_ball =
        std::make_unique<OpponentProjectile>(opponent_list[i]->GetX(),
                                             opponent_list[i]->GetY());
    if (opponent_list[i]->LaunchProjectile() != nullptr) {
      opponent_projectile_list.push_back(std::move(fire_ball));
    }
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_list.size(); i++) {
    if (opponent_list[i]->GameElement::GetIsActive()) {
      opponent_list[i]->Move(game_screen);
    }
  }

  for (int j = 0; j < opponent_projectile_list.size(); j++) {
    if (opponent_projectile_list[j]->GetIsActive()) {
      opponent_projectile_list[j]->Move(game_screen);
    }
  }

  for (int h = 0; h < player_projectile_list.size(); h++) {
    if (player_projectile_list[h]->GetIsActive()) {
      player_projectile_list[h]->Move(game_screen);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_list.size(); i++) {
    if (player.IntersectsWith(opponent_list[i].get()) && player.GetIsActive()) {
      opponent_list[i]->SetIsActive(false);
      player.SetIsActive(false);
      has_lost = true;
    }
  }

  for (int j = 0; j < opponent_projectile_list.size(); j++) {
    if (player.IntersectsWith(opponent_projectile_list[j].get()) &&
        player.GetIsActive()) {
      opponent_projectile_list[j]->SetIsActive(false);
      player.SetIsActive(false);
      has_lost = true;
    }
  }

  for (int h = 0; h < player_projectile_list.size(); h++) {
    for (int j = 0; j < opponent_list.size(); j++) {
      if (player_projectile_list[h]->IntersectsWith(opponent_list[j].get()) &&
          player_projectile_list[h]->GetIsActive()) {
        player_projectile_list[h]->SetIsActive(false);
        opponent_list[j]->SetIsActive(false);

        if (player.GetIsActive()) {
          score += 1;
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (opponent_list.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetX() < game_screen.GetWidth() && event.GetX() > 0 &&
      event.GetY() > 0 && event.GetY() < game_screen.GetHeight()) {
    player.SetX(event.GetX() - 25);
    player.SetY(event.GetY() - 25);
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> ice_ball =
        std::make_unique<PlayerProjectile>(player.GetX(), player.GetY());
    player_projectile_list.push_back(std::move(ice_ball));
  }
}
