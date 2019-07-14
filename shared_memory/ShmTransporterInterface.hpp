#pragma once

#include <functional>
#include <string>

namespace atl
{

class ShmTransporterInterface
{
 public:
  virtual ~ShmTransporterInterface() = default;
  virtual void Send(void* data, size_t size) = 0;
  virtual void Receive(std::function<void(void*)> callback) = 0;
  virtual std::string Receive() = 0;
};

} // namespace atl
