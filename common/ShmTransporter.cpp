#include "ShmTransporter.hpp"

#include <cstring>
#include <exception>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "dbg_trace.hpp"

namespace atl
{

ShmTransporter::ShmTransporter(const std::string& name)
    : managed_shm_{boost::interprocess::open_only, (name + "_shm").c_str()}
{
  auto mtx_pair = managed_shm_.find<boost::interprocess::interprocess_mutex>("mtx");
  LOG_AND_THROW_IF_NULLPTR(mtx_pair.first, "Pointer to mutex is NULL");
  shm_mutex_ = mtx_pair.first;

  auto cnd_pair = managed_shm_.find<boost::interprocess::interprocess_condition>("cnd");
  LOG_AND_THROW_IF_NULLPTR(cnd_pair.first, "Pointer to condition variable is NULL");
  shm_condition_variable_ = cnd_pair.first;
}

void ShmTransporter::Send(const std::string& data)
{
  auto [ptr_to_shm, shm_size] = managed_shm_.find<char>("Data");
  LOG_AND_THROW_IF_NULLPTR(ptr_to_shm, "Pointer to Shm is NULL")

  auto data_size = data.size() + 1;
  if (data_size > shm_size)
  {
    LOG_AND_THROW("Data size: {} is greater than Shm buffer size: {}", data_size, shm_size);
  }

  std::strncpy(ptr_to_shm, data.c_str(), data_size);
  shm_condition_variable_->notify_one();
}

std::string ShmTransporter::Receive()
{
  boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock{*shm_mutex_};
  shm_condition_variable_->wait(lock);

  auto [received_data, size] = managed_shm_.find<char>("Data");
  (void)size;
  LOG_AND_THROW_IF_NULLPTR(received_data, "Pointer to Shm is NULL");

  return std::string{received_data};
}

std::unique_ptr<ShmTransporterInterface> RealTransporterFactoryMethod::CreateTransporter(const std::string& name)
{
  return std::make_unique<ShmTransporter>(name);
}

} // namespace atl
