#include "DaemonLoop.hpp"

namespace atl
{

DaemonLoop::DaemonLoop(ShmTransporterInterface& transporter, ConnectionDiaryInterface& diary)
  : transporter_{transporter}, diary_{diary} {}

void DaemonLoop::Run()
{
  std::string command;

  while ((command = transporter_.Receive()) != "quit")
  {
    if (command.at(0) == '+')
    {
      HandleCommand(&ConnectionDiaryInterface::AddConnection, command.substr(1));
    }
    else if (command.at(0) == '-')
    {
      HandleCommand(&ConnectionDiaryInterface::DeleteConnection, command.substr(1));
    }
  }
}

// Private methods

void DaemonLoop::HandleCommand(bool (atl::ConnectionDiaryInterface::* diary_method_ptr)(const std::string&),
            const std::string& connsection_str)
{
  std::string response;
  if ((diary_.*diary_method_ptr)(connsection_str))
  {
    response = "ok";
  }
  else
  {
    response = "nok";
  }
  transporter_.Send(static_cast<void*>(response.data()), response.size());
}

} // namespace atl
