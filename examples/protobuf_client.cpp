#include <cstdlib>
#include <string>

#include "atl_client.hpp"
#include "dbg_trace.hpp"
#include "example.pb.h"

int main(int argc, char **argv)
{
  dbg_trace::SetVerbosity(dbg_trace::Level::kInfo);
  LOG_INFO("Client started");

  if (argc != 3)
  {
    LOG_ERROR("Invalid number of arguments");
    return EXIT_FAILURE;
  }

  auto base = std::stoi(argv[1]);
  auto exponent = std::stoi(argv[2]);

  example::ExponentiationArgs request;
  request.set_base(base);
  request.set_exponent(exponent);
  std::string data_to_send;
  request.SerializeToString(&data_to_send);

  atl::Client client{1, 2, 2};
  client.Send(data_to_send);

  auto result_str = client.Receive();
  example::ExponentiationResult result;
  result.ParseFromString(result_str);

  if (!result.success())
  {
    LOG_ERROR("Error received from server");
  }
  else
  {
    LOG_INFO("Result: {}", result.result());
  }
}
