#pragma once

#include "ShmTransporterInterface.hpp"

#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

namespace atl
{

class ShmTransporter : public ShmTransporterInterface
{
 public:
  explicit ShmTransporter(const std::string& name);
  void Send(const std::string& data) override;
  std::string Receive() override;

 private:
  boost::interprocess::managed_shared_memory managed_shm_;
  boost::interprocess::interprocess_mutex* shm_mutex_;
  boost::interprocess::interprocess_condition* shm_condition_variable_;
};

class RealTransporterFactoryMethod : public TransporterFactoryMethod
{
 public:
  std::unique_ptr<ShmTransporterInterface> CreateTransporter(const std::string& name) override;
};

} // namespace atl
