#include "controller.h"
#include "game.h"
#include "helper.h"
#include "memory"
#include "renderer.h"
#include <iostream>

using namespace GuiSettings; // from Helper class

int main()
{
  bool restartFlag{true};
  while (restartFlag)
  {
    bool running{true};
    // Put game instance inside a scope. Fix for Alt-F4
    while (running)
    {
      // Setup game, controller and renderer
      std::unique_ptr<Game> gameInstance = std::make_unique<Game>(kGridWidth, kGridHeight);
      auto renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
      auto contoller = std::make_unique<Controller>();
      // Start Game
      running = gameInstance->Run(contoller, renderer, kMsPerFrame);
      // Game Ended - Display Results
      std::cout << "============================================\n";
      std::cout << "*                Results                   *\n";
      std::cout << "Score: " << gameInstance->GetScore() << "\n";
      std::cout << "Size: " << gameInstance->GetSize() << "\n";
      std::cout << "============================================\n";
    }
    // Prompt To Restart
    restartFlag = Helper::Prompt("Restart The Game ? (y/n)", 'y') ? true : false;
  }
  return 0;
}
