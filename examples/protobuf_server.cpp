#include <cmath>
#include <string>

#include "atl_client.hpp"
#include "dbg_trace.hpp"
#include "example.pb.h"

int main()
{
  dbg_trace::SetVerbosity(dbg_trace::Level::kInfo);
  LOG_INFO("Server started");

  atl::Client client{1, 2, 2};
  LOG_INFO("Waiting  for data...");

  auto received_data = client.Receive();

  example::ExponentiationArgs request;
  request.ParseFromString(received_data);
  LOG_INFO("Received arguments: base = {}, exponent = {}", request.base(), request.exponent());

  example::ExponentiationResult response;
  response.set_result(static_cast<int>(pow(request.base(), request.exponent())));
  response.set_success(true);
  std::string response_str;
  response.SerializeToString(&response_str);
  client.Send(response_str);
}
