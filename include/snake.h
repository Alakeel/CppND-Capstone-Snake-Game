#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include <vector>

class Snake
{
public:
  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight
  };

  Snake(int grid_width, int grid_height);
  ~Snake() = default;
  Snake(const Snake &source);
  Snake& operator=(const Snake &source);
  Snake(Snake &&source);
  Snake& operator=(Snake &&source);

  Direction direction = Direction::kUp;

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);

  void SetSpeed(float aSpeed);
  void SetAccelerationRate(float aAccRate);
  void SetAlive(bool aAlive);

  float Speed() const;
  float AccelerationRate() const;
  float Alive() const;

  int Size() const;
  float HeadY() const;
  float HeadX() const;

  std::vector<SDL_Point> Body() const;

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  std::vector<SDL_Point> body;
  bool growing{false};
  int size{1};

  int grid_width;
  int grid_height;

  float head_x;
  float head_y;

  float speed{0.1f};
  float accelerationRate{0.02};
  bool alive{true};
};

#endif
