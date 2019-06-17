#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
  shared_memory_object shdmem{open_or_create, "atl_shm", read_write};
  mapped_region region2{shdmem, read_only};

  int *i2 = static_cast<int*>(region2.get_address());
  std::cout << "Waiting  for data..." << '\n';

  named_mutex named_mtx{open_or_create, "atl_mtx"};
  named_condition named_cnd{open_or_create, "atl_cnd"};
  scoped_lock<named_mutex> lock{named_mtx};
  
  named_cnd.wait(lock);
  std::cout << *i2 << '\n';

}
