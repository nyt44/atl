#include "ClientImpl.hpp"

#include <exception>

namespace atl
{

ClientImpl::ClientImpl(const std::string& conn_str, ShmTransporterInterface& daemon_stream,
                       TransporterFactoryMethod& transporter_factory)
  : daemon_stream_{daemon_stream}, transporter_factory_{transporter_factory}, conn_str_{conn_str}
{
  auto add_request_str = "+" + conn_str_;
  daemon_stream_.Send(static_cast<void*>(add_request_str.data()), add_request_str.size());
  auto response = daemon_stream_.Receive();

  if (response == "ok")
  {
    transporter_ = transporter_factory_.CreateTransporter(conn_str_);
  }
  else
  {
    throw std::runtime_error{"Channel requesting is unsuccessfull"};
  }
}

ClientImpl::~ClientImpl()
{
  try
  {
    auto del_request_str = "-" + conn_str_;
    daemon_stream_.Send(static_cast<void*>(del_request_str.data()), del_request_str.size());
    // TODO Receive
  }
  catch (...)
  {
    // TODO print sth here
  }
}

void ClientImpl::Send(void * data, size_t size)
{
  transporter_->Send(data, size);
}

std::string ClientImpl::Receive()
{
  return transporter_->Receive();
}

}
