#pragma once

#include "ShmTransporterInterface.hpp"
#include "ConnectionDiaryInterface.hpp"
#include "Connection.hpp"

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
