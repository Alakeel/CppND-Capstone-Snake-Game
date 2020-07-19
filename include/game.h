#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "memory"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);

  //! return false if game is not running anymore.
  int Run(std::unique_ptr<Controller> const &controller,  std::unique_ptr<Renderer> &renderer,
           std::size_t target_frame_duration);
  void End();

  int GetScore() const;
  int GetSize() const;

 private:
  bool running;
  std::shared_ptr<Snake> snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif
