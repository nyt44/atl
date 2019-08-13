#include "Connection.hpp"

#include <boost/interprocess/managed_shared_memory.hpp>

namespace
{
constexpr auto kFixedShmSize = 1024;
}

namespace atl
{
Connection::Connection(const std::string& name) : shm_segment_name_{name + "_shm"}
{
  boost::interprocess::shared_memory_object::remove(shm_segment_name_.c_str());
  boost::interprocess::shared_memory_object shm_segment_object_{boost::interprocess::open_or_create,
                                                                shm_segment_name_.c_str(),
                                                                boost::interprocess::read_write};
  shm_segment_object_.truncate(kFixedShmSize);
}

Connection::~Connection()
{
  boost::interprocess::shared_memory_object::remove(shm_segment_name_.c_str());
}

} // namespace atl
