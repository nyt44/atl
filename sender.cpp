#include <iostream>

#include "SharedMemoryTransporter.hpp"

int main()
{
  SharedMemoryTransporter transporter{"atl"};

  int data = 999;
  transporter.Send(static_cast<void*>(&data), sizeof(data));
}
