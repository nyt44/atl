#pragma once

#include "shm_transporter_interface.hpp"
#include "connection_diary_interface.hpp"
#include "connection.hpp"

namespace atl
{

class DaemonLoop
{
 public:
  DaemonLoop(ShmTransporterInterface& transporter, ConnectionDiaryInterface& diary);
  void Run();

 private:
  void HandleCommand(bool (atl::ConnectionDiaryInterface::* diary_method_ptr)(const std::string&),
              const std::string& connsection_str);

  ShmTransporterInterface& transporter_;
  ConnectionDiaryInterface& diary_;
};

}
