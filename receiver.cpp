#include <iostream>

#include "SharedMemoryTransporter.hpp"

int main()
{
  SharedMemoryTransporter transporter{"atl"};
  std::cout << "Waiting  for data..." << '\n';
  transporter.Receive([](void* raw_data)
  {
    auto data_ptr = static_cast<int*>(raw_data);
    std::cout << "Receieved data: " << *data_ptr << std::endl;
  });
}
