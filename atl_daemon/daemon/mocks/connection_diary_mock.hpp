#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "connection_diary_interface.hpp"

namespace mocks
{

class ConnectionDiaryMock : public atl::ConnectionDiaryInterface
{
 public:
  MOCK_METHOD1(AddConnection, bool(const std::string&));
  MOCK_METHOD1(DeleteConnection, bool(const std::string&));
};

} // namespace mocks
