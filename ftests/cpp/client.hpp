#pragma once

#include <memory>

#include "atl_client.hpp"

class Client
{
 public:
  Client(int src_addr, int dest_addr, int conn_nr);
  void Send(const std::string& data);
  std::string Receive();
 private:
  std::shared_ptr<atl::Client> client_;
};
