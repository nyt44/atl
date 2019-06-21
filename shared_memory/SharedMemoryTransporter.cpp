#include "SharedMemoryTransporter.hpp"

#include <cstring>

#include <boost/interprocess/sync/scoped_lock.hpp>

SharedMemoryTransporter::SharedMemoryTransporter(const std::string& name)
    : shm_object_{boost::interprocess::open_or_create, (name + "_shm").c_str(), boost::interprocess::read_write},
      shm_region_{shm_object_, boost::interprocess::read_write},
      shm_condition_variable_{boost::interprocess::open_or_create, (name + "_cnd").c_str()},
      shm_mutex_{boost::interprocess::open_or_create, (name + "_mtx").c_str()} {}

void SharedMemoryTransporter::Send(void *data, size_t size)
{
  if (size > shm_region_.get_size())
  {
    throw TooBigDataSizeErrror("The size of data to sent exceeds the shared memory buffer");
  }
  auto ptr_to_shm = shm_region_.get_address();
  std::memcpy(ptr_to_shm, data, size);
  shm_condition_variable_.notify_one();
}

void SharedMemoryTransporter::Receive(std::function<void (void *)> callback)
{
  auto ptr_to_shm = shm_region_.get_address();
  boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock{shm_mutex_};
  shm_condition_variable_.wait(lock);
  callback(ptr_to_shm);
}

TooBigDataSizeErrror::TooBigDataSizeErrror(const std::string& msg) : std::runtime_error{msg} {}


