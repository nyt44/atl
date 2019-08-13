#include <iostream>

#include "ATLClient.hpp"

int main()
{
  atl::Client client{1, 2, 1};
  std::cout << "Waiting  for data..." << '\n';
  auto received_data = client.Receive();
  std::cout << "Received data: " << received_data << std::endl;
}
