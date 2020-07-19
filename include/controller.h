#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>
class BaseController
{
  public:
    virtual void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const = 0;
};

class Controller : public BaseController
{
  public:
    Controller() = default;
    ~Controller() = default;
    void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const override;

  private:
    void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input,
                        Snake::Direction opposite) const;
};

#endif
