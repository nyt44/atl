#include <iostream>
#include <string>

#include "ATLClient.hpp"

int main()
{
  atl::Client client{1, 2, 1};
  std::string data_to_send{"example data..."};
  client.Send(data_to_send);
}
