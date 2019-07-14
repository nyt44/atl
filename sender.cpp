#include <iostream>

#include "ShmTransporter.hpp"

int main()
{
  atl::ShmTransporter transporter{"atl"};
  int data = 999;
  transporter.Send(static_cast<void*>(&data), sizeof(data));
}
