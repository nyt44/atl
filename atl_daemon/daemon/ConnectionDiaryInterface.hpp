#pragma once

#include <string>

namespace atl
{

class ConnectionDiaryInterface
{
 public:
  virtual ~ConnectionDiaryInterface() = default;
  virtual bool AddConnection(const std::string& connection_str) = 0;
  virtual bool DeleteConnection(const std::string& connection_str) = 0;
};

} // namespace atl
