#include "controller.h"

#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "memory"

void Controller::ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->Size() == 1) snake->direction = input;
  return;
}

void Controller::HandleInput(bool &running, std::shared_ptr<Snake> &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;

        case SDLK_ESCAPE: // pause game on escape
          SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "Game Paused",
                         "You've paused the game. Click OK to resume.",
                         NULL);
          break;
      }
    }
  }
}
