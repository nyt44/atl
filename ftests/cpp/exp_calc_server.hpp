#pragma once

#include <memory>

#include "atl_client.hpp"

class ExpCalcServer
{
public:
  ExpCalcServer(int src_addr, int dest_addr, int conn_nr);
  void Run();
private:
  std::shared_ptr<atl::Client> client_;
};
