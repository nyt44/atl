#pragma once

#include "connection_diary_interface.hpp"

#include "connection_map_wrapper_interface.hpp"

namespace atl
{

class ConnectionDiary : public ConnectionDiaryInterface
{
 public:
  explicit ConnectionDiary(ConnectionMapWrapperInterface& map_wrapper);
  bool AddConnection(const std::string& connection_str) override;
  bool DeleteConnection(const std::string& connection_str) override;

 private:
  ConnectionMapWrapperInterface& map_wrapper_;
};

} // namespace atl
