#include "client.hpp"

Client::Client(int src_addr, int dest_addr, int conn_nr)
    : client_{std::make_shared<atl::Client>(src_addr, dest_addr, conn_nr)} {}

void Client::Send(const std::string& data)
{
  client_->Send(data);
}

std::string Client::Receive()
{
  return client_->Receive();
}
