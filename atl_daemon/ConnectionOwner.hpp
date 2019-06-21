#pragma once

#include <string>

class ConnectionOwner
{
 public:
  explicit ConnectionOwner(std::string name);
  ~ConnectionOwner();
 private:
  std::string shm_segment_name_;
};
