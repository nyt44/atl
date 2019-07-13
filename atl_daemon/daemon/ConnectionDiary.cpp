#include "ConnectionDiary.hpp"

namespace atl
{

ConnectionDiary::ConnectionDiary(ConnectionMapWrapperInterface& map_wrapper)
  : map_wrapper_{map_wrapper} {}

bool ConnectionDiary::AddConnection(const std::string& connection_str)
{
  bool result = false;
  if (!map_wrapper_.EntryExists(connection_str))
  {
    result =  map_wrapper_.AddEntry(connection_str);
  }
  else
  {
    map_wrapper_.IncreaseEntryRefCount(connection_str);
    result = true;
  }

  return result;
}

bool ConnectionDiary::DeleteConnection(const std::string& connection_str)
{
  if (map_wrapper_.EntryExists(connection_str))
  {
    if (map_wrapper_.GetEntryRefCount(connection_str) == 1)
    {
      return map_wrapper_.DeleteEntry(connection_str);
    }
    else
    {
      map_wrapper_.DecreaseEntryRefCount(connection_str);
      return true;
    }
  }

  return false;
}

} // namespace atl
