#include <boost/python.hpp>

#include "client.hpp"
#include "exp_calc_server.hpp"
#include "exp_calc_client.hpp"

BOOST_PYTHON_MODULE(py_atl)
{
  using namespace boost::python;

  class_<Client>("client", init<int, int, int>())
    .def("send", &Client::Send)
    .def("receive", &Client::Receive)
  ;
  class_<ExpCalcServer>("exp_calc_server", init<int, int, int>())
    .def("run", &ExpCalcServer::Run)
  ;
  class_<ExpCalcClient>("exp_calc_client", init<int, int, int>())
    .def("calculate", &ExpCalcClient::Calculate)
  ;
}

