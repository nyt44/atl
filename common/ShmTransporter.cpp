#include "ShmTransporter.hpp"

#include <cstring>
#include <exception>

#include <boost/interprocess/sync/scoped_lock.hpp>

namespace atl
{

ShmTransporter::ShmTransporter(const std::string& name)
    : shm_object_{boost::interprocess::open_or_create, (name + "_shm").c_str(), boost::interprocess::read_write},
      shm_region_{shm_object_, boost::interprocess::read_write},
      shm_condition_variable_{boost::interprocess::open_or_create, (name + "_cnd").c_str()},
      shm_mutex_{boost::interprocess::open_or_create, (name + "_mtx").c_str()}
{
}

void ShmTransporter::Send(const std::string& data)
{
  if (data.size() > shm_region_.get_size())
  {
    throw std::runtime_error("The size of data to sent exceeds the shared memory buffer");
  }
  auto ptr_to_shm = shm_region_.get_address();
  std::strncpy(static_cast<char*>(ptr_to_shm), data.c_str(), shm_region_.get_size());
  shm_condition_variable_.notify_one();
}

std::string ShmTransporter::Receive()
{
  auto ptr_to_shm = shm_region_.get_address();
  boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock{shm_mutex_};
  shm_condition_variable_.wait(lock);
  return std::string{static_cast<const char *>(ptr_to_shm)};
}

std::unique_ptr<ShmTransporterInterface> RealTransporterFactoryMethod::CreateTransporter(const std::string& name)
{
  return std::make_unique<ShmTransporter>(name);
}

} // namespace atl
