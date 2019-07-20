#pragma once

#include <string>
#include <memory>

#include <ShmTransporterInterface.hpp>

namespace atl
{

class ClientImpl
{
 public:
  ClientImpl(const std::string& conn_str, ShmTransporterInterface& daemon_stream,
             TransporterFactoryMethod& transporter_factory);
  ~ClientImpl();
  void Send(void* data, size_t size);
  std::string Receive();

 private:
  ShmTransporterInterface& daemon_stream_;
  TransporterFactoryMethod& transporter_factory_;
  std::string conn_str_;
  std::unique_ptr<ShmTransporterInterface> transporter_;
};

}
