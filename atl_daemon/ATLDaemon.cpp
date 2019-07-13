#include <iostream>

#include "Connection.hpp"

int main()
{
  atl::Connection connection{"atl"};

  std::cout << "Press any key to close daemon...";
  std::cin.get();
}
