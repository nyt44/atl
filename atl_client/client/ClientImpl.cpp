#include "ClientImpl.hpp"

#include <exception>

#include "dbg_trace.hpp"

namespace atl
{

ClientImpl::ClientImpl(const std::string& conn_str, ShmTransporterInterface& daemon_stream,
                       TransporterFactoryMethod& transporter_factory)
  : daemon_stream_{daemon_stream}, transporter_factory_{transporter_factory}, conn_str_{conn_str}
{
  auto add_request_str = "+" + conn_str_;
  daemon_stream_.Send(add_request_str);
  auto response = daemon_stream_.Receive();

  if (response == "ok")
  {
    transporter_ = transporter_factory_.CreateTransporter(conn_str_);
  }
  else
  {
    std::string err_msg = "Channel requesting is unsuccessfull. Response from daemon: " + response;
    LOG_ERROR(err_msg);
    throw std::runtime_error{err_msg};
  }
}

ClientImpl::~ClientImpl()
{
  try
  {
    auto del_request_str = "-" + conn_str_;
    daemon_stream_.Send(del_request_str);
    // TODO Receive
  }
  catch (...)
  {
    LOG_ERROR("ATL Client destruction failed");
  }
}

void ClientImpl::Send(const std::string& data)
{
  transporter_->Send(data);
}

std::string ClientImpl::Receive()
{
  return transporter_->Receive();
}

}
