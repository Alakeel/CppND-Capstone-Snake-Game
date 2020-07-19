#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(std::make_shared<Snake>(grid_width, grid_height)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{
  PlaceFood();
}

int Game::Run(std::unique_ptr<Controller> const &controller, std::unique_ptr<Renderer> &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller->HandleInput(running, snake);
    Update();
    auto respone = renderer->Render(snake, food);
    if (!respone) // no respone when snake is dead and messageBox is checked.
    {
      End();
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  return false;
}

void Game::End()
{
  running = false;
  snake->SetAlive(false);
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if (!snake->Alive())
    return;

  snake->Update();

  int new_x = static_cast<int>(snake->HeadX());
  int new_y = static_cast<int>(snake->HeadY());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->SetSpeed(snake->Speed() + snake->AccelerationRate());
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->Size(); }

