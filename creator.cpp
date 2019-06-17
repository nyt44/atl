#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;

int main()
{
  shared_memory_object shdmem{open_or_create, "atl_shm", read_write};
  shdmem.truncate(1024);
}
