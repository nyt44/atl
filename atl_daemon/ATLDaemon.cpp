#include <iostream>

#include "ConnectionOwner.hpp"

int main()
{
  ConnectionOwner connection{"atl"};

  std::cout << "Press any key to close daemon...";
  std::cin.get();
}
