#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ConnectionMapWrapperInterface.hpp"

namespace mocks
{
class ConnectionMapWrapperMock : public atl::ConnectionMapWrapperInterface
{
 public:
  MOCK_METHOD1(AddEntry, bool(const std::string&));
  MOCK_METHOD1(DeleteEntry, bool(const std::string&));
  MOCK_METHOD1(IncreaseEntryRefCount, void(const std::string&));
  MOCK_METHOD1(DecreaseEntryRefCount, void(const std::string&));
  MOCK_CONST_METHOD1(GetEntryRefCount, int(const std::string&));
  MOCK_CONST_METHOD1(EntryExists, bool(const std::string&));
};

} // namespace mocks
