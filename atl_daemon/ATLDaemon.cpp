#include <iostream>
#include <string>

#include "DaemonLoop.hpp"
#include "Connection.hpp"
#include "ConnectionMapWrapper.hpp"
#include "ConnectionDiary.hpp"
#include "ShmTransporter.hpp"
#include "dbg_trace.hpp"

int main()
{
  dbg_trace::SetVerbosity(dbg_trace::Level::kInfo);
  LOG_INFO("ATL Daemon started");

  std::string daemon_stream_name{"atl_daemon_stream"};
  atl::Connection conn{daemon_stream_name};

  atl::ConnectionMapWrapper connection_map_wrapper;
  atl::ConnectionDiary connection_diary{connection_map_wrapper};
  atl::ShmTransporter transporter{daemon_stream_name};
  atl::DaemonLoop daemon_loop{transporter, connection_diary};

  daemon_loop.Run();
  LOG_INFO("ATL Daemon closed normally");
}
