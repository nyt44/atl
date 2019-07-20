#pragma once

#include "ShmTransporterInterface.hpp"

#include <string>
#include <functional>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

namespace atl
{

class ShmTransporter : public ShmTransporterInterface
{
 public:
  explicit ShmTransporter(const std::string& name);
  void Send(void* data, size_t size) override;
  void Receive(std::function<void(void*)> callback) override;
  std::string Receive() override;

 private:
  boost::interprocess::shared_memory_object shm_object_;
  boost::interprocess::mapped_region shm_region_;
  boost::interprocess::named_condition shm_condition_variable_;
  boost::interprocess::named_mutex shm_mutex_;
};

class RealTransporterFactoryMethod : public TransporterFactoryMethod
{
 public:
  std::unique_ptr<ShmTransporterInterface> CreateTransporter(const std::string& name) override;
};

} // namespace atl
