#include "atl_client.hpp"
#include "dbg_trace.hpp"


int main()
{
  dbg_trace::SetVerbosity(dbg_trace::Level::kInfo);
  LOG_INFO("Receiver started");

  atl::Client client{1, 2, 1};
  LOG_INFO("Waiting  for data...");
  auto received_data = client.Receive();
  LOG_INFO("Received data: {}", received_data);
}
