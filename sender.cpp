#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
  shared_memory_object shdmem{open_or_create, "atl_shm", read_write};
  mapped_region region{shdmem, read_write};
  int *i1 = static_cast<int*>(region.get_address());

  named_condition named_cnd{open_or_create, "atl_cnd"};

  *i1 = 101;

  named_cnd.notify_all();
}
