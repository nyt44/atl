#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "ShmTransporterInterface.hpp"

namespace mocks
{

class ShmTransporterMock : public atl::ShmTransporterInterface
{
 public:
  MOCK_METHOD1(Send, void(const std::string&));
  MOCK_METHOD0(Receive, std::string());
};

class MockTransporterFactoryMethod : public atl::TransporterFactoryMethod
{
 public:
  std::unique_ptr<atl::ShmTransporterInterface> CreateTransporter(const std::string& name) override
  {
    return std::unique_ptr<ShmTransporterMock>(CreateTransporterRaw(name));
  }
  MOCK_METHOD1(CreateTransporterRaw, ShmTransporterMock*(const std::string&));
};

} // namespace mocks
