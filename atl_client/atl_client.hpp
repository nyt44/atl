#pragma once

#include <string>

#include "client_impl.hpp"
#include "shm_transporter.hpp"

namespace atl
{

class Client
{
 public:
  Client(int src_addr, int dest_addr, int conn_nr);
  void Send(const std::string& data);
  std::string Receive();

 private:
  ShmTransporter daemon_stream_;
  RealTransporterFactoryMethod transporter_factory_;
  ClientImpl client_impl_;
};

}
