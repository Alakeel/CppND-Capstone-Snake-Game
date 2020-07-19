#include "helper.h"

bool Helper::Prompt(const std::string aMsg, const char aKeyChar)
{
  char flag;
  std::cout << aMsg << std::endl;
  std::cin >> flag;
  return flag == tolower(aKeyChar) || flag == toupper(aKeyChar) ? true : false;
}
