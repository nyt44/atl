#pragma once

#include <string>
#include <functional>
#include <exception>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

class SharedMemoryTransporter
{
 public:
  explicit SharedMemoryTransporter(const std::string& name);
  void Send(void* data, size_t size);
  void Receive(std::function<void(void*)> callback);

 private:
  boost::interprocess::shared_memory_object shm_object_;
  boost::interprocess::mapped_region shm_region_;
  boost::interprocess::named_condition shm_condition_variable_;
  boost::interprocess::named_mutex shm_mutex_;
};

class TooBigDataSizeErrror : public std::runtime_error
{
 public:
  TooBigDataSizeErrror(const std::string& msg);
};
