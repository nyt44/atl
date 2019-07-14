#include <iostream>

#include "ShmTransporter.hpp"

int main()
{
  atl::ShmTransporter transporter{"atl"};
  std::cout << "Waiting  for data..." << '\n';
  transporter.Receive([](void* raw_data)
  {
    auto data_ptr = static_cast<int*>(raw_data);
    std::cout << "Receieved data: " << *data_ptr << std::endl;
  });
}
