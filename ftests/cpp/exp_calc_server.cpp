#include "exp_calc_server.hpp"

#include "example.pb.h"


ExpCalcServer::ExpCalcServer(int src_addr, int dest_addr, int conn_nr)
  : client_{std::make_shared<atl::Client>(src_addr, dest_addr, conn_nr)} {}

void ExpCalcServer::Run()
{
  auto received_data = client_->Receive();
  example::ExponentiationArgs request;
  request.ParseFromString(received_data);

  example::ExponentiationResult response;
  response.set_result(static_cast<int>(pow(request.base(), request.exponent())));
  response.set_success(true);
  std::string response_str;
  response.SerializeToString(&response_str);
  client_->Send(response_str);
}
