#include "snake.h"
#include <cmath>
#include <iostream>

// Constructor
Snake::Snake(int grid_width, int grid_height)
    : grid_width(grid_width),
      grid_height(grid_height),
      head_x(grid_width / 2),
      head_y(grid_height / 2) {}

// Copy constructor
Snake::Snake(const Snake &source)
    : grid_width(source.grid_width),
      grid_height(source.grid_height),
      head_x(source.head_x),
      head_y(source.head_y)
{
}

// Copy assignment operator
Snake &Snake::operator=(const Snake &source)
{
  return *this;
}

// Move constructor
Snake::Snake(Snake &&source)
    : grid_width(source.grid_width),
      grid_height(source.grid_height),
      head_x(source.head_x),
      head_y(source.head_y)
{
}

// Move assignment operator
Snake &Snake::operator=(Snake &&source)
{
  return *this;
}

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else
  {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body)
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}

void Snake::SetSpeed(float aSpeed)
{
  speed = aSpeed;
}

void Snake::SetAccelerationRate(float aAccRate)
{
  accelerationRate = aAccRate;
}

void Snake::SetAlive(bool aAlive)
{
  alive = aAlive;
}

float Snake::Speed() const
{
  return speed;
}

float Snake::AccelerationRate() const
{
  return accelerationRate;
}

float Snake::Alive() const
{
  return alive;
}

float Snake::HeadY() const
{
  return head_y;
}
float Snake::HeadX() const
{
  return head_x;
}

int Snake::Size() const
{
  return size;
}

std::vector<SDL_Point> Snake::Body() const
{
  return body;
}
