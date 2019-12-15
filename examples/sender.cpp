#include <string>

#include "atl_client.hpp"
#include "dbg_trace.hpp"

int main()
{
  dbg_trace::SetVerbosity(dbg_trace::Level::kInfo);
  LOG_INFO("Sender started");

  atl::Client client{1, 2, 1};
  std::string data_to_send{"example data..."};
  client.Send(data_to_send);
}
