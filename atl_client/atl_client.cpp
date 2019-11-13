#include "atl_client.hpp"

using std::to_string;

namespace atl
{

Client::Client(int src_addr, int dest_addr, int conn_nr)
  : daemon_stream_{"atl_daemon_stream"}, transporter_factory_{},
    client_impl_{to_string(src_addr) + "->" + to_string(dest_addr) + ":" + to_string(conn_nr),
                 daemon_stream_, transporter_factory_}
{
}

void Client::Send(const std::string& data)
{
  client_impl_.Send(data);
}

std::string Client::Receive()
{
  return client_impl_.Receive();
}

}
