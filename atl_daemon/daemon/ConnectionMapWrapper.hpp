#pragma once

#include "ConnectionMapWrapperInterface.hpp"

#include <unordered_map>
#include <memory>

#include "Connection.hpp"

namespace atl
{

class ConnectionMapWrapper : public ConnectionMapWrapperInterface
{
 public:
  bool AddEntry(const std::string& connection_str) override;
  bool DeleteEntry(const std::string& connection_str) override;
  void IncreaseEntryRefCount(const std::string& connection_str) override;
  void DecreaseEntryRefCount(const std::string& connection_str) override;
  int GetEntryRefCount(const std::string& connection_str) const override;
  bool EntryExists(const std::string& connection_str) const override;

 private:
  struct Entry
  {
    explicit Entry(const std::string& s) : connection{s} {}
    Connection connection;
    int ref_count{0};
  };
  std::unordered_map<std::string, Entry> diary_;
};

} // namespace atl
