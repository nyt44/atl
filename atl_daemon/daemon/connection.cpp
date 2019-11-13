#include "connection.hpp"

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "dbg_trace.hpp"

namespace
{
constexpr auto kFixedShmSize = 1024;
constexpr auto kFixedBufferSize  = 512;
}

namespace atl
{
Connection::Connection(const std::string& name) : shm_segment_name_{name + "_shm"},
                                                  managed_shm_{boost::interprocess::open_or_create,
                                                               shm_segment_name_.c_str(),
                                                               kFixedShmSize}
{
  managed_shm_.find_or_construct<char>("Data")[kFixedBufferSize]();
  managed_shm_.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")();
  managed_shm_.find_or_construct<boost::interprocess::interprocess_condition>("cnd")();

  LOG_DEBUG("Connection {} created", shm_segment_name_);
}

Connection::~Connection()
{
  boost::interprocess::shared_memory_object::remove(shm_segment_name_.c_str());
  LOG_DEBUG("Connection {} deleted", shm_segment_name_);
}

} // namespace atl
