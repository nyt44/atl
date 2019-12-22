#include "exp_calc_client.hpp"

#include "example.pb.h"

ExpCalcClient::ExpCalcClient(int src_addr, int dest_addr, int conn_nr)
  : client_{std::make_shared<atl::Client>(src_addr, dest_addr, conn_nr)} {}

int ExpCalcClient::Calculate(int base, int exponent)
{

  example::ExponentiationArgs request;
  request.set_base(base);
  request.set_exponent(exponent);
  std::string data_to_send;
  request.SerializeToString(&data_to_send);

  client_->Send(data_to_send);

  auto result_str = client_->Receive();
  example::ExponentiationResult result;
  result.ParseFromString(result_str);

  return result.result();
}
