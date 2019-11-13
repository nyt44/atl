#include "atl_client.hpp"

#include <memory>
#include <boost/python.hpp>

class client
{
 public:
  client(int src_addr, int dest_addr, int conn_nr)
    : client_{std::make_shared<atl::Client>(src_addr, dest_addr, conn_nr)} {}
  void Send(const std::string& data)
  {
    client_->Send(data);
  }
  std::string Receive()
  {
    return client_->Receive();
  }
 private:
  std::shared_ptr<atl::Client> client_;
};


BOOST_PYTHON_MODULE(py_atl)
{
  using namespace boost::python;

  class_<client>("client", init<int, int, int>())
    .def("send", &client::Send)
    .def("receive", &client::Receive)
  ;
}

