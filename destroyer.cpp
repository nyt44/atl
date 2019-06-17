#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
  bool removed = shared_memory_object::remove("atl_shm");
  std::cout << std::boolalpha << removed << '\n';
}
