#pragma once

#include <string>

namespace atl
{
class Connection
{
 public:
  explicit Connection(const std::string& name);
  ~Connection();
 private:
  std::string shm_segment_name_;
};

} // namespace atl;
