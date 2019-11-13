#pragma once

#include <string>

namespace atl
{

class ConnectionMapWrapperInterface
{
 public:
  virtual ~ConnectionMapWrapperInterface() = default;
  virtual bool AddEntry(const std::string& connection_str) = 0;
  virtual bool DeleteEntry(const std::string& connection_str) = 0;
  virtual void IncreaseEntryRefCount(const std::string& connection_str) = 0;
  virtual void DecreaseEntryRefCount(const std::string& connection_str) = 0;
  virtual int GetEntryRefCount(const std::string& connection_str) const = 0;
  virtual bool EntryExists(const std::string& connection_str) const = 0;
};

} // namespace atl
