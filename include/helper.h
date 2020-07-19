#ifndef HELPER_H
#define HELPER_H

#include <cctype>
#include <iostream>

namespace GuiSettings {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
}

class Helper
{
public:
//! Display a prompt for user to enter char key.
static bool Prompt(const std::string aMsg, const char aKeyChar);
};

#endif

