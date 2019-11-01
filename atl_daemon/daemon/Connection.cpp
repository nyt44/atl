#include "Connection.hpp"

#include <boost/interprocess/managed_shared_memory.hpp>

#include "dbg_trace.hpp"

namespace
{
constexpr auto kFixedShmSize = 1024;
}

namespace atl
{
Connection::Connection(const std::string& name) : shm_segment_name_{name + "_shm"}
{
  boost::interprocess::shared_memory_object shm_segment_object_{boost::interprocess::open_or_create,
                                                                shm_segment_name_.c_str(),
                                                                boost::interprocess::read_write};
  shm_segment_object_.truncate(kFixedShmSize);
  LOG_DEBUG("Connection {} created", shm_segment_name_);
}

Connection::~Connection()
{
  boost::interprocess::shared_memory_object::remove(shm_segment_name_.c_str());
  LOG_DEBUG("Connection {} deleted", shm_segment_name_);
}

} // namespace atl
