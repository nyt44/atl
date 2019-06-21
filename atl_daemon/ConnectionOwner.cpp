#include "ConnectionOwner.hpp"

#include <boost/interprocess/managed_shared_memory.hpp>

namespace
{
constexpr auto kFixedShmSize = 1024;
}

ConnectionOwner::ConnectionOwner(std::string name) : shm_segment_name_{std::move(name) + "_shm"}
{
  boost::interprocess::shared_memory_object shm_segment_object{boost::interprocess::open_or_create,
                                                               shm_segment_name_.c_str(),
                                                               boost::interprocess::read_write};
  shm_segment_object.truncate(kFixedShmSize);
}

ConnectionOwner::~ConnectionOwner()
{
  boost::interprocess::shared_memory_object::remove(shm_segment_name_.c_str());
}
