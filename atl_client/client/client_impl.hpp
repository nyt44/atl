#pragma once

#include <string>
#include <memory>

#include "shm_transporter_interface.hpp"

namespace atl
{

class ClientImpl
{
 public:
  ClientImpl(const std::string& conn_str, ShmTransporterInterface& daemon_stream,
             TransporterFactoryMethod& transporter_factory);
  ~ClientImpl();
  void Send(const std::string& data);
  std::string Receive();

 private:
  ShmTransporterInterface& daemon_stream_;
  TransporterFactoryMethod& transporter_factory_;
  std::string conn_str_;
  std::unique_ptr<ShmTransporterInterface> transporter_;
};

}
