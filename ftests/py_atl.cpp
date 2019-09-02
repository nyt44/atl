#include "ATLClient.hpp"

#include <memory>
#include <boost/python.hpp>

class AtlClientWrapper
{
 public:
  AtlClientWrapper(int src_addr, int dest_addr, int conn_nr)
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

  class_<AtlClientWrapper>("AtlClientWrapper", init<int, int, int>())
    .def("Send", &AtlClientWrapper::Send)
    .def("Receive", &AtlClientWrapper::Receive)
  ;
}

