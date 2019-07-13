#pragma once

#include <string>

namespace atl
{
class Connection
{
 public:
  explicit Connection(std::string name);
  ~Connection();
 private:
  std::string shm_segment_name_;
};

} // namespace atl;
