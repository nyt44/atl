#pragma once

#include <string>
#include <memory>

namespace atl
{

class ShmTransporterInterface
{
 public:
  virtual ~ShmTransporterInterface() = default;
  virtual void Send(const std::string& data) = 0;
  virtual std::string Receive() = 0;
};

class TransporterFactoryMethod
{
 public:
  virtual ~TransporterFactoryMethod() = default;
  virtual std::unique_ptr<ShmTransporterInterface> CreateTransporter(const std::string&) = 0;
};

} // namespace atl
