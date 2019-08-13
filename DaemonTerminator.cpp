#include <string>

#include "ShmTransporter.hpp"

int main()
{
  atl::ShmTransporter transporter{"atl_daemon_stream"};
  std::string data_to_send{"quit"};
  transporter.Send(data_to_send);
}
