#pragma once

#include <memory>

#include "atl_client.hpp"

class ExpCalcClient
{
public:
  ExpCalcClient(int src_addr, int dest_addr, int conn_nr);
  int Calculate(int base, int exponent);
private:
  std::shared_ptr<atl::Client> client_;
};
