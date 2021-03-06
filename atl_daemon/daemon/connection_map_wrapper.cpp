#include "connection_map_wrapper.hpp"

#include "dbg_trace.hpp"

namespace atl
{

bool ConnectionMapWrapper::AddEntry(const std::string& connection_str)
{
  auto insertion_result = diary_.emplace(connection_str, connection_str);
  LOG_INFO("Added connection: {}", connection_str);
  return insertion_result.second;
}

bool ConnectionMapWrapper::DeleteEntry(const std::string& connection_str)
{
  LOG_INFO("Removed connection: {}", connection_str);
  return diary_.erase(connection_str) == 1;
}

void ConnectionMapWrapper::IncreaseEntryRefCount(const std::string& connection_str)
{
  auto& entry_ref = diary_.at(connection_str);
  ++(entry_ref.ref_count);
  LOG_INFO("Reference count of connection {} increased. Current value: {}", connection_str, entry_ref.ref_count);
}

void ConnectionMapWrapper::DecreaseEntryRefCount(const std::string& connection_str)
{
  auto& entry_ref = diary_.at(connection_str);
  --(entry_ref.ref_count);
  LOG_INFO("Reference count of connection {} decreased. Current value: {}", connection_str, entry_ref.ref_count);
}

int ConnectionMapWrapper::GetEntryRefCount(const std::string& connection_str) const
{
  return diary_.at(connection_str).ref_count;
}

bool ConnectionMapWrapper::EntryExists(const std::string& connection_str) const
{
  return diary_.find(connection_str) != diary_.end();
}

} // namespace atl
