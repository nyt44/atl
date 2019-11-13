#pragma once

#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace atl
{
class Connection
{
 public:
  explicit Connection(const std::string& name);
  Connection(const Connection&) = delete;
  Connection& operator=(const Connection&) = delete;
  ~Connection();
 private:
  std::string shm_segment_name_;
  boost::interprocess::managed_shared_memory managed_shm_;
};

} // namespace atl;
