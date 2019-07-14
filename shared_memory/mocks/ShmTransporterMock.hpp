#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ShmTransporterInterface.hpp"

namespace mocks
{

class ShmTransporterMock : public atl::ShmTransporterInterface
{
 public:
  MOCK_METHOD2(Send, void(void*, size_t));
  MOCK_METHOD1(Receive, void(std::function<void(void*)>));
  MOCK_METHOD0(Receive, std::string());
};

} // namespace mocks
